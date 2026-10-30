/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "E:\\BASIC LANGUAGE\\parser\\parser.y"

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"

extern int yylex(void);
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

void yyerror(const char *s);

/* Globals populated during parsing */
ASTNode *g_root_ast = NULL;
TokenList *g_token_list = NULL;
DiagnosticList *g_diagnostic_list = NULL;
int g_syntax_error_count = 0;
int g_lexical_error_count = 0;
char **g_source_lines = NULL;
int g_source_line_count = 0;

const char *get_source_line_snippet(int line);

static SourceLocation make_loc(int line, int col) {
    SourceLocation loc;
    loc.line = line;
    loc.column = col;
    return loc;
}

extern SourceLocation current_token_loc;


#line 114 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_IDENTIFIER = 3,           /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_INT_LITERAL = 4,          /* TOKEN_INT_LITERAL  */
  YYSYMBOL_TOKEN_FLOAT_LITERAL = 5,        /* TOKEN_FLOAT_LITERAL  */
  YYSYMBOL_TOKEN_STRING_LITERAL = 6,       /* TOKEN_STRING_LITERAL  */
  YYSYMBOL_TOKEN_LET = 7,                  /* TOKEN_LET  */
  YYSYMBOL_TOKEN_PRINT = 8,                /* TOKEN_PRINT  */
  YYSYMBOL_TOKEN_INPUT = 9,                /* TOKEN_INPUT  */
  YYSYMBOL_TOKEN_IF = 10,                  /* TOKEN_IF  */
  YYSYMBOL_TOKEN_THEN = 11,                /* TOKEN_THEN  */
  YYSYMBOL_TOKEN_ELSE = 12,                /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_ELSEIF = 13,              /* TOKEN_ELSEIF  */
  YYSYMBOL_TOKEN_END_IF = 14,              /* TOKEN_END_IF  */
  YYSYMBOL_TOKEN_FOR = 15,                 /* TOKEN_FOR  */
  YYSYMBOL_TOKEN_TO = 16,                  /* TOKEN_TO  */
  YYSYMBOL_TOKEN_STEP = 17,                /* TOKEN_STEP  */
  YYSYMBOL_TOKEN_NEXT = 18,                /* TOKEN_NEXT  */
  YYSYMBOL_TOKEN_WHILE = 19,               /* TOKEN_WHILE  */
  YYSYMBOL_TOKEN_WEND = 20,                /* TOKEN_WEND  */
  YYSYMBOL_TOKEN_GOTO = 21,                /* TOKEN_GOTO  */
  YYSYMBOL_TOKEN_GOSUB = 22,               /* TOKEN_GOSUB  */
  YYSYMBOL_TOKEN_RETURN = 23,              /* TOKEN_RETURN  */
  YYSYMBOL_TOKEN_END = 24,                 /* TOKEN_END  */
  YYSYMBOL_TOKEN_STOP = 25,                /* TOKEN_STOP  */
  YYSYMBOL_TOKEN_EOL = 26,                 /* TOKEN_EOL  */
  YYSYMBOL_TOKEN_COLON = 27,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_AND = 28,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 29,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 30,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_EQ = 31,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 32,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LE = 33,                  /* TOKEN_LE  */
  YYSYMBOL_TOKEN_GE = 34,                  /* TOKEN_GE  */
  YYSYMBOL_TOKEN_LT = 35,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_GT = 36,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_MOD = 37,                 /* TOKEN_MOD  */
  YYSYMBOL_THEN_PREC = 38,                 /* THEN_PREC  */
  YYSYMBOL_39_ = 39,                       /* '+'  */
  YYSYMBOL_40_ = 40,                       /* '-'  */
  YYSYMBOL_41_ = 41,                       /* '*'  */
  YYSYMBOL_42_ = 42,                       /* '/'  */
  YYSYMBOL_43_ = 43,                       /* '\\'  */
  YYSYMBOL_UMINUS = 44,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 45,                     /* UPLUS  */
  YYSYMBOL_46_ = 46,                       /* '^'  */
  YYSYMBOL_47_ = 47,                       /* ','  */
  YYSYMBOL_48_ = 48,                       /* ';'  */
  YYSYMBOL_49_ = 49,                       /* '('  */
  YYSYMBOL_50_ = 50,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_lines = 53,                     /* lines  */
  YYSYMBOL_line = 54,                      /* line  */
  YYSYMBOL_opt_line_label = 55,            /* opt_line_label  */
  YYSYMBOL_statements_on_line = 56,        /* statements_on_line  */
  YYSYMBOL_block_lines = 57,               /* block_lines  */
  YYSYMBOL_statement = 58,                 /* statement  */
  YYSYMBOL_assignment_stmt = 59,           /* assignment_stmt  */
  YYSYMBOL_print_stmt = 60,                /* print_stmt  */
  YYSYMBOL_print_item_list_opt = 61,       /* print_item_list_opt  */
  YYSYMBOL_print_item_list = 62,           /* print_item_list  */
  YYSYMBOL_print_item = 63,                /* print_item  */
  YYSYMBOL_input_stmt = 64,                /* input_stmt  */
  YYSYMBOL_var_list = 65,                  /* var_list  */
  YYSYMBOL_if_stmt = 66,                   /* if_stmt  */
  YYSYMBOL_opt_else_clause = 67,           /* opt_else_clause  */
  YYSYMBOL_for_stmt = 68,                  /* for_stmt  */
  YYSYMBOL_opt_step = 69,                  /* opt_step  */
  YYSYMBOL_opt_next_var = 70,              /* opt_next_var  */
  YYSYMBOL_while_stmt = 71,                /* while_stmt  */
  YYSYMBOL_goto_stmt = 72,                 /* goto_stmt  */
  YYSYMBOL_gosub_stmt = 73,                /* gosub_stmt  */
  YYSYMBOL_return_stmt = 74,               /* return_stmt  */
  YYSYMBOL_end_stmt = 75,                  /* end_stmt  */
  YYSYMBOL_stop_stmt = 76,                 /* stop_stmt  */
  YYSYMBOL_expression = 77,                /* expression  */
  YYSYMBOL_primary_expr = 78               /* primary_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   316

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      49,    50,    41,    39,    47,    40,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    43,     2,    46,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    44,    45
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   127,   127,   135,   138,   151,   154,   165,   168,   175,
     179,   186,   189,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   217,   222,   231,   235,   239,   246,
     249,   255,   259,   263,   270,   278,   282,   287,   295,   301,
     312,   318,   326,   341,   344,   348,   357,   367,   370,   376,
     379,   386,   395,   403,   412,   420,   429,   437,   445,   453,
     456,   460,   464,   468,   472,   476,   480,   484,   488,   492,
     496,   500,   504,   508,   512,   516,   520,   524,   531,   534,
     537,   542,   547
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_IDENTIFIER",
  "TOKEN_INT_LITERAL", "TOKEN_FLOAT_LITERAL", "TOKEN_STRING_LITERAL",
  "TOKEN_LET", "TOKEN_PRINT", "TOKEN_INPUT", "TOKEN_IF", "TOKEN_THEN",
  "TOKEN_ELSE", "TOKEN_ELSEIF", "TOKEN_END_IF", "TOKEN_FOR", "TOKEN_TO",
  "TOKEN_STEP", "TOKEN_NEXT", "TOKEN_WHILE", "TOKEN_WEND", "TOKEN_GOTO",
  "TOKEN_GOSUB", "TOKEN_RETURN", "TOKEN_END", "TOKEN_STOP", "TOKEN_EOL",
  "TOKEN_COLON", "TOKEN_AND", "TOKEN_OR", "TOKEN_NOT", "TOKEN_EQ",
  "TOKEN_NEQ", "TOKEN_LE", "TOKEN_GE", "TOKEN_LT", "TOKEN_GT", "TOKEN_MOD",
  "THEN_PREC", "'+'", "'-'", "'*'", "'/'", "'\\\\'", "UMINUS", "UPLUS",
  "'^'", "','", "';'", "'('", "')'", "$accept", "program", "lines", "line",
  "opt_line_label", "statements_on_line", "block_lines", "statement",
  "assignment_stmt", "print_stmt", "print_item_list_opt",
  "print_item_list", "print_item", "input_stmt", "var_list", "if_stmt",
  "opt_else_clause", "for_stmt", "opt_step", "opt_next_var", "while_stmt",
  "goto_stmt", "gosub_stmt", "return_stmt", "end_stmt", "stop_stmt",
  "expression", "primary_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-45)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -112,     3,    10,  -112,  -112,  -112,  -112,   221,   -15,    34,
       2,    32,     2,    36,     2,    40,    42,  -112,  -112,  -112,
      21,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,     2,    19,  -112,  -112,  -112,  -112,     2,
       2,     2,     2,  -112,     6,  -112,    45,  -112,  -112,    64,
      52,    61,    24,   222,  -112,  -112,  -112,  -112,  -112,   221,
      45,     2,   254,    37,    37,   177,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,    49,   105,   178,     2,  -112,  -112,
      45,  -112,  -112,  -112,   254,   238,   270,   270,   270,   270,
     270,   270,    37,    72,    72,    37,    37,    37,    37,    52,
      52,  -112,  -112,   104,   116,     0,     5,   221,     2,  -112,
    -112,    95,     2,   110,  -112,   137,  -112,    94,  -112,     2,
     115,     8,   117,    45,  -112,  -112,     7,     5,   139,  -112,
    -112,  -112
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     7,     1,     8,     5,     4,     0,     0,     0,
      29,     0,     0,     0,     0,     0,     0,    56,    57,    58,
       0,     9,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     0,     0,    81,    78,    79,    80,     0,
       0,     0,     0,    26,    30,    31,    34,    59,    38,     0,
      35,     0,     0,     0,    53,    52,    55,    54,     6,     0,
      25,     0,    62,    77,    76,     0,    27,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    11,    10,
      24,    82,    32,    33,    61,    60,    63,    64,    67,    68,
      65,    66,    74,    69,    70,    71,    72,    73,    75,    37,
      36,    39,    11,    41,     0,     7,     7,     0,     0,    51,
      12,     0,     0,     0,    42,    47,    11,     0,    40,     0,
       0,     7,     0,    48,    11,    11,     7,     7,    49,    45,
      50,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -112,  -112,  -112,   144,  -112,  -112,  -111,   -46,  -112,  -112,
    -112,  -112,    53,  -112,    55,  -112,    23,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,   -12,  -112
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,   120,     7,    20,   115,    21,    22,    23,
      43,    44,    45,    24,    50,    25,   123,    26,   130,   141,
      27,    28,    29,    30,    31,    32,    46,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   116,    53,     3,     4,    35,    36,    37,    38,     4,
      -2,     4,     4,    89,     4,   131,    33,   121,   122,   -43,
     119,    60,   -44,   136,   137,   138,     5,    62,    63,    64,
      65,     5,    39,     5,     5,    48,     5,    34,    49,    52,
     113,    40,    41,    54,    55,    56,    57,    58,    59,    90,
      61,    42,    48,    66,    67,    87,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   124,    86,    68,    69,   114,    70,    71,    72,    73,
      74,    75,    76,    82,    77,    78,    79,    80,    81,    68,
      69,    82,    70,    71,    72,    73,    74,    75,    76,    85,
      77,    78,    79,    80,    81,   132,   125,    82,   111,    76,
     127,    83,    84,    79,    80,    81,   117,   133,    82,    92,
      93,   126,    68,    69,   128,    70,    71,    72,    73,    74,
      75,    76,   118,    77,    78,    79,    80,    81,   109,   110,
      82,   134,   140,   135,    68,    69,     6,    70,    71,    72,
      73,    74,    75,    76,   129,    77,    78,    79,    80,    81,
     139,     0,    82,     0,     0,    68,    69,     0,    70,    71,
      72,    73,    74,    75,    76,     0,    77,    78,    79,    80,
      81,     8,     0,    82,     0,     9,    10,    11,    12,     0,
       0,     0,     0,    13,     0,     0,     0,    14,     0,    15,
      16,    17,    18,    19,   112,    68,    69,     0,    70,    71,
      72,    73,    74,    75,    76,     0,    77,    78,    79,    80,
      81,     0,     0,    82,     8,     0,     0,    91,     9,    10,
      11,    12,     0,     0,     0,     0,    13,     0,     0,     0,
      14,     0,    15,    16,    17,    18,    19,     0,    88,     0,
      68,    69,     0,    70,    71,    72,    73,    74,    75,    76,
       0,    77,    78,    79,    80,    81,    68,     0,    82,    70,
      71,    72,    73,    74,    75,    76,     0,    77,    78,    79,
      80,    81,     0,     0,    82,    70,    71,    72,    73,    74,
      75,    76,     0,    77,    78,    79,    80,    81,     0,     0,
      82,   -45,   -45,   -45,   -45,   -45,   -45,    76,     0,    77,
      78,    79,    80,    81,     0,     0,    82
};

static const yytype_int16 yycheck[] =
{
      12,   112,    14,     0,     4,     3,     4,     5,     6,     4,
       0,     4,     4,    59,     4,   126,    31,    12,    13,    14,
      20,    33,    14,   134,   135,    18,    26,    39,    40,    41,
      42,    26,    30,    26,    26,     3,    26,     3,     6,     3,
      86,    39,    40,     3,     4,     3,     4,    26,    27,    61,
      31,    49,     3,    47,    48,    31,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,   117,    11,    28,    29,    87,    31,    32,    33,    34,
      35,    36,    37,    46,    39,    40,    41,    42,    43,    28,
      29,    46,    31,    32,    33,    34,    35,    36,    37,    47,
      39,    40,    41,    42,    43,    11,   118,    46,     3,    37,
     122,    47,    48,    41,    42,    43,    12,   129,    46,    66,
      67,    26,    28,    29,    14,    31,    32,    33,    34,    35,
      36,    37,    16,    39,    40,    41,    42,    43,    83,    84,
      46,    26,     3,    26,    28,    29,     2,    31,    32,    33,
      34,    35,    36,    37,    17,    39,    40,    41,    42,    43,
     137,    -1,    46,    -1,    -1,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,     3,    -1,    46,    -1,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    19,    -1,    21,
      22,    23,    24,    25,    26,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    -1,    -1,    46,     3,    -1,    -1,    50,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      19,    -1,    21,    22,    23,    24,    25,    -1,    26,    -1,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      -1,    39,    40,    41,    42,    43,    28,    -1,    46,    31,
      32,    33,    34,    35,    36,    37,    -1,    39,    40,    41,
      42,    43,    -1,    -1,    46,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      46,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,     4,    26,    54,    55,     3,     7,
       8,     9,    10,    15,    19,    21,    22,    23,    24,    25,
      56,    58,    59,    60,    64,    66,    68,    71,    72,    73,
      74,    75,    76,    31,     3,     3,     4,     5,     6,    30,
      39,    40,    49,    61,    62,    63,    77,    78,     3,     6,
      65,    77,     3,    77,     3,     4,     3,     4,    26,    27,
      77,    31,    77,    77,    77,    77,    47,    48,    28,    29,
      31,    32,    33,    34,    35,    36,    37,    39,    40,    41,
      42,    43,    46,    47,    48,    47,    11,    31,    26,    58,
      77,    50,    63,    63,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    65,
      65,     3,    26,    58,    77,    57,    57,    12,    16,    20,
      54,    12,    13,    67,    58,    77,    26,    77,    14,    17,
      69,    57,    11,    77,    26,    26,    57,    57,    18,    67,
       3,    70
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    59,    59,    60,    60,    60,    61,
      61,    62,    62,    62,    63,    64,    64,    64,    65,    65,
      66,    66,    66,    67,    67,    67,    68,    69,    69,    70,
      70,    71,    72,    72,    73,    73,    74,    75,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    78,    78,
      78,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     3,     0,     1,     1,
       3,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     2,     3,     3,     0,
       1,     1,     3,     3,     1,     2,     4,     4,     1,     3,
       7,     4,     6,     0,     3,     6,    11,     0,     2,     0,
       1,     5,     2,     2,     2,     2,     1,     1,     1,     1,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     1,
       1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: lines  */
