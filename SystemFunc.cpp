#include "SystemFunc.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
// declaration of writeln and write
llvm::Function* createWritePrototype(llvm::LLVMContext& context, llvm::Module* mod)
{
    std::vector<llvm::Type*> arg_tys;
    arg_tys.push_back(llvm::Type::getInt8PtrTy(context));
    auto func_ty = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), arg_tys, true);
    auto func = llvm::Function::Create(func_ty, llvm::Function::ExternalLinkage, llvm::Twine("printf"), mod);
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

// declaration of read
llvm::Function* createReadPrototype(llvm::LLVMContext& context, llvm::Module* mod)
{
    std::vector<llvm::Type*> arg_tys;
    arg_tys.push_back(llvm::Type::getInt8PtrTy(context));
    auto func_ty = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), arg_tys, true);
    auto func = llvm::Function::Create(func_ty, llvm::Function::ExternalLinkage, llvm::Twine("scanf"), mod);
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

std::vector<llvm::Value*> getWriteArgument(llvm::LLVMContext& context, const std::vector<llvm::Value*>& args, llvm::Module& mod, bool writeln)
{
    std::string format_str = "";
    for (auto& arg: args)
    {
        auto ty = arg->getType();
        if (ty->isIntegerTy(32) || ty->isIntegerTy(1))
            format_str += "%d ";
        else if (ty->isIntegerTy(8))
            format_str += "%c ";
        else if (ty->isDoubleTy())
            format_str += "%f ";
    }
    format_str[format_str.size() - 1] = writeln ? '\n' : '\0';
    std::vector<llvm::Value *> printf_args;
    auto printf_format_const = llvm::ConstantDataArray::getString(context, format_str, true);
    auto format_string_var = new llvm::GlobalVariable(mod,
    llvm::ArrayType::get(llvm::IntegerType::get(context, 8),
                        format_str.length() + 1), true,
    llvm::GlobalValue::PrivateLinkage, printf_format_const);
    auto zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(context));
    std::vector<llvm::Constant *> indices;
    indices.push_back(zero);
    indices.push_back(zero);
    auto var_ref = llvm::ConstantExpr::getGetElementPtr(
            llvm::ArrayType::get(llvm::IntegerType::get(context, 8), format_str.size() + 1),
            format_string_var,
            indices);

    printf_args.push_back(var_ref);
    for (auto& arg: args)
        printf_args.push_back(arg);
    return printf_args;
}

std::vector<llvm::Value*> getReadArgument(llvm::LLVMContext& context, const std::vector<llvm::Value*>& args, const std::vector<llvm::Type*>& args_type, llvm::Module& mod)
{
    std::string format_str = "";
    for (auto& ty: args_type)
    {
        if (ty->isIntegerTy(32) || ty->isIntegerTy(1))
            format_str += "%d";
        else if (ty->isIntegerTy(8))
            format_str += "%c";
        else if (ty->isDoubleTy())
            format_str += "%f";
    }
    std::vector<llvm::Value*> read_args;
    auto scanf_format_const = llvm::ConstantDataArray::getString(context, format_str, true);
    auto format_string_var = new llvm::GlobalVariable(mod,
    llvm::ArrayType::get(llvm::IntegerType::get(context, 8),
                        format_str.length() + 1), true,
    llvm::GlobalValue::PrivateLinkage, scanf_format_const);
    auto zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(context));
    std::vector<llvm::Constant *> indices;
    indices.push_back(zero);
    indices.push_back(zero);
    auto var_ref = llvm::ConstantExpr::getGetElementPtr(
            llvm::ArrayType::get(llvm::IntegerType::get(context, 8), format_str.size() + 1),
            format_string_var,
            indices);
    read_args.push_back(var_ref);
    for(auto& arg: args)
        read_args.push_back(arg);
    return read_args;
}