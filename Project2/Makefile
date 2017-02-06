parser: parser.o lex.yy.o parser.tab.o node.o
	g++ parser.o lex.yy.o parser.tab.o node.o -o parser

node.o: node.cpp node.h
	g++ -c node.cpp

lex.yy.o: parser.lex 
	flex parser.lex
	g++ -c lex.yy.c

parser.tab.o: parser.y
	bison -d parser.y
	g++ -c parser.tab.c

parser.o: parser.c
	g++ -c parser.c

clean:
	rm *.o
