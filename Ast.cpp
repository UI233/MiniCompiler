#include "Ast.h"

using namespace SPL;

LabelAst::LabelAst(int label_, Ast* nonLabelAst_) :
	label(label_), nonLabelAst(nonLabelAst_) {
	this->nodeType = AST_LABEL;
}

void LabelAst::__show(std::fstream& fout) {
	fout << "LabelAst:" << std::endl << "label:" << label << std::endl << "nonLabel Ast:" << std::endl;
	nonLabelAst->__show(fout);
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
	fout << "MathAst: \nOperator:" << op << std::endl;
	fout << "Left:";
	if (lchild) lchild->__show(fout);
	fout << "Right:";
	if (rchild) rchild->__show(fout);
}

MathAst::~MathAst() {
	;
}

ConstAst::ConstAst(char x) :
	type(CHAR) {
	value.valChar = x;
	this->nodeType = AST_CONST_DECL;
}
ConstAst::ConstAst(int x) :
	type(INT) {
	value.valInt = x;
	this->nodeType = AST_CONST_DECL;
}
ConstAst::ConstAst(double x):
	type(REAL) {
	value.valDouble = x;
	this->nodeType = AST_CONST_DECL;
}
ConstAst::ConstAst(bool x) :
	type(BOOL) {
	value.valBool = x;
	this->nodeType = AST_CONST_DECL;
}
ConstAst::ConstAst(std::string x) :
	type(STRING) {
	value.valString = &x;
	this->nodeType = AST_CONST_DECL;
}

void ConstAst::__show(std::fstream& fout) {
	fout << "ConstDeclAst:";
	switch (type) {
	case STRING:fout << "STRING:" << *(value.valString) << std::endl; break;
	case INT:fout << "INT:" << value.valInt << std::endl; break;
	case REAL:fout << "REAL:" << value.valDouble << std::endl; break;
	case BOOL:fout << "BOOL:" << value.valBool << std::endl; break;
	case CHAR:fout << "CHAR:" << value.valChar << std::endl; break;
	}
}

ConstAst::~ConstAst() {
	;
}

SymbolAst::SymbolAst(const std::string& name_) :
	name(name_) {
	this->nodeType = AST_SYMBOL;
}

void SymbolAst::__show(std::fstream& fout) {
	fout << "SymbolAst:" << name << std::endl;
}

SymbolAst::~SymbolAst() {
	;
}

ArrayAst::ArrayAst(SymbolAst* sym_, ExprAst* exp_) :
	sym(sym_), exp_index(exp_) {
	this->nodeType = AST_ARRAY;
}

void ArrayAst::__show(std::fstream& fout) {
	fout << "ArrayAst:" << std::endl;
	fout << "ArrayNameAst:";
	sym->__show(fout);
	fout << "IndexExpAst:";
	exp_index->__show(fout);
}

ArrayAst::~ArrayAst() {
	;
}

AssignAst::AssignAst(VarAst* lhs_, ExprAst* rhs_) :
	lhs(lhs_), rhs(rhs_) {
	this->StmtAst::nodeType = this->ExprAst::nodeType = AST_ASSIGN;

}

void AssignAst::__show(std::fstream& fout) {
	fout << "AssignAst:" << std::endl;
	fout << "LhsVarAst:";
	lhs->__show(fout);
	fout << "RhsExprAst:";
	rhs->__show(fout);
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
	cond->__show(fout);
	fout << "doIfAst:";
	ifStmt->__show(fout);
	fout << "ElseAst:";
	elseStmt->__show(fout);
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
		caseStmt.push_back(it);
	}
}

void CaseAst::__show(std::fstream& fout) {
	fout << "CASE AST:" << std::endl;
	for (auto it : caseStmt) {
		fout << "CASE:" << it->val << std::endl;
		it->stmt->__show(fout);
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
	cond->__show(fout);
	fout << "WHILE AST-stmt:" << std::endl;
	stmt->__show(fout);
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
		stmtList.push_back(std::move(t));
	}
}

