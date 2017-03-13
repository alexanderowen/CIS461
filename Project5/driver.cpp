#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iostream>

#include "TranslatorVisitor.hpp"
#include "visitor.h"
#include "type.hpp"
#include "node.hpp"
#include "lex.yy.h"
#include "quack.tab.h"
/*
using namespace std;

extern int yylex();
void yyerror(const char *msg);
*/
extern FILE *yyin;
extern int yyparse();
extern Program *root;
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return -1;
    }

    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) 
    {
        fprintf(stderr, "I can't open file!\n");
        return -1;
    }

    int condition;
    yyin = myfile;
    //fprintf(stderr, "Beginning parse of %s\n", argv[1]);
    
    condition = yyparse();
    if (condition != 0)
        return -1;

    //fprintf(stderr, "Program lineno: %d", root->lineno);
    if (!root->checkClassHierarchy())
    {
        fprintf(stderr, "Error: Class hierarchy is malformed\n");
        return 0;
    } 

    ConstructorVisitor cv;
    root->accept(&cv);
    //cv.print();
    if (!cv.checkStructure())
    {
        fprintf(stderr, "Error: Call to constructor that is not defined\n");
        return 0;
    }

    TypeTreeVisitor ttv;
    root->accept(&ttv);    
    //ttv.tt->print();

    TypeCheckVisitor tcv(ttv.tt);
    root->accept(&tcv);
    //printf("Size: %d\n", tcv.st->vMap.size());
    if (tcv.errors > 0)
    {
        for (list<char*>::const_iterator it = tcv.msgs.begin(); it != tcv.msgs.end(); ++it)
        {
            fprintf(stderr, "%s:", argv[0]);
            fprintf(stderr, "%s\n", (*it));
        }
        fprintf(stderr, "%d errors reported\n", tcv.errors);
        return -1;
    }

    if (condition != 0)
    {
        return -1;
    }

    TranslatorVisitor tv((char*)"q.out", ttv.tt);
    root->accept(&tv);

    delete root;

    return 0;
}
