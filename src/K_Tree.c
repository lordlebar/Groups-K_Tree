#include "include/K_Tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_digit(char *n, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (n[i] < '0' || n[i] > '9') // if not a digit
            return 0;
        continue;
    }
    return 1;
}

TreeNode *new_node()
{
    TreeNode *n = malloc(sizeof(TreeNode));
    if (!n) // if malloc fails
    {
        fprintf(stderr, "Memory Error\n");
        exit(1);
    }
    n->nv = 0;
    return n;
}

int research(TreeNode *node, int val_to_search, int h)
{
    for (int i = 0; i < 3; i++) // value in node
    {
        if (node->key[i] == val_to_search)
        {
            printf("Value : %d find at height : %d\n", node->key[i], h);
            return 0;
        }
    }

    h += 1; // increment height
    // Recursive search
    if (val_to_search < node->key[0])
    {
        if (!node->child[0])
            return -1;
        return research(node->child[0], val_to_search, h);
    }
    else if (val_to_search < node->key[1] || !node->key[1])
    {
        if (!node->child[1])
            return -1;
        return research(node->child[1], val_to_search, h);
    }
    else if (val_to_search < node->key[2] || !node->key[2])
    {
        if (!node->child[2])
            return -1;
        return research(node->child[2], val_to_search, h);
    }
    else
    {
        if (!node->child[3])
            return -1;
        return research(node->child[3], val_to_search, h);
    }
    return -1;
}

void split_full_node(TreeNode *node, TreeNode **node2, TreeNode **node3, int *k) // node2 = node->left, node3 = node->right, k = node->key
{
    *k = node->key[1];
    *node2 = new_node();
    *node3 = new_node();
    node2[0]->nv = 2;
    node3[0]->nv = 2;
    node2[0]->child[0] = node->child[0];
    node2[0]->child[1] = node->child[1];
    node3[0]->child[0] = node->child[2];
    node3[0]->child[1] = node->child[3];
    node2[0]->key[0] = node->key[0];
    node3[0]->key[0] = node->key[2];
    printf("Split.\n");
}

void add_key(TreeNode *node, int n, int val_to_insert) // add new key to node
{
    int i;
    node->child[node->nv] = NULL;
    for (i = node->nv - 1; i > n; i--)
        node->key[i] = node->key[i - 1];

    node->key[n] = val_to_insert;
    node->nv++;
    printf("Value : %d insert\n", val_to_insert);
}

void insert__(TreeNode *parent_node, int val_to_insert, int n, TreeNode *node)
{
    if (node == NULL)
    {
        add_key(parent_node, n, val_to_insert);
        return;
    }
    if (node->nv == 4)
    {
        TreeNode *node2, *node3;
        int k;
        int i = 0;
        split_full_node(node, &node2, &node3, &k);

        for (i = parent_node->nv; i > n; i--)
            parent_node->child[i] = parent_node->child[i - 1];

        for (i = parent_node->nv - 1; i > n; i--)
            parent_node->key[i] = parent_node->key[i - 1];

        parent_node->key[n] = k;
        parent_node->child[n] = node2;
        parent_node->child[n + 1] = node3;
        parent_node->nv++;
        free(node);
        if (val_to_insert < k) // if val_to_insert < k
            insert__(parent_node, val_to_insert, 0, node2);

        else // if val_to_insert > k or val_to_insert == k
            insert__(parent_node, val_to_insert, 1, node3);
    }
    else // if node->nv < 4
    {
        if (val_to_insert < node->key[0]) // if val_to_insert < node->key[0]
            insert__(node, val_to_insert, 0, node->child[0]);

        else if (node->nv == 2)
            insert__(node, val_to_insert, 1, node->child[1]);

        else
        {
            if (val_to_insert < node->key[1]) // if val_to_insert < node->key[1]
                insert__(node, val_to_insert, 1, node->child[1]);
            else
                insert__(node, val_to_insert, 2, node->child[2]);
        }
    }
}

void insert_(TreeNode *node, int val_to_insert)
{
    if (val_to_insert < node->key[0]) // if val_to_insert < node->key[0]
        insert__(node, val_to_insert, 0, node->child[0]);
    else // if val_to_insert >= node->key[0]
    {
        if (node->nv == 2)
            insert__(node, val_to_insert, 1, node->child[1]);
        else // if node->nv == 1 or 3
        {
            if (val_to_insert < node->key[1]) // if val_to_insert < node->key[1]
            {
                insert__(node, val_to_insert, 1, node->child[1]);
            }
            else // if val_to_insert >= node->key[1]
            {
                printf("%d > %d\n", val_to_insert, node->key[1]);
                insert__(node, val_to_insert, 2, node->child[2]);
            }
        }
    }
}

