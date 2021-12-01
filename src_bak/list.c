#include "list.h" 

#define ISNULL(NODE_NAME) ((NODE_NAME)?0:1)

typedef enum {
    NODE_IS_EXIST,
    NODE_NOT_ESIXT,
} NODE_EXIST;

typedef enum {
    LIST_IS_CYCLE,
    LIST_NOT_CYCLE,
} LIST_CYCLE;

/**
  * @brief  Whether node is cycle?
  * @param  list structure of _list
  * @retval Cycle or not cycle
  */
int folyd_cycle_detection(struct _list *list)
{
    struct _node *ptr_rabbit = list->head;
    struct _node *ptr_tortoise = list->head->next;

    while (ptr_rabbit!=NULL && ptr_tortoise!=NULL) {
        if (ptr_rabbit == ptr_tortoise) {
            return LIST_IS_CYCLE;
        }
        ptr_rabbit = ptr_rabbit->next;
        ptr_tortoise = ptr_tortoise->next->next;
    }

    return LIST_NOT_CYCLE;
}



/**
  * @brief  Whether node in list?
  * @param  list structure of _list
  * @retval Exist or not exist.
  */
static inline NODE_EXIST node_exist(struct _list *head, struct _node *node)
{
    struct _node *ptr_node;
    LIST_FOR_EACH(ptr_node, head) {
        if (ptr_node == node) {
            return NODE_IS_EXIST;
        }
    }

    return NODE_NOT_ESIXT;
}

/**
  * @brief  Push new node into tail of list.
  * @param  list structure of _list
  * @param  node structure of node
  */
static inline void _push_back(struct _list *list, struct _node *node)
{
    struct _node *ptr_node;

    if (list->head == NULL) {
        list->head = node;
        node->next = NULL;
        return;
    }

    LIST_FOR_EACH(ptr_node, list) {
        if (ptr_node->next == NULL) {
            ptr_node->next = node;
            node->next = NULL;
            break;
        }
    }
}

/**
  * @brief  Pop node from tail of list.
  * @param  list structure of _list
  */
static inline void _pop_back(struct _list *list)
{
    struct _node *ptr_node;

    LIST_FOR_EACH(ptr_node, list) {
        if (ptr_node->next->next == NULL) {
            ptr_node->next = NULL;
            break;
        }
    }
}

/**
  * @brief  Pop node from head of list.
  * @param  list structure of _list
  */
struct _node *_pop_front(struct _list *list)
{
    struct _node *ptr_node = list->head;
    list->head = list->head->next;
    return ptr_node;
}

void list_push_back(struct _list *list, struct _node *node)
{
    _push_back(list, node);
}

void list_pop_back(struct _list *list)
{
    _pop_back(list);
}

struct _node *list_pop_front(struct _list *list)
{
    return _pop_front(list);
}
