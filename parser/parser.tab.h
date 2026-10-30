/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_E_BASIC_LANGUAGE_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_E_BASIC_LANGUAGE_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 44 "E:\\BASIC LANGUAGE\\parser\\parser.y"

    #include "ast.h"

#line 53 "E:\\BASIC LANGUAGE\\parser\\parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_IDENTIFIER = 258,        /* TOKEN_IDENTIFIER  */
    TOKEN_INT_LITERAL = 259,       /* TOKEN_INT_LITERAL  */
    TOKEN_FLOAT_LITERAL = 260,     /* TOKEN_FLOAT_LITERAL  */
    TOKEN_STRING_LITERAL = 261,    /* TOKEN_STRING_LITERAL  */
    TOKEN_LET = 262,               /* TOKEN_LET  */
    TOKEN_PRINT = 263,             /* TOKEN_PRINT  */
    TOKEN_INPUT = 264,             /* TOKEN_INPUT  */
    TOKEN_IF = 265,                /* TOKEN_IF  */
    TOKEN_THEN = 266,              /* TOKEN_THEN  */
    TOKEN_ELSE = 267,              /* TOKEN_ELSE  */
    TOKEN_ELSEIF = 268,            /* TOKEN_ELSEIF  */
    TOKEN_END_IF = 269,            /* TOKEN_END_IF  */
    TOKEN_FOR = 270,               /* TOKEN_FOR  */
    TOKEN_TO = 271,                /* TOKEN_TO  */
    TOKEN_STEP = 272,              /* TOKEN_STEP  */
    TOKEN_NEXT = 273,              /* TOKEN_NEXT  */
    TOKEN_WHILE = 274,             /* TOKEN_WHILE  */
    TOKEN_WEND = 275,              /* TOKEN_WEND  */
    TOKEN_GOTO = 276,              /* TOKEN_GOTO  */
    TOKEN_GOSUB = 277,             /* TOKEN_GOSUB  */
    TOKEN_RETURN = 278,            /* TOKEN_RETURN  */
    TOKEN_END = 279,               /* TOKEN_END  */
    TOKEN_STOP = 280,              /* TOKEN_STOP  */
    TOKEN_EOL = 281,               /* TOKEN_EOL  */
    TOKEN_COLON = 282,             /* TOKEN_COLON  */
    TOKEN_AND = 283,               /* TOKEN_AND  */
    TOKEN_OR = 284,                /* TOKEN_OR  */
    TOKEN_NOT = 285,               /* TOKEN_NOT  */
    TOKEN_EQ = 286,                /* TOKEN_EQ  */
    TOKEN_NEQ = 287,               /* TOKEN_NEQ  */
    TOKEN_LE = 288,                /* TOKEN_LE  */
    TOKEN_GE = 289,                /* TOKEN_GE  */
    TOKEN_LT = 290,                /* TOKEN_LT  */
    TOKEN_GT = 291,                /* TOKEN_GT  */
    TOKEN_MOD = 292,               /* TOKEN_MOD  */
    THEN_PREC = 293,               /* THEN_PREC  */
    UMINUS = 294,                  /* UMINUS  */
    UPLUS = 295                    /* UPLUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 48 "E:\\BASIC LANGUAGE\\parser\\parser.y"

    int int_val;
    double float_val;
    char *str_val;
    ASTNode *node;
    ASTNodeList *node_list;

#line 118 "E:\\BASIC LANGUAGE\\parser\\parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_E_BASIC_LANGUAGE_PARSER_PARSER_TAB_H_INCLUDED  */
