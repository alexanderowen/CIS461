
#include <list>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "visitor.h"
#include "node.h"
#include "util.h"

using std::list;

void Visitor::visitProgram(Program *p) 
{
    for (list<Class *>::const_iterator it = p->classes->begin(); it != p->classes->end(); ++it)
    {
        (*it)->accept(this);
    }
    for (list<Statement *>::const_iterator it = p->statements->begin(); it != p->statements->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitClass(Class *c) 
{
    c->clssig->accept(this);
    c->clsbdy->accept(this);
}

void Visitor::visitFalseExtendsOption(FalseExtendsOption *f) {}
void Visitor::visitTrueExtendsOption(TrueExtendsOption *t) {}
void Visitor::visitFormalArg(FormalArg *f) {}

void Visitor::visitClassSignature(ClassSignature *cs) 
{
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

void Visitor::visitClassBody(ClassBody *cb) 
{
    for (list<Statement *>::const_iterator it = cb->stmts->begin(); it != cb->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
    for (list<Method *>::const_iterator it = cb->meths->begin(); it != cb->meths->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitFalseIdentOption(FalseIdentOption *f) {}
void Visitor::visitTrueIdentOption(TrueIdentOption *t) {}

void Visitor::visitMethod(Method *m) 
{
    for (list<FormalArg *>::const_iterator it = m->fargs->begin(); it != m->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    m->ident->accept(this);
    for (list<Statement *>::const_iterator it = m->stmts->begin(); it != m->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitEmptyRExpr(EmptyRExpr *e) {}
void Visitor::visitDotRExpr(DotRExpr *d) 
{
    d->rexpr->accept(this);
    for (list<RExpr *>::const_iterator it = d->args->begin(); it != d->args->end(); ++it)
    {
        (*it)->accept(this);
    }
}    

void Visitor::visitConstructorRExpr(ConstructorRExpr *c) 
{
    for (list<RExpr *>::const_iterator it = c->args->begin(); it != c->args->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitRExprToLExpr(RExprToLExpr *rl) 
{
    rl->lexpr->accept(this);
}

void Visitor::visitStringNode(StringNode *s) {}
void Visitor::visitIntNode(IntNode *i) {}

void Visitor::visitNotNode(NotNode *n) 
{
    n->value->accept(this);
}

void Visitor::visitBinaryOperatorNode(BinaryOperatorNode *b) 
{
    b->left->accept(this);
    b->right->accept(this);
}

void Visitor::visitRExprStatement(RExprStatement *r) 
{
    r->rexpr->accept(this);
}

void Visitor::visitReturnStatement(ReturnStatement *r) 
{
    r->rexpr->accept(this);
}

void Visitor::visitAssignmentStatement(AssignmentStatement *a) 
{
    a->lexpr->accept(this);
    a->ident->accept(this);
    a->rexpr->accept(this);
}

void Visitor::visitWhileStatement(WhileStatement *w) 
{
    w->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = w->stmts->begin(); it != w->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitIfBlock(IfBlock *i) 
{
    i->_if->accept(this);
    for (list<ElifClause *>::const_iterator it = i->_elifs->begin(); it != i->_elifs->end(); ++it)
    {
        (*it)->accept(this);
    }
    i->_else->accept(this);
}

void Visitor::visitIfClause(IfClause *i) 
{
    i->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = i->stmts->begin(); it != i->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitElifClause(ElifClause *e) 
{
    e->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitFalseElseOption(FalseElseOption *e) {}
void Visitor::visitTrueElseOption(TrueElseOption *e) 
{
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitIdentNode(IdentNode *i) {}

void Visitor::visitObjectFieldLExpr(ObjectFieldLExpr *o) 
{
    o->rexpr->accept(this);
}



ConstructorVisitor::ConstructorVisitor() {}
ConstructorVisitor::~ConstructorVisitor() {}
void ConstructorVisitor::visitConstructorRExpr(ConstructorRExpr *c)
{
    if (!withinList(&constructors, c->id))
        constructors.push_back(c->id);
    for (list<RExpr *>::const_iterator it = c->args->begin(); it != c->args->end(); ++it)
    {
        (*it)->accept(this);
    }
}
void ConstructorVisitor::visitClassSignature(ClassSignature *cs)
{
    classes.push_back(cs->id);
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

bool ConstructorVisitor::checkStructure()
{
    for (list<char *>::const_iterator it = constructors.begin(); it != constructors.end(); ++it)
    {
        if (!withinList(&classes, (*it)))
            return false;
    }
    return true;
}
void ConstructorVisitor::print()
{
    std::cout << "Constructors: "; 
    std::copy(std::begin(constructors), std::end(constructors), std::ostream_iterator<char *>(std::cout, " "));
    std::cout << "\n" << std::endl;
    std::cout << "Classes: ";
    std::copy(std::begin(classes), std::end(classes), std::ostream_iterator<char *>(std::cout, " "));
    std::cout << "\n" << std::endl;
}
