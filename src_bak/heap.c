#include "heap.h"
#define INIT_HEAP_TREE_VAL(TYPE) ((typeof(TYPE)*)0)

struct _heap_tree {
    int val;
    struct _rb_leaf_node rb_leaf_node;
};

static inline bool cmp_rb_tree(struct _rb_leaf_node *rb_leaf_node_1, struct _rb_leaf_node *rb_leaf_node_2)
{
    int a_value = CONTAINER_OF(rb_leaf_node_1, struct _heap_tree, rb_leaf_node)->val;
    int b_value = CONTAINER_OF(rb_leaf_node_2, struct _heap_tree, rb_leaf_node)->val;
    if (a_value > b_value) {
        return 1;
    } else {
        return 0;
    }
}

// Sorting int, double, float, char from ascii code last location to first location. 
static inline void _sort(struct _heap *heap)
{
    // Create binary tree.
    INIT_ROOT(root1);

    struct _heap_tree *new_node_heap_tree = NULL;

    struct _queue ptr_result;

    struct _node *node = NULL;

    // Put node into tree.
    for (int heap_idx = 0; heap_idx < heap->size ;heap_idx++) {
        new_node_heap_tree = (struct _heap_tree*)calloc(1, sizeof(struct _heap_tree));
        new_node_heap_tree->val = heap->ptr_heap_memory[heap_idx];
        tree_insert_leaf(&root1, cmp_rb_tree, &(new_node_heap_tree->rb_leaf_node));
    }

    bfs(&root1, &ptr_result);



}