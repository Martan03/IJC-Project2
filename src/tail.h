#ifndef TAIL_INCLUDED
#define TAIL_INCLUDED

typedef struct
{
    // to be implemented
} cb_t;


void cb_create(int n);

void cb_put(cb_t cb, char *line);

void cb_get(cb_t cb);

void cb_free(cb_t cb);

#endif // TAIL_INCLUDED
