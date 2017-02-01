/* Project 2, Quack parser (without abstract syntax tree), Winter 2017
 * Author: Alexander Owen
 *
 * Driver for Bison parser for Quack (.qk) programs
 * */

#include <stdio.h>
#include "lex.yy.h"
#include "parser.tab.h"

extern FILE *yyin;
extern int yyparse();

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
    fprintf(stderr, "Beginning parse of %s\n", argv[1]);
    condition = yyparse();
    if (condition == 0)
        fprintf(stderr, "Finished parse with no errors\n"); 

    return 0;
}
