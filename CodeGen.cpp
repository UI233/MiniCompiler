#include "CodeGen.h"
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
#include "llvm/Support/Host.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "SymbolTable.h"
#include "SystemFunc.h"

llvm::LLVMContext context;
llvm::IRBuilder<> builder(context);
llvm::Module module("MainModule", context);
int errorno = 0;

namespace SPL 
{
constexpr int ERRORNO = -2184744;
SymbolTable st;

void logError(const std::string& err, int lineno) 
{
    errorno = 1;
    std::cerr << err << (lineno == -1 ? "" : "at line" + std::to_string(lineno)) << std::endl;
}

int getIntTyWidth(llvm::Type* ty) 
{
   return ty->isIntegerTy() ? ty->getScalarSizeInBits() : -1;
}

int ConstAst::genIndex() const
{
    return value.valInt;
}

int SymbolAst::genIndex() const
{
    auto constant = st.getConstant(name);
    if (!constant.first)
    {
        logError("Index is not constant", lineNo);
        return ERRORNO;
    }

    return constant.second.valInt;
}

Ast::SPL_IR ConstAst::codeGen() const
{
    switch(type)
    {
    case BOOL:
        return llvm::ConstantInt::get(context, llvm::APInt(1, value.valBool, false));
        break;
    case CHAR:
        return llvm::ConstantInt::get(context, llvm::APInt(8, value.valChar, true));
        break;
	case INT:
        return llvm::ConstantInt::get(context, llvm::APInt(32, value.valInt, true));
        break;
	case REAL:
        return llvm::ConstantFP::get(context, llvm::APFloat(value.valDouble));
        break;
    default:
        logError("Non-constant type with constant", lineNo);
        return nullptr;
    }
}

Ast::SPL_IR MathAst::codeGen() const
{
    static auto isSupportedType = [](llvm::Type* ty)
    {
        return ty ? ty->isDoubleTy() || ty->isIntegerTy() : true;
    };
    llvm::Value* lhs = nullptr, *rhs = nullptr;
    llvm::Type* lhs_ty = nullptr, *rhs_ty= nullptr;
    bool is_fp = true;
    if (lchild)
    {
        lhs = lchild->codeGen();
        lhs_ty = lhs->getType();
        is_fp &= lhs_ty->isDoubleTy();
    }
    if (rchild)
    {
        rhs = rchild->codeGen();
        rhs_ty = rhs->getType();
        is_fp &= rhs_ty->isDoubleTy();
    }
    if ((!lchild && !rchild) || (!rchild && op != OP_NG && op != OP_NOT))
    {
        logError("Invalid number of operand for operator", lineNo);
        return nullptr;
    }
    if (!isSupportedType(lhs_ty) || !isSupportedType(rhs_ty))
    {
        logError("Invalid type of operand for operator", lineNo);
        return nullptr;
    }
    if (lhs_ty != rhs_ty && rhs_ty)
    {
        if (lhs_ty->isDoubleTy()) 
            rhs = builder.CreateSIToFP(rhs, lhs_ty, "rcasttmp");
        else if (rhs_ty->isDoubleTy())
            lhs = builder.CreateSIToFP(lhs, rhs_ty, "lcasttmp");
        else if(lhs_ty->isIntegerTy() && rhs_ty->isIntegerTy())
        {
            int lhs_width = getIntTyWidth(lhs_ty), rhs_width = getIntTyWidth(rhs_ty);
            if (lhs_width < 0 || rhs_width < 0)
                throw "wrong type";
            if (lhs_width > rhs_width)
                rhs = builder.CreateSExt(rhs, lhs_ty, "");
            else if (rhs_width > lhs_width)
                lhs = builder.CreateSExt(lhs, rhs->getType(), "");
            else 
                throw "same type";
        }
        else 
        {
            throw "unsupported branch";
        }
        lhs_ty = lhs->getType();
        rhs_ty = rhs->getType();
        is_fp = lhs_ty->isDoubleTy() && rhs_ty->isDoubleTy() ;
    }
    
    switch(op)
    {
    case OP_ADD:
        return is_fp ? builder.CreateFAdd(lhs, rhs, "faddtmp") : builder.CreateAdd(lhs, rhs, "addtmp");
    case OP_SUB:
        return is_fp ? builder.CreateFSub(lhs, rhs, "fsubtmp") : builder.CreateSub(lhs, rhs, "subtmp");
    case OP_DIV:
        return is_fp ? builder.CreateFDiv(lhs, rhs, "fdivtmp") : builder.CreateSDiv(lhs, rhs, "divtmp");
    case OP_MUL:
        return is_fp ? builder.CreateFMul(lhs, rhs, "fmultmp") : builder.CreateMul(lhs, rhs, "multmp");
    case OP_MOD:
        return is_fp ? builder.CreateFRem(lhs, rhs, "fmodtmp") : builder.CreateSRem(lhs, rhs, "remtmp");
    case OP_GE:
        return is_fp ? builder.CreateFCmpOGE(lhs, rhs, "fgetmp") : builder.CreateICmpSGE(lhs, rhs, "remtmp");
    case OP_GT:
        return is_fp ? builder.CreateFCmpOGT(lhs, rhs, "fgttmp") : builder.CreateICmpSGT(lhs, rhs, "gttmp");
    case OP_LE:
        return is_fp ? builder.CreateFCmpOLE(lhs, rhs, "fletmp") : builder.CreateICmpSLE(lhs, rhs, "letmp");
    case OP_LT:
        return is_fp ? builder.CreateFCmpOLT(lhs, rhs, "flttmp") : builder.CreateICmpSLT(lhs, rhs, "lttmp");
    case OP_EQ:
        return is_fp ? builder.CreateFCmpOEQ(lhs, rhs, "feqtmp") : builder.CreateICmpEQ(lhs, rhs, "eqtmp");
    case OP_NE:
        return is_fp ? builder.CreateFCmpONE(lhs, rhs, "funetmp") : builder.CreateICmpNE(lhs, rhs, "remtmp");
    case OP_OR:
        return is_fp ? logError("Unsupported and operator for floating point", lineNo), nullptr : builder.CreateOr(lhs, rhs, "ortmp");
    case OP_AND:
        return is_fp ? logError("Unsupported and operator for floating point", lineNo), nullptr : builder.CreateAnd(lhs, rhs, "ortmp");
    case OP_NOT:
        return is_fp ? logError("Unsupported and operator for floating point", lineNo), nullptr : builder.CreateNot(lhs, "nottmp");
    case OP_NG:
        return is_fp ? builder.CreateFNeg(lhs, "fnegtmp") : builder.CreateNeg(lhs, "negtmp");
    default:
        return nullptr;
    }
}

Ast::SPL_IR SymbolAst::genPtr() const
{
    auto ptr =  st.getVarSymbol(name);
    if (!ptr)
        logError("Undefined Variable", lineNo);
    return ptr;
}

Ast::SPL_IR SymbolAst::codeGen() const
{
    if (st.getSymbolType(name, false) & SymbolTable::CONST)
        return st.getConstant(name).first;
    else {
        auto ptr = genPtr();
        if (ptr == nullptr)
        {
            logError("Not a variable", lineNo);
            return nullptr;
        }
        return builder.CreateLoad(ptr);
    }
}

Ast::SPL_IR ArrayAst::genPtr() const
{
    llvm::Value* array = sym->genPtr();
    if (!array->getType()->getContainedType(0)->isArrayTy())
    {
        logError("Variable is not array type", lineNo);
        return nullptr;
    }
    llvm::Value* index = exp_index->codeGen();
    llvm::Value* offset = st.getArrayOffset(array->getType()->getContainedType(0));
    llvm::Value* offset_index = builder.CreateSub(index, offset);
    if (!index->getType()->isIntegerTy())
    {
        logError("Non-integer index", lineNo);
        return nullptr;
    }
    auto zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
    auto element_ptr = builder.CreateInBoundsGEP(array, {zero, offset_index});
    return element_ptr;
}

Ast::SPL_IR ArrayAst::codeGen() const
{
    auto ptr = genPtr();
    if (ptr == nullptr)
    {
        logError("Not a variable", lineNo);
        return nullptr;
    }

    return builder.CreateLoad(ptr);
}

Ast::SPL_IR DotAst::genPtr() const
{
    auto record_ptr = record->genPtr();
    auto struct_mem = st.getRecordMap(record_ptr->getType()->getContainedType(0));
    if (!struct_mem.count(field))
    {
        logError("Record doesn't have field " + field, lineNo);
        return nullptr;
    }
    auto zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
    auto offset = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), struct_mem[field]);
    return builder.CreateInBoundsGEP(record_ptr, {zero, offset});
}

