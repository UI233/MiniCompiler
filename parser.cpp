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
#line 1 "parser.y" /* yacc.c:337  */

    #include "Ast.h"
    #include <fstream>
    SPL::CompoundAst* program;
    extern int yylineno;
    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %s\n at line:%d\n", s, yylineno); }


    //typedef struct para para;
    std::string true_string("true");
    std::string false_string("false");
    std::string maxint_string("maxint");
    std::string dotdot_string("..");
    std::string minus_string("-");
    std::string array_string("array:");
    int INT_MAX_SPL = 2147483647;
    std::string sys_funct[] = {"abs","chr","odd","ord","pred","sqr","sqrt","succ","read","write","writeln"};
    std::vector<std::string> SYS_FUNC_NAME(sys_funct, sys_funct+sizeof(sys_funct)/sizeof(sys_funct[1]));
    

#line 92 "parser.cpp" /* yacc.c:337  */
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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    TOKEN_SYS_CONST = 258,
    TOKEN_SYS_FUNCTION = 259,
    TOKEN_SYS_PROCEDURE = 260,
    TOKEN_SYS_TYPE = 261,
    TOKEN_READ = 262,
    TOKEN_INTEGER_LITERAL = 263,
    TOKEN_REAL_LITERAL = 264,
    TOKEN_CHAR_LITERAL = 265,
    TOKEN_ID = 266,
    TOKEN_LP = 267,
    TOKEN_RP = 268,
    TOKEN_LB = 269,
    TOKEN_RB = 270,
    TOKEN_DOT = 271,
    TOKEN_DOTDOT = 272,
    TOKEN_COMMA = 273,
    TOKEN_SEMI = 274,
    TOKEN_COLON = 275,
    TOKEN_ADD = 276,
    TOKEN_SUB = 277,
    TOKEN_MUL = 278,
    TOKEN_DIV = 279,
    TOKEN_MOD = 280,
    TOKEN_LT = 281,
    TOKEN_LE = 282,
    TOKEN_GT = 283,
    TOKEN_GE = 284,
    TOKEN_EQ = 285,
    TOKEN_NE = 286,
    TOKEN_ASSIGN = 287,
    TOKEN_NOT = 288,
    TOKEN_AND = 289,
    TOKEN_OR = 290,
    TOKEN_ARRAY = 291,
    TOKEN_BEGIN = 292,
    TOKEN_CASE = 293,
    TOKEN_CONST = 294,
    TOKEN_DO = 295,
    TOKEN_DOWNTO = 296,
    TOKEN_ELSE = 297,
    TOKEN_END = 298,
    TOKEN_FOR = 299,
    TOKEN_FUNCTION = 300,
    TOKEN_GOTO = 301,
    TOKEN_IF = 302,
    TOKEN_IN = 303,
    TOKEN_OF = 304,
    TOKEN_PROGRAM = 305,
    TOKEN_PROCEDURE = 306,
    TOKEN_PACKED = 307,
    TOKEN_RECORD = 308,
    TOKEN_REPEAT = 309,
    TOKEN_SET = 310,
    TOKEN_THEN = 311,
    TOKEN_TO = 312,
    TOKEN_TYPE = 313,
    TOKEN_UNTIL = 314,
    TOKEN_VAR = 315,
    TOKEN_WHILE = 316,
    TOKEN_WITH = 317
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "parser.y" /* yacc.c:352  */

	SPL::Ast *ast;
	SPL::ExprAst* exprast;
	SPL::IndexAst* indexast;
	SPL::MathAst* mathast;
	SPL::ConstAst* constast;
	SPL::SymbolAst* symbolast;
	SPL::CompoundAst* compoundast;
	SPL::TypeAst* typeast;
	SPL::SimpleTypeAst* simpletypeast;
	SPL::ArrayTypeAst* arraytypeast;
	SPL::RecordTypeAst* recordtypeast;
	SPL::TypeDeclAst* typedeclast;
	SPL::SimpleVarDeclAst* simplevardeclast;
	SPL::FuncDeclAst* funcdeclast;
	SPL::StmtAst* stmtast;
	SPL::AssignAst* assignast;
	SPL::IfAst* ifast;
	SPL::RepeatAst* repeatast;
	SPL::WhileAst* whileast;
	SPL::ForAst* forast;
	SPL::CaseUnit* caseunit;
	SPL::CaseAst* caseast;
	SPL::ParaDecl* paradecl;
	SPL::GotoAst* gotoast;

	std::vector<SPL::FuncDeclAst*>* vecfuncdeclastPtr;
	std::vector<struct para>* vecparaPtr;
	std::vector<std::string> * vecstrPtr;
	std::vector<SPL::StmtAst*>* vecstmtastPtr;
	std::vector<SPL::CaseUnit*>* veccaseunitPtr;
	std::pair<SPL::TypeAst*, std::vector<std::string> >* recordunit;
	std::string* stringPtr;
	std::vector<SPL::ExprAst*>* vecexprastPtr;
	int valInt;
	bool valbool;

#line 236 "parser.cpp" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */



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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   309

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  243

