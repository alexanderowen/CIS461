#ifndef NODE_H
#define NODE_H

#include <list>
#include <stdio.h>

using std::list;

class ClassSignature;
class ClassBody;

class Class 
{
    protected:
        ClassSignature *clssig;
        ClassBody *clsbdy;
    public:
        Class(ClassSignature *cs, ClassBody *cb);
        virtual void print();
        char *getID();
        char *getExtends();
};

class FormalArgs;

class ExtendsOption //ABC
{
    public:
        virtual void print() = 0;
        virtual char *getID() = 0;
};

class FalseExtendsOption : public ExtendsOption
{
    public:
        FalseExtendsOption();
        virtual void print();
        virtual char *getID();
};


class TrueExtendsOption : public ExtendsOption
{
    protected:
        char *id;
    public:
        TrueExtendsOption(char *i);
        virtual void print();
        virtual char *getID();
};

class FormalArg 
{
    protected:
        char *id;
        char *type;
    public:
        FormalArg(char *i, char *t);
        virtual void print();
};

class ClassSignature 
{
    protected:
        char *id;
        list<FormalArg *> *fargs;
        ExtendsOption *exop;
    public:
        ClassSignature(char *i, list<FormalArg *> *f, ExtendsOption *e);
        virtual void print();
        char *getID();
        char *getExtends();
};



class Statement;
class Method;
class ClassBody 
{
    protected:
        list<Statement *> *stmts;
        list<Method *> *meths;
    public:
        ClassBody(list<Statement *> *s, list<Method *> *m);
        virtual void print();
};

class IdentOption //ABC 
{
    public:
        virtual void print() = 0;
};

class FalseIdentOption : public IdentOption
{
    public:
        FalseIdentOption();
        virtual void print();
};

class TrueIdentOption : public IdentOption
{
    protected:
        char *id;
    public:
        TrueIdentOption(char *i);
        virtual void print();
};
class Method 
{
    protected:
        char *id;
        list<FormalArg *> *fargs;
        IdentOption *ident;
        list<Statement *> *stmts;
    public:
        Method(char *, list<FormalArg *> *, IdentOption *, list<Statement *> *);
        virtual void print(); 
};



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

class EmptyRExpr : public RExpr
{
    public:
        EmptyRExpr();
        virtual void print();
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

/**********
 * Statement classes
 * ********/
class Statement //ABC 
{
    public:
        virtual void print() = 0;
};

class RExprStatement : public Statement 
{
    protected:
        RExpr *rexpr;
    public:
        RExprStatement(RExpr* r);
        virtual void print(); 
};

class ReturnStatement : public Statement
{
    protected:
        RExpr *rexpr;
    public:
        ReturnStatement(RExpr *r);
        virtual void print();
};

class AssignmentStatement : public Statement
{
    protected:
        LExpr       *lexpr;
        IdentOption *ident;
        RExpr       *rexpr;
    public:
        AssignmentStatement(LExpr *l, IdentOption *i, RExpr *r);
        virtual void print();
};

class WhileStatement : public Statement 
{
    protected:
        RExpr *rexpr;
        list<Statement *> *stmts;
    public:
        WhileStatement(RExpr *r, list<Statement *> *s);
        virtual void print();
}; 

class IfClause;
class ElifClause;
class ElseOption;

class IfBlock : public Statement 
{
    protected:
        IfClause *_if;
        list<ElifClause *> *_elifs;
        ElseOption *_else;
    public:
        IfBlock(IfClause *i, list<ElifClause *> *ei, ElseOption *el);
        virtual void print();
};

class IfClause //Decided not to make this an ABC despite being production and rule
{
    protected:
        RExpr *rexpr;
        list<Statement *> *stmts;
    public:
        IfClause(RExpr *r, list<Statement *> *stmts);
        virtual void print();
};

class ElifClause
{
    protected:
        RExpr *rexpr;
        list<Statement *> *stmts;
    public:
        ElifClause(RExpr *r, list<Statement *> *stmts);
        virtual void print();

};

class ElseOption //ABC
{
    public:
        virtual void print() = 0;
};

class FalseElseOption : public ElseOption
{
    public:
        FalseElseOption();
        virtual void print();
};

class TrueElseOption : public ElseOption
{
    protected:
        list<Statement *> *stmts;
    public:
        TrueElseOption(list<Statement *> *s);
        virtual void print();
};


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

class Program 
{
    protected:
        list<Statement *> *statements;
        list<Class *>     *classes;
    public:
        Program(list<Class *> *c, list<Statement *> *s);
        bool checkClassHierarchy();
};

#endif
