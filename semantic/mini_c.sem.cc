/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "mini_c.yxx" /* yacc.c:337  */

#include <cstdio>
#include <cmath>
#include <string>
#include <cstdarg>
#include "ast.hpp"
#include "val_type.hpp"
#include "../utility/utility.hpp"
#include "../lexical/mini_c.lex.hpp"
using namespace std;
#define YYSTYPE ValueType
extern int yylineno;
extern int yyleng;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);

#line 88 "mini_c.sem.cc" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "mini_c.sem.sub.hpp".  */
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
    LoopBreak = 290,
    LoopContinue = 291,
    InitializerList = 292,
    OperatorAccess = 293,
    OperatorUnaryMinus = 294,
    CondIfTrue = 295
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



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   424

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

#define YYUNDEFTOK  2
#define YYMAXUTOK   295

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    71,    72,    78,    81,    84,    87,    90,
      93,    98,   105,   106,   109,   112,   117,   124,   128,   134,
     137,   142,   147,   152,   153,   156,   162,   165,   166,   169,
     172,   175,   178,   181,   191,   196,   199,   204,   208,   212,
     216,   220,   224,   228,   232,   236,   237,   241,   245,   249,
     253,   258,   261,   264,   267,   270,   274,   278,   282,   286,
     292,   295
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LiteralInteger", "Identifier",
  "OperatorRelation", "IdentifierType", "LiteralFloat", "LiteralString",
  "LiteralChar", "ParLeft", "ParRight", "BlockLeft", "BlockRight",
  "Semicolon", "Comma", "OperatorPlus", "OperatorMinus", "OperatorMul",
  "OperatorDiv", "OperatorAssign", "OperatorAnd", "OperatorOr",
  "OperatorNot", "CondIf", "CondElse", "LoopWhile", "Return",
  "OperatorAddr", "OperatorDeref", "OperatorMember", "OperatorAccessL",
  "OperatorAccessR", "AsArray", "AsPointer", "LoopBreak", "LoopContinue",
  "InitializerList", "OperatorAccess", "OperatorUnaryMinus", "CondIfTrue",
  "$accept", "program", "ExtDefList", "ExtDef", "Specifier",
  "VariableList", "VarDec", "FuncDec", "ParamList", "ParamDec", "StmtBlk",
  "StmList", "Stmt", "Def", "InitList", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF -81

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-81)))

