#ifndef __MESSAGE_H__
#define __MESSAGE_H__
#include "list.h"
#include <cjson/cJSON.h>
#include <string.h>
#define INIT_LIST_MESSAGE (LIST_MESSAGE_NAME) \
            struct _list_message (LIST_MESSAGE_NAME);

struct _list_message {
    struct _list message_list;
};

struct _message {
    char type_name[50];
    void *ptr_type;
    void *ptr_callback_func;
    struct _node message_node;
};



#endif