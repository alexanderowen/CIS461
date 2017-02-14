#include <list>
#include <stdio.h>
#include <string.h>

#include "visitor.h"
#include "node.h"
#include "util.h"

using std::list;

Class::Class(ClassSignature *cs, ClassBody *cb) : clssig(cs), clsbdy(cb) {}
void Class::print()
{
    fprintf(stdout, "Found Class\n");
}
void Class::accept(Visitor *v)
{
    v->visitClass(this);
}
char *Class::getID() 
{
    return clssig->getID();
}
char *Class::getExtends()
{
    return clssig->getExtends();
}

ClassSignature::ClassSignature(char *i, list<FormalArg *> *f, ExtendsOption *e) 
    : id(i), fargs(f), exop(e) {}
void ClassSignature::print()
{
    fprintf(stdout, "Found ClassSignature\n");
}
void ClassSignature::accept(Visitor *v)
{
    v->visitClassSignature(this);
}
char *ClassSignature::getID()
{
    return id;
}
char *ClassSignature::getExtends()
{
    return exop->getID();
}


FalseExtendsOption::FalseExtendsOption() {}
void FalseExtendsOption::print()
{
    fprintf(stdout, "Found FalseExtendsOption\n");
}
void FalseExtendsOption::accept(Visitor *v)
{
    v->visitFalseExtendsOption(this);
}
char * FalseExtendsOption::getID()
{
    return (char *)"Obj";
}

TrueExtendsOption::TrueExtendsOption(char *i) : id(i) {}
void TrueExtendsOption::print()
{
    fprintf(stdout, "Found TrueExtendsOption\n");
}
void TrueExtendsOption::accept(Visitor *v)
{
    v->visitTrueExtendsOption(this);
}
char *TrueExtendsOption::getID()
{
    return id;
}

FormalArg::FormalArg(char *i, char *t) : id(i), type(t) {}
void FormalArg::print()
{
    fprintf(stdout, "Found FormalArg\n");
}
void FormalArg::accept(Visitor *v)
{
    v->visitFormalArg(this);
}

ClassBody::ClassBody(list<Statement *> *s, list<Method *> *m) : stmts(s), meths(m) {}
void ClassBody::print()
{
    fprintf(stdout, "Found ClassBody\n");
}
void ClassBody::accept(Visitor *v)
{
    v->visitClassBody(this);
}

Method::Method(char *i, list<FormalArg *> *f, IdentOption *io, list<Statement *> *s) 
    : id(i), fargs(f), ident(io), stmts(s) {}
void Method::print()
{
    fprintf(stdout, "Found Method\n");
}
void Method::accept(Visitor *v)
{
    v->visitMethod(this);
}

FalseIdentOption::FalseIdentOption() {}
void FalseIdentOption::print()
{
    fprintf(stdout, "Found FalseIdentOption\n");
}
void FalseIdentOption::accept(Visitor *v)
{
    v->visitFalseIdentOption(this);
}

TrueIdentOption::TrueIdentOption(char *i) : id(i) {}
void TrueIdentOption::print()
{
    fprintf(stdout, "Foudn TrueIdentOption\n");
}
void TrueIdentOption::accept(Visitor *v)
{
    v->visitTrueIdentOption(this);
}


/*****************
 * RExpr classes *
 *****************/
EmptyRExpr::EmptyRExpr() {}
void EmptyRExpr::print()
{
    fprintf(stdout, "Found EmptyRExpr\n");
}
void EmptyRExpr::accept(Visitor *v)
{
    v->visitEmptyRExpr(this);
}

DotRExpr::DotRExpr(RExpr *r, char *i, list<RExpr *> *a) : rexpr(r), id(i), args(a) {}
void DotRExpr::print()
{
    fprintf(stdout, "Found DotRExpr\n");
}
void DotRExpr::accept(Visitor *v)
{
    v->visitDotRExpr(this);
}