Ast::SPL_IR DotAst::codeGen() const
{
    auto ptr = genPtr();
    if (ptr == nullptr)
    {
        logError("Not a variable", lineNo);
        return nullptr;
    }

    return builder.CreateLoad(ptr);
}

Ast::SPL_IR FuncAst::codeGen() const
{
    int lineNo = SPL::ExprAst::lineNo;
    auto func = st.getFuncSymbol(funcName);
    if (!std::get<0>(func))
    {
        logError("Undefined function", lineNo);
        return nullptr;
    }
    if (funcName == "writeln" || funcName == "write")
    {
        std::get<1>(func) = std::vector<bool>(argList.size(), false);
    }
    if (funcName == "read")
        std::get<1>(func) = std::vector<bool>(argList.size(), true);
    if (argList.size() != std::get<1>(func).size())
    {
        logError("Wrong number of parameters passed", lineNo);
        return nullptr;
    }
    int idx = 0;
    std::vector<llvm::Value*> argsv;
    std::vector<llvm::Type*> arg_raw_type;
    if (funcName == "writeln" || funcName == "write")
    {
        bool writeln = funcName == "writeln";
        for (auto& arg: argList)
            argsv.push_back(arg->codeGen());
        argsv = getWriteArgument(context, argsv, module, writeln);
    }
    else if (funcName == "read")
    {
        for (auto& arg: argList)
        {
            VarAst* arg_ptr = dynamic_cast<VarAst*>(arg.get());
            if (!arg_ptr)
            {
                logError("Right value cannot be refered", lineNo);
                return nullptr;
            }
            auto ptr = arg_ptr->genPtr();
            argsv.push_back(ptr);
            arg_raw_type.push_back(ptr->getType()->getContainedType(0));
        }
        argsv = getReadArgument(context, argsv, arg_raw_type, module);
    }
    else
        for (auto& arg: std::get<0>(func)->args())
        {
            if (idx == std::get<1>(func).size())
            {
                auto additional_info = st.genParamType(std::get<2>(func));
                auto str = builder.CreateAlloca(additional_info.struct_ty);
                auto zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
                int idx = 0;
                for (auto& var_name: additional_info.var_name)
                {
                    auto index = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), idx);
                    auto var_ptr = builder.CreateInBoundsGEP(str, {zero, index});
                    if (!st.hasShadowedVar(var_name, std::get<2>(func) + 1))
                    {
                        auto var = st.getVarSymbol(var_name);
                        builder.CreateStore(var, var_ptr);
                    }
                    ++idx;
                }

                for (auto& var_name: additional_info.constant_name)
                {
                    auto index = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), idx);
                    auto var_ptr = builder.CreateInBoundsGEP(str, {zero, index});
                    if (!st.hasShadowedVar(var_name, std::get<2>(func) + 1))
                    {
                        auto var = st.getConstant(var_name).first;
                        builder.CreateStore(var, var_ptr);
                    }
                    ++idx;
                }
                argsv.push_back(str);
            }
            else {
                bool is_var = std::get<1>(func)[idx];
                if (is_var)
                {
                    auto var_ptr = dynamic_cast<VarAst*>(argList[idx].get());
                    if (!var_ptr)
                    {
                        logError("Right value cannot be refered", lineNo);
                        return nullptr;
                    }
                    argsv.push_back(var_ptr->genPtr());
                }
                else
                    argsv.push_back(argList[idx]->codeGen());
                if (!argsv.back())
                    return nullptr;
                if (argsv.back()->getType() != arg.getType())
                {
                    logError("Parameter's type unmatched", lineNo);
                    return nullptr;
                }
            }
            ++idx;
        }
    return builder.CreateCall(std::get<0>(func), argsv);
}

