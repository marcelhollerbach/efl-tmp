/**
 * @defgroup List List
 * @ingroup Elementary
 *
 * @image html img/widget/list/preview-00.png
 * @image latex img/widget/list/preview-00.eps width=\textwidth
 *
 * @image html img/list.png
 * @image latex img/list.eps width=\textwidth
 *
 * A list widget is a container whose children are displayed vertically or
 * horizontally, in order, and can be selected.
 * The list can accept only one or multiple items selection. Also has many
 * modes of items displaying.
 *
 * A list is a very simple type of list widget.  For more robust
 * lists, @ref Genlist should probably be used.
 *
 * Smart callbacks one can listen to:
 * - @c "activated" - The user has double-clicked or pressed
 *   (enter|return|spacebar) on an item. The @c event_info parameter
 *   is the item that was activated.
 * - @c "clicked,double" - The user has double-clicked an item.
 *   The @c event_info parameter is the item that was double-clicked.
 * - "selected" - when the user selected an item
 * - "unselected" - when the user unselected an item
 * - "longpressed" - an item in the list is long-pressed
 * - "edge,top" - the list is scrolled until the top edge
 * - "edge,bottom" - the list is scrolled until the bottom edge
 * - "edge,left" - the list is scrolled until the left edge
 * - "edge,right" - the list is scrolled until the right edge
 * - "language,changed" - the program's language changed
 *
 * Available styles for it:
 * - @c "default"
 *
 * List of examples:
 * @li @ref list_example_01
 * @li @ref list_example_02
 * @li @ref list_example_03
 */

/**
 * @addtogroup List
 * @{
 */

/**
 * @enum _Elm_List_Mode
 * @typedef Elm_List_Mode
 *
 * Set list's resize behavior, transverse axis scroll and
 * items cropping. See each mode's description for more details.
 *
 * @note Default value is #ELM_LIST_SCROLL.
 *
 * Values <b> don't </b> work as bitmask, only one can be choosen.
 *
 * @see elm_list_mode_set()
 * @see elm_list_mode_get()
 *
 * @ingroup List
 */
typedef enum
{
   ELM_LIST_COMPRESS = 0, /**< Won't set any of its size hints to inform how a possible container should resize it. Then, if it's not created as a "resize object", it might end with zero dimensions. The list will respect the container's geometry and, if any of its items won't fit into its transverse axis, one won't be able to scroll it in that direction. */
   ELM_LIST_SCROLL, /**< Default value. Won't set any of its size hints to inform how a possible container should resize it. Then, if it's not created as a "resize object", it might end with zero dimensions. The list will respect the container's geometry and, if any of its items won't fit into its transverse axis, one will be able to scroll it in that direction (large items will get cropped). */
   ELM_LIST_LIMIT, /**< Set a minimun size hint on the list object, so that containers may respect it (and resize itself to fit the child properly). More specifically, a minimum size hint will be set for its transverse axis, so that the @b largest item in that direction fits well. Can have effects bounded by setting the list object's maximum size hints. */
   ELM_LIST_EXPAND, /**< Besides setting a minimum size on the transverse axis, just like the previous mode, will set a minimum size on the longitudinal axis too, trying to reserve space to all its children to be visible at a time. Can have effects bounded by setting the list object's maximum size hints. */
   ELM_LIST_LAST /**< Indicates error if returned by elm_list_mode_get() */
} Elm_List_Mode;

typedef struct _Elm_List_Item Elm_List_Item;    /**< Item of Elm_List. Sub-type of Elm_Widget_Item. Can be created with elm_list_item_append(), elm_list_item_prepend() and functions to add items in relative positions, like elm_list_item_insert_before(), and deleted with elm_list_item_del().  */

/**
 * Add a new list widget to the given parent Elementary
 * (container) object.
 *
 * @param parent The parent object.
 * @return a new list widget handle or @c NULL, on errors.
 *
 * This function inserts a new list widget on the canvas.
 *
 * @ingroup List
 */
EAPI Evas_Object                 *elm_list_add(Evas_Object *parent);

/**
 * Starts the list.
 *
 * @param obj The list object
 *
 * @note Call before running show() on the list object.
 * @warning If not called, it won't display the list properly.
 *
 * @code
 * li = elm_list_add(win);
 * elm_list_item_append(li, "First", NULL, NULL, NULL, NULL);
 * elm_list_item_append(li, "Second", NULL, NULL, NULL, NULL);
 * elm_list_go(li);
 * evas_object_show(li);
 * @endcode
 *
 * @ingroup List
 */
EAPI void                         elm_list_go(Evas_Object *obj);

/**
 * Enable or disable multiple items selection on the list object.
 *
 * @param obj The list object
 * @param multi @c EINA_TRUE to enable multi selection or @c EINA_FALSE to
 * disable it.
 *
 * Disabled by default. If disabled, the user can select a single item of
 * the list each time. Selected items are highlighted on list.
 * If enabled, many items can be selected.
 *
 * If a selected item is selected again, it will be unselected.
 *
 * @see elm_list_multi_select_get()
 *
 * @ingroup List
 */
