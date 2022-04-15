#include "htab.h"
#include "htab_item_t.h"
#include <stdlib.h>

typedef struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
} htab_t;
