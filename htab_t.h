#include <htab.h>
#include <stdlib.h>

struct htab_t {
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;
};
