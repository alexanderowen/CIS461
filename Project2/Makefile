parser: parser.tab.o lex.yy.o node.o
	g++ lex.yy.o parser.tab.o node.o -o parser -ll

#parser.o: parser.cpp
#	g++ -c parser.cpp

node.o: node.cpp node.h
	g++ -c node.cpp

parser.tab.o: parser.y
	bison -d parser.y
	g++ -c parser.tab.c

lex.yy.o: parser.lex 
	flex parser.lex
	g++ -c lex.yy.c


clean:
	rm *.o
