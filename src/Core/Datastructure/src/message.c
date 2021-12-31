#include "message.h"

static inline void _create(struct _list_message *list_message, struct _message *node_message,\
                                char *type_name, void *type, void *cb)
{
    node_message->ptr_callback_func = cb;
    node_message->ptr_type = type;
    strcpy(node_message->type_name, type_name);
    list_push_back(&list_message->message_list, &node_message->message_node);
}

static inline void _process(struct _list_message *list_message, char *type_name, void *ptr_mqtt_message)
{
    struct _node *ptr_node;
    /*
    LIST_FOR_EACH(ptr_node, &(list_message->message_list)) {
        if (strcmp(CONTAINER_OF(ptr_node, struct _message, message_node)->type_name, type_name) == 0) {
            
        }
    };
    */
}