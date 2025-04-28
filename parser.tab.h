
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 51 "parser.y"

	int intValue;
	float floatValue;
	int boolValue;
	char* stringValue;
    nodeType* nodeValue;



/* Line 1676 of yacc.c  */
#line 152 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;