ConstructorRExpr::ConstructorRExpr(char *i, list<RExpr *> *a) : id(i), args(a) {}
void ConstructorRExpr::print()
{
    fprintf(stdout, "Found ConstructorRExpr\n");
}
void ConstructorRExpr::accept(Visitor *v)
{
    v->visitConstructorRExpr(this);
}

RExprToLExpr::RExprToLExpr(LExpr *l) : lexpr(l) {}
void RExprToLExpr::print()
{
    fprintf(stdout, "Found RExprToLExpr\n");
}
void RExprToLExpr::accept(Visitor *v)
{
    v->visitRExprToLExpr(this);
}

StringNode::StringNode(char *i) : id(i) {}
void StringNode::print()
{
    fprintf(stdout, "Found StringNode\n");
}
void StringNode::accept(Visitor *v)
{
    v->visitStringNode(this);
}

IntNode::IntNode(int i) : value(i) {}
void IntNode::print()
{
    fprintf(stdout, "Found IntNode\n");
}
void IntNode::accept(Visitor *v)
{
    v->visitIntNode(this);
}

NotNode::NotNode(RExpr *v) : value(v) {}
void NotNode::print()
{
    fprintf(stdout, "Found NotNode\n");
}
void NotNode::accept(Visitor *v)
{
    v->visitNotNode(this);
}

BinaryOperatorNode::BinaryOperatorNode(RExpr *r, RExpr *l)
{
    right = r;
    left  = l;
}
void BinaryOperatorNode::accept(Visitor *v)
{
    v->visitBinaryOperatorNode(this);
}

PlusNode::PlusNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {} 
void PlusNode::print()
{
    fprintf(stdout, "Found PlusNode\n");
}

MinusNode::MinusNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void MinusNode::print()
{
    fprintf(stdout, "Found MinusNode\n");
}

TimesNode::TimesNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void TimesNode::print()
{
    fprintf(stdout, "Found TimesNode\n");
}

DivideNode::DivideNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void DivideNode::print()
{
    fprintf(stdout, "Found DivideNode\n");
}

EqualsNode::EqualsNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void EqualsNode::print()
{
    fprintf(stdout, "Found EqualsNode\n");
}

AtMostNode::AtMostNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void AtMostNode::print()
{
    fprintf(stdout, "Found AtMostNode\n");
}

LessThanNode::LessThanNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void LessThanNode::print()
{
    fprintf(stdout, "Found LessThanNode\n");
}

AtLeastNode::AtLeastNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void AtLeastNode::print()
{
    fprintf(stdout, "Found AtLeastNode\n");
}


GreaterThanNode::GreaterThanNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void GreaterThanNode::print()
{
    fprintf(stdout, "Found GreaterThanNode\n");
}

AndNode::AndNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void AndNode::print()
{
    fprintf(stdout, "Found AndNode\n");
}

OrNode::OrNode(RExpr *l, RExpr *r) : BinaryOperatorNode(l, r) {}
void OrNode::print()
{
    fprintf(stdout, "Found OrNode\n");
}

/*********
 * Statement classes
 * *******/

RExprStatement::RExprStatement(RExpr *r) : rexpr(r) {}
void RExprStatement::print()
{
    fprintf(stdout, "Found RExprStatement\n");
}
void RExprStatement::accept(Visitor *v)
{
    v->visitRExprStatement(this);
}

ReturnStatement::ReturnStatement(RExpr *r) : rexpr(r) {}
void ReturnStatement::print()
{
    fprintf(stdout, "Found ReturnStatement\n");
}
void ReturnStatement::accept(Visitor *v)
{
    v->visitReturnStatement(this);
}

AssignmentStatement::AssignmentStatement(LExpr *l, IdentOption *i, RExpr *r) : lexpr(l), ident(i), rexpr(r) {}
void AssignmentStatement::print()
{
    fprintf(stdout, "Found AssignmentStatement\n");
}
void AssignmentStatement::accept(Visitor *v)
{
    v->visitAssignmentStatement(this);
}

