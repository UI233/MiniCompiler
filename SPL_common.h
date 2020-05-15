#ifndef _SPL_COMMON_H
#define _SPL_COMMON_H

enum SPL_TYPE {
	BOOL = 1,
	CHAR,
	INT,
	REAL,
	STRING,
	
	//Maybe Useless
	ARRAY,
	RECORD,
	ERROR_VALUE
};

enum SPL_OP {
	OP_ADD = 1,
	OP_SUB,
	OP_DIV,
	OP_MUL,
	OP_OR,
	OP_AND,
	OP_MOD,

	OP_GE,
	OP_GT,
	OP_LE,
	OP_LT,
	OP_EQUAL,
	OP_UNEQUAL

	//filling
};

enum AST_NODE_TYPE {
	AST_MATH = 1,
	AST_EXPR,
	AST_SYM,
	AST_ARRAY,
	AST_DOT,
	AST_ASSIGN,
	AST_IF,
	AST_CASE,
	AST_WHILE,
	AST_REPEAT,
	AST_FOR,
	AST_GOTO,
	AST_COMPOUND,
	AST_FUNC,
	AST_SYSFUNC
};

union valueUnion {
	char    valChar;
	bool    valBool;
	int     valInt;
	double  valDouble;
	std::string* valString;
	valueUnion() {}
	~valueUnion() {}
};

enum SYS_FUNC_ID {
	SQRT = 1
};

#endif