#include "Ast.h"

using namespace SPL;

int node_count = 0;

LabelAst::LabelAst(int label_, StmtAst* nonLabelAst_) :
	label(label_), nonLabelAst(nonLabelAst_) {
	this->nodeType = AST_LABEL;
}

void LabelAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num = node_count++;

	fout << "_" << num << "[label=\"label:" << this->label << "\"]" << std::endl;
	fout << "_" << num << " -> _" << next_num << std::endl;
	this->nonLabelAst->__show(fout, next_num);
}

LabelAst::~LabelAst() {
	;
}

Ast::Ast() {
	;
}

Ast::~Ast() {
	;
}

// ExprAst::ExprAst() {
// 	;
// }

// ExprAst::~ExprAst() {
// 	;
// }
StmtAst::StmtAst() {
	;
}

StmtAst::~StmtAst() {
	;
}


MathAst::MathAst(SPL_OP op_, ExprAst* left , ExprAst* right) :
	op(op_), lchild(left), rchild(right) {
	this->nodeType = AST_MATH;
}

void MathAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=\"op:" << this->op << "\"]" << std::endl;
	if (this->lchild){
		int next_num1 = node_count++;
		fout << "_" << num << " -> _" << next_num1 << std::endl;
		this->lchild->__show(fout, next_num1);
	} 
	if (this->rchild){
		int next_num2 = node_count++;
		fout << "_" << num << " -> _" << next_num2 << std::endl;
		this->rchild->__show(fout, next_num2);
	} 
	fout<<std::endl;
}

MathAst::~MathAst() {
	;
}


ConstAst::ConstAst(char x) :
	type(CHAR) {
	this->value.valChar = x;
	this->nodeType = AST_CONST_DECL;
}
ConstAst::ConstAst(int x) :
	type(INT) {
	this->value.valInt = x;
	this->nodeType = AST_CONST_DECL;
}
ConstAst::ConstAst(double x):
	type(REAL) {
	this->value.valDouble = x;
	this->nodeType = AST_CONST_DECL;
}
ConstAst::ConstAst(bool x) :
	type(BOOL) {
	this->value.valBool = x;
	this->nodeType = AST_CONST_DECL;
}
ConstAst::ConstAst(std::string x) :
	type(STRING) {
	this->value.valString = new std::string(x);
	this->nodeType = AST_CONST_DECL;
}

void ConstAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	switch (type) {
	case STRING:fout << "_" << num << "[label=\"String: " << *(this->value.valString) << "\"]" << std::endl;break;
	case INT:fout << "_" << num << "[label=\"Int: " << this->value.valInt << "\"]" << std::endl;break;
	case REAL:fout << "_" << num << "[label=\"Double: " << this->value.valDouble << "\"]" << std::endl;break;
	case BOOL:fout << "_" << num << "[label=\"Bool: " << this->value.valBool << "\"]" << std::endl;break;
	case CHAR:fout << "_" << num << "[label=\"Char: " << this->value.valChar << "\"]" << std::endl;break;
	}
}

ConstAst::~ConstAst() {
	;
}

TypeAst::TypeAst() {
	;
}

TypeAst::~TypeAst() {
	;
}

SimpleTypeAst::SimpleTypeAst(const std::string& name_):
	name(name_) {
	;
}

void SimpleTypeAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=\"SimpleType: " << name << "\"]" << std::endl;
}

SimpleTypeAst::~SimpleTypeAst() {;}

ArrayTypeAst::ArrayTypeAst(TypeAst* memberType_, IndexAst* minIndex_, IndexAst* maxIndex_) :
	memberType(memberType_), minIndex(minIndex_), maxIndex(maxIndex_) {
	;
}

void ArrayTypeAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;
	int next_num3 = node_count++;
	fout << "_" << num << "[label=array]" << std::endl;

	fout << "_" << num << " -> _" << next_num1 << "[label=type]"  << std::endl;
	this->memberType->__show(fout, next_num1);
	fout << "_" << num << " -> _" << next_num2 << "[label=minIndex]"  << std::endl;
	this->minIndex->__show(fout, next_num2);
	fout << "_" << num << " -> _" << next_num3 << "[label=maxIndex]"  << std::endl;
	this->maxIndex->__show(fout, next_num3);
}


ArrayTypeAst::~ArrayTypeAst() {;}

RecordTypeAst::RecordTypeAst() : members() {
	;
}

RecordTypeAst::RecordTypeAst(std::vector<std::pair<TypeAst*, std::string> > members_) : members() {
/*	for (auto member:members_) {
		std::pair< std::unique_ptr<TypeAst>, std::string > t(member);
		members.push_back(t);
	}
*/
}


void RecordTypeAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=Record]" << std::endl;
	for (int i=0;i<this->members.size();i++) {
		int next_num = node_count++;
		fout << "_" << num << " -> _" << next_num << "[label=\"member"<< i <<":"<<this->members[i].second << "\"]" << std::endl;
		this->members[i].first->__show(fout, next_num);
	}
}

void RecordTypeAst::addMember(std::pair<TypeAst*, std::vector<std::string> > mem_) {
	for (auto name:mem_.second ) {
		std::unique_ptr<TypeAst> tp(mem_.first);
		this->members.push_back(std::pair<std::unique_ptr<TypeAst>, std::string> ( std::move(tp), name ));
	}
}

RecordTypeAst::~RecordTypeAst() {;}

SymbolAst::SymbolAst(const std::string& name_) :
	name(name_) {
	this->nodeType = AST_SYMBOL;
}

void SymbolAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=\"Symbol: " << this->name << "\"]" << std::endl;
}

SymbolAst::~SymbolAst() {
	;
}


ArrayAst::ArrayAst(VarAst* sym_, ExprAst* exp_) :
	sym(sym_), exp_index(exp_) {
	this->nodeType = AST_ARRAY;
}

void ArrayAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;
	fout << "_" << num << "[label=Array]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=name]" << std::endl;
	this->sym->__show(fout, next_num1);
	fout << "_" << num << " -> _" << next_num2 << "[label=index]" << std::endl;
	this->exp_index->__show(fout, next_num2);
}

ArrayAst::~ArrayAst() {
	;
}

AssignAst::AssignAst(VarAst* lhs_, ExprAst* rhs_) :
	lhs(lhs_), rhs(rhs_) {
	this->nodeType = AST_ASSIGN;

}

void AssignAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;
	fout << "_" << num << "[label=\":=\"]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=LhsVar]" << std::endl;
	this->lhs->__show(fout, next_num1);
	fout << "_" << num << " -> _" << next_num2 << "[label=RhsVar]" << std::endl;
	this->rhs->__show(fout, next_num2);
}

AssignAst::~AssignAst() {
	;
}


IfAst::IfAst(ExprAst* cond_, StmtAst* doIf_, StmtAst* doElse_) :
	cond(cond_),ifStmt(doIf_),elseStmt(doElse_) {
	this->nodeType = AST_IF;
}

void IfAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;

	fout << "_" << num << "[label=If]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=cond]" << std::endl;
	this->cond->__show(fout, next_num1);
	fout << "_" << num << " -> _" << next_num2 << "[label=doIf]" << std::endl;
	this->ifStmt->__show(fout, next_num2);
	if (this->elseStmt) {
		int next_num3 = node_count++;
		fout << "_" << num << " -> _" << next_num3 << "[label=else]" << std::endl;
		this->elseStmt->__show(fout, next_num3);
	} 
}

void IfAst::addRight(StmtAst* doElse_) {
	this->elseStmt.reset(doElse_);
}

IfAst::~IfAst() {
	;
}