IfClause::IfClause(RExpr *r, list<Statement *> *s) : rexpr(r), stmts(s) {}
void IfClause::print()
{
    fprintf(stdout, "Found IfClause\n");
}
void IfClause::accept(Visitor *v)
{
    v->visitIfClause(this);
}

ElifClause::ElifClause(RExpr *r, list<Statement *> *s) : rexpr(r), stmts(s) {}
void ElifClause::print()
{
    fprintf(stdout, "Found ElifClause\n");
}
void ElifClause::accept(Visitor *v)
{
    v->visitElifClause(this);
}

FalseElseOption::FalseElseOption() {}
void FalseElseOption::print()
{
    fprintf(stdout, "Found FalseElseOption\n");
}
void FalseElseOption::accept(Visitor *v)
{
    v->visitFalseElseOption(this);
}

TrueElseOption::TrueElseOption(list<Statement *> *s) : stmts(s) {}
void TrueElseOption::print()
{
    fprintf(stdout, "Found TrueElseOption\n");
}
void TrueElseOption::accept(Visitor *v)
{
    v->visitTrueElseOption(this);
}

IfBlock::IfBlock(IfClause *i, list<ElifClause *> *ei, ElseOption *el) : _if(i), _elifs(ei), _else(el) {}
void IfBlock::print()
{
    fprintf(stdout, "Found IfBlock\n");
}
void IfBlock::accept(Visitor *v)
{
    v->visitIfBlock(this);
}

WhileStatement::WhileStatement(RExpr *r, list<Statement *> *s) : rexpr(r), stmts(s) {}
void WhileStatement::print()
{
    fprintf(stdout, "Found a WhileStatement\n");
}
void WhileStatement::accept(Visitor *v)
{
    v->visitWhileStatement(this);
}

IdentNode::IdentNode(char *i) : id(i) {}
void IdentNode::print()
{
    fprintf(stdout, "Found a LExpr\n");
}
void IdentNode::accept(Visitor *v)
{
    v->visitIdentNode(this);
}

ObjectFieldLExpr::ObjectFieldLExpr(RExpr *r, char *i) : rexpr(r), id(i) {}
void ObjectFieldLExpr::print()
{
    fprintf(stdout, "Found a ObjectFieldLExpr\n");
}
void ObjectFieldLExpr::accept(Visitor *v)
{
    v->visitObjectFieldLExpr(this);
}


Program::Program(list<Class *> *c, list<Statement *> *s) : classes(c), statements(s) {}
void Program::accept(Visitor *v)
{
    v->visitProgram(this);
}
bool Program::checkClassHierarchy()
{
    list<char *> def;     // defined by Quack
    def.push_back((char *)"Obj");
    def.push_back((char *)"Int");
    def.push_back((char *)"String");
    def.push_back((char *)"Nothing");
    list<char *> userDef; // defined by user
    list<char *> toBeDef; // to be defined by user
    for (list<Class *>::const_iterator it = classes->begin(); it != classes->end(); ++it)
    {
        char *id = (*it)->getID();
        char *extend = (*it)->getExtends();
        //fprintf(stderr, "Extends: '%s'\n", extend);
        
        if (withinList(&toBeDef, (*it)->getID()) && withinList(&userDef, (*it)->getExtends()))
            return false;
        userDef.push_back((*it)->getID());
        if (withinList(&toBeDef, (*it)->getID()))
        {
            int i = findWithinList(&toBeDef, (*it)->getID()); 
            list<char *>::iterator iter = toBeDef.begin();
            advance(iter, i);
            toBeDef.erase(iter);
        }
        if (!withinList(&userDef, extend) && !withinList(&def, extend))
        {
            toBeDef.push_back(extend);
        }
    }

    if (toBeDef.size() > 0)
        return false;
    return true;
}