EAPI void                         elm_list_multi_select_set(Evas_Object *obj, Eina_Bool multi);

/**
 * Get a value whether multiple items selection is enabled or not.
 *
 * @see elm_list_multi_select_set() for details.
 *
 * @param obj The list object.
 * @return @c EINA_TRUE means multiple items selection is enabled.
 * @c EINA_FALSE indicates it's disabled. If @p obj is @c NULL,
 * @c EINA_FALSE is returned.
 *
 * @ingroup List
 */
EAPI Eina_Bool                    elm_list_multi_select_get(const Evas_Object *obj);

/**
 * Set which mode to use for the list object.
 *
 * @param obj The list object
 * @param mode One of #Elm_List_Mode: #ELM_LIST_COMPRESS, #ELM_LIST_SCROLL,
 * #ELM_LIST_LIMIT or #ELM_LIST_EXPAND.
 *
 * Set list's resize behavior, transverse axis scroll and
 * items cropping. See each mode's description for more details.
 *
 * @note Default value is #ELM_LIST_SCROLL.
 *
 * Only one can be set, if a previous one was set, it will be changed
 * by the new mode set. Bitmask won't work as well.
 *
 * @see elm_list_mode_get()
 *
 * @ingroup List
 */
EAPI void                         elm_list_mode_set(Evas_Object *obj, Elm_List_Mode mode);

/**
 * Get the mode the list is at.
 *
 * @param obj The list object
 * @return One of #Elm_List_Mode: #ELM_LIST_COMPRESS, #ELM_LIST_SCROLL,
 * #ELM_LIST_LIMIT, #ELM_LIST_EXPAND or #ELM_LIST_LAST on errors.
 *
 * @note see elm_list_mode_set() for more information.
 *
 * @ingroup List
 */
EAPI Elm_List_Mode                elm_list_mode_get(const Evas_Object *obj);

/**
 * Enable or disable horizontal mode on the list object.
 *
 * @param obj The list object.
 * @param horizontal @c EINA_TRUE to enable horizontal or @c EINA_FALSE to
 * disable it, i.e., to enable vertical mode.
 *
 * @note Vertical mode is set by default.
 *
 * On horizontal mode items are displayed on list from left to right,
 * instead of from top to bottom. Also, the list will scroll horizontally.
 * Each item will presents left icon on top and right icon, or end, at
 * the bottom.
 *
 * @see elm_list_horizontal_get()
 *
 * @ingroup List
 */
EAPI void                         elm_list_horizontal_set(Evas_Object *obj, Eina_Bool horizontal);

/**
 * Get a value whether horizontal mode is enabled or not.
 *
 * @param obj The list object.
 * @return @c EINA_TRUE means horizontal mode selection is enabled.
 * @c EINA_FALSE indicates it's disabled. If @p obj is @c NULL,
 * @c EINA_FALSE is returned.
 *
 * @see elm_list_horizontal_set() for details.
 *
 * @ingroup List
 */
EAPI Eina_Bool                    elm_list_horizontal_get(const Evas_Object *obj);

/**
 * Enable or disable always select mode on the list object.
 *
 * @param obj The list object
 * @param always_select @c EINA_TRUE to enable always select mode or
 * @c EINA_FALSE to disable it.
 *
 * @note Always select mode is disabled by default.
 *
 * Default behavior of list items is to only call its callback function
 * the first time it's pressed, i.e., when it is selected. If a selected
 * item is pressed again, and multi-select is disabled, it won't call
 * this function (if multi-select is enabled it will unselect the item).
 *
 * If always select is enabled, it will call the callback function
 * everytime a item is pressed, so it will call when the item is selected,
 * and again when a selected item is pressed.
 *
 * @see elm_list_always_select_mode_get()
 * @see elm_list_multi_select_set()
 *
 * @ingroup List
 */
EAPI void                         elm_list_always_select_mode_set(Evas_Object *obj, Eina_Bool always_select);

/**
 * Get a value whether always select mode is enabled or not, meaning that
 * an item will always call its callback function, even if already selected.
 *
 * @param obj The list object
 * @return @c EINA_TRUE means horizontal mode selection is enabled.
 * @c EINA_FALSE indicates it's disabled. If @p obj is @c NULL,
 * @c EINA_FALSE is returned.
 *
 * @see elm_list_always_select_mode_set() for details.
 *
 * @ingroup List
 */
EAPI Eina_Bool                    elm_list_always_select_mode_get(const Evas_Object *obj);

/**
 * Set bouncing behaviour when the scrolled content reaches an edge.
 *
 * Tell the internal scroller object whether it should bounce or not
 * when it reaches the respective edges for each axis.
 *
 * @param obj The list object
 * @param h_bounce Whether to bounce or not in the horizontal axis.
 * @param v_bounce Whether to bounce or not in the vertical axis.
 *
 * @see elm_scroller_bounce_set()
 *
 * @ingroup List
 */
