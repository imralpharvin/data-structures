CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g

main: src/main.c src/PasswordVault.c src/HashTableAPI.c
	$(CC) $(CFLAGS) src/main.c src/PasswordVault.c src/HashTableAPI.c  -Iinclude -o bin/runMe

test: src/testAPI.c src/PasswordVault.c src/HashTableAPI.c
	$(CC) $(CFLAGS) src/testAPI.c src/PasswordVault.c src/HashTableAPI.c  -Iinclude -o bin/testMe

cppcheck:
		cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

clean:
	rm bin/*
	rm assets/*
