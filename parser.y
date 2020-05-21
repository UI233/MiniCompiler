%{
    #include "Ast.h"
    #include <fstream>
    SPL::CompoundAst* program;
    extern int yylineno;
    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %s\n at line:%d\n", s, yylineno); }


    //typedef struct para para;
    std::string true_string("true");
    std::string false_string("false");
    std::string maxint_string("maxint");
    std::string dotdot_string("..");
    std::string minus_string("-");
    std::string array_string("array:");
    int INT_MAX_SPL = 2147483647;
    
%}

%union{
	SPL::Ast *ast;
	SPL::ExprAst* exprast;
	SPL::IndexAst* indexast;
	SPL::MathAst* mathast;
	SPL::ConstAst* constast;
	SPL::SymbolAst* symbolast;
	SPL::CompoundAst* compoundast;
	SPL::TypeAst* typeast;
	SPL::SimpleTypeAst* simpletypeast;
	SPL::ArrayTypeAst* arraytypeast;
	SPL::RecordTypeAst* recordtypeast;
	SPL::TypeDeclAst* typedeclast;
	SPL::SimpleVarDeclAst* simplevardeclast;
	SPL::FuncDeclAst* funcdeclast;
	SPL::StmtAst* stmtast;
	SPL::AssignAst* assignast;
	SPL::IfAst* ifast;
	SPL::RepeatAst* repeatast;
	SPL::WhileAst* whileast;
	SPL::ForAst* forast;
	SPL::CaseUnit* caseunit;
	SPL::CaseAst* caseast;
	SPL::ParaDecl* paradecl;
	SPL::GotoAst* gotoast;

	std::vector<SPL::FuncDeclAst*>* vecfuncdeclastPtr;
	std::vector<struct para>* vecparaPtr;
	std::vector<std::string> * vecstrPtr;
	std::vector<SPL::StmtAst*>* vecstmtastPtr;
	std::vector<SPL::CaseUnit*>* veccaseunitPtr;
	std::pair<SPL::TypeAst*, std::vector<std::string> >* recordunit;
	std::string* stringPtr;
	std::vector<SPL::ExprAst*>* vecexprastPtr;
	int valInt;
	bool valbool;
};

%token <stringPtr> TOKEN_SYS_CONST TOKEN_SYS_FUNCTION TOKEN_SYS_PROCEDURE TOKEN_SYS_TYPE TOKEN_READ
%token <stringPtr> TOKEN_INTEGER_LITERAL TOKEN_REAL_LITERAL TOKEN_CHAR_LITERAL
%token <stringPtr> TOKEN_ID


%token <token> TOKEN_LP TOKEN_RP TOKEN_LB TOKEN_RB
%token <token> TOKEN_DOT TOKEN_DOTDOT TOKEN_COMMA TOKEN_SEMI TOKEN_COLON
%token <token> TOKEN_ADD TOKEN_SUB TOKEN_MUL TOKEN_DIV TOKEN_MOD
%token <token> TOKEN_LT TOKEN_LE TOKEN_GT TOKEN_GE TOKEN_EQ TOKEN_NE
%token <token> TOKEN_ASSIGN
%token <token> TOKEN_NOT TOKEN_AND TOKEN_OR
%token <token> TOKEN_ARRAY
%token <token> TOKEN_BEGIN
%token <token> TOKEN_CASE TOKEN_CONST
%token <token> TOKEN_DO TOKEN_DOWNTO
%token <token> TOKEN_ELSE TOKEN_END
%token <token> TOKEN_FOR TOKEN_FUNCTION
%token <token> TOKEN_GOTO
%token <token> TOKEN_IF TOKEN_IN
%token <token> TOKEN_OF
%token <token> TOKEN_PROGRAM TOKEN_PROCEDURE TOKEN_PACKED
%token <token> TOKEN_RECORD
%token <token> TOKEN_REPEAT
%token <token> TOKEN_SET
%token <token> TOKEN_THEN TOKEN_TO TOKEN_TYPE
%token <token> TOKEN_UNTIL
%token <token> TOKEN_VAR
%token <token> TOKEN_WHILE
%token <token> TOKEN_WITH





