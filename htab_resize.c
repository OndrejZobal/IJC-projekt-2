#include "htab.h"
#include "htab_t.h"
#include <stdio.h>

// FIXME aaaaaaaaaaaaaaaaa
void htab_resize(htab_t *t, size_t newn) {
    //t->arr_ptr = realloc(t->arr_ptr, sizeof(htab_pair**) * newn);
    // TODO Ths needs to be done differently
    // I esentially need to make the whole array separately and then
    //manually readd every single hash. :facepalm:

    htab_item_t **newArray = calloc(sizeof(htab_item_t**), newn);
    if (!newArray) {
        fprintf(stderr, "Cannot allocate memory!\n");
        exit(1);
    }
    // Initing newArray
    for (size_t i = 0; i < newn; i++) {
        newArray[i] = NULL;
    }

    // For every index in the old array.
    for(int i = 0; (size_t) i < t->arr_size; i++) {
        // Looking up the has in the hash table
        htab_item_t *items = t->arr_ptr[i];
        htab_item_t *prevItems = NULL;

        // Itarating through the item list.
        while(items) {
            // Copute a new has of the item.
            int hash = htab_hash_function(items->pair.key);
            // Append to a propper list in the new Array.
            htab_item_t *newItems = newArray[hash % newn];
            htab_item_t *prevNewItems = NULL;

            // Searching for the end of the list.
            while(newItems) {
                prevNewItems = newItems;
                newItems = newItems->next;
            }

            // Appending to the end of the list.
            if(newItems != NULL) {
                newItems->next = items;
            }
            else if (prevNewItems != NULL) {
                prevNewItems->next = items;
            }
            else {
                newArray[hash % newn] = items;
            }

            prevItems = items;
            items = items->next;
            // Clearing the "next" ptr.
            prevItems->next = NULL;
        }
    }

    t->arr_size = newn;
    free(t->arr_ptr);
    t->arr_ptr = newArray;
}
