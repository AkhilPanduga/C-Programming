CFLAGS=-Wall -Werror -pedantic -std=gnu99
test-c4deck: test-c4deck.o eval.o deck.o cards.o
	gcc -o test-c4deck test-c4deck.o eval.o deck.o cards.o

test-c4deck.o: test-c4deck.c
	gcc $(CFLAGS) -c test-c4deck.c

eval.o: eval.c eval.h
	gcc $(CFLAGS) -c eval.c

deck.o: deck.c deck.h
	gcc $(CFLAGS) -c deck.c

cards.o: cards.c cards.h
	gcc $(CFLAGS) -c cards.c

.PHONY:
clean:
	rm -f test-c4deck test-c4deck.o *.c~