%type <compoundast> const_part
%type <compoundast> const_expr_list
%type <constast> const_ast
%type <compoundast> type_part
%type <compoundast> type_decl_list
%type <typedeclast> type_defination
%type <typeast> type_decl
%type <simpletypeast> simple_type_decl
%type <arraytypeast> array_type_decl
%type <recordtypeast> record_type_decl
%type <recordtypeast> field_decl_list
%type <recordunit> field_decl
%type <vecstrPtr> name_list
%type <compoundast> var_part
%type <compoundast> var_decl_list
%type <compoundast> var_decl
%type <vecstmtastPtr> stmt_list
%type <stmtast> stmt
%type <compoundast> routine_body
%type <compoundast> compound_stmt
%type <stmtast> non_label_stmt
%type <assignast> assign_stmt
%type <ifast> if_stmt
%type <stmtast> else_clause
%type <repeatast> repeat_stmt
%type <whileast> while_stmt
%type <forast> for_stmt
%type <valbool> direction
%type <exprast> expression
%type <exprast> expr
%type <exprast> term
%type <exprast> factor
%type <caseast> case_stmt
%type <veccaseunitPtr> case_expr_list
%type <caseunit> case_expr
%type <compoundast> routine
%type <compoundast> sub_routine
%type <compoundast> routine_head
%type <funcdeclast> function_decl
%type <funcdeclast> procedure_decl
%type <compoundast> routine_part
%type <paradecl> parameters
%type <paradecl> para_decl_list
%type <paradecl> para_type_list
%type <vecstrPtr> var_para_list
%type <vecstrPtr> val_para_list
%type <gotoast> goto_stmt
%type <vecexprastPtr> args_list
%type <compoundast> program


%start program

%%

program : program_head routine TOKEN_DOT {
	$$ = $<compoundast>2;
}

program_head : TOKEN_PROGRAM TOKEN_ID TOKEN_SEMI {
	;
}

routine : routine_head routine_body {
//TODO
	$$ = $<compoundast>1;
	$$ -> merge($<compoundast>2);
	program = $$;
	//program = $$;
}

sub_routine: routine_head routine_body {
	//$$ = new SPL::RoutineAst($<routineheadast>1, $<compoundast>2);
	$$ = $<compoundast>1;
	$$ -> merge($<compoundast>2);
}

routine_head: const_part type_part var_part routine_part{
	$$ = $<compoundast>1;
	if ($$==nullptr) $$ = new SPL::CompoundAst(std::vector<SPL::StmtAst*>());
	$$ -> merge($<compoundast>2);
	$$ -> merge($<compoundast>3);
	$$ -> merge($<compoundast>4);
}

const_part: TOKEN_CONST const_expr_list {
	$$ = $<compoundast>2;
}
| {$$ = nullptr;}

const_expr_list:const_expr_list TOKEN_ID TOKEN_EQ const_ast TOKEN_SEMI {
	SPL::ConstDeclAst* t = new SPL::ConstDeclAst(*$<stringPtr>2, $<constast>4->getType(), $<constast>4->getValue());
	$$ = $<compoundast>1;
	$$->addStmt(t);
}
| TOKEN_ID TOKEN_EQ const_ast TOKEN_SEMI {
	SPL::ConstDeclAst* t = new SPL::ConstDeclAst(*$<stringPtr>1, $<constast>3->getType(), $<constast>3->getValue());
	std::vector<SPL::StmtAst*> vect;
	vect.push_back(t);
	$$ = new SPL::CompoundAst(vect);
}