#define YYTABLE_NINF -4

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      28,     5,   -81,    13,     4,    26,   -81,    28,    29,   -81,
      27,   -81,   -81,   -81,    25,    33,    -9,    10,    32,    -2,
     -81,    55,   153,    72,   -81,   -81,     4,   -81,    55,    52,
      51,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   153,   153,
     153,    57,    58,   153,   187,    59,    60,   153,    63,    69,
      55,   -81,    61,    72,    72,   205,   -81,   -81,   -81,     4,
     223,   -81,   -81,   153,   153,    39,   241,   153,   136,    55,
     153,   153,   153,   153,   153,   153,   153,    81,   153,   153,
     153,   259,   -81,   -81,    73,   -81,   -81,   -81,   -81,   -81,
     -81,   277,   295,   -81,   153,   393,   -81,   313,    62,   -81,
     -16,   -16,   -18,   -18,   367,   377,   385,   -81,   169,   331,
     349,   -81,   -81,   -81,   -81,   -81,   153,   -81,   -81,   106,
     106,   -81,    65,   -81,   106,   -81
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     9,     0,     0,     0,     2,     0,     0,     8,
       0,    11,     1,     4,    16,     0,    12,     0,     0,     0,
       5,     0,     0,    23,     6,     7,     0,    18,     0,     0,
      19,    16,    14,    56,    55,    57,    58,    59,     0,     0,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,    27,     0,    23,    23,     0,    10,    21,    17,     0,
       0,    46,    47,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    29,     0,    22,    24,    25,    26,    20,
      45,     0,     0,    54,     0,    40,    53,    61,     0,    15,
      41,    42,    43,    44,    37,    38,    39,    50,     0,     0,
       0,    30,    34,    49,    48,    35,     0,    52,    51,     0,
       0,    60,    31,    33,     0,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,    79,   -81,     1,   -14,    64,   -81,    34,   -81,
      71,    11,   -80,   -81,    -3,   -22,   -19
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,    50,    15,    16,    17,    29,    30,
      51,    52,    53,    54,    65,    55,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,     8,    72,    73,     2,    11,    21,    32,     8,    27,
       2,    22,    77,    78,    77,    78,    60,    61,    62,     9,
      28,    66,    23,    10,    24,    81,    12,    56,    -3,     1,
      18,     3,     4,    14,     2,    19,    84,     3,     4,   122,
     123,    91,    92,    26,   125,    95,    97,    20,   100,   101,
     102,   103,   104,   105,   106,    99,   108,   109,   110,    31,
      28,     3,     4,    58,    86,    87,    59,    63,    64,    79,
      80,    93,    66,   117,    85,    33,    34,    82,     2,    35,
      36,    37,    38,    83,    23,   107,    13,   112,    25,    39,
     124,   115,    57,    89,    97,    40,    45,   121,    46,    47,
      41,    42,     0,    43,     0,     3,     4,    48,    49,    33,
      34,     0,     0,    35,    36,    37,    38,     0,    23,     0,
       0,     0,     0,    39,     0,     0,     0,     0,     0,    40,
      45,     0,    46,    47,    41,    42,     0,    43,     0,    33,
      34,    48,    49,    35,    36,    37,    38,    96,     0,     0,
       0,     0,     0,    39,     0,     0,    33,    34,     0,    40,
      35,    36,    37,    38,    41,    42,     0,    43,     0,     0,
      39,     0,     0,     0,    67,     0,    40,     0,     0,    68,
       0,    41,    42,     0,    43,    70,    71,    72,    73,    74,
      75,    76,    67,     0,     0,     0,     0,    68,     0,    77,
      78,   118,    69,    70,    71,    72,    73,    74,    75,    76,
      67,     0,     0,     0,     0,    68,     0,    77,    78,    88,
       0,    70,    71,    72,    73,    74,    75,    76,    67,     0,
       0,     0,     0,    68,    90,    77,    78,     0,     0,    70,
      71,    72,    73,    74,    75,    76,    67,     0,     0,     0,
       0,    68,     0,    77,    78,     0,    94,    70,    71,    72,
      73,    74,    75,    76,    67,     0,     0,     0,     0,    68,
       0,    77,    78,   111,     0,    70,    71,    72,    73,    74,
      75,    76,    67,     0,     0,     0,     0,    68,   113,    77,
      78,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      67,     0,     0,     0,     0,    68,   114,    77,    78,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    67,     0,
       0,     0,     0,    68,     0,    77,    78,     0,   116,    70,
      71,    72,    73,    74,    75,    76,    67,     0,     0,     0,
       0,    68,   119,    77,    78,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    67,     0,     0,     0,     0,    68,
     120,    77,    78,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    67,     0,     0,     0,     0,     0,     0,    77,
      78,     0,    67,    70,    71,    72,    73,     0,    75,    76,
      67,     0,     0,    70,    71,    72,    73,    77,    78,     0,
       0,    70,    71,    72,    73,     0,    75,    77,    78,    70,
      71,    72,    73,     0,     0,    77,    78,     0,     0,     0,
       0,     0,     0,    77,    78
};

