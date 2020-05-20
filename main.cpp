#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Ast.h"
#include "parser.hpp"

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
    auto sourceFile = sourcePath + argv[1];
    std::cout << "input file: " << sourceFile << std::endl;
    yyin = fopen(sourceFile.c_str(), "r");
    yyparse();

    SPL::Ast* root = program;
	std::fstream fout;
	fout.open("output",std::ios::out);
	root->__show(fout);

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
