#ifndef PRIVATE_HTAB_INCLUDED
#define PRIVATE_HTAB_INCLUDED

#include "htab.h"

typedef struct htab_item htab_item;

struct htab_item {
    htab_item* next;
    htab_pair_t data;
};

struct htab {
    htab_item** arr_ptr;
    size_t size, arr_size;
};

htab_item* _htab_find(const htab_t* t, htab_key_t key, bool add);

#endif // PRIVATE_HTAB_INCLUDED
