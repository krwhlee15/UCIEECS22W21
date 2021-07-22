#Makefile: PhotoLab_v2

all: PhotoLab_v2

PhotoLab_v2: FileIO.o DIPs.o Advanced.o PhotoLab_v2.o
	gcc -g -Wall -ansi -std=c99 -lm FileIO.o DIPs.o Advanced.o PhotoLab_v2.o -o PhotoLab_v2

PhotoLabTest: FileIO.o DIPs.o Advanced.o PhotoLabTest.o
	gcc -g -Wall -ansi -std=c99 -lm FileIO.o DIPs.o Advanced.o PhotoLabTest.o -o PhotoLabTest

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -std=c99 -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -ansi -std=c99 -c DIPs.c -o DIPs.o

PhotoLab_v2.o: PhotoLab_v2.c Constants.h
	gcc -Wall -ansi -std=c99 -c PhotoLab_v2.c -o PhotoLab_v2.o

PhotoLabTest.o: PhotoLab_v2.c Constants.h
	gcc -DDEBUG -Wall -ansi -std=c99 -c PhotoLab_v2.c -o PhotoLabTest.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -Wall -ansi -std=c99 -c Advanced.c -o Advanced.o

clean:
	rm -f *.o
	rm -f PhotoLab_v2
	rm -f PhotoLabTest
