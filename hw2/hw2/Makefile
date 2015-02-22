#
#	makefile for the Simple Expression Evaluator
#
#

CC = gcc

CFLAGS = -g

LIBS = -lfl

YACC = bison

LEX = flex

SOURCE = parse.y main.c

OBJECTS = parse.o main.o

see: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o see

y.tab.h parse.c: parse.y
	$(YACC) -y -t -v parse.y
	mv y.tab.c parse.c

clean:
	-rm *.o parse.c y.output see
