#include <stdio.h>
#include "list.h"
#include "queue.h"
#include "tree.h"
#include "wireless.h"

struct _test {
    int val;
    struct _node node;
};

struct my_rb_tree_node {
    int val;
    struct _rb_leaf_node rb_leaf_node;
};

bool cmp_rb_tree(struct _rb_leaf_node *rb_leaf_node_1, struct _rb_leaf_node *rb_leaf_node_2)
{
    int a_value = CONTAINER_OF(rb_leaf_node_1, struct my_rb_tree_node, rb_leaf_node)->val;
    int b_value = CONTAINER_OF(rb_leaf_node_2, struct my_rb_tree_node, rb_leaf_node)->val;
    if (a_value > b_value) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char **argv)
{
    struct _wireless_iface_iwlist_node *new_wireless_node = _find_support_freq_channel(4);

    return 0;
}