#define YYUNDEFTOK  2
#define YYMAXUTOK   317

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   150,   150,   154,   158,   166,   172,   180,   183,   185,
     190,   197,   202,   206,   210,   217,   220,   222,   226,   232,
     236,   239,   242,   247,   251,   254,   257,   260,   263,   267,
     287,   291,   294,   299,   303,   306,   313,   315,   317,   320,
     324,   334,   337,   341,   344,   347,   354,   358,   362,   366,
     369,   374,   378,   383,   387,   392,   397,   401,   410,   414,
     416,   420,   422,   424,   426,   428,   430,   432,   434,   436,
     438,   450,   452,   454,   458,   462,   464,   468,   472,   476,
     480,   482,   486,   490,   494,   497,   502,   504,   508,   510,
     512,   514,   516,   518,   520,   524,   526,   528,   530,   534,
     536,   538,   540,   542,   546,   548,   550,   552,   554,   556,
     558,   560,   572,   575,   578
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_SYS_CONST", "TOKEN_SYS_FUNCTION",
  "TOKEN_SYS_PROCEDURE", "TOKEN_SYS_TYPE", "TOKEN_READ",
  "TOKEN_INTEGER_LITERAL", "TOKEN_REAL_LITERAL", "TOKEN_CHAR_LITERAL",
  "TOKEN_ID", "TOKEN_LP", "TOKEN_RP", "TOKEN_LB", "TOKEN_RB", "TOKEN_DOT",
  "TOKEN_DOTDOT", "TOKEN_COMMA", "TOKEN_SEMI", "TOKEN_COLON", "TOKEN_ADD",
  "TOKEN_SUB", "TOKEN_MUL", "TOKEN_DIV", "TOKEN_MOD", "TOKEN_LT",
  "TOKEN_LE", "TOKEN_GT", "TOKEN_GE", "TOKEN_EQ", "TOKEN_NE",
  "TOKEN_ASSIGN", "TOKEN_NOT", "TOKEN_AND", "TOKEN_OR", "TOKEN_ARRAY",
  "TOKEN_BEGIN", "TOKEN_CASE", "TOKEN_CONST", "TOKEN_DO", "TOKEN_DOWNTO",
  "TOKEN_ELSE", "TOKEN_END", "TOKEN_FOR", "TOKEN_FUNCTION", "TOKEN_GOTO",
  "TOKEN_IF", "TOKEN_IN", "TOKEN_OF", "TOKEN_PROGRAM", "TOKEN_PROCEDURE",
  "TOKEN_PACKED", "TOKEN_RECORD", "TOKEN_REPEAT", "TOKEN_SET",
  "TOKEN_THEN", "TOKEN_TO", "TOKEN_TYPE", "TOKEN_UNTIL", "TOKEN_VAR",
  "TOKEN_WHILE", "TOKEN_WITH", "$accept", "program", "program_head",
  "routine", "sub_routine", "routine_head", "const_part",
  "const_expr_list", "const_ast", "type_part", "type_decl_list",
  "type_defination", "type_decl", "simple_type_decl", "array_type_decl",
  "record_type_decl", "field_decl_list", "field_decl", "name_list",
  "var_part", "var_decl_list", "var_decl", "routine_part", "function_decl",
  "procedure_decl", "parameters", "para_decl_list", "para_type_list",
  "var_para_list", "val_para_list", "routine_body", "compound_stmt",
  "stmt_list", "stmt", "non_label_stmt", "assign_stmt", "if_stmt",
  "else_clause", "repeat_stmt", "while_stmt", "for_stmt", "direction",
  "case_stmt", "goto_stmt", "case_expr_list", "case_expr", "expression",
  "expr", "term", "factor", "args_list", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317
};
# endif