CaseAst::CaseAst(ExprAst* cond_, std::vector<CaseUnit*> caseStmt_):
	cond(cond_) {
	this->nodeType = AST_CASE;
	for (auto it:caseStmt_) {
		this->caseStmt.push_back(it);
	}
}

void CaseAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	fout << "_" << num << "[label=CASE]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=cond]" << std::endl;
	this->cond->__show(fout, next_num1);
	for (int i=0;i<this->caseStmt.size();i++) {
		if (this->caseStmt[i]) {
			int next_num2 = node_count++;
			fout << "_" << next_num2 << "[label=CASE" << i+1 << "]" << std::endl;
			fout << "_" << num << " -> _" << next_num2 << std::endl;
			if (this->caseStmt[i]->val){
				int next_num3 = node_count++;
				fout << "_" << next_num2 << " -> _" << next_num3 << "[label=val" << std::endl;
				this->caseStmt[i]->val->__show(fout, next_num3);
			} 
			if (this->caseStmt[i]->stmt){
				int next_num4 = node_count++;
				fout << "_" << next_num2 << " -> _" << next_num4 << "[label=stmt" << std::endl;
				this->caseStmt[i]->stmt->__show(fout, next_num4);
			} 
		}
	}
}

CaseAst::~CaseAst() {
	;
}

WhileAst::WhileAst(ExprAst* cond_, StmtAst* stmt_) :
	cond(cond_), stmt(stmt_) {
	this->nodeType = AST_WHILE;
}

void WhileAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;

	fout << "_" << num << "[label=while]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=cond]" << std::endl;
	this->cond->__show(fout, next_num1);
	fout << "_" << num << " -> _" << next_num1 << "[label=stmt]" << std::endl;
	this->stmt->__show(fout, next_num2);
}

WhileAst::~WhileAst() {
	;
}

RepeatAst::RepeatAst(std::vector<StmtAst*>& stmtList_, ExprAst* exp_) :
	exp(exp_) {
	this->nodeType = AST_REPEAT;
	for (auto it : stmtList_) {
		std::unique_ptr<StmtAst> t(it);
		this->stmtList.push_back(std::move(t));
	}
}

void RepeatAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;

	fout << "_" << num << "[label=Repeat]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=exp]" << std::endl;
	this->exp->__show(fout, next_num1);
	fout << "_" << next_num2 << "[label=stmtList]" << std::endl;
	fout << "_" << num << " -> _" << next_num2 << std::endl;
	for (auto it = this->stmtList.begin(); it != this->stmtList.end();it++) {
		int next_num3 = node_count++;
		fout << "_" << next_num2 << " -> _" << next_num3 << std::endl;
		(*it)->__show(fout, next_num3);
	}
}

RepeatAst::~RepeatAst() {
	;
}

ForAst::ForAst(SymbolAst* id_, ExprAst* init_, bool dir_, ExprAst* fin_, StmtAst* stmt_) :
	loop_var(id_), init(init_), dir_init_to_end(dir_), end(fin_), stmt(stmt_) {
	this->nodeType = AST_FOR;
}

void ForAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;
	int next_num3 = node_count++;
	int next_num4 = node_count++;
	int next_num5 = node_count++;

	fout << "_" << num << "[label=For]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=loopvar]" << std::endl;
	this->loop_var->__show(fout, next_num1);
	fout << "_" << num << " -> _" << next_num2 << "[label=init]" << std::endl;
	this->init->__show(fout, next_num2);
	fout << "_" << num << " -> _" << next_num3 << "[label=end]" << std::endl;
	this->end->__show(fout, next_num3);
	fout << "_" << next_num4 << "[label=" << dir_init_to_end << "]" << std::endl;
	fout << "_" << num << " -> _" << next_num4 << "[label=dir]" << std::endl;
	fout << "_" << num << " -> _" << next_num5 << "[label=stmt]" << std::endl;
	this->stmt->__show(fout, next_num5);
}

ForAst::~ForAst() {
	;
}

