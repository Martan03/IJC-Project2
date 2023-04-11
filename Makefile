CC:=clang
OUT:=tail
CFLAGS:=-g -Wall -Wextra -std=c11 -pedantic -fsanitize=address
RFLAGS:=-std=c17 -lm -DNDEBUG -O3

tail: tail.o

wordcount: wordcount.o io.o libhtab.a
	clang $(CFLAGS) -o $@ $^

wordcount-dynamic: wordcount.o io.o libhtab.so
	clang $(CFLAGS) -o $@ $^

libhtab.a: htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o
	ar r $@ $^

libhtab.so: htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o
	clang -shared -o $@ $^

wordcount.o: wordcount.c io.h htab.h
io.o: io.c
htab_%.o: htab_%.c private_htab.h 

%.o: %.c
	clang $(CFLAGS) -c $< -fPIC -o $@

clean:
	-rm *.o libhtab.a libhtab.so tail wordcount wordcount-dynamic