EAPI void                         elm_list_bounce_set(Evas_Object *obj, Eina_Bool h_bounce, Eina_Bool v_bounce);

/**
 * Get the bouncing behaviour of the internal scroller.
 *
 * Get whether the internal scroller should bounce when the edge of each
 * axis is reached scrolling.
 *
 * @param obj The list object.
 * @param h_bounce Pointer where to store the bounce state of the horizontal
 * axis.
 * @param v_bounce Pointer where to store the bounce state of the vertical
 * axis.
 *
 * @see elm_scroller_bounce_get()
 * @see elm_list_bounce_set()
 *
 * @ingroup List
 */
EAPI void                         elm_list_bounce_get(const Evas_Object *obj, Eina_Bool *h_bounce, Eina_Bool *v_bounce);

/**
 * Set the scrollbar policy.
 *
 * @param obj The list object
 * @param policy_h Horizontal scrollbar policy.
 * @param policy_v Vertical scrollbar policy.
 *
 * This sets the scrollbar visibility policy for the given scroller.
 * #ELM_SCROLLER_POLICY_AUTO means the scrollbar is made visible if it
 * is needed, and otherwise kept hidden. #ELM_SCROLLER_POLICY_ON turns
 * it on all the time, and #ELM_SCROLLER_POLICY_OFF always keeps it off.
 * This applies respectively for the horizontal and vertical scrollbars.
 *
 * The both are disabled by default, i.e., are set to
 * #ELM_SCROLLER_POLICY_OFF.
 *
 * @ingroup List
 */
EAPI void                         elm_list_scroller_policy_set(Evas_Object *obj, Elm_Scroller_Policy policy_h, Elm_Scroller_Policy policy_v);

/**
 * Get the scrollbar policy.
 *
 * @see elm_list_scroller_policy_get() for details.
 *
 * @param obj The list object.
 * @param policy_h Pointer where to store horizontal scrollbar policy.
 * @param policy_v Pointer where to store vertical scrollbar policy.
 *
 * @ingroup List
 */
EAPI void                         elm_list_scroller_policy_get(const Evas_Object *obj, Elm_Scroller_Policy *policy_h, Elm_Scroller_Policy *policy_v);

/**
 * Append a new item to the list object.
 *
 * @param obj The list object.
 * @param label The label of the list item.
 * @param icon The icon object to use for the left side of the item. An
 * icon can be any Evas object, but usually it is an icon created
 * with elm_icon_add().
 * @param end The icon object to use for the right side of the item. An
 * icon can be any Evas object.
 * @param func The function to call when the item is clicked.
 * @param data The data to associate with the item for related callbacks.
 *
 * @return The created item or @c NULL upon failure.
 *
 * A new item will be created and appended to the list, i.e., will
 * be set as @b last item.
 *
 * Items created with this method can be deleted with
 * elm_list_item_del().
 *
 * Associated @p data can be properly freed when item is deleted if a
 * callback function is set with elm_list_item_del_cb_set().
 *
 * If a function is passed as argument, it will be called everytime this item
 * is selected, i.e., the user clicks over an unselected item.
 * If always select is enabled it will call this function every time
 * user clicks over an item (already selected or not).
 * If such function isn't needed, just passing
 * @c NULL as @p func is enough. The same should be done for @p data.
 *
 * Simple example (with no function callback or data associated):
 * @code
 * li = elm_list_add(win);
 * ic = elm_icon_add(win);
 * elm_icon_file_set(ic, "path/to/image", NULL);
 * elm_icon_scale_set(ic, EINA_TRUE, EINA_TRUE);
 * elm_list_item_append(li, "label", ic, NULL, NULL, NULL);
 * elm_list_go(li);
 * evas_object_show(li);
 * @endcode
 *
 * @see elm_list_always_select_mode_set()
 * @see elm_list_item_del()
 * @see elm_list_item_del_cb_set()
 * @see elm_list_clear()
 * @see elm_icon_add()
 *
 * @ingroup List
 */
EAPI Elm_List_Item               *elm_list_item_append(Evas_Object *obj, const char *label, Evas_Object *icon, Evas_Object *end, Evas_Smart_Cb func, const void *data);

/**
 * Prepend a new item to the list object.
 *
 * @param obj The list object.
 * @param label The label of the list item.
 * @param icon The icon object to use for the left side of the item. An
 * icon can be any Evas object, but usually it is an icon created
 * with elm_icon_add().
 * @param end The icon object to use for the right side of the item. An
 * icon can be any Evas object.
 * @param func The function to call when the item is clicked.
 * @param data The data to associate with the item for related callbacks.
 *
 * @return The created item or @c NULL upon failure.
 *
 * A new item will be created and prepended to the list, i.e., will
 * be set as @b first item.
 *
 * Items created with this method can be deleted with
 * elm_list_item_del().
 *
 * Associated @p data can be properly freed when item is deleted if a
 * callback function is set with elm_list_item_del_cb_set().
 *
 * If a function is passed as argument, it will be called everytime this item
 * is selected, i.e., the user clicks over an unselected item.
 * If always select is enabled it will call this function every time
 * user clicks over an item (already selected or not).
 * If such function isn't needed, just passing
 * @c NULL as @p func is enough. The same should be done for @p data.
 *
 * @see elm_list_item_append() for a simple code example.
 * @see elm_list_always_select_mode_set()
 * @see elm_list_item_del()
 * @see elm_list_item_del_cb_set()
 * @see elm_list_clear()
 * @see elm_icon_add()
 *
 * @ingroup List
 */
