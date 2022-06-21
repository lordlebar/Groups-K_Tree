#include "include/K_Tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *newNode()
{
    Node *n = malloc(sizeof(Node));
    if (!n)
    {
        fprintf(stderr, "-NEWNODE- Memory Allocate Error\n");
        exit(1);
    }
    n->nv = 0;
    return n;
}

void printNode(Node *node) 
{
	if (node->nv == 0)
		return;
	else if (node->nv == 1)
		printf("(%d)nv%d ", node->values[0], node->nv);
	else if (node->nv == 2)
		printf("(%d %d)nv%d ", node->values[0], node->values[1], node->nv);
	else
		printf("(%d %d %d)nv%d ", node->values[0], node->values[1], node->values[2], node->nv);
	return;
}

Node *nsplit(Node *node, Node *pnode)
{
    if (node->nv != 3)
    {
        fprintf(stderr, "-NSPLIT- Node->nv = %u, must be 3 exactly\n", node->nv);
        exit(1);
    }

    if (!pnode) // is root
    {
        pnode = newNode();
    }

    Node *left = newNode(); // instance of new node (left one)
    left->values[0] = node->values[0];
    left->nv += 1;
    left->child[0] = node->child[0];
    left->child[1] = node->child[1];

    Node *right = newNode(); // instance of new node (right one)
    right->values[0] = node->values[2];
    right->nv += 1;
    right->child[0] = node->child[2];
    right->child[1] = node->child[3];

    if (pnode->nv == 0) // (empty pnode -> root)
    {
        pnode->values[0] = node->values[1];
        pnode->child[0] = left;
        pnode->child[1] = right;
        pnode->nv += 1;
        printf("-SLIT- NV : %d VAL : %d\n", pnode->nv, pnode->values[0]);
    }

    else if (pnode->nv == 1) // (2-pnode)
    {
        if (node->values[2] < pnode->values[0]) // insert in values[0]
        {
            pnode->values[1] = pnode->values[0];
            pnode->values[0] = node->values[1];
            pnode->child[2] = pnode->child[1];
            pnode->child[1] = right;
            pnode->child[0] = left;
        }
        else // insert in values[1]
        {
            pnode->values[1] = node->values[2];
            pnode->child[2] = right;
            pnode->child[1] = left;
        }
        pnode->nv += 1;
    }

    else if (pnode->nv == 2) // (3-pnode)
    {
        if (node->values[2] < pnode->values[0]) // insert in values[0]
        {
            pnode->values[2] = pnode->values[1];
            pnode->values[1] = pnode->values[0];
            pnode->values[0] = node->values[2];
            pnode->child[3] = pnode->child[2];
            pnode->child[2] = pnode->child[1];
            pnode->child[1] = right;
            pnode->child[0] = left;
        }
        else if (node->values[2] < pnode->values[1]) // insert in values[1]
        {
            pnode->values[2] = pnode->values[1];
            pnode->values[1] = node->values[2];
            pnode->child[3] = pnode->child[2];
            pnode->child[2] = right;
            pnode->child[1] = left;
        }
        else // insert in values[2]
        {
            pnode->values[2] = node->values[2];
            pnode->child[3] = right;
            pnode->child[2] = left;
        }
        pnode->nv += 1;
    }
    free(node);
    printf("-SLIT2- NV : %d VAL : %d\n", pnode->nv, pnode->values[0]);
    return pnode;
}

Node *insert(Node *node, Node *pnode, int val)
{
    if (node->nv == 3) // if 4-node -> Split
    {
        node = nsplit(node, pnode);
    }
    printf("-INSERT- NV : %d VAL : %d\n", node->nv, node->values[0]);
    // is leaf
    if (!node->child[0])
    {
        if (node->nv == 0) // (empty node) & insert in values[0]
        {
            node->values[0] = val;
            node->nv += 1;
        }

        else if (node->nv == 1) // (2-node)      
        {
            if (val < node->values[0]) // insert in values[0]
            {
                node->values[1] = node->values[0];
                node->values[0] = val;
                printNode(node);
                printf("-AAAAAAA- NV : %d VAL : %d\n", node->nv, node->values[0]);
            }
            else // insert in values[1]
            {
                node->values[1] = val;
            }
            node->nv += 1;
        }

        else if (node->nv == 2)// (3-node)
        {
            if (val < node->values[0]) // insert in values[0]
            {
                node->values[2] = node->values[1];
                node->values[1] = node->values[0];
                node->values[0] = val;
            }
            else if (val < node->values[1]) // insert in values[1]
            {
                node->values[2] = node->values[1];
                node->values[1] = val;
            }
            else // insert in values[2]
            {
                node->values[2] = val;
            }
            node->nv += 1;
        }

        if (node->nv > 3) // Check node->nv
        {
            fprintf(stderr, "-INSERTION- Node->nv = %u out of range, must be  0 < nv < 3\n", node->nv);
            exit(1);
        }
    }
    else // is not leaf -> recursive insertion
    {
        if (val < node->values[0])
        {
            node = insert(node->child[0], node, val);
        }
        else if (val < node->values[1] || node->nv == 1)
        {
            node = insert(node->child[1], node, val);
        }
        else if (val < node->values[2] || node->nv == 2)
        {
            node = insert(node->child[2], node, val);
        }
        else
        {
            node = insert(node->child[3], node, val);
        }
    }
    printNode(node);
    return node;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "K_tree: Usage: %s (insert val)\n", argv[0]);
        return 1;
    }
    if (argc == 2)
    {
        int val = -1;
        Node *root = newNode();
        root = insert(root, NULL, atoi(argv[1]));
        printNode(root);
        printf("\n");
        while (1)
        {
            printf("Insert a value : ");
            scanf("%d", &val);
            printf("\n");
            root = insert(root, NULL, val);
            printNode(root);
            printf("\n");
        }
    }
    return 0;
}