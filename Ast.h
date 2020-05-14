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

		//get the value of ast, if has not, return ERROR_NO_VAL
		virtual valueUnion getValue() = 0;
		//the function is for debug
		virtual void __show(std::fstream& fout) = 0;
		virtual ~Ast() = 0;
	};

	class LabelAst final: public Ast {
	private:
		int label;
		std::unique_ptr<Ast> nonLabelAst;
	public:
		LabelAst(int label_, Ast* nonLabelAst_);
		ExprAst::SPL_IR codeGen() const;
		~LabelAst();
	};

	class ExprAst : public Ast
		// ExprAst is Ast those has value, such as 2+3(MathAst),a[i](ArrayAst),a = 2+3, ...
	{
	public:
		SPL_TYPE valueType;
		using SPL_IR = llvm::Value*;
		//get Ast's value (if has)
		virtual valueUnion getValue() = 0;
		virtual void __show(std::fstream& fout) = 0;
		virtual ~ExprAst() = 0;
		virtual SPL_IR codeGen() const = 0;
	};

	class IndexAst {
	public:
		IndexAst();
		~IndexAst();
	};

	class MathAst final :public ExprAst {
		//such as expr + expr
	protected:
		SPL_OP op;
		std::unique_ptr<ExprAst> lchild;
		std::unique_ptr<ExprAst> rchild;
	public:
		MathAst(SPL_OP op, ExprAst* left = nullptr, ExprAst* right = nullptr);
		valueUnion getValue();
		void __show(std::fstream& fout);
		ExprAst::SPL_IR codeGen() const override;
		~MathAst();
	};

	class ConstAst final : public ExprAst,public IndexAst {
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
		ExprAst::SPL_IR codeGen() const;
		~ConstAst();
	};

	class SymbolAst final : public ExprAst,public IndexAst {
	protected:
		std::string name;
	public:
		SymbolAst(const std::string& name);
		~SymbolAst();
		valueUnion getValue();
		void __show(std::fstream& fout);
		ExprAst::SPL_IR codeGen() const;
	};

	class ArrayAst final : public ExprAst {
	protected:
		//void print(void);
		std::string arrayName;
		std::unique_ptr<SymbolAst> sym;
		std::unique_ptr<ExprAst> exp_index;
	public:
		ArrayAst(SymbolAst* sym_, ExprAst* exp_);
		valueUnion getValue();
		void __show(std::fstream& fout);
		~ArrayAst();
		ExprAst::SPL_IR codeGen() const;
	};

	class AssignAst final :public ExprAst {
	protected:
		std::unique_ptr<ExprAst> lhs;
		std::unique_ptr<ExprAst> rhs;
	public:
		AssignAst(ExprAst* lhs_, ExprAst* rhs_);
		~AssignAst();
		valueUnion getValue();
		void __show(std::fstream& fout);
		ExprAst::SPL_IR codeGen() const;
	};

	class StmtAst :public Ast
		// StmtAst is Ast those has not value.
	{
		//the function is for debug
		virtual void __show(std::fstream& fout) = 0;
		virtual ~StmtAst() = 0;
	public:
		virtual void codeGen() const;
	};

	class IfAst final :public StmtAst {
	protected:
		std::unique_ptr<ExprAst> cond;
		std::unique_ptr<StmtAst> ifStmt;
		std::unique_ptr<StmtAst> elseStmt;
	public:
		IfAst(ExprAst* cond_, StmtAst* doIf_, StmtAst* doElse_);
		valueUnion getValue();
		void __show(std::fstream& fout);
		void addRight(StmtAst* doElse_);
		StmtAst* getDoElse(void);
		void codeGen() const override;
		~IfAst();
	};

	class CaseUnit {
		std::unique_ptr<ExprAst> val;
		std::unique_ptr<StmtAst> stmt;
		inline CaseUnit(ExprAst* val_, StmtAst* stmt_) : val(val_), stmt(stmt_) {}
	};

	class CaseAst final : public StmtAst {
	protected:
		std::unique_ptr<ExprAst> cond;
		std::vector<CaseUnit>* caseStmt;
	public:
		CaseAst(ExprAst* cond, std::vector<CaseUnit>* caseStmt);
		valueUnion getValue();
		void __show(std::fstream& fout);
		void codeGen() const override;
		~CaseAst();
	};

	class WhileAst final : public StmtAst
	{
	protected:
		std::unique_ptr<ExprAst> cond;
		std::unique_ptr<StmtAst> stmt;
	public:
		WhileAst(ExprAst* cond_, StmtAst* stmt_);
		~WhileAst();
		valueUnion getValue();
		void __show(std::fstream& fout);
		void codeGen() const override;
	};

	class RepeatAst final : public StmtAst
	{
	protected:
		std::vector<std::unique_ptr<StmtAst>>* stmtList;
		std::unique_ptr<ExprAst> exp;
	public:
		RepeatAst(std::vector<StmtAst*>* stmtList_, ExprAst* exp_);
		~RepeatAst();
		valueUnion getValue(std::fstream& fout);
		void __show();
		void codeGen() const override;
	};

	class ForAst final : public StmtAst
	{
	protected:
		std::unique_ptr<AssignAst> init;
		bool dir_init_to_end;
		std::unique_ptr<ExprAst> end;
		std::unique_ptr<StmtAst> stmt;
	public:
		ForAst(AssignAst* init_, bool dir_, ExprAst* fin_, StmtAst* stmt_);
		~ForAst();
		valueUnion getValue(std::fstream& fout);
		void __show();
		void codeGen() const override;
	};

	class GotoAst final : public StmtAst
	{
	protected:
		int label;
	public:
		GotoAst(int label_);
		~GotoAst();
		int getlabel();
		valueUnion getValue();
		void __show(std::fstream& fout);
		void codeGen() const override;
	};

	class CompoundAst final : public StmtAst
	{
	protected:
		std::vector<std::unique_ptr<StmtAst>>* stmtList;
	public:
		CompoundAst(std::vector<StmtAst*>* stmtList_);
		~CompoundAst();
		valueUnion getValue();
		void __show(std::fstream& fout);
		void codeGen() const override;
	};

	class FuncAst : public ExprAst
	{
	protected:
		bool isProc;
		std::string funcName;
		std::vector<std::unique_ptr<ExprAst>> argList;
	public:
		FuncAst(bool isProc_, std::string& funcName_, std::vector<ExprAst*> argList_);
		~FuncAst();
		valueUnion getValue();
		void __show(std::fstream& fout);
		ExprAst::SPL_IR codeGen() const override;
	};

	class TypeAst
	{
	private:
		std::string name;
		bool isArray;
		std::unique_ptr<TypeAst> ArrayMemType;
		int arrayLen;
	public:
		TypeAst(const std::string& t_name);
		llvm::Type* codeGen() const;
	};


	class DotAst final :public ExprAst {
	protected:
		std::unique_ptr<TypeAst> record;
		std::string field;
	public:
		DotAst(SymbolAst* record_, SymbolAst* field_);
		valueUnion getValue();
		void __show(std::fstream& fout);
		~DotAst();
		ExprAst::SPL_IR codeGen() const;
	};


	class RecordDeclAst
	{
	private:
		std::string name;
		std::vector<std::pair<std::unique_ptr<TypeAst>, std::string>> members;
	public:
		RecordDeclAst(std::string t_name, std::vector<std::pair<TypeAst*, std::string>> t_members);
		llvm::Value* codeGen() const;
	};

	class FuncDeclAst
	{
	private:
		std::string name;
		std::unique_ptr<CompoundAst> body;
		std::vector<std::pair<std::unique_ptr<TypeAst>, std::string>> varArgs;
		std::vector<std::pair<std::unique_ptr<TypeAst>, std::string>> valArgs;
		std::unique_ptr<TypeAst> ret_type;
	public:
		FuncDeclAst(bool isProc_, std::string& funcName_, std::vector<ExprAst*>* varArgList_, std::vector<ExprAst*>* valArgList_);
		llvm::Function* codeGen() const;
	};

	class ConstDeclAst {
	private:
		std::string name;
		SPL_TYPE type;
		valueUnion const_value;
	public:
		ConstDeclAst(std::string& name_, SPL_TYPE type_, valueUnion const_value_);
		llvm::Function* codeGen() const;
	};

	class SimpleVarDeclAst
	{
	private:
		std::string name;
		SPL_TYPE type;
	public:
		SimpleVarDeclAst(std::string& name_, SPL_TYPE type);
		llvm::Value* codeGen() const;
	};

	class TypeDeclAst {
	private:
		std::string name;
		std::unique_ptr<TypeAst> type;
	public:
		TypeDeclAst(std::string& name_, TypeAst* type_);
		llvm::Value* codeGen() const;
	};

	

	class ArrayDeclAst {
	private:
		std::string name;
		std::unique_ptr<IndexAst> minIndex;
		std::unique_ptr<IndexAst> maxIndex;
		std::unique_ptr<TypeAst> type;
	public:
		ArrayDeclAst(std::string& name_, ConstAst* minIndex_, ConstAst* maxIndex_, TypeAst* type);
		llvm::Value* codeGen(); const;
	};



class SysFuncAst final:public FuncAst {
protected:
	SYS_FUNC_ID id;
public:
	SysFuncAst(int sysFuncId_, std::vector<ExprAst*>* argList_);
	ExprAst::SPL_IR codeGen() const override;
};

}