EAPI Elm_List_Item               *elm_list_item_prepend(Evas_Object *obj, const char *label, Evas_Object *icon, Evas_Object *end, Evas_Smart_Cb func, const void *data);

/**
 * Insert a new item into the list object before item @p before.
 *
 * @param obj The list object.
 * @param before The list item to insert before.
 * @param label The label of the list item.
 * @param icon The icon object to use for the left side of the item. An
 * icon can be any Evas object, but usually it is an icon created
 * with elm_icon_add().
 * @param end The icon object to use for the right side of the item. An
 * icon can be any Evas object.
 * @param func The function to call when the item is clicked.
 * @param data The data to associate with the item for related callbacks.
 *
 * @return The created item or @c NULL upon failure.
 *
 * A new item will be created and added to the list. Its position in
 * this list will be just before item @p before.
 *
 * Items created with this method can be deleted with
 * elm_list_item_del().
 *
 * Associated @p data can be properly freed when item is deleted if a
 * callback function is set with elm_list_item_del_cb_set().
 *
 * If a function is passed as argument, it will be called everytime this item
 * is selected, i.e., the user clicks over an unselected item.
 * If always select is enabled it will call this function every time
 * user clicks over an item (already selected or not).
 * If such function isn't needed, just passing
 * @c NULL as @p func is enough. The same should be done for @p data.
 *
 * @see elm_list_item_append() for a simple code example.
 * @see elm_list_always_select_mode_set()
 * @see elm_list_item_del()
 * @see elm_list_item_del_cb_set()
 * @see elm_list_clear()
 * @see elm_icon_add()
 *
 * @ingroup List
 */
EAPI Elm_List_Item               *elm_list_item_insert_before(Evas_Object *obj, Elm_List_Item *before, const char *label, Evas_Object *icon, Evas_Object *end, Evas_Smart_Cb func, const void *data);

/**
 * Insert a new item into the list object after item @p after.
 *
 * @param obj The list object.
 * @param after The list item to insert after.
 * @param label The label of the list item.
 * @param icon The icon object to use for the left side of the item. An
 * icon can be any Evas object, but usually it is an icon created
 * with elm_icon_add().
 * @param end The icon object to use for the right side of the item. An
 * icon can be any Evas object.
 * @param func The function to call when the item is clicked.
 * @param data The data to associate with the item for related callbacks.
 *
 * @return The created item or @c NULL upon failure.
 *
 * A new item will be created and added to the list. Its position in
 * this list will be just after item @p after.
 *
 * Items created with this method can be deleted with
 * elm_list_item_del().
 *
 * Associated @p data can be properly freed when item is deleted if a
 * callback function is set with elm_list_item_del_cb_set().
 *
 * If a function is passed as argument, it will be called everytime this item
 * is selected, i.e., the user clicks over an unselected item.
 * If always select is enabled it will call this function every time
 * user clicks over an item (already selected or not).
 * If such function isn't needed, just passing
 * @c NULL as @p func is enough. The same should be done for @p data.
 *
 * @see elm_list_item_append() for a simple code example.
 * @see elm_list_always_select_mode_set()
 * @see elm_list_item_del()
 * @see elm_list_item_del_cb_set()
 * @see elm_list_clear()
 * @see elm_icon_add()
 *
 * @ingroup List
 */
EAPI Elm_List_Item               *elm_list_item_insert_after(Evas_Object *obj, Elm_List_Item *after, const char *label, Evas_Object *icon, Evas_Object *end, Evas_Smart_Cb func, const void *data);

/**
 * Insert a new item into the sorted list object.
 *
 * @param obj The list object.
 * @param label The label of the list item.
 * @param icon The icon object to use for the left side of the item. An
 * icon can be any Evas object, but usually it is an icon created
 * with elm_icon_add().
 * @param end The icon object to use for the right side of the item. An
 * icon can be any Evas object.
 * @param func The function to call when the item is clicked.
 * @param data The data to associate with the item for related callbacks.
 * @param cmp_func The comparing function to be used to sort list
 * items <b>by #Elm_List_Item item handles</b>. This function will
 * receive two items and compare them, returning a non-negative integer
 * if the second item should be place after the first, or negative value
 * if should be placed before.
 *
 * @return The created item or @c NULL upon failure.
 *
 * @note This function inserts values into a list object assuming it was
 * sorted and the result will be sorted.
 *
 * A new item will be created and added to the list. Its position in
 * this list will be found comparing the new item with previously inserted
 * items using function @p cmp_func.
 *
 * Items created with this method can be deleted with
 * elm_list_item_del().
 *
 * Associated @p data can be properly freed when item is deleted if a
 * callback function is set with elm_list_item_del_cb_set().
 *
 * If a function is passed as argument, it will be called everytime this item
 * is selected, i.e., the user clicks over an unselected item.
 * If always select is enabled it will call this function every time
 * user clicks over an item (already selected or not).
 * If such function isn't needed, just passing
 * @c NULL as @p func is enough. The same should be done for @p data.
 *
 * @see elm_list_item_append() for a simple code example.
 * @see elm_list_always_select_mode_set()
 * @see elm_list_item_del()
 * @see elm_list_item_del_cb_set()
 * @see elm_list_clear()
 * @see elm_icon_add()
 *
 * @ingroup List
 */