TreeNode *insert(TreeNode *root, int val_to_insert)
{
    if (root == NULL || root->nv == 0) // if root is null or root is empty
    {
        TreeNode *node = new_node();
        node->nv = 2;
        node->child[0] = NULL;
        node->child[1] = NULL;
        node->key[0] = val_to_insert;
        printf("Value : %d insert\n", val_to_insert);
        return node;
    }
    else if (root->nv == 4) // node is full
    {
        TreeNode *node_ = new_node();
        node_->nv = 2;
        split_full_node(root, &node_->child[0], &node_->child[1], &node_->key[0]);
        insert_(node_, val_to_insert);
        free(root);
        return node_;
    }
    else // node is not full
    {
        insert_(root, val_to_insert);
        return root;
    }
}

/*------------------------------------------------Test Graphiz------------------------------------------------*/
// void print_Tree(TreeNode *node) // print tree
// {
//     // write in the file diagraph.dot
//     const char *filename = "diagraph.dot";

//     FILE *output_file = fopen(filename, "w+");
//     if (!output_file) // if file is not open
//     {
//         perror("fopen");
//         exit(EXIT_FAILURE);
//     }

//     fprintf(output_file, "digraph{\n");
//     fprintf(output_file, " \" %d\" -> \" %d,%d\"   \" %d\" -> \" %d,%d\"  ", node->key[0], node->child[0]->key[0], node->child[0]->key[1], node->key[0], node->child[1]->key[0], node->child[1]->key[1]);
//     fprintf(output_file, "}");
//     printf("Done Writing !\n");

//     fclose(output_file);
//     free_tree(node);
// }
/*------------------------------------------------Test Graphiz------------------------------------------------*/

void spaces(int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("   ");
}

void print_Tree(TreeNode *node, int n_node)
{
    int i;
    if (node == NULL)
        return;
    print_Tree(node->child[0], n_node + 1);
    for (i = 0; i < node->nv - 1; i++)
    {
        spaces(n_node);
        printf("%d\n", node->key[i]);
        print_Tree(node->child[i + 1], n_node + 1);
    }
}

void free_tree(TreeNode *root)
{
    if (root == NULL)
        return;
    for (int i = 0; i < root->nv; i++)
        free_tree(root->child[i]);
    free(root);
}

enum
{
    max_string = 127 // max string length
};
static char string_insert[max_string + 1] = "";   // string to insert
static char string_research[max_string + 1] = ""; // string to research

int main(int argc, char *argv[])
{
    if (argc <= 1) // if no argument
    {
        fprintf(stderr, "Usage : \"./K_Tree `value to insert`\",\nThe value found here is not admissible: %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    else if (argc >= 3) // if there is more than one argument
    {
        fprintf(stderr, "Usage : \"./K_Tree `value to insert`\",\nnumber of argument is too high.\nYou put some: %d\n", (argc - 1));
        exit(EXIT_FAILURE);
    }

    else if (is_digit(argv[1], strlen(argv[1])) == 0) // if argv[1] is not a digit
    {
        fprintf(stderr, "Usage : \"./K_Tree `value to insert`\",\nInsert a number.\nYour value is : `%s`\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (argc == 2) // if there is only one argument
    {
        TreeNode *root = new_node();
        root = insert(root, atoi(argv[1])); // insert the value of argv[1]
        while (1)                           // loop until user want to quit
        {
            printf("Insert a value (q for quit, p for print tree, r for research): ");
            fflush(stdout);
            fgets(string_insert, max_string, stdin);
            char *endPtr;

            strtol(argv[1], &endPtr, 10);
            if (strcmp(string_insert, "q\n") == 0) // if user want to quit
            {
                printf("exit success...\n");
                free_tree(root);
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(string_insert, "p\n") == 0) // if user want to print tree
                print_Tree(root, 0);
            else if (strcmp(string_insert, "r\n") == 0) // if user want to research
            {
                printf("Value to research: ");
                fflush(stdout);
                fgets(string_research, max_string, stdin);
                int val = atoi(string_research);
                if (research(root, val, 0) == -1)
                {
                    printf("Value %d is not in the tree\n", val);
                }
            }
            else // if user want to insert a value
            {
                strtol(string_insert, &endPtr, 10);
                if (endPtr == string_insert)
                    fprintf(stderr, "Bad string format (is not number): %s", endPtr);
                else
                    root = insert(root, atoi(string_insert));
            }
        }
        return 0;
    }
}
