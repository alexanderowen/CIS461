#ifndef TRANSLATORVISITOR_H
#define TRANSLATORVISITOR_H

#include "stdio.h"

#include <unordered_map>
#include <string>

#include "visitor.h"
#include "type.hpp"

using std::unordered_map;
using std::string;

class TranslatorVisitor : public Visitor 
{
    private:
        FILE *f = NULL;
        unordered_map<string, string> typeMap;
        unordered_map<string, string> keywords;
        TypeTree *tt;

        char *className;

        IdentNode *isIdent(RExpr *);
        ObjectFieldLExpr *isOFL(RExpr *);
        char *getType(RExpr *);
        void printRExpr(RExpr *);

        // Given a TypeNode, print it's methods
        void printMethodSignatures(TypeNode *);
        list<MethodNode*> collectMethods(TypeNode *, list<MethodNode*>);

    public:
        TranslatorVisitor(char *, TypeTree *);
       ~TranslatorVisitor(); 

        void visitProgram(Program *);

        void visitClass(Class *);
        void visitClassSignature(ClassSignature *);
        void visitClassBody(ClassBody *);

        void visitFormalArg(FormalArg *);

        void visitAssignmentStatement(AssignmentStatement *);

        void visitIfClause(IfClause *);
        void visitElifClause(ElifClause *);
        void visitTrueElseOption(TrueElseOption *);

        void visitWhileStatement(WhileStatement *);

        void visitIntNode(IntNode *);
        void visitStringNode(StringNode *);
        void visitNotNode(NotNode *);
        void visitBinaryOperatorNode(BinaryOperatorNode *);
        void visitIdentNode(IdentNode *);
        void visitObjectFieldLExpr(ObjectFieldLExpr *);
        void visitDotRExpr(DotRExpr *);
};

#endif 
