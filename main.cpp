#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Ast.h"
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

extern llvm::LLVMContext context;
extern llvm::IRBuilder<> builder;
extern llvm::Module module;

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
	/* Create the top level interpreter function to call as entry */
	std::vector<llvm::Type *> argTypes;
	llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), makeArrayRef(argTypes),
														false);
	// change GlobalValue::InternalLinkage into ExternalLinkage
	llvm::Function *mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, "main", &module);
	llvm::BasicBlock *bblock = llvm::BasicBlock::Create(context, "entry", mainFunction, nullptr);
	builder.SetInsertPoint(bblock);
	root->codeGen(); 
	module.print(llvm::errs(), nullptr);
	builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0));
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
