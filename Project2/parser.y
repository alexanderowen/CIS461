%{
#include <stdio.h>
#include <stdlib.h>

// stuff from flex that bison needs to know about:
int yylex();
int yyparse();
FILE *yyin;
 
void yyerror(const char *s);
%}

%token CLASS DEF EXTENDS IF ELIF ELSE WHILE RETURN ATLEAST ATMOST EQUALS 
%token AND OR NOT IDENT INT_LIT STRING_LIT

%%
// this is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:
program:
       statements

statements:
          statement
        | statements statement
        ;

statement:
          l_expr '=' r_expr ';' {printf("evaluated statement\n");}
        ;

l_expr:
      IDENT
    | r_expr '.' IDENT
    ;

r_expr:
      STRING_LIT
    | INT_LIT
    ;

%%

int main(int argc, char* argv[]) {
    // open a file handle to a particular file:
    FILE *myfile = fopen(argv[1], "r");
    // make sure it is valid:
    if (!myfile) {
        fprintf(stderr, "I can't open file!\n");
        return -1;
    }
    // set flex to read from it instead of defaulting to STDIN:
    yyin = myfile;
    
    // parse through the input until there is no more:
    do {
        yyparse();
    } while (!feof(yyin));
    
}

void yyerror(const char *s) {
    fprintf(stderr, "parse error! Message: %s\n", s);
    // might as well halt now:
    exit(-1);
}
