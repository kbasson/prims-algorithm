prim: prim.o helpers.o
	clang -Wall -pedantic -std=c99 prim.o helpers.o -o prim

prim.o: prim.c prim.h
	clang -Wall -pedantic -std=c99 -c prim.c -o prim.o

helpers.o: helpers.c prim.h
	clang -Wall -pedantic -std=c99 -c helpers.c -o helpers.o

clean:
	rm *.o
