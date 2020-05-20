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

#line 89 "parser.cpp" /* yacc.c:337  */
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
#line 20 "parser.y" /* yacc.c:352  */

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

#line 233 "parser.cpp" /* yacc.c:352  */
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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  217

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
       0,   147,   147,   155,   161,   169,   172,   174,   179,   186,
     191,   195,   199,   206,   209,   211,   215,   221,   225,   228,
     231,   236,   240,   243,   246,   249,   252,   256,   276,   280,
     283,   288,   292,   295,   302,   304,   306,   309,   313,   323,
     326,   330,   333,   336,   343,   347,   351,   355,   358,   363,
     367,   372,   376,   381,   386,   390,   399,   403,   405,   409,
     411,   413,   415,   417,   419,   421,   423,   427,   431,   435,
     437,   441,   445,   449,   453,   455,   459,   463,   467,   470,
     475,   477,   481,   483,   485,   487,   489,   491,   493,   497,
     499,   501,   503,   507,   509,   511,   513,   515,   519,   521,
     523,   525,   527,   529,   531,   535,   538,   541
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
  "TOKEN_WHILE", "TOKEN_WITH", "$accept", "routine", "sub_routine",
  "routine_head", "const_part", "const_expr_list", "const_ast",
  "type_part", "type_decl_list", "type_defination", "type_decl",
  "simple_type_decl", "array_type_decl", "record_type_decl",
  "field_decl_list", "field_decl", "name_list", "var_part",
  "var_decl_list", "var_decl", "routine_part", "function_decl",
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

