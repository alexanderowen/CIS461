quack: quack.tab.o lex.yy.o node.o visitor.o
	g++ lex.yy.o quack.tab.o node.o -o quack -ll

#quack.o: quack.cpp
#	g++ -c quack.cpp
visitor.o: visitor.h visitor.cpp
	g++ -c visitor.cpp

node.o: node.cpp node.h
	g++ -c node.cpp

quack.tab.o: quack.y
	bison -d quack.y
	g++ -c quack.tab.c

lex.yy.o: quack.lex 
	flex quack.lex
	g++ -c lex.yy.c


clean:
	rm *.o
