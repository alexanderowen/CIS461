#ifndef NODE_H
#define NODE_H

#include <list>
#include <stdio.h>

using std::list;

class Class //ABC
{
    public:
        Class() {} //TODO: Remove this. Make this an ABC
};

class ClassSignature {};

class ExtendsOption {};

class FormalArgs {};

class FormalArg {};

class ExtraFormalArgsStar {};

class ClassBody {};

class Method {};

class IdentOption {};

class StatementBlock {};

/*****************
 * RExpr classes *
 *****************/
class RExpr  //ABC
{
    public:
        virtual void print() = 0;
};

class StringNode : public RExpr
{
    protected:
        char *id;
    public:
        StringNode(char *i);
        virtual void print(); 
};

class IntNode : public RExpr
{
    protected:
        int value;
    public:
        IntNode(int i);
        virtual void print(); 
};

class Statement //ABC 
{
    public:
        virtual void print() = 0;
};

class RExprStatement : public Statement 
{
    protected:
        RExpr* r;
    public:
        RExprStatement(RExpr* R);
        virtual void print(); 
};

class IfBlock {};

class IfStatement {};

class ElifStatement {};

class ElifStatementOption {};

class WhileStatement {};

class LExpr {};



class RExprOption {};

class ActualArgs {};

class ExtraActualArgs {};

class Program 
{
    protected:
        list<Statement *> *statements;
        list<Class *>     *classes;
    public:
        Program(list<Class *> *c, list<Statement *> *s);
};

#endif
