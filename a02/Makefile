CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g


main: src/main.c src/PasswordVault.c src/HashTableAPI.c
	$(CC) $(CFLAGS) src/main.c src/PasswordVault.c src/HashTableAPI.c  -Iinclude -o bin/runMe

test: src/testQueue.c  src/LinkedListAPI.c src/QueueADT.c src/car.c
	$(CC) $(CFLAGS) src/testQueue.c src/LinkedListAPI.c src/QueueADT.c src/car.c  -Iinclude -o bin/testMe

cppcheck:
		cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

clean:
	rm bin/*
