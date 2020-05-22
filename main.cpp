#include <iostream>
#include <stdio.h>
#include <fstream>
#include "CodeGen.h"
#include "parser.hpp"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

extern FILE *yyin;
//extern SPL::Ast *program_const_part;
//extern SPL::Ast *program_type_part;
//extern SPL::Ast *program_var_part;
//extern SPL::Ast *program_routine_body;
extern SPL::CompoundAst *program;

//void installSystemFunctions(Program *root);

extern int yyparse();

std::ofstream astOut;

int main(int argc, char **argv) {
    std::string sourcePath;
	std::string sourceFile;
	// read lib function
	yyin = fopen("lib.spl", "r");
    yyparse();
	fclose(yyin);
    SPL::Ast* libroot = program;
	// read program
	if (argc > 1) {
		sourceFile = sourcePath + argv[1];
		yyin = fopen(sourceFile.c_str(), "r");
	}
	else
		yyin = stdin;
    yyparse();
	fclose(yyin);
    SPL::Ast* root = program;
	std::fstream fout;
	fout.open("output",std::ios::out);
	root->__show(fout);
	/* Create the top level interpreter function to call as entry */
	genIR(libroot, root, llvm::errs());
/*
	root = program_type_part;
	root->__show(fout);
	root = program_var_part;
	root->__show(fout);
	root = program_routine_body;
	root->__show(fout);
*/
//	fout.close();
    return 0;
}
