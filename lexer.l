%{
#include <string>
#include <iostream>
#include "Ast.h"
#include "parser.hpp"


#define TOKEN(t) (t)

int lineno = 1;
%}

delim		[ \t]
ws			{delim}+
letter		[A-Za-z]
digit		[0-9]
id			{letter}(_|{letter}|{digit})*
integer		[+\-]?{digit}+
real		{digit}+(\.{digit}+)?(([E|e])[+\-]?{digit}+)?
comment1	("{")
comment2	(\/\/.*\n)
char		(\'.\')

%%


{ws}		{}
{comment1}	{ }
{comment2}	{ }
"\n"		{ lineno++; }

"("			{ return TOKEN(TOKEN_LP); }
")"			{ return TOKEN(TOKEN_RP); }
"["			{ return TOKEN(TOKEN_LB); }
"]"			{ return TOKEN(TOKEN_RB); }
":="	        { return TOKEN(TOKEN_ASSIGN); }
".."		{ return TOKEN(TOKEN_DOTDOT); }
"."			{ return TOKEN(TOKEN_DOT); }

","			{ return TOKEN(TOKEN_COMMA); }
":"			{ return TOKEN(TOKEN_COLON); }
";"			{ return TOKEN(TOKEN_SEMI); }

"+"             { return TOKEN(TOKEN_ADD); }
"-"             { return TOKEN(TOKEN_SUB); }
"*"             { return TOKEN(TOKEN_MUL); }
"/"             { return TOKEN(TOKEN_DIV); }
"MOD"|"mod"   { return TOKEN(TOKEN_MOD); }

"<>"	        { return TOKEN(TOKEN_NE); }
"<="            { return TOKEN(TOKEN_LE); }
">="	        { return TOKEN(TOKEN_GE); }
"<"	            { return TOKEN(TOKEN_LT); }
"="	            { return TOKEN(TOKEN_EQ); }



">"	            { return TOKEN(TOKEN_GT); }


"NOT"	        { return TOKEN(TOKEN_NOT); }

"and"			{ return TOKEN(TOKEN_AND); }
"or"			{ return TOKEN(TOKEN_OR); }
"not"			{ return TOKEN(TOKEN_NOT); }
"div"			{ return TOKEN(TOKEN_DIV); }

"array"				{ return TOKEN(TOKEN_ARRAY); }
"begin"			{ return TOKEN(TOKEN_BEGIN); }
"case"				{ return TOKEN(TOKEN_CASE); }
"const"				{ return TOKEN(TOKEN_CONST); }
"do"						{ return TOKEN(TOKEN_DO); }
"downto"			{ return TOKEN(TOKEN_DOWNTO); }
"else"				{ return TOKEN(TOKEN_ELSE); }
"end"					{ return TOKEN(TOKEN_END); }
"for"					{ return TOKEN(TOKEN_FOR); }
"function"	{ return TOKEN(TOKEN_FUNCTION); }
"goto"				{ return TOKEN(TOKEN_GOTO); }
"if"						{ return TOKEN(TOKEN_IF); }
"in"						{ return TOKEN(TOKEN_IN); }
"of"						{ return TOKEN(TOKEN_OF); }
"packed"			{ return TOKEN(TOKEN_PACKED); }
"procedure"	{ return TOKEN(TOKEN_PROCEDURE); }
"program"		{ return TOKEN(TOKEN_PROGRAM); }
"record"			{ return TOKEN(TOKEN_RECORD); }
"repeat"			{ return TOKEN(TOKEN_REPEAT); }
"set"					{ return TOKEN(TOKEN_SET); }
"then"				{ return TOKEN(TOKEN_THEN); }
"to"						{ return TOKEN(TOKEN_TO); }
"type"				{ return TOKEN(TOKEN_TYPE); }
"until"				{ return TOKEN(TOKEN_UNTIL); }
"var"					{ return TOKEN(TOKEN_VAR); }
"while"				{ return TOKEN(TOKEN_WHILE); }
"with"				{ return TOKEN(TOKEN_WITH); }

"false"|"maxint"|"true" { yylval.stringPtr = new std::string(yytext);  return TOKEN(TOKEN_SYS_CONST); }
"boolean"|"char"|"integer"|"real"|"string" {yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_SYS_TYPE); }

{id}		{yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_ID); }
{char}	{yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_CHAR_LITERAL); }
{integer}	{yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_INTEGER_LITERAL); }
{real}		{yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_REAL_LITERAL); }



. std::cout<<"Unknown token:"<<yytext<<"at line:"<<lineno<<std::endl;

%%
int yywrap() {
	return 1;
}

