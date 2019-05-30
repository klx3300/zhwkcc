/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_MINI_C_SEM_SUB_HPP_INCLUDED
# define YY_YY_MINI_C_SEM_SUB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LiteralInteger = 258,
    Identifier = 259,
    OperatorRelation = 260,
    IdentifierType = 261,
    LiteralFloat = 262,
    LiteralString = 263,
    LiteralChar = 264,
    ParLeft = 265,
    ParRight = 266,
    BlockLeft = 267,
    BlockRight = 268,
    Semicolon = 269,
    Comma = 270,
    OperatorPlus = 271,
    OperatorMinus = 272,
    OperatorMul = 273,
    OperatorDiv = 274,
    OperatorAssign = 275,
    OperatorAnd = 276,
    OperatorOr = 277,
    OperatorNot = 278,
    CondIf = 279,
    CondElse = 280,
    LoopWhile = 281,
    Return = 282,
    OperatorAddr = 283,
    OperatorDeref = 284,
    OperatorMember = 285,
    OperatorAccessL = 286,
    OperatorAccessR = 287,
    AsArray = 288,
    AsPointer = 289,
    OperatorAccess = 290,
    OperatorUnaryMinus = 291,
    CondIfTrue = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef ValueType YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_MINI_C_SEM_SUB_HPP_INCLUDED  */
