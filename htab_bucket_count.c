#include "htab.h"
#include "htab_t.h"

size_t htab_bucket_count(const htab_t * t) {
    return t->arr_ptr;
}