Ast::SPL_IR AssignAst::codeGen() const
{
    auto var_ptr = lhs -> genPtr();
    auto value = rhs->codeGen();
    if (var_ptr == nullptr || value == nullptr)
        return nullptr;
    if (!dynamic_cast<DotAst*>(lhs.get()) && !dynamic_cast<SymbolAst*>(lhs.get()) && !dynamic_cast<ArrayAst*>(lhs.get()))
    {
        logError("Right value cannot be assigned", lineNo);
        return nullptr;
    }
    auto var_ty = var_ptr->getType()->getContainedType(0);
    auto value_ty = value->getType();
    if (value_ty->isIntegerTy() && var_ty->isIntegerTy()) 
        value = builder.CreateSExtOrTrunc(value, var_ptr->getType()->getContainedType(0));
    else if (value_ty->isDoubleTy() && var_ty->isIntegerTy())
        value = builder.CreateFPToSI(value, var_ty);
    else if (value_ty->isIntegerTy() && var_ty->isDoubleTy())
        value = builder.CreateSIToFP(value, var_ty);
    if (var_ptr->getType()->getContainedType(0) != value->getType())
    {
        logError("Type unmatched", lineNo);
        return nullptr;
    }
    return builder.CreateStore(value, var_ptr);
}

llvm::Type* SimpleTypeAst::genType() const
{
    auto struct_type = st.getType(name);
    if (struct_type.type)
        return struct_type.type;
    if (name == "boolean")
        return llvm::Type::getInt1Ty(context);
    if (name == "integer")
        return llvm::Type::getInt32Ty(context);
    if (name == "char")
        return llvm::Type::getInt8Ty(context);
    if (name == "real")
        return llvm::Type::getDoubleTy(context);
    logError("Undefined type", lineNo);
    return nullptr;
}

