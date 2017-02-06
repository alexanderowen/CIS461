%{
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "lex.yy.h"
#include "node.h"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *msg);

Program *root;
%}

%union {
    int integer;
    char *id;
    list<Statement *> stmts;
    Statement *stmt;
    RExpr *rexpr;
    Program *pgm;

}

%token <integer> INT_LIT
%token <id>      STRING_LIT IDENT
%token CLASS DEF EXTENDS IF ELIF ELSE WHILE RETURN 
%token ATLEAST ATMOST EQUALS AND OR NOT 

%left AND OR NOT
%left '<' '>' '=' ATMOST ATLEAST EQUALS 
%left '+' '-'
%left '*' '/'
%left '.'

%type <pgm> program
%type <stmt> statement
%type <stmts> statement_star
%type <rexpr> r_expr
%%
program:
        class_star statement_star {$$ = new Program($1, $2); root = $$;}
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
          /* epsilon */            {$$ = new list<Statement *>();}
        | statement_star statement {$$ = $1; $1->push_back($2)} 
        ;

statement_block:
                '{' statement_star  '}'
                ;

statement:
          if_block
        | while_statement 
        | l_expr ident_option '=' r_expr ';'
        | RETURN r_expr_option ';'
        | r_expr ';' {$$ = new RExprStatement($1);}
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
      STRING_LIT {$$ = new StringNode($1);}
    | INT_LIT    {$$ = new IntNode($1);}
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


