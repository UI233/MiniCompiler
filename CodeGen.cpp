#include "llvm/IR/IRBuilder.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "Ast.h"
#include "SymbolTable.h"

namespace SPL 
{
static llvm::LLVMContext context;
static llvm::IRBuilder<> builder(context);
static llvm::Module module("MainModule", context);
static SymbolTable st;

void logError(const std::string& err) 
{
    std::cerr << err << std::endl;
}

int getIntTyWidth(llvm::Type* ty) 
{
    return ty->isIntegerTy(1) ? 1 : (
        ty->isIntegerTy(8) ? 8 :
        (ty->isIntegerTy(32) ? 32 : -1)
    );
}

ExprAst::SPL_IR ConstAst::codeGen() const
{
    switch(valueType)
    {
    BOOL:
        return llvm::ConstantInt::get(context, llvm::APInt(1, value.valBool, false));
        break;
    CHAR:
        return llvm::ConstantInt::get(context, llvm::APInt(8, value.valChar, true));
        break;
	INT:
        return llvm::ConstantInt::get(context, llvm::APInt(32, value.valInt, true));
        break;
	REAL:
        return llvm::ConstantFP::get(context, llvm::APFloat(value.valDouble));
        break;
    default:
        logError("Non-constant type with constant");
        return nullptr;
    }
}

ExprAst::SPL_IR MathAst::codeGen() const
{
    static auto isSupportedType = [](llvm::Type* ty)
    {
        return ty->isDoubleTy() || ty->isIntegerTy();
    };
    if (!lchild || !rchild) 
    {
        logError("Invalid number of operand for operator");
        return nullptr;
    }
    auto lhs = lchild->codeGen();
    auto rhs = rchild->codeGen();
    if (!lhs || !rhs)
        return nullptr;
    llvm::Type* lhs_ty = lhs->getType();
    auto rhs_ty = rhs->getType();
    if (!isSupportedType(lhs_ty) || !isSupportedType(rhs_ty))
    {
        logError("Invalid type of operand for operator");
        return nullptr;
    }
    if (lhs_ty != rhs_ty)
    {
        if (lhs_ty->isDoubleTy())
            rhs = builder.CreateFPCast(rhs, lhs_ty, "rcasttmp");
        else if (rhs_ty->isDoubleTy())
            lhs = builder.CreateFPCast(lhs, rhs_ty, "lcasttmp");
        else if(lhs_ty->isIntegerTy() && rhs_ty->isIntegerTy())
        {
            int lhs_width = getIntTyWidth(lhs_ty), rhs_width = getIntTyWidth(rhs_ty);
            if (lhs_width < 0 || rhs_width < 0)
                throw "wrong type";
            if (lhs_width > rhs_width)
                rhs = builder.CreateIntCast(rhs, lhs->getType(), true);
            else if (rhs_width > lhs_width)
                lhs = builder.CreateIntCast(lhs, rhs->getType(), true);
            else 
                throw "same type";
        }
        else 
        {
            throw "unsupported branch";
        }
    }
    bool is_fp = lhs_ty->isDoubleTy() && rhs_ty->isDoubleTy();
    bool is_boolean = getIntTyWidth(lhs_ty) == 1 && getIntTyWidth(rhs_ty) == 1;
    switch(op)
    {
    OP_ADD:
        return is_fp ? builder.CreateFAdd(lhs, rhs, "faddtmp") : builder.CreateAdd(lhs, rhs, "addtmp");
    OP_SUB:
        return is_fp ? builder.CreateFSub(lhs, rhs, "fsubtmp") : builder.CreateSub(lhs, rhs, "subtmp");
    OP_DIV:
        return is_fp ? builder.CreateFDiv(lhs, rhs, "fdivtmp") : builder.CreateSDiv(lhs, rhs, "divtmp");
    OP_MUL:
        return is_fp ? builder.CreateFMul(lhs, rhs, "fmultmp") : builder.CreateMul(lhs, rhs, "multmp");
    OP_MOD:
        return is_fp ? builder.CreateFRem(lhs, rhs, "fmodtmp") : builder.CreateSRem(lhs, rhs, "remtmp");
    OP_GE:
        return is_fp ? builder.CreateFRem(lhs, rhs, "fmodtmp") : builder.CreateSRem(lhs, rhs, "remtmp");
    OP_GT:
        return is_fp ? builder.CreateFCmpOGT(lhs, rhs, "fgttmp") : builder.CreateICmpSGT(lhs, rhs, "gttmp");
    OP_LE:
        return is_fp ? builder.CreateFCmpOLE(lhs, rhs, "fletmp") : builder.CreateICmpSLE(lhs, rhs, "letmp");
    OP_LT:
        return is_fp ? builder.CreateFCmpOLT(lhs, rhs, "flttmp") : builder.CreateICmpSLT(lhs, rhs, "lttmp");
    OP_EQUAL:
        return is_fp ? builder.CreateFCmpOEQ(lhs, rhs, "feqtmp") : builder.CreateICmpEQ(lhs, rhs, "eqtmp");
    OP_UNEQUAL:
        return is_fp ? builder.CreateFCmpONE(lhs, rhs, "funetmp") : builder.CreateICmpNE(lhs, rhs, "remtmp");
    OP_OR:
        return is_fp ? logError("Unsupported and operator for floating point"), nullptr : builder.CreateOr(lhs, rhs, "ortmp");
    OP_AND:
        return is_fp ? logError("Unsupported and operator for floating point"), nullptr : builder.CreateAnd(lhs, rhs, "ortmp");
    }
}

ExprAst::SPL_IR SymbolAst::genPtr() const
{
    return st.getVarSymbol(name);
}

ExprAst::SPL_IR SymbolAst::codeGen() const
{
    auto ptr = genPtr();
    if (ptr == nullptr)
    {
        logError("Not a variable");
        return nullptr;
    }

    return builder.CreateLoad(ptr);
}

ExprAst::SPL_IR ArrayAst::genPtr() const
{
    llvm::Value* array = st.getVarSymbol(arrayName);    
    if (!array->getType()->isArrayTy())
    {
        logError("Variable is not array type");
        return nullptr;
    }
    llvm::Value* index = exp_index->codeGen();
    llvm::Value* offset = st.getArraySymbol(arrayName);
    llvm::Value* offset_index = builder.CreateAdd(index, offset);
    if (!index->getType()->isIntegerTy())
    {
        logError("Non-integer index");
        return nullptr;
    }
    auto element_ptr = builder.CreateInBoundsGEP(array, offset_index);
    return element_ptr;
}

ExprAst::SPL_IR ArrayAst::codeGen() const
{
    auto ptr = genPtr();
    if (ptr == nullptr)
    {
        logError("Not a variable");
        return nullptr;
    }

    return builder.CreateLoad(ptr);
}

ExprAst::SPL_IR DotAst::genPtr() const
{
    auto record_ptr = record->genPtr();
    auto struct_mem = st.getRecordSymbol(record->codeGen()->getType()->getStructName()).second;
    if (!struct_mem.count(field))
    {
        logError("Record doesn't have field " + field);
        return nullptr;
    }
    return builder.CreateInBoundsGEP(record_ptr, llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), struct_mem[field]));
}