Ast::SPL_IR SimpleVarDeclAst::codeGen() const
{
    auto var_t = this->type->genType();
    if (!var_t)
        return nullptr;
    if (st.hasName(name, true))
    {
        logError("Redefinition of variable", lineNo);
        return nullptr;
    }

    auto var = builder.CreateAlloca(var_t);
    // auto type_record = st.getType(type->getName());

    // if (type_record.is_array) {
    //     auto min_const = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), type_record.min_index);
    //     st.insertArray(name, var, min_const);
    // }
    // else
    st.insertVar(name, var);
    return nullptr;
}

llvm::Value* FuncDeclAst::codeGen() const
{
    auto beforebb = builder.GetInsertBlock();
    if (st.hasName(name))
    {
        logError("Name collision", lineNo);
        return nullptr;
    }
    // generate the prototype of function
    std::vector<llvm::Type*> arg_tys;
    auto additional_info = st.genParamType();
    int idx = 0;
    for (auto& arg: args)
    {
        auto arg_ty = arg.first->genType();
        if (!arg_ty)
        {
            logError("Undefined type", lineNo);
            return nullptr;
        }
        if (is_var[idx++])
            arg_ty = arg_ty->getPointerTo();
        arg_tys.push_back(arg_ty);
    }
    if (additional_info.struct_ty)
        arg_tys.push_back(additional_info.struct_ty->getPointerTo());
    auto ret_ty = ret_type ==nullptr ? llvm::Type::getVoidTy(context) :ret_type->genType();
    if (!ret_ty)
    {
        logError("Undefined type", lineNo);
        return nullptr;
    }
    auto func_ty = llvm::FunctionType::get(ret_ty, arg_tys, false);
    auto func = llvm::Function::Create(func_ty, llvm::Function::ExternalLinkage, name, &module);
    idx = 0;
    for (auto& arg: func->args())
        if (idx == is_var.size())
            arg.setName("0father_var");
        else
            arg.setName(args[idx++].second);
    // parameter pass of function    
    auto scope_num = st.getScopeNum();
    st.insertFunction(name, func, is_var, scope_num);
    st.pushScope();
    st.insertFunction(name, func, is_var, scope_num);
    auto entrybb = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entrybb);
    idx = 0;
    for (auto& arg: func->args())
    {
        // bool is_array = st.getType(args[idx].first->getName()).is_array;
        if (arg.getName() == "0father_var")
        {
            auto zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
            int idx = 0;
            for (auto& var_name: additional_info.var_name) 
            {
                auto index = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), idx);
                auto var_ptr = builder.CreateInBoundsGEP(&arg, {zero, index});
                auto var = builder.CreateLoad(var_ptr);
                st.insertVar(var_name, var, true);
                ++idx;
            }

            for (int i = 0; i < additional_info.constant_name.size(); ++i, ++idx)
            {
                auto index = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), idx);
                auto var_ptr = builder.CreateInBoundsGEP(&arg, {zero, index});
                auto var = builder.CreateLoad(var_ptr);
                st.insertConstant(additional_info.constant_name[i], var, additional_info.constant_value[i], true);
            }
        }
        else {
            if (is_var[idx])
            {
                st.insertVar(arg.getName(), &arg);
            }
            else 
            {
                auto tmp_ptr = builder.CreateAlloca(arg.getType());
                builder.CreateStore(&arg, tmp_ptr);
                st.insertVar(arg.getName(), tmp_ptr);
            }
        }
        ++idx;
    }
    llvm::Value* ret_ptr = nullptr;
    if (!ret_ty->isVoidTy())
    {
        ret_ptr = builder.CreateAlloca(ret_ty, nullptr, "ret_var");
        st.insertVar("0" + name, ret_ptr);
    }
    // generate body of function
    body->codeGen();
    if (!ret_ty->isVoidTy())
    {
        auto ret_v = builder.CreateLoad(ret_ptr);
        builder.CreateRet(ret_v);
    }
    else
        builder.CreateRetVoid();
    llvm::verifyFunction(*func);
    // remove local variable from symbol table
    st.popScope();
    builder.SetInsertPoint(beforebb);
    return nullptr;
}

