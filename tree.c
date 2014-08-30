#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct Node {
    void *data;
    int num_children;
    Node **children;
};

// Make <children> the children of root
void set_children(Node *root, Node **children, int num_children) {
    root->children = children;
    root->num_children = num_children;
}

// Return children pointer
Node **get_children(Node *root) {
    return root->children;
}

// Return number of children
int get_num_children(Node *root) {
    return root->num_children;
}

// Allocate <n> nodes
Node **make_children(int n) {
    Node **children = malloc(sizeof(Node *) * n);
    int i;
    for(i = 0; i < n; i++) {
        children[i] = calloc(sizeof(Node), 1);
    }
    return children;
}

// Free nodes
void free_children(Node **children, int n) {
    int i;
    for(i = 0; i < n; i++) {
        free(children[i]);
    }
    free(children);
}

// Allocate a node
Node *make_node(void *data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->num_children = 0;
    node->children = NULL;
    node->data = data;
    return node;
}

// Free an individual node
void free_node(Node *node) {
    free(node);
}

// Return data
void *get_data(Node *node) {
    return node->data;
}

// Modify data
void set_data(Node *node, void *data) {
    node->data = data;
}

// Free entire tree
void free_tree(Node *root) {
    int i;
    int num_children = get_num_children(root);
    Node **children = get_children(root);
    for(i = 0; i < num_children; i++) {
        free_tree(children[i]);
    }
    free_node(root);
}
