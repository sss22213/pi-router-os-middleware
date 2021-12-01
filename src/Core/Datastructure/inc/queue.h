#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "list.h"

#define INIT_QUEUE(QUEUE_NAME, LIST_NAME) \
            LIST_INIT(LIST_NAME);\
            struct _queue (QUEUE_NAME) = {0, &(LIST_NAME)};

#define QUEUE_FOR_EACH(POS, QUEUE_NAME) \
        LIST_FOR_EACH(POS, (QUEUE_NAME)->ptr_queue_head)

struct _queue {
    int size;
    struct _list *ptr_queue_head;
};

struct _node *queue_pull(struct _queue*);
void queue_push(struct _queue*, struct _node*);

#endif