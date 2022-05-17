#ifndef K_Tree_H
#define K_Tree_H

#define MAX_CHILD 4

typedef struct K_Tree_Node
{
    int values[3];
    unsigned nv;
    struct node *child[4];
}Node;

typedef struct to_print
{
    char *node_name;
    struct Print *tp[MAX_CHILD + 1];
}Print;

struct Node insert(Node *node);

#endif /* ! K_ARBRE */