#define YYPACT_NINF -114

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-114)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -27,     4,    16,   -13,   -26,     5,    44,  -114,  -114,  -114,
    -114,    47,     1,   173,    53,    52,    56,    47,  -114,    81,
     -34,  -114,  -114,  -114,  -114,    72,   173,    77,    75,   152,
    -114,    93,   101,   152,  -114,   152,  -114,    97,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,    40,  -114,  -114,    24,
      81,  -114,   111,   114,   -34,  -114,  -114,  -114,   104,   110,
     152,   112,   152,   152,  -114,   170,    80,    13,  -114,   105,
    -114,   139,    73,   206,  -114,  -114,   116,   173,   136,    81,
     134,   140,  -114,  -114,  -114,   162,    40,  -114,   163,   163,
    -114,  -114,  -114,  -114,   227,   152,   152,   166,  -114,  -114,
     152,   152,   152,   152,   152,   152,   132,   152,   152,   152,
     152,   152,   152,   152,   152,    92,   152,    92,   167,   172,
     199,    -2,  -114,    62,   173,  -114,  -114,   165,    -6,   171,
     174,   227,    46,   200,  -114,    80,    80,    80,    80,    80,
      80,   183,   184,    10,  -114,    13,    13,    13,  -114,  -114,
    -114,  -114,    -1,   175,   227,  -114,  -114,   203,   179,  -114,
    -114,    40,  -114,  -114,    81,   196,    20,  -114,   198,   202,
     199,   -27,  -114,   152,  -114,    92,    92,  -114,  -114,  -114,
    -114,   152,    92,  -114,   173,  -114,   195,   197,   196,  -114,
      -6,   199,   199,   201,   204,   -13,   227,   205,   226,   212,
    -114,  -114,    40,  -114,  -114,  -114,  -114,   -27,  -114,  -114,
    -114,  -114,    92,  -114,   228,  -114,  -114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     0,    14,     0,     5,     1,    56,     2,
      53,     0,    35,     0,     0,     0,     0,    13,    16,     0,
      41,    12,     9,    10,    11,     0,     0,     0,     0,     0,
      54,     0,     0,     0,    56,     0,    60,     0,    58,    59,
      61,    62,    63,    64,    65,    66,     0,    15,    33,     0,
      34,    37,     0,     0,     4,    40,    43,     8,     0,     0,
       0,    99,     0,     0,    98,     0,    88,    92,    97,     0,
      77,     0,     0,     0,    55,    21,    22,     0,     0,     0,
       0,     0,    18,    19,    20,     0,     0,    36,     0,     0,
      39,    42,     7,    57,    67,   107,     0,     0,   100,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,    17,    32,     0,     0,     0,
       0,   106,     0,     0,   101,    85,    84,    83,    82,    86,
      87,     0,     0,     0,    79,    89,    90,    91,    93,    94,
      95,    96,     0,    70,    71,    72,    26,     0,     0,    28,
      29,     0,    23,    38,     0,    52,     0,    48,     0,     0,
       0,     6,   104,     0,   102,     0,     0,    76,    78,    75,
      74,     0,     0,    68,     0,    24,     0,     0,    51,    46,
       0,     0,     0,     0,     0,     0,   105,     0,     0,     0,
      69,    25,     0,    31,    47,    49,    50,     6,    45,     3,
      81,    80,     0,    27,     0,    73,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,    41,   249,  -114,  -114,   -12,  -114,  -114,   233,
     -84,  -113,  -114,  -114,  -114,   130,   -76,  -114,  -114,   215,
    -114,   213,   214,   177,  -114,    82,  -114,  -114,    74,    -3,
     236,  -107,   216,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,   128,   -29,   159,    79,   -40,  -114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,   194,   195,     4,     6,    64,    12,    17,    18,
      81,    82,    83,    84,   121,   122,    49,    20,    50,    51,
      54,    55,    56,   129,   166,   167,   168,   169,     9,    36,
      15,    37,    38,    39,    40,   183,    41,    42,    43,   181,
      44,    45,   143,   144,    65,    66,    67,    68,   132
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      10,    25,   127,   123,    71,    48,    73,   158,   153,    48,
     155,    52,     1,    21,    58,     5,     7,    53,    22,    23,
      24,   141,    98,    99,     8,   100,   101,   102,   103,   104,
     105,    94,    11,   189,    80,    13,   110,   111,   112,   190,
     179,   159,    85,    21,    86,   123,    75,   113,    22,    23,
      24,    76,   165,   177,   164,    14,   180,   193,    16,   172,
      27,    19,    77,    28,   173,   119,   131,   133,   197,   198,
     148,   149,   150,   151,    80,   200,    78,   187,   205,   206,
      85,    27,   161,    26,    28,   152,    46,   154,   188,     8,
      29,    57,    48,    79,   142,    30,    31,    59,    32,    33,
      27,   107,   108,    28,    69,   215,    34,    60,    80,    70,
       8,    29,   162,    35,   165,   109,    74,    31,   213,    32,
      33,    28,    88,    92,    95,    89,    96,    34,    97,     8,
      29,   142,   116,   118,    35,    21,    31,   114,    32,    33,
      22,    23,    24,   141,   196,   185,    34,     8,    29,    80,
     120,   124,   199,    35,    31,    21,    32,    33,    80,   125,
      22,    23,    24,    61,    34,   100,   101,   102,   103,   104,
     105,    35,   201,   126,    62,   128,    21,   134,   156,    80,
      80,    22,    23,    24,   163,    63,   145,   146,   147,   157,
      80,   170,    10,   171,   186,   115,   100,   101,   102,   103,
     104,   105,    21,   175,   176,    75,    21,    22,    23,    24,
      76,    22,    23,    24,    85,   174,   203,   182,   191,   106,
     207,    77,   192,   208,   210,   184,   100,   101,   102,   103,
     104,   105,   100,   101,   102,   103,   104,   105,   100,   101,
     102,   103,   104,   105,   202,   211,   117,   216,   214,     3,
      47,   160,   212,   100,   101,   102,   103,   104,   105,   135,
     136,   137,   138,   139,   140,    87,   130,    90,    91,   209,
      72,   178,   204,     0,     0,    93
};

