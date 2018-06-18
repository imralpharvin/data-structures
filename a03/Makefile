CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g


main: src/main.c src/heap.c src/priorityQueueADT.c src/emergency.c
	$(CC) $(CFLAGS) src/main.c src/heap.c src/priorityQueueADT.c src/emergency.c -Iinclude -o bin/runMe -lm

test: src/testQueue.c  src/LinkedListAPI.c src/QueueADT.c src/car.c
	$(CC) $(CFLAGS) src/testQueue.c src/LinkedListAPI.c src/QueueADT.c src/car.c  -Iinclude -o bin/testMe -lm

cppcheck:
		cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

clean:
	rm bin/*
