
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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         cexpparse
#define yylex           cexplex
#define yyerror         cexperror
#define yylval          cexplval
#define yychar          cexpchar
#define yydebug         cexpdebug
#define yynerrs         cexpnerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "cexp.y"

/* $Id: cexp.y,v 1.49 2009/12/04 17:23:10 strauman Exp $ */
/* Grammar definition and lexical analyzer for Cexp */

/* SLAC Software Notices, Set 4 OTT.002a, 2004 FEB 03
 *
 * Authorship
 * ----------
 * This software (CEXP - C-expression interpreter and runtime
 * object loader/linker) was created by
 *
 *    Till Straumann <strauman@slac.stanford.edu>, 2002-2008,
 * 	  Stanford Linear Accelerator Center, Stanford University.
 *
 * Acknowledgement of sponsorship
 * ------------------------------
 * This software was produced by
 *     the Stanford Linear Accelerator Center, Stanford University,
 * 	   under Contract DE-AC03-76SFO0515 with the Department of Energy.
 * 
 * Government disclaimer of liability
 * ----------------------------------
 * Neither the United States nor the United States Department of Energy,
 * nor any of their employees, makes any warranty, express or implied, or
 * assumes any legal liability or responsibility for the accuracy,
 * completeness, or usefulness of any data, apparatus, product, or process
 * disclosed, or represents that its use would not infringe privately owned
 * rights.
 * 
 * Stanford disclaimer of liability
 * --------------------------------
 * Stanford University makes no representations or warranties, express or
 * implied, nor assumes any liability for the use of this software.
 * 
 * Stanford disclaimer of copyright
 * --------------------------------
 * Stanford University, owner of the copyright, hereby disclaims its
 * copyright and all other rights in this software.  Hence, anyone may
 * freely use it for any purpose without restriction.  
 * 
 * Maintenance of notices
 * ----------------------
 * In the interest of clarity regarding the origin and status of this
 * SLAC software, this and all the preceding Stanford University notices
 * are to remain affixed to any copy or derivative of this software made
 * or distributed by the recipient and are to be affixed to any copy of
 * software made or distributed by the recipient that contains a copy or
 * derivative of this software.
 * 
 * SLAC Software Notices, Set 4 OTT.002a, 2004 FEB 03
 */ 

#include <stdio.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cexpsyms.h"
#include "cexpmod.h"
#include "vars.h"
#include <stdarg.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* not letting them live makes not much sense */
#ifndef CONFIG_STRINGS_LIVE_FOREVER
#define CONFIG_STRINGS_LIVE_FOREVER
#endif

#define YYLEX_PARAM		ctx
#define YYERROR_VERBOSE

#define EVAL_INH	 ((ctx)->evalInhibit)
#define PSHEVAL(inh) do { EVAL_INH<<=1; if (inh) EVAL_INH++; } while(0)
#define POPEVAL      do { EVAL_INH>>=1; } while(0)
#define EVAL(stuff)  if (! EVAL_INH ) do { stuff; } while (0)

#define CHECK(cexpTfuncall) do { const char *e=(cexpTfuncall);\
					 if (e) { yyerror(ctx, e); YYERROR; } } while (0)

/* acceptable characters for identifiers - must not
 * overlap with operators
 */
#define ISIDENTCHAR(ch) ('_'==(ch) || '@'==(ch))

#define LEXERR	-1
/* ugly hack; helper for word completion */
#define LEXERR_INCOMPLETE_STRING	-100

       void yyerror(CexpParserCtx ctx, const char*msg);
static void errmsg(CexpParserCtx ctx, const char *msg, ...);
static void wrnmsg(CexpParserCtx ctx, const char *msg, ...);

int  yylex();

typedef char *LString;

struct CexpParserCtxRec_;

typedef void (*RedirCb)(struct CexpParserCtxRec_ *, void *);

typedef struct CexpParserCtxRec_ {
	const char		*chpt;
	LString			lineStrTbl[10];	/* allow for 10 strings on one line of input  */
	CexpSymRec		rval_sym;       /* return value and status of last evaluation */
	CexpValU		rval;
	int             status;         
	unsigned long	evalInhibit;
	FILE			*outf;			/* where to print evaluated value			  */
	FILE			*errf;			/* where to print error messages 			  */
	char            sbuf[1000];		/* scratch space for strings                  */
	FILE            *o_stdout;      /* redirection */
	FILE            *o_stderr;      /* redirection */
	FILE            *o_stdin;       /* redirection */
	FILE            *o_outf;
	FILE            *o_errf;
	RedirCb         redir_cb;
	void            *cb_arg;
} CexpParserCtxRec;

static CexpSym
varCreate(CexpParserCtx ctx, char *name, CexpType type)
{
CexpSym rval;
	if (!(rval=cexpVarLookup(name,1)/*allow creation*/)) {
		if ( ctx->errf )
			fprintf(ctx->errf, "unable to add new user variable");
		return 0;
	}
	rval->value.type = type;
	if (CEXP_TYPE_PTRQ(type))
		rval->value.ptv->p=0;
	else switch(type) {
		case TUChar:	rval->value.ptv->c=0;		break;
		case TUShort:	rval->value.ptv->s=0;		break;
		case TULong:	rval->value.ptv->l=0;		break;
		case TFloat:	rval->value.ptv->f=0.0;	break;
		case TDouble:	rval->value.ptv->d=0.0;	break;
		default:
			assert(!"unknown type");
	}
	return rval;
}

static int
cexpRedir(CexpParserCtx ctx, unsigned long op, void *opath, void *ipath);

static void
cexpUnredir(CexpParserCtx ctx);

/* Redefine so that we can wrap */
#undef yyparse
#define yyparse __cexpparse



/* Line 189 of yacc.c  */
#line 242 "cexp.tab.c"

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
     NUMBER = 258,
     STR_CONST = 259,
     FUNC = 260,
     VAR = 261,
     UVAR = 262,
     IDENT = 263,
     KW_CHAR = 264,
     KW_SHORT = 265,
     KW_LONG = 266,
     KW_FLOAT = 267,
     KW_DOUBLE = 268,
     MODOP = 269,
     REDIR = 270,
     REDIRBOTH = 271,
     REDIRAPPEND = 272,
     REDIRAPPENDBOTH = 273,
     NONE = 274,
     OR = 275,
     AND = 276,
     NE = 277,
     EQ = 278,
     GE = 279,
     LE = 280,
     SHR = 281,
     SHL = 282,
     CAST = 283,
     VARCAST = 284,
     DEREF = 285,
     ADDR = 286,
     PREFIX = 287,
     MM = 288,
     PP = 289,
     NEG = 290,
     CALL = 291
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 162 "cexp.y"

	CexpTypedValRec				val;
	CexpTypedAddrRec			lval;
	CexpTypedAddr				varp;
	CexpSym						sym;	/* a symbol table entry */
	CexpType					typ;
	CexpBinOp					binop;
	char						*lstr;	/* string in the line string table */
	struct			{
		CexpTypedAddrRec	lval;
		CexpBinOp			op;
	}							fixexp;
	struct			{
		CexpSym				sym;
		char				*mname;		/* string kept in the line string table */
	}							method;
	unsigned long				ul;
	char                        *chrp;