static const yytype_int8 yycheck[] =
{
      22,     0,    18,    19,     6,     4,    15,    21,     7,    11,
       6,    20,    30,    31,    30,    31,    38,    39,    40,    14,
      19,    43,    12,    10,    14,    47,     0,    26,     0,     1,
       3,    33,    34,     4,     6,    10,    50,    33,    34,   119,
     120,    63,    64,    11,   124,    67,    68,    14,    70,    71,
      72,    73,    74,    75,    76,    69,    78,    79,    80,     4,
      59,    33,    34,    11,    53,    54,    15,    10,    10,    10,
      10,    32,    94,    11,    13,     3,     4,    14,     6,     7,
       8,     9,    10,    14,    12,     4,     7,    14,    17,    17,
      25,    94,    28,    59,   116,    23,    24,   116,    26,    27,
      28,    29,    -1,    31,    -1,    33,    34,    35,    36,     3,
       4,    -1,    -1,     7,     8,     9,    10,    -1,    12,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    23,
      24,    -1,    26,    27,    28,    29,    -1,    31,    -1,     3,
       4,    35,    36,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    17,    -1,    -1,     3,     4,    -1,    23,
       7,     8,     9,    10,    28,    29,    -1,    31,    -1,    -1,
      17,    -1,    -1,    -1,     5,    -1,    23,    -1,    -1,    10,
      -1,    28,    29,    -1,    31,    16,    17,    18,    19,    20,
      21,    22,     5,    -1,    -1,    -1,    -1,    10,    -1,    30,
      31,    32,    15,    16,    17,    18,    19,    20,    21,    22,
       5,    -1,    -1,    -1,    -1,    10,    -1,    30,    31,    14,
      -1,    16,    17,    18,    19,    20,    21,    22,     5,    -1,
      -1,    -1,    -1,    10,    11,    30,    31,    -1,    -1,    16,
      17,    18,    19,    20,    21,    22,     5,    -1,    -1,    -1,
      -1,    10,    -1,    30,    31,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,     5,    -1,    -1,    -1,    -1,    10,
      -1,    30,    31,    14,    -1,    16,    17,    18,    19,    20,
      21,    22,     5,    -1,    -1,    -1,    -1,    10,    11,    30,
      31,    -1,    -1,    16,    17,    18,    19,    20,    21,    22,
       5,    -1,    -1,    -1,    -1,    10,    11,    30,    31,    -1,
      -1,    16,    17,    18,    19,    20,    21,    22,     5,    -1,
      -1,    -1,    -1,    10,    -1,    30,    31,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,     5,    -1,    -1,    -1,
      -1,    10,    11,    30,    31,    -1,    -1,    16,    17,    18,
      19,    20,    21,    22,     5,    -1,    -1,    -1,    -1,    10,
      11,    30,    31,    -1,    -1,    16,    17,    18,    19,    20,
      21,    22,     5,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,     5,    16,    17,    18,    19,    -1,    21,    22,
       5,    -1,    -1,    16,    17,    18,    19,    30,    31,    -1,
      -1,    16,    17,    18,    19,    -1,    21,    30,    31,    16,
      17,    18,    19,    -1,    -1,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    33,    34,    42,    43,    44,    45,    14,
      10,    45,     0,    43,     4,    46,    47,    48,     3,    10,
      14,    15,    20,    12,    14,    51,    11,    11,    45,    49,
      50,     4,    46,     3,     4,     7,     8,     9,    10,    17,
      23,    28,    29,    31,    56,    24,    26,    27,    35,    36,
      45,    51,    52,    53,    54,    56,    45,    47,    11,    15,
      56,    56,    56,    10,    10,    55,    56,     5,    10,    15,
      16,    17,    18,    19,    20,    21,    22,    30,    31,    10,
      10,    56,    14,    14,    46,    13,    52,    52,    14,    49,
      11,    56,    56,    32,    15,    56,    11,    56,    57,    46,
      56,    56,    56,    56,    56,    56,    56,     4,    56,    56,
      56,    14,    14,    11,    11,    55,    15,    11,    32,    11,
      11,    57,    53,    53,    25,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    45,
      45,    45,    46,    46,    46,    46,    47,    48,    48,    49,
      49,    50,    51,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    55,    55,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     3,     3,     2,     1,
       5,     2,     1,     3,     3,     5,     1,     4,     3,     1,
       3,     2,     3,     0,     2,     2,     2,     1,     2,     2,
       3,     5,     7,     5,     3,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     4,
       3,     4,     4,     3,     3,     1,     1,     1,     1,     1,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 63 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyvsp[0].astnode)->recursive_print(0);
        /* semantic_Analysis0($1); */
    }
#line 1517 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 3:
#line 71 "mini_c.yxx" /* yacc.c:1652  */
    {(yyval.astnode)=NULL;}
