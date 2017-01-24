parser: lex.yy.c parser.tab.c parser.tab.h
	gcc parser.tab.c lex.yy.c -ll -o parser

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: parser.lex parser.tab.h
	flex parser.lex