/* Line 214 of yacc.c  */
#line 336 "cexp.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 348 "cexp.tab.c"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   481

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNRULES -- Number of states.  */
#define YYNSTATES  212

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      56,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,     2,     2,    41,    28,     2,
      54,    55,    39,    38,    20,    37,    53,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    22,     2,
      31,    23,    32,    21,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    27,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    26,     2,    50,     2,     2,     2,
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
      15,    16,    17,    18,    19,    24,    25,    29,    30,    33,
      34,    35,    36,    42,    43,    44,    45,    46,    47,    48,
      49,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    13,    16,    19,    22,
      23,    26,    29,    34,    39,    42,    46,    54,    57,    61,
      69,    71,    74,    76,    80,    82,    85,    88,    91,    94,
      96,   100,   104,   108,   110,   113,   116,   120,   124,   128,
     132,   136,   140,   144,   148,   152,   156,   160,   164,   168,
     172,   176,   180,   183,   186,   189,   192,   195,   198,   200,
     202,   204,   206,   209,   212,   215,   218,   220,   222,   224,
     226,   228,   231,   233,   235,   237,   239,   241,   245,   250,
     252,   261,   263,   266,   268,   270,   272,   275,   278,   281,
     285,   289,   293,   297,   299,   303,   308,   315,   319,   324,
     331,   340,   351,   364,   379,   396,   415,   436,   459,   484,
     511
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    61,    66,    -1,    32,    -1,    35,    -1,
      32,    28,    -1,    35,    28,    -1,    74,    22,    -1,     4,
      22,    -1,    -1,    59,    60,    -1,    31,    60,    -1,    31,
      60,    59,    60,    -1,    59,    60,    31,    60,    -1,    77,
      75,    -1,    77,    39,    75,    -1,    80,    54,    39,    75,
      55,    54,    55,    -1,    77,     8,    -1,    77,    39,     8,
      -1,    80,    54,    39,     8,    55,    54,    55,    -1,    63,
      -1,    62,    51,    -1,    67,    -1,    65,    20,    67,    -1,
      56,    -1,     8,    56,    -1,    64,    56,    -1,    62,    56,
      -1,    65,    56,    -1,    68,    -1,    76,    23,    67,    -1,
      76,    14,    67,    -1,     8,    23,    67,    -1,    83,    -1,
      69,    68,    -1,    70,    68,    -1,    68,    26,    68,    -1,
      68,    27,    68,    -1,    68,    28,    68,    -1,    68,    29,
      68,    -1,    68,    30,    68,    -1,    68,    32,    68,    -1,
      68,    31,    68,    -1,    68,    34,    68,    -1,    68,    33,
      68,    -1,    68,    36,    68,    -1,    68,    35,    68,    -1,
      68,    38,    68,    -1,    68,    37,    68,    -1,    68,    39,
      68,    -1,    68,    40,    68,    -1,    68,    41,    68,    -1,
      68,    24,    -1,    68,    25,    -1,    47,    76,    -1,    48,
      76,    -1,    76,    47,    -1,    76,    48,    -1,    76,    -1,
       3,    -1,     4,    -1,    85,    -1,    51,    83,    -1,    50,
      83,    -1,    37,    83,    -1,    28,    74,    -1,     6,    -1,
       7,    -1,    74,    -1,     5,    -1,    74,    -1,    39,    83,
      -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,    13,
      -1,    54,    77,    55,    -1,    54,    77,    39,    55,    -1,
      77,    -1,    54,    80,    54,    39,    55,    54,    55,    55,
      -1,     5,    -1,    28,     5,    -1,    72,    -1,    71,    -1,
      73,    -1,    78,    83,    -1,    79,    83,    -1,    81,    83,
      -1,     6,    53,     8,    -1,     7,    53,     8,    -1,     5,
      53,     8,    -1,    54,    65,    55,    -1,    82,    -1,    84,
      54,    55,    -1,    84,    54,    67,    55,    -1,    84,    54,
      67,    20,    67,    55,    -1,    85,    54,    55,    -1,    85,
      54,    67,    55,    -1,    85,    54,    67,    20,    67,    55,
      -1,    85,    54,    67,    20,    67,    20,    67,    55,    -1,
      85,    54,    67,    20,    67,    20,    67,    20,    67,    55,
      -1,    85,    54,    67,    20,    67,    20,    67,    20,    67,
      20,    67,    55,    -1,    85,    54,    67,    20,    67,    20,
      67,    20,    67,    20,    67,    20,    67,    55,    -1,    85,
      54,    67,    20,    67,    20,    67,    20,    67,    20,    67,
      20,    67,    20,    67,    55,    -1,    85,    54,    67,    20,
      67,    20,    67,    20,    67,    20,    67,    20,    67,    20,
      67,    20,    67,    55,    -1,    85,    54,    67,    20,    67,
      20,    67,    20,    67,    20,    67,    20,    67,    20,    67,
      20,    67,    20,    67,    55,    -1,    85,    54,    67,    20,
      67,    20,    67,    20,    67,    20,    67,    20,    67,    20,
      67,    20,    67,    20,    67,    20,    67,    55,    -1,    85,
      54,    67,    20,    67,    20,    67,    20,    67,    20,    67,
      20,    67,    20,    67,    20,    67,    20,    67,    20,    67,
      20,    67,    55,    -1,    85,    54,    67,    20,    67,    20,
      67,    20,    67,    20,    67,    20,    67,    20,    67,    20,
      67,    20,    67,    20,    67,    20,    67,    20,    67,    55,
      -1,    85,    54,    67,    20,    67,    20,    67,    20,    67,
      20,    67,    20,    67,    20,    67,    20,    67,    20,    67,
      20,    67,    20,    67,    20,    67,    20,    67,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   248,   248,   251,   253,   255,   257,   261,   269,   275,
     276,   278,   280,   282,   286,   288,   290,   294,   299,   304,
     311,   311,   314,   315,   319,   321,   327,   328,   332,   369,
     370,   372,   379,   388,   389,   393,   397,   399,   401,   403,
     405,   407,   409,   411,   413,   415,   417,   419,   421,   423,
     425,   427,   431,   435,   439,   441,   446,   448,   450,   458,
     459,   463,   464,   466,   468,   474,   478,   480,   483,   485,
     489,   491,   506,   508,   510,   512,   514,   518,   523,   527,
     545,   549,   551,   553,   565,   579,   580,   582,   584,   589,
     591,   593,   599,   600,   601,   603,   605,   607,   609,   611,
     613,   615,   617,   619,   621,   623,   625,   627,   629,   631,
     633
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STR_CONST", "FUNC", "VAR",
  "UVAR", "IDENT", "KW_CHAR", "KW_SHORT", "KW_LONG", "KW_FLOAT",
  "KW_DOUBLE", "MODOP", "REDIR", "REDIRBOTH", "REDIRAPPEND",
  "REDIRAPPENDBOTH", "NONE", "','", "'?'", "':'", "'='", "OR", "AND",
  "'|'", "'^'", "'&'", "NE", "EQ", "'<'", "'>'", "GE", "LE", "SHR", "SHL",
  "'-'", "'+'", "'*'", "'/'", "'%'", "CAST", "VARCAST", "DEREF", "ADDR",
  "PREFIX", "MM", "PP", "NEG", "'~'", "'!'", "CALL", "'.'", "'('", "')'",
  "'\\n'", "$accept", "input", "oredirop", "redirarg", "redir", "redef",
  "newdef", "def", "commaexp", "line", "exp", "binexp", "or", "and",
  "prefix", "postfix", "unexp", "nonfuncvar", "anyvar", "lval", "typeid",
  "cast", "pcast", "fptype", "fpcast", "funcp", "castexp", "symmethod",
  "call", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      44,    63,    58,    61,   275,   276,   124,    94,    38,   277,
     278,    60,    62,   279,   280,   281,   282,    45,    43,    42,
      47,    37,   283,   284,   285,   286,   287,   288,   289,   290,
     126,    33,   291,    46,    40,    41,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    59,    59,    60,    60,    61,
      61,    61,    61,    61,    62,    62,    62,    63,    63,    63,
      64,    64,    65,    65,    66,    66,    66,    66,    66,    67,
      67,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    70,    71,    71,    72,    72,    72,    73,
      73,    73,    73,    73,    73,    73,    74,    74,    75,    75,
      76,    76,    77,    77,    77,    77,    77,    78,    79,    80,
      81,    82,    82,    82,    82,    83,    83,    83,    83,    84,
      84,    84,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     2,     2,     2,     0,
       2,     2,     4,     4,     2,     3,     7,     2,     3,     7,
       1,     2,     1,     3,     1,     2,     2,     2,     2,     1,
       3,     3,     3,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     3,     4,     1,
       8,     1,     2,     1,     1,     1,     2,     2,     2,     3,
       3,     3,     3,     1,     3,     4,     6,     3,     4,     6,
       8,    10,    12,    14,    16,    18,    20,    22,    24,    26,
      28
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       9,     0,     3,     4,     0,     0,     0,     0,    66,    67,
      11,     0,     5,     6,     1,    10,    59,    60,    81,    66,
      67,     0,    72,    73,    74,    75,    76,     0,     0,     0,
       0,     0,     0,     0,     0,    24,     0,    20,     0,     0,
       2,    22,    29,     0,     0,    84,    83,    85,    70,    58,
      79,     0,     0,     0,     0,    93,    33,     0,    61,     8,
       0,     7,     0,     0,     0,     0,     0,    25,    82,    65,
      58,    64,    71,    54,    55,    63,    62,     0,     0,    79,
       0,    21,    27,    26,     0,    28,    52,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,     0,     0,    56,    57,
      69,    17,     0,    68,    14,    86,    87,     0,    88,     0,
       0,    12,    13,    91,    89,    90,    32,    92,     0,    77,
       0,    23,    36,    37,    38,    39,    40,    42,    41,    44,
      43,    46,    45,    48,    47,    49,    50,    51,    31,    30,
      18,    15,     0,    94,     0,    97,     0,    78,     0,     0,
       0,     0,    95,     0,    98,     0,     0,     0,     0,     0,
       0,     0,     0,    96,     0,    99,     0,    19,    16,     0,
      80,     0,   100,     0,     0,   101,     0,     0,   102,     0,
       0,   103,     0,     0,   104,     0,     0,   105,     0,     0,
     106,     0,     0,   107,     0,     0,   108,     0,     0,   109,
       0,   110
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,    10,     6,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,   114,    70,
      50,    51,    52,    53,    54,    55,    56,    57,    58
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -112
static const yytype_int16 yypact[] =
{
      87,   127,    18,    35,    21,   127,   200,    74,  -112,  -112,
      37,    76,  -112,  -112,  -112,    71,  -112,  -112,   -27,   -24,
      59,   -12,  -112,  -112,  -112,  -112,  -112,     1,   323,   323,
      31,    31,   323,   323,   307,  -112,   -37,  -112,    53,   -17,
    -112,  -112,   354,   323,   323,  -112,  -112,  -112,  -112,    26,
     153,   323,   323,    61,   323,  -112,  -112,    67,    73,  -112,
     127,  -112,   127,   122,   128,   135,   100,  -112,  -112,  -112,
      77,  -112,  -112,  -112,  -112,  -112,  -112,   117,   -10,    56,
      88,  -112,  -112,  -112,   100,  -112,  -112,  -112,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   371,   387,   100,   100,  -112,  -112,
    -112,  -112,   209,  -112,  -112,  -112,  -112,   106,  -112,   216,
     254,  -112,  -112,  -112,  -112,  -112,  -112,  -112,    91,  -112,
     110,  -112,   402,   416,   429,   440,   440,   194,   194,   194,
     194,   132,   132,    36,    36,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,   235,  -112,    -8,  -112,    -7,  -112,    97,    98,
     109,   100,  -112,   100,  -112,   111,   120,   123,   121,    -5,
     124,   125,   136,  -112,   100,  -112,   139,  -112,  -112,    -4,
    -112,   100,  -112,    -3,   100,  -112,    -2,   100,  -112,     2,
     100,  -112,     3,   100,  -112,     7,   100,  -112,    10,   100,
    -112,    12,   100,  -112,    13,   100,  -112,    16,   100,  -112,
     140,  -112
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -112,  -112,   172,    -1,  -112,  -112,  -112,  -112,   149,  -112,
     -64,    -9,  -112,  -112,  -112,  -112,  -112,     4,  -111,    -6,
     155,  -112,  -112,   163,  -112,  -112,   134,  -112,  -112
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      49,   151,   126,    84,    15,    11,    68,     8,     9,    11,
      84,    66,   161,   163,    81,   174,   181,   184,   187,    82,
     131,    14,   190,   193,    73,    74,    63,   196,    49,    64,
     199,    69,   202,   205,   104,   105,   208,     8,     9,    85,
     106,   160,   148,   149,    67,   127,    12,   162,   164,   107,
     175,   182,   185,   188,   113,   154,   156,   191,   194,   121,
      49,   122,   197,    13,    11,   200,    11,   203,   206,     2,
      29,   209,     3,   108,   109,   101,   102,   103,    49,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   128,    59,   168,    61,   169,
      49,    49,    62,    16,    17,    18,    19,    20,    77,    83,
     179,   129,    65,    49,    49,   117,   113,   183,     1,     2,
     186,   119,     3,   189,   108,   109,   192,   120,    27,   195,
     123,     7,   198,     8,     9,   201,   124,    28,   204,    29,
      66,   207,   130,   125,   210,   152,   157,    30,    31,   158,
      32,    33,   165,   166,    34,    49,   113,    49,   110,     8,
       9,   111,    71,    72,   167,   170,    75,    76,    49,    99,
     100,   101,   102,   103,   171,    49,   173,   172,    49,   176,
     177,    49,    60,    78,    49,   115,   116,    49,   118,    79,
      49,   178,   112,    49,   180,   211,    49,    80,     0,    49,
       0,     0,    49,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,   110,     8,     9,   150,     0,    16,
      17,    18,    19,    20,    77,     0,     0,     0,    27,    97,
      98,    99,   100,   101,   102,   103,     0,    28,     0,    29,
     110,     8,     9,   159,    27,     0,     0,    30,    31,     0,
      32,    33,     0,    28,    34,    29,    35,    16,    17,    18,
      19,    20,    77,    30,    31,     0,    32,    33,     0,     0,
      34,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,     0,     0,     0,     0,     0,     0,
       0,    28,     0,    29,     0,     0,     0,     0,     0,     0,
       0,    30,    31,     0,    32,    33,     0,     0,    34,   155,
      16,    17,    18,    19,    20,    77,    22,    23,    24,    25,
      26,     0,     0,     0,     0,     0,    16,    17,    18,    19,
      20,     0,     0,     0,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,    28,     0,    29,     0,     0,     0,
       0,    27,     0,     0,    30,    31,     0,    32,    33,     0,
      28,    34,    29,     0,     0,     0,     0,     0,     0,     0,
      30,    31,     0,    32,    33,     0,     0,    34,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103
};