static const yytype_int16 yycheck[] =
{
       3,    13,    86,    79,    33,    11,    35,   120,   115,    11,
     117,    45,    39,     3,    26,    11,     0,    51,     8,     9,
      10,    11,    62,    63,    37,    26,    27,    28,    29,    30,
      31,    60,    58,    13,    46,    30,    23,    24,    25,    19,
      41,    43,    18,     3,    20,   121,     6,    34,     8,     9,
      10,    11,   128,    43,    60,    11,    57,   170,    11,    13,
       8,    60,    22,    11,    18,    77,    95,    96,   175,   176,
     110,   111,   112,   113,    86,   182,    36,   161,   191,   192,
      18,     8,    20,    30,    11,   114,    30,   116,   164,    37,
      38,    19,    11,    53,   106,    43,    44,    20,    46,    47,
       8,    21,    22,    11,    11,   212,    54,    32,   120,     8,
      37,    38,   124,    61,   190,    35,    19,    44,   202,    46,
      47,    11,    11,    19,    12,    11,    14,    54,    16,    37,
      38,   143,    59,    17,    61,     3,    44,    32,    46,    47,
       8,     9,    10,    11,   173,   157,    54,    37,    38,   161,
      14,    17,   181,    61,    44,     3,    46,    47,   170,    19,
       8,     9,    10,    11,    54,    26,    27,    28,    29,    30,
      31,    61,   184,    11,    22,    12,     3,    11,    11,   191,
     192,     8,     9,    10,    19,    33,   107,   108,   109,    17,
     202,    20,   195,    19,    15,    56,    26,    27,    28,    29,
      30,    31,     3,    20,    20,     6,     3,     8,     9,    10,
      11,     8,     9,    10,    18,    15,    19,    42,    20,    49,
      19,    22,    20,    19,    19,    22,    26,    27,    28,    29,
      30,    31,    26,    27,    28,    29,    30,    31,    26,    27,
      28,    29,    30,    31,    49,    19,    40,    19,   207,     0,
      17,   121,    40,    26,    27,    28,    29,    30,    31,   100,
     101,   102,   103,   104,   105,    50,    89,    54,    54,   195,
      34,   143,   190,    -1,    -1,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    39,    64,    66,    67,    11,    68,     0,    37,    91,
      92,    58,    70,    30,    11,    93,    11,    71,    72,    60,
      80,     3,     8,     9,    10,    69,    30,     8,    11,    38,
      43,    44,    46,    47,    54,    61,    92,    94,    95,    96,
      97,    99,   100,   101,   103,   104,    30,    72,    11,    79,
      81,    82,    45,    51,    83,    84,    85,    19,    69,    20,
      32,    11,    22,    33,    69,   107,   108,   109,   110,    11,
       8,   107,    93,   107,    19,     6,    11,    22,    36,    53,
      69,    73,    74,    75,    76,    18,    20,    82,    11,    11,
      84,    85,    19,    95,   107,    12,    14,    16,   110,   110,
      26,    27,    28,    29,    30,    31,    49,    21,    22,    35,
      23,    24,    25,    34,    32,    56,    59,    40,    17,    69,
      14,    77,    78,    79,    17,    19,    11,    73,    12,    86,
      86,   107,   111,   107,    11,   108,   108,   108,   108,   108,
     108,    11,    69,   105,   106,   109,   109,   109,   110,   110,
     110,   110,   107,    94,   107,    94,    11,    17,    74,    43,
      78,    20,    69,    19,    60,    79,    87,    88,    89,    90,
      20,    19,    13,    18,    15,    20,    20,    43,   106,    41,
      57,   102,    42,    98,    22,    69,    15,    73,    79,    13,
      19,    20,    20,    74,    65,    66,   107,    94,    94,   107,
      94,    69,    49,    19,    88,    74,    74,    19,    19,    91,
      19,    19,    40,    73,    65,    94,    19
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    70,    70,    71,    71,    72,    73,    73,
      73,    74,    74,    74,    74,    74,    74,    75,    76,    77,
      77,    78,    79,    79,    80,    80,    81,    81,    82,    83,
      83,    83,    83,    83,    84,    85,    86,    87,    87,    88,
      88,    89,    90,    91,    92,    93,    93,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    96,    97,    98,
      98,    99,   100,   101,   102,   102,   103,   104,   105,   105,
     106,   106,   107,   107,   107,   107,   107,   107,   107,   108,
     108,   108,   108,   109,   109,   109,   109,   109,   110,   110,
     110,   110,   110,   110,   110,   111,   111,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     4,     2,     0,     5,     4,     1,
       1,     1,     1,     2,     0,     2,     1,     4,     1,     1,
       1,     1,     1,     3,     4,     5,     3,     6,     3,     2,
       1,     4,     3,     1,     2,     0,     2,     1,     4,     2,
       1,     0,     2,     1,     8,     6,     3,     3,     1,     3,
       3,     2,     1,     1,     3,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     2,
       0,     4,     4,     8,     1,     1,     5,     2,     2,     1,
       4,     4,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     1,     3,     3,     3,     3,     1,     1,     1,
       2,     3,     4,     2,     4,     3,     1,     0
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
#line 147 "parser.y" /* yacc.c:1652  */
    {
//TODO
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast) -> merge((yyvsp[0].compoundast));
	program = (yyval.compoundast);
	//program = $$;
}
#line 1509 "parser.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 155 "parser.y" /* yacc.c:1652  */
    {
	//$$ = new SPL::RoutineAst($<routineheadast>1, $<compoundast>2);
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast) -> merge((yyvsp[0].compoundast));
}
#line 1519 "parser.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 161 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-3].compoundast);
	if ((yyval.compoundast)==nullptr) (yyval.compoundast) = new SPL::CompoundAst(std::vector<SPL::StmtAst*>());
	(yyval.compoundast) -> merge((yyvsp[-2].compoundast));
	(yyval.compoundast) -> merge((yyvsp[-1].compoundast));
	(yyval.compoundast) -> merge((yyvsp[0].compoundast));
}
#line 1531 "parser.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 169 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
}
#line 1539 "parser.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 172 "parser.y" /* yacc.c:1652  */
    {(yyval.compoundast) = nullptr;}
