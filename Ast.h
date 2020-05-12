#ifndef _AST_H
#define _AST_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
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

	//check semantic for ast
	virtual bool check() = 0;
	//get the value of ast, if has not, return ERROR_NO_VAL
	virtual valueUnion getValue() = 0;
	//this function is used to convert AST to IR, and add it to 'ir'.
	virtual void toIR(SPL_IR* ir) = 0;
	//the function is for debug
	virtual void __show(std::fstream& fout) = 0;
	virtual ~Ast() = 0;
};

class ExprAst:public Ast 
// ExprAst is Ast those has value, such as 2+3(MathAst),a[i](ArrayAst),a = 2+3, ...
{
public:
	SPL_TYPE valueType;

	virtual bool check() = 0;
	//get Ast's value (if has)
	virtual valueUnion getValue() = 0;
	virtual void toIR(SPL_IR* ir) = 0;
	virtual void __show(std::fstream& fout) = 0;
	virtual ~ExprAst() = 0;
};

class MathAst :public ExprAst {
//such as expr + expr
protected:
	SPL_OP op;
	ExprAst* lchild;
	ExprAst* rchild;
public:
	MathAst(SPL_OP op, ExprAst* left = nullptr, ExprAst* right = nullptr);
	bool check();
	valueUnion getValue();
	void toIR(SPL_IR* ir);
	void __show(std::fstream& fout);
	~MathAst();
};

class ConstAst : public ExprAst {
protected:
	valueUnion value;
public:
	ConstAst(char x);
	ConstAst(int x);
	ConstAst(double x);
	ConstAst(bool x);
	ConstAst(const std::string& x);
	valueUnion getValue();
	bool check();
	void __show(std::fstream& fout);
	void toIR(SPL_IR* ir);
	~ConstAst();
};

class SymbolAst : public ExprAst {
public:

	std::string id;
	unsigned int scopeIndex;
	Symbol* symbol;


	SymbolAst(std::string& id_, unsigned int scopeIndex_, Symbol* s);
	~SymbolAst();
	valueUnion getValue();
	bool check();
	void __show(std::fstream& fout);
	void toIR(SPL_IR* ir);
	Symbol* get_symbol() {
		//TODO: THROW
		return symbol;
	}


};

class ArrayAst : public ExprAst {
public:
	//void print(void);
	Symbol* symbol;
	SymbolAst* sym;
	ExprAst* exp;

	ArrayAst(SymbolAst* sym_, ExprAst* exp_);
	bool check();
	valueUnion getValue();
	void __show(std::fstream& fout);
	void toIR(SPL_IR* ir);
	Symbol* get_symbol() {
		//if (!symbol) throw invalid_argument{ "access void pointer in symbol: " + sym->id };
		return symbol;
	}
	~ArrayAst();
	
};

class DotAst :public ExprAst {
protected:
	SymbolAst* record;
	SymbolAst* field;

public:
	DotAst(SymbolAst* record_, SymbolAst* field_);
	bool check();
	valueUnion getValue();
	void __show(std::fstream& fout);
	void toIR(SPL_IR* ir);
	~DotAst();
};

class AssignAst :public ExprAst {
protected:
	ExprAst* lhs;
	ExprAst* rhs;

public:
	AssignAst(ExprAst* lhs_, ExprAst* rhs_);
	~AssignAst() ;
	valueUnion getValue() ;
	void __show(std::fstream& fout) ;
	bool check();
	void toIR(SPL_IR* ir) ;
	
};



class StmtAst :public Ast
// StmtAst is Ast those has not value.
{
	virtual bool check() = 0;
	//this function is used to convert AST to IR, and add it to 'ir'.
	virtual void toIR(SPL_IR* ir) = 0;
	//the function is for debug
	virtual void __show(std::fstream& fout) = 0;
	virtual ~StmtAst() = 0;
};

