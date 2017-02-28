
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

    inMethod = false;
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
    inMethod = true;
    args = new list<char*>;
    for (list<FormalArg *>::const_iterator it = m->fargs->begin(); it != m->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }

    m->ident->accept(this);
    MethodNode *meth = new MethodNode(m->id, *args, ret);
    tt->addMethodToType(cur, meth);
    inMethod = false;
    /*
    for (list<Statement *>::const_iterator it = m->stmts->begin(); it != m->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
    */
    
}

void TypeTreeVisitor::visitFormalArg(FormalArg *f) 
{
    //fprintf(stderr, "Formal arg id: %s", f->id);
    //fprintf(stderr, "and type: %s", f->type);
    if (inMethod)
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

    inMethod = false;
    inMethodReturnCheck = false;
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


    inMethod = false;
    inMethodReturnCheck = false;
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
    //fprintf(stderr, "Inside Binary op\n");
    if (check())
        return;
    b->left->accept(this);
    b->right->accept(this);
    char *t1 = getType(b->left);
    char *t2 = getType(b->right);
    if (t1 == NULL || t2 == NULL)
    {
        //fprintf(stderr, "Compiler error. At line %d. One of the binary operator types is null\n", b->lineno);
        /*
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tType error. Undefined types.\n", b->lineno);
        addError(msg);
        */
        return;
    }
    if (strcmp(t1, (char*)"-") == 0 || strcmp(t2, (char*)"-") == 0)
    {
        fprintf(stderr, "Compiler error. I don't know the types of this binary operator\n");
    }

    if (strcmp(t1, t2) != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tBinary opeartor type mismatch: '%s' and '%s'\n", b->lineno, t1, t2);
        addError(msg);
    }

    char *op;

    //plus:0 minus:1 times:2 divide:3 equals:4 atmost:5 lessthan:6 atleast:7 greater:8 and:9 or:10
    switch(b->operation) {
        case 0:
            op = (char*)"PLUS";
            break;
        case 1:
            op = (char*)"MINUS";
            break;
        case 2:
            op = (char*)"TIMES";
            break;
        case 3:
            op = (char*)"DIVIDE";
            break;
        case 4:
            op = (char*)"EQUALS";
            break;
        case 5:
            op = (char*)"ATMOST";
            break;
        case 6:
            op = (char*)"LESS";
            break;
        case 7:
            op = (char*)"ATLEAST";
            break;
        case 8:
            op = (char*)"MORE";
            break;
        case 9:
            op = (char*)"AND";
            break;
        case 10:
            op = (char*)"OR";
            break;
        default:
            break;
    }
    MethodNode *method = tt->typeGetMethod(t1, op);
    if (method == NULL)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tType '%s' has no operator named '%s'\n", b->lineno, t1, op);
        addError(msg);
    } 
}
   
void TypeCheckVisitor::visitAssignmentStatement(AssignmentStatement *a)
{
    char *type;
    IdentNode *id = dynamic_cast<IdentNode*>(a->lexpr);
    if (id != NULL)
    {
        VariableSym *defined = st->lookupVariable(id->id);
        TrueIdentOption *tio = dynamic_cast<TrueIdentOption*>(a->ident);
        if (tio != NULL && defined != NULL)
        {
            type = tt->LCA(tio->id, getType(a->rexpr));
            type = tt->LCA(defined->type, type);
        }
        else if (defined != NULL) // If this variable has already been defined, perform LCA
        {
            type = tt->LCA(defined->type, getType(a->rexpr));    
        }
        else if (tio != NULL)
        {
            type = tt->LCA(tio->id, getType(a->rexpr));
        }
        else 
        {
            type = getType(a->rexpr);
        }
        if (type == NULL)
            return;
        VariableSym *v = new VariableSym(id->id, strdup(type));
        //fprintf(stderr, "Adding variable '%s' with type '%s'\n", id->id, getType(a->rexpr));
        st->addVariable(strdup(id->id), v);
    }
    ObjectFieldLExpr *ofl = dynamic_cast<ObjectFieldLExpr*>(a->lexpr);
    if (ofl != NULL) //TODO: Handle the ident, LCA thing
    {
        IdentNode *ident = isIdent(ofl->rexpr);
        if (ident != NULL)
        {
            if (strcmp(ident->id, (char*)"this") == 0)
            {
                //fprintf(stderr, "Adding variable node. Adding '%s' of type '%s' to type '%s'\n", ofl->id, getType(a->rexpr), className);
                VariableNode *v = new VariableNode(strdup(ofl->id), strdup(getType(a->rexpr)));
                tt->addVarToType(strdup(className), v);
            }
        } 
    }
    a->lexpr->accept(this);
    a->ident->accept(this);
    a->rexpr->accept(this);
}

