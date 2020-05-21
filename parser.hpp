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
#line 23 "parser.y" /* yacc.c:1921  */

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

#line 159 "parser.hpp" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
