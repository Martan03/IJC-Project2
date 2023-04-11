#include <stdlib.h>
#include "private_htab.h"

void htab_clear(htab_t* t) {
    htab_item* tmp;
    for (size_t i = 0; i < t->arr_size; ++i) {
        tmp = t->arr_ptr[i];
        while (tmp) {
            htab_item* next = tmp->next;
            free((char*)tmp->data.key);
            free(tmp);
            tmp = next;
        }
    }
}

void htab_free(htab_t* t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
} 