void TypeCheckVisitor::visitIdentNode(IdentNode *i) 
{
    if (strcmp(i->id, (char*)"this") == 0) {
        return;
    }
    /*
    else if (st->lookupVariable(i->id) == NULL) 
    {
        errors++;
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tUse of uninitialized variable '%s'\n", i->lineno, i->id);
        msgs.push_back(msg);
    }
    */
}

void TypeCheckVisitor::visitDotRExpr(DotRExpr *d)
{
    // visit first, collect args
    list<char*> args;
    d->rexpr->accept(this);
    for (list<RExpr *>::const_iterator it = d->args->begin(); it != d->args->end(); ++it)
    {
        (*it)->accept(this);
        IdentNode *ident = isIdent((*it)); // TODO: If we are in a class, then 'this.x'(objectfieldlexpr) is ok if it exists
        if (ident != NULL) 
        {
            args.push_back(st->lookupVariable(ident->id)->type);
        }
        else 
        {
            args.push_back((*it)->type());
        }
    }
    // now type check
    char *type;
    /*
    RExprToLExpr *rl = dynamic_cast<RExprToLExpr*>(d->rexpr);
    if (rl != NULL) //if it is an lexpr
    {
        IdentNode *id = dynamic_cast<IdentNode*>(rl->lexpr);
        if (id != NULL) //and the lexpr is an ident node //TODO: If we are in a class, then 'this.x' is ok if it exists and is a class
        {
            //fprintf(stderr, "Setting up using lookupVar\n");
            type = st->lookupVariable(id->id)->type;
            fprintf(stderr, "Found type %s\n", type);
        }
    }
    else 
    {
        //type = d->rexpr->type();
        fprintf(stderr, "Setting up using getType\n");
        type = getType(d->rexpr);
    }
    */
    type = getType(d->rexpr);
    fprintf(stderr, "searching for method '%s' of type '%s'\n", d->id, type);
    MethodNode *m = tt->typeGetMethod(type, d->id);
    if (m == NULL)
    {
        errors++;
        char *msg = (char*) malloc(sizeof(char)*256);
        //fprintf(stderr, "This type? : %s\n", type);
        sprintf(msg, "%d: Syntax Error\n\tType '%s' has no method named '%s'\n", d->lineno, type, d->id);
        //fprintf(stderr, "Error message: %s\n", msg);
        msgs.push_back(msg);
    } 
    else  
    { 
        if (m->argsType.size() != args.size())
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tInvalid call to method '%s'; not enough arguments supplied\n", d->lineno, d->id);
            addError(msg);
            return;
        }

        list<char*>::const_iterator methodArgs = m->argsType.begin();
        list<char*>::const_iterator arg = args.begin(); 
        for (int i = 0; i < m->argsType.size(); i++)
        {
            if (strcmp((*methodArgs), (*arg)) != 0)
            {
                if (!tt->isSubtype((*arg),(*methodArgs)))
                {
                    char *msg = (char*) malloc(sizeof(char)*256);
                    sprintf(msg, "%d: Syntax Error\n\tMethod call argument at position %d is not the same type or a subtype of required argument\n", d->lineno, i+1);
                    addError(msg);
                }
            }
            std::advance(methodArgs, 1);
            std::advance(arg, 1);
        }
    }
}

