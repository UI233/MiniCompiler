#pragma once
#include "Ast.h"
#include "llvm/Support/raw_ostream.h"

namespace SPL{
void genIR(Ast* lib_func, SPL::Ast* root, std::string output_file, SPL_OUTPUT_TYPE output_flag);
}