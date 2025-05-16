#ifndef B_TREE_HEADER
#define B_TREE_HEADER
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode TreeNode;

struct TreeNode
{
    int key;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *search(TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->key == key)
        return root;

    TreeNode *left_ptr_search = NULL;
    TreeNode *right_ptr_search = NULL;

    // Recursivly search each branch until a leaf reached or key found
    if (root->left != NULL)
    {
        left_ptr_search = search(root->left, key);
    }

    if (root->right != NULL)
    {
        right_ptr_search = search(root->right, key);
    }

    return left_ptr_search != NULL ? left_ptr_search : right_ptr_search;
}

int getDepth(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int left_depth = getDepth(root->left) + 1;
    int right_depth = getDepth(root->right) + 1;

    return left_depth > right_depth ? left_depth : right_depth;
}

TreeNode *createNode(int key)
{
    TreeNode *n = malloc(sizeof(TreeNode));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}

bool insert(TreeNode *root, TreeNode *node)
{
    if (root == NULL || node == NULL)
        return false;

    if (node->key < root->key)
    {
        if (root->left == NULL)
        {
            root->left = node;
            return true;
        }
        else
            return insert(root->left, node);
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = node;
            return true;
        }
        else
            return insert(root->right, node);
    }
}

TreeNode *createTreeFromArray(int *array, size_t len)
{
    if (len == 0)
        return NULL;

    TreeNode *root = createNode(array[0]);
    for (size_t i = 1; i < len; i++)
    {
        TreeNode *node = createNode(array[i]);

        assert(node != NULL && "Create node was NULL, cant insert a NULL node.");

        insert(root, node);
    }
    return root;
}

/**** CHATGPT code, dont have the time or care about the workings of printing the tree in a tree structure.*****/

void printTreeHorizontal(int level, TreeNode *ptr, TreeNode *root)
{
    int i;
    if (ptr != NULL)
    {
        printTreeHorizontal(level + 1, ptr->right, root);
        printf("\n");
        if (ptr == root)
            printf("Root -> ");
        for (i = 0; i < level && ptr != root; i++)
            printf("        ");
        printf("%d", ptr->key);
        printTreeHorizontal(level + 1, ptr->left, root);
    }
}

void printTree(TreeNode *root)
{
    printTreeHorizontal(0, root, root);
}

/******* END OF CHATGPT CODE!! *****/

TreeNode *minimum(TreeNode *root)
{
    if (root == NULL)
        return NULL;

    // find left most leaf, it is the min in a binary search tree
    if (root->left != NULL)
        return minimum(root->left);

    return root;
}

TreeNode *maximum(TreeNode *root)
{
    if (root == NULL)
        return NULL;
    // find right most leaf, it is the max in a binary search tree
    if (root->right != NULL)
        return maximum(root->right);

    return root;
}

TreeNode *successor(TreeNode *root, TreeNode *node)
{
    if (root == NULL || node == NULL)
        return NULL;

    // Right node is always next largest
    if (node->right != NULL)
        return minimum(node->right);

    // If right node is null, travers up until a right node is found
    TreeNode *succ = NULL;
    TreeNode *curr = root;

    while (curr)
    {
        if (node->key < curr->key)
        {
            succ = curr;
            curr = curr->left;
        }
        else if (node->key > curr->key)
        {
            curr = curr->right;
        }
        else
        {
            break;
        }
    }

    return succ;
}

TreeNode *predecessor(TreeNode *root, TreeNode *node)
{
    if (root == NULL || node == NULL)
        return NULL;

    // Left node is always next smallest
    if (node->left != NULL)
        return maximum(node->left);

    // If left node is null, travers up until a left node is found
    TreeNode *succ = NULL;
    TreeNode *curr = root;

    while (curr)
    {
        if (node->key > curr->key)
        {
            succ = curr;
            curr = curr->right;
        }
        else if (node->key < curr->key)
        {
            curr = curr->left;
        }
        else
        {
            break;
        }
    }

    return succ;
}

void printSortedTree(TreeNode *root)
{
    TreeNode *succ = minimum(root);
    while (succ != NULL)
    {
        printf("%d", succ->key);
        printf(", ");
        succ = successor(root, succ);
    }
}

#endif