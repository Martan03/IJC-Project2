// tail.c
// Řešení IJC-DU2, příklad a), 30.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: clang 14.0.0-1ubuntu1
// Implementace funkcionality tail pomocí circular bufferu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdarg.h>

#define MAX_LINE 80
#define R "\x1b[91m"
#define G "\x1b[92m"
#define Y "\x1b[93m"
#define W "\x1b[97m"
#define BB "\x1b[90m"
#define RS "\x1b[0m"

#define printe(msg) fprintf(stderr, R "Error: " RS "%s", msg)

typedef struct
{
    char **data;
    int size, end, start;
} cb_t;

/// @brief Processes given file to get last n lines
/// @param f file
/// @param n number of lines to be printed
void process(FILE* f, int n);

/// @brief Checks if string was malloced correctly, exits on failure
/// @param line line to be checked
static inline void line_malloced(char* line);

/// @brief Gets line from file
/// @param f file
/// @param line output string
/// @param len length of the output string
/// @return number of read characters
size_t get_line(FILE* f, char* line, size_t len);

/// @brief Creates circular buffer
/// @param n number of lines in cb
/// @return created circular buffer
cb_t cb_create(int n);

/// @brief Puts line to the cb
/// @param cb circular buffer
/// @param line line to be added
char* cb_put(cb_t* cb, char *line);

/// @brief Gets line from cb
/// @param cb cirular buffer
char* cb_get(cb_t* cb);

/// @brief Frees cb
/// @param cb circular buffer
void cb_free(cb_t cb);

/// @brief Prints help
void help();

int main(int argc, char** argv) {
    FILE* f = stdin;
    int n = 10;
    while(*++argv) {
        if (strcmp(*argv, "-h") == 0 || strcmp(*argv, "--help") == 0) {
            help();
            return 0;
        }
        else if (strcmp(*argv, "-n") == 0) {
            n = atoi(*++argv);
        }
        else {
            if (f != stdin) {
                printe("multiple files not supported\n");
                fclose(f);
                return 1;
            }
            f = fopen(*argv, "r");
            if (!f) {
                printe("invalid usage, ");
                fprintf(stderr, "'%s' is not file nor flag.\n", *argv);
                return 1;
            }
        }
    }

    process(f, n);
    fclose(f);

    return 0;
}

void process(FILE *f, int n) {
    cb_t cb = cb_create(n);

    char* line = malloc(MAX_LINE);
    line_malloced(line);

    bool warn = true;
    int count = 0;
    while ((count = get_line(f, line, MAX_LINE))) {
        if (line[count - 1] != '\n') {
            line[count - 1] = '\n';
            if (warn) {
                printe("line too long\n");
                warn = false;
            }
            fscanf(f, "%*[^\n]");
            fscanf(f, "\n");
        }

        line = cb_put(&cb, line);

        if (!line) {
            line = malloc(MAX_LINE);
            line_malloced(line);
        }
    }

    while (cb.start != cb.end) {
        printf("%s", cb_get(&cb));
    }

    cb_free(cb);
    free(line);
}

static inline void line_malloced(char* line) {
    if (!line) {
        printe("allocating memory");
        exit(1);
    }
}

size_t get_line(FILE *f, char* line, size_t len) {
    int c = 0;
    size_t org = len;
    while (--len && c != '\n' && (c = fgetc(f)) != EOF)
        *line++ = c;
    *line = '\0';
    return org - len - 1;
}

cb_t cb_create(int n) {
    cb_t cb = {
        .size = n + 1,
        .start = 0,
        .end = 0
    };

    cb.data = calloc(cb.size, sizeof(char*));
    if (!cb.data) {
        printe("allocating memory\n");
        exit(1);
    }
    return cb;
}

char* cb_put(cb_t* cb, char *line) {
    char* item = cb->data[cb->end];

    if ((cb->end + 1) % cb->size == cb->start)
        cb->start = (cb->start + 1) % cb->size;

    cb->data[cb->end++] = line;
    cb->end %= cb->size;
    return item;
}

char* cb_get(cb_t* cb) {
    char* item = cb->data[cb->start++];
    cb->start %= cb->size;
    return item;
}

void cb_free(cb_t cb) {
    for (cb.size -= 1; cb.size >= 0; cb.size--) {
        if (cb.data[cb.size]) {
            free(cb.data[cb.size]);
            cb.data[cb.size] = NULL;
        }
    }
    free(cb.data);
    cb.data = NULL;
}

void help() {
    printf("Welcome to help for " G "Tail" RS " by ");
    // Prints name with color gradient
    char* name = "xsleza26";
    int r = 0, g = 220;
    for (size_t i = 0; i < strlen(name); ++i)
        printf("\x1b[38;2;%lu;%lu;255m%c", r + i * 25, g - i * 20, name[i]);
    printf("");

    // Prints usage
    printf(G "\nUsage: " W "tail " BB "[flags] [file]\n\n" RS);
    printf(G "Flags:\n" RS);
    printf(Y "  -h --help\n" RS "    Displays help\n\n");
    printf(Y "  -n " BB "[number]\n" RS
        "    Prints given number of lines\n\n");
}