#line 1523 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 4:
#line 72 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_MASTER_LIST,(yyvsp[-1].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1531 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 5:
#line 78 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_GLOBAL_VAR,(yyvsp[-2].astnode),(yyvsp[-1].astnode),NULL,yylineno);
    }
#line 1539 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 6:
#line 81 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_FUNC_DECL,(yyvsp[-2].astnode),(yyvsp[-1].astnode),NULL,yylineno);
    }
#line 1547 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 7:
#line 84 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_FUNC_DEF,(yyvsp[-2].astnode),(yyvsp[-1].astnode),(yyvsp[0].astnode),yylineno);
    }
#line 1555 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 8:
#line 87 "mini_c.yxx" /* yacc.c:1652  */
    {(yyval.astnode)=NULL;}
#line 1561 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 9:
#line 90 "mini_c.yxx" /* yacc.c:1652  */
    { (yyval.astnode)=new ASTNode(TYPE_TYPESPEC,NULL,NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string((yyvsp[0].identifier));
    }
#line 1569 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 10:
#line 93 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_COMPLEX, (yyvsp[0].astnode), NULL, NULL, yylineno);
        (yyval.astnode)->data.identifier = string("array");
        (yyval.astnode)->data.literal_int = (yyvsp[-2].literal_int);
    }
#line 1579 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 11:
#line 98 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_COMPLEX, (yyvsp[0].astnode), NULL, NULL, yylineno);
        (yyval.astnode)->data.identifier = string("pointer");
    }
#line 1588 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 12:
#line 105 "mini_c.yxx" /* yacc.c:1652  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1594 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 13:
#line 106 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_INITIALIZER,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1602 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 14:
#line 109 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_VAR_DECLIST,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1610 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 15:
#line 112 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_INITIALIZER,(yyvsp[-4].astnode),(yyvsp[-2].astnode),(yyvsp[0].astnode),yylineno);
    }
#line 1618 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 16:
#line 117 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_VARNAME,NULL,NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string((yyvsp[0].identifier));
    }
#line 1627 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 17:
#line 124 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_FUNC_PROTO,(yyvsp[-1].astnode),NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string((yyvsp[-3].identifier));
    }
#line 1636 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 18:
#line 128 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_FUNC_PROTO,NULL,NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string((yyvsp[-2].identifier));
    }
#line 1645 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 19:
#line 134 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_PARAM_LIST,(yyvsp[0].astnode),NULL,NULL,yylineno);
    }
#line 1653 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 20:
#line 137 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_PARAM_LIST,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1661 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 21:
#line 142 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_PARAM,(yyvsp[-1].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1669 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 22:
#line 147 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_STMTBLK, (yyvsp[-1].astnode), NULL, NULL, yylineno);
    }
#line 1677 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 23:
#line 152 "mini_c.yxx" /* yacc.c:1652  */
    {(yyval.astnode)=NULL;}
#line 1683 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 24:
#line 153 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_STMTLIST,(yyvsp[-1].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1691 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 25:
#line 156 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_STMTLIST,(yyvsp[-1].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1699 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 26:
#line 162 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_EXPR,(yyvsp[-1].astnode),NULL,NULL,yylineno);
    }
#line 1707 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 27:
#line 165 "mini_c.yxx" /* yacc.c:1652  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1713 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 28:
#line 166 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_BREAK, NULL, NULL, NULL, yylineno);
    }
#line 1721 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 29:
#line 169 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_CONTINUE, NULL, NULL, NULL, yylineno);
    }
#line 1729 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 30:
#line 172 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_RETURN,(yyvsp[-1].astnode),NULL,NULL,yylineno);
    }
#line 1737 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 31:
#line 175 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_IFTRUE,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1745 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 32:
#line 178 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_IF,(yyvsp[-4].astnode),(yyvsp[-2].astnode),(yyvsp[0].astnode),yylineno);
    }
#line 1753 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 33:
#line 181 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_WHILE,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1761 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 34:
#line 191 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_VARDEF,(yyvsp[-2].astnode),(yyvsp[-1].astnode),NULL,yylineno);
    }
#line 1769 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 35:
#line 196 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_INITLIST, (yyvsp[-2].astnode), (yyvsp[0].astnode), NULL, yylineno);
    }
