
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

    #include "semantic.h"
    #include "code_generation.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>
    #include <stdbool.h>
    #include "parser.tab.h"

    extern int yylineno;

    int syntax_error = 0;
    FILE* f;
	int yylex(void);
	// Expression Nodes
	nodeType *opr(int oper, int nops, ...);
	nodeType *id(char* i, char* type);
	nodeType *constNode(char* i);
	nodeType *conInt(int value);
	nodeType *conFloat(double value);
	nodeType *conBool(int value);
	nodeType *conString(char* value);
    

    SymbolTable* initialize_global_symbol_table(struct SymbolTable* global_symbol_table, struct SymbolTable* current_symbol_table);
    void create_symbol_table(SymbolTable** current_symbol_table);
    Symbol* insert_symbol(SymbolTable* table, char* name, char* type, char* kind);
    Symbol* lookup_symbol(SymbolTable* table, char* name);
    Symbol* lookup_symbol_same_scope(SymbolTable* table, char* name);
    int variable_redeclaration_val(SymbolTable* table, char* name);
    void track_scope(SymbolTable* t);
    void cleanup_all_symbol_tables();
    // for memory-usage

    void track_scope(SymbolTable* t);
    void cleanup_all_symbol_tables();

    // nodeType *cond(int oper, int nops, ...);

	void freeNode(nodeType *p);
	void yyerror(const char *msg);

    // Graph functions
    int ex (nodeType *p);

    nodeType* topNode = NULL;


/* Line 189 of yacc.c  */
#line 123 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GLOBAL_LIST = 258,
     WHILE = 259,
     REPEATUNTIL = 260,
     SWITCH = 261,
     CASE = 262,
     DEFAULT = 263,
     BREAK = 264,
     CONTINUE = 265,
     RETURN = 266,
     TERNARY = 267,
     COLON = 268,
     SL = 269,
     S = 270,
     BLOCK = 271,
     COND = 272,
     ITER_BODY = 273,
     FOR = 274,
     FOR_COND = 275,
     FOR_INIT = 276,
     FOR_STEP = 277,
     FOR_TERM = 278,
     COMMA = 279,
     FUNC = 280,
     FUNC_ARG_LIST = 281,
     FUNC_BODY = 282,
     FUNC_ARG = 283,
     FUNC_CALL = 284,
     ARG_VALUES = 285,
     ARG_VALUE = 286,
     FUNC_ID = 287,
     IF = 288,
     ELSE = 289,
     IFELSE = 290,
     SWITCH_BODY = 291,
     SWITCH_CASES = 292,
     SWITCH_CASE = 293,
     DEFAULT_CASE = 294,
     SWITCH_VAR = 295,
     INCREMENT_PREFIX = 296,
     INCREMENT_POSTFIX = 297,
     DECREMENT_POSTFIX = 298,
     DECREMENT_PREFIX = 299,
     KW_VAR = 300,
     KW_CONST = 301,
     KW_FUNC = 302,
     KW_INT = 303,
     KW_FLOAT = 304,
     KW_BOOL = 305,
     KW_STRING = 306,
     KW_VOID = 307,
     IDENTIFIER = 308,
     STRING = 309,
     INTEGER = 310,
     FLOAT = 311,
     BOOLEAN = 312,
     PLUS = 313,
     MINUS = 314,
     STAR = 315,
     SLASH = 316,
     PERCENT = 317,
     EQ = 318,
     NEQ = 319,
     LT = 320,
     GT = 321,
     LE = 322,
     GE = 323,
     AND = 324,
     OR = 325,
     NOT = 326,
     ASSIGN = 327,
     SEMICOLON = 328,
     LPAREN = 329,
     RPAREN = 330,
     LBRACE = 331,
     RBRACE = 332,
     PLUS_ASSIGN = 333,
     MINUS_ASSIGN = 334,
     STAR_ASSIGN = 335,
     SLASH_ASSIGN = 336,
     BIT_AND = 337,
     BIT_OR = 338,
     BIT_XOR = 339,
     BIT_NOT = 340,
     SHIFT_LEFT = 341,
     SHIFT_RIGHT = 342,
     INCREMENT = 343,
     DECREMENT = 344,
     LOWER_THAN_ELSE = 345
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 51 "parser.y"

	int intValue;
	float floatValue;
	int boolValue;
	char* stringValue;
    nodeType* nodeValue;