void RepeatAst::__show(std::fstream& fout) {
	fout << "RepeatAST-exp:" << std::endl;
	exp->__show(fout);
	fout << "RepeatAST-stmtList:" << std::endl;
	for (auto it = stmtList.begin(); it != stmtList.end();it++) {
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
	loop_var->__show(fout);
	fout << "For AST_INIT:" << std::endl;
	init->__show(fout);
	fout << "For AST_END:" << std::endl;
	end->__show(fout);
	fout << "For-DIR:" << dir_init_to_end << std::endl;
	fout << "For-stmt:" << std::endl;
	stmt->__show(fout);
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

CompoundAst::CompoundAst(const std::vector<StmtAst*>& stmtList_) {
	this->nodeType = AST_COMPOUND;
	for (auto it : stmtList_) {
		std::unique_ptr<StmtAst> t(it);
		stmtList.push_back(std::move(t));
	}
}

void CompoundAst::__show(std::fstream& fout) {
	fout << "Compound Ast:" << std::endl;
	for (auto it = stmtList.begin(); it != stmtList.end(); it++) {
		(*it)->__show(fout);
	}
	fout << "Compound Ast END" << std::endl;
}

CompoundAst::~CompoundAst() {
	;
}

FuncAst::FuncAst(bool isProc_, std::string& funcName_, std::vector<ExprAst*> argList_) :
	isProc(isProc_), funcName(funcName_) {
	this->StmtAst::nodeType = this->ExprAst::nodeType = AST_FUNC;
	for (auto it : argList_) {
		std::unique_ptr<ExprAst> t(it);
		argList.push_back(std::move(t));
	}
}

FuncAst::FuncAst() :
	isProc(false), funcName(), argList() {
	;
}

void FuncAst::__show(std::fstream& fout) {
	fout << "FUNC-AST:NAME:" << funcName << std::endl;
	for (auto it = argList.begin(); it != argList.end(); it++) {
		fout << "ARG:" << std::endl;
		(*it)->__show(fout);
	}
}

FuncAst::~FuncAst() {
	;
}

TypeAst::TypeAst(const std::string& t_name, bool isArray_, TypeAst* ArrayMemType_, int arrayLen_) :
	name(t_name), isArray(isArray_), ArrayMemType(ArrayMemType_), arrayLen(arrayLen_) {
	this->nodeType = AST_TYPE;
}

void TypeAst::__show(std::fstream& fout) {
	fout << "Type AST-name:" << name << std::endl;
	if (isArray) {
		fout << "Is Array Of:" << arrayLen << std::endl;
		ArrayMemType->__show(fout);
	}
}

TypeAst::~TypeAst() {
	;
}

DotAst::DotAst(SymbolAst* record_, std::string& field_) :
	record(record_), field(field_) {
	this->nodeType = AST_DOT;
}

void DotAst::__show(std::fstream& fout) {
	fout << "DOT AST-FIELD:" << field << std::endl;
	fout << "DOT AST-RECORD:";
	record->__show(fout);
}

DotAst::~DotAst() {
	;
}

RecordDeclAst::RecordDeclAst(std::string t_name, std::vector<std::pair<TypeAst*, std::string>> t_members) :
	name(t_name) {
	this->nodeType = AST_RECORD_DECL;
	for (auto it : t_members) {
		std::unique_ptr<TypeAst> t(it.first);
		members.push_back(std::pair<std::unique_ptr<TypeAst>, std::string>(std::move(t), it.second));
	}
}

void RecordDeclAst::__show(std::fstream& fout) {
	fout << "Record Decl Ast-Name:" << name << std::endl;
	for (auto it = members.begin(); it != members.end(); it++) {
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
		args.push_back(arg_t(std::move(t), it.second));
	}
}

void FuncDeclAst::__show(std::fstream& fout) {
	fout << "Func Decl Ast-name:" << name << std::endl;
	fout << "Para:" << std::endl;
	for (int i = 0; i < args.size(); i++) {
		if (is_var[i]) fout << "Var:"<<args[i].second;
		else fout << "non-Var:"<<args[i].second;
		args[i].first->__show(fout);
	}
}

FuncDeclAst::~FuncDeclAst() {
	;
}

ConstDeclAst::ConstDeclAst(std::string& name_, SPL_TYPE type_, valueUnion const_value_):
	name(name_), type(type_), const_value(const_value_){
	this->nodeType = AST_CONST_DECL;
}

void ConstDeclAst::__show(std::fstream& fout) {
	fout << "Const Decl Ast-name:" << name << "\t type:" << type << std::endl;
}

ConstDeclAst::~ConstDeclAst() {
	;
}

SimpleVarDeclAst::SimpleVarDeclAst(std::string& name_, TypeAst* type_) :
	name(name_), type(type_){
	this->nodeType = AST_SIMPLE_VAR_DECL;
}

void SimpleVarDeclAst::__show(std::fstream& fout) {
	fout << "Simple var Decl Ast-name:" << name << std::endl;
	fout << "Simple var Decl Ast-type:";
	type->__show(fout);
}

SimpleVarDeclAst::~SimpleVarDeclAst() { ; }

TypeDeclAst::TypeDeclAst(std::string& name_, TypeAst* type_):
	name(name_),type(type_){
	this->nodeType = AST_TYPE_DECL;
}

void TypeDeclAst::__show(std::fstream& fout) {
	fout << "Type Decl Ast-name:" << name << std::endl;
	fout << "Type Decl Ast-type:";
	type->__show(fout);
}

TypeDeclAst::~TypeDeclAst() { ; }

ArrayDeclAst::ArrayDeclAst(std::string& name_, ConstAst* minIndex_, ConstAst* maxIndex_, TypeAst* type_) :
	name(name_), minIndex(minIndex_), maxIndex(maxIndex_), type(type_) {
	this->nodeType = AST_ARRAY_DECL;
}

void ArrayDeclAst::__show(std::fstream& fout) {
	fout << "Array Decl Ast-name:" << name << "\t minIndex:" << minIndex << "\t maxIndex:" << maxIndex << std::endl;
	fout << "Array Decl Ast-type:";
	type->__show(fout);
}

ArrayDeclAst::~ArrayDeclAst() {
	;
}

SysFuncAst::SysFuncAst(SYS_FUNC_ID sysFuncId_, std::vector<ExprAst*>& argList_) :
	id(sysFuncId_) {
	this->FuncAst::ExprAst::nodeType = this->FuncAst::StmtAst::nodeType = AST_SYSFUNC;
	for (auto it : argList_) {
		std::unique_ptr<ExprAst> t(it);
		argList.push_back(std::move(t));
	}
}

void SysFuncAst::__show(std::fstream& fout) {
	fout << "SYSFUNC ID:" << id << std::endl;
	for (auto it = argList.begin(); it != argList.end(); it++) {
		fout << "ARG:" << std::endl;
		(*it)->__show(fout);
	}
}

SysFuncAst::~SysFuncAst() {
	;
}