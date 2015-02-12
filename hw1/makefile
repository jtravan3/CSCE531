babycpp: lex.yy.o main.o dict.o
	gcc lex.yy.o main.o dict.o -o babycpp -lfl

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

main.o: main.c defs.h
	gcc -c main.c

dict.o: dict.c defs.h
	gcc -c dict.c

lex.yy.c: driver.lex defs.h
	flex driver.lex

clean:
	rm *.o babycpp lex.yy.c

comment:
	rm comments.txt
