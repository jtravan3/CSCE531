babycpp : lex.yy.c my_dict.c
	gcc lex.yy.c my_dict.c -o babycpp -lfl

lex.yy.c : define.lex
	flex define.lex

clean :
	rm babycpp lex.yy.c
