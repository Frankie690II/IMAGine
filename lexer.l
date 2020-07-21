/* recognize tokens for the calculator */

%option noyywrap nodefault yylineno
%{
# include "utils.h"
# include "parser.tab.h"
%}

/* float exponent */
EXP	([Ee][-+]?[0-9]+)

%%
 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"(" |
")"     { return yytext[0]; }

 /* comparison ops */
">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"<>"    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }

 /* keywords */

"if"    { return IF; }
"then"  { return THEN; }
"else"  { return ELSE; }
"while" { return WHILE; }
"do"    { return DO; }
"def"   { return DEF;}
"img"   { return IMG; }

 /* debug hack */
"debug"[0-9]+ { debug = atoi(&yytext[5]); printf("debug set to %d\n", debug); }

 /* strings */
[a-zA-Z][a-zA-Z0-9]*  { yylval.str = lookup(yytext); return STRING; }

 /* path */
.+\.(png|jpg|jpeg)    {yylval.str=lookup(yytext); return PATH; }

 /* int */
[0-9]+              { yylval.i = atof(yytext); return INT; }

 /* double */
[0-9]\.{1}[0-9]+    { yylval.d = atof(yytext); return DOUBLE; }

"//".*  
[ \t]   /* ignore white space */ 
\\\n    printf("c> "); /* ignore line continuation */
"\n"    {  }

.	{ yyerror("Mystery character %c\n", *yytext); }
%%