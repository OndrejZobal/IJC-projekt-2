#include "htab.h"
#ifndef __HTAB_ITEM_T__
#define __HTAB_ITEM_T__

typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

#endif
