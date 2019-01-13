CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g


test: src/main.c src/heap.c
	$(CC) $(CFLAGS) src/main.c src/heap.c -Iinclude -o bin/testMe -lm

cppcheck:
		cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

clean:
	rm bin/*
