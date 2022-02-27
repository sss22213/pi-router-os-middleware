#include "http.h"

#define HTTP_RESPONSE_PACKAGE "HTTP/1.1 %s \nContent-Type: %s\nContent-Length: %d\n\n%s"

void http_response_gen(char *status_code,\
                        char *content,\
                        char *content_type,\
                        char *ret_pack)
{
    sprintf(ret_pack, HTTP_RESPONSE_PACKAGE, status_code, content_type, strlen(content), content);
}