#define YYPACT_NINF -132

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-132)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -38,     8,    54,    -6,    50,  -132,    78,    62,    55,    44,
    -132,    75,   106,  -132,  -132,  -132,  -132,   115,    71,    40,
     116,     9,   122,   115,  -132,   145,   -29,  -132,  -132,  -132,
    -132,   144,    40,   166,   153,    98,   212,  -132,   173,   177,
     212,  -132,   212,  -132,   175,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,   161,  -132,  -132,   121,   145,  -132,   184,
     185,   -29,  -132,  -132,  -132,   179,   212,    30,   212,   212,
     197,   212,   199,   113,   212,   212,  -132,   176,    10,    41,
    -132,   180,  -132,    67,    96,   202,  -132,  -132,   192,    40,
     204,   145,   210,   200,  -132,  -132,  -132,   215,   161,  -132,
     231,   231,  -132,  -132,  -132,   241,    26,  -132,    72,   209,
     227,   241,   212,   212,   212,   233,  -132,  -132,   212,   212,
     212,   212,   212,   212,   255,   212,   212,   212,   212,   212,
     212,   212,   212,   107,   212,   107,   250,   245,   171,    -1,
    -132,   129,    40,  -132,  -132,   260,    -3,   261,   263,  -132,
     212,  -132,   248,   212,    95,   103,   226,  -132,    10,    10,
      10,    10,    10,    10,   264,   265,    18,  -132,    41,    41,
      41,  -132,  -132,  -132,  -132,   160,   244,   241,  -132,  -132,
      15,   268,  -132,  -132,   161,  -132,  -132,   145,   269,    17,
    -132,   270,   271,   171,    -6,   241,   212,   241,  -132,  -132,
    -132,   107,   107,  -132,  -132,  -132,  -132,   212,   107,  -132,
      40,  -132,   239,   273,   269,  -132,    -3,   171,   171,   274,
     275,    55,   241,   276,   277,   220,  -132,  -132,   161,  -132,
    -132,  -132,  -132,    -6,  -132,  -132,  -132,  -132,   107,  -132,
     278,  -132,  -132
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     8,     0,     1,     0,     0,     0,    16,
       3,     0,     7,     2,    58,     4,    55,     0,    37,     0,
       0,     0,     0,    15,    18,     0,    43,    14,    11,    12,
      13,     0,     0,     0,     0,     0,     0,    56,     0,     0,
       0,    58,     0,    62,     0,    60,    61,    63,    64,    65,
      66,    67,    68,     0,    17,    35,     0,    36,    39,     0,
       0,     6,    42,    45,    10,     0,   114,     0,   114,     0,
       0,     0,     0,   105,     0,     0,   104,     0,    94,    98,
     103,     0,    83,     0,     0,     0,    57,    23,    24,     0,
       0,     0,     0,     0,    20,    21,    22,     0,     0,    38,
       0,     0,    41,    44,     9,   113,     0,    59,     0,     0,
       0,    71,   114,   114,     0,     0,   106,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,     0,     0,    19,    34,     0,     0,     0,     0,    70,
       0,    69,     0,     0,     0,     0,     0,   107,    91,    90,
      89,    88,    92,    93,     0,     0,     0,    85,    95,    96,
      97,    99,   100,   101,   102,     0,    76,    77,    78,    28,
       0,     0,    30,    31,     0,    25,    40,     0,    54,     0,
      50,     0,     0,     0,     8,   112,     0,    73,   111,   110,
     108,     0,     0,    82,    84,    81,    80,     0,     0,    74,
       0,    26,     0,     0,    53,    48,     0,     0,     0,     0,
       0,     0,    72,     0,     0,     0,    75,    27,     0,    33,
      49,    51,    52,     8,    47,     5,    87,    86,     0,    29,
       0,    79,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,  -132,    56,   295,  -132,  -132,   -18,  -132,
    -132,   279,   -96,  -131,  -132,  -132,  -132,   162,   -88,  -132,
    -132,   242,  -132,   243,   246,   205,  -132,    84,  -132,  -132,
      82,    -8,   267,  -129,   238,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,   143,   -31,   155,    33,     7,
     -53
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,   220,   221,     9,    12,    76,    18,
      23,    24,    93,    94,    95,    96,   139,   140,    56,    26,
      57,    58,    61,    62,    63,   147,   189,   190,   191,   192,
      15,    43,    21,    44,    45,    46,    47,   209,    48,    49,
      50,   207,    51,    52,   166,   167,   105,    78,    79,    80,
     106
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      16,    31,   145,   141,   176,    77,   178,   181,    55,    83,
      55,    85,     1,    33,    65,   108,    59,    34,    27,     4,
      35,    27,    60,    28,    29,    30,    28,    29,    30,   164,
     215,   125,   126,     6,    33,    92,   216,   210,   109,   149,
     111,    35,   182,    27,   150,   127,    14,    36,    28,    29,
      30,   141,    37,    38,     5,    39,    40,   187,   188,   154,
     155,   203,   219,    41,   128,   129,   130,    14,    36,    10,
      42,   137,   223,   224,    38,   131,    39,    40,    13,   226,
      92,   116,   117,   156,    41,   151,   231,   232,   213,    11,
     150,    42,    14,   118,   119,   120,   121,   122,   123,   214,
      33,   175,    17,   177,    34,    19,   165,    35,   198,   241,
      68,    33,    69,   150,    70,    34,   199,    20,    35,   195,
      92,   150,   197,   133,   185,   113,    22,   114,   188,   115,
      71,    25,   239,    14,    36,   171,   172,   173,   174,    97,
      38,    98,    39,    40,    14,    36,    32,    97,   165,   184,
      41,    38,    53,    39,    40,   134,    55,    42,   168,   169,
     170,    41,   211,    64,    27,   222,    92,    87,    42,    28,
      29,    30,    88,    67,    27,    92,   225,    87,    66,    28,
      29,    30,    88,    89,    81,    82,   118,   119,   120,   121,
     122,   123,   227,    89,    86,   100,   101,    90,   104,    92,
      92,   205,   118,   119,   120,   121,   122,   123,   110,   136,
      92,   112,   132,    16,    91,    27,    72,   206,   138,   143,
      28,    29,    30,    73,   152,   124,   144,   142,   118,   119,
     120,   121,   122,   123,    74,   118,   119,   120,   121,   122,
     123,   200,   135,   146,   157,    75,   118,   119,   120,   121,
     122,   123,   118,   119,   120,   121,   122,   123,    27,   153,
     238,   179,   180,    28,    29,    30,   164,   118,   119,   120,
     121,   122,   123,   158,   159,   160,   161,   162,   163,   186,
     196,   193,   194,   212,   201,   202,   208,    97,   228,   240,
     217,   218,   229,   233,   234,   236,   237,   242,     8,    99,
     230,   183,    54,   235,   102,   107,   148,   103,    84,   204
};

