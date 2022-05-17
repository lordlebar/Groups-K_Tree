#include "include/K_Tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *newNode()
{
    Node *n = malloc(sizeof(Node));
    n->nv = 0;
    return n;
}

void printNode(Node *node)
{
    if (!node)
        fprintf(stderr, "Node is missing");
    
    else if (node->nv < 1)
        fprintf(stderr, "Node is empty");
    
    unsigned i = 0;

    while (i < node->nv)
    {
        printf("%d ", node->values[i]);
        i++;
    }
    printf("%d\n", node->values[node->nv]);
}

Node *search(Node *node, int val)
{
    if (!node->child)
    {
        return node;
    }

    unsigned i = 0;

    while (i < node->nv && val > node.values[i])
        i++;

    if (value == node->values[i])
    {
        fprintf(stderr, "%s found", val);
        return node;
    }
    else
        return search(node->child[i], val)

    fprintf(stderr, "%s not found", val);
    // return Node;
}

Node *insert(Node *node, int val)
{
    Node *tmp = *node;
    if (node->nv == 3)
    {
        Node *new_node = newNode();
        new_node->child[0] = node
        node = tmp;
    }
    return node;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "K_tree: Usage: %s (insert val)\n", argv[0]);
        return 1;
    }
    if (argc = 2)
    {
        unsigned i = 0;
        size_t len = sizeof(argv) / sizeof(int);
        Node *root = newNode();
        while (i < len)
        {
            insert(root, argv[i]);
            i++;
        }
    }
    return 0;
}