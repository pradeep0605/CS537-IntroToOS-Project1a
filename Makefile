varsort: varsort.o
	gcc -O -Wall -o varsort varsort.c

clean:
	rm varsort

debug:
	gcc -O -g -Wall -o varsort varsort.c
