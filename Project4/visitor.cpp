
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
    cur = strdup(cs->id); //current class working on
    //fprintf(stderr, "currently working on %s\n", cur);
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

void TypeTreeVisitor::visitFalseExtendsOption(FalseExtendsOption *f) 
{
    tt->addSubtype(cur, strdup((char*)"Obj"));
}

void TypeTreeVisitor::visitTrueExtendsOption(TrueExtendsOption *t) 
{
    int f = tt->addSubtype(cur, t->id);
    //fprintf(stderr, "adding %s to %s resulted in:%d\n", cur, t->id, f);
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
    ret = strdup((char*)"Nothing");
}

void TypeTreeVisitor::visitTrueIdentOption(TrueIdentOption *t) 
{
    ret = t->id;
}



/***/
TypeCheckVisitor::TypeCheckVisitor()
{
    st = new SymbolTable(NULL);
    // Adding the built in 'variables'
    VariableSym *t = new VariableSym(strdup((char*)"true"), strdup((char*)"Boolean"));
    st->addVariable(strdup((char*)"true"), t);
    VariableSym *f = new VariableSym(strdup((char*)"false"), strdup((char*)"Boolean"));
    st->addVariable(strdup((char*)"false"), f);

    tt = new TypeTree();    
    errors = 0;

    inIf = false;
    ifCount = 0;

    inMethod = false;
    returnType = NULL;
    returned = false;

    inClass = false;
    className = NULL;
    supertype = NULL;
}
TypeCheckVisitor::TypeCheckVisitor(TypeTree *t)
{
    st = new SymbolTable(NULL);
    // Adding the built in 'variables'
    VariableSym *tr = new VariableSym(strdup((char*)"true"), strdup((char*)"Boolean"));
    st->addVariable(strdup((char*)"true"), tr);
    VariableSym *f = new VariableSym(strdup((char*)"false"), strdup((char*)"Boolean"));
    st->addVariable(strdup((char*)"false"), f);

    tt = t;
    errors = 0;

    inIf = false;
    ifCount = 0;

    inMethod = false;
    returnType = NULL;
    returned = false;
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
        VariableSym *v = new VariableSym(id->id, a->rexpr->type());
        //fprintf(stderr, "Adding variable '%s' with type '%s'\n", id->id, a->rexpr->type());
        st->addVariable(strdup(id->id), v);
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
        sprintf(msg, "%d: Syntax Error\n\tUse of uninitialized variable '%s'\n", i->lineno, i->id);
        msgs.push_back(msg);
    }
}

void TypeCheckVisitor::visitDotRExpr(DotRExpr *d)
{
    // visit first, collect args
    list<char*> args;
    d->rexpr->accept(this);
    for (list<RExpr *>::const_iterator it = d->args->begin(); it != d->args->end(); ++it)
    {
        (*it)->accept(this);
        args.push_back((*it)->type());
    }
    // now type check
    //IdentNode *id = dynamic_cast<IdentNode*>(a->lexpr);
    char *type;
    RExprToLExpr *rl = dynamic_cast<RExprToLExpr*>(d->rexpr);
    if (rl != NULL) //if it is an lexpr
    {
        IdentNode *id = dynamic_cast<IdentNode*>(rl->lexpr);
        if (id != NULL) //and the lexpr is an ident node
        {
            type = st->lookupVariable(id->id)->type;
        }
    }
    else 
    {
        type = d->rexpr->type();
    }
    MethodNode *m = tt->typeGetMethod(type, d->id);
    if (m == NULL)
    {
        errors++;
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tType '%s' has no method named '%s'\n", d->lineno, type, d->id);
        msgs.push_back(msg);
    } 
    else if (!m->argsMatch(args))  // TODO: It's ok to call the method using super/sub types?
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tArguments don't match on method call to '%s'\n", d->lineno, d->id);
        addError(msg);
    }
}

/* Cases currently ignoring
 * 1)
 * if - {
 *      x = 10
 *      x = 20
 * } else {
 *
 * }
 *
 * q = x
 *
 * 2)
 * if - {
 *      y = 2
 *      x = x + y //valid thing to do
 * }
 *
 * TODO: Resolve how to do this.
 * */
void TypeCheckVisitor::visitIfBlock(IfBlock *i)
{
    inIf = true;
    i->_if->accept(this);
    for (list<ElifClause *>::const_iterator it = i->_elifs->begin(); it != i->_elifs->end(); ++it)
    {
        (*it)->accept(this);
    }
    i->_else->accept(this);
    inIf = false;
    ifCount = 0;
    assignments.clear();
}

void TypeCheckVisitor::visitIfClause(IfClause *i)
{
    char *type;
    IdentNode *ident = isIdent(i->rexpr);
    if (ident != NULL)
        type = st->lookupVariable(ident->id)->type;    
    else
        type = i->rexpr->type();

    if (strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tIf condition must be of type 'Boolean'\n", i->lineno);
        addError(msg);
    }
}

