#include <iostream>
#include <stdio.h>
#include <fstream>
#include "CodeGen.h"
#include "parser.hpp"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

extern FILE *yyin;
extern SPL::CompoundAst *program;
extern int yylineno;
extern int yyparse();

int main(int argc, char **argv) {
	SPL_OUTPUT_TYPE output_flag = OBJ;
	std::string output_file;
    std::string sourcePath;
	std::string sourceFile;
	// read lib function
	yyin = fopen("lib.spl", "r");
    yyparse();
	fclose(yyin);
	yylineno = 1;
    SPL::Ast* libroot = program;
	// parse argument
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i] == std::string("-o"))
		{
			if (i + 1 < argc)
				output_file = argv[++i];
			else
			{
				std::cerr << "fatal error: output file not specified" << std::endl;
				return 1;
			}
		}	
		else if (argv[i] == std::string("-s"))
			output_flag = ASSEMBLY;
		else if (argv[i] == std::string("-ll"))
			output_flag = IR;
		else if (argv[i] == std::string("-c"))
			output_flag = OBJ;
		else
			sourceFile = sourcePath + argv[i];
	}
	if (argc <= 1) {
		std::cerr << "fatal error: no input files" << std::endl;
		return 1;
	}
	if (output_file == "")
	{
		switch (output_flag)
		{
		case OBJ:
			output_file = sourceFile + ".o";
			break;
		case IR:
			output_file = sourceFile + ".ll";
			break;
		case ASSEMBLY:
			output_file = sourceFile + ".s";
			break;
		default:
			break;
		}
	}
	yyin = fopen(sourceFile.c_str(), "r");
    yyparse();
	fclose(yyin);
    SPL::Ast* root = program;
	std::fstream fout;
	fout.open("output",std::ios::out);
	if (root)
		genIR(libroot, root, output_file, output_flag);
    return 0;
}