GotoAst::GotoAst(int label_) :
	label(label_) {
	this->nodeType = AST_GOTO;
}

int GotoAst::getlabel() {
	return this->label;
}

void GotoAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=\"GOTO " << this->label << "\"]" << std::endl;
}

GotoAst::~GotoAst() {
	;
}

CompoundAst::CompoundAst(const std::vector<StmtAst*>& stmtList_) 
	: stmtList() {
	this->nodeType = AST_COMPOUND;
	for (auto it : stmtList_) {
		std::unique_ptr<StmtAst> t(it);
		this->stmtList.push_back(std::move(t));
	}
}

void CompoundAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=Compound]" << std::endl;
	for (auto it = this->stmtList.begin(); it != this->stmtList.end(); it++) {
		int next_num = node_count++;
		fout << "_" << num << " -> _" << next_num << std::endl;
		(*it)->__show(fout, next_num);
	}
}

CompoundAst::~CompoundAst() {
	;
}

FuncAst::FuncAst( std::string& funcName_, std::vector<ExprAst*> argList_) :
	funcName(funcName_) {
	this->StmtAst::nodeType = this->ExprAst::nodeType = AST_FUNC;
	for (auto it : argList_) {
		std::unique_ptr<ExprAst> t(it);
		this->argList.push_back(std::move(t));
	}
}

FuncAst::FuncAst() :
	funcName(), argList() {
	;
}

void FuncAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=\"FUNC: " << this->funcName << "\"]" << std::endl;
	for (auto it = this->argList.begin(); it != this->argList.end(); it++) {
		int next_num = node_count++;
		fout << "_" << num << " -> _" << next_num << "[label=arg]" << std::endl;
		(*it)->__show(fout, next_num);
	}
}

FuncAst::~FuncAst() {
	;
}


DotAst::DotAst(VarAst* record_, std::string& field_) :
	record(record_), field(field_) {
	this->nodeType = AST_DOT;
}

void DotAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;

	fout << "_" << num << "[label=Dot]" << std::endl;
	fout << "_" << next_num1 << "[label=" << this->field << "]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=field]" << std::endl;
	fout << "_" << num << " -> _" << next_num2 << "[label=record]" << std::endl;
	this->record->__show(fout, next_num2);
}

DotAst::~DotAst() {
	;
}

RecordDeclAst::RecordDeclAst(std::string t_name, std::vector<std::pair<TypeAst*, std::string>> t_members) :
	name(t_name) {
	this->nodeType = AST_RECORD_DECL;
	for (auto it : t_members) {
		std::unique_ptr<TypeAst> t(it.first);
		this->members.push_back(std::pair<std::unique_ptr<TypeAst>, std::string>(std::move(t), it.second));
	}
}

void RecordDeclAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=\"Record Decl: " << name << "\"]" << std::endl;
	for (auto it = this->members.begin(); it != this->members.end(); it++) {
		int next_num = node_count++;
		fout << "_" << num << " -> _" << next_num << "[label=member]" << std::endl;
		(it->first)->__show(fout, next_num);
	}
}

RecordDeclAst::~RecordDeclAst() { ; }

FuncDeclAst::FuncDeclAst(std::string& funcName_, CompoundAst* body_, const std::vector<std::pair<TypeAst*, std::string>>& args_, const std::vector<bool>& is_var_, TypeAst* ret_type_) :
	name(funcName_), body(body_), is_var(is_var_), ret_type(ret_type_) {
	this->nodeType = AST_FUNC_DECL;
	for (auto it : args_) {
		std::unique_ptr<TypeAst> t(it.first);
		this->args.push_back(arg_t(std::move(t), it.second));
	}
}

void FuncDeclAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num2 = node_count++;

	fout << "_" << num << "[label=\"Func Decl: " << this->name << "\"]" << std::endl;
	for (int i = 0; i < args.size(); i++) {
		int next_num = node_count++;
		if (this->is_var[i]){
			fout << "_" << num << " -> _" << next_num << "[label=\"Para Var: "<<this->args[i].second << "\"]" << std::endl;
		} 
		else{
			fout << "_" << num << " -> _" << next_num << "[label=\"Para non_Var:"<<this->args[i].second << "\"]" << std::endl;
		} 
		this->args[i].first->__show(fout, next_num);
	}
	fout << "_" << num << " -> _" << next_num2 << "[label=body]" << std::endl;
	this->body->__show(fout, next_num2);
}

FuncDeclAst::~FuncDeclAst() {
	;
}

ConstDeclAst::ConstDeclAst(std::string& name_, SPL_TYPE type_, valueUnion const_value_):
	name(name_), type(type_), const_value(const_value_){
	this->nodeType = AST_CONST_DECL;
}

void ConstDeclAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=\"Const " << this->type << ": " << this->name << "\"]" << std::endl;
}

ConstDeclAst::~ConstDeclAst() {
	;
}

SimpleVarDeclAst::SimpleVarDeclAst(const std::string& name_, TypeAst* type_) :
	name(name_), type(type_){
	this->nodeType = AST_SIMPLE_VAR_DECL;
}

void SimpleVarDeclAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num = node_count++;

	fout << "_" << num << "[label=\"SimpleVarDecl: " << this->name << "\"]" << std::endl;
	fout << "_" << num << " -> _" << next_num << "[label=type]" << std::endl;
	this->type->__show(fout, next_num);
}

SimpleVarDeclAst::~SimpleVarDeclAst() { ; }

TypeDeclAst::TypeDeclAst(std::string& name_, TypeAst* type_):
	name(name_), type(type_) {
	this->nodeType = AST_TYPE_DECL;
}

void TypeDeclAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num = node_count++;

	fout << "_" << num << "[label=\"TypeDec:" << this->name << "\"]" << std::endl;
	fout << "_" << num << " -> _" << next_num << "[label=type]" << std::endl;
	this->type->__show(fout, next_num);
}

TypeDeclAst::~TypeDeclAst() { ; }

ArrayDeclAst::ArrayDeclAst(std::string& name_, ConstAst* minIndex_, ConstAst* maxIndex_, TypeAst* type_) :
	name(name_), minIndex(minIndex_), maxIndex(maxIndex_), type(type_) {
	this->nodeType = AST_ARRAY_DECL;
}

void ArrayDeclAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	int next_num1 = node_count++;
	int next_num2 = node_count++;

	fout << "_" << num << "[label=ArrayDec]" << std::endl;
	fout << "_" << next_num1 << "[label=" << this->name << "]" << std::endl;
	fout << "_" << num << " -> _" << next_num1 << "[label=name]" << std::endl;
	fout << "_" << num << " -> _" << next_num2 << "[label=type]" << std::endl;
	this->type->__show(fout, next_num2);
}

ArrayDeclAst::~ArrayDeclAst() {
	;
}


SysFuncAst::SysFuncAst(SYS_FUNC_ID sysFuncId_, std::vector<ExprAst*>& argList_) :
	id(sysFuncId_) {
	this->FuncAst::ExprAst::nodeType = this->FuncAst::StmtAst::nodeType = AST_SYSFUNC;
	for (auto it : argList_) {
		std::unique_ptr<ExprAst> t(it);
		this->argList.push_back(std::move(t));
	}
}

void SysFuncAst::__show(std::fstream& fout, int node_num) {
	int num = (node_num == -1 ? node_count++ : node_num);
	fout << "_" << num << "[label=\"SYSFUNC: " << this->id << "\"]" << std::endl;
	for (auto it = this->argList.begin(); it != this->argList.end(); it++) {
		int next_num = node_count++;
		fout << "_" << num << " -> _" << next_num << "[label=arg]" << std::endl;
		(*it)->__show(fout, next_num);
	}
}

SysFuncAst::~SysFuncAst() {
	;
}
