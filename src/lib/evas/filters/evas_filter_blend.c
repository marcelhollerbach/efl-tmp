#include "evas_filter.h"
#include "evas_filter_private.h"
#include "evas_blend_private.h"

#if DIV_USING_BITSHIFT
static int
_smallest_pow2_larger_than(int val)
{
   int n;

   for (n = 0; n < 32; n++)
     if (val <= (1 << n)) return n;

   ERR("Value %d is too damn high!", val);
   return 32;
}
# define DEFINE_DIVIDER(div) const int pow2 = _smallest_pow2_larger_than((div) << 10); const int numerator = (1 << pow2) / (div);
# define DIVIDE(val) (((val) * numerator) >> pow2)
#else
# define DEFINE_DIAMETER(div) const int divider = (div);
# define DIVIDE(val) ((val) / divider)
#endif

typedef Eina_Bool (*image_draw_func) (void *data, void *context, void *surface, void *image, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, int smooth, Eina_Bool do_async);
static void _mapped_blend_cpu(void *data, void *drawctx, RGBA_Image *in, RGBA_Image *out, Evas_Filter_Fill_Mode fillmode, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh, image_draw_func image_draw);

struct Alpha_Blend_Draw_Context
{
   int render_op;
   DATA32 color;
};

static Eina_Bool
_image_draw_cpu_alpha2alpha(void *data EINA_UNUSED, void *context,
                            void *surface, void *image,
                            int src_x, int src_y, int src_w, int src_h,
                            int dst_x, int dst_y, int dst_w, int dst_h,
                            int smooth EINA_UNUSED,
                            Eina_Bool do_async EINA_UNUSED)
{
   struct Alpha_Blend_Draw_Context *dc = context;
   RGBA_Image *src = image;
   RGBA_Image *dst = surface;
   DATA8* srcdata = src->mask.data;
   DATA8* dstdata = dst->mask.data;
   Alpha_Gfx_Func func;
   int y, sw, dw;

   EINA_SAFETY_ON_FALSE_RETURN_VAL((src_w == dst_w) && (src_h == dst_h), EINA_FALSE);

   func = evas_common_alpha_func_get(dc->render_op);
   EINA_SAFETY_ON_NULL_RETURN_VAL(func, EINA_FALSE);

   sw = src->cache_entry.w;
   dw = dst->cache_entry.w;

   srcdata += src_y * sw;
   dstdata += dst_y * dw;
   for (y = src_h; y; y--)
     {
        func(srcdata + src_x, dstdata + dst_x, src_w);
        srcdata += sw;
        dstdata += dw;
     }

   return EINA_TRUE;
}

static Eina_Bool
_image_draw_cpu_alpha2rgba(void *data EINA_UNUSED, void *context,
                           void *surface, void *image,
                           int src_x, int src_y, int src_w, int src_h,
                           int dst_x, int dst_y, int dst_w, int dst_h,
                           int smooth EINA_UNUSED,
                           Eina_Bool do_async EINA_UNUSED)
{
   struct Alpha_Blend_Draw_Context *dc = context;
   RGBA_Image *src = image;
   RGBA_Image *dst = surface;
   DATA8* srcdata = src->mask.data;
   DATA32* dstdata = dst->image.data;
   RGBA_Gfx_Func func;
   int y, sw, dw;

   EINA_SAFETY_ON_FALSE_RETURN_VAL((src_w == dst_w) && (src_h == dst_h), EINA_FALSE);

   func = evas_common_gfx_func_composite_mask_color_span_get
     (dc->color, surface, 1, dc->render_op);
   EINA_SAFETY_ON_NULL_RETURN_VAL(func, EINA_FALSE);

   sw = src->cache_entry.w;
   dw = dst->cache_entry.w;

   srcdata += src_y * sw;
   dstdata += dst_y * dw;
   for (y = src_h; y; y--)
     {
        func(NULL, srcdata + src_x, dc->color, dstdata + dst_x, src_w);
        srcdata += sw;
        dstdata += dw;
     }

   return EINA_TRUE;
}

