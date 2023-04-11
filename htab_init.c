#include <stdlib.h>
#include "private_htab.h"

htab_t* htab_init(const size_t n) {
    htab_t* htab = malloc(sizeof(htab_t));
    if (!htab)
        return NULL;
    
    htab->arr_ptr = calloc(n, sizeof(htab_item));
    if (!htab->arr_ptr) {
        free(htab);
        return NULL;
    }

    htab->size = 0;
    htab->arr_size = n;
    return htab;
}