static const yytype_uint8 yycheck[] =
{
       8,    19,    98,    91,   133,    36,   135,   138,    11,    40,
      11,    42,    50,     4,    32,    68,    45,     8,     3,    11,
      11,     3,    51,     8,     9,    10,     8,     9,    10,    11,
      13,    21,    22,    39,     4,    53,    19,    22,    69,    13,
      71,    11,    43,     3,    18,    35,    37,    38,     8,     9,
      10,   139,    43,    44,     0,    46,    47,    60,   146,   112,
     113,    43,   193,    54,    23,    24,    25,    37,    38,    19,
      61,    89,   201,   202,    44,    34,    46,    47,    16,   208,
      98,    74,    75,   114,    54,    13,   217,   218,   184,    11,
      18,    61,    37,    26,    27,    28,    29,    30,    31,   187,
       4,   132,    58,   134,     8,    30,   124,    11,    13,   238,
      12,     4,    14,    18,    16,     8,    13,    11,    11,   150,
     138,    18,   153,    56,   142,    12,    11,    14,   216,    16,
      32,    60,   228,    37,    38,   128,   129,   130,   131,    18,
      44,    20,    46,    47,    37,    38,    30,    18,   166,    20,
      54,    44,    30,    46,    47,    59,    11,    61,   125,   126,
     127,    54,   180,    19,     3,   196,   184,     6,    61,     8,
       9,    10,    11,    20,     3,   193,   207,     6,    12,     8,
       9,    10,    11,    22,    11,     8,    26,    27,    28,    29,
      30,    31,   210,    22,    19,    11,    11,    36,    19,   217,
     218,    41,    26,    27,    28,    29,    30,    31,    11,    17,
     228,    12,    32,   221,    53,     3,     4,    57,    14,    19,
       8,     9,    10,    11,    15,    49,    11,    17,    26,    27,
      28,    29,    30,    31,    22,    26,    27,    28,    29,    30,
      31,    15,    40,    12,    11,    33,    26,    27,    28,    29,
      30,    31,    26,    27,    28,    29,    30,    31,     3,    32,
      40,    11,    17,     8,     9,    10,    11,    26,    27,    28,
      29,    30,    31,   118,   119,   120,   121,   122,   123,    19,
      32,    20,    19,    15,    20,    20,    42,    18,    49,   233,
      20,    20,    19,    19,    19,    19,    19,    19,     3,    57,
     216,   139,    23,   221,    61,    67,   101,    61,    41,   166
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    64,    65,    11,     0,    39,    66,    68,    69,
      19,    11,    70,    16,    37,    93,    94,    58,    72,    30,
      11,    95,    11,    73,    74,    60,    82,     3,     8,     9,
      10,    71,    30,     4,     8,    11,    38,    43,    44,    46,
      47,    54,    61,    94,    96,    97,    98,    99,   101,   102,
     103,   105,   106,    30,    74,    11,    81,    83,    84,    45,
      51,    85,    86,    87,    19,    71,    12,    20,    12,    14,
      16,    32,     4,    11,    22,    33,    71,   109,   110,   111,
     112,    11,     8,   109,    95,   109,    19,     6,    11,    22,
      36,    53,    71,    75,    76,    77,    78,    18,    20,    84,
      11,    11,    86,    87,    19,   109,   113,    97,   113,   109,
      11,   109,    12,    12,    14,    16,   112,   112,    26,    27,
      28,    29,    30,    31,    49,    21,    22,    35,    23,    24,
      25,    34,    32,    56,    59,    40,    17,    71,    14,    79,
      80,    81,    17,    19,    11,    75,    12,    88,    88,    13,
      18,    13,    15,    32,   113,   113,   109,    11,   110,   110,
     110,   110,   110,   110,    11,    71,   107,   108,   111,   111,
     111,   112,   112,   112,   112,   109,    96,   109,    96,    11,
      17,    76,    43,    80,    20,    71,    19,    60,    81,    89,
      90,    91,    92,    20,    19,   109,    32,   109,    13,    13,
      15,    20,    20,    43,   108,    41,    57,   104,    42,   100,
      22,    71,    15,    75,    81,    13,    19,    20,    20,    76,
      67,    68,   109,    96,    96,   109,    96,    71,    49,    19,
      90,    76,    76,    19,    19,    93,    19,    19,    40,    75,
      67,    96,    19
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    66,    67,    68,    69,    69,    70,
      70,    71,    71,    71,    71,    72,    72,    73,    73,    74,
      75,    75,    75,    76,    76,    76,    76,    76,    76,    77,
      78,    79,    79,    80,    81,    81,    82,    82,    83,    83,
      84,    85,    85,    85,    85,    85,    86,    87,    88,    89,
      89,    90,    90,    91,    92,    93,    94,    95,    95,    96,
      96,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    98,    98,    98,    99,   100,   100,   101,   102,   103,
     104,   104,   105,   106,   107,   107,   108,   108,   109,   109,
     109,   109,   109,   109,   109,   110,   110,   110,   110,   111,
     111,   111,   111,   111,   112,   112,   112,   112,   112,   112,
     112,   112,   113,   113,   113
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     4,     2,     0,     5,
       4,     1,     1,     1,     1,     2,     0,     2,     1,     4,
       1,     1,     1,     1,     1,     3,     4,     5,     3,     6,
       3,     2,     1,     4,     3,     1,     2,     0,     2,     1,
       4,     2,     1,     0,     2,     1,     8,     6,     3,     3,
       1,     3,     3,     2,     1,     1,     3,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     3,     6,     5,     5,     2,     0,     4,     4,     8,
       1,     1,     5,     2,     2,     1,     4,     4,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     1,     3,
       3,     3,     3,     1,     1,     1,     2,     3,     4,     2,
       4,     4,     3,     1,     0
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
        case 2:
#line 150 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
}
#line 1528 "parser.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 154 "parser.y" /* yacc.c:1652  */
    {
	;
}
#line 1536 "parser.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 158 "parser.y" /* yacc.c:1652  */
    {
//TODO
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast) -> merge((yyvsp[0].compoundast));
	program = (yyval.compoundast);
	//program = $$;
}
#line 1548 "parser.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 166 "parser.y" /* yacc.c:1652  */
    {
	//$$ = new SPL::RoutineAst($<routineheadast>1, $<compoundast>2);
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast) -> merge((yyvsp[0].compoundast));
}
#line 1558 "parser.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 172 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-3].compoundast);
	if ((yyval.compoundast)==nullptr) (yyval.compoundast) = new SPL::CompoundAst(std::vector<SPL::StmtAst*>());
	(yyval.compoundast) -> merge((yyvsp[-2].compoundast));
	(yyval.compoundast) -> merge((yyvsp[-1].compoundast));
	(yyval.compoundast) -> merge((yyvsp[0].compoundast));
}
#line 1570 "parser.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 180 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
}
#line 1578 "parser.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 183 "parser.y" /* yacc.c:1652  */
    {(yyval.compoundast) = nullptr;}
