#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <fstream>
#include "SPL_common.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/DerivedTypes.h>

namespace SPL {


	class Ast {
	private:
		int lineNo;
	public:
		using SPL_IR = llvm::Value*;
		AST_NODE_TYPE nodeType;
		Ast();
		//get the value of ast, if has not, return ERROR_NO_VAL
		//virtual valueUnion getValue() = 0;
		//the function is for debug
		virtual void __show(std::fstream& fout) = 0;

		void setLineNo(int lineNo_) {this->lineNo = lineNo_;};
		int getLineNo() { return this->lineNo; };
		virtual ~Ast() = 0;
		virtual SPL_IR codeGen() const = 0;
	};

	

	class ExprAst : public Ast
		// ExprAst is Ast those has value, such as 2+3(MathAst),a[i](ArrayAst),a = 2+3, ...
	{
	public:
		SPL_TYPE valueType;
		using SPL_IR = void;
		//get Ast's value (if has)
		//virtual valueUnion getValue() = 0;
		virtual void __show(std::fstream& fout) = 0;
		virtual ~ExprAst() = default;
		ExprAst() = default;
	};

	class IndexAst {
	public:
		IndexAst() {};
		virtual ~IndexAst() {};
		virtual void __show(std::fstream& fout) {};
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
	
	class ConstAst final : public ExprAst,public IndexAst {
	protected:
		valueUnion value;
		SPL_TYPE type;
	public:
		ConstAst(char x);
		ConstAst(int x);
		ConstAst(double x);
		ConstAst(bool x);
		ConstAst(std::string x);
		int genIndex() const override;
		SPL_TYPE getType() {return this->type;};
		valueUnion getValue() {return this->value;};
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
		~ConstAst();
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
		// valueUnion getValue();
		int genIndex() const override;
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
		Ast::SPL_IR genPtr() const override;
	};


	class ArrayAst final : public VarAst {
	protected:
		//void print(void);
		std::unique_ptr<VarAst> sym;
		std::unique_ptr<ExprAst> exp_index;
	public:
		ArrayAst(VarAst* sym_, ExprAst* exp_);
		//valueUnion getValue();
		void __show(std::fstream& fout);
		~ArrayAst();
		Ast::SPL_IR codeGen() const override;
		Ast::SPL_IR genPtr() const override;
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
	

	class AssignAst final : public StmtAst {
	protected:
		std::unique_ptr<VarAst> lhs;
		std::unique_ptr<ExprAst> rhs;
	public:
		AssignAst(VarAst* lhs_, ExprAst* rhs_);
		~AssignAst();
		valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
	};
	
	class LabelAst final: public StmtAst {
	private:
		int label;
		std::unique_ptr<StmtAst> nonLabelAst;
	public:
		LabelAst(int label_, StmtAst* nonLabelAst_);
		Ast::SPL_IR codeGen() const override;
		void __show(std::fstream& fout);
		~LabelAst();
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
		Ast::SPL_IR codeGen() const override;
		~IfAst();
	};

	class CaseUnit {
	public:
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
		RepeatAst(std::vector<StmtAst*>& stmtList_, ExprAst* exp_);
		~RepeatAst();
		//valueUnion getValue(std::fstream& fout);
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
		//valueUnion getValue(std::fstream& fout);
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
		void addStmt(StmtAst* p) { std::unique_ptr<StmtAst> t(p); this->stmtList.push_back(std::move(t));}
		void merge(CompoundAst* p) {
			if (p==nullptr) return;
			for (int i=0;i<(p->stmtList).size();i++) {
				this->stmtList.push_back(std::move(p->stmtList[i]));
			}
		}
		~CompoundAst();
		//valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
	};

	class FuncAst : public ExprAst,public StmtAst
	{
	protected:
		std::string funcName;
		std::vector<std::unique_ptr<ExprAst>> argList;
	public:
		FuncAst();
		FuncAst(std::string& funcName_, std::vector<ExprAst*> argList_);
		~FuncAst();
		//valueUnion getValue();
		void __show(std::fstream& fout);
		Ast::SPL_IR codeGen() const override;
	};

	class TypeAst: public Ast
	{
	
	public:
		TypeAst();
		virtual void __show(std::fstream& fout) = 0;
		virtual ~TypeAst() = 0;
		virtual llvm::Type* genType() const = 0;
		//llvm::Type* codeGen() const override;
	};

	class SimpleTypeAst: public TypeAst {
	private:
		std::string name;
	public:
		SimpleTypeAst(const std::string& name_);
		std::string getName() {return name;};
		void __show(std::fstream& fout);
		llvm::Type* genType() const override;
		~SimpleTypeAst();
	};

	class ArrayTypeAst: public TypeAst {
	private:
		std::unique_ptr<TypeAst> memberType;
		std::unique_ptr<IndexAst> minIndex;
		std::unique_ptr<IndexAst> maxIndex;
	public:
		ArrayTypeAst(TypeAst* memberType_, IndexAst* minIndex_, IndexAst* maxIndex_);
		void __show(std::fstream& fout);
		llvm::Type* genType() const override;
		~ArrayTypeAst();
	};

