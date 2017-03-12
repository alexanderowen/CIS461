#ifndef TRANSLATORVISITOR_H
#define TRANSLATORVISITOR_H

#include "stdio.h"

#include <unordered_map>
#include <string>

#include "visitor.h"

using std::unordered_map;
using std::string;

class TranslatorVisitor : public Visitor 
{
    private:
        FILE *f = NULL;
        unordered_map<string, string> typeMap;
        unordered_map<string, string> keywords;

        IdentNode *isIdent(RExpr *);
        ObjectFieldLExpr *isOFL(RExpr *);
        char *getType(RExpr *);
        void printRExpr(RExpr *);

    public:
        TranslatorVisitor(char *);
       ~TranslatorVisitor(); 

        void visitProgram(Program *);
        void visitAssignmentStatement(AssignmentStatement *);

        void visitIfClause(IfClause *);
        void visitElifClause(ElifClause *);
        void visitTrueElseOption(TrueElseOption *);

        void visitWhileStatement(WhileStatement *);

        void visitIntNode(IntNode *);
        void visitStringNode(StringNode *);
        void visitBinaryOperatorNode(BinaryOperatorNode *);
        void visitIdentNode(IdentNode *);
        void visitDotRExpr(DotRExpr *);
};

#endif 
