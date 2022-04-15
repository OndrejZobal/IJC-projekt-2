#include "htab.h"
#include "htab_t.h"

#include <stdio.h>

htab_t *htab_init(size_t n) {
    // Allocating Htab
    htab_t *newHtab = malloc(sizeof(htab_t));
    if (newHtab == NULL) {
        fprintf(stderr, "Memory error");
        exit(1);
    }

    // Filling Htab
    newHtab->size = 0;
    newHtab->arr_size = n;
    // All pointers in array will be NULL thanks to calloc.
    newHtab->arr_ptr = calloc(sizeof(htab_pair_t**), n);
    if (newHtab->arr_ptr == NULL) {
        fprintf(stderr, "Memory error");
        exit(1);
    }

    return newHtab;
}
