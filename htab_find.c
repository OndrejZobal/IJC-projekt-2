#include "htab.h"
#include "htab_t.h"
#include "htab_item_t.h"

htab_pair_t *htab_find(htab_t * t, htab_key_t key) {
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

    // The key is not in the hashtable.
    return NULL;
}