ExprAst::SPL_IR DotAst::codeGen() const
{
    auto ptr = genPtr();
    if (ptr == nullptr)
    {
        logError("Not a variable");
        return nullptr;
    }

    return builder.CreateLoad(ptr);
}

ExprAst::SPL_IR FuncAst::codeGen() const
{
    auto func = st.getFuncSymbol(funcName);
    if (argList.size() != func.second.size())
    {
        logError("Wrong number of parameters passed");
        return nullptr;
    }
    std::vector<llvm::Value*> argsv;
    int idx = 0;
    for (auto& arg: func.first->args())
    {
        bool is_var = func.second[idx++];
        if (is_var)
        {
            auto var_ptr = dynamic_cast<VarAst*>(argList[idx].get());
            if (!var_ptr)
            {
                logError("Right value cannot be refered");
                return nullptr;
            }
            argsv.push_back(var_ptr->genPtr());
        }
        else
            argsv.push_back(argList[idx]->codeGen());
        if (!argsv.back())
            return nullptr;
        ++idx;
    }

    return builder.CreateCall(func.first, argsv);
}

ExprAst::SPL_IR AssignAst::codeGen() const
{
    auto variable = lhs->codeGen();
    auto value = rhs->codeGen();
    if (variable == nullptr || value == nullptr)
        return nullptr;
    if (!dynamic_cast<DotAst*>(lhs.get()) && !dynamic_cast<SymbolAst*>(lhs.get()) && !dynamic_cast<ArrayAst*>(lhs.get()))
    {
        logError("Right value cannot be assigned");
        return nullptr;
    }
    if (variable->getType() != value->getType())
    {
        logError("Type unmatched");
        return nullptr;
    }
    
    auto var_ptr = lhs -> genPtr();
    return builder.CreateStore(value, var_ptr);
}


}