const_ast: TOKEN_INTEGER_LITERAL {
	std::string* t = $<stringPtr>1;
	$$ = new SPL::ConstAst(std::stoi(*t));

}
| TOKEN_REAL_LITERAL {
	std::string* t = $<stringPtr>1;
	$$ = new SPL::ConstAst(std::stod(*t));
}
| TOKEN_CHAR_LITERAL {
	std::string* t = $<stringPtr>1;
	$$ = new SPL::ConstAst((*t)[1]);
}
| TOKEN_SYS_CONST {
	std::string* t = $<stringPtr>1;
	if (*t == maxint_string)  $$ = new SPL::ConstAst(INT_MAX_SPL);
	else if (*t == true_string) $$ = new SPL::ConstAst(true);
	else if (*t == false_string) $$ = new SPL::ConstAst(false);
}

type_part: TOKEN_TYPE type_decl_list {
	$$ = $<compoundast>2;
}
| {$$ = nullptr; }

type_decl_list: type_decl_list type_defination {
	$$ = $<compoundast>1;
	$$->addStmt($<typedeclast>2);
}
| type_defination {
	std::vector<SPL::StmtAst*> vect;
	vect.push_back($<typedeclast>1);
	$$ = new SPL::CompoundAst(vect);
}

type_defination: TOKEN_ID TOKEN_EQ type_decl TOKEN_SEMI {
	$$ = new SPL::TypeDeclAst(*($<stringPtr>1), $<typeast>3);
}

type_decl: simple_type_decl {
	$$ = $<simpletypeast>1;
}
| array_type_decl {
	$$ = $<arraytypeast>1;
}
| record_type_decl {
	$$ = $<recordtypeast>1;
}


simple_type_decl: TOKEN_SYS_TYPE {
	std::string t = *($<stringPtr>1);
	$$ = new SPL::SimpleTypeAst(t);
}
| TOKEN_ID {
	$$ = new SPL::SimpleTypeAst(*($<stringPtr>1));
}
| const_ast TOKEN_DOTDOT const_ast {
	$$ = new SPL::SimpleTypeAst(std::to_string(($<constast>1)->getValue().valInt)+dotdot_string+std::to_string(($<constast>3)->getValue().valInt));
}
| TOKEN_SUB const_ast TOKEN_DOTDOT const_ast {
	$$ = new SPL::SimpleTypeAst(minus_string+std::to_string(($<constast>2)->getValue().valInt)+dotdot_string+std::to_string(($<constast>4)->getValue().valInt));
}
| TOKEN_SUB const_ast TOKEN_DOTDOT TOKEN_SUB const_ast {
	$$ = new SPL::SimpleTypeAst(minus_string+std::to_string(($<constast>2)->getValue().valInt)+dotdot_string+minus_string+std::to_string(($<constast>5)->getValue().valInt));
}
| TOKEN_ID TOKEN_DOTDOT TOKEN_ID {
	$$ = new SPL::SimpleTypeAst(*($<stringPtr>1)+dotdot_string+*($<stringPtr>3));
}

array_type_decl: TOKEN_ARRAY TOKEN_LB simple_type_decl TOKEN_RB TOKEN_OF type_decl {
	std::string str = ($<simpletypeast>3)->getName();
	int i=0;
	for ( ;i<str.length();i++) {
		if (str[i]=='.') break;
	}
	std::string minstr = str.substr(0,i);
	std::string maxstr = str.substr(i+2);
	SPL::IndexAst* minIndex_=nullptr;
	SPL::IndexAst* maxIndex_=nullptr;
	if ((minstr[0]<='z'&&minstr[0]>='a')||(minstr[0]<='Z'&&minstr[0]>='A')) {
		minIndex_ = new SPL::SymbolAst(minstr);
		maxIndex_ = new SPL::SymbolAst(maxstr);
	} else {
		minIndex_ = new SPL::ConstAst(std::stoi(minstr));
		maxIndex_ = new SPL::ConstAst(std::stoi(maxstr));
	}
	$$ = new SPL::ArrayTypeAst( $<typeast>6 , minIndex_, maxIndex_);
}

record_type_decl: TOKEN_RECORD field_decl_list TOKEN_END {
	$$ = $<recordtypeast>2;
}

field_decl_list: field_decl_list field_decl {
	$$ = $1;
	$$ -> addMember(*$<recordunit>2);
} | field_decl {
	$$ = new SPL::RecordTypeAst();
	$$ -> addMember(*$<recordunit>1);
}

