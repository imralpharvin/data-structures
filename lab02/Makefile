CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g


main: src/main.c src/HashTableAPI.c
	$(CC) $(CFLAGS) src/main.c src/HashTableAPI.c -Iinclude -o bin/runMe

cppcheck:
		cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

clean:
	rm bin/*
