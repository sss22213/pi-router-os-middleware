#ifndef __LIST_H_
#define __LIST_H_
#include <stdint.h>
#include <stdlib.h>

#define NEW_NODE(NODE_NAME) \
        struct _node (NODE_NAME) = {NULL}

#define CONCAT_NODE(NODE_NAME1, NODE_NAME2) \
        (NODE_NAME1)->next = (NODE_NAME2);

#define LIST_INIT(LIST_NAME) \
        struct _list (LIST_NAME) = {NULL}

#define LIST_INIT_HEAD(LIST_NAME, HEAD_NODE_NAME) \
        struct _list (LIST_NAME) = {HEAD_NODE_NAME}

#define LIST_FOR_EACH(POS, LIST_NAME) \
        for ((POS) = (LIST_NAME)->head; (POS) != NULL; (POS) = (POS)->next)

#define OFFSETOF(TYPE, MEMBER) \
        (size_t)&(((TYPE*)0)->MEMBER)

#define CONTAINER_OF(PTR, TYPE, MEMBER) ({\
        const typeof(((TYPE*)0)->MEMBER) *__mptr = (PTR);\
        (TYPE*)( (char*)__mptr - OFFSETOF(TYPE, MEMBER));})

struct _node {
    struct _node *next;
};

struct _list {
    struct _node *head;
};

void list_push_back(struct _list*, struct _node*);
void list_pop_back(struct _list*);
struct _node *list_pop_front(struct _list*);
int folyd_cycle_detection(struct _list*);

#endif