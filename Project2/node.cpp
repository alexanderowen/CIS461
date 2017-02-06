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

class LExpr {};
*/

/*****************
 * RExpr classes *
 *****************/

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

/*
class RExprOption {};

class ActualArgs {};

class ExtraActualArgs {};
*/

Program::Program(list<Class *> *c, list<Statement *> *s) : classes(c), statements(s) {}