#line 127 "E:\\BASIC LANGUAGE\\parser\\parser.y"
            {
        SourceLocation loc = make_loc(1, 1);
        g_root_ast = create_program_node((yyvsp[0].node_list), loc);
        (yyval.node) = g_root_ast;
    }
#line 1319 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 3: /* lines: %empty  */
#line 135 "E:\\BASIC LANGUAGE\\parser\\parser.y"
             {
        (yyval.node_list) = ast_node_list_create();
    }
#line 1327 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 4: /* lines: lines line  */
#line 138 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                 {
        (yyval.node_list) = (yyvsp[-1].node_list);
        if ((yyvsp[0].node_list)) {
            for (size_t i = 0; i < (yyvsp[0].node_list)->count; i++) {
                ast_node_list_append((yyval.node_list), (yyvsp[0].node_list)->items[i]);
            }
            free((yyvsp[0].node_list)->items);
            free((yyvsp[0].node_list));
        }
    }
#line 1342 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 5: /* line: TOKEN_EOL  */
#line 151 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 1350 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 6: /* line: opt_line_label statements_on_line TOKEN_EOL  */
#line 154 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                  {
        (yyval.node_list) = (yyvsp[-1].node_list);
        if ((yyvsp[-2].int_val) > 0 && (yyval.node_list) && (yyval.node_list)->count > 0) {
            /* Attach line number to the first statement on this line */
            SourceLocation loc = make_loc((yyval.node_list)->items[0]->location.line, 1);
            (yyval.node_list)->items[0] = create_labeled_stmt_node((yyvsp[-2].int_val), (yyval.node_list)->items[0], loc);
        }
    }
