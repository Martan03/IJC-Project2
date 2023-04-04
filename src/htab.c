#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "htab.h"

typedef struct htab_item htab_item;

struct htab_item {
    htab_item* next;
    htab_pair_t data;
};

struct htab {
    htab_item* arr_ptr;
    size_t size, arr_size;
};

#define htab_loop(inside) \
    htab_item* tmp; \
    for (size_t i = 0; i < t->arr_size; ++i) { \
        tmp = &(t->arr_ptr[i]); \
        while (tmp) { \
            inside \
        } \
    } \

size_t htab_hash_function(const char *str) {
    uint32_t h = 0;     // musí mít 32 bitů
    const unsigned char* p;
    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}

htab_t* htab_init(const size_t n) {
    htab_t* htab = calloc(1, sizeof(htab_t));
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

size_t htab_size(const htab_t * t) {
    return t->size;
}

size_t htab_bucket_count(const htab_t* t) {
    return t->arr_size;
}

htab_pair_t* htab_find(const htab_t* t, htab_key_t key) {
    htab_item* tmp;
    for (htab_item* i = t->arr_ptr; i; ++i) {
        tmp = i;
        while (tmp) {
            if (strcmp(i->data.key, key) == 0)
                return &(i->data);
            tmp = tmp->next;
        }
    }
    return NULL;
}

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key) {
    size_t index = htab_hash_function(key);
    htab_item* tmp = &(t->arr_ptr[index]);
    while (tmp) {
        if (strcmp(tmp->data.key, key) == 0) {
            tmp->data.value++;
            return &(tmp->data);
        }
    }

    htab_item* item = calloc(1, sizeof(htab_item));
    if (!item)
        return NULL;

    item->data.key = key;
    item->data.value = 1;
    tmp->next = item;

    return item;
}

void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data)) {
    htab_loop(
        f(&tmp->data);
        tmp = tmp->next;
    );
}

void htab_clear(htab_t* t) {
    htab_loop(
        htab_item* next = tmp->next;
        free(tmp);
        tmp = next;
    );
}

void htab_free(htab_t* t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
} 