EAPI Elm_List_Item               *elm_list_item_sorted_insert(Evas_Object *obj, const char *label, Evas_Object *icon, Evas_Object *end, Evas_Smart_Cb func, const void *data, Eina_Compare_Cb cmp_func);

/**
 * Remove all list's items.
 *
 * @param obj The list object
 *
 * @see elm_list_item_del()
 * @see elm_list_item_append()
 *
 * @ingroup List
 */
EAPI void                         elm_list_clear(Evas_Object *obj);

/**
 * Get a list of all the list items.
 *
 * @param obj The list object
 * @return An @c Eina_List of list items, #Elm_List_Item,
 * or @c NULL on failure.
 *
 * @see elm_list_item_append()
 * @see elm_list_item_del()
 * @see elm_list_clear()
 *
 * @ingroup List
 */
EAPI const Eina_List             *elm_list_items_get(const Evas_Object *obj);

/**
 * Get the selected item.
 *
 * @param obj The list object.
 * @return The selected list item.
 *
 * The selected item can be unselected with function
 * elm_list_item_selected_set().
 *
 * The selected item always will be highlighted on list.
 *
 * @see elm_list_selected_items_get()
 *
 * @ingroup List
 */
EAPI Elm_List_Item               *elm_list_selected_item_get(const Evas_Object *obj);

/**
 * Return a list of the currently selected list items.
 *
 * @param obj The list object.
 * @return An @c Eina_List of list items, #Elm_List_Item,
 * or @c NULL on failure.
 *
 * Multiple items can be selected if multi select is enabled. It can be
 * done with elm_list_multi_select_set().
 *
 * @see elm_list_selected_item_get()
 * @see elm_list_multi_select_set()
 *
 * @ingroup List
 */
EAPI const Eina_List             *elm_list_selected_items_get(const Evas_Object *obj);

/**
 * Set the selected state of an item.
 *
 * @param item The list item
 * @param selected The selected state
 *
 * This sets the selected state of the given item @p it.
 * @c EINA_TRUE for selected, @c EINA_FALSE for not selected.
 *
 * If a new item is selected the previosly selected will be unselected,
 * unless multiple selection is enabled with elm_list_multi_select_set().
 * Previoulsy selected item can be get with function
 * elm_list_selected_item_get().
 *
 * Selected items will be highlighted.
 *
 * @see elm_list_item_selected_get()
 * @see elm_list_selected_item_get()
 * @see elm_list_multi_select_set()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_selected_set(Elm_List_Item *item, Eina_Bool selected);

/*
 * Get whether the @p item is selected or not.
 *
 * @param item The list item.
 * @return @c EINA_TRUE means item is selected. @c EINA_FALSE indicates
 * it's not. If @p obj is @c NULL, @c EINA_FALSE is returned.
 *
 * @see elm_list_selected_item_set() for details.
 * @see elm_list_item_selected_get()
 *
 * @ingroup List
 */
EAPI Eina_Bool                    elm_list_item_selected_get(const Elm_List_Item *item);

/**
 * Set or unset item as a separator.
 *
 * @param it The list item.
 * @param setting @c EINA_TRUE to set item @p it as separator or
 * @c EINA_FALSE to unset, i.e., item will be used as a regular item.
 *
 * Items aren't set as separator by default.
 *
 * If set as separator it will display separator theme, so won't display
 * icons or label.
 *
 * @see elm_list_item_separator_get()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_separator_set(Elm_List_Item *it, Eina_Bool setting);

/**
 * Get a value whether item is a separator or not.
 *
 * @see elm_list_item_separator_set() for details.
 *
 * @param it The list item.
 * @return @c EINA_TRUE means item @p it is a separator. @c EINA_FALSE
 * indicates it's not. If @p it is @c NULL, @c EINA_FALSE is returned.
 *
 * @ingroup List
 */
EAPI Eina_Bool                    elm_list_item_separator_get(const Elm_List_Item *it);