Ast::SPL_IR RecordDeclAst::codeGen() const
{
    auto type = genType();
    std::vector<std::string> member_name;
    for (auto& member: members)
        member_name.push_back(member.second);
    st.insertRecord(type, member_name);
    return nullptr;
}

llvm::StructType* RecordDeclAst::genType() const
{
    if (st.hasName(name))
    {
        logError("Collision of name", lineNo);
        return nullptr;
    }
    std::vector<llvm::Type*> member_ty;
    for (auto& member: members)
    {
        member_ty.push_back(member.first->genType());
        if (!member_ty.back())
        {
            logError("Undefined type", lineNo);
            return nullptr;
        }
    }
    return llvm::StructType::create(context, member_ty);
}

Ast::SPL_IR ConstDeclAst::codeGen() const
{
    if (st.hasName(name))
    {
        logError("Redefinition of variable", lineNo);
        return nullptr;
    }

    switch(type)
    {
    case REAL:
        st.insertConstant(name, llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), const_value.valDouble), const_value);
        return nullptr;
    case BOOL:
        st.insertConstant(name, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), const_value.valBool), const_value);
        return nullptr;
    case CHAR:
        st.insertConstant(name, llvm::ConstantInt::get(llvm::Type::getInt8Ty(context), const_value.valChar), const_value);
        return nullptr;
    case INT:
        st.insertConstant(name, llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), const_value.valInt), const_value);
        return nullptr;
    default:
        std::cerr << INT << std::endl;
        std::cerr << type << std::endl;
        logError("This type cannot be constant", lineNo);
        return nullptr;
    }
}

Ast::SPL_IR ArrayDeclAst::codeGen() const
{
    if (st.hasName(name))
    {
        logError("Redefinition of variable", lineNo);
        return nullptr;
    }
    
    int min_value = minIndex->genIndex();
    int max_value = maxIndex->genIndex();
    int length = max_value - min_value + 1;
    if (min_value == ERRORNO || max_value == ERRORNO)
        return nullptr;
    if (length <= 0)
    {
        logError("Length of array cannot be negative", lineNo);
        return nullptr;
    }
    auto ele_ty = type->genType();
    if (!ele_ty)
        return nullptr;
    auto arr_ty = llvm::ArrayType::get(ele_ty, length);
    auto arr_ptr = builder.CreateAlloca(arr_ty);
    auto min_const = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), min_value);
    st.insertVar(name, arr_ptr);
    if (!st.insertArray(arr_ty, min_const))
        logError(name + " has already been defined", lineNo);
    return nullptr;
}

// llvm::Type* ArrayDeclAst::genType() const
// {
//     int min_value = minIndex->genIndex();
//     int max_value = maxIndex->genIndex();
//     int length = max_value - min_value + 1;
//     return llvm::ArrayType::get(type->codeGen(), length);
// }

Ast::SPL_IR LabelAst::codeGen() const
{
    if (st.hasName(std::to_string(label)))
    {
        logError("Collision of name", lineNo);
        return nullptr;
    }
    auto thefunc = builder.GetInsertBlock()->getParent();
    auto labelbb = llvm::BasicBlock::Create(context, "labelbb", thefunc);
    auto afterbb = llvm::BasicBlock::Create(context, "afterbb");
    builder.CreateBr(labelbb);
    builder.SetInsertPoint(labelbb);
    nonLabelAst->codeGen();
    builder.CreateBr(afterbb);
    thefunc->getBasicBlockList().push_back(afterbb);
    builder.SetInsertPoint(afterbb);
    st.insertLabel(std::to_string(label), labelbb);
    return nullptr;
}

