
CC = gcc

CPPFLAGS += -D _GNU_SOURCE
#CPPFLAGS += -D DEBUG

CFLAGS += -Wall -Werror
#CFLAGS += -g -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable

LDLIBS += -lm

main: main.o evaluate.o parser.o print.o scope.o builtins.o value.o avl.o

main.o: main.c argv0.h parser.h evaluate.h print.h value.h

builtins.o: builtins.c builtins.h argv0.h value.h evaluate.h scope.h

avl.o: avl.c avl.h

evaluate.o: evaluate.c evaluate.h parser.h value.h scope.h

scope.o: scope.c scope.h avl.h value.h argv0.h

print.o: print.c print.h value.h

parser.o: parser.c parser.h

value.o: value.c value.h argv0.h

parser.c parser.h: parser.zb
	zebu -m -t fileio -i parser.zb -o parser

ARGS += ./input.lisp

run: main
	./main $(ARGS)

valrun: main
	valgrind ./main $(ARGS)

valrun-leak: main
	valgrind --leak-check=full ./main $(ARGS)

clean:
	rm -vf main parser.c parser.h *.o
	
	
	
	
	
	
	
	
	
	
	
