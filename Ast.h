#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <llvm/IR/Value.h>
#include "SPL_common.h"

namespace SPL {

union valueUnion {
	char    valChar;
	bool    valBool;
	int     valInt;
	double  valDouble;
	std::string* valString;
	valueUnion() {}
	~valueUnion() {}
};

class Ast {

public:
	AST_NODE_TYPE nodeType;
	using SPL_IR = llvm::Value*;

	//get the value of ast, if has not, return ERROR_NO_VAL
	virtual valueUnion getValue() = 0;
	//the function is for debug
	virtual void __show(std::fstream& fout) = 0;
	virtual SPL_IR codeGen() = 0;
	virtual ~Ast() = 0;
};

class ExprAst: public Ast 
// ExprAst is Ast those has value, such as 2+3(MathAst),a[i](ArrayAst),a = 2+3, ...
{
public:
	SPL_TYPE valueType;
	//get Ast's value (if has)
	virtual valueUnion getValue() = 0;
	virtual void __show(std::fstream& fout) = 0;
	virtual ~ExprAst() = 0;
};

class MathAst final:public ExprAst {
//such as expr + expr
protected:
	SPL_OP op;
	ExprAst* lchild;
	ExprAst* rchild;
public:
	MathAst(SPL_OP op, ExprAst* left = nullptr, ExprAst* right = nullptr);
	valueUnion getValue();
	void __show(std::fstream& fout);
	virtual Ast::SPL_IR codeGen();
	~MathAst();
};

class ConstAst final: public ExprAst {
protected:
	valueUnion value;
public:
	ConstAst(char x);
	ConstAst(int x);
	ConstAst(double x);
	ConstAst(bool x);
	ConstAst(const std::string& x);
	valueUnion getValue();
	void __show(std::fstream& fout);
	virtual Ast::SPL_IR codeGen();
	~ConstAst();
};

class SymbolAst final: public ExprAst {
protected:
	std::string name;
public:
	SymbolAst(const std::string& name);
	~SymbolAst();
	valueUnion getValue();
	void __show(std::fstream& fout);
	virtual Ast::SPL_IR codeGen();
};

class ArrayAst final: public ExprAst {
protected:
	//void print(void);
	std::string arrayName;
	SymbolAst* sym;
	ExprAst* exp_index;
public:
	ArrayAst(SymbolAst* sym_, ExprAst* exp_);
	valueUnion getValue();
	void __show(std::fstream& fout);
	~ArrayAst();
	virtual Ast::SPL_IR codeGen();
};

class DotAst final:public ExprAst {
protected:
	SymbolAst* record;
	SymbolAst* field;
public:
	DotAst(SymbolAst* record_, SymbolAst* field_);
	valueUnion getValue();
	void __show(std::fstream& fout);
	~DotAst();
	virtual Ast::SPL_IR codeGen();
};

class AssignAst final:public ExprAst {
protected:
	ExprAst* lhs;
	ExprAst* rhs;
public:
	AssignAst(ExprAst* lhs_, ExprAst* rhs_);
	~AssignAst() ;
	valueUnion getValue() ;
	void __show(std::fstream& fout) ;
	virtual Ast::SPL_IR codeGen();
};



class StmtAst:public Ast
// StmtAst is Ast those has not value.
{
	//the function is for debug
	virtual void __show(std::fstream& fout) = 0;
	virtual ~StmtAst() = 0;
};

class IfAst final:public StmtAst {
protected:
	ExprAst* cond;
	StmtAst* ifStmt;
	StmtAst* elseStmt;
public:
	IfAst(ExprAst* cond_, StmtAst* doIf_, StmtAst* doElse_);
	valueUnion getValue();
	void __show(std::fstream& fout);
	void addRight(StmtAst* doElse_);
	StmtAst* getDoElse(void);
	virtual Ast::SPL_IR codeGen();
	~IfAst();
};

class CaseUnit {
	ExprAst* val;
	StmtAst* stmt;
	inline CaseUnit(ExprAst* val_, StmtAst* stmt_) : val(val_), stmt(stmt_) {}
};

class CaseAst final: public StmtAst {
protected:
	ExprAst* cond;
	std::vector<CaseUnit>* caseStmt;
public:
	CaseAst(ExprAst* cond, std::vector<CaseUnit>* caseStmt);
	valueUnion getValue();
	void __show(std::fstream& fout);
	virtual Ast::SPL_IR codeGen();
	~CaseAst();
};

class WhileAst final: public StmtAst
{
protected:
	ExprAst* cond;
	StmtAst* stmt;
public:
	WhileAst(ExprAst* cond_, StmtAst* stmt_);
	~WhileAst();
	valueUnion getValue();
	void __show(std::fstream& fout); 
	virtual Ast::SPL_IR codeGen();
};

class RepeatAst final: public StmtAst
{
protected:
	std::vector<StmtAst*>* stmtList;
	ExprAst* exp;
public:
	RepeatAst(std::vector<StmtAst*>* stmtList_, ExprAst* exp_);
	~RepeatAst();
	valueUnion getValue(std::fstream& fout);
	void __show();
	virtual Ast::SPL_IR codeGen();
};

class ForAst final: public StmtAst
{
protected:
	AssignAst* init;
	bool dir_init_to_end;
	ExprAst* end;
	StmtAst* stmt;
public:
	ForAst(AssignAst* init_, bool dir_, ExprAst* fin_, StmtAst* stmt_);
	~ForAst();
	valueUnion getValue(std::fstream& fout);
	void __show();
	virtual Ast::SPL_IR codeGen();
};

class GotoAst final: public StmtAst
{
protected:
	int label;
public:
	GotoAst(int label_);
	~GotoAst();
	int getlabel();
	valueUnion getValue();
	void __show(std::fstream& fout);
	virtual Ast::SPL_IR codeGen();
};

class CompoundAst final: public StmtAst
{
protected:
	std::vector<StmtAst*>* stmtList;
public:
	CompoundAst(std::vector<StmtAst*>* stmtList_);
	~CompoundAst();
	valueUnion getValue();
	void __show(std::fstream& fout);
	virtual Ast::SPL_IR codeGen();
};

class FuncAst : public ExprAst
{
protected:
	bool isProc;
	std::string funcName;
	std::vector<ExprAst*>* argList;
public:
	FuncAst(bool isProc_, std::string& funcName_, std::vector<ExprAst*>* argList_);
	~FuncAst();
	valueUnion getValue();
	void __show(std::fstream& fout);
	virtual Ast::SPL_IR codeGen();
};

class SysFuncAst final:public FuncAst {
protected:
	SYS_FUNC_ID id;
public:
	SysFuncAst(int sysFuncId_, std::vector<ExprAst*>* argList_);
	virtual Ast::SPL_IR codeGen();
};

}
