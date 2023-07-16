LIBS = -L/usr/local/lib

all: gdb strace ltrace

gdb: gdb.c
	gcc -zlazy -g gdb.c -o trygdb

strace: strace.c
	gcc -zlazy -g strace.c -o trystrace

ltrace: ltrace.c
	gcc -zlazy -g ltrace.c -o tryltrace

clean:
	rm trygdb trystrace tryltrace