#line 1363 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 7: /* opt_line_label: %empty  */
#line 165 "E:\\BASIC LANGUAGE\\parser\\parser.y"
             {
        (yyval.int_val) = 0;
    }
#line 1371 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 8: /* opt_line_label: TOKEN_INT_LITERAL  */
#line 168 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                        {
        (yyval.int_val) = (int)(yyvsp[0].node)->data.num_literal.value;
        free_ast((yyvsp[0].node));
    }
#line 1380 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 9: /* statements_on_line: statement  */
#line 175 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                {
        (yyval.node_list) = ast_node_list_create();
        if ((yyvsp[0].node)) ast_node_list_append((yyval.node_list), (yyvsp[0].node));
    }
#line 1389 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 10: /* statements_on_line: statements_on_line TOKEN_COLON statement  */
#line 179 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                               {
        (yyval.node_list) = (yyvsp[-2].node_list);
        if ((yyvsp[0].node)) ast_node_list_append((yyval.node_list), (yyvsp[0].node));
    }
#line 1398 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 11: /* block_lines: %empty  */
#line 186 "E:\\BASIC LANGUAGE\\parser\\parser.y"
             {
        (yyval.node_list) = ast_node_list_create();
    }
#line 1406 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 12: /* block_lines: block_lines line  */
#line 189 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                       {
        (yyval.node_list) = (yyvsp[-1].node_list);
        if ((yyvsp[0].node_list)) {
            for (size_t i = 0; i < (yyvsp[0].node_list)->count; i++) {
                ast_node_list_append((yyval.node_list), (yyvsp[0].node_list)->items[i]);
            }
            free((yyvsp[0].node_list)->items);
            free((yyvsp[0].node_list));
        }
    }
