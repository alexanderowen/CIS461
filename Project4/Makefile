quack: quack.tab.o lex.yy.o node.o visitor.o util.o
	g++ lex.yy.o quack.tab.o node.o visitor.o util.o -o quack -ll

util.o: util.h util.cpp
	g++ -c util.cpp -I.

visitor.o: visitor.h visitor.cpp
	g++ -c visitor.cpp -I.

node.o: node.cpp node.h
	g++ -c node.cpp -I.

quack.tab.o: quack.y
	bison -d quack.y
	g++ -c quack.tab.c

lex.yy.o: quack.lex 
	flex quack.lex
	g++ -c lex.yy.c


clean:
	rm *.o
