#include "htab.h"
#include "htab_t.h"

// FIXME aaaaaaaaaaaaaaaaa
void htab_resize(htab_t *t, size_t newn) {
    //t->arr_ptr = realloc(t->arr_ptr, sizeof(htab_pair**) * newn);
    // TODO Ths needs to be done differently
    // I esentially need to make the whole array separately and then
    //manually readd every single hash. :facepalm:

}