#line 1421 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 13: /* statement: assignment_stmt  */
#line 202 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1427 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 14: /* statement: print_stmt  */
#line 203 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1433 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 15: /* statement: input_stmt  */
#line 204 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1439 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 16: /* statement: if_stmt  */
#line 205 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1445 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 17: /* statement: for_stmt  */
#line 206 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1451 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 18: /* statement: while_stmt  */
#line 207 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1457 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 19: /* statement: goto_stmt  */
#line 208 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1463 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 20: /* statement: gosub_stmt  */
#line 209 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1469 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 21: /* statement: return_stmt  */
#line 210 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1475 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 22: /* statement: end_stmt  */
#line 211 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1481 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 23: /* statement: stop_stmt  */
#line 212 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1487 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 24: /* assignment_stmt: TOKEN_LET TOKEN_IDENTIFIER TOKEN_EQ expression  */
#line 217 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                     {
        SourceLocation loc = (yyvsp[0].node) ? (yyvsp[0].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_assignment_node((yyvsp[-2].str_val), (yyvsp[0].node), true, loc);
        free((yyvsp[-2].str_val));
    }
#line 1497 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 25: /* assignment_stmt: TOKEN_IDENTIFIER TOKEN_EQ expression  */
#line 222 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                           {
        SourceLocation loc = (yyvsp[0].node) ? (yyvsp[0].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_assignment_node((yyvsp[-2].str_val), (yyvsp[0].node), false, loc);
        free((yyvsp[-2].str_val));
    }
