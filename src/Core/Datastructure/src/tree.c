#include "tree.h"

void bfs(struct _rb_root_node *rb_root_node, struct _queue *ptr_result)
{
    INIT_QUEUE(queue1, list1);
    int queue_size = 0;
    struct _rb_leaf_node *rb_tmp_node = rb_root_node->ptr_root_node;

    struct _leaf_and_lift_node *new_leaf_and_lift_node = \
                (struct _leaf_and_lift_node*)calloc(1, sizeof(struct _leaf_and_lift_node));
                
    new_leaf_and_lift_node->rb_leaf_node = rb_tmp_node;

    queue_push(&queue1, &(new_leaf_and_lift_node->list_node));

    while (queue1.size != 0) {
        queue_size = queue1.size;
        while (queue_size-- != 0) {
            struct _node *rb_ptr_node = queue_pull(&queue1);

            queue_push(ptr_result, rb_ptr_node);

            if (CONTAINER_OF(rb_ptr_node, struct _leaf_and_lift_node, list_node)->rb_leaf_node->left != NULL) {
                new_leaf_and_lift_node = \
                    (struct _leaf_and_lift_node*)calloc(1, sizeof(struct _leaf_and_lift_node));
                new_leaf_and_lift_node->rb_leaf_node = CONTAINER_OF(rb_ptr_node, struct _leaf_and_lift_node, list_node)->rb_leaf_node->left;
                queue_push(&queue1, &(new_leaf_and_lift_node->list_node));
            }

            if (CONTAINER_OF(rb_ptr_node, struct _leaf_and_lift_node, list_node)->rb_leaf_node->right != NULL) {
                new_leaf_and_lift_node = \
                    (struct _leaf_and_lift_node*)calloc(1, sizeof(struct _leaf_and_lift_node));
                new_leaf_and_lift_node->rb_leaf_node = CONTAINER_OF(rb_ptr_node, struct _leaf_and_lift_node, list_node)->rb_leaf_node->right;
                queue_push(&queue1, &(new_leaf_and_lift_node->list_node));
            }
        }
    }
}

void tree_insert_leaf(struct _rb_root_node *rb_root_node, bool (*cmp)(struct _rb_leaf_node*, struct _rb_leaf_node*), \
                        struct _rb_leaf_node *rb_leaf_node)
{
    struct _rb_leaf_node **ptr_rb_leaf_node = &(rb_root_node->ptr_root_node);

    while (*ptr_rb_leaf_node != NULL) {
        if (cmp(*ptr_rb_leaf_node, rb_leaf_node) > 0) {
            ptr_rb_leaf_node = &((*ptr_rb_leaf_node)->left);
        } else {
            ptr_rb_leaf_node = &((*ptr_rb_leaf_node)->right);
        }
    }

    *ptr_rb_leaf_node = rb_leaf_node;
}

void tree_search_leaf(struct _rb_root_node *rb_root_node, bool (*cmp)(struct _rb_leaf_node*, struct _rb_leaf_node*), \
                            struct _rb_leaf_node* target_rb_root_node, struct _rb_leaf_node *ptr_result)
{
    ptr_result = rb_root_node->ptr_root_node;

    while (ptr_result != target_rb_root_node && ptr_result != NULL) {
        if (cmp(ptr_result, target_rb_root_node) > 0) {
            ptr_result = ptr_result->left;
        } else {
            ptr_result = ptr_result->right;
        }
    }
}

// Hibbard deletion algorithm: ref http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete2.html
void tree_remove_leaf(struct _rb_root_node *rb_root_node, bool (*cmp)(struct _rb_leaf_node*, struct _rb_leaf_node*), \
                        struct _rb_leaf_node *target_rb_root_node)
{
    struct _rb_leaf_node **ptr_rb_leaf_node =  &(rb_root_node->ptr_root_node);
    struct _rb_leaf_node **ptr_rb_leaf_right_tmp_node = NULL;
    struct _rb_leaf_node **ptr_rb_leaf_left_tmp_node = NULL;
    struct _rb_leaf_node **ptr_rb_leaf_min_node = NULL;
    struct _rb_leaf_node **ptr_rb_leaf_min_prv_node = NULL;
    struct _rb_leaf_node *ptr_rb_leaf_min_net_right_node = NULL;

