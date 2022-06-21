#ifndef K_Tree_H
#define K_Tree_H

#define MAX_CHILD 4

typedef struct Node Node;

struct Node
{
    int values[MAX_CHILD - 1];
    unsigned nv;
    struct Node *child[MAX_CHILD];
};

Node *newNode();
Node *nsplit(Node *node, Node *pnode);
void printNode(Node *node);
Node *insert(Node *node, Node *pnode, int val);

#endif /* ! K_ARBRE */