#line 1507 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 26: /* print_stmt: TOKEN_PRINT print_item_list_opt  */
#line 231 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                      {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_print_node((yyvsp[0].node_list), true, loc);
    }
#line 1516 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 27: /* print_stmt: TOKEN_PRINT print_item_list ','  */
#line 235 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                      {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_print_node((yyvsp[-1].node_list), false, loc);
    }
#line 1525 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 28: /* print_stmt: TOKEN_PRINT print_item_list ';'  */
#line 239 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                      {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_print_node((yyvsp[-1].node_list), false, loc);
    }
#line 1534 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 29: /* print_item_list_opt: %empty  */
#line 246 "E:\\BASIC LANGUAGE\\parser\\parser.y"
             {
        (yyval.node_list) = ast_node_list_create();
    }
#line 1542 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 30: /* print_item_list_opt: print_item_list  */
#line 249 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 1550 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 31: /* print_item_list: print_item  */
#line 255 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                 {
        (yyval.node_list) = ast_node_list_create();
        if ((yyvsp[0].node)) ast_node_list_append((yyval.node_list), (yyvsp[0].node));
    }
#line 1559 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 32: /* print_item_list: print_item_list ',' print_item  */
#line 259 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                     {
        (yyval.node_list) = (yyvsp[-2].node_list);
        if ((yyvsp[0].node)) ast_node_list_append((yyval.node_list), (yyvsp[0].node));
    }
