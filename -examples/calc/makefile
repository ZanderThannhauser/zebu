
CC = gcc

CFLAGS += -Wall -Werror
CFLAGS += -g -Wno-unused-variable

LDLIBS += -lreadline -lm

main: main.o evaluate.o parser.o

main.o: main.c parser.h evaluate.h

evaluate.o: evaluate.c evaluate.h parser.h

parser.o: parser.c parser.h

parser.c parser.h: parser.zb
	zebu -l -t readline -i parser.zb -o parser

run: main
	./main
