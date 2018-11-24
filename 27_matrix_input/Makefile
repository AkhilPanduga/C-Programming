CFLAGS=-Wall -Werror -pedantic -std=gnu99

rotate: rotateMatrix.o
	gcc -o rotate rotateMatrix.o

rotateMatrix.o: rotateMatrix.c
	gcc $(CFLAGS) -c rotateMatrix.c

.PHONY:
clean:
	rm -f rotate *.o *.c~ 