#line 1568 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 33: /* print_item_list: print_item_list ';' print_item  */
#line 263 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                     {
        (yyval.node_list) = (yyvsp[-2].node_list);
        if ((yyvsp[0].node)) ast_node_list_append((yyval.node_list), (yyvsp[0].node));
    }
#line 1577 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 34: /* print_item: expression  */
#line 270 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                 {
        SourceLocation loc = (yyvsp[0].node) ? (yyvsp[0].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_print_item_node((yyvsp[0].node), "", loc);
    }
#line 1586 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 35: /* input_stmt: TOKEN_INPUT var_list  */
#line 278 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                           {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_input_node(NULL, NULL, (yyvsp[0].node_list), loc);
    }
#line 1595 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 36: /* input_stmt: TOKEN_INPUT TOKEN_STRING_LITERAL ';' var_list  */
#line 282 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                    {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_input_node((yyvsp[-2].str_val), ";", (yyvsp[0].node_list), loc);
        free((yyvsp[-2].str_val));
    }
#line 1605 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 37: /* input_stmt: TOKEN_INPUT TOKEN_STRING_LITERAL ',' var_list  */
#line 287 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                    {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_input_node((yyvsp[-2].str_val), ",", (yyvsp[0].node_list), loc);
        free((yyvsp[-2].str_val));
    }
#line 1615 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 38: /* var_list: TOKEN_IDENTIFIER  */
#line 295 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                       {
        (yyval.node_list) = ast_node_list_create();
        SourceLocation loc = make_loc(yylineno, 1);
        ast_node_list_append((yyval.node_list), create_var_node((yyvsp[0].str_val), loc));
        free((yyvsp[0].str_val));
    }
#line 1626 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 39: /* var_list: var_list ',' TOKEN_IDENTIFIER  */
#line 301 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                    {
        (yyval.node_list) = (yyvsp[-2].node_list);
        SourceLocation loc = make_loc(yylineno, 1);
        ast_node_list_append((yyval.node_list), create_var_node((yyvsp[0].str_val), loc));
        free((yyvsp[0].str_val));
    }
#line 1637 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 40: /* if_stmt: TOKEN_IF expression TOKEN_THEN TOKEN_EOL block_lines opt_else_clause TOKEN_END_IF  */
#line 312 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                                                        {
        SourceLocation loc = (yyvsp[-5].node) ? (yyvsp[-5].node)->location : make_loc(yylineno, 1);
        ASTNode *then_branch = create_stmt_list_node((yyvsp[-2].node_list), loc);
        (yyval.node) = create_if_node((yyvsp[-5].node), then_branch, (yyvsp[-1].node), false, loc);
    }
#line 1647 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 41: /* if_stmt: TOKEN_IF expression TOKEN_THEN statement  */
#line 318 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                               {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        ASTNodeList *then_list = ast_node_list_create();
        if ((yyvsp[0].node)) ast_node_list_append(then_list, (yyvsp[0].node));
        ASTNode *then_branch = create_stmt_list_node(then_list, loc);
        (yyval.node) = create_if_node((yyvsp[-2].node), then_branch, NULL, true, loc);
    }
#line 1659 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 42: /* if_stmt: TOKEN_IF expression TOKEN_THEN statement TOKEN_ELSE statement  */
#line 326 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                                    {
        SourceLocation loc = (yyvsp[-4].node) ? (yyvsp[-4].node)->location : make_loc(yylineno, 1);
        ASTNodeList *then_list = ast_node_list_create();
        if ((yyvsp[-2].node)) ast_node_list_append(then_list, (yyvsp[-2].node));
        ASTNode *then_branch = create_stmt_list_node(then_list, loc);

        ASTNodeList *else_list = ast_node_list_create();
        if ((yyvsp[0].node)) ast_node_list_append(else_list, (yyvsp[0].node));
        ASTNode *else_branch = create_stmt_list_node(else_list, loc);

        (yyval.node) = create_if_node((yyvsp[-4].node), then_branch, else_branch, true, loc);
    }
#line 1676 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 43: /* opt_else_clause: %empty  */
#line 341 "E:\\BASIC LANGUAGE\\parser\\parser.y"
             {
        (yyval.node) = NULL;
    }
#line 1684 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 44: /* opt_else_clause: TOKEN_ELSE TOKEN_EOL block_lines  */
#line 344 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                       {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_stmt_list_node((yyvsp[0].node_list), loc);
    }