#line 1545 "parser.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 174 "parser.y" /* yacc.c:1652  */
    {
	SPL::ConstDeclAst* t = new SPL::ConstDeclAst(*(yyvsp[-3].stringPtr), (yyvsp[-1].constast)->getType(), (yyvsp[-1].constast)->getValue());
	(yyval.compoundast) = (yyvsp[-4].compoundast);
	(yyval.compoundast)->addStmt(t);
}
#line 1555 "parser.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 179 "parser.y" /* yacc.c:1652  */
    {
	SPL::ConstDeclAst* t = new SPL::ConstDeclAst(*(yyvsp[-3].stringPtr), (yyvsp[-1].constast)->getType(), (yyvsp[-1].constast)->getValue());
	std::vector<SPL::StmtAst*> vect;
	vect.push_back(t);
	(yyval.compoundast) = new SPL::CompoundAst(vect);
}
#line 1566 "parser.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 186 "parser.y" /* yacc.c:1652  */
    {
	std::string* t = (yyvsp[0].stringPtr);
	(yyval.constast) = new SPL::ConstAst(std::stoi(*t));

}
#line 1576 "parser.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 191 "parser.y" /* yacc.c:1652  */
    {
	std::string* t = (yyvsp[0].stringPtr);
	(yyval.constast) = new SPL::ConstAst(std::stod(*t));
}
#line 1585 "parser.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 195 "parser.y" /* yacc.c:1652  */
    {
	std::string* t = (yyvsp[0].stringPtr);
	(yyval.constast) = new SPL::ConstAst((*t)[1]);
}
#line 1594 "parser.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 199 "parser.y" /* yacc.c:1652  */
    {
	std::string* t = (yyvsp[0].stringPtr);
	if (*t == maxint_string)  (yyval.constast) = new SPL::ConstAst(INT_MAX_SPL);
	else if (*t == true_string) (yyval.constast) = new SPL::ConstAst(true);
	else if (*t == false_string) (yyval.constast) = new SPL::ConstAst(false);
}
#line 1605 "parser.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 206 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
}
#line 1613 "parser.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 209 "parser.y" /* yacc.c:1652  */
    {(yyval.compoundast) = nullptr; }
