#include "Ast.h"
#include <fstream>

int main() {
	std::fstream fout;
	fout.open("output.txt", std::ios::out);
/*
AST For below program:

PROGRAM 1 ;
CONST A = 1; C = 100;
TYPE SHORT = integer;

FUNCTION sum ( a:int ; b:int ) : int ;
	VAR i:SHORT;ans:integer;
	BEGIN
	ans = 0;
	FOR i = a to b DO
		ans = ans + i;
	END

BEGIN
	A = sum( A , C );
END
*/
	std::string A = std::string("A");
	std::string C = std::string("C");
	std::string a = std::string("a");
	std::string b = std::string("b");
	std::string i = std::string("i");
	std::string ans = std::string("ans");
	std::string intname = std::string("integer");
	std::string typeName_ = std::string("SHORT");
	std::string funcName = std::string("sum");
	SPL::valueUnion val1, val2;
	val1.valInt = 1;
	val2.valInt = 100;
	SPL::ConstDeclAst* L21 = new SPL::ConstDeclAst(A, INT, val1);
	SPL::ConstDeclAst* L22 = new SPL::ConstDeclAst(C, INT, val2);
	SPL::TypeAst* L30 = new SPL::TypeAst(intname);
	SPL::TypeDeclAst* L3 = new SPL::TypeDeclAst(typeName_, L30);

	SPL::TypeAst* L50a = new SPL::TypeAst(intname);
	SPL::TypeAst* L50b = new SPL::TypeAst(intname);
	std::vector<std::pair<SPL::TypeAst*, std::string>> args;
	args.push_back(std::pair<SPL::TypeAst*, std::string>(L50a, a));
	args.push_back(std::pair<SPL::TypeAst*, std::string>(L50b, b));
	std::vector<bool> is_var;
	is_var.push_back(false);
	is_var.push_back(false);
	SPL::TypeAst* L50r = new SPL::TypeAst(intname);

	SPL::SimpleVarDeclAst* L61 = new SPL::SimpleVarDeclAst(ans, new SPL::TypeAst(intname));
	SPL::SimpleVarDeclAst* L62 = new SPL::SimpleVarDeclAst(i, new SPL::TypeAst(typeName_));
	SPL::AssignAst* L7 = new SPL::AssignAst(new SPL::SymbolAst(ans), new SPL::ConstAst(0));
	SPL::MathAst* L90 = new SPL::MathAst(OP_ADD, new SPL::SymbolAst(ans), new SPL::SymbolAst(i));
	SPL::AssignAst* L9 = new SPL::AssignAst(new SPL::SymbolAst(ans), L90);
	SPL::ForAst* forstmt = new SPL::ForAst(new SPL::SymbolAst(i), new SPL::SymbolAst(a), true, new SPL::SymbolAst(b), L9);
	std::vector<SPL::StmtAst*> stmtList;
	stmtList.push_back(L61); stmtList.push_back(L62); stmtList.push_back(L7); stmtList.push_back(forstmt);
	SPL::CompoundAst* body = new SPL::CompoundAst(stmtList);
	SPL::FuncDeclAst* L5 = new SPL::FuncDeclAst(funcName,body,args, is_var, L50r);

	std::vector<SPL::ExprAst*> arglist;
	arglist.push_back(new SPL::SymbolAst(A)); arglist.push_back(new SPL::SymbolAst(C));

	SPL::FuncAst* L140 = new SPL::FuncAst(true, funcName, arglist);
	SPL::AssignAst* L14 = new SPL::AssignAst(new SPL::SymbolAst(A), L140);

	std::vector<SPL::StmtAst*> programVec;
	programVec.push_back(L21);
	programVec.push_back(L22);
	programVec.push_back(L3);
	programVec.push_back(L5);
	programVec.push_back(L140);

	SPL::CompoundAst* program = new SPL::CompoundAst(programVec);

	program->__show(fout);
	fout.close();
	return 0;
}