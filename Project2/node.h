#ifndef NODE_H
#define NODE_H

#include <list>
#include <stdio.h>

class Class {};

class ClassSignature {};

class ExtendsOption {};

class FormalArgs {};

class FormalArg {};

class ExtraFormalArgsStar {};

class ClassBody {};

class Method {};

class IdentOption {};

class StatementBlock {};

class Statement //ABC 
{
    public:
        void print() = 0;
};

class RExprStatement : public Statement 
{
    protected:
        RExpr* r;
    public:
        RExprStatement(RExpr* R);
        void print(); 
};

class IfBlock {};

class IfStatement {};

class ElifStatement {};

class ElifStatementOption {};

class WhileStatement {};

class LExpr {};


/*****************
 * RExpr classes *
 *****************/
class RExpr  //ABC
{
    public:
        void print() = 0;
};

class StringNode : RExpr
{
    protected:
        char *id;
    public:
        StringNode(char *i);
        void print(); 
};

class IntNode : RExpr
{
    protected:
        int value;
    public:
        IntNode(int i);
        void print(); 
};

class RExprOption {};

class ActualArgs {};

class ExtraActualArgs {};

class Program 
{
    protected:
        list<Statement *> statements;
        list<Class *>     classes;
    public:
        Program(list<Statement *> s, list<Class *> c);
};

#endif
