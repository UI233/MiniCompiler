#pragma once
#include <unordered_map>
#include <string>
#include "llvm/IR/IRBuilder.h"


class SymbolTable
{
public:
    using NamedStruct = std::pair<llvm::StructType*, std::map<std::string, int>>;
    using NamedArray = llvm::Value*;
    using NamedFunction = std::pair<llvm::Function*, std::vector<bool>>;
private:
    std::unordered_map<std::string, llvm::Value*> named_variable;
    std::unordered_map<std::string, NamedStruct> named_record;
    std::unordered_map<std::string, NamedArray> named_array;
    std::unordered_map<std::string, NamedFunction> named_function;
    std::unordered_map<std::string, llvm::BasicBlock*> named_label;
    std::unordered_map<std::string, llvm::Type*> named_type;
public:
    enum SymbolType
    {
        RECORD = 1,
        FUNCTION = 2,
        VAR = 4,
        LABEL = 8,
        TYPE = 16,
        ARRAY = 32,
        CONST = 64,
        OTHER = 0
    };

    int getSymbolType(const std::string& name) const;
    NamedFunction getFuncSymbol(const std::string& name) const;
    NamedStruct getRecordSymbol(const std::string& name) const;
    NamedArray getArraySymbol(const std::string& name) const;
    llvm::Value* getVarSymbol(const std::string& name) const;
    llvm::BasicBlock* getLabelSymbol(const std::string& name) const;
    void insertVar(const std::string& name, llvm::Value* ptr);
    bool hasName(const std::string& name) const;

    SymbolTable() = default;
    ~SymbolTable() = default;
};
