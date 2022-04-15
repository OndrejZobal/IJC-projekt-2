// 2) htab_t.h
// Ondřej Zobal (xzobal01)
// FIT VUT v Brně
// 15.4.2022

#include "htab.h"
#include "htab_item_t.h"
#include <stdlib.h>

typedef struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
} htab_t;
