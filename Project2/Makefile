parser: parser.o lex.yy.o parser.tab.o
	gcc parser.o lex.yy.o parser.tab.o -o parser

lex.yy.o: lex.yy.c
parser.tab.o: parser.tab.c
parser.o: parser.c

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: parser.lex parser.tab.h
	flex parser.lex

clean:
	rm *.o