Ast::SPL_IR IfAst::codeGen() const
{
    auto condv = cond->codeGen();
    if (!condv)
        return nullptr;
    if (!condv->getType()->isIntegerTy(1))
    {
        logError("Condition expression should be boolean", lineNo);
        return nullptr;
    }
    auto thefunc = builder.GetInsertBlock()->getParent();
    auto thenbb = llvm::BasicBlock::Create(context, "thenbb", thefunc);
    auto elsebb = llvm::BasicBlock::Create(context, "elsebb");
    auto mergebb = llvm::BasicBlock::Create(context, "mergebb");
    builder.CreateCondBr(condv, thenbb, elsebb);
    builder.SetInsertPoint(thenbb);
    ifStmt->codeGen();
    builder.CreateBr(mergebb);
    thefunc->getBasicBlockList().push_back(elsebb);
    builder.SetInsertPoint(elsebb);
    if (elseStmt)
        elseStmt->codeGen();
    builder.CreateBr(mergebb);
    thefunc->getBasicBlockList().push_back(mergebb);
    builder.SetInsertPoint(mergebb);
    return nullptr;
}

Ast::SPL_IR CaseAst::codeGen() const
{
    auto thefunc = builder.GetInsertBlock()->getParent();
    auto initbb = llvm::BasicBlock::Create(context, "initbb", thefunc);
    builder.CreateBr(initbb);
    builder.SetInsertPoint(initbb);
    auto condv = cond->codeGen();
    if (!condv)
        return nullptr;
    if (!condv->getType()->isIntegerTy())
    {
        logError("Case expression should be integer type", lineNo);
        return nullptr;
    }
    std::vector<llvm::BasicBlock*> entries;
    for (int i = 0; i < caseStmt.size(); ++i)
        entries.push_back(llvm::BasicBlock::Create(context, "case" + std::to_string(i)));
    auto afterbb = llvm::BasicBlock::Create(context, "afterbb");
    builder.CreateBr(entries.size() == 0 ? afterbb : entries[0]);
    for (int i = 0; i < entries.size(); ++i)
    {
        thefunc->getBasicBlockList().push_back(entries[i]);
        builder.SetInsertPoint(entries[i]);
        auto val = caseStmt[i]->val->codeGen();
        auto bodybb = llvm::BasicBlock::Create(context, "casebody" + std::to_string(i));
        auto eqcond = builder.CreateICmpEQ(condv, val);
        builder.CreateCondBr(eqcond, bodybb, i == entries.size() - 1 ? afterbb : entries[i + 1]);
        thefunc->getBasicBlockList().push_back(bodybb);
        builder.SetInsertPoint(bodybb);
        caseStmt[i]->stmt->codeGen();
        builder.CreateBr(afterbb);
    }
    thefunc->getBasicBlockList().push_back(afterbb);
    builder.SetInsertPoint(afterbb);
    return nullptr;
}

Ast::SPL_IR ForAst::codeGen() const
{
    auto thefunc = builder.GetInsertBlock()->getParent();
    auto initbb = llvm::BasicBlock::Create(context, "initbb", thefunc);
    auto bodybb = llvm::BasicBlock::Create(context, "bodybb");
    auto calcbb = llvm::BasicBlock::Create(context, "calcbb");
    auto afterbb = llvm::BasicBlock::Create(context, "afterbb");
    builder.CreateBr(initbb);
    builder.SetInsertPoint(initbb);
    auto loopv_ptr = loop_var->genPtr();
    auto loopv = init->codeGen();
    if (!loopv->getType()->isIntegerTy() || !loopv_ptr->getType()->getContainedType(0)->isIntegerTy())
    {
        logError("Loop variable should be integer", lineNo);
        return nullptr;
    }
    auto loop_var = builder.CreateStore(loopv, loopv_ptr);
    auto endv = end->codeGen();
    if (!endv)
        return nullptr;
    llvm::Value* condv = nullptr;
    if (dir_init_to_end)
        condv = builder.CreateICmpSGT(loopv, endv);
    else 
        condv = builder.CreateICmpSLT(loopv, endv);
    builder.CreateCondBr(condv, afterbb, bodybb);
    thefunc->getBasicBlockList().push_back(bodybb);
    builder.SetInsertPoint(bodybb);
    stmt->codeGen();
    loopv = builder.CreateLoad(loopv_ptr);
    condv = builder.CreateICmpEQ(loopv, endv);
    builder.CreateCondBr(condv, afterbb, calcbb);
    thefunc->getBasicBlockList().push_back(calcbb);
    builder.SetInsertPoint(calcbb);
    loopv = builder.CreateLoad(loopv_ptr);
    if (dir_init_to_end)
        loopv = builder.CreateAdd(loopv, llvm::ConstantInt::get(loopv->getType(), 1));
    else 
        loopv = builder.CreateSub(loopv, llvm::ConstantInt::get(loopv->getType(), 1));
    builder.CreateStore(loopv, loopv_ptr);
    builder.CreateBr(bodybb);
    thefunc->getBasicBlockList().push_back(afterbb);
    builder.SetInsertPoint(afterbb);
    return nullptr;
}

