CC:=clang
OUT:=tail
CFLAGS:=-g -Wall -Wextra -std=c11 -pedantic -fsanitize=address
RFLAGS:=-std=c17 -lm -DNDEBUG -O3
OBJS:=$(patsubst src/%.c, obj/%.o, $(CFILES))

debug: ./obj/tail.o
	$(CC) $(CFLAGS) -o bin/debug/$(OUT) $<

release: $(CFILES)
	$(CC) $(RFLAGS) -o bin/release/$(OUT) $(CFILES)

./obj/tail.o: ./src/tail.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS)
