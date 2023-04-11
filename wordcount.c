#include <stdlib.h>
#include "io.h"
#include "htab.h"

void print(htab_pair_t* pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main() {
    char* s = malloc(255);
    if (!s)
        return 1;

    htab_t* t = htab_init(100);
    while (read_word(s, 255, stdin)) {
        htab_lookup_add(t, s);
    }

    htab_for_each(t, print);

    htab_erase(t, "se");

    printf("\n");
    htab_for_each(t, print);

    free(s);
    htab_free(t);
    return 0;
}
