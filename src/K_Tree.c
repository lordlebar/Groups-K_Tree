#include "include/K_Tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_digit(char *n, int len){
    for (int i = 0; i < len; i++){
        if (n[i] < '0' || n[i] > '9')
            return 0;
        continue;
    }
    return 1;
}

TreeNode *new_node()
{
    TreeNode *n = malloc(sizeof(TreeNode));
    if (!n)
    {
        fprintf(stderr, "-NEWNODE- Memory Allocate Error\n");
        exit(1);
    }
    n->nv = 0;
    return n;
}

void print_node(TreeNode *node) 
{
	if (node->nv == 0)
		return;
	else if (node->nv == 1)
		printf("(%d)nv%d\n", node->key[0], node->nv);
	else if (node->nv == 2)
		printf("(%d %d)nv%d\n", node->key[0], node->key[1], node->nv);
	else
		printf("(%d %d %d)nv%d\n", node->key[0], node->key[1], node->key[2], node->nv);
	return;
}

void print(TreeNode *node){
    for (size_t i = 0; i < node->nv; i++)
    {
        printf("%d", node->key[i]);
        printf("%d->%d", node->key[i], node->child[i]->key[i]);
    }
}

TreeNode *nsplit(TreeNode *node, TreeNode *parent_node)
{
    if (node->nv != 3)
    {
        fprintf(stderr, "-NSPLIT- TreeNode->nv = %u, must be 3 exactly\n", node->nv);
        exit(1);
    }

    if (!parent_node) // is root
        parent_node = new_node();

    TreeNode *left = new_node(); // instance of new node (left one)
    left->key[0] = node->key[0];
    left->nv += 1;
    left->child[0] = node->child[0];
    left->child[1] = node->child[1];

    TreeNode *right = new_node(); // instance of new node (right one)
    right->key[0] = node->key[2];
    right->nv += 1;
    right->child[0] = node->child[2];
    right->child[1] = node->child[3];

    if (parent_node->nv == 0) // (empty parent_node -> root)
    {
        parent_node->key[0] = node->key[1];
        parent_node->child[0] = left;
        parent_node->child[1] = right;
        parent_node->nv += 1;
    }

    else if (parent_node->nv == 1) // (2-parent_node)
    {
        if (node->key[2] < parent_node->key[0]) // insert in key[0]
        {
            parent_node->key[1] = parent_node->key[0];
            parent_node->key[0] = node->key[1];
            parent_node->child[2] = parent_node->child[1];
            parent_node->child[1] = right;
            parent_node->child[0] = left;
        }
        else // insert in key[1]
        {
            parent_node->key[1] = node->key[2];
            parent_node->child[2] = right;
            parent_node->child[1] = left;
        }
        parent_node->nv += 1;
    }

    else if (parent_node->nv == 2) // (3-parent_node)
    {
        if (node->key[2] < parent_node->key[0]) // insert in key[0]
        {
            parent_node->key[2] = parent_node->key[1];
            parent_node->key[1] = parent_node->key[0];
            parent_node->key[0] = node->key[2];
            parent_node->child[3] = parent_node->child[2];
            parent_node->child[2] = parent_node->child[1];
            parent_node->child[1] = right;
            parent_node->child[0] = left;
        }
        else if (node->key[2] < parent_node->key[1]) // insert in key[1]
        {
            parent_node->key[2] = parent_node->key[1];
            parent_node->key[1] = node->key[2];
            parent_node->child[3] = parent_node->child[2];
            parent_node->child[2] = right;
            parent_node->child[1] = left;
        }
        else // insert in key[2]
        {
            parent_node->key[2] = node->key[2];
            parent_node->child[3] = right;
            parent_node->child[2] = left;
        }
        parent_node->nv += 1;
    }
    free(node);
    return parent_node;
}

TreeNode *insert(TreeNode *node, TreeNode *parent_node, int val_to_insert)
{
    if (node->nv == 3) // if 4-node -> Split
        node = nsplit(node, parent_node);
    // is leaf
    if (!node->child[0])
    {
        if (node->nv == 0) // (empty node) & insert in key[0]
        {
            node->key[0] = val_to_insert;
            node->nv += 1;
        }

        else if (node->nv == 1) // (2-node)      
        {
            if (val_to_insert < node->key[0]) // insert in key[0]
            {
                node->key[1] = node->key[0];
                node->key[0] = val_to_insert;
                print_node(node);
            }
            else // insert in key[1]
                node->key[1] = val_to_insert;
            node->nv += 1;
        }

        else if (node->nv == 2)// (3-node)
        {
            if (val_to_insert < node->key[0]) // insert in key[0]
            {
                node->key[2] = node->key[1];
                node->key[1] = node->key[0];
                node->key[0] = val_to_insert;
            }
            else if (val_to_insert < node->key[1]) // insert in key[1]
            {
                node->key[2] = node->key[1];
                node->key[1] = val_to_insert;
            }
            else // insert in key[2]
                node->key[2] = val_to_insert;
            node->nv += 1;
        }

        if (node->nv > 3) // Check node->nv
        {
            fprintf(stderr, "-INSERTION- TreeNode->nv = %u out of range, must be  0 < nv < 3\n", node->nv);
            exit(1);
        }
    }
    else // not leaf -> recursion
    {
        if (val_to_insert < node->key[0])
            node = insert(node->child[0], node, val_to_insert);
        else if (val_to_insert < node->key[1] || node->nv == 1)
            node = insert(node->child[1], node, val_to_insert);
        else if (val_to_insert < node->key[2] || node->nv == 2)
            node = insert(node->child[2], node, val_to_insert);
        else
            node = insert(node->child[3], node, val_to_insert);
    }
    return node;
}

enum { max_string = 127 };
static char string[max_string + 1] = "";

int main(int argc, char *argv[])
{
    if (argc <= 1){
        fprintf(stderr, "Usage : \"./K_Tree `valeur a inserer`\",\nla valeur trouver ici est %s donc non recevable.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    else if (argc >= 3)
    {
        fprintf(stderr, "Usage : \"./K_Tree `valeur a inserer`\",\nle nombre d'argument est trop elever. 1 seul argument est autorisé,\nVous en avez mis %d\n", (argc - 1));
        exit(EXIT_FAILURE);
    }
    else if (is_digit(argv[1], strlen(argv[1])) == 0){
        fprintf(stderr, "Usage : \"./K_Tree `valeur a inserer`\",\nVeuillez inserez un nombre.\nVotre valeur actuel est : `%s`\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (argc == 2)
    {
        TreeNode *root = new_node();
        root = insert(root, NULL, atoi(argv[1]));
        print_node(root);
        printf("\n");
        while (1)
        {
            printf("Insert a value (q for quit): ");
            fflush(stdout);
            fgets(string, max_string, stdin);
            if (strcmp(string, "q\n") == 0)
            {
                printf("exit success...\n");
                exit(EXIT_FAILURE);
                free(root);
            }
            else
            {
                root = insert(root, NULL, atoi(string));
                print_node(root);
            }

        }
    }
    return 0;
}
