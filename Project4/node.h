#ifndef NODE_H
#define NODE_H

#include <list>
#include <stdio.h>

class Visitor;

using std::list;

class Node 
{
    public:
        int lineno;
        Node(int l);
        Node() {lineno = 0;}
        void setLineno(int l);
};

class ClassSignature;
class ClassBody;

class Class : public Node 
{
    public:
        ClassSignature *clssig;
        ClassBody *clsbdy;
    public:
        Class(ClassSignature *cs, ClassBody *cb);
        virtual void print();
        virtual void accept(Visitor *v);
        char *getID();
        char *getExtends();
};

class FormalArgs;

class ExtendsOption : public Node //ABC
{
    public:
        virtual void print() = 0;
        virtual char *getID() = 0;
        virtual void accept(Visitor *v) = 0;
};

class FalseExtendsOption : public ExtendsOption
{
    public:
        FalseExtendsOption();
        virtual void print();
        virtual char *getID();
        virtual void accept(Visitor *v);
};


class TrueExtendsOption : public ExtendsOption
{
    public:
        char *id;
    public:
        TrueExtendsOption(char *i);
        virtual void print();
        virtual void accept(Visitor *v);
        virtual char *getID();
};

class FormalArg : public Node 
{
    public:
        char *id;
        char *type;
    public:
        FormalArg(char *i, char *t);
        virtual void print();
        virtual void accept(Visitor *v);
};

class ClassSignature : public Node 
{
    public:
        char *id;
        list<FormalArg *> *fargs;
        ExtendsOption *exop;
    public:
        ClassSignature(char *i, list<FormalArg *> *f, ExtendsOption *e);
        virtual void print();
        virtual void accept(Visitor *v);
        char *getID();
        char *getExtends();
};



class Statement;
class Method;
class ClassBody : public Node 
{
    public:
        list<Statement *> *stmts;
        list<Method *> *meths;
    public:
        ClassBody(list<Statement *> *s, list<Method *> *m);
        virtual void print();
        virtual void accept(Visitor *v);
};

class IdentOption : public Node //ABC 
{
    public:
        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;
};

class FalseIdentOption : public IdentOption
{
    public:
        FalseIdentOption();
        virtual void print();
        virtual void accept(Visitor *v);
};

class TrueIdentOption : public IdentOption
{
    public:
        char *id;
    public:
        TrueIdentOption(char *i);
        virtual void print();
        virtual void accept(Visitor *v);
};
class Method : public Node 
{
    public:
        char *id;
        list<FormalArg *> *fargs;
        IdentOption *ident;
        list<Statement *> *stmts;
    public:
        Method(char *, list<FormalArg *> *, IdentOption *, list<Statement *> *);
        virtual void print(); 
        virtual void accept(Visitor *v);
};



/*****************
 * RExpr classes *
 *****************/

class ActualArgs;
class LExpr;

class RExpr : public Node  //ABC
{
    public:
        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;
        virtual char *type(); // TODO: make pure virtual
};

class EmptyRExpr : public RExpr
{
    public:
        EmptyRExpr();
        virtual void print();
        virtual void accept(Visitor *v);
        virtual char *type();
};

class DotRExpr : public RExpr
{
    public:
        RExpr      *rexpr;
        char       *id;
        list<RExpr *> *args;
    public:
        DotRExpr(RExpr *r, char *i, list<RExpr *> *a);
        virtual void print();
        virtual void accept(Visitor *v);
};

class ConstructorRExpr : public RExpr
{
    public:
        char *id;
        list<RExpr *> *args;
    public:
        ConstructorRExpr(char *i, list<RExpr *> *a);
        virtual void print();
        virtual void accept(Visitor *v);
        virtual char *type();
};

class RExprToLExpr : public RExpr
{
    public:
        LExpr *lexpr;
    public:
        RExprToLExpr(LExpr *l);
        virtual void print();
        virtual void accept(Visitor *v);
};

class StringNode : public RExpr
{
    public:
        char *id;
    public:
        StringNode(char *i);
        virtual void print(); 
        virtual void accept(Visitor *v);
        virtual char *type();
};

class IntNode : public RExpr
{
    public:
        int value;
    public:
        IntNode(int i);
        virtual void print(); 
        virtual void accept(Visitor *v);
        virtual char *type();
};

