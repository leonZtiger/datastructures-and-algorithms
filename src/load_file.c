#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "load_file.h"

// Reads integers from a file and returns them
// as a malloc-allocated array.
// Array indexes are 1..n.
// array[0] will contain the number "n" of elements in the array.
// The physical length of the array is therefore n+1.

int *load_file(const char *file_name)
{
    int *data = malloc(sizeof(int)); // For the length in data[0]
    int num_elements = 0;

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Couldn't open file '%s' (%s)\n", file_name, strerror(errno));
        fprintf(stderr, "Sorry. Goodbye.\n");
        exit(EXIT_FAILURE);
    }
    int this_number;
    while (fscanf(file, "%d", &this_number) == 1) {
        data = realloc(data, (++num_elements + 1) * sizeof(int));
        data[num_elements] = this_number;
    }
    if (!feof(file)) {
        fprintf(stderr, "Error: Malformed file '%s'. Goodbye.\n", file_name);
        exit(EXIT_FAILURE);
    }
    fclose(file);
    
    data[0] = num_elements;
    return data;
}