static const yytype_int16 yycheck[] =
{
       6,   112,    66,    20,     5,     1,     5,     6,     7,     5,
      20,    23,    20,    20,    51,    20,    20,    20,    20,    56,
      84,     0,    20,    20,    30,    31,    53,    20,    34,    53,
      20,    27,    20,    20,    43,    44,    20,     6,     7,    56,
      14,   152,   106,   107,    56,    55,    28,    55,    55,    23,
      55,    55,    55,    55,    50,   119,   120,    55,    55,    60,
      66,    62,    55,    28,    60,    55,    62,    55,    55,    32,
      39,    55,    35,    47,    48,    39,    40,    41,    84,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    39,    22,   161,    22,   163,
     106,   107,    31,     3,     4,     5,     6,     7,     8,    56,
     174,    55,    53,   119,   120,    54,   112,   181,    31,    32,
     184,    54,    35,   187,    47,    48,   190,    54,    28,   193,
       8,     4,   196,     6,     7,   199,     8,    37,   202,    39,
      23,   205,    54,     8,   208,    39,    55,    47,    48,    39,
      50,    51,    55,    55,    54,   161,   152,   163,     5,     6,
       7,     8,    28,    29,    55,    54,    32,    33,   174,    37,
      38,    39,    40,    41,    54,   181,    55,    54,   184,    55,
      55,   187,    10,    34,   190,    51,    52,   193,    54,    34,
     196,    55,    39,   199,    55,    55,   202,    34,    -1,   205,
      -1,    -1,   208,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     5,     6,     7,     8,    -1,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    28,    35,
      36,    37,    38,    39,    40,    41,    -1,    37,    -1,    39,
       5,     6,     7,     8,    28,    -1,    -1,    47,    48,    -1,
      50,    51,    -1,    37,    54,    39,    56,     3,     4,     5,
       6,     7,     8,    47,    48,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    50,    51,    -1,    -1,    54,    55,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    39,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    47,    48,    -1,    50,    51,    -1,
      37,    54,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    50,    51,    -1,    -1,    54,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    31,    32,    35,    58,    59,    61,     4,     6,     7,
      60,    74,    28,    28,     0,    60,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    28,    37,    39,
      47,    48,    50,    51,    54,    56,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    22,
      59,    22,    31,    53,    53,    53,    23,    56,     5,    74,
      76,    83,    83,    76,    76,    83,    83,     8,    65,    77,
      80,    51,    56,    56,    20,    56,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    68,    68,    14,    23,    47,    48,
       5,     8,    39,    74,    75,    83,    83,    54,    83,    54,
      54,    60,    60,     8,     8,     8,    67,    55,    39,    55,
      54,    67,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    67,    67,
       8,    75,    39,    55,    67,    55,    67,    55,    39,     8,
      75,    20,    55,    20,    55,    55,    55,    55,    67,    67,
      54,    54,    54,    55,    20,    55,    55,    55,    55,    67,
      55,    20,    55,    67,    20,    55,    67,    20,    55,    67,
      20,    55,    67,    20,    55,    67,    20,    55,    67,    20,
      55,    67,    20,    55,    67,    20,    55,    67,    20,    55,
      67,    55
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
      yyerror (ctx, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
		  Type, Value, ctx); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, CexpParserCtx ctx)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, ctx)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    CexpParserCtx ctx;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (ctx);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, CexpParserCtx ctx)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, ctx)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    CexpParserCtx ctx;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, ctx);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, CexpParserCtx ctx)
