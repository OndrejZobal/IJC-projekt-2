#include "htab.h"
#include "htab_t.h"
#include "htab_item_t.h"

void htab_free(htab_t * t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}
