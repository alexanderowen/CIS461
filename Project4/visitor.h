#ifndef VISITOR_H 
#define VISITOR_H

#include <list>
#include <stdio.h>
#include "node.h"
#include "SymbolTable.h"
#include "type.h"

using std::list;

class Visitor
{
    public:
    virtual void visitProgram(Program *p);
    virtual void visitClass(Class *c);
    virtual void visitFalseExtendsOption(FalseExtendsOption *f);
    virtual void visitTrueExtendsOption(TrueExtendsOption *t);
    virtual void visitFormalArg(FormalArg *f);
    virtual void visitClassSignature(ClassSignature *cs);
    virtual void visitClassBody(ClassBody *cb);
    virtual void visitFalseIdentOption(FalseIdentOption *f);
    virtual void visitTrueIdentOption(TrueIdentOption *t);
    virtual void visitMethod(Method *m);
    virtual void visitEmptyRExpr(EmptyRExpr *e);
    virtual void visitDotRExpr(DotRExpr *d);    
    virtual void visitConstructorRExpr(ConstructorRExpr *c);
    virtual void visitRExprToLExpr(RExprToLExpr *rl);
    virtual void visitStringNode(StringNode *s);
    virtual void visitIntNode(IntNode *i);
    virtual void visitNotNode(NotNode *n);
    virtual void visitBinaryOperatorNode(BinaryOperatorNode *b);
    virtual void visitRExprStatement(RExprStatement *r);
    virtual void visitReturnStatement(ReturnStatement *r);
    virtual void visitAssignmentStatement(AssignmentStatement *a);
    virtual void visitWhileStatement(WhileStatement *w);
    virtual void visitIfBlock(IfBlock *i);
    virtual void visitIfClause(IfClause *i);
    virtual void visitElifClause(ElifClause *e);
    virtual void visitFalseElseOption(FalseElseOption *e);
    virtual void visitTrueElseOption(TrueElseOption *e);
    virtual void visitIdentNode(IdentNode *i);
    virtual void visitObjectFieldLExpr(ObjectFieldLExpr *o);
};

class ConstructorVisitor : public Visitor
{
    private:
        list<char *> constructors;
        list<char *> classes;
    public:
        ConstructorVisitor();
        ~ConstructorVisitor();
        virtual void visitConstructorRExpr(ConstructorRExpr *c);
        virtual void visitClassSignature(ClassSignature *cs);
        bool checkStructure();
        void print();
};

class TypeCheckVisitor : public Visitor
{
    public: //TODO: Change to private
        typedef Visitor super;
        SymbolTable *st;
        TypeTree *tt;

    public:
        int errors;
        list<char*> msgs;

        TypeCheckVisitor();
        ~TypeCheckVisitor();
    
        bool check(); 
        virtual void visitBinaryOperatorNode(BinaryOperatorNode *b);
        virtual void visitAssignmentStatement(AssignmentStatement *a);
        virtual void visitIdentNode(IdentNode *i);

};

#endif