/* Line 214 of yacc.c  */
#line 259 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 284 "parser.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   791

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNRULES -- Number of states.  */
#define YYNSTATES  224

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   345

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    14,    18,    21,
      25,    27,    30,    33,    36,    38,    40,    42,    45,    48,
      52,    56,    59,    62,    65,    69,    73,    77,    81,    85,
      89,    93,    97,   101,   105,   108,   111,   114,   117,   122,
     127,   132,   137,   139,   141,   143,   145,   147,   149,   151,
     155,   159,   163,   167,   171,   175,   179,   183,   187,   191,
     195,   199,   203,   207,   211,   215,   218,   222,   226,   230,
     234,   237,   241,   245,   248,   254,   260,   266,   272,   278,
     284,   286,   292,   294,   296,   298,   300,   302,   304,   306,
     308,   314,   320,   323,   328,   332,   334,   335,   338,   341,
     343,   347,   349,   350,   352,   354,   356,   360,   362,   368,
     376,   382,   384,   386,   388,   393,   397,   400,   402,   407,
     412,   414,   416,   418,   420
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      92,     0,    -1,    93,    -1,    -1,   110,    -1,    93,   110,
      -1,    96,    73,    -1,    93,    96,    73,    -1,    99,    73,
      -1,    93,    99,    73,    -1,    95,    -1,    94,    95,    -1,
      96,    73,    -1,    99,    73,    -1,   119,    -1,   102,    -1,
     101,    -1,     9,    73,    -1,    10,    73,    -1,    11,   100,
      73,    -1,    11,   111,    73,    -1,    11,    73,    -1,   111,
      73,    -1,   109,    53,    -1,    53,    72,   100,    -1,    53,
      72,   111,    -1,    53,    78,   100,    -1,    53,    78,   111,
      -1,    53,    79,   100,    -1,    53,    79,   111,    -1,    53,
      80,   100,    -1,    53,    80,   111,    -1,    53,    81,   100,
      -1,    53,    81,   111,    -1,    88,   100,    -1,    89,   100,
      -1,   100,    88,    -1,   100,    89,    -1,    46,    53,    72,
     100,    -1,    46,    53,    72,   111,    -1,   109,    53,    72,
     100,    -1,   109,    53,    72,   111,    -1,    98,    -1,    97,
      -1,    55,    -1,    56,    -1,    53,    -1,    54,    -1,    57,
      -1,   100,    58,   100,    -1,   100,    59,   100,    -1,   100,
      60,   100,    -1,   100,    61,   100,    -1,   100,    62,   100,
      -1,   100,    63,   100,    -1,   100,    64,   100,    -1,   100,
      65,   100,    -1,   100,    66,   100,    -1,   100,    67,   100,
      -1,   100,    68,   100,    -1,   100,    69,   100,    -1,   100,
      70,   100,    -1,   100,    82,   100,    -1,   100,    83,   100,
      -1,   100,    84,   100,    -1,    85,   100,    -1,   100,    86,
      55,    -1,   100,    87,    55,    -1,   100,    86,    53,    -1,
     100,    87,    53,    -1,    71,   100,    -1,    74,   100,    75,
      -1,    76,    94,    77,    -1,    76,    77,    -1,     4,    74,
     103,    75,   108,    -1,     4,    74,   103,    75,    73,    -1,
       5,    74,   103,    75,   108,    -1,     5,    74,   103,    75,
      73,    -1,    19,    74,   104,    75,   108,    -1,    19,    74,
     104,    75,    73,    -1,   100,    -1,   105,    73,   106,    73,
     107,    -1,    98,    -1,   100,    -1,    97,    -1,    95,    -1,
      50,    -1,    48,    -1,    49,    -1,    51,    -1,   113,    74,
     112,    75,   118,    -1,   113,    74,   112,    75,    73,    -1,
     111,    73,    -1,   114,    74,   115,    75,    -1,   112,    24,
     117,    -1,   117,    -1,    -1,   109,    53,    -1,    52,    53,
      -1,    53,    -1,   115,    24,   116,    -1,   116,    -1,    -1,
     126,    -1,    53,    -1,    96,    -1,    96,    72,   126,    -1,
     101,    -1,    33,    74,   103,    75,   120,    -1,    33,    74,
     103,    75,   120,    34,   121,    -1,     6,    74,   122,    75,
     123,    -1,    95,    -1,    95,    -1,    53,    -1,    76,   124,
     127,    77,    -1,    76,   124,    77,    -1,   124,   125,    -1,
     125,    -1,     7,   126,    13,    94,    -1,     7,   126,    13,
     125,    -1,    55,    -1,    56,    -1,    54,    -1,    57,    -1,
       8,    13,    94,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   106,   110,   111,   112,   113,   114,   115,
     119,   120,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   138,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   159,   160,
     161,   162,   166,   167,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   202,   203,   207,   208,   209,   210,   211,   212,
     216,   220,   224,   228,   232,   236,   240,   241,   242,   243,
     247,   248,   249,   253,   257,   258,   259,   263,   264,   268,
     272,   273,   274,   278,   279,   283,   284,   288,   292,   293,
     294,   298,   302,   306,   310,   311,   315,   316,   320,   321,
     325,   326,   327,   328,   332
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GLOBAL_LIST", "WHILE", "REPEATUNTIL",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "TERNARY",
  "COLON", "SL", "S", "BLOCK", "COND", "ITER_BODY", "FOR", "FOR_COND",
  "FOR_INIT", "FOR_STEP", "FOR_TERM", "COMMA", "FUNC", "FUNC_ARG_LIST",
  "FUNC_BODY", "FUNC_ARG", "FUNC_CALL", "ARG_VALUES", "ARG_VALUE",
  "FUNC_ID", "IF", "ELSE", "IFELSE", "SWITCH_BODY", "SWITCH_CASES",
  "SWITCH_CASE", "DEFAULT_CASE", "SWITCH_VAR", "INCREMENT_PREFIX",
  "INCREMENT_POSTFIX", "DECREMENT_POSTFIX", "DECREMENT_PREFIX", "KW_VAR",
  "KW_CONST", "KW_FUNC", "KW_INT", "KW_FLOAT", "KW_BOOL", "KW_STRING",
  "KW_VOID", "IDENTIFIER", "STRING", "INTEGER", "FLOAT", "BOOLEAN", "PLUS",
  "MINUS", "STAR", "SLASH", "PERCENT", "EQ", "NEQ", "LT", "GT", "LE", "GE",
  "AND", "OR", "NOT", "ASSIGN", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "PLUS_ASSIGN", "MINUS_ASSIGN", "STAR_ASSIGN", "SLASH_ASSIGN",
  "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT", "SHIFT_LEFT", "SHIFT_RIGHT",
  "INCREMENT", "DECREMENT", "LOWER_THAN_ELSE", "$accept", "program",
  "global_list", "statement_list", "statement", "declaration_statement",
  "reassignment_statement", "initialized_statement",
  "assignment_statement", "expression", "block_statement",
  "iterative_statement", "condition", "for_condition", "for_init",
  "for_terminate", "for_step", "iter_body", "type_keyword",
  "function_statement", "function_call", "function_arguments",
  "function_def_id", "function_id", "arguments_values", "argument_value",
  "function_argument", "function_body", "conditional_statement", "if_body",
  "else_body", "switch_variable", "switch_body", "switch_cases",
  "single_case", "case_value", "default_case", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    93,    93,    93,    93,    93,    93,
      94,    94,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      98,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   102,   102,   102,   102,   102,   102,
     103,   104,   105,   106,   107,   108,   109,   109,   109,   109,
     110,   110,   110,   111,   112,   112,   112,   113,   113,   114,
     115,   115,   115,   116,   116,   117,   117,   118,   119,   119,
     119,   120,   121,   122,   123,   123,   124,   124,   125,   125,
     126,   126,   126,   126,   127
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     2,     3,     2,     3,
       1,     2,     2,     2,     1,     1,     1,     2,     2,     3,
       3,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       2,     3,     3,     2,     5,     5,     5,     5,     5,     5,
       1,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     5,     2,     4,     3,     1,     0,     2,     2,     1,
       3,     1,     0,     1,     1,     1,     3,     1,     5,     7,
       5,     1,     1,     1,     4,     3,     2,     1,     4,     4,
       1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    87,    88,    86,    89,     0,    46,    47,    44,
      45,    48,     0,     0,     0,     0,     0,     0,     2,     0,
      43,    42,     0,     0,     0,     4,     0,     0,     0,     0,
      98,     0,     0,     0,     0,     0,    46,    70,     0,    65,
      34,    35,     1,     0,     0,     5,     6,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    23,    92,
      96,   102,     0,    46,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    71,     7,     9,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    68,    66,    69,    67,     0,   105,     0,
       0,    95,   104,   122,   120,   121,   123,     0,   101,   103,
      38,    39,    40,    41,     0,    23,     0,     0,     0,    93,
     106,    94,    91,     0,   107,    90,   100,     0,     0,     0,
       0,     0,     0,     0,     0,    73,     0,    10,     0,     0,
      16,    15,     0,     0,    14,     0,     0,     0,    17,    18,
      21,     0,     0,     0,     0,    72,    11,    12,    13,    23,
      22,    80,     0,     0,   113,     0,    19,    20,    82,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,    85,    74,    77,    76,     0,   110,    79,    78,    83,
       0,   111,   108,     0,     0,   117,     0,     0,     0,     0,
     115,   116,     0,    46,    84,    81,   112,   109,     0,     0,
     114,   118,   119,   124
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,   146,   147,   148,    20,    21,   149,    23,
     150,   151,   172,   179,   180,   200,   215,   192,   152,    25,
     153,   110,    27,    28,   117,   118,   111,   135,   154,   202,
     217,   175,   196,   204,   205,   119,   212
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -193
static const yytype_int16 yypact[] =
{
     455,     0,  -193,  -193,  -193,  -193,    10,    24,  -193,  -193,
    -193,  -193,   240,   240,   240,   240,   240,    90,   455,    27,
    -193,  -193,    36,   499,    57,  -193,    41,    54,    64,    53,
    -193,   298,   298,   298,   298,   298,  -193,  -193,   531,  -193,
     591,   591,  -193,    69,    81,  -193,  -193,  -193,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   -20,    46,  -193,  -193,    77,  -193,
      86,    66,   298,    65,   591,  -193,   591,  -193,   591,  -193,
     591,  -193,   591,  -193,  -193,  -193,  -193,    -3,    -3,  -193,
    -193,  -193,    21,    21,   -31,   -31,   -31,   -31,   633,   621,
     704,   663,   674,  -193,  -193,  -193,  -193,   298,    78,   106,
     -14,  -193,  -193,  -193,  -193,  -193,  -193,   -13,  -193,  -193,
     591,  -193,   591,  -193,    91,  -193,    86,    51,    66,  -193,
    -193,  -193,  -193,   107,  -193,  -193,  -193,    94,    99,   100,
     109,   112,   202,   113,   114,  -193,   161,  -193,   116,   117,
    -193,  -193,   133,   118,  -193,   240,   240,   140,  -193,  -193,
    -193,   561,   124,   -33,   240,  -193,  -193,  -193,  -193,   126,
    -193,   591,   125,   127,  -193,   128,  -193,  -193,  -193,   129,
     132,   146,   131,   215,   273,   137,   331,   240,   126,   443,
    -193,  -193,  -193,  -193,  -193,   194,  -193,  -193,  -193,   591,
     135,  -193,   188,    91,     1,  -193,   467,   443,   210,   214,
    -193,  -193,   151,    -8,  -193,  -193,  -193,  -193,   389,   443,
    -193,   443,  -193,   443
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -193,  -193,  -193,  -144,   -92,     7,    23,    67,    14,   -12,
     104,  -193,   -71,  -193,  -193,  -193,  -193,    -7,     6,   218,
      34,  -193,  -193,  -193,  -193,   105,   115,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -192,  -119,  -193
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -100
static const yytype_int16 yytable[] =
{
      37,    38,    39,    40,    41,   130,    24,    19,   203,   209,
     126,   128,   211,     1,    22,     2,     3,     4,     5,    74,
      76,    78,    80,    82,    24,    43,   222,    48,    49,    50,
      51,    52,    44,   103,    26,   104,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,    26,    29,   166,    64,    65,    50,    51,    52,
     120,   127,   129,    30,    31,    75,    77,    79,    81,    83,
      32,    33,    34,    35,   221,   223,   109,   108,   210,    48,
      49,    50,    51,    52,   208,   173,    55,    56,    57,    58,
      42,   191,   191,   182,   191,   122,    31,   201,   -99,   105,
      46,   106,    32,    33,    34,    35,   121,    64,    65,    47,
      68,   137,   138,   139,    69,   216,   140,   141,   142,   112,
     113,   114,   115,   116,   132,    72,   143,   133,    70,   166,
     161,   166,   109,   108,     2,     3,     4,     5,    71,   -99,
     144,   123,    85,   171,   171,   113,   114,   115,   116,   107,
     124,   -97,   171,     1,    86,     2,     3,     4,     5,   125,
       7,     8,     9,    10,    11,   137,   138,   139,   155,   181,
     140,   141,   142,   156,   157,   199,   162,   194,    12,   198,
     143,    13,   158,   133,   145,   159,   169,   163,   164,   167,
     168,   170,    14,   174,   144,    15,    16,   177,   107,   188,
     183,   203,   184,   185,   186,   187,   189,     1,   206,     2,
       3,     4,     5,   195,     7,     8,     9,    10,    11,   137,
     138,   139,   207,   218,   140,   141,   142,   219,   220,   214,
     178,   134,    12,   136,   143,    13,    45,   133,   165,     0,
       0,   131,     0,     0,     0,     0,    14,     0,   144,    15,
      16,     0,     0,     0,     0,    73,     8,     9,    10,    11,
       0,     1,     0,     2,     3,     4,     5,     0,     7,     8,
       9,    10,    11,    12,     0,   160,    13,   137,   138,   139,
       0,     0,   140,   141,   142,     0,    12,    14,   190,    13,
       0,   133,   143,    36,     8,     9,    10,    11,     0,     0,
      14,     0,     0,    15,    16,     0,   144,     0,     0,     0,
       0,    12,     0,     0,    13,     0,     0,     0,     0,     1,
       0,     2,     3,     4,     5,    14,     7,     8,     9,    10,
      11,     0,     0,     0,     0,   137,   138,   139,     0,     0,
     140,   141,   142,     0,    12,     0,   193,    13,     0,   133,
     143,    73,     8,     9,    10,    11,     0,     0,    14,     0,
       0,    15,    16,     0,   144,     0,     0,     0,     0,    12,
       0,     0,    13,     0,     0,     0,     0,     1,     0,     2,
       3,     4,     5,    14,     7,     8,     9,    10,    11,     0,
       0,     0,     0,   137,   138,   139,   203,     0,   140,   141,
     142,     0,    12,     0,   197,    13,     0,   133,   143,     0,
       0,     0,     0,     0,     0,     0,    14,     0,     0,    15,
      16,     0,   144,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     2,     3,     4,
       5,     0,     7,     8,     9,    10,    11,   137,   138,   139,
       0,     0,   140,   141,   142,     0,     0,     0,     0,     0,
      12,     0,   143,    13,     0,   133,     0,     0,     0,     0,
       0,     0,     0,     0,    14,     0,   144,    15,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     2,     3,     4,     5,     0,     7,     8,     9,    10,
      11,     1,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,     0,    12,     0,     0,    13,     0,   133,
     213,     8,     9,    10,    11,     0,    12,     0,    14,    13,
       0,    15,    16,     0,     0,     0,     0,     0,    12,     0,
      14,    13,     0,    15,    16,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,    15,    16,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,     0,    64,    65,    66,    67,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,    61,    62,    63,     0,    64,    65,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,     0,    64,    65,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,     0,    64,    65,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,     0,    61,    62,    63,     0,    64,    65,     0,
       0,     0,     0,     0,     0,    61,    62,    63,     0,    64,
      65,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,     0,    61,     0,    63,     0,    64,
      65,     0,     0,     0,     0,     0,    61,     0,     0,     0,
      64,    65,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,    65
};

static const yytype_int16 yycheck[] =
{
      12,    13,    14,    15,    16,   124,     0,     0,     7,     8,
      24,    24,   204,    46,     0,    48,    49,    50,    51,    31,
      32,    33,    34,    35,    18,    18,   218,    58,    59,    60,
      61,    62,    18,    53,     0,    55,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    18,    53,   146,    86,    87,    60,    61,    62,
      72,    75,    75,    53,    72,    31,    32,    33,    34,    35,
      78,    79,    80,    81,   218,   219,    70,    70,    77,    58,
      59,    60,    61,    62,   203,   156,    65,    66,    67,    68,
       0,   183,   184,   164,   186,   107,    72,   189,    74,    53,
      73,    55,    78,    79,    80,    81,    72,    86,    87,    73,
      53,     4,     5,     6,    73,   207,     9,    10,    11,    53,
      54,    55,    56,    57,    73,    72,    19,    76,    74,   221,
     142,   223,   126,   126,    48,    49,    50,    51,    74,    74,
      33,   107,    73,   155,   156,    54,    55,    56,    57,    72,
      72,    74,   164,    46,    73,    48,    49,    50,    51,    53,
      53,    54,    55,    56,    57,     4,     5,     6,    74,   163,
       9,    10,    11,    74,    74,   187,   142,   184,    71,   186,
      19,    74,    73,    76,    77,    73,    53,    74,    74,    73,
      73,    73,    85,    53,    33,    88,    89,    73,    72,    53,
      75,     7,    75,    75,    75,    73,    75,    46,    73,    48,
      49,    50,    51,    76,    53,    54,    55,    56,    57,     4,
       5,     6,    34,    13,     9,    10,    11,    13,    77,   206,
     163,   127,    71,   128,    19,    74,    18,    76,    77,    -1,
      -1,   126,    -1,    -1,    -1,    -1,    85,    -1,    33,    88,
      89,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      -1,    46,    -1,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    71,    -1,    73,    74,     4,     5,     6,
      -1,    -1,     9,    10,    11,    -1,    71,    85,    73,    74,
      -1,    76,    19,    53,    54,    55,    56,    57,    -1,    -1,
      85,    -1,    -1,    88,    89,    -1,    33,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    74,    -1,    -1,    -1,    -1,    46,
      -1,    48,    49,    50,    51,    85,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    -1,     4,     5,     6,    -1,    -1,
       9,    10,    11,    -1,    71,    -1,    73,    74,    -1,    76,
      19,    53,    54,    55,    56,    57,    -1,    -1,    85,    -1,
      -1,    88,    89,    -1,    33,    -1,    -1,    -1,    -1,    71,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    46,    -1,    48,
      49,    50,    51,    85,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,     4,     5,     6,     7,    -1,     9,    10,
      11,    -1,    71,    -1,    73,    74,    -1,    76,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,    88,
      89,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,     4,     5,     6,
      -1,    -1,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    19,    74,    -1,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    -1,    33,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    71,    -1,    -1,    74,    -1,    76,
      53,    54,    55,    56,    57,    -1,    71,    -1,    85,    74,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      85,    74,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    -1,    -1,    88,    89,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    83,    84,    -1,    86,    87,    88,    89,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    84,    -1,    86,    87,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    84,    -1,    86,    87,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    84,    -1,    86,    87,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    82,    83,    84,    -1,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    83,    84,    -1,    86,
      87,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    -1,    82,    -1,    84,    -1,    86,
      87,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      86,    87,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    46,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    71,    74,    85,    88,    89,    92,    93,    96,
      97,    98,    99,   100,   109,   110,   111,   113,   114,    53,
      53,    72,    78,    79,    80,    81,    53,   100,   100,   100,
     100,   100,     0,    96,    99,   110,    73,    73,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    82,    83,    84,    86,    87,    88,    89,    53,    73,
      74,    74,    72,    53,   100,   111,   100,   111,   100,   111,
     100,   111,   100,   111,    75,    73,    73,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,    53,    55,    53,    55,    72,    96,   109,
     112,   117,    53,    54,    55,    56,    57,   115,   116,   126,
     100,   111,   100,   111,    72,    53,    24,    75,    24,    75,
     126,   117,    73,    76,   101,   118,   116,     4,     5,     6,
       9,    10,    11,    19,    33,    77,    94,    95,    96,    99,
     101,   102,   109,   111,   119,    74,    74,    74,    73,    73,
      73,   100,   111,    74,    74,    77,    95,    73,    73,    53,
      73,   100,   103,   103,    53,   122,    73,    73,    98,   104,
     105,   109,   103,    75,    75,    75,    75,    73,    53,    75,
      73,    95,   108,    73,   108,    76,   123,    73,   108,   100,
     106,    95,   120,     7,   124,   125,    73,    34,   126,     8,
      77,   125,   127,    53,    97,   107,    95,   121,    13,    13,
      77,    94,   125,    94
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
	    /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    { topNode=(yyvsp[(1) - (1)].nodeValue);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    { (yyval.nodeValue) = opr(GLOBAL_LIST, 1, (yyvsp[(1) - (1)].nodeValue)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    { (yyval.nodeValue) = opr(GLOBAL_LIST, 2, (yyvsp[(1) - (2)].nodeValue), (yyvsp[(2) - (2)].nodeValue)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    { (yyval.nodeValue) = opr(GLOBAL_LIST, 1, (yyvsp[(1) - (2)].nodeValue)); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    { (yyval.nodeValue) = opr(GLOBAL_LIST, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(2) - (3)].nodeValue)); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 114 "parser.y"
    { (yyval.nodeValue) = opr(GLOBAL_LIST, 1, (yyvsp[(1) - (2)].nodeValue)); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    { (yyval.nodeValue) = opr(GLOBAL_LIST, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(2) - (3)].nodeValue)); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    { (yyval.nodeValue) = opr(SL, 2, (yyvsp[(1) - (2)].nodeValue), (yyvsp[(2) - (2)].nodeValue)); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (2)].nodeValue); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (2)].nodeValue); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 126 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 127 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { (yyval.nodeValue) = opr(BREAK, 0); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 129 "parser.y"
    { (yyval.nodeValue) = opr(CONTINUE, 0); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    { (yyval.nodeValue) = opr(RETURN, 1, (yyvsp[(2) - (3)].nodeValue)); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { (yyval.nodeValue) = opr(RETURN, 1, (yyvsp[(2) - (3)].nodeValue)); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    { (yyval.nodeValue) = opr(RETURN, 0); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (2)].nodeValue); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    { (yyval.nodeValue) = id((yyvsp[(2) - (2)].stringValue), (yyvsp[(1) - (2)].stringValue)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    { (yyval.nodeValue) = opr(ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 143 "parser.y"
    { (yyval.nodeValue) = opr(ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    { (yyval.nodeValue) = opr(PLUS_ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    { (yyval.nodeValue) = opr(PLUS_ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    { (yyval.nodeValue) = opr(MINUS_ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    { (yyval.nodeValue) = opr(MINUS_ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    { (yyval.nodeValue) = opr(STAR_ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    { (yyval.nodeValue) = opr(STAR_ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 150 "parser.y"
    { (yyval.nodeValue) = opr(SLASH_ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    { (yyval.nodeValue) = opr(SLASH_ASSIGN, 2, id((yyvsp[(1) - (3)].stringValue), "undefined"), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    { (yyval.nodeValue) = opr(INCREMENT_PREFIX, 1, (yyvsp[(2) - (2)].nodeValue)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    { (yyval.nodeValue) = opr(DECREMENT_PREFIX, 1, (yyvsp[(2) - (2)].nodeValue)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    { (yyval.nodeValue) = opr(INCREMENT_POSTFIX, 1, (yyvsp[(1) - (2)].nodeValue)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    { (yyval.nodeValue) = opr(DECREMENT_POSTFIX, 1, (yyvsp[(1) - (2)].nodeValue)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    { (yyval.nodeValue) = opr(ASSIGN, 2, constNode((yyvsp[(2) - (4)].stringValue)), (yyvsp[(4) - (4)].nodeValue)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    { (yyval.nodeValue) = opr(ASSIGN, 2, constNode((yyvsp[(2) - (4)].stringValue)), (yyvsp[(4) - (4)].nodeValue)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    { (yyval.nodeValue) = opr(ASSIGN, 2, id((yyvsp[(2) - (4)].stringValue), (yyvsp[(1) - (4)].stringValue)), (yyvsp[(4) - (4)].nodeValue)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 162 "parser.y"
    { (yyval.nodeValue) = opr(ASSIGN, 2, id((yyvsp[(2) - (4)].stringValue), (yyvsp[(1) - (4)].stringValue)), (yyvsp[(4) - (4)].nodeValue)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 166 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    { (yyval.nodeValue) = conInt((yyvsp[(1) - (1)].intValue));  ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 172 "parser.y"
    { (yyval.nodeValue) = conFloat((yyvsp[(1) - (1)].floatValue));  ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 173 "parser.y"
    { (yyval.nodeValue) = id((yyvsp[(1) - (1)].stringValue), "undefined");  ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 174 "parser.y"
    { (yyval.nodeValue) = conString((yyvsp[(1) - (1)].stringValue));  ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    { (yyval.nodeValue) = conBool((yyvsp[(1) - (1)].boolValue));  ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    { (yyval.nodeValue) = opr(PLUS, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    { (yyval.nodeValue) = opr(MINUS, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    { (yyval.nodeValue) = opr(STAR, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 179 "parser.y"
    { (yyval.nodeValue) = opr(SLASH, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 180 "parser.y"
    { (yyval.nodeValue) = opr(PERCENT, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 181 "parser.y"
    { (yyval.nodeValue) = opr(EQ, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    { (yyval.nodeValue) = opr(NEQ, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    { (yyval.nodeValue) = opr(LT, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    { (yyval.nodeValue) = opr(GT, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 185 "parser.y"
    { (yyval.nodeValue) = opr(LE, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    { (yyval.nodeValue) = opr(GE, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    { (yyval.nodeValue) = opr(AND, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyval.nodeValue) = opr(OR, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue));  ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    { (yyval.nodeValue) = opr(BIT_AND, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    { (yyval.nodeValue) = opr(BIT_OR, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    { (yyval.nodeValue) = opr(BIT_XOR, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    { (yyval.nodeValue) = opr(BIT_NOT, 1, (yyvsp[(2) - (2)].nodeValue)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    { (yyval.nodeValue) = opr(SHIFT_LEFT, 2, (yyvsp[(1) - (3)].nodeValue), conInt((yyvsp[(3) - (3)].intValue))); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    { (yyval.nodeValue) = opr(SHIFT_RIGHT, 2, (yyvsp[(1) - (3)].nodeValue), conInt((yyvsp[(3) - (3)].intValue))); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    { (yyval.nodeValue) = opr(SHIFT_LEFT, 2, (yyvsp[(1) - (3)].nodeValue), id((yyvsp[(3) - (3)].stringValue), "undefined")); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    { (yyval.nodeValue) = opr(SHIFT_RIGHT, 2, (yyvsp[(1) - (3)].nodeValue), id((yyvsp[(3) - (3)].stringValue), "undefined")); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    { (yyval.nodeValue) = opr(NOT, 1, (yyvsp[(2) - (2)].nodeValue));  ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 198 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(2) - (3)].nodeValue); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    { (yyval.nodeValue) = opr(BLOCK, 1, (yyvsp[(2) - (3)].nodeValue));  ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    { (yyval.nodeValue) = opr(BLOCK, 0);  ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    { (yyval.nodeValue) = opr(WHILE, 2, (yyvsp[(3) - (5)].nodeValue), (yyvsp[(5) - (5)].nodeValue));  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 208 "parser.y"
    { (yyval.nodeValue) = opr(WHILE, 1, (yyvsp[(3) - (5)].nodeValue));  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    { (yyval.nodeValue) = opr(REPEATUNTIL, 2, (yyvsp[(3) - (5)].nodeValue), (yyvsp[(5) - (5)].nodeValue));  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    { (yyval.nodeValue) = opr(REPEATUNTIL, 1, (yyvsp[(3) - (5)].nodeValue));  ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 211 "parser.y"
    { (yyval.nodeValue) = opr(FOR, 2, (yyvsp[(3) - (5)].nodeValue), (yyvsp[(5) - (5)].nodeValue));  ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    { (yyval.nodeValue) = opr(FOR, 1, (yyvsp[(3) - (5)].nodeValue));  ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 216 "parser.y"
    { (yyval.nodeValue) = opr(COND, 1, (yyvsp[(1) - (1)].nodeValue)); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 220 "parser.y"
    { (yyval.nodeValue) = opr(FOR_COND, 3, (yyvsp[(1) - (5)].nodeValue), (yyvsp[(3) - (5)].nodeValue), (yyvsp[(5) - (5)].nodeValue)); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 224 "parser.y"
    { (yyval.nodeValue) = opr(FOR_INIT, 1, (yyvsp[(1) - (1)].nodeValue)); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    { (yyval.nodeValue) = opr(FOR_TERM, 1, (yyvsp[(1) - (1)].nodeValue)); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 232 "parser.y"
    { (yyval.nodeValue) = opr(FOR_STEP, 1, (yyvsp[(1) - (1)].nodeValue)); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 236 "parser.y"
    { (yyval.nodeValue) = opr(ITER_BODY, 1, (yyvsp[(1) - (1)].nodeValue)); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 240 "parser.y"
    { (yyval.stringValue) = (yyvsp[(1) - (1)].stringValue); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 241 "parser.y"
    { (yyval.stringValue) = (yyvsp[(1) - (1)].stringValue); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 242 "parser.y"
    { (yyval.stringValue) = (yyvsp[(1) - (1)].stringValue); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    { (yyval.stringValue) = (yyvsp[(1) - (1)].stringValue); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 247 "parser.y"
    { (yyval.nodeValue) = opr(FUNC, 3, (yyvsp[(1) - (5)].nodeValue), (yyvsp[(3) - (5)].nodeValue), (yyvsp[(5) - (5)].nodeValue)); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 248 "parser.y"
    { (yyval.nodeValue) = opr(FUNC, 2, (yyvsp[(1) - (5)].nodeValue), (yyvsp[(3) - (5)].nodeValue)); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 249 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (2)].nodeValue); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_CALL, 2, (yyvsp[(1) - (4)].nodeValue), (yyvsp[(3) - (4)].nodeValue)); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 257 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_ARG_LIST, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 259 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_ARG_LIST, 0); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 263 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_ID, 1, id((yyvsp[(2) - (2)].stringValue), (yyvsp[(1) - (2)].stringValue))); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 264 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_ID, 1, id((yyvsp[(2) - (2)].stringValue), (yyvsp[(1) - (2)].stringValue))); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 268 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_ID, 1, id((yyvsp[(1) - (1)].stringValue), "undefined")); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 272 "parser.y"
    { (yyval.nodeValue) = opr(ARG_VALUES, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    { (yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 274 "parser.y"
    { (yyval.nodeValue) = opr(ARG_VALUES, 0); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 278 "parser.y"
    { (yyval.nodeValue) = opr(ARG_VALUE, 1, (yyvsp[(1) - (1)].nodeValue)); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 279 "parser.y"
    { (yyval.nodeValue) = opr(ARG_VALUE, 1, id((yyvsp[(1) - (1)].stringValue), "undefined")); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_ARG, 1, (yyvsp[(1) - (1)].nodeValue)); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 284 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_ARG, 2, (yyvsp[(1) - (3)].nodeValue), (yyvsp[(3) - (3)].nodeValue)); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 288 "parser.y"
    { (yyval.nodeValue) = opr(FUNC_BODY, 1, (yyvsp[(1) - (1)].nodeValue));  ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 292 "parser.y"
    {(yyval.nodeValue) = opr(IF, 2, (yyvsp[(3) - (5)].nodeValue), (yyvsp[(5) - (5)].nodeValue));;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 293 "parser.y"
    {(yyval.nodeValue) = opr(IFELSE, 3, (yyvsp[(3) - (7)].nodeValue), (yyvsp[(5) - (7)].nodeValue), (yyvsp[(7) - (7)].nodeValue));;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 294 "parser.y"
    {(yyval.nodeValue) = opr(SWITCH, 2, (yyvsp[(3) - (5)].nodeValue), (yyvsp[(5) - (5)].nodeValue));;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {(yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue);}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 302 "parser.y"
    {(yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue);}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    {(yyval.nodeValue) = opr(SWITCH_VAR, 1, id((yyvsp[(1) - (1)].stringValue), "undefined"));;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 310 "parser.y"
    {(yyval.nodeValue) = opr(SWITCH_BODY, 2, (yyvsp[(2) - (4)].nodeValue), (yyvsp[(3) - (4)].nodeValue));;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 311 "parser.y"
    {(yyval.nodeValue) = opr(SWITCH_BODY, 1, (yyvsp[(2) - (3)].nodeValue)); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 315 "parser.y"
    {(yyval.nodeValue) = opr(SWITCH_CASES, 2, (yyvsp[(1) - (2)].nodeValue), (yyvsp[(2) - (2)].nodeValue));;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 316 "parser.y"
    {(yyval.nodeValue) = (yyvsp[(1) - (1)].nodeValue);;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 320 "parser.y"
    {(yyval.nodeValue) = opr(SWITCH_CASE, 2, (yyvsp[(2) - (4)].nodeValue), (yyvsp[(4) - (4)].nodeValue));;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 321 "parser.y"
    {(yyval.nodeValue) = opr(SWITCH_CASE, 2, (yyvsp[(2) - (4)].nodeValue), (yyvsp[(4) - (4)].nodeValue));;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    { (yyval.nodeValue) = conInt((yyvsp[(1) - (1)].intValue));  ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 326 "parser.y"
    { (yyval.nodeValue) = conFloat((yyvsp[(1) - (1)].floatValue));  ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 327 "parser.y"
    { (yyval.nodeValue) = conString((yyvsp[(1) - (1)].stringValue));  ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 328 "parser.y"
    { (yyval.nodeValue) = conBool((yyvsp[(1) - (1)].boolValue));  ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {(yyval.nodeValue) = opr(DEFAULT_CASE, 1, (yyvsp[(3) - (3)].nodeValue));;}
    break;



/* Line 1455 of yacc.c  */
#line 2713 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 337 "parser.y"


// Parse Tree
nodeType *conInt(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        printf("out of memory");

    /* copy information */
    p->type = typeIntCon;
    p->conI.value = value;

    return p;
}

nodeType *conFloat(double value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        printf("out of memory");

    /* copy information */
    p->type = typeFloatCon;
    p->conF.value = value;

    return p;
}

nodeType *conBool(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        printf("out of memory");

    /* copy information */
    p->type = typeBoolCon;
    p->conB.value = value;

    return p;
}

nodeType *conString(char* value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        printf("out of memory");

    /* copy information */
    p->type = typeStringCon;
    p->conS.value = strdup(value);

    return p;
}

nodeType *id(char* name, char* type) {
    nodeType *p;
    

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        printf("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.name = strdup(name);
    p->id.type = strdup(type);

    return p;
}

nodeType *constNode(char* name) {
    nodeType *p;
    

    /* allocate node */
    if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
        printf("out of memory");

    /* copy information */
    p->type = typeConst;
    p->constant.name = strdup(name);

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node, extending op array */
    if ((p = (nodeType*)malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
        printf("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}


void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(const char *msg) {
    FILE *file = fopen("errors_and_warnings.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }
    
    printf(
      "Error: at line %d: %s\n",
      yylineno,
      msg);

    fprintf(
        file,
        "Error: at line %d: %s\n",
        yylineno,
        msg);

    fclose(file);

    syntax_error = 1;
}
extern FILE *yyin;


int main() {
    yyin = stdin;
    printf("Global Symbol Table is Initialized\n");
    yyparse();
    if (syntax_error) {
        printf("Syntax Error\n");

        f = fopen("quadruples.txt", "w");
        fprintf(f, "-----------------------------------------------");
        fclose(f);
        f = fopen("tracked_tables.txt", "w");
        fprintf(f, "-----------------------------------------------");
        fclose(f);
        

        return 0;
    }
    printf("Syntax Tree is Created\n");


    // ex(topNode);
    semantic_check(topNode);
    call_extract_quads(topNode);
    return 0;
}

