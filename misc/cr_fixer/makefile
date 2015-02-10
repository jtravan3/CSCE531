fixer: lex.yy.o
	gcc lex.yy.o -o fixer -lfl

lex.yy.o: lex.yy.c
	gcc lex.yy.c -c -lfl

lex.yy.c: 
	flex cr.lex

clean:
	rm lex.yy.c lex.yy.o fixer