#line 1584 "parser.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 185 "parser.y" /* yacc.c:1652  */
    {
	SPL::ConstDeclAst* t = new SPL::ConstDeclAst(*(yyvsp[-3].stringPtr), (yyvsp[-1].constast)->getType(), (yyvsp[-1].constast)->getValue());
	(yyval.compoundast) = (yyvsp[-4].compoundast);
	(yyval.compoundast)->addStmt(t);
}
#line 1594 "parser.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 190 "parser.y" /* yacc.c:1652  */
    {
	SPL::ConstDeclAst* t = new SPL::ConstDeclAst(*(yyvsp[-3].stringPtr), (yyvsp[-1].constast)->getType(), (yyvsp[-1].constast)->getValue());
	std::vector<SPL::StmtAst*> vect;
	vect.push_back(t);
	(yyval.compoundast) = new SPL::CompoundAst(vect);
}
#line 1605 "parser.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 197 "parser.y" /* yacc.c:1652  */
    {
	std::string* t = (yyvsp[0].stringPtr);
	(yyval.constast) = new SPL::ConstAst(std::stoi(*t));

}
#line 1615 "parser.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 202 "parser.y" /* yacc.c:1652  */
    {
	std::string* t = (yyvsp[0].stringPtr);
	(yyval.constast) = new SPL::ConstAst(std::stod(*t));
}
#line 1624 "parser.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 206 "parser.y" /* yacc.c:1652  */
    {
	std::string* t = (yyvsp[0].stringPtr);
	(yyval.constast) = new SPL::ConstAst((*t)[1]);
}
#line 1633 "parser.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 210 "parser.y" /* yacc.c:1652  */
    {
	std::string* t = (yyvsp[0].stringPtr);
	if (*t == maxint_string)  (yyval.constast) = new SPL::ConstAst(INT_MAX_SPL);
	else if (*t == true_string) (yyval.constast) = new SPL::ConstAst(true);
	else if (*t == false_string) (yyval.constast) = new SPL::ConstAst(false);
}
#line 1644 "parser.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 217 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
}
#line 1652 "parser.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 220 "parser.y" /* yacc.c:1652  */
    {(yyval.compoundast) = nullptr; }
#line 1658 "parser.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 222 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast)->addStmt((yyvsp[0].typedeclast));
}
#line 1667 "parser.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 226 "parser.y" /* yacc.c:1652  */
    {
	std::vector<SPL::StmtAst*> vect;
	vect.push_back((yyvsp[0].typedeclast));
	(yyval.compoundast) = new SPL::CompoundAst(vect);
}
#line 1677 "parser.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 232 "parser.y" /* yacc.c:1652  */
    {
	(yyval.typedeclast) = new SPL::TypeDeclAst(*((yyvsp[-3].stringPtr)), (yyvsp[-1].typeast));
}
#line 1685 "parser.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 236 "parser.y" /* yacc.c:1652  */
    {
	(yyval.typeast) = (yyvsp[0].simpletypeast);
}
#line 1693 "parser.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 239 "parser.y" /* yacc.c:1652  */
    {
	(yyval.typeast) = (yyvsp[0].arraytypeast);
}
#line 1701 "parser.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 242 "parser.y" /* yacc.c:1652  */
    {
	(yyval.typeast) = (yyvsp[0].recordtypeast);
}
#line 1709 "parser.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 247 "parser.y" /* yacc.c:1652  */
    {
	std::string t = *((yyvsp[0].stringPtr));
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(t);
}
#line 1718 "parser.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 251 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(*((yyvsp[0].stringPtr)));
}
#line 1726 "parser.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 254 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(std::to_string(((yyvsp[-2].constast))->getValue().valInt)+dotdot_string+std::to_string(((yyvsp[0].constast))->getValue().valInt));
}
#line 1734 "parser.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 257 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(minus_string+std::to_string(((yyvsp[-2].constast))->getValue().valInt)+dotdot_string+std::to_string(((yyvsp[0].constast))->getValue().valInt));
}
#line 1742 "parser.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 260 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(minus_string+std::to_string(((yyvsp[-3].constast))->getValue().valInt)+dotdot_string+minus_string+std::to_string(((yyvsp[0].constast))->getValue().valInt));
}
#line 1750 "parser.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 263 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(*((yyvsp[-2].stringPtr))+dotdot_string+*((yyvsp[0].stringPtr)));
}
#line 1758 "parser.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 267 "parser.y" /* yacc.c:1652  */
    {
	std::string str = ((yyvsp[-3].simpletypeast))->getName();
	int i=0;
	for ( ;i<str.length();i++) {
		if (str[i]=='.') break;
	}
	std::string minstr = str.substr(0,i);
	std::string maxstr = str.substr(i+2);
	SPL::IndexAst* minIndex_=nullptr;
	SPL::IndexAst* maxIndex_=nullptr;
	if ((minstr[0]<='z'&&minstr[0]>='a')||(minstr[0]<='Z'&&minstr[0]>='A')) {
		minIndex_ = new SPL::SymbolAst(minstr);
		maxIndex_ = new SPL::SymbolAst(maxstr);
	} else {
		minIndex_ = new SPL::ConstAst(std::stoi(minstr));
		maxIndex_ = new SPL::ConstAst(std::stoi(maxstr));
	}
	(yyval.arraytypeast) = new SPL::ArrayTypeAst( (yyvsp[0].typeast) , minIndex_, maxIndex_);
}
#line 1782 "parser.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 287 "parser.y" /* yacc.c:1652  */
    {
	(yyval.recordtypeast) = (yyvsp[-1].recordtypeast);
}
#line 1790 "parser.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 291 "parser.y" /* yacc.c:1652  */
    {
	(yyval.recordtypeast) = (yyvsp[-1].recordtypeast);
	(yyval.recordtypeast) -> addMember(*(yyvsp[0].recordunit));
}
#line 1799 "parser.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 294 "parser.y" /* yacc.c:1652  */
    {
	(yyval.recordtypeast) = new SPL::RecordTypeAst();
	(yyval.recordtypeast) -> addMember(*(yyvsp[0].recordunit));
}
#line 1808 "parser.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 299 "parser.y" /* yacc.c:1652  */
    {
	(yyval.recordunit) = new std::pair<SPL::TypeAst*, std::vector<std::string> > ((yyvsp[-1].typeast), *(yyvsp[-3].vecstrPtr));
}
#line 1816 "parser.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 303 "parser.y" /* yacc.c:1652  */
    {
	(yyvsp[-2].vecstrPtr)->push_back(*(yyvsp[0].stringPtr));
	(yyval.vecstrPtr) = (yyvsp[-2].vecstrPtr);
}
#line 1825 "parser.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 306 "parser.y" /* yacc.c:1652  */
    {
	std::string t = std::string(*((yyvsp[0].stringPtr)));
	(yyval.vecstrPtr) = new std::vector<std::string> ();
	(yyval.vecstrPtr)->push_back(t);
}
#line 1835 "parser.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 313 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
}
#line 1843 "parser.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 315 "parser.y" /* yacc.c:1652  */
    {(yyval.compoundast) = nullptr;}
