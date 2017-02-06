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

class ActualArgs;
class LExpr;

class RExpr  //ABC
{
    public:
        virtual void print() = 0;
};

class DotRExpr : public RExpr
{
    protected:
        RExpr      *rexpr;
        char       *id;
        list<RExpr *> *args;
    public:
        DotRExpr(RExpr *r, char *i, list<RExpr *> *a);
        virtual void print();
};

class ConstructorRExpr : public RExpr
{
    protected:
        char *id;
        list<RExpr *> *args;
    public:
        ConstructorRExpr(char *i, list<RExpr *> *a);
        virtual void print();
};

class RExprToLExpr : public RExpr
{
    protected:
        LExpr *lexpr;
    public:
        RExprToLExpr(LExpr *l);
        virtual void print();
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

class NotNode : public RExpr
{
    protected:
        RExpr *value;
    public:
        NotNode(RExpr* v);
        void print();
};



class BinaryOperatorNode : public RExpr
{
    protected:
        RExpr *left;
        RExpr *right;
    public:
        BinaryOperatorNode(RExpr *l, RExpr *r);
};

class PlusNode : public BinaryOperatorNode
{
    public:
        PlusNode(RExpr *l, RExpr *r);
        virtual void print();
};

class MinusNode : public BinaryOperatorNode
{
    public:
        MinusNode(RExpr *l, RExpr *r);
        virtual void print();
};

class TimesNode : public BinaryOperatorNode
{
    public:
        TimesNode(RExpr *l, RExpr *r);
        virtual void print();
};

class DivideNode : public BinaryOperatorNode
{
    public:
        DivideNode(RExpr *l, RExpr *r);
        virtual void print();
};

class EqualsNode : public BinaryOperatorNode
{
    public:
        EqualsNode(RExpr *l, RExpr *r);
        virtual void print();
};

class AtMostNode : public BinaryOperatorNode
{
    public:
        AtMostNode(RExpr *l, RExpr *r);
        virtual void print();
};

class LessThanNode : public BinaryOperatorNode
{
    public:
        LessThanNode(RExpr *l, RExpr *r);
        virtual void print();
};

class AtLeastNode : public BinaryOperatorNode
{
    public:
        AtLeastNode(RExpr *l, RExpr *r);
        virtual void print();
};

class GreaterThanNode : public BinaryOperatorNode
{
    public:
        GreaterThanNode(RExpr *l, RExpr *r);
        virtual void print();
};

class AndNode : public BinaryOperatorNode
{
    public:
        AndNode(RExpr *l, RExpr *r);
        virtual void print();
};

class OrNode : public BinaryOperatorNode
{
    public:
        OrNode(RExpr *l, RExpr *r);
        virtual void print();
};
// END RExpr

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

/***************
 * LExpr classes
 * *************/
class LExpr // ABC 
{
    public:
        virtual void print() = 0;
};

class IdentNode : public LExpr
{
    protected:
        char *id;
    public:
        IdentNode(char *i);
        virtual void print();
};

class ObjectFieldLExpr : public LExpr
{
    protected:
        RExpr *rexpr;
        char  *id;
    public:
        ObjectFieldLExpr(RExpr *r, char *i);
        virtual void print();
};

class RExprOption {};
/*
class ExtraActualArgs; //forward decl.
class ActualArgs 
{
    protected:
        RExpr *rexpr;
        list<RExpr *> 
    public:
        ActualArgs(RExpr *r, ExtraActualArgs *a);
        ActualArgs();
        virtual void print();
};
*/

class Program 
{
    protected:
        list<Statement *> *statements;
        list<Class *>     *classes;
    public:
        Program(list<Class *> *c, list<Statement *> *s);
};

#endif