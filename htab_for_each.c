#include "htab.h"
#include "htab_t.h"
#include "htab_item_t.h"
#include "stdio.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for(int i = 0; (size_t) i < t->arr_size; i++) {
        htab_item_t *current_item = t->arr_ptr[i];
        while(current_item != NULL) {
            f(&current_item->pair);
            current_item = current_item->next;
        }
    }
}
