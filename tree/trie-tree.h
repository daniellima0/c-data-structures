#ifndef TRIE_TREE_H
#define TRIE_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTERS 26

typedef struct node {
    char letter;
    struct node* sons[LETTERS];
    int is_last_node;
} node;

node* create_node(char letter) {
    node* n = (node*)malloc(sizeof(node));
    int i;
    if (n != NULL) {
        n->is_last_node = 0;
        n->letter = letter;
        for (i = 0; i < LETTERS; i++)
            n->sons[i] = NULL;
    }
    return n;
}

node* insert_item(node* root, char* word) {
    node* n = root;
    int size = strlen(word);
    int i;
    for (i = 0; i < size; i++) {
        int index = (int)word[i] - 'a';
        if (n->sons[index] == NULL) {
            n->sons[index] = create_node(word[i]);
        }
        n = n->sons[index];
    }
    n->is_last_node = 1;
    return root;
}

int search_node(node* root, char* word) {
    node* n = root;
    int size = strlen(word);
    int i;
    for (i = 0; i < size; i++) {
        int pos = word[i] - 'a';
        if (n->sons[pos] == NULL)
            return 0;
        n = n->sons[pos];
    }
    if (n != NULL && n->is_last_node == 1)
        return 1;
    return 0;
}

int has_son(node* root) {
    int i;
    for (i = 0; i < LETTERS; i++)
        if (root->sons[i])
            return 1;
    return 0;
}

int remove_item(node** root, char* word) {
    if (*root == NULL)
        return 0;

    if (*word) {
        if (*root != NULL && (*root)->sons[*word - 'a'] != NULL &&
            remove_item(&((*root)->sons[*word - 'a']), word + 1) &&
            (*root)->is_last_node == 0) {
            if (!has_son(*root)) {
                free(*root);
                (*root) = NULL;
                return 1;
            } else {
                (*root)->sons[*word - 'a'] = NULL;
                return 0;
            }
        }
    }

    if (*word == '\0' && (*root)->is_last_node) {
        if (!has_son(*root)) {
            free(*root);
            (*root) = NULL;
            return 1;
        }
        else {
            (*root)->is_last_node = 0;
            return 0;
        }
    }

    return 0;
}

#endif