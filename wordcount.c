#include <stdlib.h>
#include "io.h"
#include "htab.h"

// Creating macros for ansi color codes
#define R "\x1b[91m"
#define G "\x1b[92m"
#define Y "\x1b[93m"
#define W "\x1b[97m"
#define BB "\x1b[90m"
#define RS "\x1b[0m"

// Macro for printing error message
#define printe(msg) fprintf(stderr, R "Error: " RS "%s", msg)

/// @brief Prints given pair
/// @param pair 
void print(htab_pair_t* pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main() {
    char* s = malloc(255);
    if (!s) {
        printe("allocating memory\n");
        return 1;
    }

    // Initiliazies hash table
    htab_t* t = htab_init(314159);
    htab_pair_t* pair = NULL;

    // Reads words and adds them to hash table
    while (read_word(s, 255, stdin) != EOF) {
        pair = htab_lookup_add(t, s);
        if (!pair) {
            printe("allocating memory\n");
            return 1;
        }
    }

    // Prints hash table
    htab_for_each(t, print);

#ifdef STATISTICS
    htab_statistics(t);
#endif // STATISTICS

    // Frees everything needed
    free(s);
    htab_free(t);
    return 0;
}