    while (*ptr_rb_leaf_node != target_rb_root_node && *ptr_rb_leaf_node != NULL) {
        if (cmp(*ptr_rb_leaf_node, target_rb_root_node) > 0) {
            ptr_rb_leaf_node = &((*ptr_rb_leaf_node)->left);
        } else {
            ptr_rb_leaf_node = &((*ptr_rb_leaf_node)->right);
        }
    }

    // The node is not exist.
    if (*ptr_rb_leaf_node == NULL) {
         printf("Can not target node.\n");
        return;
    }

    // Case 1: The node have not node on the subtree.
    if ((*ptr_rb_leaf_node)->left == NULL && (*ptr_rb_leaf_node)->right == NULL) {
        *ptr_rb_leaf_node = NULL;
        printf("Case 1\n");
        return;

    // Case 2: The node have single node on the subtree.
    } else if ((*ptr_rb_leaf_node)->left != NULL && (*ptr_rb_leaf_node)->right == NULL) {
        if ((*ptr_rb_leaf_node)->left->right == NULL && (*ptr_rb_leaf_node)->left->left == NULL) {
            // Case 1: The node is right node.
            printf("Case 2-1\n");
            *ptr_rb_leaf_node = (*ptr_rb_leaf_node)->left;
            return;
        }
    } else if ((*ptr_rb_leaf_node)->left == NULL && (*ptr_rb_leaf_node)->right != NULL){
        if ((*ptr_rb_leaf_node)->right->right == NULL && (*ptr_rb_leaf_node)->right->left == NULL) {
            // Case 2: The node is left node.
            printf("Case 2-2\n");
            *ptr_rb_leaf_node = (*ptr_rb_leaf_node)->right;
            return;
        }
    }
    // Case 3: The node have double node on the subtree.
    
    // 1. Find minimum leaf on right subtree.
    if ((*ptr_rb_leaf_node)->left == NULL) {
    // Case 1: The node have not left subtree.
        printf("Case 3-1-1\n");
        // Switch first right subtree node to target node.
        (*ptr_rb_leaf_node) = (*ptr_rb_leaf_node)->right;
        return;
    } else {
    // Case 2: The node have left subtree.
        printf("Case 3-1-2\n");
        
        ptr_rb_leaf_min_prv_node = &((*ptr_rb_leaf_node)->right);
        while ((*ptr_rb_leaf_min_prv_node)->left->left != NULL) {
            ptr_rb_leaf_min_prv_node = &((*ptr_rb_leaf_min_prv_node)->left);
        }

        ptr_rb_leaf_min_node = &((*ptr_rb_leaf_min_prv_node)->left);
    }
    
    // 2. Replace target node by successor node.
    if ((*ptr_rb_leaf_min_node)->left == NULL && (*ptr_rb_leaf_min_node)->right == NULL) {
        // Case 1: The successor node have not subtree.
        printf("Case 3-2-1\n");
        // Record target left subtree and right subtree.
        ptr_rb_leaf_right_tmp_node = &((*ptr_rb_leaf_node)->right);
        ptr_rb_leaf_left_tmp_node = &((*ptr_rb_leaf_node)->left);

        // Replace the replace node by min node.
        *ptr_rb_leaf_node = *ptr_rb_leaf_min_node;

        // Connect the min node to left and right subtree of the target node.
        (*ptr_rb_leaf_node)->right = *ptr_rb_leaf_right_tmp_node;
        (*ptr_rb_leaf_node)->left = *ptr_rb_leaf_left_tmp_node;

        // Left subtree of the prv-min node connect to NULL.
        (*ptr_rb_leaf_min_prv_node)->left = NULL;

        return;
    } else {
        // Case 2: The successor node have right subtree.
        printf("Case 3-2-2\n");
        // Record target left subtree and right subtree.
        ptr_rb_leaf_right_tmp_node = &((*ptr_rb_leaf_node)->right);
        ptr_rb_leaf_left_tmp_node = &((*ptr_rb_leaf_node)->left);
        ptr_rb_leaf_min_net_right_node = (*ptr_rb_leaf_min_node)->right;

        // Replace the replace node by min node.
        *ptr_rb_leaf_node = *ptr_rb_leaf_min_node;

        // Connect the min node to left and right subtree of the target node.
        (*ptr_rb_leaf_node)->right = *ptr_rb_leaf_right_tmp_node;
        (*ptr_rb_leaf_node)->left = *ptr_rb_leaf_left_tmp_node;

        // Left subtree of the prv-min node connect to the prv-min right subtree.
        (*ptr_rb_leaf_min_prv_node)->left = ptr_rb_leaf_min_net_right_node;
        
        return;
    }
}