#else
static void
yy_reduce_print (yyvsp, yyrule, ctx)
    YYSTYPE *yyvsp;
    int yyrule;
    CexpParserCtx ctx;
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
		       		       , ctx);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, ctx); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, CexpParserCtx ctx)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, ctx)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    CexpParserCtx ctx;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (ctx);

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
int yyparse (CexpParserCtx ctx);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





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
yyparse (CexpParserCtx ctx)
#else
int
yyparse (ctx)
    CexpParserCtx ctx;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 248 "cexp.y"
    { if ( TVoid != (yyvsp[(2) - (2)].val).type ) { ctx->rval=(yyvsp[(2) - (2)].val).tv; ctx->rval_sym.value.type = (yyvsp[(2) - (2)].val).type; } ctx->status = 0; YYACCEPT; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 252 "cexp.y"
    { (yyval.ul)=REDIR; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 254 "cexp.y"
    { (yyval.ul)=REDIRAPPEND; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 256 "cexp.y"
    { (yyval.ul)=REDIRBOTH; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 258 "cexp.y"
    { (yyval.ul)=REDIRAPPENDBOTH; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 262 "cexp.y"
    {
			if ( TUCharP != (yyvsp[(1) - (2)].varp)->type ) {
				errmsg(ctx, "(bad type): redirector requires string argument\n");
				YYERROR;
			}
			(yyval.chrp) = (yyvsp[(1) - (2)].varp)->ptv->p;
		;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 270 "cexp.y"
    {
			(yyval.chrp) = (yyvsp[(1) - (2)].val).tv.p;
		;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 277 "cexp.y"
    { if ( cexpRedir( ctx, (yyvsp[(1) - (2)].ul), (yyvsp[(2) - (2)].chrp),  0 ) ) YYERROR; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 279 "cexp.y"
    { if ( cexpRedir( ctx,  0,  0, (yyvsp[(2) - (2)].chrp) ) ) YYERROR; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 281 "cexp.y"
    { if ( cexpRedir( ctx, (yyvsp[(3) - (4)].ul), (yyvsp[(4) - (4)].chrp), (yyvsp[(2) - (4)].chrp) ) ) YYERROR; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 283 "cexp.y"
    { if ( cexpRedir( ctx, (yyvsp[(1) - (4)].ul), (yyvsp[(2) - (4)].chrp), (yyvsp[(4) - (4)].chrp) ) ) YYERROR; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 287 "cexp.y"
    { EVAL((yyvsp[(2) - (2)].varp)->type = (yyvsp[(1) - (2)].typ);); CHECK(cexpTA2TV(&(yyval.val),(yyvsp[(2) - (2)].varp))); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 289 "cexp.y"
    { EVAL((yyvsp[(3) - (3)].varp)->type = CEXP_TYPE_BASE2PTR((yyvsp[(1) - (3)].typ));); CHECK(cexpTA2TV(&(yyval.val),(yyvsp[(3) - (3)].varp))); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 291 "cexp.y"
    { EVAL((yyvsp[(4) - (7)].varp)->type = (yyvsp[(1) - (7)].typ)); CHECK(cexpTA2TV(&(yyval.val),(yyvsp[(4) - (7)].varp))); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 295 "cexp.y"
    { CexpSym found;
					  EVAL(if (!(found = varCreate(ctx, (yyvsp[(2) - (2)].lstr), (yyvsp[(1) - (2)].typ)))) YYERROR; \
					  		CHECK(cexpTA2TV(&(yyval.val),&found->value)) );
					;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 300 "cexp.y"
    { CexpSym found;
					  EVAL(if (!(found = varCreate(ctx, (yyvsp[(3) - (3)].lstr), CEXP_TYPE_BASE2PTR((yyvsp[(1) - (3)].typ))))) YYERROR; \
					  		CHECK(cexpTA2TV(&(yyval.val),&found->value)));
					;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 305 "cexp.y"
    { CexpSym found;
					  EVAL(if (!(found = varCreate(ctx, (yyvsp[(4) - (7)].lstr), (yyvsp[(1) - (7)].typ)))) YYERROR; \
					  		CHECK(cexpTA2TV(&(yyval.val),&found->value)));
					;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 316 "cexp.y"
    { (yyval.val)=(yyvsp[(3) - (3)].val); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 320 "cexp.y"
    {	(yyval.val).type=TVoid; ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 322 "cexp.y"
    {
						(yyval.val).type=TVoid;
						yyerror(ctx, "unknown symbol/variable; '=' expected");
						YYERROR;
					;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 328 "cexp.y"
    {
						errmsg(ctx, ": symbol already defined; append '!' to enforce recast\n");
						YYERROR;
					;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 333 "cexp.y"
    {FILE *f=ctx->outf;
						(yyval.val)=(yyvsp[(1) - (2)].val);
						if (CEXP_TYPE_FPQ((yyvsp[(1) - (2)].val).type)) {
							CHECK(cexpTypeCast(&(yyvsp[(1) - (2)].val),TDouble,0));
							if (f)
								fprintf(f,"%f\n",(yyvsp[(1) - (2)].val).tv.d);
						}else {
							if (TUChar==(yyvsp[(1) - (2)].val).type) {
								unsigned char c=(yyvsp[(1) - (2)].val).tv.c,e=0;
								if (f) {
									fprintf(f,"0x%02x (%d)",c,c);
									switch (c) {
										case 0:	    e=1; c='0'; break;
										case '\t':	e=1; c='t'; break;
										case '\r':	e=1; c='r'; break;
										case '\n':	e=1; c='n'; break;
										case '\f':	e=1; c='f'; break;
										default: 	break;
									}
									if (isprint(c)) {
										fputc('\'',f);
										if (e) fputc('\\',f);
										fputc(c,f);
										fputc('\'',f);
									}
									fputc('\n',f);
								}
							} else {
								CHECK(cexpTypeCast(&(yyvsp[(1) - (2)].val),TULong,0));
								if (f)
									fprintf(f,"0x%08lx (%ld)\n",(yyvsp[(1) - (2)].val).tv.l,(yyvsp[(1) - (2)].val).tv.l);
							}
						}
					;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 371 "cexp.y"
    { (yyval.val)=(yyvsp[(3) - (3)].val); EVAL(CHECK(cexpTVAssign(&(yyvsp[(1) - (3)].lval), &(yyvsp[(3) - (3)].val)))); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 373 "cexp.y"
    { EVAL( \
						CHECK(cexpTA2TV(&(yyval.val),&(yyvsp[(1) - (3)].lval))); \
						CHECK(cexpTVBinOp(&(yyval.val), &(yyval.val), &(yyvsp[(3) - (3)].val), (yyvsp[(2) - (3)].binop))); \
						CHECK(cexpTVAssign(&(yyvsp[(1) - (3)].lval),&(yyval.val))); \
					  );
					;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 380 "cexp.y"
    { CexpSym found;
					  (yyval.val)=(yyvsp[(3) - (3)].val); EVAL(if (!(found=varCreate(ctx, (yyvsp[(1) - (3)].lstr), (yyvsp[(3) - (3)].val).type))) {	\
									YYERROR; 								\
								}\
								CHECK(cexpTVAssign(&found->value, &(yyvsp[(3) - (3)].val))); );
					;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 390 "cexp.y"
    { (yyval.val).tv.l = (yyvsp[(1) - (2)].ul) || cexpTVTrueQ(&(yyvsp[(2) - (2)].val));
					  (yyval.val).type = TULong;
					  POPEVAL; ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 394 "cexp.y"
    { (yyval.val).tv.l = (yyvsp[(1) - (2)].ul) && cexpTVTrueQ(&(yyvsp[(2) - (2)].val));
					  (yyval.val).type = TULong;
					  POPEVAL; ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 398 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OOr)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 400 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OXor)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 402 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OAnd)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 404 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),ONe)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 406 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OEq)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 408 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OGt)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 410 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OLt)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 412 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OLe)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 414 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OGe)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 416 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OShL)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 418 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OShR)); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 420 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OAdd)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 422 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OSub)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 424 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OMul)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 426 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),ODiv)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 428 "cexp.y"
    { CHECK(cexpTVBinOp(&(yyval.val),&(yyvsp[(1) - (3)].val),&(yyvsp[(3) - (3)].val),OMod)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 432 "cexp.y"
    { (yyval.ul)=cexpTVTrueQ(&(yyvsp[(1) - (2)].val)); PSHEVAL((yyval.ul)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 436 "cexp.y"
    { (yyval.ul)=cexpTVTrueQ(&(yyvsp[(1) - (2)].val)); PSHEVAL( ! (yyval.ul)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 440 "cexp.y"
    { (yyval.fixexp).lval=(yyvsp[(2) - (2)].lval); (yyval.fixexp).op=OSub; ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 442 "cexp.y"
    { (yyval.fixexp).lval=(yyvsp[(2) - (2)].lval); (yyval.fixexp).op=OAdd; ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 447 "cexp.y"
    { (yyval.fixexp).lval=(yyvsp[(1) - (2)].lval); (yyval.fixexp).op=OSub; ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 449 "cexp.y"
    { (yyval.fixexp).lval=(yyvsp[(1) - (2)].lval); (yyval.fixexp).op=OAdd; ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 451 "cexp.y"
    { (yyval.fixexp).lval=(yyvsp[(1) - (1)].lval); (yyval.fixexp).op=ONoop; ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 465 "cexp.y"
    { (yyval.val).type=TULong; (yyval.val).tv.l = ! cexpTVTrueQ(&(yyvsp[(2) - (2)].val)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 467 "cexp.y"
    { CHECK(cexpTVUnOp(&(yyval.val),&(yyvsp[(2) - (2)].val),OCpl)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 469 "cexp.y"
    { CHECK(cexpTVUnOp(&(yyval.val),&(yyvsp[(2) - (2)].val),ONeg)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 475 "cexp.y"
    { CHECK(cexpTVPtr(&(yyval.val), (yyvsp[(2) - (2)].varp))); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 479 "cexp.y"
    { (yyval.varp)=&(yyvsp[(1) - (1)].sym)->value; ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 481 "cexp.y"
    { (yyval.varp)=&(yyvsp[(1) - (1)].sym)->value; ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 484 "cexp.y"
    { (yyval.varp)=(yyvsp[(1) - (1)].varp); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 486 "cexp.y"
    { (yyval.varp)=&(yyvsp[(1) - (1)].sym)->value; ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 490 "cexp.y"
    { (yyval.lval) = *(yyvsp[(1) - (1)].varp); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 492 "cexp.y"
    { if (!CEXP_TYPE_PTRQ((yyvsp[(2) - (2)].val).type) || CEXP_TYPE_FUNQ((yyvsp[(2) - (2)].val).type)) {
						yyerror(ctx, "not a valid lval address");
						YYERROR;
					  }
					  (yyval.lval).type=CEXP_TYPE_PTR2BASE((yyvsp[(2) - (2)].val).type);
					  (yyval.lval).ptv=(CexpVal)(yyvsp[(2) - (2)].val).tv.p;
					;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 507 "cexp.y"
    { (yyval.typ)=TUChar; ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 509 "cexp.y"
    { (yyval.typ)=TUShort; ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 511 "cexp.y"
    { (yyval.typ)=TULong; ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 513 "cexp.y"
    { (yyval.typ)=TFloat; ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 515 "cexp.y"
    { (yyval.typ)=TDouble; ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 519 "cexp.y"
    { (yyval.typ)=(yyvsp[(2) - (3)].typ); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 524 "cexp.y"
    { (yyval.typ)=CEXP_TYPE_BASE2PTR((yyvsp[(2) - (4)].typ)); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 528 "cexp.y"
    { switch ((yyvsp[(1) - (1)].typ)) {
						default:
							yyerror(ctx, "invalid type for function pointer cast");
						YYERROR;

						case TDouble:
							(yyval.typ)=TDFuncP;
						break;

						case TULong:
							(yyval.typ)=TFuncP;
						break;
					  }
					;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 546 "cexp.y"
    { (yyval.typ)=(yyvsp[(2) - (8)].typ); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 550 "cexp.y"
    { (yyval.val).type=(yyvsp[(1) - (1)].sym)->value.type; (yyval.val).tv.p=(void*)(yyvsp[(1) - (1)].sym)->value.ptv; ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 552 "cexp.y"
    { (yyval.val).type=(yyvsp[(2) - (2)].sym)->value.type; (yyval.val).tv.p=(void*)(yyvsp[(2) - (2)].sym)->value.ptv; ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 554 "cexp.y"
    { CexpTypedValRec tmp;
					  EVAL( \
						CHECK(cexpTA2TV(&(yyval.val),&(yyvsp[(1) - (1)].fixexp).lval)); \
						tmp.type=TUChar; \
						tmp.tv.c=1; \
						if (ONoop != (yyvsp[(1) - (1)].fixexp).op) { \
							CHECK(cexpTVBinOp(&tmp,&(yyval.val),&tmp,(yyvsp[(1) - (1)].fixexp).op)); \
							CHECK(cexpTVAssign(&(yyvsp[(1) - (1)].fixexp).lval,&tmp)); \
						} \
					  );
					;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 566 "cexp.y"
    { CexpTypedValRec tmp;
					  EVAL( \
						CHECK(cexpTA2TV(&(yyval.val),&(yyvsp[(1) - (1)].fixexp).lval)); \
						tmp.type=TUChar; \
						tmp.tv.c=1; \
						if (ONoop != (yyvsp[(1) - (1)].fixexp).op) { \
							CHECK(cexpTVBinOp(&(yyval.val),&(yyval.val),&tmp,(yyvsp[(1) - (1)].fixexp).op)); \
							CHECK(cexpTVAssign(&(yyvsp[(1) - (1)].fixexp).lval,&(yyval.val))); \
						} \
					  );
					;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 581 "cexp.y"
    { (yyval.val)=(yyvsp[(2) - (2)].val); CHECK(cexpTypeCast(&(yyval.val),(yyvsp[(1) - (2)].typ),CNV_FORCE)); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 583 "cexp.y"
    { (yyval.val)=(yyvsp[(2) - (2)].val); CHECK(cexpTypeCast(&(yyval.val),(yyvsp[(1) - (2)].typ),CNV_FORCE)); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 585 "cexp.y"
    { (yyval.val)=(yyvsp[(2) - (2)].val); CHECK(cexpTypeCast(&(yyval.val),(yyvsp[(1) - (2)].typ),CNV_FORCE)); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 589 "cexp.y"
    { (yyval.method).sym = (yyvsp[(1) - (3)].sym); (yyval.method).mname=(yyvsp[(3) - (3)].lstr); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 591 "cexp.y"
    { (yyval.method).sym = (yyvsp[(1) - (3)].sym); (yyval.method).mname=(yyvsp[(3) - (3)].lstr); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 593 "cexp.y"
    { (yyval.method).sym = (yyvsp[(1) - (3)].sym); (yyval.method).mname=(yyvsp[(3) - (3)].lstr); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 599 "cexp.y"
    { (yyval.val)=(yyvsp[(2) - (3)].val); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 602 "cexp.y"
    {	EVAL(CHECK(cexpSymMember(&(yyval.val), (yyvsp[(1) - (3)].method).sym, (yyvsp[(1) - (3)].method).mname, 0))); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 604 "cexp.y"
    {	EVAL(CHECK(cexpSymMember(&(yyval.val), (yyvsp[(1) - (4)].method).sym, (yyvsp[(1) - (4)].method).mname, &(yyvsp[(3) - (4)].val), 0))); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 606 "cexp.y"
    {	EVAL(CHECK(cexpSymMember(&(yyval.val), (yyvsp[(1) - (6)].method).sym, (yyvsp[(1) - (6)].method).mname, &(yyvsp[(3) - (6)].val), &(yyvsp[(5) - (6)].val), 0))); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 608 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (3)].val),0))); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 610 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (4)].val),&(yyvsp[(3) - (4)].val),0))); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 612 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (6)].val),&(yyvsp[(3) - (6)].val),&(yyvsp[(5) - (6)].val),0))); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 614 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (8)].val),&(yyvsp[(3) - (8)].val),&(yyvsp[(5) - (8)].val),&(yyvsp[(7) - (8)].val),0))); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 616 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (10)].val),&(yyvsp[(3) - (10)].val),&(yyvsp[(5) - (10)].val),&(yyvsp[(7) - (10)].val),&(yyvsp[(9) - (10)].val),0))); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 618 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (12)].val),&(yyvsp[(3) - (12)].val),&(yyvsp[(5) - (12)].val),&(yyvsp[(7) - (12)].val),&(yyvsp[(9) - (12)].val),&(yyvsp[(11) - (12)].val),0))); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 620 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (14)].val),&(yyvsp[(3) - (14)].val),&(yyvsp[(5) - (14)].val),&(yyvsp[(7) - (14)].val),&(yyvsp[(9) - (14)].val),&(yyvsp[(11) - (14)].val),&(yyvsp[(13) - (14)].val),0))); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 622 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (16)].val),&(yyvsp[(3) - (16)].val),&(yyvsp[(5) - (16)].val),&(yyvsp[(7) - (16)].val),&(yyvsp[(9) - (16)].val),&(yyvsp[(11) - (16)].val),&(yyvsp[(13) - (16)].val),&(yyvsp[(15) - (16)].val),0))); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 624 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (18)].val),&(yyvsp[(3) - (18)].val),&(yyvsp[(5) - (18)].val),&(yyvsp[(7) - (18)].val),&(yyvsp[(9) - (18)].val),&(yyvsp[(11) - (18)].val),&(yyvsp[(13) - (18)].val),&(yyvsp[(15) - (18)].val),&(yyvsp[(17) - (18)].val),0))); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 626 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (20)].val),&(yyvsp[(3) - (20)].val),&(yyvsp[(5) - (20)].val),&(yyvsp[(7) - (20)].val),&(yyvsp[(9) - (20)].val),&(yyvsp[(11) - (20)].val),&(yyvsp[(13) - (20)].val),&(yyvsp[(15) - (20)].val),&(yyvsp[(17) - (20)].val),&(yyvsp[(19) - (20)].val),0))); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 628 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (22)].val),&(yyvsp[(3) - (22)].val),&(yyvsp[(5) - (22)].val),&(yyvsp[(7) - (22)].val),&(yyvsp[(9) - (22)].val),&(yyvsp[(11) - (22)].val),&(yyvsp[(13) - (22)].val),&(yyvsp[(15) - (22)].val),&(yyvsp[(17) - (22)].val),&(yyvsp[(19) - (22)].val),&(yyvsp[(21) - (22)].val),0))); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 630 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (24)].val),&(yyvsp[(3) - (24)].val),&(yyvsp[(5) - (24)].val),&(yyvsp[(7) - (24)].val),&(yyvsp[(9) - (24)].val),&(yyvsp[(11) - (24)].val),&(yyvsp[(13) - (24)].val),&(yyvsp[(15) - (24)].val),&(yyvsp[(17) - (24)].val),&(yyvsp[(19) - (24)].val),&(yyvsp[(21) - (24)].val),&(yyvsp[(23) - (24)].val),0))); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 632 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (26)].val),&(yyvsp[(3) - (26)].val),&(yyvsp[(5) - (26)].val),&(yyvsp[(7) - (26)].val),&(yyvsp[(9) - (26)].val),&(yyvsp[(11) - (26)].val),&(yyvsp[(13) - (26)].val),&(yyvsp[(15) - (26)].val),&(yyvsp[(17) - (26)].val),&(yyvsp[(19) - (26)].val),&(yyvsp[(21) - (26)].val),&(yyvsp[(23) - (26)].val),&(yyvsp[(25) - (26)].val),0))); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 634 "cexp.y"
    {	EVAL(CHECK(cexpTVFnCall(&(yyval.val),&(yyvsp[(1) - (28)].val),&(yyvsp[(3) - (28)].val),&(yyvsp[(5) - (28)].val),&(yyvsp[(7) - (28)].val),&(yyvsp[(9) - (28)].val),&(yyvsp[(11) - (28)].val),&(yyvsp[(13) - (28)].val),&(yyvsp[(15) - (28)].val),&(yyvsp[(17) - (28)].val),&(yyvsp[(19) - (28)].val),&(yyvsp[(21) - (28)].val),&(yyvsp[(23) - (28)].val),&(yyvsp[(25) - (28)].val),&(yyvsp[(27) - (28)].val),0))); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2598 "cexp.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
      yyerror (ctx, YY_("syntax error"));
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
	    yyerror (ctx, yymsg);
	  }
	else
	  {
	    yyerror (ctx, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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
		      yytoken, &yylval, ctx);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, ctx);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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
  yyerror (ctx, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, ctx);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, ctx);
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
#line 638 "cexp.y"