#line 1619 "parser.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 211 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast)->addStmt((yyvsp[0].typedeclast));
}
#line 1628 "parser.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 215 "parser.y" /* yacc.c:1652  */
    {
	std::vector<SPL::StmtAst*> vect;
	vect.push_back((yyvsp[0].typedeclast));
	(yyval.compoundast) = new SPL::CompoundAst(vect);
}
#line 1638 "parser.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 221 "parser.y" /* yacc.c:1652  */
    {
	(yyval.typedeclast) = new SPL::TypeDeclAst(*((yyvsp[-3].stringPtr)), (yyvsp[-1].typeast));
}
#line 1646 "parser.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 225 "parser.y" /* yacc.c:1652  */
    {
	(yyval.typeast) = (yyvsp[0].simpletypeast);
}
#line 1654 "parser.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 228 "parser.y" /* yacc.c:1652  */
    {
	(yyval.typeast) = (yyvsp[0].arraytypeast);
}
#line 1662 "parser.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 231 "parser.y" /* yacc.c:1652  */
    {
	(yyval.typeast) = (yyvsp[0].recordtypeast);
}
#line 1670 "parser.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 236 "parser.y" /* yacc.c:1652  */
    {
	std::string t = *((yyvsp[0].stringPtr));
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(t);
}
#line 1679 "parser.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 240 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(*((yyvsp[0].stringPtr)));
}
#line 1687 "parser.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 243 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(std::to_string(((yyvsp[-2].constast))->getValue().valInt)+dotdot_string+std::to_string(((yyvsp[0].constast))->getValue().valInt));
}
#line 1695 "parser.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 246 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(minus_string+std::to_string(((yyvsp[-2].constast))->getValue().valInt)+dotdot_string+std::to_string(((yyvsp[0].constast))->getValue().valInt));
}
#line 1703 "parser.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 249 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(minus_string+std::to_string(((yyvsp[-3].constast))->getValue().valInt)+dotdot_string+minus_string+std::to_string(((yyvsp[0].constast))->getValue().valInt));
}
#line 1711 "parser.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 252 "parser.y" /* yacc.c:1652  */
    {
	(yyval.simpletypeast) = new SPL::SimpleTypeAst(*((yyvsp[-2].stringPtr))+dotdot_string+*((yyvsp[0].stringPtr)));
}
#line 1719 "parser.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 256 "parser.y" /* yacc.c:1652  */
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
#line 1743 "parser.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 276 "parser.y" /* yacc.c:1652  */
    {
	(yyval.recordtypeast) = (yyvsp[-1].recordtypeast);
}
#line 1751 "parser.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 280 "parser.y" /* yacc.c:1652  */
    {
	(yyval.recordtypeast) = (yyvsp[-1].recordtypeast);
	(yyval.recordtypeast) -> addMember(*(yyvsp[0].recordunit));
}
#line 1760 "parser.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 283 "parser.y" /* yacc.c:1652  */
    {
	(yyval.recordtypeast) = new SPL::RecordTypeAst();
	(yyval.recordtypeast) -> addMember(*(yyvsp[0].recordunit));
}
#line 1769 "parser.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 288 "parser.y" /* yacc.c:1652  */
    {
	(yyval.recordunit) = new std::pair<SPL::TypeAst*, std::vector<std::string> > ((yyvsp[-1].typeast), *(yyvsp[-3].vecstrPtr));
}
#line 1777 "parser.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 292 "parser.y" /* yacc.c:1652  */
    {
	(yyvsp[-2].vecstrPtr)->push_back(*(yyvsp[0].stringPtr));
	(yyval.vecstrPtr) = (yyvsp[-2].vecstrPtr);
}
#line 1786 "parser.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 295 "parser.y" /* yacc.c:1652  */
    {
	std::string t = std::string(*((yyvsp[0].stringPtr)));
	(yyval.vecstrPtr) = new std::vector<std::string> ();
	(yyval.vecstrPtr)->push_back(t);
}
#line 1796 "parser.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 302 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
}
#line 1804 "parser.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 304 "parser.y" /* yacc.c:1652  */
    {(yyval.compoundast) = nullptr;}