Ast::SPL_IR WhileAst::codeGen() const
{
    auto thefunc = builder.GetInsertBlock()->getParent();
    auto entrybb = llvm::BasicBlock::Create(context, "entrybb", thefunc);
    auto bodybb = llvm::BasicBlock::Create(context, "bodybb");
    auto afterbb = llvm::BasicBlock::Create(context, "afterbb");
    builder.CreateBr(entrybb);
    builder.SetInsertPoint(entrybb);
    auto condv = cond->codeGen();
    if (!condv->getType()->isIntegerTy(1))
    {
        logError("Conditional expression should be boolean", lineNo);
        return nullptr;
    }
    builder.CreateCondBr(condv, bodybb, afterbb);
    thefunc->getBasicBlockList().push_back(bodybb);
    builder.SetInsertPoint(bodybb);
    stmt->codeGen();
    builder.CreateBr(entrybb);
    thefunc->getBasicBlockList().push_back(afterbb);
    builder.SetInsertPoint(afterbb);
    return nullptr;
}

Ast::SPL_IR RepeatAst::codeGen() const
{
    auto thefunc = builder.GetInsertBlock()->getParent();
    auto bodybb = llvm::BasicBlock::Create(context, "bodybb", thefunc);
    auto exitbb = llvm::BasicBlock::Create(context, "exitbb");
    auto afterbb = llvm::BasicBlock::Create(context, "afterbb");
    builder.CreateBr(bodybb);
    builder.SetInsertPoint(bodybb);
    for (auto& stmt: stmtList)
        stmt->codeGen();
    builder.CreateBr(exitbb);
    thefunc->getBasicBlockList().push_back(exitbb);
    builder.SetInsertPoint(exitbb);
    auto condv = exp->codeGen();
    if (!condv->getType()->isIntegerTy(1))
    {
        logError("Conditional expression should be boolean", lineNo);
        return nullptr;
    }
    builder.CreateCondBr(condv, afterbb, bodybb);
    thefunc->getBasicBlockList().push_back(afterbb);
    builder.SetInsertPoint(afterbb);
    return nullptr;
}

Ast::SPL_IR GotoAst::codeGen() const
{
    
    if (!st.hasName(std::to_string(label), false))
    {
        logError("Undefined label", lineNo);
        return nullptr;
    }
    auto gotobb = st.getLabelSymbol(std::to_string(label));
    if (gotobb->getParent() != builder.GetInsertBlock()->getParent())
    {
        logError("Cannot goto another label in other function", lineNo);
        return nullptr;
    }
    builder.CreateBr(gotobb);
    return nullptr;
}

llvm::Value* TypeDeclAst::codeGen() const
{
    if (st.hasName(name))
    {
        logError("Type has been defined", lineNo);
        return nullptr;
    }
    // if (simple_t.get())
    // {
    //     if (simple_t->codeGen()) {
    //         st.insertType(name, st.getType(simple_t->getName()));
    //     }
    //     return nullptr;
    // }
    // else if (arr_t.get())
    // {
    //     auto array_type = arr_t->genType();
    //     st.insertType(name, SymbolTable::NamedType(array_type, arr_t->getIndex()));
    // }
    // else {
    //     auto struct_t = record_t->genType();
    //     st.insertType(name, SymbolTable::NamedType(struct_t));
    // }
    st.insertType(name, type->genType());
    return nullptr;
}

