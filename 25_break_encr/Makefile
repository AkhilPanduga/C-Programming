CFLAGS=-Wall -Werror -pedantic -std=gnu99

breaker: breaker.o
	gcc -o breaker breaker.o

breaker.o: breaker.c
	gcc $(CFLAGS) -c breaker.c

.PHONY: clean
clean:
	rm -f breaker *.o *.c~