/* add a string to the line string table returning its index
 * RETURNS a negative number on error
 */
LString
lstAddString(CexpParserCtx env, char *string)
{
LString			rval=0;
LString			*chppt;
int				i;
	for (i=0,chppt=env->lineStrTbl;
		 i<sizeof(env->lineStrTbl)/sizeof(env->lineStrTbl[0]);
		 i++,chppt++) {
		if (*chppt) {
			if  (strcmp(string,*chppt))			continue;
			else /* string exists already */	return *chppt;
		}
		/* string exists already */
		if ((rval=malloc(strlen(string)+1))) {
			*chppt=rval;
			strcpy(rval,string);
			return (LString) rval;
		}
	}
	if ( env->errf )
		fprintf(env->errf,"Cexp: Line String Table exhausted\n");
	return 0;
}

#define ch (*pa->chpt)
#define getch() do { (pa->chpt)++;} while(0)

/* helper to save typing */
static int
prerr(CexpParserCtx ctx)
{
	errmsg(ctx, "(yylex): buffer overflow\n");
	return LEXERR;
}

static int
scanfrac(char *buf, char *chpt, int size, YYSTYPE *rval, CexpParserCtx pa, int rejectLonely)
{
int hasE=0;
	/* first, we put ch to the buffer */
	*(chpt++)=(char)ch; size--; /* assume it's still safe */
	getch();
	if ( isdigit(ch) || 'E' == toupper(ch) ) {
		do {
			while(isdigit(ch) && size) {
				*(chpt++)=(char)ch; if (!--size) return prerr(pa);
				getch();
			}
			if (toupper(ch)=='E' && !hasE) {
				*(chpt++)=(char)'E'; if (!--size) return prerr(pa);
				getch();
				if ('-'==ch || '+'==ch) {
					*(chpt++)=(char)ch; if (!--size) return prerr(pa);
					getch();
				}
				hasE=1;
			} else {
		break; /* the loop */
			}
		} while (1);
	} else {
		if ( rejectLonely )
			return '.';
	}
	*chpt=0;
	rval->val.type=TDouble;
	rval->val.tv.d=strtod(buf,&chpt);
	return *chpt ? LEXERR : NUMBER;
}