#line 1810 "parser.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 306 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast)->merge((yyvsp[0].compoundast));
}
#line 1819 "parser.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 309 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
}
#line 1827 "parser.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 313 "parser.y" /* yacc.c:1652  */
    {

	(yyval.compoundast) = new SPL::CompoundAst(std::vector<SPL::StmtAst*> () );
	for (auto name: *((yyvsp[-3].vecstrPtr)) ) {
		(yyval.compoundast) -> addStmt(new SPL::SimpleVarDeclAst(name, (yyvsp[-1].typeast) ));
	}

}
#line 1840 "parser.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 323 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast)->addStmt((yyvsp[0].funcdeclast));
}
#line 1849 "parser.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 326 "parser.y" /* yacc.c:1652  */
    {
	std::vector<SPL::StmtAst*> t;
	t.push_back((yyvsp[0].funcdeclast));
	(yyval.compoundast) = new SPL::CompoundAst(t);
}
#line 1859 "parser.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 330 "parser.y" /* yacc.c:1652  */
    {
	std::vector<SPL::StmtAst*> t;
	(yyval.compoundast) = new SPL::CompoundAst(t);
}
#line 1868 "parser.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 333 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[-1].compoundast);
	(yyval.compoundast)->addStmt((yyvsp[0].funcdeclast));
}
#line 1877 "parser.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 336 "parser.y" /* yacc.c:1652  */
    {
	std::vector<SPL::StmtAst*> t;
	t.push_back((yyvsp[0].funcdeclast));
	(yyval.compoundast) = new SPL::CompoundAst(t);
}
#line 1887 "parser.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 343 "parser.y" /* yacc.c:1652  */
    {
	(yyval.funcdeclast) = new SPL::FuncDeclAst(*((yyvsp[-6].stringPtr)), (yyvsp[-1].compoundast), (yyvsp[-5].paradecl)->args, (yyvsp[-5].paradecl)->is_var, (yyvsp[-3].typeast) );
}
#line 1895 "parser.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 347 "parser.y" /* yacc.c:1652  */
    {
	(yyval.funcdeclast) = new SPL::FuncDeclAst(*((yyvsp[-4].stringPtr)), (yyvsp[-1].compoundast), (yyvsp[-3].paradecl)->args, (yyvsp[-3].paradecl)->is_var, nullptr );
}
#line 1903 "parser.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 351 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = (yyvsp[-1].paradecl);
}
#line 1911 "parser.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 355 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = (yyvsp[-2].paradecl);
	(yyval.paradecl) -> addList((yyvsp[0].paradecl));
}
#line 1920 "parser.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 358 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = new SPL::ParaDecl();
	(yyval.paradecl) -> addList((yyvsp[0].paradecl));
}
#line 1929 "parser.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 363 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = new SPL::ParaDecl();
	(yyval.paradecl)->addPara(*(yyvsp[-2].vecstrPtr), (yyvsp[0].typeast), true);
}
#line 1938 "parser.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 367 "parser.y" /* yacc.c:1652  */
    {
	(yyval.paradecl) = new SPL::ParaDecl();
	(yyval.paradecl)->addPara(*(yyvsp[-2].vecstrPtr), (yyvsp[0].typeast), false);
}
#line 1947 "parser.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 372 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecstrPtr) = (yyvsp[0].vecstrPtr);
}
#line 1955 "parser.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 376 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecstrPtr) = (yyvsp[0].vecstrPtr);
}
#line 1963 "parser.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 381 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = (yyvsp[0].compoundast);
	//program_routine_body = $<compoundast>1;
}
#line 1972 "parser.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 386 "parser.y" /* yacc.c:1652  */
    {
	(yyval.compoundast) = new SPL::CompoundAst(*(yyvsp[-1].vecstmtastPtr));
}
#line 1980 "parser.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 390 "parser.y" /* yacc.c:1652  */
    {
	if ((yyvsp[-2].vecstmtastPtr)) {
		(yyval.vecstmtastPtr) = (yyvsp[-2].vecstmtastPtr);
		(yyval.vecstmtastPtr)->push_back((yyvsp[-1].stmtast));
	} else {
		(yyval.vecstmtastPtr) = new std::vector<SPL::StmtAst*> ();
		(yyval.vecstmtastPtr)->push_back((yyvsp[-1].stmtast));
	}
}
#line 1994 "parser.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 399 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecstmtastPtr) = nullptr;
}
#line 2002 "parser.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 403 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = new SPL::LabelAst(std::stoi(*(yyvsp[-2].stringPtr)), (yyvsp[0].stmtast));
}
#line 2010 "parser.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 405 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].stmtast);
}
#line 2018 "parser.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 409 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].assignast);
}
#line 2026 "parser.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 411 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].compoundast);
}
#line 2034 "parser.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 413 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].ifast);
}
#line 2042 "parser.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 415 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].repeatast);
}
#line 2050 "parser.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 417 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].whileast);
}
#line 2058 "parser.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 419 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].forast);
}
#line 2066 "parser.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 421 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].caseast);
}
#line 2074 "parser.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 423 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].gotoast);
}
#line 2082 "parser.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 427 "parser.y" /* yacc.c:1652  */
    {
	(yyval.assignast) = new SPL::AssignAst(new SPL::SymbolAst(*((yyvsp[-2].stringPtr))), (yyvsp[0].exprast) );
}
#line 2090 "parser.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 431 "parser.y" /* yacc.c:1652  */
    {
	(yyval.ifast) = new SPL::IfAst((yyvsp[-3].exprast), (yyvsp[-1].stmtast), (yyvsp[0].stmtast));
}
#line 2098 "parser.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 435 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = (yyvsp[0].stmtast);
}
#line 2106 "parser.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 437 "parser.y" /* yacc.c:1652  */
    {
	(yyval.stmtast) = nullptr;
}
#line 2114 "parser.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 441 "parser.y" /* yacc.c:1652  */
    {
	(yyval.repeatast) = new SPL::RepeatAst(*(yyvsp[-2].vecstmtastPtr), (yyvsp[0].exprast));
}
#line 2122 "parser.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 445 "parser.y" /* yacc.c:1652  */
    {
	(yyval.whileast) = new SPL::WhileAst((yyvsp[-2].exprast),(yyvsp[0].stmtast));
}
#line 2130 "parser.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 449 "parser.y" /* yacc.c:1652  */
    {
	(yyval.forast) = new SPL::ForAst(new SPL::SymbolAst(*(yyvsp[-6].stringPtr)),(yyvsp[-4].exprast),(yyvsp[-3].valbool),(yyvsp[-2].exprast),(yyvsp[0].stmtast));
}
#line 2138 "parser.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 453 "parser.y" /* yacc.c:1652  */
    {
	(yyval.valbool) = true;
}
#line 2146 "parser.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 455 "parser.y" /* yacc.c:1652  */
    {
	(yyval.valbool) = false;
}
#line 2154 "parser.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 459 "parser.y" /* yacc.c:1652  */
    {
	(yyval.caseast) = new SPL::CaseAst((yyvsp[-3].exprast), *(yyvsp[-1].veccaseunitPtr));
}
#line 2162 "parser.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 463 "parser.y" /* yacc.c:1652  */
    {
	(yyval.gotoast) = new SPL::GotoAst(std::stoi(*(yyvsp[-1].stringPtr)));
}
#line 2170 "parser.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 467 "parser.y" /* yacc.c:1652  */
    {
	(yyval.veccaseunitPtr) = (yyvsp[-1].veccaseunitPtr);
	(yyval.veccaseunitPtr)->push_back((yyvsp[0].caseunit));
}
#line 2179 "parser.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 470 "parser.y" /* yacc.c:1652  */
    {
	(yyval.veccaseunitPtr) = new std::vector<SPL::CaseUnit*>();
	(yyval.veccaseunitPtr)->push_back((yyvsp[0].caseunit));
}
#line 2188 "parser.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 475 "parser.y" /* yacc.c:1652  */
    {
	(yyval.caseunit) = new SPL::CaseUnit((yyvsp[-3].exprast), (yyvsp[-1].stmtast));
}
#line 2196 "parser.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 477 "parser.y" /* yacc.c:1652  */
    {
	(yyval.caseunit) = new SPL::CaseUnit((yyvsp[-3].exprast), (yyvsp[-1].stmtast));
}
#line 2204 "parser.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 481 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_GE,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2212 "parser.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 483 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_GT,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2220 "parser.cpp" /* yacc.c:1652  */
    break;

  case 84:
#line 485 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_LE,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2228 "parser.cpp" /* yacc.c:1652  */
    break;

  case 85:
#line 487 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_LT,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2236 "parser.cpp" /* yacc.c:1652  */
    break;

  case 86:
#line 489 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_EQ,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2244 "parser.cpp" /* yacc.c:1652  */
    break;

  case 87:
#line 491 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_NE,(yyvsp[-2].exprast),(yyvsp[0].exprast));
}
#line 2252 "parser.cpp" /* yacc.c:1652  */
    break;

  case 88:
#line 493 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = (yyvsp[0].exprast);
}
#line 2260 "parser.cpp" /* yacc.c:1652  */
    break;

  case 89:
#line 497 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_ADD,(yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2268 "parser.cpp" /* yacc.c:1652  */
    break;

  case 90:
#line 499 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_SUB,(yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2276 "parser.cpp" /* yacc.c:1652  */
    break;

  case 91:
#line 501 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_OR,(yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2284 "parser.cpp" /* yacc.c:1652  */
    break;

  case 92:
#line 503 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = (yyvsp[0].exprast);
}
#line 2292 "parser.cpp" /* yacc.c:1652  */
    break;

  case 93:
#line 507 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_MUL, (yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2300 "parser.cpp" /* yacc.c:1652  */
    break;

  case 94:
#line 509 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_DIV, (yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2308 "parser.cpp" /* yacc.c:1652  */
    break;

  case 95:
#line 511 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_MOD, (yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2316 "parser.cpp" /* yacc.c:1652  */
    break;

  case 96:
#line 513 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_AND, (yyvsp[-2].exprast), (yyvsp[0].exprast));
}
#line 2324 "parser.cpp" /* yacc.c:1652  */
    break;

  case 97:
#line 515 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = (yyvsp[0].exprast);
}
#line 2332 "parser.cpp" /* yacc.c:1652  */
    break;

  case 98:
#line 519 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = (yyvsp[0].constast);
}
#line 2340 "parser.cpp" /* yacc.c:1652  */
    break;

  case 99:
#line 521 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::SymbolAst(*(yyvsp[0].stringPtr));
}
#line 2348 "parser.cpp" /* yacc.c:1652  */
    break;

  case 100:
#line 523 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_NG,(yyvsp[0].exprast), nullptr);
}
#line 2356 "parser.cpp" /* yacc.c:1652  */
    break;

  case 101:
#line 525 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::DotAst(new SPL::SymbolAst(*(yyvsp[-2].stringPtr)), *(yyvsp[-1].stringPtr));
}
#line 2364 "parser.cpp" /* yacc.c:1652  */
    break;

  case 102:
#line 527 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::ArrayAst(new SPL::SymbolAst(*(yyvsp[-3].stringPtr)), (yyvsp[-1].exprast));
}
#line 2372 "parser.cpp" /* yacc.c:1652  */
    break;

  case 103:
#line 529 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::MathAst(OP_NOT,(yyvsp[0].exprast), nullptr);
}
#line 2380 "parser.cpp" /* yacc.c:1652  */
    break;

  case 104:
#line 531 "parser.y" /* yacc.c:1652  */
    {
	(yyval.exprast) = new SPL::FuncAst(*(yyvsp[-3].stringPtr), *(yyvsp[-1].vecexprastPtr));
}
#line 2388 "parser.cpp" /* yacc.c:1652  */
    break;

  case 105:
#line 535 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecexprastPtr) = (yyvsp[-2].vecexprastPtr);
	(yyval.vecexprastPtr) -> push_back((yyvsp[0].exprast));
}
#line 2397 "parser.cpp" /* yacc.c:1652  */
    break;

  case 106:
#line 538 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecexprastPtr) = new std::vector<SPL::ExprAst*> ();
	(yyval.vecexprastPtr) -> push_back((yyvsp[0].exprast));
}
#line 2406 "parser.cpp" /* yacc.c:1652  */
    break;

  case 107:
#line 541 "parser.y" /* yacc.c:1652  */
    {
	(yyval.vecexprastPtr) = new std::vector<SPL::ExprAst*> ();
}
#line 2414 "parser.cpp" /* yacc.c:1652  */
    break;


#line 2418 "parser.cpp" /* yacc.c:1652  */
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
