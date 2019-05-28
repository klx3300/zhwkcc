%{
#include <string>
#include "../semantic/mini_c.tab.h"
#include "../semantic/word_type.h"
#include "../utility/utility.h"
/* this is to produce the correct column number. */
int current_column=1;
#define YY_USER_ACTION do{\
    yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = current_column;\
    yylloc.last_column = current_column + yyleng-1;\
    current_column += yyleng;\
    }while(0);
#define YYSTYPE WordType

%}
%option yylineno

identifier   [A-Za-z][A-Za-z0-9]*
literal_int    [0-9]+
literal_float  ([0-9]*\.[0-9]+)|([0-9]+\.)
literal_string ".*"


%%
{literal_int}        {yylval.type_int=atoi(yytext); return INT;}
{literal_float}      {yylval.type_float=atof(yytext); return FLOAT;}
{literal_string}
"int"        {strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {strcpy(yylval.type_id,  yytext);return TYPE;}

"return"     {return RETURN;}
"if"         {return IF;}
"else"       {return ELSE;}
"while"      {return WHILE;}

{identifier}       {strcpy(yylval.type_id,  yytext); return ID;}
";"			{return SEMI;}
","			{return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{return ASSIGNOP;}
"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return STAR;}
"/"			{return DIV;}
"&&"         {return AND;}
"||"            {return OR;}
"!"			{return NOT;}
"("			{return LP;}
")"			{return RP;}
"{"			{return LC;}
"}"			{return RC;}
[\n]           {current_column = 1;}   
[ \r\t]          {}   
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}
/* TODO: C & C++ style comments */
%%

/* 
void main()
{
yylex();
return 0;
}

int yywrap()
{
return 1;
}
*/
