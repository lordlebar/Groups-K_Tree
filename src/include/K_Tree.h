#ifndef K_Tree_H
#define K_Tree_H

#define MAX_CHILD 4

typedef struct Node
{
    int key[MAX_CHILD - 1];
    int nv;
    struct Node *child[MAX_CHILD];
}TreeNode;

int is_digit(char *n, int len);
void add_key(TreeNode *node, int n, int val_to_insert);
void research(TreeNode *root, int val_to_search);
void print_Tree(TreeNode *node, int level);
void spaces(int n);

void split_full_node(TreeNode *node, TreeNode **node2, TreeNode **node3, int *k);
void insert__(TreeNode *parent_node, int val_to_insert, int n, TreeNode *node);
void insert_(TreeNode *node, int val_to_insert);
TreeNode *insert(TreeNode *node, int val_to_insert);

void free_tree(TreeNode *root);

#endif /* ! K_ARBRE */