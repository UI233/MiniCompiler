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
	std::string now_dir(argv[0]);
	now_dir = now_dir.substr(0, now_dir.find_last_of('/'));
	std::string lib_func = now_dir + "/lib.spl";
	// read lib function
	yyin = fopen(lib_func.c_str(), "r");
	if (!yyin)
	{
		std::cerr << "fatal error: cannot find lib functions at " << lib_func << std::endl;
		return 1;
	}
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
		else if (argv[i] == std::string("-mips"))
			output_flag = MIPS;
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
		case MIPS:
		case ASSEMBLY:
			output_file = sourceFile + ".s";
			break;

		default:
			break;
		}
	}
	yyin = fopen(sourceFile.c_str(), "r");
	if (!yyin)
	{
		std::cerr << "fatal error: cannot open input file" << std::endl;
		return 1;
	}
    yyparse();
	fclose(yyin);
    SPL::Ast* root = program;
	std::fstream fout;
	fout.open("output",std::ios::out);
	if (root)
		genIR(libroot, root, output_file, output_flag);
	fout.close();

	std::cout<<"output AST begin"<<std::endl;
	fout.open("ast.dot",std::ios::out);
	fout << "digraph ast{" << std::endl;
	root->__show(fout, -1);
	fout << "}" << std::endl;
	fout.close();
	std::cout<<"end AST begin"<<std::endl;

    return 0;
}
