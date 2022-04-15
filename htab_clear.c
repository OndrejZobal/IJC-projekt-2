// 2) htab_clear.c
// Ondřej Zobal (xzobal01)
// FIT VUT v Brně
// 15.4.2022

#include "htab.h"
#include "htab.h"
#include "htab_t.h"
#include "htab_item_t.h"

// TODO maybe make a header
void htab_clear_helper(struct htab_item *i) {
    if(i == NULL) {
        return;
    }

    htab_clear_helper(i->next);
    free((char*) i->pair.key);
    free(i);
}

void htab_clear(htab_t * t) {
    for(size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *current_item = t->arr_ptr[i];
        htab_clear_helper(current_item);
        t->arr_ptr[i] = NULL;
    }
}

