#include <assert.h>
#include <stdio.h>
#include "b-tree.h"
#include "load_file.h"

#define ARRAY_LEN(x) (sizeof(x) / sizeof(x[0]))

void test_create_and_insert_search()
{   
    int values[] = {20, 10, 30, 5, 15, 25, 35};
    TreeNode *root = createTreeFromArray(values, ARRAY_LEN(values));
    assert(root != NULL);
    assert(root->key == 20);

    // Search for each value in the tree based on the values added from values array
    // all values should be found
    for (int i = 0; i < ARRAY_LEN(values); ++i)
    {
        TreeNode *found = search(root, values[i]);
        assert(found != NULL);
        assert(found->key == values[i]);
    }
    // 100 is not in the array and those search should return NULL
    assert(search(root, 100) == NULL); 
    printf("createTreeFromArray & insert & search passed.\n");
}

void test_get_depth()
{   
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    TreeNode *root = createTreeFromArray(values, ARRAY_LEN(values));
    assert(getDepth(root) == 3);
    printf("getDepth passed.\n");
}

void test_minimum_maximum()
{
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    TreeNode *root = createTreeFromArray(values, ARRAY_LEN(values));
    TreeNode *minNode = minimum(root);
    TreeNode *maxNode = maximum(root);
    // Assert the minimum and maximum found is correct
    assert(minNode != NULL && minNode->key == 20);
    assert(maxNode != NULL && maxNode->key == 80);
    printf("minimum & maximum passed.\n");
}

void test_successor_predecessor()
{
    int values[] = {20, 10, 30, 5, 15, 25, 35};
    TreeNode *root = createTreeFromArray(values, ARRAY_LEN(values));

    TreeNode *n10 = search(root, 10);
    TreeNode *n30 = search(root, 30);
    TreeNode *n35 = search(root, 35);
    TreeNode *n5 = search(root, 5);

    // Simple chech the successor/predessor if there correct based on the values array
    assert(successor(root, n10)->key == 15); // next larger
    assert(successor(root, n30)->key == 35);
    assert(successor(root, n35) == NULL); // max node has no successor

    assert(predecessor(root, n30)->key == 25);
    assert(predecessor(root, n5) == NULL); // min node has no predecessor
    printf("successor & predecessor passed.\n");
}

void test_edge_cases()
{
    TreeNode *root = NULL;
    // ensure faulty values are handled correctly
    assert(search(root, 42) == NULL);
    assert(getDepth(NULL) == 0);
    assert(minimum(NULL) == NULL);
    assert(maximum(NULL) == NULL);
    assert(successor(NULL, NULL) == NULL);
    assert(predecessor(NULL, NULL) == NULL);
    assert(insert(NULL, NULL) == false);
    assert(insert(createNode(1), NULL) == false);
    assert(insert(NULL, createNode(2)) == false);

    TreeNode *single = createNode(10);
    assert(getDepth(single) == 1);
    assert(minimum(single)->key == 10);
    assert(maximum(single)->key == 10);
    assert(successor(single, single) == NULL);
    assert(predecessor(single, single) == NULL);

    printf("All edge cases checks passed.\n");
}

void test_print_tree()
{
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    TreeNode *root = createTreeFromArray(values, ARRAY_LEN(values));
    printf("\n");
    printTree(root);
    printf("\n");
    printSortedTree(root);
}

void print_sorted_from_file(const char *path)
{
    int *arr = load_file(path);

    if (arr == NULL)
        return;

    int len = arr[0];
    printf("\n\n");

    printSortedTree(createTreeFromArray(arr++, len));
}

int main(int argc, char *argv[])
{
    test_create_and_insert_search();
    test_get_depth();
    test_minimum_maximum();
    test_successor_predecessor();
    test_edge_cases();
    test_print_tree();

    // File path passed as param
    if (argc >= 2)
        print_sorted_from_file(argv[1]);

    printf("\n All tests passed!!\n");
    return 0;
}
