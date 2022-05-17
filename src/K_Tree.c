#include "include/K_Tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "K_tree: Usage: %s (insert val)\n", argv[0]);
    }
    return 0;
}

Node *search(Node *node, int val)
{
    unsigned i = 0;
    for (i, i <= 3, i++)
    {
        if (node->values)
            node->nv = i;
    }
    while(i != 0)
    {
        if (node->values[i] == val)
        {
            fprintf(stderr, "%s found", val);
            return node;
        }
        if (node->values[i] < val)
            return search(node->child[i - 1], val);
        if (node->values[i] > val)
            return search(node->child[i], val);
        i--;
    }
    fprintf(stderr, "%s not found", val);
    return Node;
}

Node *insert(Node *node, int val)
{
    if (!val)
        fprintf(stderr, "%s is missing", val);
    return node;
}
