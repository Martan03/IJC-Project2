#include <stdlib.h>
#include "private_htab.h"

bool htab_erase(htab_t* t, htab_key_t key) {
    // Get key index using hash function
    int index = htab_hash_function(key) % t->arr_size;

    // First item on given index
    htab_item* prev = NULL;
    htab_item* tmp = t->arr_ptr[index];

    while (tmp) {
        // Return item with given key
        if (strcmp(tmp->data.key, key) == 0) {
            prev->next = tmp->next;
            free((char*) tmp->data.key);
            free(tmp);

            t->size--;

            return true;
        }
        
        // Get next item
        prev = tmp;
        tmp = tmp->next;
    }

    return false;
}
