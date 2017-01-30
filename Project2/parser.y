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
        class_star statement_star
        ;

class_star: 
            /* epsilon */
          | class_star class
          ;

class:
     class_signature class_body
    ;

class_signature:
               CLASS IDENT '(' formal_args ')' extends_option 
             ;

extends_option:
              /* epsilon */
            | EXTENDS IDENT
            ;

formal_args: 
             /* epsilon */
           | formal_arg extra_formal_args_star 
           ;

formal_arg:
          IDENT ':' IDENT
        ;

extra_formal_args_star: 
                  /* epsilon */
                | extra_formal_args_star ',' IDENT ':' IDENT 
                ;

class_body:
          '{' statement_star method_star '}'

method:
       DEF IDENT '(' formal_args ')' ident_option statement_block
     ;

ident_option:
          /* epsilon */
        | ':' IDENT
        ;

method_star:
          /* epsilon */
        | method_star method
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
        | l_expr ident_option '=' r_expr ';'
        | RETURN r_expr_option ';'
        | r_expr ';'
        ;

if_block:
        if_statement elif_statement_star else_statement_option
        ;

if_statement:
            IF r_expr statement_block
            ;

elif_statement_star: 
                  /* epsilon */
                | elif_statement_star elif_statement
                ;
                
elif_statement:
              ELIF r_expr statement_block
            ;

else_statement_option: 
              /* epsilon */
            | ELSE statement_block
            ;

while_statement:
               WHILE r_expr statement_block
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
    | r_expr '.' IDENT '(' actual_args ')'
    | IDENT '(' actual_args ')'
    ;

r_expr_option:
              /* epsilon */
            | r_expr
            ;

actual_args:
           /* epsilon */
        |  r_expr extra_actual_args
        ;

extra_actual_args:
                  /* epsilon */
                | extra_actual_args ',' r_expr
%%

int main(int argc, char* argv[]) {
    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) 
    {
        fprintf(stderr, "I can't open file!\n");
        return -1;
    }

    fprintf(stderr, "Beginning parse of %s\n", argv[1]);
    yyin = myfile;
    do {
        yyparse();
    } while (!feof(yyin));

    fprintf(stderr, "Finished parse with result 0\n");
    return 0;
}

void yyerror(const char *s) 
{
    fprintf(stderr, "parse error! Message: %s\n", s);
    exit(-1);
}
