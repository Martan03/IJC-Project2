#include <stdio.h>
#include <inttypes.h>
#include "private_htab.h"

void htab_statistics(const htab_t * t) {
    size_t min = SIZE_MAX, max = 0, len = 0, sum;
    double avg = t->size;
    for (size_t i = 0; i < t->arr_size; ++i) {
        sum = 0;
        for (htab_item* tmp = t->arr_ptr[i]; tmp; tmp = tmp->next)
            ++sum;
        
        len += sum != 0;

        if (min > sum)
            min = sum;

        if (max < sum)
            max = sum;
    }
    
    if (!len) {
        avg = 0;
        len = 1;
    }

    avg /= len;

    fprintf(stderr, "Min: %zu\nMax: %zu\nAvg: %lf\n", min, max, avg);
}