#line 1693 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 45: /* opt_else_clause: TOKEN_ELSEIF expression TOKEN_THEN TOKEN_EOL block_lines opt_else_clause  */
#line 348 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                                               {
        SourceLocation loc = (yyvsp[-4].node) ? (yyvsp[-4].node)->location : make_loc(yylineno, 1);
        ASTNode *then_branch = create_stmt_list_node((yyvsp[-1].node_list), loc);
        (yyval.node) = create_if_node((yyvsp[-4].node), then_branch, (yyvsp[0].node), false, loc);
    }
#line 1703 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 46: /* for_stmt: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_EQ expression TOKEN_TO expression opt_step TOKEN_EOL block_lines TOKEN_NEXT opt_next_var  */
#line 357 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                                                                                                {
        SourceLocation loc = make_loc(yylineno, 1);
        ASTNode *body_node = create_stmt_list_node((yyvsp[-2].node_list), loc);
        (yyval.node) = create_for_node((yyvsp[-9].str_val), (yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-4].node), body_node, (yyvsp[0].str_val), loc);
        free((yyvsp[-9].str_val));
        if ((yyvsp[0].str_val)) free((yyvsp[0].str_val));
    }
#line 1715 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 47: /* opt_step: %empty  */
#line 367 "E:\\BASIC LANGUAGE\\parser\\parser.y"
             {
        (yyval.node) = NULL;
    }
#line 1723 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 48: /* opt_step: TOKEN_STEP expression  */
#line 370 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1731 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 49: /* opt_next_var: %empty  */
#line 376 "E:\\BASIC LANGUAGE\\parser\\parser.y"
             {
        (yyval.str_val) = NULL;
    }
#line 1739 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 50: /* opt_next_var: TOKEN_IDENTIFIER  */
#line 379 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                       {
        (yyval.str_val) = (yyvsp[0].str_val);
    }
#line 1747 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 51: /* while_stmt: TOKEN_WHILE expression TOKEN_EOL block_lines TOKEN_WEND  */
#line 386 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                                              {
        SourceLocation loc = make_loc(yylineno, 1);
        ASTNode *body_node = create_stmt_list_node((yyvsp[-1].node_list), loc);
        (yyval.node) = create_while_node((yyvsp[-3].node), body_node, loc);
    }
#line 1757 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 52: /* goto_stmt: TOKEN_GOTO TOKEN_INT_LITERAL  */
#line 395 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                   {
        SourceLocation loc = make_loc(yylineno, 1);
        int line_num = (int)(yyvsp[0].node)->data.num_literal.value;
        char num_buf[32];
        snprintf(num_buf, sizeof(num_buf), "%d", line_num);
        (yyval.node) = create_goto_node(line_num, num_buf, loc);
        free_ast((yyvsp[0].node));
    }
#line 1770 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 53: /* goto_stmt: TOKEN_GOTO TOKEN_IDENTIFIER  */
#line 403 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                  {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_goto_node(0, (yyvsp[0].str_val), loc);
        free((yyvsp[0].str_val));
    }
#line 1780 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 54: /* gosub_stmt: TOKEN_GOSUB TOKEN_INT_LITERAL  */
#line 412 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                    {
        SourceLocation loc = make_loc(yylineno, 1);
        int line_num = (int)(yyvsp[0].node)->data.num_literal.value;
        char num_buf[32];
        snprintf(num_buf, sizeof(num_buf), "%d", line_num);
        (yyval.node) = create_gosub_node(line_num, num_buf, loc);
        free_ast((yyvsp[0].node));
    }
#line 1793 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 55: /* gosub_stmt: TOKEN_GOSUB TOKEN_IDENTIFIER  */
#line 420 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                   {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_gosub_node(0, (yyvsp[0].str_val), loc);
        free((yyvsp[0].str_val));
    }
#line 1803 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 56: /* return_stmt: TOKEN_RETURN  */
#line 429 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                   {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_return_node(loc);
    }
#line 1812 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 57: /* end_stmt: TOKEN_END  */
#line 437 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_end_node(loc);
    }
#line 1821 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 58: /* stop_stmt: TOKEN_STOP  */
#line 445 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                 {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_stop_node(loc);
    }
