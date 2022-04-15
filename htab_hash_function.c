// 2) htab_hash_function.c
// Ondřej Zobal (xzobal01)
// FIT VUT v Brně
// 15.4.2022

#include <stdint.h>
#include "htab.h"

size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}
