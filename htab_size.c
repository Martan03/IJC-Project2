#include "private_htab.h"

size_t htab_size(const htab_t * t) {
    return t->size;
}

size_t htab_bucket_count(const htab_t* t) {
    return t->arr_size;
}
