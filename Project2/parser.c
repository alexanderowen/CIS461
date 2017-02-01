

#include <stdio.h>
#include "lex.yy.h"
#include "parser.tab.h"

int main(int argc, char* argv[])
{
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
        fprintf(stderr, "Finished parse with no errors"); 

    return 0;
}