class IfAst :public StmtAst {
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
	bool check();
	void toIR(SPL_IR* ir);
	~IfAst();
};

class CaseUnit {
	ExprAst* val;
	StmtAst* stmt;
	inline CaseUnit(ExprAst* val_, StmtAst* stmt_) : val(val_), stmt(stmt_) {}
};

class CaseAst : public StmtAst {
protected:
	ExprAst* cond;
	std::vector<CaseUnit>* caseStmt;
public:
	CaseAst(ExprAst* cond, std::vector<CaseUnit>* caseStmt);
	valueUnion getValue();
	void __show(std::fstream& fout);
	bool check();
	void toIR(SPL_IR* ir);
	~CaseAst();
};

class WhileAst : public StmtAst
{
protected:
	ExprAst* cond;
	StmtAst* stmt;

public:
	WhileAst(ExprAst* cond_, StmtAst* stmt_);
	~WhileAst();
	valueUnion getValue();
	void __show(std::fstream& fout);
	bool check() ;
	void toIR(SPL_IR* ir);

};

class RepeatAst : public StmtAst
{
protected:
	std::vector<StmtAst*>* stmtList;
	ExprAst* exp;
public:
	RepeatAst(std::vector<StmtAst*>* stmtList_, ExprAst* exp_);
	~RepeatAst();
	valueUnion getValue(std::fstream& fout);
	void __show();
	bool check();
	void toIR(SPL_IR* ir);


};

class ForAst : public StmtAst
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
	bool check();
	void toIR(SPL_IR* ir);

};

class GotoAst : public StmtAst
{
protected:
	int label;
public:
	GotoAst(int label_);
	~GotoAst();
	int getlabel();
	valueUnion getValue();
	void __show(std::fstream& fout);
	bool check();
	void toIR(SPL_IR* ir);
};

class CompoundAst : public StmtAst
{
protected:
	std::vector<StmtAst*>* stmtList;
public:
	CompoundAst(std::vector<StmtAst*>* stmtList_);
	~CompoundAst();
	valueUnion getValue();
	void __show(std::fstream& fout);
	bool check();
	void toIR(SPL_IR* ir);
};

class FuncAst : public ExprAst
{
protected:
	bool isProc;
	std::string funcID;
	std::vector<ExprAst*>* argList;
	unsigned int scopeIndex;
	Symbol* symbol;
public:
	FuncAst(bool isProc_, std::string& funcId_, std::vector<ExprAst*>* argList_, unsigned int scopeIndex, Symbol* symbol_);
	~FuncAst();
	valueUnion getValue();
	void __show(std::fstream& fout);
	bool check();
	void toIR(SPL_IR* ir);
	Symbol* get_symbol() {
		//if (!symbol) throw invalid_argument{ "access void pointer in function: " + funcId };
		return symbol;
	}
};

class SysFuncAst :public FuncAst {
protected:
	int sys_func_id;
public:
	SysFuncAst(int sysFuncId_, std::vector<ExprAst*>* argList_);
};


class AST_Manager
{

public:
	std::vector<Ast*>* functions = nullptr;
	std::vector<unsigned int>* scopes = nullptr;
	std::vector<unsigned int>* defined_scopes = nullptr;
	//std::vector<std::string> *name = nullptr;
	AST_Manager() {
		functions = new std::vector<Ast*>();
		scopes = new std::vector<unsigned int>();
		defined_scopes = new std::vector<unsigned int>();
	}
	void addFunc(Ast* func, unsigned int scope, unsigned int preScope) {
		functions->emplace_back(func);
		scopes->emplace_back(scope);
		defined_scopes->emplace_back(preScope);
	}
	void __show(std::fstream& fout) {
		for (std::vector<Ast*>::iterator it = functions->begin(); it != functions->end(); ++it) {
			Ast* ast = *it;
			ast->__show(fout);
			fout << std::endl;
		}
	}
	~AST_Manager() {}
};



}

#endif