int
yylex(YYSTYPE *rval, CexpParserCtx pa)
{
unsigned long num;
int           limit=sizeof(pa->sbuf)-1;
char          *chpt;

	while (' '==ch || '\t'==ch)
		getch();

	if (isdigit(ch) || '\''==ch) {
		/* a number */
		num=0;

		if ('\''==ch) {
			/* char constant */
			getch();
			num=ch;
			if ('\\'==ch) {
				getch();
				/* escape sequence */
				switch (ch) {
					case 't': num='\t'; break;
					case 'n': num='\n'; break;
					case 'r': num='\r'; break;
					case '0': num=0;	break;
					case 'f': num='\f';	break;
					case '\\': num='\\';break;
					case '\'': num='\'';break;
					default:
						wrnmsg(pa, ": unknown escape sequence, using unescaped char\n");
						num=ch;
					break;
				}
			}
			getch();
			if ('\''!=ch)
				wrnmsg(pa, ": missing closing '\n");
			else
				getch();
			rval->val.tv.c=(unsigned char)num;
			rval->val.type=TUChar;
			return NUMBER;
		}
		chpt=pa->sbuf;
		if ('0'==ch) {
			
			/* hex, octal or fractional */
			*(chpt++)=(char)ch; limit--;
			getch();
			if ('x'==ch) {
				/* a hex number */
				getch();
				while (isxdigit(ch)) {
					num<<=4;
					if (ch>='a')		num+=ch-'a'+10;
					else if (ch>='A')	num+=ch-'A'+10;
					else				num+=ch-'0';
					getch();
				}
			} else if ('.'==ch) {
				/* a decimal number */
				return scanfrac(pa->sbuf,chpt,limit,rval,pa,0);
			} else {
				/* OK, it's octal */
				while ('0'<=ch && ch<'8') {
					num<<=3;
					num+=ch-'0';
					getch();
				}
			}
		} else {
			/* so it must be base 10 */
			do {
				*(chpt++)=(char)ch; limit--;
				num=10*num+(ch-'0');
				getch();
			} while (isdigit(ch) && limit);
			if (!limit) {
				return prerr(pa);
			}
			if ('.'==ch) {
				/* it's a fractional number */
				return scanfrac(pa->sbuf,chpt,limit,rval,pa,0);
			}
		}
		rval->val.tv.l=num;
		rval->val.type=TULong;
		return NUMBER;
	} else if ('.'==ch) {
		/* perhaps also a fractional number */
		return
			scanfrac(pa->sbuf,pa->sbuf,limit,rval,pa,1);
	} else if (isalpha(ch) || ISIDENTCHAR(ch)) {
		/* slurp in an identifier */
		chpt=pa->sbuf;
		do {
			*(chpt++)=ch;
			getch();
		} while ((isalnum(ch)||ISIDENTCHAR(ch)) && (--limit > 0));
		*chpt=0;
		if (!limit)
			return prerr(pa);
		/* is it one of the type cast keywords? */
		if (!strcmp(pa->sbuf,"char"))
			return KW_CHAR;
		else if (!strcmp(pa->sbuf,"short"))
			return KW_SHORT;
		else if (!strcmp(pa->sbuf,"long"))
			return KW_LONG;
		else if (!strcmp(pa->sbuf,"float"))
			return KW_FLOAT;
		else if (!strcmp(pa->sbuf,"double"))
			return KW_DOUBLE;
		else if ((rval->sym=cexpSymLookup(pa->sbuf, 0)))
			return CEXP_TYPE_FUNQ(rval->sym->value.type) ? FUNC : VAR;
		else if ((rval->sym=cexpVarLookup(pa->sbuf,0))) {
			return UVAR;
		}

		/* it's a currently undefined symbol */
		return (rval->lstr=lstAddString(pa,pa->sbuf)) ? IDENT : LEXERR;
	} else if ('"'==ch) {
		/* generate a string constant */
		char *dst;
		const char *strStart;
		dst=pa->sbuf-1;
		strStart = pa->chpt+1;
		do {
		skipit:	
			dst++; limit--;
			getch();
			*dst=ch;
			if ('\\'==ch) {
				getch();
				switch (ch) {
					case 'n':	*dst='\n'; goto skipit;
					case 'r':	*dst='\r'; goto skipit;
					case 't':	*dst='\t'; goto skipit;
					case '"':	*dst='"';  goto skipit;
					case '\\':	           goto skipit;
					case '0':	*dst=0;    goto skipit;
					default:
						dst++; limit--; *dst=ch;
						break;
				}
			}
			if ('"'==ch) {
				*dst=0;
				getch();
				rval->val.type=TUCharP;
#ifdef CONFIG_STRINGS_LIVE_FOREVER
				rval->val.tv.p=cexpStrLookup(pa->sbuf,1);
#else
				rval->val.tv.p=lstAddString(pa,pa->sbuf);
#endif
				return rval->val.tv.p ? STR_CONST : LEXERR;
			}
		} while (ch && limit>2);
		return LEXERR_INCOMPLETE_STRING - (pa->chpt - strStart);
	} else {
		long rv=ch;
		if (rv) getch();

		/* comments? skip the rest of the line */
		if ('#'==rv || ('/'==ch && '/'==rv)) {
			while (ch && '\n'!=rv) {
				rv=ch;
				getch();
			}
			return '\n';
		}

		/* it's any kind of 'special' character such as
		 * an operator etc.
		 */

		/* check for 'double' character operators '&&' '||' '<<' '>>' '==' '!=' '<=' '>=' */
		switch (ch) { /* the second character */
			default: break;

			case '+': if ('+'==rv) rv=PP;  break;
			case '-': if ('-'==rv) rv=MM;  break;

			case '&': if ('&'==rv) rv=AND; break;
			case '|': if ('|'==rv) rv=OR;  break;

			case '<': if ('<'==rv) rv=SHL; break;
			case '>': if ('>'==rv) rv=SHR; break;


			case '=':
				switch (rv) {
					default: break;
					case '=': rv=EQ;	break;
					case '!': rv=NE;	break;
					case '<': rv=LE;	break;
					case '>': rv=GE;	break;
					case '+': rv=MODOP; rval->binop=OAdd;	break;
					case '-': rv=MODOP; rval->binop=OSub;	break;
					case '*': rv=MODOP; rval->binop=OMul;	break;
					case '/': rv=MODOP; rval->binop=ODiv;	break;
					case '%': rv=MODOP; rval->binop=OMod;	break;
					case '&': rv=MODOP; rval->binop=OAnd;	break;
					case '^': rv=MODOP; rval->binop=OXor;	break;
					case '|': rv=MODOP; rval->binop=OOr;	break;
				}
			break;
		}
		if (rv>255) getch(); /* skip second char */
		/* yyparse cannot deal with '\0' chars, so we translate it back to '\n'...*/
		if ((SHL==rv || SHR==rv) && '=' == ch) {
			getch();
			rval->binop = (SHL==rv ? OShL : OShR);
			rv=MODOP;
		}
		return rv ? rv : '\n';
	}
	return 0; /* seems to mean ERROR/EOF */
}