/**
 * Show @p item in the list view.
 *
 * @param item The list item to be shown.
 *
 * It won't animate list until item is visible. If such behavior is wanted,
 * use elm_list_bring_in() intead.
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_show(Elm_List_Item *item);

/**
 * Bring in the given item to list view.
 *
 * @param item The item.
 *
 * This causes list to jump to the given item @p item and show it
 * (by scrolling), if it is not fully visible.
 *
 * This may use animation to do so and take a period of time.
 *
 * If animation isn't wanted, elm_list_item_show() can be used.
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_bring_in(Elm_List_Item *item);

/**
 * Delete them item from the list.
 *
 * @param item The item of list to be deleted.
 *
 * If deleting all list items is required, elm_list_clear()
 * should be used instead of getting items list and deleting each one.
 *
 * @see elm_list_clear()
 * @see elm_list_item_append()
 * @see elm_list_item_del_cb_set()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_del(Elm_List_Item *item);

/**
 * Set the function called when a list item is freed.
 *
 * @param item The item to set the callback on
 * @param func The function called
 *
 * If there is a @p func, then it will be called prior item's memory release.
 * That will be called with the following arguments:
 * @li item's data;
 * @li item's Evas object;
 * @li item itself;
 *
 * This way, a data associated to a list item could be properly freed.
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_del_cb_set(Elm_List_Item *item, Evas_Smart_Cb func);

/**
 * Get the data associated to the item.
 *
 * @param item The list item
 * @return The data associated to @p item
 *
 * The return value is a pointer to data associated to @p item when it was
 * created, with function elm_list_item_append() or similar. If no data
 * was passed as argument, it will return @c NULL.
 *
 * @see elm_list_item_append()
 *
 * @ingroup List
 */
EAPI void                        *elm_list_item_data_get(const Elm_List_Item *item);

/**
 * Get the left side icon associated to the item.
 *
 * @param item The list item
 * @return The left side icon associated to @p item
 *
 * The return value is a pointer to the icon associated to @p item when
 * it was
 * created, with function elm_list_item_append() or similar, or later
 * with function elm_list_item_icon_set(). If no icon
 * was passed as argument, it will return @c NULL.
 *
 * @see elm_list_item_append()
 * @see elm_list_item_icon_set()
 *
 * @ingroup List
 */
EAPI Evas_Object                 *elm_list_item_icon_get(const Elm_List_Item *item);

/**
 * Set the left side icon associated to the item.
 *
 * @param item The list item
 * @param icon The left side icon object to associate with @p item
 *
 * The icon object to use at left side of the item. An
 * icon can be any Evas object, but usually it is an icon created
 * with elm_icon_add().
 *
 * Once the icon object is set, a previously set one will be deleted.
 * @warning Setting the same icon for two items will cause the icon to
 * dissapear from the first item.
 *
 * If an icon was passed as argument on item creation, with function
 * elm_list_item_append() or similar, it will be already
 * associated to the item.
 *
 * @see elm_list_item_append()
 * @see elm_list_item_icon_get()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_icon_set(Elm_List_Item *item, Evas_Object *icon);

/**
 * Get the right side icon associated to the item.
 *
 * @param item The list item
 * @return The right side icon associated to @p item
 *
 * The return value is a pointer to the icon associated to @p item when
 * it was
 * created, with function elm_list_item_append() or similar, or later
 * with function elm_list_item_icon_set(). If no icon
 * was passed as argument, it will return @c NULL.
 *
 * @see elm_list_item_append()
 * @see elm_list_item_icon_set()
 *
 * @ingroup List
 */
EAPI Evas_Object                 *elm_list_item_end_get(const Elm_List_Item *item);

/**
 * Set the right side icon associated to the item.
 *
 * @param item The list item
 * @param end The right side icon object to associate with @p item
 *
 * The icon object to use at right side of the item. An
 * icon can be any Evas object, but usually it is an icon created
 * with elm_icon_add().
 *
 * Once the icon object is set, a previously set one will be deleted.
 * @warning Setting the same icon for two items will cause the icon to
 * dissapear from the first item.
 *
 * If an icon was passed as argument on item creation, with function
 * elm_list_item_append() or similar, it will be already
 * associated to the item.
 *
 * @see elm_list_item_append()
 * @see elm_list_item_end_get()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_end_set(Elm_List_Item *item, Evas_Object *end);

/**
 * Gets the base object of the item.
 *
 * @param item The list item
 * @return The base object associated with @p item
 *
 * Base object is the @c Evas_Object that represents that item.
 *
 * @ingroup List
 */
EAPI Evas_Object                 *elm_list_item_object_get(const Elm_List_Item *item);

/**
 * Get the label of item.
 *
 * @param item The item of list.
 * @return The label of item.
 *
 * The return value is a pointer to the label associated to @p item when
 * it was created, with function elm_list_item_append(), or later
 * with function elm_list_item_label_set. If no label
 * was passed as argument, it will return @c NULL.
 *
 * @see elm_list_item_label_set() for more details.
 * @see elm_list_item_append()
 *
 * @ingroup List
 */
EAPI const char                  *elm_list_item_label_get(const Elm_List_Item *item);

