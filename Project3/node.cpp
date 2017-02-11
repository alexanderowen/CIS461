#include <list>
#include <stdio.h>
#include <string.h>
#include "node.h"

using std::list;

Class::Class(ClassSignature *cs, ClassBody *cb) : clssig(cs), clsbdy(cb) {}
void Class::print()
{
    fprintf(stdout, "Found Class\n");
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
char * FalseExtendsOption::getID()
{
    return (char *)"";
}

TrueExtendsOption::TrueExtendsOption(char *i) : id(i) {}
void TrueExtendsOption::print()
{
    fprintf(stdout, "Found TrueExtendsOption\n");
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
/*
class ExtraFormalArgsStar {};
*/

ClassBody::ClassBody(list<Statement *> *s, list<Method *> *m) : stmts(s), meths(m) {}
void ClassBody::print()
{
    fprintf(stdout, "Found ClassBody\n");
}

Method::Method(char *i, list<FormalArg *> *f, IdentOption *io, list<Statement *> *s) 
    : id(i), fargs(f), ident(io), stmts(s) {}
void Method::print()
{
    fprintf(stdout, "Found Method\n");
}

FalseIdentOption::FalseIdentOption() {}
void FalseIdentOption::print()
{
    fprintf(stdout, "Found FalseIdentOption\n");
}

TrueIdentOption::TrueIdentOption(char *i) : id(i) {}
void TrueIdentOption::print()
{
    fprintf(stdout, "Foudn TrueIdentOption\n");
}
/*
class StatementBlock {};
*/


/*****************
 * RExpr classes *
 *****************/
EmptyRExpr::EmptyRExpr() {}
void EmptyRExpr::print()
{
    fprintf(stdout, "Found EmptyRExpr\n");
}

DotRExpr::DotRExpr(RExpr *r, char *i, list<RExpr *> *a) : rexpr(r), id(i), args(a) {}
void DotRExpr::print()
{
    fprintf(stdout, "Found DotRExpr\n");
}

ConstructorRExpr::ConstructorRExpr(char *i, list<RExpr *> *a) : id(i), args(a) {}
void ConstructorRExpr::print()
{
    fprintf(stdout, "Found ConstructorRExpr\n");
}

RExprToLExpr::RExprToLExpr(LExpr *l) : lexpr(l) {}
void RExprToLExpr::print()
{
    fprintf(stdout, "Found RExprToLExpr\n");
}

StringNode::StringNode(char *i) : id(i) {}
void StringNode::print()
{
    fprintf(stdout, "Found StringNode\n");
}

IntNode::IntNode(int i) : value(i) {}
void IntNode::print()
{
    fprintf(stdout, "Found IntNode\n");
}

NotNode::NotNode(RExpr *v) : value(v) {}
void NotNode::print()
{
    fprintf(stdout, "Found NotNode\n");
}

BinaryOperatorNode::BinaryOperatorNode(RExpr *r, RExpr *l)
{
    right = r;
    left  = l;
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

ReturnStatement::ReturnStatement(RExpr *r) : rexpr(r) {}
void ReturnStatement::print()
{
    fprintf(stdout, "Found ReturnStatement\n");
}

AssignmentStatement::AssignmentStatement(LExpr *l, IdentOption *i, RExpr *r) : lexpr(l), ident(i), rexpr(r) {}
void AssignmentStatement::print()
{
    fprintf(stdout, "Found AssignmentStatement\n");
}

/*
class IfBlock {};
*/
IfClause::IfClause(RExpr *r, list<Statement *> *s) : rexpr(r), stmts(s) {}
void IfClause::print()
{
    fprintf(stdout, "Found IfClause\n");
}

ElifClause::ElifClause(RExpr *r, list<Statement *> *s) : rexpr(r), stmts(s) {}
void ElifClause::print()
{
    fprintf(stdout, "Found ElifClause\n");
}

FalseElseOption::FalseElseOption() {}
void FalseElseOption::print()
{
    fprintf(stdout, "Found FalseElseOption\n");
}

TrueElseOption::TrueElseOption(list<Statement *> *s) : stmts(s) {}
void TrueElseOption::print()
{
    fprintf(stdout, "Found TrueElseOption\n");
}

IfBlock::IfBlock(IfClause *i, list<ElifClause *> *ei, ElseOption *el) : _if(i), _elifs(ei), _else(el) {}
void IfBlock::print()
{
    fprintf(stdout, "Found IfBlock\n");
}

WhileStatement::WhileStatement(RExpr *r, list<Statement *> *s) : rexpr(r), stmts(s) {}
void WhileStatement::print()
{
    fprintf(stdout, "Found a WhileStatement\n");
}

IdentNode::IdentNode(char *i) : id(i) {}
void IdentNode::print()
{
    fprintf(stdout, "Found a LExpr\n");
}

ObjectFieldLExpr::ObjectFieldLExpr(RExpr *r, char *i) : rexpr(r), id(i) {}
void ObjectFieldLExpr::print()
{
    fprintf(stdout, "Found a ObjectFieldLExpr\n");
}

bool withinList(list<char *> *l, char *c)
{
    for (list<char *>::const_iterator it = l->begin(); it != l->end(); ++it)
    {
        if (strcmp(*it, c) == 0)
            return true;
    }
    return false;
}

int findWithinList(list<char *> *l, char *c)
{
    int i = 0;
    for (list<char *>::const_iterator it = l->begin(); it != l->end(); ++it)
    {
        if (strcmp(*it, c) == 0)
            return i;
        i++;
    }
    return -1;

}

Program::Program(list<Class *> *c, list<Statement *> *s) : classes(c), statements(s) {}
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
