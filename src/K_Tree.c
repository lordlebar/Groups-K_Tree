#include "include/K_Tree.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "K_tree: Usage: %s (insert value)\n", argv[0]);
    }

    return 0;
}

struct Node insert(Node *node, int val)
{
    printf("%d\n", node->nv);
}
