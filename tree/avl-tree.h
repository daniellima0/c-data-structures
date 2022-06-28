#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node* avltree;

struct node {
    struct node* left;
    int info;
    int height;
    struct node* right;
};

int print_counter = 0;

avltree* create_avltree() {
    avltree* root = (avltree*)malloc(sizeof(avltree));
    if (root != NULL) {
        *root = NULL;
    }
    return root;
}

void pre_order(avltree* root) {
    if (root == NULL) return;
    if (*root != NULL) {
        if (print_counter != 0) {
            printf(" ");
        }
        printf("%d", (*root)->info);
        print_counter++;
        pre_order(&((*root)->left));
        pre_order(&((*root)->right));
    }
}

void in_order(avltree* root) {
    if (root == NULL) return;
    if (*root != NULL) {
        in_order(&((*root)->left));
        if (print_counter != 0) {
            printf(" ");
        }
        printf("%d", (*root)->info);
        print_counter++;
        in_order(&((*root)->right));
    }
}

void post_order(avltree* root) {
    if (root == NULL) return;
    if (*root != NULL) {
        post_order(&((*root)->left));
        post_order(&((*root)->right));
        if (print_counter != 0) {
            printf(" ");
        }
        printf("%d", (*root)->info);
        print_counter++;
    }
}

int get_avltree_height(avltree* root) {
    if (root == NULL) return 0;
    if (*root == NULL) return 0;
    int left_height = get_avltree_height(&((*root)->left));
    int right_height = get_avltree_height(&((*root)->right));
    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

int get_node_amount(avltree* root) {
    if (root == NULL) return 0;
    if (*root == NULL) return 0;
    int left_total = get_node_amount(&((*root)->left));
    int right_total = get_node_amount(&((*root)->right));
    return (left_total + right_total + 1);
}

int is_avltree_empty(avltree* root) {
    if (root == NULL) return 1;
    if (*root == NULL) return 1;
    return 0;
}

int insert_item(avltree* root, int value) {
    int result;
    if (*root == NULL) {
        struct node* new_node;
        new_node = (struct node*)malloc(sizeof(struct node));
        if (new_node == NULL) return 0;
        new_node->info = value;
        new_node->height = 0;
        new_node->right = NULL;
        new_node->left = NULL;
        *root = new_node;
        return 1;
    } else {
        struct node* current = *root;
        if (value < current->info) {
            if ((result = insert_item(&(current->left), value)) == 1) {
                if (get_balance_factor(current) >= 2) {
                    if (value < (*root)->left->info) {
                        ll_rotation(root);
                    } else {
                        lr_rotation(root);
                    }
                }
            }
        } else {
            if (value > current->info) {
                if ((result = insert_item(&(current->right), value)) == 1) {
                    if (get_balance_factor(current) >= 2) {
                        if (value > (*root)->right->info) {
                            rr_rotation(root);
                        } else {
                            rl_rotation(root);
                        }
                    }
                }
            } else {
                return 0;
            }
        }
        current->height = get_bigger_value(get_node_height(current->left), get_node_height(current->right)) + 1;
        return result;
    }
}

void destroy_node(struct node* n) {
    if (n == NULL) return;
    destroy_node(n->left);
    destroy_node(n->right);
    free(n);
    n = NULL;
}

void destroy_tree(avltree* root) {
    if (root == NULL) return;
    destroy_node(*root);
    free(root);
}

int consult_avl_value(avltree* root, int value) {
    if (root == NULL) return 0;
    if (*root == NULL) return 0;
    struct node* current = *root;
    while (current != NULL) {
        if (current->info == value) {
            return 1;
        } else {
            if (current->info > value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    return 0;
}

int get_node_height(struct node* n) {
    if (n == NULL)
        return -1;
    else
        return n->height;
}

int get_balance_factor(struct node* n) {
    int left = get_node_height(n->left);
    int right = get_node_height(n->right);
    return labs(left - right);
}

int get_bigger_value(int x, int y) {
    return (x > y) ? x : y;
}

void ll_rotation(avltree* root) {
    struct node* n;
    n = (*root)->left;
    (*root)->left = n->right;
    n->right = *root;
    (*root)->height = get_bigger_value(get_node_height((*root)->left), get_node_height((*root)->right)) + 1;
    n->height = get_bigger_value(get_node_height(n->left), (*root)->height) + 1;
    *root = n;
}

void rr_rotation(avltree* root) {
    struct node* n;
    n = (*root)->right;
    (*root)->right = n->left;
    n->left = *root;
    (*root)->height = get_bigger_value(get_node_height((*root)->left), get_node_height((*root)->right)) + 1;
    n->height = get_bigger_value(get_node_height(n->right), (*root)->height) + 1;
    *root = n;
}

void lr_rotation(avltree* root) {
    rr_rotation(&(*root)->left);
    ll_rotation(root);
}

void rl_rotation(avltree* root) {
    ll_rotation(&(*root)->right);
    rr_rotation(root);
}

int remove_item(avltree* root, int value) {
    int result;
    if (*root == NULL) {
        printf("Value %d not found", value);
        return 0;
    }
    if (value < (*root)->info) {
        if ((result = remove_item(&(*root)->left, value)) == 1) {
            if (get_balance_factor(*root) >= 2) {
                if (get_node_height((*root)->right->left) <= get_node_height((*root)->right->right)) {
                    rr_rotation(root);
                } else {
                    rl_rotation(root);
                }
            }
        }
    } else if (value > (*root)->info) {
        if ((result = remove_item(&(*root)->right, value)) == 1) {
            if (get_balance_factor(*root) >= 2) {
                if (get_node_height((*root)->left->right) <= get_node_height((*root)->left->left)) {
                    ll_rotation(root);
                } else {
                    lr_rotation(root);
                }
            }
        }
    } else {
        if (((*root)->left == NULL) || ((*root)->right == NULL)) {
            struct node* old_node = (*root);
            if ((*root)->left != NULL)
                *root = (*root)->left;
            else
                *root = (*root)->right;
            free(old_node);
            return 1;
        } else {
            struct node* temp = search_leftmost_item((*root)->right);
            (*root)->info = temp->info;
            remove_item(&(*root)->right, (*root)->info);
            if (get_balance_factor(*root) >= 2) {
                if (get_node_height((*root)->left->right) <= get_node_height((*root)->left->left)) {
                    ll_rotation(root);
                } else {
                    lr_rotation(root);
                }
            }
            return 1;
        }
        return result;
    }
}

struct node* search_leftmost_item(struct node* current) {
    struct node* node1 = current;
    struct node* node2 = current->left;
    while (node2 != NULL) {
        node1 = node2;
        node2 = node1->left;
    }
    return node1;
}

#endif