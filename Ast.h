#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "SPL_common.h"
#include <llvm/IR/Value.h>

namespace SPL {
	class Ast {
	public:
		using SPL_IR = llvm::Value*;
		AST_NODE_TYPE nodeType;
		Ast();
		//get the value of ast, if has not, return ERROR_NO_VAL
		//virtual valueUnion getValue() = 0;
		//the function is for debug
		virtual void __show(std::fstream& fout) = 0;
		virtual ~Ast() = 0;
		virtual SPL_IR codeGen() const = 0;
	};
	
	class LabelAst final: public Ast {
	private:
		int label;
		std::unique_ptr<Ast> nonLabelAst;
	public:
		LabelAst(int label_, Ast* nonLabelAst_);
		Ast::SPL_IR codeGen() const;
		void __show(std::fstream& fout);
		~LabelAst();
	};
	
	class ExprAst : public Ast
		// ExprAst is Ast those has value, such as 2+3(MathAst),a[i](ArrayAst),a = 2+3, ...
	{
	public:
		SPL_TYPE valueType;
		using SPL_IR = void;
		ExprAst();
		//get Ast's value (if has)
		//virtual valueUnion getValue() = 0;
		virtual void __show(std::fstream& fout) = 0;
		virtual ~ExprAst() = 0;
	};
	
	class IndexAst {
	public:
		IndexAst();
		~IndexAst();
		virtual int genIndex() const = 0;
	};

	class MathAst final : public ExprAst {
		//such as expr + expr
	protected:
		SPL_OP op;
		std::unique_ptr<ExprAst> lchild;
		std::unique_ptr<ExprAst> rchild;
	public:
		MathAst(SPL_OP op, ExprAst* left = nullptr, ExprAst* right = nullptr);
		//valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
		~MathAst();
	};

	class ConstAst final : public ExprAst, public IndexAst {
	protected:
		valueUnion value;
		SPL_TYPE type;
	public:
		ConstAst(char x);
		ConstAst(int x);
		ConstAst(double x);
		ConstAst(bool x);
		ConstAst(std::string& x);
		int genIndex() const override;
		// valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const;
		~ConstAst();
	};
	
	class VarAst : public ExprAst{
    public:
		virtual Ast::SPL_IR genPtr() const = 0;
	};

	class VarAst : public ExprAst{
    public:
		virtual Ast::SPL_IR genPtr() const = 0;
	};

	class SymbolAst final : public VarAst,public IndexAst {
	protected:
		std::string name;
	public:
		SymbolAst(const std::string& name);
		~SymbolAst();
		valueUnion getValue();
		int genIndex() const override;
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const;
		Ast::SPL_IR genPtr() const override;
	};


	class ArrayAst final : public VarAst {
	protected:
		//void print(void);
		std::string arrayName;
		std::unique_ptr<SymbolAst> sym;
		std::unique_ptr<ExprAst> exp_index;
	public:
		ArrayAst(SymbolAst* sym_, ExprAst* exp_);
		//valueUnion getValue();
		void __show(std::fstream& fout);
		~ArrayAst();
		Ast::SPL_IR codeGen() const;
		Ast::SPL_IR genPtr() const override;
	};

	class AssignAst final :public StmtAst {
	protected:
		std::unique_ptr<VarAst> lhs;
		std::unique_ptr<ExprAst> rhs;
	public:
		AssignAst(VarAst* lhs_, ExprAst* rhs_);
		~AssignAst();
		valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const;
	};
	
	class StmtAst :public Ast
		// StmtAst is Ast those has not value.
	{
		//the function is for debug
	public:
		StmtAst();
		virtual void __show(std::fstream& fout) = 0;
		virtual ~StmtAst() = 0;
	};

	class IfAst final :public StmtAst {
	protected:
		std::unique_ptr<ExprAst> cond;
		std::unique_ptr<StmtAst> ifStmt;
		std::unique_ptr<StmtAst> elseStmt;
	public:
		IfAst(ExprAst* cond_, StmtAst* doIf_, StmtAst* doElse_=nullptr);
		//valueUnion getValue();
		void __show(std::fstream& fout);
		void addRight(StmtAst* doElse_);
		StmtAst* getDoElse(void);
		Ast::SPL_IR codeGen() const override;
		~IfAst();
	};

	struct CaseUnit {
		std::unique_ptr<ExprAst> val;
		std::unique_ptr<StmtAst> stmt;
		inline CaseUnit(ExprAst* val_, StmtAst* stmt_) : val(val_), stmt(stmt_) {
		}
	};

	class CaseAst final : public StmtAst {
	protected:
		std::unique_ptr<ExprAst> cond;
		std::vector<CaseUnit*> caseStmt;
	public:
		CaseAst(ExprAst* cond_, std::vector<CaseUnit*> caseStmt_);
		//valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
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
		//valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
	};

	class RepeatAst final : public StmtAst
	{
	protected:
		std::vector<std::unique_ptr<StmtAst>> stmtList;
		std::unique_ptr<ExprAst> exp;
	public:
		RepeatAst(const std::vector<StmtAst*>& stmtList_, ExprAst* exp_);
		~RepeatAst();
		// valueUnion getValue(std::fstream& fout);
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
	};

