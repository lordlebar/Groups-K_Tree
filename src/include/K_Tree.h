#ifndef K_Tree_H
#define K_Tree_H

#define MAX_CHILD 4

typedef struct Node
{
    int key[MAX_CHILD - 1];
    unsigned nv;
    struct Node *child[MAX_CHILD];
}TreeNode;

TreeNode *new_node();
int is_digit(char *n, int len);
TreeNode *nsplit(TreeNode *node, TreeNode *pnode);
void print_node(TreeNode *node);
TreeNode *insert(TreeNode *node, TreeNode *pnode, int val);

#endif /* ! K_ARBRE */
