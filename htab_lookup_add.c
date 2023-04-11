#include <stdlib.h>
#include <string.h>
#include "private_htab.h"

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key) {
    // Gets item by key, new item if doesn't exist
    htab_item* item = _htab_find(t, key, 1); 

    // If key is set, add one to value
    if (item->data.key) {
        item->data.value++;
        return &(item->data);
    }

    // Copying key string to created item
    size_t key_len = strlen(key) + 1;
    char* new_key = malloc(key_len);
    memcpy(new_key, key, key_len);
    
    item->data.key = new_key;
    item->data.value = 1;

    return &(item->data);
}
