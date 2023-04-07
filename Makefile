CC:=clang
OUT:=tail
CFLAGS:=-g -Wall -Wextra -std=c11 -pedantic -fsanitize=address
RFLAGS:=-std=c17 -lm -DNDEBUG -O3
OBJS:=$(patsubst src/%.c, obj/%.o, $(CFILES))

debug: wordcount

release: $(CFILES)
	$(CC) $(RFLAGS) -o bin/release/$(OUT) $(CFILES)

./obj/tail.o: ./src/tail.c
	$(CC) $(CFLAGS) -c $^ -o $@

wordcount: obj/wordcount.o obj/io.o obj/htab.o
	$(CC) $(CFLAGS) -o bin/debug/$@ $^

obj/wordcount.o: src/wordcount.c ./src/io.h ./src/htab.h
obj/io.o: src/io.c

obj/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS)
