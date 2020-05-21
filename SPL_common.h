#ifndef _SPL_COMMON_H
#define _SPL_COMMON_H




enum SPL_TYPE {
	BOOL = 1,
	CHAR,
	INT,
	REAL,
	STRING,
	
	//Maybe Useless
	ARRAY_TYPE,
	RECORD_TYPE,
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
	OP_NOT,
	OP_NG,  // negative, like: -1

	OP_GE,
	OP_GT,
	OP_LE,
	OP_LT,
	OP_EQ,
	OP_NE

	//filling
};

enum AST_NODE_TYPE {
	AST_MATH = 1,
	AST_EXPR,
	AST_SYMBOL,
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
	AST_SYSFUNC,
	AST_LABEL,
	AST_CONST_DECL,
	AST_TYPE,
	AST_RECORD_DECL,
	AST_FUNC_DECL,
	AST_SIMPLE_VAR_DECL,
	AST_TYPE_DECL,
	AST_ARRAY_DECL,
	AST_RETURN
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
	ABS = 0,
	CHR,
	ODD,
	ORD,
	PRED,
	SQR,
	SQRT,
	SUCC,
	READ,
	WRITE,
	WRITELN
};

#endif