field_decl: name_list TOKEN_COLON type_decl TOKEN_SEMI {
	$$ = new std::pair<SPL::TypeAst*, std::vector<std::string> > ($<typeast>3, *$<vecstrPtr>1);
}

name_list: name_list TOKEN_COMMA TOKEN_ID {
	$<vecstrPtr>1->push_back(*$<stringPtr>3);
	$$ = $<vecstrPtr>1;
} | TOKEN_ID {
	std::string t = std::string(*($<stringPtr>1));
	$$ = new std::vector<std::string> ();
	$$->push_back(t);
}


var_part: TOKEN_VAR var_decl_list {
	$$ = $<compoundast>2;
} | {$$ = nullptr;}

var_decl_list: var_decl_list var_decl {
	$$ = $1;
	$$->merge($<compoundast>2);
} | var_decl {
	$$ = $<compoundast>1;
}

var_decl: name_list TOKEN_COLON type_decl TOKEN_SEMI {

	$$ = new SPL::CompoundAst(std::vector<SPL::StmtAst*> () );
	for (auto name: *($<vecstrPtr>1) ) {
		$$ -> addStmt(new SPL::SimpleVarDeclAst(name, $<typeast>3 ));
	}

}


routine_part: routine_part function_decl {
	$$ = $<compoundast>1;
	$$->addStmt($<funcdeclast>2);
} | function_decl {
	std::vector<SPL::StmtAst*> t;
	t.push_back($<funcdeclast>1);
	$$ = new SPL::CompoundAst(t);
} | {
	std::vector<SPL::StmtAst*> t;
	$$ = new SPL::CompoundAst(t);
} | routine_part procedure_decl {
	$$ = $<compoundast>1;
	$$->addStmt($<funcdeclast>2);
} | procedure_decl {
	std::vector<SPL::StmtAst*> t;
	t.push_back($<funcdeclast>1);
	$$ = new SPL::CompoundAst(t);
}


function_decl: TOKEN_FUNCTION TOKEN_ID parameters TOKEN_COLON simple_type_decl TOKEN_SEMI sub_routine TOKEN_SEMI {
	$$ = new SPL::FuncDeclAst(*($<stringPtr>2), $<compoundast>7, $<paradecl>3->args, $<paradecl>3->is_var, $<typeast>5 );
}

procedure_decl:TOKEN_PROCEDURE TOKEN_ID parameters TOKEN_SEMI sub_routine TOKEN_SEMI {
	$$ = new SPL::FuncDeclAst(*($<stringPtr>2), $<compoundast>5, $<paradecl>3->args, $<paradecl>3->is_var, nullptr );
}

parameters: TOKEN_LP para_decl_list TOKEN_RP {
	$$ = $<paradecl>2;
}

para_decl_list: para_decl_list TOKEN_SEMI para_type_list {
	$$ = $<paradecl>1;
	$$ -> addList($<paradecl>3);
} | para_type_list {
	$$ = new SPL::ParaDecl();
	$$ -> addList($<paradecl>1);
}

para_type_list: var_para_list TOKEN_COLON simple_type_decl {
	$$ = new SPL::ParaDecl();
	$$->addPara(*$<vecstrPtr>1, $<typeast>3, true);
}
| val_para_list TOKEN_COLON simple_type_decl {
	$$ = new SPL::ParaDecl();
	$$->addPara(*$<vecstrPtr>1, $<typeast>3, false);
}

var_para_list: TOKEN_VAR name_list {
	$$ = $<vecstrPtr>2;
}

val_para_list: name_list {
	$$ = $<vecstrPtr>1;
}


routine_body: compound_stmt{
	$$ = $<compoundast>1;
	//program_routine_body = $<compoundast>1;
}

compound_stmt: TOKEN_BEGIN stmt_list TOKEN_END {
	$$ = new SPL::CompoundAst(*$<vecstmtastPtr>2);
}

