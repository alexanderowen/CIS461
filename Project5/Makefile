quack: quack.tab.o lex.yy.o node.o visitor.o util.o SymbolTable.o type.o driver.o TranslatorVisitor.o
	g++ driver.o lex.yy.o quack.tab.o node.o visitor.o util.o SymbolTable.o type.o TranslatorVisitor.o -o quack -ll

TranslatorVisitor.o: TranslatorVisitor.hpp TranslatorVisitor.cpp
	g++ -c -std=c++11 TranslatorVisitor.cpp

driver.o: driver.cpp
	g++ -c -std=c++11 driver.cpp

type.o: type.hpp type.cpp
	g++ -std=c++11 -c -g type.cpp

SymbolTable.o: SymbolTable.h SymbolTable.cpp
	g++ -std=c++11 -c -g SymbolTable.cpp

util.o: util.h util.cpp
	g++ -std=c++11 -c util.cpp -I.

visitor.o: visitor.h visitor.cpp
	g++ -std=c++11 -c -g visitor.cpp -I.

node.o: node.cpp node.hpp
	g++ -std=c++11 -c -g node.cpp -I.

quack.tab.o: quack.y
	bison -d quack.y
	g++ -std=c++11 -c -g quack.tab.c

lex.yy.o: quack.lex 
	flex quack.lex
	g++ -c -g lex.yy.c


clean:
	rm *.o
