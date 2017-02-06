#include <list>
#include <stdio.h>
#include "node.h"

using std::list;

/*
class Class {};

class ClassSignature {};

class ExtendsOption {};

class FormalArgs {};

class FormalArg {};

class ExtraFormalArgsStar {};

class ClassBody {};

class Method {};

class IdentOption {};

class StatementBlock {};
*/


/*****************
 * RExpr classes *
 *****************/
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

RExprStatement::RExprStatement(RExpr *R) : r(R) {}
void RExprStatement::print()
{
    fprintf(stdout, "Found RExprStatement\n");
}

/*
class IfBlock {};

class IfStatement {};

class ElifStatement {};

class ElifStatementOption {};

class WhileStatement {};
*/
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

/*
class RExprOption {};
*/

/* might not be necessary
ActualArgs::ActualArgs(RExpr *r, ExtraActualArgs *a) : rexpr(r), args(a) {}
ActualArgs::ActualArgs() : rexpr(NULL), args(NULL) {}
void ActualArgs::print()
{
    fprintf(stdout, "Found ActualArgs\n");
}
*/

/*
class ExtraActualArgs {};
*/

Program::Program(list<Class *> *c, list<Statement *> *s) : classes(c), statements(s) {}