stmt_list: stmt_list stmt TOKEN_SEMI {
	if ($<vecstmtastPtr>1) {
		$$ = $<vecstmtastPtr>1;
		$$->push_back($<stmtast>2);
	} else {
		$$ = new std::vector<SPL::StmtAst*> ();
		$$->push_back($<stmtast>2);
	}
}
| {
	$$ = nullptr;
}

stmt: TOKEN_INTEGER_LITERAL TOKEN_COLON non_label_stmt {
	$$ = new SPL::LabelAst(std::stoi(*$<stringPtr>1), $<stmtast>3);
} | non_label_stmt {
	$$ = $<stmtast>1;
}

non_label_stmt:assign_stmt {
	$$ = $<assignast>1;
} | compound_stmt {
	$$ = $<compoundast>1;
} | if_stmt {
	$$ = $<ifast>1;
} | repeat_stmt {
	$$ = $<repeatast>1;
} | while_stmt {
	$$ = $<whileast>1;
} | for_stmt {
	$$ = $<forast>1;
} | case_stmt {
	$$ = $<caseast>1;
} | goto_stmt {
	$$ = $<gotoast>1;
} | TOKEN_ID TOKEN_LP args_list TOKEN_RP {
	$<stmtast>$ = new SPL::FuncAst(*$<stringPtr>1, *$<vecexprastPtr>3);
} | TOKEN_SYS_FUNCTION TOKEN_LP args_list TOKEN_RP {
	$<stmtast>$ = new SPL::FuncAst(*$<stringPtr>1, *$<vecexprastPtr>3);
}

assign_stmt: TOKEN_ID TOKEN_ASSIGN expression {
	$$ = new SPL::AssignAst(new SPL::SymbolAst(*($<stringPtr>1)), $<exprast>3 );
} | TOKEN_ID TOKEN_LB expression TOKEN_RB TOKEN_ASSIGN expression {
	$$ = new SPL::AssignAst(new SPL::ArrayAst(new SPL::SymbolAst(*($<stringPtr>1)), $<exprast>3), $<exprast>6 );	
} | TOKEN_ID TOKEN_DOT TOKEN_ID TOKEN_ASSIGN expression {
	$$ = new SPL::AssignAst(new SPL::DotAst(new SPL::SymbolAst(*($<stringPtr>1)), *($<stringPtr>3) ), $<exprast>5 );
}

if_stmt: TOKEN_IF expression TOKEN_THEN stmt else_clause {
	$$ = new SPL::IfAst($<exprast>2, $<stmtast>4, $<stmtast>5);
}

else_clause: TOKEN_ELSE stmt {
	$$ = $<stmtast>2;
} | {
	$$ = nullptr;
}

repeat_stmt: TOKEN_REPEAT stmt_list TOKEN_UNTIL expression {
	$$ = new SPL::RepeatAst(*$<vecstmtastPtr>2, $<exprast>4);
}

while_stmt: TOKEN_WHILE expression TOKEN_DO stmt {
	$$ = new SPL::WhileAst($<exprast>2,$<stmtast>4);
}

for_stmt: TOKEN_FOR TOKEN_ID TOKEN_ASSIGN expression direction expression TOKEN_DO stmt{
	$$ = new SPL::ForAst(new SPL::SymbolAst(*$<stringPtr>2),$<exprast>4,$<valbool>5,$<exprast>6,$<stmtast>8);
}

direction: TOKEN_TO {
	$$ = true;
} | TOKEN_DOWNTO {
	$$ = false;
}

case_stmt: TOKEN_CASE expression TOKEN_OF case_expr_list TOKEN_END {
	$$ = new SPL::CaseAst($<exprast>2, *$<veccaseunitPtr>4);
}

goto_stmt: TOKEN_GOTO TOKEN_INTEGER_LITERAL {
	$$ = new SPL::GotoAst(std::stoi(*$<stringPtr>1));
}

case_expr_list: case_expr_list case_expr {
	$$ = $1;
	$$->push_back($<caseunit>2);
} | case_expr {
	$$ = new std::vector<SPL::CaseUnit*>();
	$$->push_back($<caseunit>1);
}