/* re-initialize a parser context to parse 'buf';
 * If called with a NULL argument, a new
 * context is created and initialized.
 *
 * RETURNS: initialized context
 */

static void
releaseStrings(CexpParserCtx ctx)
{
int			i;
char		**chppt;

	/* release the line string table */
	for (i=0,chppt=ctx->lineStrTbl;
		 i<sizeof(ctx->lineStrTbl)/sizeof(ctx->lineStrTbl[0]);
		 i++,chppt++) {
		if (*chppt) {
			free(*chppt);
			*chppt=0;
		}
	}
}

CexpParserCtx
cexpCreateParserCtx(FILE *outf, FILE *errf, RedirCb redir_cb, void *uarg)
{
CexpParserCtx	ctx=0;

	assert(ctx=(CexpParserCtx)malloc(sizeof(*ctx)));
	memset(ctx,0,sizeof(*ctx));
	ctx->rval_sym.value.type = TULong;
	ctx->rval.l              = 0;
	ctx->rval_sym.value.ptv  = &ctx->rval;
	ctx->rval_sym.name       = CEXP_LAST_RESULT_VAR_NAME;
	ctx->rval_sym.size       = sizeof(ctx->rval);
	ctx->rval_sym.flags      = 0;
	ctx->rval_sym.help       = "value of last evaluated expression";
	ctx->outf                = outf;
	ctx->errf                = errf;
	ctx->status              = -1;
	ctx->o_stdout            = 0;
	ctx->o_stderr            = 0;
	ctx->o_stdin             = 0;
	ctx->o_outf              = 0;
	ctx->o_errf              = 0;
	ctx->redir_cb            = redir_cb;
	ctx->cb_arg              = uarg;

	return ctx;
}

