CFLAGS:=-g -Wall -Wextra -std=c11 -pedantic -fsanitize=address -fPIC
LDFLAGS:=-fsanitize=address
RFLAGS:=-std=c17 -lm -DNDEBUG -O3

.PHONY: default clean

default: tail wordcount wordcount-dynamic

dep:=$(shell $(CC) -MM *.c > dep.d)
-include dep.d

tail:

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o $@ $^

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o $@ $^

libhtab.a: htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o
	ar r $@ $^

libhtab.so: htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o
	$(CC) -shared -o $@ $^

clean:
	-rm *.o libhtab.a libhtab.so tail wordcount wordcount-dynamic
