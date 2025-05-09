#ifndef SORTING_HEADER
#define SORTING_HEADER
#include <stdbool.h>

// Simple bubble sort implementation with a worst case sinario of O(n^2) and best case of O(n)
void bubble_sort_int(int *arr, size_t len)
{
    bool isSorted = false;
    while (!isSorted)
    {
        isSorted = true;
        for (size_t i = 0; i < len - 1; i++)
        {
            size_t next = arr[i + 1];
            // If next element is smaller swap them.
            if (arr[i] > next)
            {
                // If a swap had to be done, set sorted to false, this mean if no swaps have been done it can exit early and improve on the best case scenario.
                isSorted = false;
                arr[i + 1] = arr[i];
                arr[i] = next;
            }
        }
    }
}
// Simple implementation of merge sort, cant sort too large arrays because its a recursive implementation.
// Time complexity of O(n log(n))
void merge_sort(int *arr, int len) {
    // 1 or less element, cant sort
    if (len < 2) return;
    // Split index, in middle
    int dividor = len / 2;
    int *left = malloc(dividor * sizeof(int));
    // len - dividor, to solve uneven lengths 
    int *right = malloc((len - dividor) * sizeof(int));

    // copy left part of divior to the left array
    for (int i = 0; i < dividor; i++) left[i] = arr[i];
    // copy right part of divior to the right array
    for (int i = dividor; i < len; i++) right[i - dividor] = arr[i];

    // Recursivly call this function, this will keep getting called until the array is unly of size 1
    // then it will proside with sorting each tree 
    merge_sort(left, dividor);
    merge_sort(right, len - dividor);

    // Merge
    int i = 0, j = 0, k = 0;
    while (i < dividor && j < len - dividor)
        arr[k++] = (left[i] < right[j]) ? left[i++] : right[j++];
    while (i < dividor) arr[k++] = left[i++];
    while (j < len - dividor) arr[k++] = right[j++];

    // Free the created arrays
    free(left);
    free(right);
}


#endif