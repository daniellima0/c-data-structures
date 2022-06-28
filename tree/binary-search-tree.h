#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdlib.h>
#include <stdio.h>

typedef int item;

typedef struct node {
    struct node *left;
    item info;
    struct node *right;
} node;

typedef node *bstree;

bstree init_bstree() {
    return NULL;
}

int is_bstree_empty(bstree root) {
    if (root == NULL)
        return 1;
    else
        return 0;
}

node *allocate() {
    node *n;
    n = (node *)malloc(sizeof(node));
    return n;
}

int insert_item(bstree *root, item e) {
    node *father = NULL, *new_node, *n;
    new_node = allocate();
    if (!new_node) return 0;

    new_node->info = e;
    new_node->left = NULL;
    new_node->right = NULL;

    n = *root;
    while (n != NULL) {
        father = n;
        if (e < n->info)
            n = n->left;
        else
            n = n->right;
    }

    if (father != NULL) {
        if (e < father->info)
            father->left = new_node;
        else
            father->right = new_node;
    } else
        *root = new_node;

    return 1;
}

void pre_order(node *n) {
    if (n != NULL) {
        printf("\n%d\n", n->info);
        pre_order(n->left);
        pre_order(n->right);
    }
}
void in_order(node *n) {
    if (n != NULL) {
        in_order(n->left);
        printf("\n%d\n", n->info);
        in_order(n->right);
    }
}

void post_order(node *n) {
    if (n != NULL) {
        post_order(n->left);
        post_order(n->right);
        printf("\n%d\n", n->info);
    }
}

node *search_item(node *n, item e) {
    while (n != NULL) {
        if (e < n->info)
            n = n->left;
        else if (e > n->info)
            n = n->right;
        else
            return (n);
    };
    return (NULL);
}
bstree search_item_rec(bstree n, item e) {
    if (n != NULL) {
        if (e < n->info)
            return search_item_rec(n->left, e);
        else if (e > n->info)
            return search_item_rec(n->right, e);
        else
            return (n);
    } else
        return (NULL);
}

int get_tree_height(bstree root) {
    if (root == NULL) return 0;
    int left_height = get_tree_height(root->left);
    int right_height = get_tree_height(root->right);
    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

int get_node_amount(bstree root) {
    if (root == NULL) return 0;
    int left_total = get_node_amount(root->left);
    int right_total = get_node_amount(root->right);
    return (left_total + right_total + 1);
}

int remove_item(bstree *root, item e) {
    node *n = *root, *prev = NULL, *sub, *father, *son;
    while (n != NULL && n->info != e) {
        prev = n;
        if (e < n->info)
            n = n->left;
        else
            n = n->right;
    }
    if (n == NULL)
        return 0;

    if (n->left == NULL)
        sub = n->right;
    else if (n->right == NULL)
        sub = n->left;
    else {
        father = n;
        sub = n->right;
        son = sub->left;
        while (son != NULL) {
            father = sub;
            sub = son;
            son = sub->left;
        }
    
        if (father != n) {
            father->left = sub->right;
            sub->right = n->right;
        }
        sub->left = n->left;
    }

    if (prev == NULL)
        *root = sub;
    else if (n == prev->left)
        prev->left = sub;
    else
        prev->right = sub;
    free(n);
    return 1;
}

void destroy_node(node *n) {
    if (n == NULL) return;
    destroy_node(n->left);
    destroy_node(n->right);
    free(n);
    n = NULL;
    return;
}

void destroy_tree(bstree *root) {
    if (*root == NULL) return;
    destroy_node(*root);
    *root = NULL;
}

#endif