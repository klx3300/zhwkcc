%{
#include <string>
#include "../semantic/word_type.hpp"
#include "../utility/utility.hpp"
// This has to be the last, to prevent some inclusion problems.
#include "../semantic/mini_c.sem.hpp"
/* this is to produce the correct column number. */
int current_column=1;
#define YY_USER_ACTION do{\
    yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = current_column;\
    yylloc.last_column = current_column + yyleng-1;\
    current_column += yyleng;\
    }while(0);
using namespace std;

%}
%option yylineno
%option noyywrap

identifier   [A-Za-z][A-Za-z0-9]*
literal_int    [0-9]+
literal_float  ([0-9]*\.[0-9]+)|([0-9]+\.)
literal_string ".*"
/*literal_char '((.)|(\\[n]))'*/
literal_char '(.)'


%%
{literal_int}        {yylval.literal_int = string_to_integer(string(yytext)); return LiteralInteger;}
{literal_float}      {yylval.literal_int = string_to_double(string(yytext)); return LiteralFloat;}
{literal_string}     {yylval.literal_string = string(yytext); return LiteralString;}
{literal_char}  {yylval.literal_string = string(yytext); return LiteralChar;}
"char"  {yylval.identifier = string(yytext); return IdentifierType;}
"int"    {yylval.identifier = string(yytext); return IdentifierType;}
"float"      {yylval.identifier = string(yytext); return IdentifierType;}
"string"    {yylval.identifier = string(yytext); return IdentifierType;}
"pointer" {yylval.identifier = string(yytext); return AsPointer;}
"array" {yylval.identifier = string(yytext); return AsArray;}

"return"     {return Return;}
"if"         {return CondIf;}
"else"       {return CondElse;}
"while"      {return LoopWhile;}

 /* identifier alike operators. */

"and"         {return OperatorAnd;}
"or"            {return OperatorOr;}
"not"			{return OperatorNot;}
"addr"  {return OperatorAddr;}
"deref" {return OperatorDeref;}
{identifier}       {yylval.identifier = string(yytext); return Identifier;}
";"			{return Semicolon;}
","			{return Comma;}
">"|"<"|">="|"<="|"=="|"!=" {yylval.identifier = string(yytext);return OperatorRelation;}
"="			{return OperatorAssign;}
"+"			{return OperatorPlus;}
"-"			{return OperatorMinus;}
"*"			{return OperatorMul;}
"/"			{return OperatorDiv;}
"("			{return ParLeft;}
")"			{return ParRight;}
"[" {return OperatorAccessL;}
"]" {return OperatorAccessR;}
"{"			{return BlockLeft;}
"}"			{return BlockRight;}
"." {return OperatorMember;}
[\n]           {current_column = 1;}   
[ \r\t]          {}
\/\/.*$ {}
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}
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
