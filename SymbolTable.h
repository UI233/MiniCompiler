#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "llvm/IR/IRBuilder.h"
#include "SPL_common.h"


class SymbolTable
{
public:
    using NamedStruct = std::pair<llvm::StructType*, std::map<std::string, int>>;
    using NamedArray = llvm::Value*;
    using NamedFunction = std::pair<llvm::Function*, std::vector<bool>>;
    using NamedConstant = std::pair<llvm::Constant*, valueUnion>;
    struct NamedType {
        llvm::Type* type;
        bool is_array;
        int min_index;
        NamedType(llvm::Type* ty) : type(ty), is_array(false) {}
        NamedType(llvm::Type* ty, int min_index_) : type(ty), is_array(true), min_index(min_index_) {}
        NamedType(const NamedType&) = default;
        NamedType(NamedType&) = default;
    };
private:
    struct Table 
    {
        using NamedStruct = std::pair<llvm::StructType*, std::map<std::string, int>>;
        using NamedArray = llvm::Value*;
        using NamedFunction = std::pair<llvm::Function*, std::vector<bool>>;
        using NamedConstant = std::pair<llvm::Constant*, valueUnion>;
        std::unordered_map<std::string, llvm::Value*> named_variable;
        std::unordered_map<std::string, NamedStruct> named_record;
        std::unordered_map<std::string, NamedArray> named_array;
        std::unordered_map<std::string, NamedFunction> named_function;
        std::unordered_map<std::string, llvm::BasicBlock*> named_label;
        std::unordered_map<std::string, NamedConstant> named_constant;
        std::unordered_map<std::string, NamedType> named_type;
    };
    std::vector<Table> tables;
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

    int getSymbolType(const std::string& name, bool current_scope = true) const;
    NamedFunction getFuncSymbol(const std::string& name) const;
    NamedStruct getRecordSymbol(const std::string& name) const;
    NamedArray getArraySymbol(const std::string& name) const;
    llvm::Value* getVarSymbol(const std::string& name) const;
    llvm::BasicBlock* getLabelSymbol(const std::string& name) const;
    NamedConstant getConstant(const std::string& name) const;
    NamedType getType(const std::string& name) const;
    bool insertVar(const std::string& name, llvm::Value* ptr);
    bool insertRecord(const std::string& name, llvm::StructType* ty, const std::vector<std::string>& member_name);
    bool insertFunction(const std::string& name, llvm::Function* func, const std::vector<bool>& is_var);
    bool insertLabel(const std::string& name, llvm::BasicBlock* block);
    bool insertConstant(const std::string& name, llvm::Constant* value, valueUnion value_v);
    bool insertArray(const std::string& name, llvm::Value* arr, llvm::ConstantInt* offset);
    bool insertType(const std::string& name, const NamedType& type);
    bool hasName(const std::string& name, bool current_scope = true) const;
    void popScope() ;
    void pushScope() ;

    SymbolTable(): tables(1) {};
    ~SymbolTable() = default;
};
