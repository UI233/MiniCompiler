 /**********************************************************
 *	File:		token.h
 *	Project:	SPL-compiler
 *	Author:		Scabbard
 *	Modified:	May 14, 2020
 **********************************************************/
#ifndef TOKEN_H
#define TOKEN_H

#define TOKENLEN 32

//==== token data structure
typedef struct token
{
    int tokentype;  // operater, delimiter, reserved, ID, num, char, str，system_function
    int tokenindex; // detailed info of token, include datatype(int, real, char)
    union {
        int intval;
        double realval;
        char charval;
        char  tokenstring[TOKENLEN];
    } tokenval;
} * TOKEN;

//==== token type
#define OPERATOR 0
#define DELIMITER 1
#define RESERVED 2
#define TOKEN_ID 3
#define TOKEN_NUM 4
#define TOKEN_CHAR 5
#define TOKEN_STR 6
#define SYSTEM_FUNC 7

//==== token index
// operator directly used
#define  PLUS 0
#define  MINUS 1
#define  MUL 2
#define  DIV 3
#define  MOD 4
#define  LT 5
#define  LE 6
#define  EQ 7
#define  NE 8
#define  GT 9
#define  GE 10
#define  ASSIGN 11
#define  NOT 12

// delimiter 
#define ID 13
#define LP 14
#define RP 15
#define LB 16
#define RB 17
#define DOT 18
#define DOTDOT 19
#define COMMA 20
#define COLON 21
#define SEMI 22

// const type
#define CONST_INT 23
#define CONST_REAL 24
#define CONST_CHAR 25

#define ARRAY 26
#define BEGIN 27
#define CASE 28
#define CONST 29
#define DO 30
#define DOWNTO 31
#define ELSE 32
#define END 33
#define FOR 34
#define FUNCTION 35
#define GOTO 36
#define IF 37
#define IN 38
#define OF 39
#define PACKED 40
#define PROCEDURE 41
#define PROGRAM 42
#define RECORD 43
#define REPEAT 44
#define SET 45
#define THEN 46
#define TO 47
#define TYPE 48
#define UNTIL 49
#define VAR 50
#define WHILE 51
#define WITH 52
#define SYS_CON 53
#define SYS_FUNCT 54
#define SYS_PROC 55
#define SYS_TYPE 56
#define READ 57

//data type
#define TYPE_INT 58
#define TYPE_REAL 59
#define TYPE_CHAR 60
#define TYPE_STR 61

// operation from reserved words
#define AND 62
#define OR 63

#endif