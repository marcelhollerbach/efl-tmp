#include "efl_network.eo.h"
#include "efl_network_server.eo.h"
#include "efl_network_connector.eo.h"
#include "efl_network_client.eo.h"
#include "efl_network_url.eo.h"

#include "efl_net_socket.eo.h"
#include "efl_net_dialer.eo.h"
#include "efl_net_server.eo.h"

#include "efl_net_socket_fd.eo.h"
#include "efl_net_server_fd.eo.h"

#include "efl_net_socket_tcp.eo.h"
#include "efl_net_dialer_tcp.eo.h"
#include "efl_net_server_tcp.eo.h"

#include "efl_net_socket_udp.eo.h"
#include "efl_net_dialer_udp.eo.h"

#include "efl_net_http_types.eot.h"

/* TODO: should be generated from 'var Efl.Net.Dialer.Error.*' */
extern Eina_Error EFL_NET_DIALER_ERROR_COULDNT_CONNECT;
extern Eina_Error EFL_NET_DIALER_ERROR_COULDNT_RESOLVE_PROXY;
extern Eina_Error EFL_NET_DIALER_ERROR_COULDNT_RESOLVE_HOST;
extern Eina_Error EFL_NET_DIALER_ERROR_PROXY_AUTHENTICATION_FAILED;

/* TODO: should be generated from 'var Efl.Net.Http.Error.*' */
extern Eina_Error EFL_NET_HTTP_ERROR_BAD_CONTENT_ENCODING;
extern Eina_Error EFL_NET_HTTP_ERROR_BAD_DOWNLOAD_RESUME;
extern Eina_Error EFL_NET_HTTP_ERROR_BAD_FUNCTION_ARGUMENT;
extern Eina_Error EFL_NET_HTTP_ERROR_CHUNK_FAILED;
extern Eina_Error EFL_NET_HTTP_ERROR_CONV_FAILED;
extern Eina_Error EFL_NET_HTTP_ERROR_CONV_REQD;
extern Eina_Error EFL_NET_HTTP_ERROR_FAILED_INIT;
extern Eina_Error EFL_NET_HTTP_ERROR_FILE_COULDNT_READ_FILE;
extern Eina_Error EFL_NET_HTTP_ERROR_FILESIZE_EXCEEDED;
extern Eina_Error EFL_NET_HTTP_ERROR_FUNCTION_NOT_FOUND;
extern Eina_Error EFL_NET_HTTP_ERROR_GOT_NOTHING;
extern Eina_Error EFL_NET_HTTP_ERROR_HTTP2;
extern Eina_Error EFL_NET_HTTP_ERROR_HTTP2_STREAM;
extern Eina_Error EFL_NET_HTTP_ERROR_HTTP_POST_ERROR;
extern Eina_Error EFL_NET_HTTP_ERROR_HTTP_RETURNED_ERROR;
extern Eina_Error EFL_NET_HTTP_ERROR_INTERFACE_FAILED;
extern Eina_Error EFL_NET_HTTP_ERROR_LOGIN_DENIED;
extern Eina_Error EFL_NET_HTTP_ERROR_NO_CONNECTION_AVAILABLE;
extern Eina_Error EFL_NET_HTTP_ERROR_NOT_BUILT_IN;
extern Eina_Error EFL_NET_HTTP_ERROR_OPERATION_TIMEDOUT;
extern Eina_Error EFL_NET_HTTP_ERROR_PARTIAL_FILE;
extern Eina_Error EFL_NET_HTTP_ERROR_PEER_FAILED_VERIFICATION;
extern Eina_Error EFL_NET_HTTP_ERROR_RANGE_ERROR;
extern Eina_Error EFL_NET_HTTP_ERROR_READ_ERROR;
extern Eina_Error EFL_NET_HTTP_ERROR_RECV_ERROR;
extern Eina_Error EFL_NET_HTTP_ERROR_REMOTE_ACCESS_DENIED;
extern Eina_Error EFL_NET_HTTP_ERROR_REMOTE_DISK_FULL;
extern Eina_Error EFL_NET_HTTP_ERROR_REMOTE_FILE_EXISTS;
extern Eina_Error EFL_NET_HTTP_ERROR_REMOTE_FILE_NOT_FOUND;
extern Eina_Error EFL_NET_HTTP_ERROR_SEND_ERROR;
extern Eina_Error EFL_NET_HTTP_ERROR_SEND_FAIL_REWIND;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_CACERT;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_CACERT_BADFILE;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_CERTPROBLEM;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_CIPHER;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_CONNECT_ERROR;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_CRL_BADFILE;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_ENGINE_INITFAILED;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_ENGINE_NOTFOUND;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_ENGINE_SETFAILED;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_INVALIDCERTSTATUS;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_ISSUER_ERROR;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_PINNEDPUBKEYNOTMATCH;
extern Eina_Error EFL_NET_HTTP_ERROR_SSL_SHUTDOWN_FAILED;
extern Eina_Error EFL_NET_HTTP_ERROR_TOO_MANY_REDIRECTS;
extern Eina_Error EFL_NET_HTTP_ERROR_UNKNOWN_OPTION;
extern Eina_Error EFL_NET_HTTP_ERROR_UNSUPPORTED_PROTOCOL;
extern Eina_Error EFL_NET_HTTP_ERROR_UPLOAD_FAILED;
extern Eina_Error EFL_NET_HTTP_ERROR_URL_MALFORMAT;
extern Eina_Error EFL_NET_HTTP_ERROR_USE_SSL_FAILED;
extern Eina_Error EFL_NET_HTTP_ERROR_WRITE_ERROR;

#include "efl_net_dialer_http.eo.h"
#include "efl_net_dialer_websocket.eo.h"
