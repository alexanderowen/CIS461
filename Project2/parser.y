%{
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "lex.yy.h"
#include "node.h"

using namespace std;

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *msg);

Program *root;
%}

%union {
    int integer;
    char *id;
    list<Statement *> *stmts;
    list<Class *>     *clsss; 
    list<RExpr *> *rexprs;
    Statement *stmt;
    RExpr *rexpr;
    LExpr *lexpr;
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
%type <lexpr> l_expr
%type <clsss> class_star 
%type <rexprs> actual_args extra_actual_args
%%
program:
        class_star statement_star {$$ = new Program($1, $2); root = $$;}
        ;

class_star: 
            /* epsilon */ {$$ = new list<Class *>();}
      /*    | class_star class */
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
        | statement_star statement {$$ = $1; $1->push_back($2);} 
        ;

statement_block:
                '{' statement_star  '}'
                ;

statement:
/*          if_block
        | while_statement 
        | l_expr ident_option '=' r_expr ';'
        | RETURN r_expr_option ';'
        | r_expr ';' {$$ = new RExprStatement($1);}
*/
        r_expr ';' {$$ = new RExprStatement($1);}
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
      IDENT            {$$ = new IdentNode($1);}
    | r_expr '.' IDENT {$$ = new ObjectFieldLExpr($1, $3);}
    ;

r_expr:
      STRING_LIT {$$ = new StringNode($1);}
    | INT_LIT    {$$ = new IntNode($1);}
    | l_expr     {$$ = new RExprToLExpr($1);} 
    | r_expr '+' r_expr {$$ = new PlusNode($1, $3);}
    | r_expr '-' r_expr {$$ = new MinusNode($1, $3);}
    | r_expr '*' r_expr {$$ = new TimesNode($1, $3);}
    | r_expr '/' r_expr {$$ = new DivideNode($1, $3);}
    | '(' r_expr ')'    {$$ = $2;} /*TODO: Make sure this works properly*/
    | r_expr EQUALS r_expr  {$$ = new EqualsNode($1, $3);}
    | r_expr ATMOST r_expr  {$$ = new AtMostNode($1, $3);}
    | r_expr '<' r_expr     {$$ = new LessThanNode($1, $3);}
    | r_expr ATLEAST r_expr {$$ = new AtLeastNode($1, $3);}
    | r_expr '>' r_expr     {$$ = new GreaterThanNode($1, $3);}
    | r_expr AND r_expr     {$$ = new AndNode($1, $3);}
    | r_expr OR r_expr      {$$ = new OrNode($1, $3);}
    | NOT r_expr            {$$ = new NotNode($2);}
    | r_expr '.' IDENT '(' actual_args ')' {$$ = new DotRExpr($1, $3, $5);}
    | IDENT '(' actual_args ')' {$$ = new ConstructorRExpr($1, $3);}
    ;

r_expr_option:
              /* epsilon */
            | r_expr
            ;

actual_args:
           /* epsilon */            {$$ = new list<RExpr *>();}
        |  r_expr extra_actual_args {$$ = new list<RExpr *>(); $$->push_back($1); $$->merge(*($2));}
        ;

extra_actual_args:
                  /* epsilon */                {$$ = new list<RExpr *>();}
                | extra_actual_args ',' r_expr {$$ = $1; $1->push_back($3);}
%%


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
