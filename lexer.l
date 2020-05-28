%{
#include <string>
#include <iostream>
#include "Ast.h"
#include "parser.hpp"

#define TOKEN(t) (t)

int flag=0;
%}

delim		[ \t]+
letter		[A-Za-z]
digit		[0-9]
id			{letter}(_|{letter}|{digit})*
integer		[+\-]?{digit}+
real		{digit}+(\.{digit}+)?(([E|e])[+\-]?{digit}+)?
char		(\'.\')
comment	(\/\/.*\n)

%%

{delim}		{}
{comment}	{}
"\n"		{}

"("			{ flag = 1; return TOKEN(TOKEN_LP); }
")"			{ flag = 1; return TOKEN(TOKEN_RP); }
"["			{ flag = 1; return TOKEN(TOKEN_LB); }
"]"			{ flag = 1; return TOKEN(TOKEN_RB); }
":="	        { flag = 1; return TOKEN(TOKEN_ASSIGN); }
".."		{ flag = 1; return TOKEN(TOKEN_DOTDOT); }
"."			{ flag = 1; return TOKEN(TOKEN_DOT); }

","			{ flag = 1; return TOKEN(TOKEN_COMMA); }
":"			{ flag = 1; return TOKEN(TOKEN_COLON); }
";"			{ flag = 1; return TOKEN(TOKEN_SEMI); }

"+"             { flag = 1; return TOKEN(TOKEN_ADD); }
"-"             { flag = 1; return TOKEN(TOKEN_SUB); }
"*"             { flag = 1; return TOKEN(TOKEN_MUL); }
"/"             { flag = 1; return TOKEN(TOKEN_DIV); }
"MOD"|"mod"|"%"   { flag = 1; return TOKEN(TOKEN_MOD); }

"<>"	        { flag = 1; return TOKEN(TOKEN_NE); }
"<="            { flag = 1; return TOKEN(TOKEN_LE); }
">="	        { flag = 1; return TOKEN(TOKEN_GE); }
"<"	            { flag = 1; return TOKEN(TOKEN_LT); }
"="	            { flag = 1; return TOKEN(TOKEN_EQ); }

">"	            { flag = 1; return TOKEN(TOKEN_GT); }

"NOT"	        { flag = 1; return TOKEN(TOKEN_NOT); }

"and"			{ flag = 1; return TOKEN(TOKEN_AND); }
"or"			{ flag = 1; return TOKEN(TOKEN_OR); }
"not"			{ flag = 1; return TOKEN(TOKEN_NOT); }
"div"			{ flag = 1; return TOKEN(TOKEN_DIV); }

"array"				{ flag = 1; return TOKEN(TOKEN_ARRAY); }
"begin"			{ flag = 1; return TOKEN(TOKEN_BEGIN); }
"case"				{ flag = 1; return TOKEN(TOKEN_CASE); }
"const"				{ flag = 1; return TOKEN(TOKEN_CONST); }
"do"						{ flag = 1; return TOKEN(TOKEN_DO); }
"downto"			{ flag = 1; return TOKEN(TOKEN_DOWNTO); }
"else"				{ flag = 1; return TOKEN(TOKEN_ELSE); }
"end"					{ flag = 1; return TOKEN(TOKEN_END); }
"for"					{ flag = 1; return TOKEN(TOKEN_FOR); }
"function"	{ flag = 1; return TOKEN(TOKEN_FUNCTION); }
"goto"				{ flag = 1; return TOKEN(TOKEN_GOTO); }
"if"						{ flag = 1; return TOKEN(TOKEN_IF); }
"in"						{ flag = 1; return TOKEN(TOKEN_IN); }
"of"						{ flag = 1; return TOKEN(TOKEN_OF); }
"packed"			{ flag = 1; return TOKEN(TOKEN_PACKED); }
"procedure"	{ flag = 1; return TOKEN(TOKEN_PROCEDURE); }
"program"		{ flag = 1; return TOKEN(TOKEN_PROGRAM); }
"record"			{ flag = 1; return TOKEN(TOKEN_RECORD); }
"repeat"			{ flag = 1; return TOKEN(TOKEN_REPEAT); }
"set"					{ flag = 1; return TOKEN(TOKEN_SET); }
"then"				{ flag = 1; return TOKEN(TOKEN_THEN); }
"to"						{ flag = 1; return TOKEN(TOKEN_TO); }
"type"				{ flag = 1; return TOKEN(TOKEN_TYPE); }
"until"				{ flag = 1; return TOKEN(TOKEN_UNTIL); }
"var"					{ flag = 1; return TOKEN(TOKEN_VAR); }
"while"				{ flag = 1; return TOKEN(TOKEN_WHILE); }
"with"				{ flag = 1; return TOKEN(TOKEN_WITH); }

"false"|"maxint"|"true" { flag = 1; yylval.stringPtr = new std::string(yytext);  return TOKEN(TOKEN_SYS_CONST); }
"boolean"|"char"|"integer"|"real"|"string" {flag = 1; yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_SYS_TYPE); }

{id}		{flag = 1; yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_ID); }
{char}		{flag = 1; yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_CHAR_LITERAL); }
{integer}	{flag = 1; yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_INTEGER_LITERAL); }
{real}		{flag = 1; yylval.stringPtr = new std::string(yytext); return TOKEN(TOKEN_REAL_LITERAL); }

.	{if(!flag) {std::cout<< "Unknown token:" << yytext << ", line:"<< yylineno << std::endl;} }

%%

int yywrap() {
	return 1;
}