void
cexpResetParserCtx(CexpParserCtx ctx, const char *buf)
{
	ctx->chpt=buf;
	ctx->evalInhibit=0;
	ctx->status = -1;
	cexpUnredir(ctx);
	releaseStrings(ctx);
}

void
cexpFreeParserCtx(CexpParserCtx ctx)
{
	cexpUnredir(ctx);
	releaseStrings(ctx);
	free(ctx);
}

CexpSym
cexpParserCtxGetResult(CexpParserCtx ctx)
{
	return &ctx->rval_sym;
}

int
cexpParserCtxGetStatus(CexpParserCtx ctx)
{
	return ctx->status;
}

void
yyerror(CexpParserCtx ctx, const char*msg)
{
va_list ap;
	if ( ctx->errf ) {
		fprintf(ctx->errf,"Cexp syntax error: %s\n", msg);
	}
}

/* Other errors that are not syntax errors */
static void
errmsg(CexpParserCtx ctx, const char *fmt, ...)
{
va_list ap;
	if ( ctx->errf ) {
		fprintf(ctx->errf,"Cexp error ");
		va_start(ap, fmt);
		vfprintf(ctx->errf, fmt, ap); 
		va_end(ap);
	}
}

static void
wrnmsg(CexpParserCtx ctx, const char *fmt, ...)
{
va_list ap;
	if ( ctx->errf ) {
		fprintf(ctx->errf,"Cexp warning ");
		va_start(ap, fmt);
		vfprintf(ctx->errf, fmt, ap); 
		va_end(ap);
	}
}


static int
cexpRedir(CexpParserCtx ctx, unsigned long op, void *oarg, void *iarg)
{
const char *opath = oarg;
const char *ipath = iarg;
FILE       *nof = 0, *nif = 0;
const char *mode;

	if ( !oarg && !iarg ) {
		errmsg(ctx, "(cexpRedir): NO PATH ARGUMENT ??\n");
		return -1;
	}

	if ( opath && (ctx->o_stdout || ctx->o_stderr) ) {
		errmsg(ctx, "(cexpRedir): OUTPUT ALREADY REDIRECTED ??\n");
		return -1;
	}

	if ( ipath && ctx->o_stdin ) {
		errmsg(ctx, "(cexpRedir): INPUT ALREADY REDIRECTED ??\n");
		return -1;
	}

	if ( ipath ) {
		if ( ! (nif = fopen(ipath, "r")) ) {
			if ( ctx->errf )
				fprintf(ctx->errf, "cexpRedir (IN) ERROR - unable to open file: %s\n", strerror(errno));
			return -1;
		}
		ctx->o_stdin = stdin;
		stdin        = nif;
	}

	if ( opath ) {
		if ( REDIRAPPEND == op || REDIRAPPENDBOTH == op )
			mode = "a";
		else
			mode = "w";

		if ( ! (nof = fopen(opath, mode)) ) {
			if ( ctx->errf )
				fprintf(ctx->errf, "cexpRedir (OUT) ERROR - unable to open file: %s\n", strerror(errno));
			if ( nif ) {
				stdin = ctx->o_stdin;
				fclose(nif);
			}
			return -1;
		}
		fflush(stdout);
		ctx->o_stdout = stdout;
		stdout = nof;

		if ( ctx->outf ) {
			fflush(ctx->outf);
			ctx->o_outf = ctx->outf;
			ctx->outf   = nof;
		}

		if ( REDIRBOTH == op || REDIRAPPENDBOTH == op ) {
			fflush(stderr);
			ctx->o_stderr = stderr;
			stderr = nof;

			if ( ctx->errf ) {
				fflush(ctx->errf);
				ctx->o_errf = ctx->errf;
				ctx->errf   = nof;
			}
		}
	}

	if ( ctx->redir_cb )
		ctx->redir_cb(ctx, ctx->cb_arg);

	return 0;
}

static void
cexpUnredir(CexpParserCtx ctx)
{
	if ( ctx->o_stdout ) {
		fclose(stdout);
		stdout = ctx->o_stdout;
		ctx->o_stdout = 0;
	}
	if ( ctx->o_outf ) {
		ctx->outf   = ctx->o_outf;
		ctx->o_outf = 0;
	}

	if ( ctx->o_stderr ) {
		stderr = ctx->o_stderr;
		ctx->o_stderr = 0;
	}
	if ( ctx->o_errf ) {
		ctx->errf   = ctx->o_errf;
		ctx->o_errf = 0;
	}

	if ( ctx->o_stdin ) {
		fclose(stdin);
		stdin = ctx->o_stdin;
		ctx->o_stdin = 0;
	}

	if ( ctx->redir_cb )
		ctx->redir_cb(ctx, ctx->cb_arg);
}

/* Trivial wrapper so that we can make sure
 * redirections are undone always and before
 * cexpparse() returns to the caller.
 */
int
cexpparse(CexpParserCtx ctx)
{
int rval;

	rval = __cexpparse(ctx);	
	cexpUnredir( ctx );

	return rval;
}

