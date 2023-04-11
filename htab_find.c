#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "private_htab.h"

htab_item* _htab_find(const htab_t* t, htab_key_t key, bool add) {
    // Get key index using hash function
    int index = htab_hash_function(key) % t->arr_size;

    // First item on given index
    htab_item* prev = NULL;
    htab_item* tmp = t->arr_ptr[index];

    while (tmp) {
        // Return item with given key
        if (strcmp(tmp->data.key, key) == 0)
            return tmp;
        
        // Get next item
        prev = tmp;
        tmp = tmp->next;
    }

    if (!add)
        return NULL;

    // Creates new item if requested
    tmp = calloc(1, sizeof(htab_item));
    if (prev)
        prev->next = tmp;
    else
        t->arr_ptr[index] = tmp;

    return tmp;
}

htab_pair_t* htab_find(const htab_t* t, htab_key_t key) {
    // Gets element by key
    htab_item* item = _htab_find(t, key, false);

    if (!item)
        return NULL;

    return &(item->data);
}