#line 1849 "parser.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 317 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast)->merge((yyvsp[0].compoundast));
}
#line 1858 "parser.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 320 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
}
#line 1866 "parser.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 324 "parser.y" /* yacc.c:1652  */
    {

	(yyval.compoundast) = new SPL::CompoundAst(std::vector<SPL::StmtAst*> () );
	for (auto name: *((yyvsp[-3].vecstrPtr)) ) {
		(yyval.compoundast) -> addStmt(new SPL::SimpleVarDeclAst(name, (yyvsp[-1].typeast) ));
	}

}
#line 1879 "parser.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 334 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast)->addStmt((yyvsp[0].funcdeclast));
}
#line 1888 "parser.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 337 "parser.y" /* yacc.c:1652  */
    {
	std::vector<SPL::StmtAst*> t;
	t.push_back((yyvsp[0].funcdeclast));
	(yyval.compoundast) = new SPL::CompoundAst(t);
}
#line 1898 "parser.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 341 "parser.y" /* yacc.c:1652  */
    {
	std::vector<SPL::StmtAst*> t;
	(yyval.compoundast) = new SPL::CompoundAst(t);
}
#line 1907 "parser.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 344 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast)->addStmt((yyvsp[0].funcdeclast));
}
#line 1916 "parser.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 347 "parser.y" /* yacc.c:1652  */
    {
	std::vector<SPL::StmtAst*> t;
	t.push_back((yyvsp[0].funcdeclast));
	(yyval.compoundast) = new SPL::CompoundAst(t);
}
#line 1926 "parser.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 354 "parser.y" /* yacc.c:1652  */
    {
	(yyval.funcdeclast) = new SPL::FuncDeclAst(*((yyvsp[-6].stringPtr)), (yyvsp[-1].compoundast), (yyvsp[-5].paradecl)->args, (yyvsp[-5].paradecl)->is_var, (yyvsp[-3].typeast) );
}
#line 1934 "parser.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 358 "parser.y" /* yacc.c:1652  */
    {
	(yyval.funcdeclast) = new SPL::FuncDeclAst(*((yyvsp[-4].stringPtr)), (yyvsp[-1].compoundast), (yyvsp[-3].paradecl)->args, (yyvsp[-3].paradecl)->is_var, nullptr );
}
#line 1942 "parser.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 362 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = (yyvsp[-1].paradecl);
}
#line 1950 "parser.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 366 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = (yyvsp[-2].paradecl);
	(yyval.paradecl) -> addList((yyvsp[0].paradecl));
}
#line 1959 "parser.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 369 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = new SPL::ParaDecl();
	(yyval.paradecl) -> addList((yyvsp[0].paradecl));
}
#line 1968 "parser.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 374 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = new SPL::ParaDecl();
	(yyval.paradecl)->addPara(*(yyvsp[-2].vecstrPtr), (yyvsp[0].typeast), true);
}
#line 1977 "parser.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 378 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = new SPL::ParaDecl();
	(yyval.paradecl)->addPara(*(yyvsp[-2].vecstrPtr), (yyvsp[0].typeast), false);
}
#line 1986 "parser.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 383 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecstrPtr) = (yyvsp[0].vecstrPtr);
}
#line 1994 "parser.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 387 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecstrPtr) = (yyvsp[0].vecstrPtr);
}
#line 2002 "parser.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 392 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
	//program_routine_body = $<compoundast>1;
}
#line 2011 "parser.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 397 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = new SPL::CompoundAst(*(yyvsp[-1].vecstmtastPtr));
}
#line 2019 "parser.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 401 "parser.y" /* yacc.c:1652  */
    {
	if ((yyvsp[-2].vecstmtastPtr)) {
		(yyval.vecstmtastPtr) = (yyvsp[-2].vecstmtastPtr);
		(yyval.vecstmtastPtr)->push_back((yyvsp[-1].stmtast));
	} else {
		(yyval.vecstmtastPtr) = new std::vector<SPL::StmtAst*> ();
		(yyval.vecstmtastPtr)->push_back((yyvsp[-1].stmtast));
	}
}
#line 2033 "parser.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 410 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecstmtastPtr) = nullptr;
}
#line 2041 "parser.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 414 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = new SPL::LabelAst(std::stoi(*(yyvsp[-2].stringPtr)), (yyvsp[0].stmtast));
}
#line 2049 "parser.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 416 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].stmtast);
}
#line 2057 "parser.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 420 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].assignast);
}
#line 2065 "parser.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 422 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].compoundast);
}
#line 2073 "parser.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 424 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].ifast);
}
#line 2081 "parser.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 426 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].repeatast);
}
#line 2089 "parser.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 428 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].whileast);
}
#line 2097 "parser.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 430 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].forast);
}
#line 2105 "parser.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 432 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].caseast);
}
#line 2113 "parser.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 434 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].gotoast);
}
#line 2121 "parser.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 436 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = new SPL::FuncAst(*(yyvsp[-3].stringPtr), *(yyvsp[-1].vecexprastPtr));
}
#line 2129 "parser.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 438 "parser.y" /* yacc.c:1652  */
    {
	SYS_FUNC_ID sys_func_id = (SYS_FUNC_ID)0;
	std::string sysname = *(yyvsp[-3].stringPtr);
	for (int i=0;i<SYS_FUNC_NAME.size();i++) {
		if (sysname == SYS_FUNC_NAME[i]) {
			sys_func_id = (SYS_FUNC_ID)i;
			break;
		}
	}
	(yyval.stmtast) = new SPL::SysFuncAst(sys_func_id, *(yyvsp[-1].vecexprastPtr));
}
#line 2145 "parser.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 450 "parser.y" /* yacc.c:1652  */
    {
	(yyval.assignast) = new SPL::AssignAst(new SPL::SymbolAst(*((yyvsp[-2].stringPtr))), (yyvsp[0].exprast) );
}
#line 2153 "parser.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 452 "parser.y" /* yacc.c:1652  */
    {
	(yyval.assignast) = new SPL::AssignAst(new SPL::ArrayAst(new SPL::SymbolAst(*((yyvsp[-5].stringPtr))), (yyvsp[-3].exprast)), (yyvsp[0].exprast) );	
}
#line 2161 "parser.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 454 "parser.y" /* yacc.c:1652  */
    {
	(yyval.assignast) = new SPL::AssignAst(new SPL::DotAst(new SPL::SymbolAst(*((yyvsp[-4].stringPtr))), *((yyvsp[-2].stringPtr)) ), (yyvsp[0].exprast) );
}
#line 2169 "parser.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 458 "parser.y" /* yacc.c:1652  */
    {
	(yyval.ifast) = new SPL::IfAst((yyvsp[-3].exprast), (yyvsp[-1].stmtast), (yyvsp[0].stmtast));
}
#line 2177 "parser.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 462 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].stmtast);
}
#line 2185 "parser.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 464 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = nullptr;
}
#line 2193 "parser.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 468 "parser.y" /* yacc.c:1652  */
    {
	(yyval.repeatast) = new SPL::RepeatAst(*(yyvsp[-2].vecstmtastPtr), (yyvsp[0].exprast));
}
#line 2201 "parser.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 472 "parser.y" /* yacc.c:1652  */
    {
	(yyval.whileast) = new SPL::WhileAst((yyvsp[-2].exprast),(yyvsp[0].stmtast));
}
#line 2209 "parser.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 476 "parser.y" /* yacc.c:1652  */
    {
	(yyval.forast) = new SPL::ForAst(new SPL::SymbolAst(*(yyvsp[-6].stringPtr)),(yyvsp[-4].exprast),(yyvsp[-3].valbool),(yyvsp[-2].exprast),(yyvsp[0].stmtast));
}
#line 2217 "parser.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 480 "parser.y" /* yacc.c:1652  */
    {
	(yyval.valbool) = true;
}
#line 2225 "parser.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 482 "parser.y" /* yacc.c:1652  */
    {
	(yyval.valbool) = false;
}
#line 2233 "parser.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 486 "parser.y" /* yacc.c:1652  */
    {
	(yyval.caseast) = new SPL::CaseAst((yyvsp[-3].exprast), *(yyvsp[-1].veccaseunitPtr));
}
#line 2241 "parser.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 490 "parser.y" /* yacc.c:1652  */
    {
	(yyval.gotoast) = new SPL::GotoAst(std::stoi(*(yyvsp[-1].stringPtr)));
}
#line 2249 "parser.cpp" /* yacc.c:1652  */
    break;

  case 84:
#line 494 "parser.y" /* yacc.c:1652  */
    {
	(yyval.veccaseunitPtr) = (yyvsp[-1].veccaseunitPtr);
	(yyval.veccaseunitPtr)->push_back((yyvsp[0].caseunit));
}
#line 2258 "parser.cpp" /* yacc.c:1652  */
    break;

  case 85:
#line 497 "parser.y" /* yacc.c:1652  */
    {
	(yyval.veccaseunitPtr) = new std::vector<SPL::CaseUnit*>();
	(yyval.veccaseunitPtr)->push_back((yyvsp[0].caseunit));
}
#line 2267 "parser.cpp" /* yacc.c:1652  */
    break;

  case 86:
#line 502 "parser.y" /* yacc.c:1652  */
    {
	(yyval.caseunit) = new SPL::CaseUnit((yyvsp[-3].exprast), (yyvsp[-1].stmtast));
}
#line 2275 "parser.cpp" /* yacc.c:1652  */
    break;

  case 87:
#line 504 "parser.y" /* yacc.c:1652  */
    {
	(yyval.caseunit) = new SPL::CaseUnit((yyvsp[-3].exprast), (yyvsp[-1].stmtast));
}
#line 2283 "parser.cpp" /* yacc.c:1652  */
    break;

  case 88:
#line 508 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_GE,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2291 "parser.cpp" /* yacc.c:1652  */
    break;

  case 89:
#line 510 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_GT,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2299 "parser.cpp" /* yacc.c:1652  */
    break;

  case 90:
#line 512 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_LE,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2307 "parser.cpp" /* yacc.c:1652  */
    break;

  case 91:
#line 514 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_LT,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2315 "parser.cpp" /* yacc.c:1652  */
    break;

  case 92:
#line 516 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_EQ,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2323 "parser.cpp" /* yacc.c:1652  */
    break;

  case 93:
#line 518 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_NE,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2331 "parser.cpp" /* yacc.c:1652  */
    break;

  case 94:
#line 520 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = (yyvsp[0].exprast);
}
#line 2339 "parser.cpp" /* yacc.c:1652  */
    break;

  case 95:
#line 524 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_ADD,(yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2347 "parser.cpp" /* yacc.c:1652  */
    break;

  case 96:
#line 526 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_SUB,(yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2355 "parser.cpp" /* yacc.c:1652  */
    break;

  case 97:
#line 528 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_OR,(yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2363 "parser.cpp" /* yacc.c:1652  */
    break;

  case 98:
#line 530 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = (yyvsp[0].exprast);
}
#line 2371 "parser.cpp" /* yacc.c:1652  */
    break;

  case 99:
#line 534 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_MUL, (yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2379 "parser.cpp" /* yacc.c:1652  */
    break;

  case 100:
#line 536 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_DIV, (yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2387 "parser.cpp" /* yacc.c:1652  */
    break;

  case 101:
#line 538 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_MOD, (yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2395 "parser.cpp" /* yacc.c:1652  */
    break;

  case 102:
#line 540 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_AND, (yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2403 "parser.cpp" /* yacc.c:1652  */
    break;

  case 103:
#line 542 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = (yyvsp[0].exprast);
}
#line 2411 "parser.cpp" /* yacc.c:1652  */
    break;

  case 104:
#line 546 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = (yyvsp[0].constast);
}
#line 2419 "parser.cpp" /* yacc.c:1652  */
    break;

  case 105:
#line 548 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::SymbolAst(*(yyvsp[0].stringPtr));
}
#line 2427 "parser.cpp" /* yacc.c:1652  */
    break;

  case 106:
#line 550 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_NG,(yyvsp[0].exprast), nullptr);
}
#line 2435 "parser.cpp" /* yacc.c:1652  */
    break;

  case 107:
#line 552 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::DotAst(new SPL::SymbolAst(*(yyvsp[-2].stringPtr)), *(yyvsp[-1].stringPtr));
}
#line 2443 "parser.cpp" /* yacc.c:1652  */
    break;

  case 108:
#line 554 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::ArrayAst(new SPL::SymbolAst(*(yyvsp[-3].stringPtr)), (yyvsp[-1].exprast));
}
#line 2451 "parser.cpp" /* yacc.c:1652  */
    break;

  case 109:
#line 556 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_NOT,(yyvsp[0].exprast), nullptr);
}
#line 2459 "parser.cpp" /* yacc.c:1652  */
    break;

  case 110:
#line 558 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::FuncAst(*(yyvsp[-3].stringPtr), *(yyvsp[-1].vecexprastPtr));
}
#line 2467 "parser.cpp" /* yacc.c:1652  */
    break;

  case 111:
#line 560 "parser.y" /* yacc.c:1652  */
    {
	SYS_FUNC_ID sys_func_id = (SYS_FUNC_ID)0;
	std::string sysname = *(yyvsp[-3].stringPtr);
	for (int i=0;i<SYS_FUNC_NAME.size();i++) {
		if (sysname == SYS_FUNC_NAME[i]) {
			sys_func_id = (SYS_FUNC_ID)i;
			break;
		}
	}
	(yyval.exprast) = new SPL::SysFuncAst(sys_func_id, *(yyvsp[-1].vecexprastPtr));
}
#line 2483 "parser.cpp" /* yacc.c:1652  */
    break;

  case 112:
#line 572 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecexprastPtr) = (yyvsp[-2].vecexprastPtr);
	(yyval.vecexprastPtr) -> push_back((yyvsp[0].exprast));
}
#line 2492 "parser.cpp" /* yacc.c:1652  */
    break;

  case 113:
#line 575 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecexprastPtr) = new std::vector<SPL::ExprAst*> ();
	(yyval.vecexprastPtr) -> push_back((yyvsp[0].exprast));
}
#line 2501 "parser.cpp" /* yacc.c:1652  */
    break;

  case 114:
#line 578 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecexprastPtr) = new std::vector<SPL::ExprAst*> ();
}
#line 2509 "parser.cpp" /* yacc.c:1652  */
    break;


#line 2513 "parser.cpp" /* yacc.c:1652  */
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
