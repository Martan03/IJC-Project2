#include <stdbool.h>
#include <ctype.h>
#include "io.h"

int read_word(char *s, int max, FILE *f) {
    int c;

    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    
    if (c == EOF)
        return 0;

    int i = 0;
    bool warn = true;
    do {
        if (i < max - 1) {
            s[i++] = c;
        }
        else if (warn) {
            fprintf(stderr, "Error: word is too long\n");
            warn = false;
        }
    } while ((c = fgetc(f)) != EOF && !isspace(c));
    s[i] = '\0';
    return i;
}
