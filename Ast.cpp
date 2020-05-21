#include "Ast.h"

using namespace SPL;


LabelAst::LabelAst(int label_, StmtAst* nonLabelAst_) :
	label(label_), nonLabelAst(nonLabelAst_) {
	this->nodeType = AST_LABEL;
}

void LabelAst::__show(std::fstream& fout) {
	fout << "LabelAst:" << std::endl << "label:" << this->label << std::endl << "nonLabel Ast:" << std::endl;
	this->nonLabelAst->__show(fout);
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

ExprAst::ExprAst() {
	;
}

ExprAst::~ExprAst() {
	;
}
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

void MathAst::__show(std::fstream& fout) {
	fout << "MathAst: \nOperator:" << this->op << std::endl;
	fout << "Left:";
	if (this->lchild) this->lchild->__show(fout);
	fout<<std::endl;
	fout << "Right:";
	if (this->rchild) this->rchild->__show(fout);
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

void ConstAst::__show(std::fstream& fout) {
	fout << "Const Ast:";
	switch (type) {
	case STRING:fout << "STRING:" << *(this->value.valString) << std::endl; break;
	case INT:fout << "INT:" << this->value.valInt << std::endl; break;
	case REAL:fout << "REAL:" << this->value.valDouble << std::endl; break;
	case BOOL:fout << "BOOL:" << this->value.valBool << std::endl; break;
	case CHAR:fout << "CHAR:" << this->value.valChar << std::endl; break;
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

void SimpleTypeAst::__show(std::fstream& fout) {
	fout<<"Simple Type Ast-name:"<<std::endl;
	fout<<name<<std::endl;
}

SimpleTypeAst::~SimpleTypeAst() {;}

ArrayTypeAst::ArrayTypeAst(TypeAst* memberType_, IndexAst* minIndex_, IndexAst* maxIndex_) :
	memberType(memberType_), minIndex(minIndex_), maxIndex(maxIndex_) {
	;
}

void ArrayTypeAst::__show(std::fstream& fout) {
	fout<<"Array Type Ast-Type:"<<std::endl;
	this->memberType->__show(fout);
	fout<<"Array Type Ast-minIndex:"<<std::endl;
	this->minIndex->__show(fout);
	fout<<"Array Type Ast-maxIndex:"<<std::endl;
	this->maxIndex->__show(fout);
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


void RecordTypeAst::__show(std::fstream& fout) {
	fout<<"Record Type Ast-members:"<<std::endl;
	for (int i=0;i<this->members.size();i++) {
		fout<<"members-"<<i<<": \nName:"<<this->members[i].second<<std::endl;
		fout<<"Type:";
		this->members[i].first->__show(fout);
	}
	fout<<"Record Type Ast-end."<<std::endl;
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

void SymbolAst::__show(std::fstream& fout) {
	fout << "SymbolAst:" << this->name << std::endl;
}

SymbolAst::~SymbolAst() {
	;
}


ArrayAst::ArrayAst(VarAst* sym_, ExprAst* exp_) :
	sym(sym_), exp_index(exp_) {
	this->nodeType = AST_ARRAY;
}

void ArrayAst::__show(std::fstream& fout) {
	fout << "ArrayAst:" << std::endl;
	fout << "ArrayNameAst:";
	this->sym->__show(fout);
	fout << "IndexExpAst:";
	this->exp_index->__show(fout);
}

ArrayAst::~ArrayAst() {
	;
}

AssignAst::AssignAst(VarAst* lhs_, ExprAst* rhs_) :
	lhs(lhs_), rhs(rhs_) {
	this->nodeType = AST_ASSIGN;

}

void AssignAst::__show(std::fstream& fout) {
	fout << "AssignAst:" << std::endl;
	fout << "LhsVarAst:";
	this->lhs->__show(fout);
	fout << "RhsExprAst:";
	this->rhs->__show(fout);
}

AssignAst::~AssignAst() {
	;
}


IfAst::IfAst(ExprAst* cond_, StmtAst* doIf_, StmtAst* doElse_) :
	cond(cond_),ifStmt(doIf_),elseStmt(doElse_) {
	this->nodeType = AST_IF;
}

void IfAst::__show(std::fstream& fout) {
	fout << "IfAst:" << std::endl;
	fout << "condAst:";
	this->cond->__show(fout);
	fout << "doIfAst:";
	this->ifStmt->__show(fout);
	if (this->elseStmt) {
		fout << "ElseAst:";
		this->elseStmt->__show(fout);
	} else {
		fout << "No else"<<std::endl;
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

void CaseAst::__show(std::fstream& fout) {
	fout << "CASE AST:" << std::endl;
	this->cond->__show(fout);
	for (int i=0;i<this->caseStmt.size();i++) {
		if (this->caseStmt[i]) {
			fout << "CASE:" <<  std::endl;
			if (this->caseStmt[i]->val) this->caseStmt[i]->val->__show(fout);
			if (this->caseStmt[i]->stmt) this->caseStmt[i]->stmt->__show(fout);
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

void WhileAst::__show(std::fstream& fout) {
	fout << "WHILE AST-cond:" << std::endl;
	this->cond->__show(fout);
	fout << "WHILE AST-stmt:" << std::endl;
	this->stmt->__show(fout);
	fout << "WHILE END" << std::endl;
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

void RepeatAst::__show(std::fstream& fout) {
	fout << "RepeatAST-exp:" << std::endl;
	this->exp->__show(fout);
	fout << "RepeatAST-stmtList:" << std::endl;
	for (auto it = this->stmtList.begin(); it != this->stmtList.end();it++) {
		(*it)->__show(fout);
	}
	fout << "Repeat END" << std::endl;
}

RepeatAst::~RepeatAst() {
	;
}

ForAst::ForAst(SymbolAst* id_, ExprAst* init_, bool dir_, ExprAst* fin_, StmtAst* stmt_) :
	loop_var(id_), init(init_), dir_init_to_end(dir_), end(fin_), stmt(stmt_) {
	this->nodeType = AST_FOR;
}

void ForAst::__show(std::fstream& fout) {
	fout << "For AST-loopvar:" << std::endl;
	this->loop_var->__show(fout);
	fout << "For AST_INIT:" << std::endl;
	this->init->__show(fout);
	fout << "For AST_END:" << std::endl;
	this->end->__show(fout);
	fout << "For-DIR:" << dir_init_to_end << std::endl;
	fout << "For-stmt:" << std::endl;
	this->stmt->__show(fout);
	fout << "For END" << std::endl;
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

void GotoAst::__show(std::fstream& fout) {
	fout << "GOTO-AST:" << this->label << std::endl;
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

void CompoundAst::__show(std::fstream& fout) {
	fout << "Compound Ast:" << std::endl;
	for (auto it = this->stmtList.begin(); it != this->stmtList.end(); it++) {
		(*it)->__show(fout);
	}
	fout << "Compound Ast END" << std::endl;
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

void FuncAst::__show(std::fstream& fout) {
	fout << "FUNC-AST:NAME:" << this->funcName << std::endl;
	for (auto it = this->argList.begin(); it != this->argList.end(); it++) {
		fout << "ARG:" << std::endl;
		(*it)->__show(fout);
	}
}

FuncAst::~FuncAst() {
	;
}


DotAst::DotAst(VarAst* record_, std::string& field_) :
	record(record_), field(field_) {
	this->nodeType = AST_DOT;
}

void DotAst::__show(std::fstream& fout) {
	fout << "DOT AST-FIELD:" << this->field << std::endl;
	fout << "DOT AST-RECORD:";
	this->record->__show(fout);
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

void RecordDeclAst::__show(std::fstream& fout) {
	fout << "Record Decl Ast-Name:" << name << std::endl;
	for (auto it = this->members.begin(); it != this->members.end(); it++) {
		fout << "Record Decl Ast-Member:";
		(it->first)->__show(fout);
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

void FuncDeclAst::__show(std::fstream& fout) {
	fout << "Func Decl Ast-name:" << this->name << std::endl;
	fout << "Para:" << std::endl;
	for (int i = 0; i < args.size(); i++) {
		if (this->is_var[i]) fout << "Var:"<<this->args[i].second;
		else fout << "non-Var:"<<this->args[i].second;
		this->args[i].first->__show(fout);
	}
	this->body->__show(fout);
}

FuncDeclAst::~FuncDeclAst() {
	;
}

ConstDeclAst::ConstDeclAst(std::string& name_, SPL_TYPE type_, valueUnion const_value_):
	name(name_), type(type_), const_value(const_value_){
	this->nodeType = AST_CONST_DECL;
}

void ConstDeclAst::__show(std::fstream& fout) {
	fout << "Const Decl Ast-name:" << this->name << "\t type:" << this->type << std::endl;
}

ConstDeclAst::~ConstDeclAst() {
	;
}

SimpleVarDeclAst::SimpleVarDeclAst(const std::string& name_, TypeAst* type_) :
	name(name_), type(type_){
	this->nodeType = AST_SIMPLE_VAR_DECL;
}

void SimpleVarDeclAst::__show(std::fstream& fout) {

	fout << "Simple var Decl Ast-name:" << this->name << std::endl;
	fout << "Simple var Decl Ast-type:";
	this->type->__show(fout);
}

SimpleVarDeclAst::~SimpleVarDeclAst() { ; }

TypeDeclAst::TypeDeclAst(std::string& name_, TypeAst* type_):
	name(name_), type(type_) {
	this->nodeType = AST_TYPE_DECL;
}

void TypeDeclAst::__show(std::fstream& fout) {
	fout << "Type Decl Ast-name:" << this->name << std::endl;
	fout << "Type Decl Ast-type:";
	this->type->__show(fout);
}

TypeDeclAst::~TypeDeclAst() { ; }

ArrayDeclAst::ArrayDeclAst(std::string& name_, ConstAst* minIndex_, ConstAst* maxIndex_, TypeAst* type_) :
	name(name_), minIndex(minIndex_), maxIndex(maxIndex_), type(type_) {
	this->nodeType = AST_ARRAY_DECL;
}

void ArrayDeclAst::__show(std::fstream& fout) {
	fout << "Array Decl Ast-name:" << this->name << "\t minIndex:"<< "\t maxIndex:" << std::endl;
	fout << "Array Decl Ast-type:";
	this->type->__show(fout);
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

void SysFuncAst::__show(std::fstream& fout) {
	fout << "SYSFUNC ID:" << this->id << std::endl;
	for (auto it = this->argList.begin(); it != this->argList.end(); it++) {
		fout << "ARG:" << std::endl;
		(*it)->__show(fout);
	}
}

SysFuncAst::~SysFuncAst() {
	;
}
