#pragma once
#include "Ast.h"
#include "llvm/Support/raw_ostream.h"

namespace SPL{
void genIR(Ast* lib_func, SPL::Ast* root, llvm::raw_ostream& out);
}