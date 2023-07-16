
all: libsess4.a uselib

libsess4.a: sess4.c sess4.h
	gcc -c -Wall -Werror sess4.c -o sess4.o
	ar rcs libsess4.a sess4.o

uselib: uselib.c libsess4.a
	gcc -L$(PWD) uselib.c -o uselib libsess4.a

clean:
	rm libsess4.a uselib sess4.o