/**
 * Set the label of item.
 *
 * @param item The item of list.
 * @param text The label of item.
 *
 * The label to be displayed by the item.
 * Label will be placed between left and right side icons (if set).
 *
 * If a label was passed as argument on item creation, with function
 * elm_list_item_append() or similar, it will be already
 * displayed by the item.
 *
 * @see elm_list_item_label_get()
 * @see elm_list_item_append()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_label_set(Elm_List_Item *item, const char *text);

/**
 * Get the item before @p it in list.
 *
 * @param it The list item.
 * @return The item before @p it, or @c NULL if none or on failure.
 *
 * @note If it is the first item, @c NULL will be returned.
 *
 * @see elm_list_item_append()
 * @see elm_list_items_get()
 *
 * @ingroup List
 */
EAPI Elm_List_Item               *elm_list_item_prev(const Elm_List_Item *it);

/**
 * Get the item after @p it in list.
 *
 * @param it The list item.
 * @return The item after @p it, or @c NULL if none or on failure.
 *
 * @note If it is the last item, @c NULL will be returned.
 *
 * @see elm_list_item_append()
 * @see elm_list_items_get()
 *
 * @ingroup List
 */
EAPI Elm_List_Item               *elm_list_item_next(const Elm_List_Item *it);

/**
 * Sets the disabled/enabled state of a list item.
 *
 * @param it The item.
 * @param disabled The disabled state.
 *
 * A disabled item cannot be selected or unselected. It will also
 * change its appearance (generally greyed out). This sets the
 * disabled state (@c EINA_TRUE for disabled, @c EINA_FALSE for
 * enabled).
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_disabled_set(Elm_List_Item *it, Eina_Bool disabled);

/**
 * Get a value whether list item is disabled or not.
 *
 * @param it The item.
 * @return The disabled state.
 *
 * @see elm_list_item_disabled_set() for more details.
 *
 * @ingroup List
 */
EAPI Eina_Bool                    elm_list_item_disabled_get(const Elm_List_Item *it);

/**
 * Set the text to be shown in a given list item's tooltips.
 *
 * @param item Target item.
 * @param text The text to set in the content.
 *
 * Setup the text as tooltip to object. The item can have only one tooltip,
 * so any previous tooltip data - set with this function or
 * elm_list_item_tooltip_content_cb_set() - is removed.
 *
 * @see elm_object_tooltip_text_set() for more details.
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_tooltip_text_set(Elm_List_Item *item, const char *text);

/**
 * @brief Disable size restrictions on an object's tooltip
 * @param item The tooltip's anchor object
 * @param disable If EINA_TRUE, size restrictions are disabled
 * @return EINA_FALSE on failure, EINA_TRUE on success
 *
 * This function allows a tooltip to expand beyond its parant window's canvas.
 * It will instead be limited only by the size of the display.
 */
EAPI Eina_Bool                    elm_list_item_tooltip_window_mode_set(Elm_List_Item *item, Eina_Bool disable);
/**
 * @brief Retrieve size restriction state of an object's tooltip
 * @param obj The tooltip's anchor object
 * @return If EINA_TRUE, size restrictions are disabled
 *
 * This function returns whether a tooltip is allowed to expand beyond
 * its parant window's canvas.
 * It will instead be limited only by the size of the display.
 */
EAPI Eina_Bool                    elm_list_item_tooltip_window_mode_get(const Elm_List_Item *item);

/**
 * Set the content to be shown in the tooltip item.
 *
 * Setup the tooltip to item. The item can have only one tooltip,
 * so any previous tooltip data is removed. @p func(with @p data) will
 * be called every time that need show the tooltip and it should
 * return a valid Evas_Object. This object is then managed fully by
 * tooltip system and is deleted when the tooltip is gone.
 *
 * @param item the list item being attached a tooltip.
 * @param func the function used to create the tooltip contents.
 * @param data what to provide to @a func as callback data/context.
 * @param del_cb called when data is not needed anymore, either when
 *        another callback replaces @a func, the tooltip is unset with
 *        elm_list_item_tooltip_unset() or the owner @a item
 *        dies. This callback receives as the first parameter the
 *        given @a data, and @c event_info is the item.
 *
 * @see elm_object_tooltip_content_cb_set() for more details.
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_tooltip_content_cb_set(Elm_List_Item *item, Elm_Tooltip_Item_Content_Cb func, const void *data, Evas_Smart_Cb del_cb);

/**
 * Unset tooltip from item.
 *
 * @param item list item to remove previously set tooltip.
 *
 * Remove tooltip from item. The callback provided as del_cb to
 * elm_list_item_tooltip_content_cb_set() will be called to notify
 * it is not used anymore.
 *
 * @see elm_object_tooltip_unset() for more details.
 * @see elm_list_item_tooltip_content_cb_set()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_tooltip_unset(Elm_List_Item *item);

/**
 * Sets a different style for this item tooltip.
 *
 * @note before you set a style you should define a tooltip with
 *       elm_list_item_tooltip_content_cb_set() or
 *       elm_list_item_tooltip_text_set()
 *
 * @param item list item with tooltip already set.
 * @param style the theme style to use (default, transparent, ...)
 *
 * @see elm_object_tooltip_style_set() for more details.
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_tooltip_style_set(Elm_List_Item *item, const char *style);

/**
 * Get the style for this item tooltip.
 *
 * @param item list item with tooltip already set.
 * @return style the theme style in use, defaults to "default". If the
 *         object does not have a tooltip set, then NULL is returned.
 *
 * @see elm_object_tooltip_style_get() for more details.
 * @see elm_list_item_tooltip_style_set()
 *
 * @ingroup List
 */
