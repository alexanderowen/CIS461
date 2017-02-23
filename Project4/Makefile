quack: quack.tab.o lex.yy.o node.o visitor.o util.o SymbolTable.o type.o
	g++ lex.yy.o quack.tab.o node.o visitor.o util.o SymbolTable.o type.o -o quack -ll

type.o: type.h type.cpp
	g++ -std=c++11 -c type.cpp

SymbolTable.o: SymbolTable.h SymbolTable.cpp
	g++ -std=c++11 -c SymbolTable.cpp

util.o: util.h util.cpp
	g++ -c util.cpp -I.

visitor.o: visitor.h visitor.cpp
	g++ -c -g visitor.cpp -I.

node.o: node.cpp node.h
	g++ -c -g node.cpp -I.

quack.tab.o: quack.y
	bison -d quack.y
	g++ -c -g quack.tab.c

lex.yy.o: quack.lex 
	flex quack.lex
	g++ -c -g lex.yy.c


clean:
	rm *.o
