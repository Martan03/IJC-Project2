#include "private_htab.h"

void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data)) {
    htab_item* tmp;
    for (size_t i = 0; i < t->arr_size; ++i) {
        tmp = t->arr_ptr[i];
        while (tmp) {
            f(&(tmp->data));
            tmp = tmp->next;
        }
    }
}
