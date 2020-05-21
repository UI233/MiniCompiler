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
#include "SystemFunc.h"

llvm::LLVMContext context;
llvm::IRBuilder<> builder(context);
llvm::Module module("MainModule", context);
namespace SPL 
{
constexpr int ERRORNO = -2184744;
SymbolTable st;

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

int ConstAst::genIndex() const
{
    return value.valInt;
}

int SymbolAst::genIndex() const
{
    auto constant = st.getConstant(name);
    if (!constant.first)
    {
        logError("Index is not constant");
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
        logError("Non-constant type with constant");
        return nullptr;
    }
}

Ast::SPL_IR MathAst::codeGen() const
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
        return is_fp ? logError("Unsupported and operator for floating point"), nullptr : builder.CreateOr(lhs, rhs, "ortmp");
    case OP_AND:
        return is_fp ? logError("Unsupported and operator for floating point"), nullptr : builder.CreateAnd(lhs, rhs, "ortmp");
    default:
        return nullptr;
    }
}

Ast::SPL_IR SymbolAst::genPtr() const
{
    return st.getVarSymbol(name);
}

Ast::SPL_IR SymbolAst::codeGen() const
{
    if (st.getSymbolType(name, false) & SymbolTable::CONST)
        return st.getConstant(name).first;
    else {
        auto ptr = genPtr();
        if (ptr == nullptr)
        {
            logError("Not a variable");
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
        logError("Variable is not array type");
        return nullptr;
    }
    llvm::Value* index = exp_index->codeGen();
    llvm::Value* offset = st.getArrayOffset(array->getType());
    llvm::Value* offset_index = builder.CreateSub(index, offset);
    if (!index->getType()->isIntegerTy())
    {
        logError("Non-integer index");
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
        logError("Not a variable");
        return nullptr;
    }

    return builder.CreateLoad(ptr);
}

Ast::SPL_IR DotAst::genPtr() const
{
    auto record_ptr = record->genPtr();
    auto struct_mem = st.getRecordMap(record->codeGen()->getType());
    if (!struct_mem.count(field))
    {
        logError("Record doesn't have field " + field);
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
        logError("Not a variable");
        return nullptr;
    }

    return builder.CreateLoad(ptr);
}

Ast::SPL_IR FuncAst::codeGen() const
{
    auto func = st.getFuncSymbol(funcName);
    if (funcName == "writeln" || funcName == "write")
    {
        func.second = std::vector<bool>(argList.size(), false);
    }
    if (funcName == "read")
        func.second = std::vector<bool>(1, false);
    if (argList.size() != func.second.size())
    {
        logError("Wrong number of parameters passed");
        return nullptr;
    }
    int idx = 0;
    std::vector<llvm::Value*> argsv;
    std::vector<llvm::Type*> arg_raw_type;
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
            if (funcName == "read")
                arg_raw_type.push_back(var_ptr->codeGen()->getType());
        }
        else
            argsv.push_back(argList[idx]->codeGen());
        if (!argsv.back())
            return nullptr;
        if (argsv.back()->getType() != arg.getType())
        {
            logError("Parameter's type unmatched");
            return nullptr;
        }
        ++idx;
    }
    if (funcName == "writeln" || funcName == "write")
    {
        bool writeln = funcName == "writeln";
        argsv = getWriteArgument(context, argsv, module, writeln);
    }
    else if (funcName == "read")
        argsv = getReadArgument(context, argsv, arg_raw_type, module);
    return builder.CreateCall(func.first, argsv);
}

