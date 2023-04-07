#ifndef IO_INCLUDED
#define IO_INCLUDED

#include <stdio.h>

/// @brief Reads words from given file
/// @param s output string
/// @param max maximum word length
/// @param f file to read from
/// @return length of the word
int read_word(char *s, int max, FILE *f);

#endif // IO_INCLUDED
