 /**********************************************************
 *	File:		lexer.l
 *	Project:	SPL-compiler
 *	Author:		Scabbard
 *	Modified:	May 14, 2020
 **********************************************************/
%{
#include <stdio.h>
#include <string.h>
#include "token.h"

TOKEN talloc();                     // allocate a new token record
void read_comments();               // deal with comments
int maketoken(int type, int which); // make a simple new token
void lexError();                    // error report
int yywrap();

TOKEN yylval;     // This is the type of the lexical analyzer result 
int lineCnt = 1;
%}

/* LEX: DECLARATIONS */
/* regular definitions */
delim		[ \t]
ws			{delim}+
letter		[A-Za-z]
digit		[0-9]
id			{letter}(_|{letter}|{digit})*
integer		{digit}+
real		{digit}+(\.{digit}+)?(([E|e])[+\-]?{digit}+)?
comment1	("{")
comment2	(\/\/.*\n)
char_string		[\']

/* LEX: rule */
%%

{ws}		{}
{comment1}	{ read_comments(); }
{comment2}	{ lineCnt++; }
"\n"		{ lineCnt++; }

"("			{ return maketoken(DELIMITER, LP); }
")"			{ return maketoken(DELIMITER, RP); }
"["			{ return maketoken(DELIMITER, LB); }
"]"			{ return maketoken(DELIMITER, RB); }
"."			{ return maketoken(OPERATOR, DOT); }
".."		{ return maketoken(DELIMITER, DOTDOT); }
","			{ return maketoken(DELIMITER, COMMA); }
":"			{ return maketoken(DELIMITER, COLON); }
";"			{ return maketoken(DELIMITER, SEMI); }

"+"             { return maketoken(OPERATOR, PLUS); }
"-"             { return maketoken(OPERATOR, MINUS); }
"*"             { return maketoken(OPERATOR, MUL); }
"/"             { return maketoken(OPERATOR, DIV); }
"MOD" | "mod"   { return maketoken(OPERATOR, MOD); }
"<"	            { return maketoken(OPERATOR, LT); }
"<="            { return maketoken(OPERATOR, LE); }
"="	            { return maketoken(OPERATOR, EQ); }
"<>"	        { return maketoken(OPERATOR, NE); }
">"	            { return maketoken(OPERATOR, GT); }
">="	        { return maketoken(OPERATOR, GE); }
":="	        { return maketoken(OPERATOR, ASSIGN); }
"NOT"	        { return maketoken(OPERATOR, NOT); }

"and"			{ return maketoken(OPERATOR, AND); }
"or"			{ return maketoken(OPERATOR, OR); }
"not"			{ return maketoken(OPERATOR, NOT); }
"div"			{ return maketoken(OPERATOR, DIV); }

"array"				{ return maketoken(RESERVED, ARRAY); }
"begin"			{ return maketoken(RESERVED, BEGIN); }
"case"				{ return maketoken(RESERVED, CASE); }
"const"				{ return maketoken(RESERVED, CONST); }
"do"						{ return maketoken(RESERVED, DO); }
"downto"			{ return maketoken(RESERVED, DOWNTO); }
"else"				{ return maketoken(RESERVED, ELSE); }
"end"					{ return maketoken(RESERVED, END); }
"for"					{ return maketoken(RESERVED, FOR); }
"function"	{ return maketoken(RESERVED, FUNCTION); }
"goto"				{ return maketoken(RESERVED, GOTO); }
"if"						{ return maketoken(RESERVED, IF); }
"in"						{ return maketoken(RESERVED, IN); }
"of"						{ return maketoken(RESERVED, OF); }
"packed"			{ return maketoken(RESERVED, PACKED); }
"procedure"	{ return maketoken(RESERVED, PROCEDURE); }
"program"		{ return maketoken(RESERVED, PROGRAM); }
"record"			{ return maketoken(RESERVED, RECORD); }
"repeat"			{ return maketoken(RESERVED, REPEAT); }
"set"					{ return maketoken(RESERVED, SET); }
"then"				{ return maketoken(RESERVED, THEN); }
"to"						{ return maketoken(RESERVED, TO); }
"type"				{ return maketoken(RESERVED, TYPE); }
"until"				{ return maketoken(RESERVED, UNTIL); }
"var"					{ return maketoken(RESERVED, VAR); }
"while"				{ return maketoken(RESERVED, WHILE); }
"with"				{ return maketoken(RESERVED, WITH); }

"false"|"maxint"|"true" { return maketoken(SYSTEM_FUNC, SYS_CON); }
"abs"|"chr"|"odd"|"ord"|"pred"|"sqr"|"sqrt"|"succ" { return maketoken(SYSTEM_FUNC, SYS_FUNCT); }
"write"|"writeln" { return maketoken(SYSTEM_FUNC, SYS_PROC); }
"boolean"|"char"|"integer"|"real"|"string" { return maketoken(SYSTEM_FUNC, SYS_TYPE); }
"read"  { return maketoken(SYSTEM_FUNC, READ); }

{id}		{ return maketoken(TOKEN_ID, TYPE_STR); }
{char_string}	{ return maketoken(TOKEN_STR, TYPE_STR); }
{integer}	{ return maketoken(TOKEN_NUM, TYPE_INT); }
{real}		{ return maketoken(TOKEN_NUM, TYPE_REAL); }

.			{ lexError(); }

%%
/* LEX: C CODE */

// allocate a new token record
TOKEN talloc() {
    TOKEN tok;
    tok = (TOKEN) calloc(1,sizeof(struct token));
    if ( tok != NULL ) return (tok);
       else {
        printf("talloc failed.");
        exit(-1);
    }
}

// deal with comments
void read_comments() {
	char c;

    /* Do nothing until the end comment characters } is read */
	while ((c = input()) != '}') {
		if (c == '\n') lineCnt++;
	}
}

// make a simple new token
int maketoken(int type, int which){
    int len = 0;
    int num = 0;
    char c;
    yylval = (TOKEN) talloc();	/* Make new token, set yylval to point to it */
	yylval->tokentype = type;
	yylval->tokenindex = which;
	
    switch(type){
    case RESERVED:
    case TOKEN_ID:
        if(yyleng<TOKENLEN){
            strcpy(yylval->tokenval.tokenstring,yytext);
        }
        else{
            printf("token_string_length out of range!  type: %d token_index: %d\n", type, which);
            yytext[TOKENLEN]='\0';
            strcpy(yylval->tokenval.tokenstring,yytext);
        }
        break;
    case TOKEN_NUM:
        if(yylval->tokenindex == TYPE_INT){
            sscanf(yytext, "%i", &num);
            yylval->tokenval.intval = num;
        }
        else if(yylval->tokenindex == TYPE_REAL){
            sscanf(yytext, "%f", &num);
            yylval->tokenval.realval = num;
        }
        else{
            printf("unsupported num type!\n");
            exit(1);
        }
        break;
    case TOKEN_STR:
        while ((c = input()) != '\'') {
            if (len < TOKENLEN) yylval->tokenval.tokenstring[len] = c;
            len++;
        }
        if (len > TOKENLEN){
            len = TOKENLEN;
            yylval->tokenval.tokenstring[len] = '\0';
        } 
        if (len == 1) {
            yylval->tokenval.charval = yylval->tokenval.tokenstring[0];
            yylval->tokentype = TOKEN_CHAR;
            yylval->tokenindex = TYPE_CHAR;
        }
        break;
    default:
        break;
    }
	
	return which+1;
}

// error report 
void lexError() {
    printf("Lexical Analysis Error at line %d:  Unknown token:%s\n", lineCnt, yytext);
}

int yywrap() {  return 1;  } 