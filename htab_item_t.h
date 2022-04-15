// 2) htab_item_t.h
// Ondřej Zobal (xzobal01)
// FIT VUT v Brně
// 15.4.2022

#include "htab.h"
#ifndef __HTAB_ITEM_T__
#define __HTAB_ITEM_T__

typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

#endif