#line 1830 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 59: /* expression: primary_expr  */
#line 453 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                   {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1838 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 60: /* expression: expression TOKEN_OR expression  */
#line 456 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                     {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("OR", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1847 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 61: /* expression: expression TOKEN_AND expression  */
#line 460 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                      {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("AND", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1856 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 62: /* expression: TOKEN_NOT expression  */
#line 464 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                           {
        SourceLocation loc = (yyvsp[0].node) ? (yyvsp[0].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_unary_expr_node("NOT", (yyvsp[0].node), loc);
    }
#line 1865 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 63: /* expression: expression TOKEN_EQ expression  */
#line 468 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                     {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("=", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1874 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 64: /* expression: expression TOKEN_NEQ expression  */
#line 472 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                      {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("<>", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1883 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 65: /* expression: expression TOKEN_LT expression  */
#line 476 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                     {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("<", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1892 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 66: /* expression: expression TOKEN_GT expression  */
#line 480 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                     {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node(">", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1901 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 67: /* expression: expression TOKEN_LE expression  */
#line 484 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                     {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("<=", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1910 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 68: /* expression: expression TOKEN_GE expression  */
#line 488 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                     {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node(">=", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1919 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 69: /* expression: expression '+' expression  */
#line 492 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("+", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1928 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 70: /* expression: expression '-' expression  */
#line 496 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("-", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1937 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 71: /* expression: expression '*' expression  */
#line 500 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("*", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1946 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 72: /* expression: expression '/' expression  */
#line 504 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("/", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1955 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 73: /* expression: expression '\\' expression  */
#line 508 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                 {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("\\", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1964 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 74: /* expression: expression TOKEN_MOD expression  */
#line 512 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                      {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("MOD", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1973 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 75: /* expression: expression '^' expression  */
#line 516 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                {
        SourceLocation loc = (yyvsp[-2].node) ? (yyvsp[-2].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_binary_expr_node("^", (yyvsp[-2].node), (yyvsp[0].node), loc);
    }
#line 1982 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 76: /* expression: '-' expression  */
#line 520 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                  {
        SourceLocation loc = (yyvsp[0].node) ? (yyvsp[0].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_unary_expr_node("-", (yyvsp[0].node), loc);
    }
#line 1991 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 77: /* expression: '+' expression  */
#line 524 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                                 {
        SourceLocation loc = (yyvsp[0].node) ? (yyvsp[0].node)->location : make_loc(yylineno, 1);
        (yyval.node) = create_unary_expr_node("+", (yyvsp[0].node), loc);
    }
#line 2000 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 78: /* primary_expr: TOKEN_INT_LITERAL  */
#line 531 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2008 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 79: /* primary_expr: TOKEN_FLOAT_LITERAL  */
#line 534 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2016 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 80: /* primary_expr: TOKEN_STRING_LITERAL  */
#line 537 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                           {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_string_literal_node((yyvsp[0].str_val), loc);
        free((yyvsp[0].str_val));
    }
#line 2026 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 81: /* primary_expr: TOKEN_IDENTIFIER  */
#line 542 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                       {
        SourceLocation loc = make_loc(yylineno, 1);
        (yyval.node) = create_var_node((yyvsp[0].str_val), loc);
        free((yyvsp[0].str_val));
    }
#line 2036 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;

  case 82: /* primary_expr: '(' expression ')'  */
#line 547 "E:\\BASIC LANGUAGE\\parser\\parser.y"
                         {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2044 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"
    break;


#line 2048 "E:\\BASIC LANGUAGE\\parser\\parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 552 "E:\\BASIC LANGUAGE\\parser\\parser.y"


const char *get_source_line_snippet(int line) {
    if (line >= 1 && line <= g_source_line_count && g_source_lines) {
        return g_source_lines[line - 1];
    }
    return "";
}

void yyerror(const char *s) {
    g_syntax_error_count++;
    int col = current_token_loc.column > 0 ? current_token_loc.column : 1;
    int line = current_token_loc.line > 0 ? current_token_loc.line : yylineno;
    const char *snippet = get_source_line_snippet(line);
    
    char clean_msg[256];
    if (strncmp(s, "syntax error", 12) == 0) {
        if (yytext && strlen(yytext) > 0 && yytext[0] != '\n') {
            snprintf(clean_msg, sizeof(clean_msg), "Syntax error near '%s'", yytext);
        } else {
            snprintf(clean_msg, sizeof(clean_msg), "Syntax error: unexpected end of statement or token");
        }
    } else {
        snprintf(clean_msg, sizeof(clean_msg), "%s", s);
    }

    if (g_diagnostic_list) {
        diagnostic_list_append(g_diagnostic_list, "SYNTAX_ERROR", clean_msg, line, col, snippet);
    }
}
