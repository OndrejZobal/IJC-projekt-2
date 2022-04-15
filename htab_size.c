// 2) htab_size.c
// Ondřej Zobal (xzobal01)
// FIT VUT v Brně
// 15.4.2022

#include "htab.h"
#include "htab_t.h"

size_t htab_size(const htab_t * t) {
    return t->size;
}
