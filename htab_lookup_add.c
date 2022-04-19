// 2) htab_lookup_add.c
// Ondřej Zobal (xzobal01)
// FIT VUT v Brně
// 15.4.2022

#include "htab.h"
#include "htab_t.h"
#include "htab_item_t.h"

#include <stdio.h>


#define AVG_LEN_MAX 3

void htab_la_check_for_resize(htab_t *t) {
    if (t->size / t->arr_size > AVG_LEN_MAX){
        printf("resize\n");
        htab_resize(t, t->size*2);
    }
}

htab_pair_t *htab_lookup_add(htab_t * t, htab_key_t key) {
    // Computing hash
    size_t hash = htab_hash_function(key);
    // Looking up the has in the hash table
    htab_item_t *items = t->arr_ptr[hash % t->arr_size];
    htab_item_t *itemsPrev = NULL;
    // Itarating through the list.
    while(items != NULL) {
        if(!strcmp(items->pair.key, key)) {
            return &items->pair;
            break;
        }
        itemsPrev = items;
        items = items->next;
    }

    // no items is either null or just before null.

    // lookup was not sucessfull
    // creating new item
    htab_item_t *newItem = malloc(sizeof(htab_item_t));
    if (newItem == NULL) {
        exit(1);
    }

    char *keyString = malloc(sizeof(char) * (strlen(key)+1));
    strcpy(keyString, key);

    newItem->pair.key = keyString;
    newItem->pair.value = 0;
    newItem->next = NULL;
    t->size++;

    if(items != NULL) {
        items->next = newItem;
    }
    else if (itemsPrev != NULL) {
        itemsPrev->next = newItem;
    }
    else {
        t->arr_ptr[hash % t->arr_size] = newItem;
    }

    // Resize if smol.
    if (t->size / t->arr_size > AVG_LEN_MAX){
        htab_resize(t, t->size*2);
    }

    return &newItem->pair;
}
