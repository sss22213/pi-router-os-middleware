#include "queue.h"

struct _node *_pull(struct _queue *queue)
{
    // struct _node *ptr_q_head = queue->ptr_queue_head->head;
    return list_pop_front(queue->ptr_queue_head);
}

void _push(struct _queue *queue, struct _node *node)
{
    list_push_back(queue->ptr_queue_head, node);
}

struct _node *queue_pull(struct _queue *queue)
{
    queue->size--;
    return _pull(queue);
}

void queue_push(struct _queue *queue, struct _node *node)
{
    queue->size++;
    _push(queue, node);
}