	class RecordTypeAst: public TypeAst {
	private:
		std::vector<std::pair<std::unique_ptr<TypeAst>, std::string>> members;
	public:
		RecordTypeAst();
		RecordTypeAst(std::vector<std::pair<TypeAst*, std::string> > members_);
		void addMember(std::pair<TypeAst*, std::vector<std::string> > mem_);
		void __show(std::fstream& fout);
		llvm::Type* genType() const override;
		~RecordTypeAst();
	};


	class DotAst final :public VarAst {
	protected:
		std::unique_ptr<VarAst> record;
		std::string field;
	public:
		DotAst(VarAst* record_, std::string& field_);
		//valueUnion getValue();
		void __show(std::fstream& fout);
		~DotAst();
		Ast::SPL_IR codeGen() const override;
		Ast::SPL_IR genPtr() const override;
	};


	class RecordDeclAst final:public StmtAst
	{
	private:
		std::string name;
		std::vector<std::pair<std::unique_ptr<TypeAst>, std::string>> members;
	public:
		RecordDeclAst(std::string t_name, std::vector<std::pair<TypeAst*, std::string>> t_members);
		void __show(std::fstream& fout);
		~RecordDeclAst();
		llvm::Value* codeGen() const override;
		llvm::StructType* genType() const;
	};

	class ParaDecl {
	public:
		std::vector<std::pair<TypeAst*,std::string> > args;
		std::vector<bool> is_var;
		ParaDecl():args(),is_var() { ; };
		void addPara(std::vector<std::string>& name_, TypeAst* type_, bool is_var_) {
			for (auto n:name_) {
				this->args.push_back(std::pair<TypeAst*,std::string> (type_,n));
				this->is_var.push_back(is_var_);
			}
		};
		void addList(ParaDecl* ParaP) {
			for (int i=0;i<ParaP->args.size()&&i<ParaP->is_var.size();i++) {
				this->args.push_back(ParaP->args[i]);
				this->is_var.push_back(ParaP->is_var[i]);
			}
		};
		~ParaDecl() {;};
		
	};

	class FuncDeclAst final :public StmtAst
	{
	private:
		using arg_t = std::pair<std::unique_ptr<TypeAst>, std::string>;
		std::string name;
		std::unique_ptr<CompoundAst> body;
		std::vector<arg_t> args;
		std::vector<bool> is_var;
		std::unique_ptr<TypeAst> ret_type;
	public:
		FuncDeclAst(std::string& funcName_, CompoundAst* body,const std::vector<std::pair<TypeAst*,std::string>>& args_, const std::vector<bool>& is_var_, TypeAst* ret_type_);
		void __show(std::fstream& fout);
		~FuncDeclAst();
		llvm::Value* codeGen() const override;
	};

	class ConstDeclAst final:public StmtAst {
	private:
		std::string name;
		SPL_TYPE type;
		valueUnion const_value;
	public:
		ConstDeclAst(std::string& name_, SPL_TYPE type_, valueUnion const_value_);
		
		void __show(std::fstream& fout);
		~ConstDeclAst();
		llvm::Value* codeGen() const override;
	};

	class VarDeclAst : public StmtAst {
	public:
		VarDeclAst() {};
		~VarDeclAst() {};
	};

	class SimpleVarDeclAst final :public VarDeclAst
	{
	private:
		std::string name;
		std::unique_ptr<TypeAst> type;
	public:
		SimpleVarDeclAst(const std::string& name_, TypeAst* type_);
		void __show(std::fstream& fout);
		~SimpleVarDeclAst();
		llvm::Value* codeGen() const override;
	};

	class TypeDeclAst final: public VarDeclAst {
	private:
		std::string name;
		std::unique_ptr<TypeAst> type;
	public:
		TypeDeclAst(std::string& name_, TypeAst* type_);
		void __show(std::fstream& fout);
		~TypeDeclAst();
		llvm::Value* codeGen() const override;
	};

	class ArrayDeclAst final: public VarDeclAst{
	private:
		std::string name;
		std::unique_ptr<IndexAst> minIndex;
		std::unique_ptr<IndexAst> maxIndex;
		std::unique_ptr<TypeAst> type;
	public:
		ArrayDeclAst(std::string& name_, ConstAst* minIndex_, ConstAst* maxIndex_, TypeAst* type_);
		void __show(std::fstream& fout);
		~ArrayDeclAst();
		llvm::Value* codeGen() const override;
	};



class SysFuncAst final:public FuncAst {
protected:
	SYS_FUNC_ID id;
public:
	SysFuncAst(SYS_FUNC_ID sysFuncId_, std::vector<ExprAst*>& argList_);
	void __show(std::fstream& fout);
	~SysFuncAst();
	//Ast::SPL_IR codeGen() const override;
};

}
