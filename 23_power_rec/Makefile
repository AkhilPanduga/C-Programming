CFLAGS=-Wall -Werror -pedantic -std=gnu99

power: test-power.o power.o
	gcc -o power test-power.o power.o

%o: %c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f power *.o *.c~