case_expr: const_ast TOKEN_COLON stmt TOKEN_SEMI {
	$$ = new SPL::CaseUnit($<exprast>1, $<stmtast>3);
} | TOKEN_ID TOKEN_COLON stmt TOKEN_SEMI {
	$$ = new SPL::CaseUnit($<exprast>1, $<stmtast>3);
}

expression: expression TOKEN_GE expr {
	$$ = new SPL::MathAst(OP_GE,$<exprast>1,$<exprast>3);
} | expression TOKEN_GT expr {
	$$ = new SPL::MathAst(OP_GT,$<exprast>1,$<exprast>3);
} | expression TOKEN_LE expr {
	$$ = new SPL::MathAst(OP_LE,$<exprast>1,$<exprast>3);
} | expression TOKEN_LT expr {
	$$ = new SPL::MathAst(OP_LT,$<exprast>1,$<exprast>3);
} | expression TOKEN_EQ expr {
	$$ = new SPL::MathAst(OP_EQ,$<exprast>1,$<exprast>3);
} | expression TOKEN_NE expr {
	$$ = new SPL::MathAst(OP_NE,$<exprast>1,$<exprast>3);
} | expr {
	$$ = $<exprast>1;
}

expr: expr TOKEN_ADD term {
	$$ = new SPL::MathAst(OP_ADD,$<exprast>1, $<exprast>3);
} | expr TOKEN_SUB term {
	$$ = new SPL::MathAst(OP_SUB,$<exprast>1, $<exprast>3);
} | expr TOKEN_OR term {
	$$ = new SPL::MathAst(OP_OR,$<exprast>1, $<exprast>3);
} | term {
	$$ = $<exprast>1;
}

term: term TOKEN_MUL factor {
	$$ = new SPL::MathAst(OP_MUL, $<exprast>1, $<exprast>3);
} | term TOKEN_DIV factor {
	$$ = new SPL::MathAst(OP_DIV, $<exprast>1, $<exprast>3);
} | term TOKEN_MOD factor {
	$$ = new SPL::MathAst(OP_MOD, $<exprast>1, $<exprast>3);
} | term TOKEN_AND factor{
	$$ = new SPL::MathAst(OP_AND, $<exprast>1, $<exprast>3);
} | factor {
	$$ = $<exprast>1;
}

factor: const_ast {
	$<exprast>$ = $<constast>1;
} | TOKEN_ID {
	$<exprast>$ = new SPL::SymbolAst(*$<stringPtr>1);
} | TOKEN_SUB factor {
	$<exprast>$ = new SPL::MathAst(OP_NG,$<exprast>2, nullptr);
} | TOKEN_ID TOKEN_DOT TOKEN_ID {
	$<exprast>$ = new SPL::DotAst(new SPL::SymbolAst(*$<stringPtr>1), *$<stringPtr>2);
} | TOKEN_ID TOKEN_LB expression TOKEN_RB {
	$<exprast>$ = new SPL::ArrayAst(new SPL::SymbolAst(*$<stringPtr>1), $<exprast>3);
} | TOKEN_NOT factor {
	$<exprast>$ = new SPL::MathAst(OP_NOT,$<exprast>2, nullptr);
} | TOKEN_ID TOKEN_LP args_list TOKEN_RP {
	$<exprast>$ = new SPL::FuncAst(*$<stringPtr>1, *$<vecexprastPtr>3);
} | TOKEN_SYS_FUNCTION TOKEN_LP args_list TOKEN_RP {
	$<exprast>$ = new SPL::FuncAst(*$<stringPtr>1, *$<vecexprastPtr>3);
}

args_list: args_list TOKEN_COMMA expression {
	$$ = $<vecexprastPtr>1;
	$$ -> push_back($<exprast>3);
} | expression {
	$$ = new std::vector<SPL::ExprAst*> ();
	$$ -> push_back($<exprast>1);
} | {
	$$ = new std::vector<SPL::ExprAst*> ();
}