void TypeCheckVisitor::visitElifClause(ElifClause *e)
{
    char *type;
    IdentNode *ident = isIdent(e->rexpr);
    if (ident != NULL)
        type = st->lookupVariable(ident->id)->type;    
    else
        type = e->rexpr->type();

    if (strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tElif condition must be of type 'Boolean'\n", e->lineno);
        addError(msg);
    }
}

void TypeCheckVisitor::visitWhileStatement(WhileStatement *w)
{
    char *type = w->rexpr->type();
    if (strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tWhile condition must be of type 'Boolean'\n", w->lineno);
        addError(msg);
    }
}

void TypeCheckVisitor::visitMethod(Method *m)
{
    inMethod = true;
    // check if it's inherited, and if it's doing it properly
    MethodNode *superMethod = tt->typeGetMethod(supertype, m->id);
    if (superMethod != NULL)
    {
        MethodNode *override = tt->typeGetMethod(className, m->id);
        if (superMethod->argsType.size() != override->argsType.size())
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tOverridden method '%s' does not have the correct number of arguments\n", m->lineno, m->id);
            addError(msg);
        }
        else //check that the args and return type are overridden correctly
        {
            list<char*>::const_iterator superArgs = superMethod->argsType.begin();                                           
            list<char*>::const_iterator overrideArgs = override->argsType.begin();                                              
            for (int i = 0; i < superMethod->argsType.size(); i++)                                                              
            {                                                                                                  
                if (strcmp((*superArgs), (*overrideArgs)) != 0)                                                    
                {
                    if (!tt->isSupertype((*overrideArgs),(*superArgs)))
                    {
                        char *msg = (char*) malloc(sizeof(char)*256);
                        sprintf(msg, "%d: Syntax Error\n\tMethod argument override at position %d is not the same type or supertype of overridden method\n", m->lineno, i+1);
                        addError(msg);
                    }
                }
                std::advance(superArgs, 1);
                std::advance(overrideArgs, 1);
            }
            //check return statement
            if (strcmp(superMethod->returnType, override->returnType) != 0)
            {
                if (!tt->isSubtype(override->returnType, superMethod->returnType))
                {
                    char *msg = (char*) malloc(sizeof(char)*256);
                    sprintf(msg, "%d: Syntax Error\n\tReturn value of override method is not the same type or subtype of overridden method\n", m->lineno);
                    addError(msg);
                }
            }
        }        
    }
    //
    for (list<FormalArg *>::const_iterator it = m->fargs->begin(); it != m->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    m->ident->accept(this);
    for (list<Statement *>::const_iterator it = m->stmts->begin(); it != m->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }

    if (!returned)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tMethod '%s' does not return value of type '%s'\n", m->lineno, m->id, returnType);
        addError(msg);
    }
    inMethod = false;
    returned = false;
}

void TypeCheckVisitor::visitTrueIdentOption(TrueIdentOption *t)
{
    if (inMethod)
        returnType = t->id;
}

void TypeCheckVisitor::visitFalseIdentOption(FalseIdentOption *f)
{
    if (inMethod)
    {
        returnType = strdup((char*)"Nothing");
        returned = true; // by default, assume the method returns nothing
    }
}

void TypeCheckVisitor::visitReturnStatement(ReturnStatement *r)
{
    if (!inMethod)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tReturn statement outside of method declaration\n", r->lineno);
        addError(msg);
        return; 
    }
    char *type;
    r->rexpr->accept(this);

    IdentNode *ident = isIdent(r->rexpr);
    if (ident != NULL)
    {
        type = st->lookupVariable(ident->id)->type;    
    } 
    else 
    {
        type = r->rexpr->type();
    }

    // TODO: If return type is subtype, it's ok
    if (strcmp(type, returnType) != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tMethod returns value of type '%s', should return '%s'\n", r->lineno, type, returnType);
        addError(msg);
    } 
    else 
    {
        returned = true;
    }
}

void TypeCheckVisitor::visitClass(Class *c) 
{
    inClass = true;
    className = c->getID();
    supertype = c->getExtends();
    c->clssig->accept(this);
    c->clsbdy->accept(this);
    inClass = false;
}


/*
{
}    
*/
void TypeCheckVisitor::addError(char *msg)
{
    errors++;
    msgs.push_back(msg);
}

IdentNode *TypeCheckVisitor::isIdent(RExpr *r)
{
    RExprToLExpr *rl = dynamic_cast<RExprToLExpr*>(r);
    if (rl != NULL) //if it is an lexpr
    {
        IdentNode *id = dynamic_cast<IdentNode*>(rl->lexpr);
        if (id != NULL) //and the lexpr is an ident node
        {
            return id; 
        }
    }
    return NULL;

}

/*
 *
 * 

OverrideMethodVisitor::OverrideMethodVisitor(TypeCheckVisitor *p, SymbolTable *s, TypeTree *t, char *super, char *sub) 
    : parent(p), st(s), tt(t), superclass(super), subclass(sub) {}


*/
