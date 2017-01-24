%option yylineno
%option header-file="lex.yy.h"
%option noyywrap

%{
#include <stdio.h>
#include "parser.tab.h"
%}

%x comment
%x triplequotes

%%

"/*"         {BEGIN(comment);}
<comment>[^*\n]*         ;
<comment>"*"+[^*/\n]*    ;
<comment>\n  ;
<comment>"*"+"/"        {BEGIN(INITIAL);}

\/\/.*  {;}

\"{3}[^\"{3}]*\"{3} {return STRING_LIT;}

[ \n\t\r\v\f] {;}

class    {return CLASS;}
def      {return DEF;}
extends  {return EXTENDS;}
if       {return IF;}
elif     {return ELIF;}
else     {return ELSE;}
while    {return WHILE;}
return   {return RETURN;}
\>\=     {return ATLEAST;}
\<\=     {return ATMOST;}
\=\=     {return EQUALS;}
and      {return AND;}
or       {return OR;}
not      {return NOT;}
[0-9]+   {return INT_LIT;}

[(){}/*+\-!:;,\.=<>]      {return yytext[0];}
["](([\\][0btnrf"\\])|[^"\n\0\b\t\n\r\f\"\\])*["]   {return STRING_LIT;}
["](([\\][^0btnrf"\\])|[^"\n])*["]  {fprintf(stderr, "%d: Illegal escape code; only \\\\, \\0, \\t, \\n, \\r, \\n are permitted (at '%s')\n",yylineno, yytext); return STRING_LIT;}
["][^"\n]*[\n] {fprintf(stderr, "%d: Unclosed string?  Encountered newline in quoted string. (at '%s')\n", yylineno, yytext ); return STRING_LIT;}
[a-zA-Z_][a-zA-Z0-9_]*       {return IDENT;}
<<EOF>>  {return EOF;}

%%


