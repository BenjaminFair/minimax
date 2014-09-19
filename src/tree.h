#ifndef __TREE_H__
#define __TREE_H__

typedef struct Node Node;

void set_children(Node *root, Node **children, int num_children);
Node **get_children(Node *root);
int get_num_children(Node *root);
Node **make_children(int n);
void free_children(Node **children, int n);
Node *make_node(void *data);
void free_node(Node *node);
void *get_data(Node *node);
void set_data(Node *node, void *data);
void free_tree(Node *root);

#endif
