#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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

size_t htab_hash_function(const char *str) {
    uint32_t h = 0;     // musí mít 32 bitů
    const unsigned char* p;
    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}

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

size_t htab_size(const htab_t * t) {
    return t->size;
}

size_t htab_bucket_count(const htab_t* t) {
    return t->arr_size;
}

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

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key) {
    // Gets item by key, new item if doesn't exist
    htab_item* item = _htab_find(t, key, true);

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

            return true;
        }
        
        // Get next item
        prev = tmp;
        tmp = tmp->next;
    }

    return false;
}

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