Ast::SPL_IR AssignAst::codeGen() const
{
    auto var_ptr = lhs -> genPtr();
    auto value = rhs->codeGen();
    if (var_ptr == nullptr || value == nullptr)
        return nullptr;
    if (!dynamic_cast<DotAst*>(lhs.get()) && !dynamic_cast<SymbolAst*>(lhs.get()) && !dynamic_cast<ArrayAst*>(lhs.get()))
    {
        logError("Right value cannot be assigned");
        return nullptr;
    }
    if (var_ptr->getType()->getContainedType(0) != value->getType())
    {
        logError("Type unmatched");
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
    logError("Undefined type");
    return nullptr;
}

Ast::SPL_IR SimpleVarDeclAst::codeGen() const
{
    auto var_t = this->type->genType();
    if (!var_t)
        return nullptr;
    if (st.hasName(name))
    {
        logError("Redefinition of variable");
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
    if (st.hasName(name))
    {
        logError("Name collision");
        return nullptr;
    }
    // generate the prototype of function
    std::vector<llvm::Type*> arg_tys;
    int idx = 0;
    for (auto& arg: args)
    {
        auto arg_ty = arg.first->genType();
        if (!arg_ty)
        {
            logError("Undefined type");
            return nullptr;
        }
        if (is_var[idx++])
            arg_ty = arg_ty->getPointerTo();
        arg_tys.push_back(arg_ty);
    }
    auto ret_ty = ret_type ==nullptr ? llvm::Type::getVoidTy(context) :ret_type->genType();
    if (!ret_ty)
    {
        logError("Undefined type");
        return nullptr;
    }
    auto func_ty = llvm::FunctionType::get(ret_ty, arg_tys, false);
    auto func = llvm::Function::Create(func_ty, llvm::Function::ExternalLinkage, name, &module);
    idx = 0;
    for (auto& arg: func->args())
        arg.setName(args[idx++].second);
    st.insertFunction(name, func, is_var);
    // parameter pass of function    
    st.pushScope();
    auto entrybb = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entrybb);
    idx = 0;
    for (auto& arg: func->args())
    {
        // bool is_array = st.getType(args[idx].first->getName()).is_array;
        if (is_var[idx])
        {
            // if (is_array) {
            //     auto min_value = st.getType(args[idx].first->getName()).min_index;
            //     auto min_const = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), min_value);
            //     st.insertArray(arg.getName(), &arg, min_const);
            // }
            // else
            st.insertVar(arg.getName(), &arg);
        }
        else 
        {
            auto tmp_ptr = builder.CreateAlloca(arg.getType());
            builder.CreateStore(tmp_ptr, &arg);
            st.insertVar(arg.getName(), tmp_ptr);
        }
        ++idx;
    }
    llvm::Value* ret_ptr = nullptr;
    if (!ret_ty->isVoidTy())
    {
        ret_ptr = builder.CreateAlloca(ret_ty);
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
    // remove local variable from symbol table
    st.popScope();
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
        logError("Collision of name");
        return nullptr;
    }
    std::vector<llvm::Type*> member_ty;
    for (auto& member: members)
    {
        member_ty.push_back(member.first->genType());
        if (!member_ty.back())
        {
            logError("Undefined type");
            return nullptr;
        }
    }
    return llvm::StructType::create(context, member_ty);
}

Ast::SPL_IR ConstDeclAst::codeGen() const
{
    if (st.hasName(name))
    {
        logError("Redefinition of variable");
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
        logError("This type cannot be constant");
        return nullptr;
    }
}

Ast::SPL_IR ArrayDeclAst::codeGen() const
{
    if (st.hasName(name))
    {
        logError("Redefinition of variable");
        return nullptr;
    }
    
    int min_value = minIndex->genIndex();
    int max_value = maxIndex->genIndex();
    int length = max_value - min_value + 1;
    if (min_value == ERRORNO || max_value == ERRORNO)
        return nullptr;
    if (length <= 0)
    {
        logError("Length of array cannot be negative");
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
        logError(name + " has already been defined");
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
        logError("Collision of name");
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
    return nullptr;
}

Ast::SPL_IR IfAst::codeGen() const
{
    auto condv = cond->codeGen();
    if (!condv)
        return nullptr;
    if (!condv->getType()->isIntegerTy(1))
    {
        logError("Condition expression should be boolean");
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
        logError("Case expression should be integer type");
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
        logError("Loop variable should be integer");
        return nullptr;
    }
    auto loop_var = builder.CreateStore(loopv, loopv_ptr);
    auto endv = end->codeGen();
    if (!endv)
        return nullptr;
    auto condv = builder.CreateICmpEQ(loopv, endv);
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
        logError("Conditional expression should be boolean");
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
        logError("Conditional expression should be boolean");
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
        logError("Undefined label");
        return nullptr;
    }
    auto gotobb = st.getLabelSymbol(std::to_string(label));
    if (gotobb->getParent() != builder.GetInsertBlock()->getParent())
    {
        logError("Cannot goto another label in other function");
        return nullptr;
    }
    builder.CreateBr(gotobb);
    return nullptr;
}

llvm::Value* TypeDeclAst::codeGen() const
{
    if (st.hasName(name))
    {
        logError("Type has been defined");
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
        logError("Length of array cannot be negative");
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
            logError("Undefined type");
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
}