class NotNode : public RExpr
{
    public:
        RExpr *value;
    public:
        NotNode(RExpr* v);
        void print();
        virtual void accept(Visitor *v);
        virtual char *type();
};



class BinaryOperatorNode : public RExpr
{
    public:
        RExpr *left;
        RExpr *right;
        int operation; //plus:0 minus:1 times:2 divide:3 equals:4 atmost:5 lessthan:6 atleast:7 greater:8 and:9 or:10
    public:
        BinaryOperatorNode(RExpr *l, RExpr *r, int o);
        virtual void accept(Visitor *v);
        virtual char *type();
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
        virtual char *type();
};

class AtMostNode : public BinaryOperatorNode
{
    public:
        AtMostNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class LessThanNode : public BinaryOperatorNode
{
    public:
        LessThanNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class AtLeastNode : public BinaryOperatorNode
{
    public:
        AtLeastNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class GreaterThanNode : public BinaryOperatorNode
{
    public:
        GreaterThanNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class AndNode : public BinaryOperatorNode
{
    public:
        AndNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class OrNode : public BinaryOperatorNode
{
    public:
        OrNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};
// END RExpr

/**********
 * Statement classes
 * ********/
class Statement : public Node //ABC 
{
    public:
        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;
};

class RExprStatement : public Statement 
{
    public:
        RExpr *rexpr;
    public:
        RExprStatement(RExpr* r);
        virtual void print(); 
        virtual void accept(Visitor *v);
};

class ReturnStatement : public Statement
{
    public:
        RExpr *rexpr;
    public:
        ReturnStatement(RExpr *r);
        virtual void print();
        virtual void accept(Visitor *v);
};

class AssignmentStatement : public Statement
{
    public:
        LExpr       *lexpr;
        IdentOption *ident;
        RExpr       *rexpr;
    public:
        AssignmentStatement(LExpr *l, IdentOption *i, RExpr *r);
        virtual void print();
        virtual void accept(Visitor *v);
};

class WhileStatement : public Statement 
{
    public:
        RExpr *rexpr;
        list<Statement *> *stmts;
    public:
        WhileStatement(RExpr *r, list<Statement *> *s);
        virtual void print();
        virtual void accept(Visitor *v);
}; 

class IfClause;
class ElifClause;
class ElseOption;

class IfBlock : public Statement 
{
    public:
        IfClause *_if;
        list<ElifClause *> *_elifs;
        ElseOption *_else;
    public:
        IfBlock(IfClause *i, list<ElifClause *> *ei, ElseOption *el);
        virtual void print();
        virtual void accept(Visitor *v);
};

class IfClause : public Node //Decided not to make this an ABC despite being production and rule
{
    public:
        RExpr *rexpr;
        list<Statement *> *stmts;
    public:
        IfClause(RExpr *r, list<Statement *> *stmts);
        virtual void print();
        virtual void accept(Visitor *v);
};

class ElifClause : public Node 
{
    public:
        RExpr *rexpr;
        list<Statement *> *stmts;
    public:
        ElifClause(RExpr *r, list<Statement *> *stmts);
        virtual void print();
        virtual void accept(Visitor *v);

};

class ElseOption : public Node //ABC
{
    public:
        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;
};

class FalseElseOption : public ElseOption
{
    public:
        FalseElseOption();
        virtual void print();
        virtual void accept(Visitor *v);
};

class TrueElseOption : public ElseOption
{
    public:
        list<Statement *> *stmts;
    public:
        TrueElseOption(list<Statement *> *s);
        virtual void print();
        virtual void accept(Visitor *v);
};


/***************
 * LExpr classes
 * *************/
class LExpr : public Node // ABC 
{
    public:
        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;
};

class IdentNode : public LExpr
{
    public:
        char *id;
    public:
        IdentNode(char *i);
        virtual void print();
        virtual void accept(Visitor *v);
};

class ObjectFieldLExpr : public LExpr
{
    public:
        RExpr *rexpr;
        char  *id;
    public:
        ObjectFieldLExpr(RExpr *r, char *i);
        virtual void print();
        virtual void accept(Visitor *v);
};

class RExprOption {};

class Program : public Node 
{
    public:
        list<Statement *> *statements;
        list<Class *>     *classes;
    public:
        Program(list<Class *> *c, list<Statement *> *s, int);
        bool checkClassHierarchy();
        virtual void accept(Visitor *v);
};

#endif