void TypeCheckVisitor::visitIfBlock(IfBlock *i)
{
    //fprintf(stderr, "Inside the if block\n");
    list<SymbolTable*> sts;
    SymbolTable *origin = st;
    st = new SymbolTable(origin);
    sts.push_back(st);

    i->_if->accept(this);
    for (list<ElifClause *>::const_iterator it = i->_elifs->begin(); it != i->_elifs->end(); ++it)
    {
        st = new SymbolTable(origin);
        sts.push_back(st);
        (*it)->accept(this);
    }

    st = new SymbolTable(origin);
    sts.push_back(st);
    i->_else->accept(this);

    //fprintf(stderr, "Calling intersection\n");
    st = sts.front()->intersection(sts, tt);
}

void TypeCheckVisitor::visitIfClause(IfClause *i)
{
    char *type;
    /*
    IdentNode *ident = isIdent(i->rexpr);
    if (ident != NULL)
        type = st->lookupVariable(ident->id)->type;    
    else
        type = i->rexpr->type();
    */
    type = getType(i->rexpr);

    if (strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tIf condition must be of type 'Boolean'\n", i->lineno);
        addError(msg);
    }
    i->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = i->stmts->begin(); it != i->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitElifClause(ElifClause *e)
{
    char *type;
    /*
    IdentNode *ident = isIdent(e->rexpr);
    if (ident != NULL)
        type = st->lookupVariable(ident->id)->type;    
    else
        type = e->rexpr->type();
    */
    type = getType(e->rexpr);

    if (strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tElif condition must be of type 'Boolean'\n", e->lineno);
        addError(msg);
    }
    e->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitTrueElseOption(TrueElseOption *e)
{
    //fprintf(stderr, "Inside the else option\n");
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        //fprintf(stderr, "Visiting a statement inside else\n");
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitWhileStatement(WhileStatement *w)
{
    char *type = getType(w->rexpr);
    if (type != NULL && strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tWhile condition must be of type 'Boolean'\n", w->lineno);
        addError(msg);
    }
    SymbolTable *origin = st;
    st = new SymbolTable(origin);
    w->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = w->stmts->begin(); it != w->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
    delete st;
    st = origin;
}

void TypeCheckVisitor::visitMethod(Method *m)
{
    inMethod = true;
    SymbolTable *origin = st;
    st = new SymbolTable(origin); //scope for Methods

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
    inMethodReturnCheck = true;
    m->ident->accept(this);
    inMethodReturnCheck = false;
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
    st = origin;
}

void TypeCheckVisitor::visitTrueIdentOption(TrueIdentOption *t)
{
    //fprintf(stderr, "TrueIdentOption visited\n");
    if (inMethodReturnCheck)
    {
        if (strcmp(t->id, (char*)"Nothing") == 0)
        {
            returned = true;  //assume method returns nothing
        }
        returnType = t->id;
    }
}

void TypeCheckVisitor::visitFalseIdentOption(FalseIdentOption *f)
{
    if (inMethodReturnCheck)
    {
        returnType = strdup((char*)"Nothing");
        returned = true; // by default, assume the method returns nothing
    }
    /*
    if (inMethod)
    {
        fprintf(stderr, "FalseIdentOption visited\n");
        returnType = strdup((char*)"Nothing");
        returned = true; // by default, assume the method returns nothing
    }
    */
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

    /*
    IdentNode *ident = isIdent(r->rexpr);
    if (ident != NULL)
    {
        type = st->lookupVariable(ident->id)->type;    
    } 
    else 
    {
        type = r->rexpr->type();
    }
    */
    type = getType(r->rexpr);

    // TODO: If return type is subtype, it's ok
    if (strcmp(type, returnType) != 0)
    {
        if (!tt->isSubtype(type, returnType))
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tMethod returns value of type '%s', should return '%s' or a subtype of '%s'\n", r->lineno, type, returnType, returnType);
            addError(msg);
        }
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
    SymbolTable *classScope = new SymbolTable(st);
    //SymbolTable *global = st;
    beyondConstructorScope = st;
    st = classScope;

    c->clssig->accept(this);
    c->clsbdy->accept(this);

    inClass = false;
    //st = global; //st is restored to global in visitClassBody
}

void TypeCheckVisitor::visitClassSignature(ClassSignature *cs) 
{
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

void TypeCheckVisitor::visitClassBody(ClassBody *cb)  
{
    for (list<Statement *>::const_iterator it = cb->stmts->begin(); it != cb->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
    /* We need a way for the constructor of a class to throw out arguments, and keep 'this'
     * instance variables. We define the 'classScope' as only for the constructor. We escape 
     * the class scope once this is done. Instance variables are retained because they 
     * exist in the TypeTree. */
    st = beyondConstructorScope;
    for (list<Method *>::const_iterator it = cb->meths->begin(); it != cb->meths->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitFormalArg(FormalArg *f)
{
    VariableSym *v = new VariableSym(f->id, f->type);
    st->addVariable(f->id, v);
}

/*
void TypeCheckVisitor::visitObjectFieldLExpr(ObjectFieldLExpr *o)
{
    IdentNode *ident = dynamic_cast<IdentNode*>(o->rexpr);
    if (ident != NULL)
    {
        if (strcmp(ident->id, (char*)"this") == 0) //special instance variable keyword
        {
                
        }
    }
    o->rexpr->accept(this);
}
*/
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

ObjectFieldLExpr *TypeCheckVisitor::isOFL(RExpr *r)
{
    RExprToLExpr *rl = dynamic_cast<RExprToLExpr*>(r);
    if (rl != NULL) //if it is an lexpr
    {
        ObjectFieldLExpr *ofl = dynamic_cast<ObjectFieldLExpr*>(rl->lexpr);
        if (ofl != NULL)
        {
            return ofl;
        }
    }
    return NULL;
}

char *TypeCheckVisitor::getType(RExpr *r)
{
    char *type;
    type = r->type();
    if (strcmp(type, (char*)"-") != 0) //type covered because it's a literal or easy to identify
        return type;

    IdentNode *ident = isIdent(r);
    if (ident != NULL) //type is in the variable information
    {
        if (strcmp(ident->id, (char*)"this") == 0)
        {
            return className;
        }
        VariableSym *v = st->lookupVariable(ident->id);
        if (v == NULL)
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tUse of uninitialized variable '%s'\n", r->lineno, ident->id);
            addError(msg);
            return NULL;
        }
        return v->type;
    }

    DotRExpr *dot = dynamic_cast<DotRExpr*>(r);
    if (dot != NULL)
    {
        char *_type = getType(dot->rexpr);
        MethodNode *m = tt->typeGetMethod(_type, dot->id);
        return m->returnType;
    }

    ObjectFieldLExpr *ofl = isOFL(r);
    if (ofl != NULL)
    {
        /*
        ObjectFieldLExpr *rofl = isOFL(ofl->rexpr);
        char *rType;
        if (rolf != NULL)
        {
            rType = getType(ofl->rexpr);
        }*/
        char *rType = getType(ofl->rexpr);
        if (rType == NULL)
            return strdup((char*)"-");
        char *__type = tt->getVarFromType(rType, ofl->id);
        if (__type == NULL)
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tType '%s' has no instance variable '%s'\n", r->lineno, rType, ofl->id);
            addError(msg);
            return strdup((char*)"-");
        }
        return __type;
    }

    PlusNode *plus = dynamic_cast<PlusNode*>(r);
    if (plus != NULL)
    {
        return getType(plus->left);
    }
    MinusNode *minus = dynamic_cast<MinusNode*>(r);
    if (minus != NULL)
    {
        return getType(minus->left);
    }
    TimesNode *times = dynamic_cast<TimesNode*>(r);
    if (times != NULL)
    {
        return getType(times->left);
    }
    DivideNode *divide = dynamic_cast<DivideNode*>(r);
    if (divide != NULL)
    {
        return getType(divide->left);
    }

    return strdup((char*)"-");
}
/*
 *
 * 

OverrideMethodVisitor::OverrideMethodVisitor(TypeCheckVisitor *p, SymbolTable *s, TypeTree *t, char *super, char *sub) 
    : parent(p), st(s), tt(t), superclass(super), subclass(sub) {}


*/
