#include "htab.h"
#include "htab_t.h"
#include "htab_item_t.h"

#include <stdio.h>

htab_pair_t *htab_lookup_add(htab_t * t, htab_key_t key) {
    // Computing hash
    size_t hash = htab_hash_function(key);
    // Looking up the has in the hash table
    htab_item_t *items = t->arr_ptr[hash % t->arr_size];
    // Itarating through the list.
    while(items != NULL) {
        if(!strcmp(items->pair->key, key)) {
            return &items->pair;
        }
        items = items->next;
    }

    items = malloc(sizeof(htab_item_t));
    if (items == NULL) {
        fprintf(stderr, "Memory error");
        exit(1);
    }

    items->pair.key = key;
    items->pair.value = 0;
    items->next = NULL;

    return &items->pair;
}
