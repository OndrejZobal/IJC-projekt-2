// 2) htab_erase.c
// Ondřej Zobal (xzobal01)
// FIT VUT v Brně
// 15.4.2022

#include "htab.h"
#include "htab_t.h"
#include "htab_item_t.h"
#include <stdbool.h>

bool htab_erase(htab_t * t, htab_key_t key) {
    // Computing hash
    size_t hash = htab_hash_function(key);
    // Looking up the has in the hash table
    htab_item_t *items = t->arr_ptr[hash % t->arr_size];
    htab_item_t *prev = NULL;

    while(items != NULL) {
        // If a match is found
        if(!strcmp(items->pair.key, key)) {
            if(prev != NULL) {
                prev->next = items->next;
            }
            else {
                t->arr_ptr[hash % t->arr_size] = NULL;
            }

            free((char*) items->pair.key);
            free(items);
            t->size--;

            return true;
        }
        prev = items;
        items = items->next;
    }

    return false;
}