#line 1777 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 36:
#line 199 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode) = (yyvsp[0].astnode);
    }
#line 1785 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 37:
#line 204 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
        (yyval.astnode)->data.identifier = string("assign");
    }
#line 1794 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 38:
#line 208 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
        (yyval.astnode)->data.identifier = string("and");
    }
#line 1803 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 39:
#line 212 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
        (yyval.astnode)->data.identifier = string("OR");
    }
#line 1812 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 40:
#line 216 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
        (yyval.astnode)->data.identifier = string((yyvsp[-1].identifier));
    }
#line 1821 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 41:
#line 220 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
        (yyval.astnode)->data.identifier = string("plus");
    }
#line 1830 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 42:
#line 224 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
        (yyval.astnode)->data.identifier = string("minus");
    }
#line 1839 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 43:
#line 228 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
        (yyval.astnode)->data.identifier = string("multiply");
    }
#line 1848 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 44:
#line 232 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
        (yyval.astnode)->data.identifier = string("divide");
    }
#line 1857 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 45:
#line 236 "mini_c.yxx" /* yacc.c:1652  */
    {(yyval.astnode)=(yyvsp[-1].astnode);}
#line 1863 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 46:
#line 237 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[0].astnode),NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string("negate");
    }
#line 1872 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 47:
#line 241 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[0].astnode),NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string("not");
    }
#line 1881 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 48:
#line 245 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-1].astnode),NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string("dereference");
    }
#line 1890 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 49:
#line 249 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-1].astnode),NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string("address");
    }
#line 1899 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 50:
#line 253 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_OPERATOR,(yyvsp[-2].astnode),NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string("member");
        (yyval.astnode)->data.literal_string = string((yyvsp[0].identifier));
    }
#line 1909 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 51:
#line 258 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_ACCESS,(yyvsp[-3].astnode),(yyvsp[-1].astnode),NULL,yylineno);
    }
#line 1917 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 52:
#line 261 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_CALL,(yyvsp[-3].astnode),(yyvsp[-1].astnode),NULL,yylineno);
    }
#line 1925 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 53:
#line 264 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_CALL,(yyvsp[-2].astnode),NULL,NULL,yylineno);
    }
#line 1933 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 54:
#line 267 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=(yyvsp[-1].astnode);
    }
#line 1941 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 55:
#line 270 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_IDENTIFIER,NULL,NULL,NULL,yylineno);
        (yyval.astnode)->data.identifier = string((yyvsp[0].identifier));
    }
#line 1950 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 56:
#line 274 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_LITERAL_INTEGER,NULL,NULL,NULL,yylineno);
        (yyval.astnode)->data.literal_int=(yyvsp[0].literal_int);
    }
#line 1959 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 57:
#line 278 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_LITERAL_FLOAT,NULL,NULL,NULL,yylineno);
        (yyval.astnode)->data.literal_float=(yyvsp[0].literal_float);
    }
#line 1968 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 58:
#line 282 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_LITERAL_STRING,NULL,NULL,NULL,yylineno);
        (yyval.astnode)->data.literal_string=trim_string_quotes(string((yyvsp[0].literal_string)));
    }
#line 1977 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 59:
#line 286 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_LITERAL_INTEGER,NULL,NULL,NULL,yylineno);
        (yyval.astnode)->data.literal_int=extract_from_char_string((yyvsp[0].literal_string));
    }
#line 1986 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 60:
#line 292 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_ARGLIST,(yyvsp[-2].astnode),(yyvsp[0].astnode),NULL,yylineno);
    }
#line 1994 "mini_c.sem.cc" /* yacc.c:1652  */
    break;

  case 61:
#line 295 "mini_c.yxx" /* yacc.c:1652  */
    {
        (yyval.astnode)=new ASTNode(TYPE_ARGLIST,(yyvsp[0].astnode),NULL,NULL,yylineno);
    }
#line 2002 "mini_c.sem.cc" /* yacc.c:1652  */
    break;


#line 2006 "mini_c.sem.cc" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 300 "mini_c.yxx" /* yacc.c:1918  */


void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}
