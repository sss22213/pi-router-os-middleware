#ifndef __HTTP_H__
#define __HTTP_H__
#include <string.h>
#include <stdint.h>

typedef enum {
    _200_OK,
    _400_Bad_Request,
    _404_NOT_FOUND,
    _405_Method_Not_Allowed,
} HTTP_STATUS_CODE;

struct _http_response {
    char *status_code;
    char *content;
    char *content_type;
    int content_length;
};

void http_response_gen(char*, char*, char*, char*);

#endif