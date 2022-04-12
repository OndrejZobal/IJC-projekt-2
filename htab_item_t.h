#include "htab.h"

typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item_t *next;
} htab_item_t;