EAPI const char                  *elm_list_item_tooltip_style_get(const Elm_List_Item *item);

/**
 * Set the type of mouse pointer/cursor decoration to be shown,
 * when the mouse pointer is over the given list widget item
 *
 * @param item list item to customize cursor on
 * @param cursor the cursor type's name
 *
 * This function works analogously as elm_object_cursor_set(), but
 * here the cursor's changing area is restricted to the item's
 * area, and not the whole widget's. Note that that item cursors
 * have precedence over widget cursors, so that a mouse over an
 * item with custom cursor set will always show @b that cursor.
 *
 * If this function is called twice for an object, a previously set
 * cursor will be unset on the second call.
 *
 * @see elm_object_cursor_set()
 * @see elm_list_item_cursor_get()
 * @see elm_list_item_cursor_unset()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_cursor_set(Elm_List_Item *item, const char *cursor);

/*
 * Get the type of mouse pointer/cursor decoration set to be shown,
 * when the mouse pointer is over the given list widget item
 *
 * @param item list item with custom cursor set
 * @return the cursor type's name or @c NULL, if no custom cursors
 * were set to @p item (and on errors)
 *
 * @see elm_object_cursor_get()
 * @see elm_list_item_cursor_set()
 * @see elm_list_item_cursor_unset()
 *
 * @ingroup List
 */
EAPI const char                  *elm_list_item_cursor_get(const Elm_List_Item *item);

/**
 * Unset any custom mouse pointer/cursor decoration set to be
 * shown, when the mouse pointer is over the given list widget
 * item, thus making it show the @b default cursor again.
 *
 * @param item a list item
 *
 * Use this call to undo any custom settings on this item's cursor
 * decoration, bringing it back to defaults (no custom style set).
 *
 * @see elm_object_cursor_unset()
 * @see elm_list_item_cursor_set()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_cursor_unset(Elm_List_Item *item);

/**
 * Set a different @b style for a given custom cursor set for a
 * list item.
 *
 * @param item list item with custom cursor set
 * @param style the <b>theme style</b> to use (e.g. @c "default",
 * @c "transparent", etc)
 *
 * This function only makes sense when one is using custom mouse
 * cursor decorations <b>defined in a theme file</b>, which can have,
 * given a cursor name/type, <b>alternate styles</b> on it. It
 * works analogously as elm_object_cursor_style_set(), but here
 * applyed only to list item objects.
 *
 * @warning Before you set a cursor style you should have definen a
 *       custom cursor previously on the item, with
 *       elm_list_item_cursor_set()
 *
 * @see elm_list_item_cursor_engine_only_set()
 * @see elm_list_item_cursor_style_get()
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_cursor_style_set(Elm_List_Item *item, const char *style);

/**
 * Get the current @b style set for a given list item's custom
 * cursor
 *
 * @param item list item with custom cursor set.
 * @return style the cursor style in use. If the object does not
 *         have a cursor set, then @c NULL is returned.
 *
 * @see elm_list_item_cursor_style_set() for more details
 *
 * @ingroup List
 */
EAPI const char                  *elm_list_item_cursor_style_get(const Elm_List_Item *item);

/**
 * Set if the (custom)cursor for a given list item should be
 * searched in its theme, also, or should only rely on the
 * rendering engine.
 *
 * @param item item with custom (custom) cursor already set on
 * @param engine_only Use @c EINA_TRUE to have cursors looked for
 * only on those provided by the rendering engine, @c EINA_FALSE to
 * have them searched on the widget's theme, as well.
 *
 * @note This call is of use only if you've set a custom cursor
 * for list items, with elm_list_item_cursor_set().
 *
 * @note By default, cursors will only be looked for between those
 * provided by the rendering engine.
 *
 * @ingroup List
 */
EAPI void                         elm_list_item_cursor_engine_only_set(Elm_List_Item *item, Eina_Bool engine_only);

/**
 * Get if the (custom) cursor for a given list item is being
 * searched in its theme, also, or is only relying on the rendering
 * engine.
 *
 * @param item a list item
 * @return @c EINA_TRUE, if cursors are being looked for only on
 * those provided by the rendering engine, @c EINA_FALSE if they
 * are being searched on the widget's theme, as well.
 *
 * @see elm_list_item_cursor_engine_only_set(), for more details
 *
 * @ingroup List
 */
EAPI Eina_Bool                    elm_list_item_cursor_engine_only_get(const Elm_List_Item *item);

/**
 * @}
 */