	class ForAst final : public StmtAst
	{
	protected:
		std::unique_ptr<SymbolAst> loop_var;
		std::unique_ptr<ExprAst> init;
		std::unique_ptr<ExprAst> end;
		std::unique_ptr<StmtAst> stmt;
		bool dir_init_to_end;
	public:
		ForAst(SymbolAst* id_, ExprAst* init, bool dir_, ExprAst* fin_, StmtAst* stmt_);
		~ForAst();
		// valueUnion getValue(std::fstream& fout);
		void __show(std::fstream& fout) override;
		Ast::SPL_IR codeGen() const override;
	};

	class GotoAst final : public StmtAst
	{
	protected:
		int label;
	public:
		GotoAst(int label_);
		~GotoAst();
		int getlabel();
		//valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
	};

	class CompoundAst final : public StmtAst
	{
	protected:
		std::vector<std::unique_ptr<StmtAst>> stmtList;
	public:
		CompoundAst(const std::vector<StmtAst*>& stmtList_);
		~CompoundAst();
		//valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
	};

	class FuncAst : public ExprAst,public StmtAst
	{
	protected:
		bool isProc;
		std::string funcName;
		std::vector<std::unique_ptr<ExprAst>> argList;
	public:
		FuncAst();
		FuncAst(bool isProc_, std::string& funcName_, std::vector<ExprAst*> argList_);
		~FuncAst();
		//valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
	};

	class TypeAst
	{
	private:
		std::string name;
		bool isArray;
		std::unique_ptr<TypeAst> ArrayMemType;
		int arrayLen;
	public:
		TypeAst(const std::string& t_name, bool isArray_=false, TypeAst* ArrayMemType_=nullptr, int arrayLen_=0);
		void __show(std::fstream& fout);
		~TypeAst();
		llvm::Type* codeGen() const;
	};


	class DotAst final :public VarAst {
	protected:
		std::unique_ptr<SymbolAst> record;
		std::string field;
	public:
		DotAst(SymbolAst* record_, std::string& field_);
		//valueUnion getValue();
		void __show(std::fstream& fout);
		~DotAst();
		Ast::SPL_IR codeGen() const;
		Ast::SPL_IR genPtr() const override;
	};


	class RecordDeclAst final : public Ast
	{
	private:
		std::string name;
		std::vector<std::pair<std::unique_ptr<TypeAst>, std::string>> members;
	public:
		RecordDeclAst(std::string t_name, std::vector<std::pair<TypeAst*, std::string>> t_members);
		void __show(std::fstream& fout);
		~RecordDeclAst();
		llvm::Value* codeGen() const;
	};

	class FuncDeclAst final : public StmtAst
	{
	private:
		using arg_t = std::pair<std::unique_ptr<TypeAst>, std::string>;
		std::string name;
		std::unique_ptr<CompoundAst> body;
		std::vector<arg_t> args;
		std::vector<bool> is_var;
		std::unique_ptr<TypeAst> ret_type;
	public:
		FuncDeclAst(const std::string& funcName_, CompoundAst* body_, const std::vector<std::pair<TypeAst*, std::string>>& args_, const std::vector<bool>& _is_var, TypeAst* ret_type_);
		void __show(std::fstream& fout);
		llvm::Value* codeGen() const;
	};

	class ConstDeclAst final : public StmtAst 
	{
	private:
		std::string name;
		SPL_TYPE type;
		valueUnion const_value;
	public:
		void __show(std::fstream& fout);
		ConstDeclAst(std::string& name_, SPL_TYPE type_, valueUnion const_value_);
		~ConstDeclAst();
		llvm::Value* codeGen() const override;
	};

	class SimpleVarDeclAst final : public StmtAst
	{
	private:
		std::string name;
		std::unique_ptr<TypeAst> type;
	public:
		SimpleVarDeclAst(std::string& name_, TypeAst* type_);
		void __show(std::fstream& fout);
		llvm::Value* codeGen() const;
	};

	class TypeDeclAst final : public StmtAst
	{
	private:
		std::string name;
		std::unique_ptr<TypeAst> type;
	public:
		TypeDeclAst(std::string& name_, TypeAst* type_);
		void __show(std::fstream& fout);
		~TypeDeclAst();
		llvm::Value* codeGen() const;
	};

	class ArrayDeclAst final: public StmtAst{
	private:
		std::string name;
		std::unique_ptr<IndexAst> minIndex;
		std::unique_ptr<IndexAst> maxIndex;
		std::unique_ptr<TypeAst> type;
	public:
		void __show(std::fstream& fout);
		ArrayDeclAst(std::string& name_, ConstAst* minIndex_, ConstAst* maxIndex_, TypeAst* type);
		llvm::Value* codeGen() const;
	};



class SysFuncAst final:public FuncAst {
protected:
	SYS_FUNC_ID id;
public:
	SysFuncAst(int sysFuncId_, std::vector<ExprAst*>* argList_);
	Ast::SPL_IR codeGen() const override;
	SysFuncAst(SYS_FUNC_ID sysFuncId_, std::vector<ExprAst*>& argList_);
	void __show(std::fstream& fout);
	~SysFuncAst();
	//Ast::SPL_IR codeGen() const override;
};
	
}
