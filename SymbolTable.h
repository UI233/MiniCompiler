#pragma once
#include <unordered_map>
#include <string>
#include "llvm/IR/IRBuilder.h"


class SymbolTable
{
public:
    using NamedStruct = std::pair<llvm::StructType*, std::vector<std::string>>;
private:
    std::unordered_map<std::string, llvm::Value*> named_variable;
    std::unordered_map<std::string, NamedStruct> named_record;
    std::unordered_map<std::string, llvm::Function*> named_function;
    std::unordered_map<std::string, llvm::BasicBlock*> named_label;
public:
    enum SymbolType
    {
        RECORD,
        FUNCTION,
        VAR,
        LABEL,
        OTHER
    };

    SymbolType getSymbolType(const std::string& name) const;
    llvm::Function* getFuncSymbol(const std::string& name) const;
    NamedStruct getRecordSymbol(const std::string& name) const;
    llvm::Value* getVarSymbol(const std::string& name) const;
    llvm::BasicBlock* getLabelSymbol(const std::string& name) const;
    bool hasName(const std::string& name) const;

    SymbolTable() = default;
    ~SymbolTable() = default;
};