llvm::Type* ArrayTypeAst::genType() const
{
    int min_value = minIndex->genIndex();
    int max_value = maxIndex->genIndex();
    int length = max_value - min_value + 1;
    if (min_value == ERRORNO || max_value == ERRORNO)
        return nullptr;
    if (length <= 0)
    {
        logError("Length of array cannot be negative", lineNo);
        return nullptr;
    }
    auto ele_ty = memberType->genType();
    if (!ele_ty)
        return nullptr;
    auto min_const = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), min_value);
    auto arr_ty  = llvm::ArrayType::get(ele_ty, length);
    st.insertArray(arr_ty, min_const);
    return arr_ty;
} 

llvm::Type* RecordTypeAst::genType() const
{
    std::vector<llvm::Type*> member_ty;
    std::vector<std::string> member_name;
    for (auto& member: members)
    {
        member_ty.push_back(member.first->genType());
        member_name.push_back(member.second);
        if (!member_ty.back())
        {
            logError("Undefined type", lineNo);
            return nullptr;
        }
    }
    auto struct_t = llvm::StructType::create(context, member_ty);
    st.insertRecord(struct_t, member_name);
    return struct_t;
}

Ast::SPL_IR CompoundAst::codeGen() const
{
    for (auto& stmt: stmtList)
        stmt->codeGen();
    return nullptr;
}

void initEnv()
{
    auto read_func = createReadPrototype(context, &module);
    auto write_func = createWritePrototype(context, &module);
    // add sys_func to symbol table
    st.insertFunction("read", read_func, std::vector<bool>(), -2);
    st.insertFunction("write", write_func, std::vector<bool>(), -2);
    st.insertFunction("writeln", write_func, std::vector<bool>(), -2);
    // add built-in type
    st.insertType("boolean", llvm::Type::getInt1Ty(context));
    st.insertType("integer", llvm::Type::getInt32Ty(context));
    st.insertType("char", llvm::Type::getInt8Ty(context));
    st.insertType("real", llvm::Type::getDoubleTy(context));
}

void genIR(Ast* lib_func, SPL::Ast* root, std::string output_file, SPL_OUTPUT_TYPE output_flag)
{
    initEnv();
    if (lib_func)
        lib_func->codeGen();
    std::vector<llvm::Type *> argTypes;
    llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), makeArrayRef(argTypes), false);
    llvm::Function *mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, "main", &module);
    llvm::BasicBlock *bblock = llvm::BasicBlock::Create(context, "entry", mainFunction, nullptr);
    builder.SetInsertPoint(bblock);
    root->codeGen(); 
    builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0));
    std::error_code EC;
    llvm::raw_fd_ostream dest(output_file, EC, llvm::sys::fs::OpenFlags::F_None);
    if (errorno == 0)
    {
        if (output_flag == IR)
            module.print(dest, nullptr);
        else {
            // Initialize the target registry etc.
            llvm::InitializeAllTargetInfos();
            llvm::InitializeAllTargets();
            llvm::InitializeAllTargetMCs();
            llvm::InitializeAllAsmParsers();
            llvm::InitializeAllAsmPrinters();
            auto TargetTriple = output_flag == MIPS ? "mips-apple-darwin17.6.0" : llvm::sys::getDefaultTargetTriple();
            module.setTargetTriple(TargetTriple);

            std::string Error;
            auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

            // Print an error and exit if we couldn't find the requested target.
            // This generally occurs if we've forgotten to initialise the
            // TargetRegistry or we have a bogus target triple.
            if (!Target) {
                llvm::errs() << Error;
                return ;
            }

            auto CPU = output_flag == MIPS ? "mips32" : "generic";
            auto Features = "";

            llvm::TargetOptions opt;
            auto RM = llvm::Optional<llvm::Reloc::Model>();
            auto TheTargetMachine =
                Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
            module.setDataLayout(TheTargetMachine->createDataLayout());
            if (EC) {
                llvm::errs() << "Could not open file: " << EC.message();
                return ;
            }

            llvm::legacy::PassManager pass;
            // generate object file or assembly
            auto FileType = output_flag == OBJ ? llvm::TargetMachine::CGFT_ObjectFile : llvm::TargetMachine::CGFT_AssemblyFile;

            if (TheTargetMachine->addPassesToEmitFile(pass, dest, FileType, true, nullptr)) {
                llvm::errs() << "TheTargetMachine can't emit a file of this type";
                return ;
            }

            pass.run(module);
            dest.flush();
        }
    }
}

}
