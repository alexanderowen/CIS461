%option yylineno
%option header-file="lex.yy.h"
%option noyywrap

%{
#include <stdio.h>
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

\"{3}[^\"{3}]*\"{3} {return 274;}

[ \n\t\r\v\f] {;}

class    {return 258;}
def      {return 259;}
extends  {return 260;}
if       {return 261;}
elif     {return 262;}
else     {return 263;}
while    {return 264;}
return   {return 265;}
\>\=     {return 266;}
\<\=     {return 267;}
\=\=     {return 268;}
and      {return 269;}
or       {return 270;}
not      {return 271;}
[0-9]+   {return 273;}

[(){}/*+\-!:;,\.=]      {return yytext[0];}
[a-zA-Z_][a-zA-Z0-9_]*       {return 272;}
["](([\\][0btnrf"\\])|[^"\\n])*["]   {return 274;}
["](([\\].)|[^"\\])*["]  {printf("%d Illegal escape code; only \\\\, \\0, \\t, \\n, \\r, \\n are permitted (at '%s')\n",yylineno, yytext); return 274;}

<<EOF>>  {return EOF;}

%%


