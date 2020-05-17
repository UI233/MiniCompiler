#pragma once
#include "Ast.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"

// declaration of writeln and write
llvm::Function* createWritePrototype(llvm::LLVMContext& context, llvm::Module* mod);

// declaration of read
llvm::Function* createReadPrototype(llvm::LLVMContext& context, llvm::Module* mod);

// 
std::vector<llvm::Value*> getWriteArgument(llvm::LLVMContext& context, const std::vector<llvm::Value*>& args, llvm::Module& mod, bool writeln);

std::vector<llvm::Value*> getReadArgument(llvm::LLVMContext& context, const std::vector<llvm::Value*>& args, const std::vector<llvm::Type*>& args_type, llvm::Module& mod);