static Eina_Bool
_filter_blend_cpu_generic_do(Evas_Filter_Command *cmd,
                             image_draw_func image_draw)
{
   RGBA_Image *in, *out;
   int sw, sh, dx, dy, dw, dh, sx, sy;
   struct Alpha_Blend_Draw_Context dc;

   in = cmd->input->backing;
   out = cmd->output->backing;
   EINA_SAFETY_ON_NULL_RETURN_VAL(in, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(out, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(in->mask.data, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(out->mask.data, EINA_FALSE);

   sx = 0;
   sy = 0;
   sw = in->cache_entry.w;
   sh = in->cache_entry.h;

   dx = cmd->draw.ox;
   dy = cmd->draw.oy;
   dw = out->cache_entry.w;
   dh = out->cache_entry.h;

   if ((dw <= 0) || (dh <= 0) || (sw <= 0) || (sh <= 0))
     return EINA_TRUE;

   // Stretch if necessary.

   /* NOTE: As of 2014/02/21, this case is impossible. An alpha buffer will
    * always be of the context buffer size, since only proxy buffers have
    * different sizes... and proxies are all RGBA (never alpha only).
    */

   if ((sw != dw || sh != dh) && (cmd->draw.fillmode & EVAS_FILTER_FILL_MODE_STRETCH_XY))
     {
        Evas_Filter_Buffer *fb;

        if (cmd->draw.fillmode & EVAS_FILTER_FILL_MODE_STRETCH_X)
          sw = dw;
        if (cmd->draw.fillmode & EVAS_FILTER_FILL_MODE_STRETCH_Y)
          sh = dh;

        BUFFERS_LOCK();
        fb = evas_filter_buffer_scaled_get(cmd->ctx, cmd->input, sw, sh);
        BUFFERS_UNLOCK();

        EINA_SAFETY_ON_NULL_RETURN_VAL(fb, EINA_FALSE);
        fb->locked = EINA_FALSE;
        in = fb->backing;
     }

   dc.render_op = cmd->draw.render_op;
   dc.color = ARGB_JOIN(cmd->draw.A, cmd->draw.R, cmd->draw.G, cmd->draw.B);
   _mapped_blend_cpu(cmd->ENDT, &dc, in, out, cmd->draw.fillmode,
                     sx, sy, sw, sh, dx, dy, dw, dh, image_draw);

   return EINA_TRUE;
}

static Eina_Bool
_image_draw_cpu_rgba2alpha(void *data EINA_UNUSED, void *context EINA_UNUSED,
                           void *surface, void *image,
                           int src_x, int src_y, int src_w, int src_h,
                           int dst_x, int dst_y, int dst_w, int dst_h,
                           int smooth EINA_UNUSED,
                           Eina_Bool do_async EINA_UNUSED)
{
   RGBA_Image *src = image;
   RGBA_Image *dst = surface;
   DATA32* srcdata = src->image.data;
   DATA8* dstdata = dst->mask.data;
   int x, y, sw, dw;
   DEFINE_DIVIDER(3);

   EINA_SAFETY_ON_FALSE_RETURN_VAL((src_w == dst_w) && (src_h == dst_h), EINA_FALSE);

   sw = src->cache_entry.w;
   dw = dst->cache_entry.w;

   srcdata += src_y * sw;
   dstdata += dst_y * dw;
   for (y = src_h; y; y--)
     {
        DATA32 *s = srcdata + src_x;
        DATA8 *d = dstdata + dst_x;
        for (x = src_w; x; x--, d++, s++)
          {
             // TODO: Add weights like in YUV <--> RGB?
             *d = DIVIDE(R_VAL(s) + G_VAL(s) + B_VAL(s));
          }
        srcdata += sw;
        dstdata += dw;
     }

   return EINA_TRUE;
}

static Eina_Bool
_filter_blend_cpu_alpha(Evas_Filter_Command *cmd)
{
   return _filter_blend_cpu_generic_do(cmd, _image_draw_cpu_alpha2alpha);
}

static Eina_Bool
_filter_blend_cpu_mask_rgba(Evas_Filter_Command *cmd)
{
   return _filter_blend_cpu_generic_do(cmd, _image_draw_cpu_alpha2rgba);
}

static Eina_Bool
_filter_blend_cpu_rgba2alpha(Evas_Filter_Command *cmd)
{
   return _filter_blend_cpu_generic_do(cmd, _image_draw_cpu_rgba2alpha);
}

static Eina_Bool
_filter_blend_cpu_rgba(Evas_Filter_Command *cmd)
{
   RGBA_Image *in, *out;
   RGBA_Draw_Context *drawctx;
   int sw, sh, dx, dy, dw, dh, sx, sy;

   in = cmd->input->backing;
   out = cmd->output->backing;
   EINA_SAFETY_ON_NULL_RETURN_VAL(in, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(out, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(in->image.data, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(out->image.data, EINA_FALSE);

   sx = 0;
   sy = 0;
   sw = in->cache_entry.w;
   sh = in->cache_entry.h;

   dx = cmd->draw.ox;
   dy = cmd->draw.oy;
   dw = out->cache_entry.w;
   dh = out->cache_entry.h;

   if ((dw <= 0) || (dh <= 0) || (sw <= 0) || (sh <= 0))
     return EINA_TRUE;

   drawctx = cmd->ENFN->context_new(cmd->ENDT);
   cmd->ENFN->context_color_set(cmd->ENDT, drawctx, cmd->draw.R, cmd->draw.G,
                                cmd->draw.B, cmd->draw.A);
   cmd->ENFN->context_render_op_set(cmd->ENDT, drawctx, cmd->draw.render_op);

   if (cmd->draw.clip_use)
     {
        cmd->ENFN->context_clip_set(cmd->ENDT, drawctx,
                                    cmd->draw.clip.x, cmd->draw.clip.y,
                                    cmd->draw.clip.w, cmd->draw.clip.h);
        cmd->ENFN->context_clip_clip(cmd->ENDT, drawctx, 0, 0,
                                     out->cache_entry.w, out->cache_entry.h);
     }
   else
     {
        cmd->ENFN->context_clip_set(cmd->ENDT, drawctx, 0, 0,
                                    out->cache_entry.w, out->cache_entry.h);
     }

   _mapped_blend_cpu(cmd->ENDT, drawctx, in, out, cmd->draw.fillmode,
                     sx, sy, sw, sh, dx, dy, dw, dh,
                     cmd->ENFN->image_draw);

   cmd->ENFN->context_free(cmd->ENDT, drawctx);
   return EINA_TRUE;
}

static void
_mapped_blend_cpu(void *data, void *drawctx,
                  RGBA_Image *in, RGBA_Image *out,
                  Evas_Filter_Fill_Mode fillmode,
                  int sx, int sy,
                  int sw, int sh,
                  int dx, int dy,
                  int dw, int dh,
                  image_draw_func image_draw)
{
   int right = 0, bottom = 0, left = 0, top = 0;
   int row, col, rows, cols;

   if (fillmode == EVAS_FILTER_FILL_MODE_NONE)
     {
        _clip_to_target(&sx, &sy, sw, sh, dx, dy, out->cache_entry.w,
                        out->cache_entry.h, &dx, &dy, &rows, &cols);

        DBG("blend: %d,%d,%d,%d --> %d,%d,%d,%d (from %dx%d to %dx%d +%d,%d)",
            0, 0, sw, sh, dx, dy, cols, rows,
            in->cache_entry.w, in->cache_entry.h,
            out->cache_entry.w, out->cache_entry.h,
            dx, dy);
        image_draw(data, drawctx, out, in,
                   sx, sy, cols, rows, // src
                   dx, dy, cols, rows, // dst
                   EINA_TRUE, // smooth
                   EINA_FALSE); // Not async
        return;
     }

   if (fillmode & EVAS_FILTER_FILL_MODE_REPEAT_X)
     {
        if (dx > 0) left = dx % sw;
        else if (dx < 0) left = sw + (dx % sw);
        cols = (dw  /*- left*/) / sw;
        if (left > 0)
          right = dw - (sw * (cols - 1)) - left;
        else
          right = dw - (sw * cols);
        dx = 0;
     }
   else if (fillmode & EVAS_FILTER_FILL_MODE_STRETCH_X)
     {
        cols = 0;
        dw = out->cache_entry.w;
        dx = 0;
     }
   else
     {
        cols = 0;
        dw = out->cache_entry.w - dx;
     }

   if (fillmode & EVAS_FILTER_FILL_MODE_REPEAT_Y)
     {
        if (dy > 0) top = dy % sh;
        else if (dy < 0) top = sh + (dy % sh);
        rows = (dh /*- top*/) / sh;
        if (top > 0)
          bottom = dh - (sh * (rows - 1)) - top;
        else
          bottom = dh - (sh * rows);
        dy = 0;
     }
   else if (fillmode & EVAS_FILTER_FILL_MODE_STRETCH_Y)
     {
        rows = 0;
        dh = out->cache_entry.h;
        dy = 0;
     }
   else
     {
        rows = 0;
        dh = out->cache_entry.h - dy;
     }

   if (top > 0) row = -1;
   else row = 0;
   for (; row <= rows; row++)
     {
        int src_x, src_y, src_w, src_h;
        int dst_x, dst_y, dst_w, dst_h;

        if (row == -1 && top > 0)
          {
             // repeat only
             src_h = top;
             src_y = sh - top;
             dst_y = dy;
             dst_h = src_h;
          }
        else if (row == rows && bottom > 0)
          {
             // repeat only
             src_h = bottom;
             src_y = 0;
             dst_y = top + dy + row * sh;
             dst_h = src_h;
          }
        else
          {
             src_y = 0;
             if (fillmode & EVAS_FILTER_FILL_MODE_STRETCH_Y)
               {
                  src_h = sh;
                  dst_h = dh;
                  dst_y = 0;
               }
             else
               {
                  dst_y = top + dy + row * sh;
                  src_h = MIN(dh - dst_y, sh);
                  dst_h = src_h;
               }
          }
        if (src_h <= 0 || dst_h <= 0) break;

        if (left > 0) col = -1;
        else col = 0;
        for (; col <= cols; col++)
          {
             if (col == -1 && left > 0)
               {
                  // repeat only
                  src_w = left;
                  src_x = sw - left;
                  dst_x = dx;
                  dst_w = src_w;
               }
             else if (col == cols && right > 0)
               {
                  // repeat only
                  src_w = right;
                  src_x = 0;
                  dst_x = left + dx + col * sw;
                  dst_w = src_w;
               }
             else
               {
                  src_x = 0;
                  if (fillmode & EVAS_FILTER_FILL_MODE_STRETCH_X)
                    {
                       src_w = sw;
                       dst_w = dw;
                       dst_x = 0;
                    }
                  else
                    {
                       dst_x = left + dx + col * sw;
                       src_w = MIN(dw - dst_x, sw);
                       dst_w = src_w;
                    }
               }
             if (src_w <= 0 || dst_w <= 0) break;

             DBG("blend: [%d,%d] %d,%d,%dx%d --> %d,%d,%dx%d "
                 "(src %dx%d, dst %dx%d)",
                 col, row, src_x, src_y, src_w, src_h,
                 dst_x, dst_y, dst_w, dst_h,
                 sw, sh, dw, dh);
             image_draw(data, drawctx, out, in,
                        src_x, src_y, src_w, src_h,
                        dst_x, dst_y, dst_w, dst_h,
                        EINA_TRUE, EINA_FALSE);
          }
     }
}

Evas_Filter_Apply_Func
evas_filter_blend_cpu_func_get(Evas_Filter_Command *cmd)
{
   EINA_SAFETY_ON_NULL_RETURN_VAL(cmd, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(cmd->output, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(cmd->input, NULL);

   if (cmd->input->alpha_only)
     {
        if (cmd->output->alpha_only)
          return _filter_blend_cpu_alpha;
        else
          return _filter_blend_cpu_mask_rgba;
     }
   else
     {
        if (cmd->output->alpha_only)
          return _filter_blend_cpu_rgba2alpha;
        else
          return _filter_blend_cpu_rgba;
     }
}
