
#include <list>
#include <stdio.h>
#include <stdlib.h>
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



ConstructorVisitor::ConstructorVisitor() 
{
    classes.push_back((char *)"Obj");
    classes.push_back((char *)"Int");
    classes.push_back((char *)"String");
    classes.push_back((char *)"Nothing");
}

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
/***/

TypeTreeVisitor::TypeTreeVisitor()
{
    tt = new TypeTree();
    cur = NULL;
    ret = NULL;
    args = NULL;
}

//TODO: CURRENT ASSUMPTION IS THAT CLASS INHERITANCE WON'T BE OUT OF ORDER
//TODO: THIS IS NOT TRUE IN QUACK
void TypeTreeVisitor::visitProgram(Program *p) 
{
    for (list<Class *>::const_iterator it = p->classes->begin(); it != p->classes->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeTreeVisitor::visitClassSignature(ClassSignature *cs) 
{
    cur = cs->id; //current class working on
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

void TypeTreeVisitor::visitFalseExtendsOption(FalseExtendsOption *f) 
{
    tt->addSubtype(cur, (char*)"Obj");
}

void TypeTreeVisitor::visitTrueExtendsOption(TrueExtendsOption *t) 
{
    tt->addSubtype(cur, t->id);
}


void TypeTreeVisitor::visitMethod(Method *m)
{
    args = new list<char*>; // TODO: Delete old one? Maybe not. Still exists in MethodNode
    for (list<FormalArg *>::const_iterator it = m->fargs->begin(); it != m->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }

    m->ident->accept(this);
    MethodNode *meth = new MethodNode(m->id, *args, ret);
    tt->addMethodToType(cur, meth);
    /*
    for (list<Statement *>::const_iterator it = m->stmts->begin(); it != m->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
    */
    
}

void TypeTreeVisitor::visitFormalArg(FormalArg *f) 
{
    args->push_back(f->type);
}

void TypeTreeVisitor::visitFalseIdentOption(FalseIdentOption *f) 
{
    ret = (char*)"Nothing";
}

void TypeTreeVisitor::visitTrueIdentOption(TrueIdentOption *t) 
{
    ret = t->id;
}



/***/
TypeCheckVisitor::TypeCheckVisitor()
{
    st = new SymbolTable(NULL);
    tt = new TypeTree();    
    errors = 0;
}
TypeCheckVisitor::~TypeCheckVisitor() 
{
    delete st;
    delete tt;
}

// Has the type checker met the max number of errors?
bool TypeCheckVisitor::check()
{
    return (errors > 10) ? true : false;
}

void TypeCheckVisitor::visitBinaryOperatorNode(BinaryOperatorNode *b)
{
    if (check())
        return;
    b->left->accept(this);
    b->right->accept(this);
    char *t1 = b->left->type();
    char *t2 = b->right->type();
    printf("Type1: %s Type2: %s\n", t1, t2);
    //TODO: Check if t1 has binary operator method
    //TODO: COME TO THIS LATER, DONT WANT TO FACE IT RIGHT NOW
    switch(b->operation) {
        case 0:
            printf("Plus");
            break;
        case 1:
            printf("Minus");
            break;
        default:
            printf("Other");
            break;
    }
}
   
void TypeCheckVisitor::visitAssignmentStatement(AssignmentStatement *a)
{
    //TODO: If the variable is already defined, do least common ancestor
    IdentNode *id = dynamic_cast<IdentNode*>(a->lexpr);
    if (id != NULL)
    {
        //TODO: Use a->ident, just ignoring it currently
        VariableSym v(id->id, a->rexpr->type());
        st->addVariable(id->id, &v);
    }
    a->lexpr->accept(this);
    a->ident->accept(this);
    a->rexpr->accept(this);
}

void TypeCheckVisitor::visitIdentNode(IdentNode *i) 
{
    if (st->lookupVariable(i->id) == NULL) 
    {
        errors++;
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tUse of uninitialized variable\n", i->lineno);
        msgs.push_back(msg);
    }
}
