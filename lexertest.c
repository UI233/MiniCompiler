#include "token.h"

static char *tokentype_print[] = {"OPERATOR", "DELIMITER", "RESERVED", "TOKEN_ID",
                                  "TOKEN_NUM", "TOKEN_CHAR", "TOKEN_STR", "SYSTEM_FUNC"};
static char *tokenindex_print[] = {"PLUS", "MINUS", "MUL", "DIV", "MOD", "LT", "LE", "EQ",
                                   "NE", "GT", "GE", "ASSIGN", "NOT", "ID", "LP", "RP", "LB",
                                   "RB", "DOT", "DOTDOT", "COMMA", "COLON", "SEMI", "CONST_INT",
                                   "CONST_REAL", "CONST_CHAR", "ARRAY", "BEGIN", "CASE", "CONST",
                                   "DO", "DOWNTO", "ELSE", "END", "FOR", "FUNCTION", "GOTO",
                                   "IF", "IN", "OF", "PACKED", "PROCEDURE", "PROGRAM", "RECORD",
                                   "REPEAT", "SET", "THEN", "TO", "TYPE", "UNTIL", "VAR", "WHILE",
                                   "WITH", "SYS_CON", "SYS_FUNCT", "SYS_PROC", "SYS_TYPE",
                                   "READ", "TYPE_INT", "TYPE_REAL", "TYPE_CHAR", "TYPE_STR", "AND", "OR"};
static char *ori_print[] = {"+", "-", "*", "/", "mod", "<", "<=", "=", "<>", ">", ">=", ":=",
                            "NOT", "ID", "(", ")", "[", "]", ".", "..", ",", ":", ";", "CONST_INT",
                            "CONST_REAL", "CONST_CHAR", "array", "begin", "case", "const",
                            "do", "downto", "else", "end", "for", "function", "goto",
                            "if", "in", "of", "packed", "procedure", "program", "record",
                            "repeat", "set", "then", "to", "type", "until", "var", "while",
                            "with", "SYS_CON", "SYS_FUNCT", "SYS_PROC", "SYS_TYPE",
                            "read", "TYPE_INT", "TYPE_REAL", "TYPE_CHAR", "TYPE_STR", "and", "or"};

void printtoken(TOKEN tok)
{
    printf("token_type: %15s    token_index: %10s   ",
           tokentype_print[tok->tokentype], tokenindex_print[tok->tokenindex]);
    switch (tok->tokentype)
    {
    case OPERATOR:
    case DELIMITER:
        printf("value:  %32s\n", ori_print[tok->tokenindex]);
        break;
    case RESERVED:
    case TOKEN_ID:
    case TOKEN_STR:
    case SYSTEM_FUNC:
        printf("value:  %32s\n", tok->tokenval.tokenstring);
        break;
    case TOKEN_CHAR:
        printf("value:  %32c\n", tok->tokenval.charval);
        break;
    case TOKEN_NUM:
        if (tok->tokenindex == TYPE_INT)
        {
            printf("value:  %32d\n", tok->tokenval.intval);
        }
        else
        {
            printf("value:  %32e\n", tok->tokenval.realval);
        }
        break;
    }
}

int type_reveal(TOKEN tok)
{
    return tok->tokentype;
}

int main()
{
    int res, done;
    extern TOKEN yylval;
    printf("Started scanner test.\n");
    done = 0;
    while (done == 0)
    {
        res = yylex(); 
        if (res != 0)
        {
            printtoken(yylval);
        }
        else
            done = 1;
    }
    return 0;
}