#
#	makefile for the Simple Expression Evaluator
#
#

CC = gcc

CFLAGS = -g

LIBS = -lfl

YACC = bison

LEX = flex

SOURCE = parse.y parse.c main.c tree.c eval.c scan.l array.c tnarray.c lex.yy.c

OBJECTS = parse.o main.o tree.o eval.o array.o tnarray.o

see: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o see

y.tab.h parse.c: parse.y defs.h eval.h
	$(YACC) -d -y -t -v parse.y
	mv y.tab.c parse.c

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

lex.yy.c: scan.l y.tab.h defs.h eval.h
	$(LEX) scan.l

clean:
	-rm *.o parse.c y.output see y.tab.h
