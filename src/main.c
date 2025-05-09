#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sorting.h"

void test_bubble_sort_int()
{
    int data[] = {3, 1, 5, 10, 8, 7};
    int expected[] = {1, 3, 5, 7, 8, 10};
    size_t len = sizeof(data) / sizeof(data[0]);

    bubble_sort_int(data, len);
    for (size_t i = 0; i < len; i++)
    {
        assert(data[i] == expected[i]);
        printf("%d\n", data[i]);
    }

    printf("test_bubble_sort_int passed.\n");
}

void test_merge_sort_int()
{
    int data[] = {3, 1, 5, 10, 8, 7};
    int expected[] = {1, 3, 5, 7, 8, 10};
    size_t len = sizeof(data) / sizeof(data[0]);

    merge_sort(data, len);
    for (size_t i = 0; i < len; i++)
    {
        assert(data[i] == expected[i]);
        printf("%d\n", data[i]);
    }

    printf("test_merge_sort_int passed.\n");
}

void test_file_with_solution(const char *problem_file)
{
    // Load problem file
    int *problem_data = load_file(problem_file);
    if (!problem_data)
    {
        printf("Failed to load problem file: %s\n", problem_file);
        return;
    }
    int size = problem_data[0];
    // Increment data pointer, since first index is the size
    int *data = problem_data + 1;

    // Load corresponding solution file
    char solution_file[256];
    strncpy(solution_file, problem_file, 250);

    // SUbstring -problem from file name to later concatante -solutions to get the solution file
    char *ext = strstr(solution_file, "-problem");

    if (ext)
        strcpy(ext, "-solution");
    else
        strcat(solution_file, "-solution");

    // Load solution array
    int *solution_data = load_file(solution_file);
    if (!solution_data)
    {
        printf("Failed to load solution file: %s\n", solution_file);
        free(problem_data);
        return;
    }

    int expected_size = solution_data[0];
    int *expected = solution_data + 1;

    if (expected_size != size)
    {
        printf("Mismatch in size between problem and solution\n");
        free(problem_data);
        free(solution_data);
        return;
    }


    merge_sort(data, size);
    // Validate the sorted array
    int passed = 1;
    for (int i = 0; i < size; i++)
    {
        if (data[i] != expected[i])
        {
            passed = 0;
            printf("Mismatch at index %d: got %d, expected %d\n", i, data[i], expected[i]);
        }
    }

    if (passed)
        printf("test_file_with_solution passed for %s\n", problem_file);
    else
        printf("test_file_with_solution FAILED for %s\n", problem_file);

    free(problem_data);
    free(solution_data);
}

int main(int argc, char *argv[])
{
    // If no args passed just run simple test
    if (argc < 2)
    {
        test_bubble_sort_int();
        test_merge_sort_int();
    }
    else
    {
        test_file_with_solution(argv[1]);
    }

    return 0;
}
