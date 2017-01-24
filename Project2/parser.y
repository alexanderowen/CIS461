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

%left AND OR NOT
%left '<' '>' '=' ATMOST ATLEAST EQUALS 
%left '+' '-'
%left '*' '/'
%left '.'
// might be incorrect to say '.' is left associative

%%
// this is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:
program:
        class_star statement_plus
        ;

class_star: 
            /* epsilon */
          | class_star class
          ;

class:
     class_signature class_body
    ;

class_signature:
               CLASS IDENT '(' formal_args ')' 
             | CLASS IDENT '(' formal_args ')' EXTENDS IDENT
             ;

formal_args: 
             /* epsilon */
           | formal_arg formal_args_star 
           ;

formal_arg:
          IDENT ':' IDENT
        ;

formal_args_star: 
                  /* epsilon */
                | ',' IDENT ':' IDENT formal_args_star 
                ;

class_body:
          '{' statement_star method_star '}'

method_star:
           DEF IDENT '(' formal_args ')' statement_block
         | DEF IDENT '(' formal_args ')' ':' IDENT statement_block  

statement_plus:
          statement
        | statement_plus statement
        ;

statement_star: 
          /* epsilon */
        | statement_star statement
        ;

statement_block:
                '{' statement_star  '}'
                ;

statement:
          if_block
        | while_statement 
        | l_expr '=' r_expr ';' {printf("evaluated statement\n");}
        | l_expr ':' IDENT '=' r_expr ';'
        ;

if_block:
        if_statement elif_statement_star else_statement_optional
        ;

if_statement:
            IF expr statement_block
            ;

elif_statement_star: 
                  /* epsilon */
                | elif_statement_star elif_statement
                ;
                
elif_statement:
              ELIF expr statement_block
            ;

else_statement_optional: 
              /* epsilon */
            | ELSE statement_block
            ;

while_statement:
               WHILE expr statement_block
            ;

expr:
     r_expr
    ;

l_expr:
      IDENT
    | r_expr '.' IDENT
    ;

r_expr:
      STRING_LIT
    | INT_LIT
    | l_expr
    | r_expr '+' r_expr
    | r_expr '-' r_expr
    | r_expr '*' r_expr
    | r_expr '/' r_expr
    | '(' r_expr ')'
    | r_expr EQUALS r_expr
    | r_expr ATMOST r_expr
    | r_expr '<' r_expr
    | r_expr ATLEAST r_expr
    | r_expr '>' r_expr
    | r_expr AND r_expr
    | r_expr OR r_expr
    | NOT r_expr
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
