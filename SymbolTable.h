#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "llvm/IR/IRBuilder.h"
#include "SPL_common.h"

struct FuncVar {
    llvm::Type* struct_ty;
    std::vector<std::string> var_name;
    std::vector<std::string> constant_name;
    std::vector<valueUnion> constant_value;
    FuncVar(llvm::Type* _struct_ty, const std::vector<std::string>& _var_name, const std::vector<std::string>& _const_name, const std::vector<valueUnion>& _const_value): 
        struct_ty(_struct_ty), var_name(_var_name), constant_name(_const_name), constant_value(_const_value) {}
    FuncVar(const FuncVar&) = default;
    FuncVar() = default;
};

class SymbolTable
{
public:
    using NamedStruct = std::pair<llvm::StructType*, std::map<std::string, int>>;
    using NamedArray = llvm::Value*;
    using NamedFunction = std::tuple<llvm::Function*, std::vector<bool>, int>;
    using NamedConstant = std::pair<llvm::Value*, valueUnion>;
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
        // using NamedStruct = std::pair<llvm::StructType*, std::map<std::string, int>>;
        // using NamedArray = llvm::Value*;
        // using NamedFunction = std::pair<llvm::Function*, std::vector<bool>>;
        // using NamedConstant = std::pair<llvm::Value*, valueUnion>;
        std::unordered_map<std::string, llvm::Value*> named_variable;
        std::unordered_map<std::string, NamedFunction> named_function;
        std::unordered_map<std::string, llvm::BasicBlock*> named_label;
        std::unordered_map<std::string, NamedConstant> named_constant;
        std::unordered_map<std::string, llvm::Type*> named_type;
        std::unordered_map<llvm::Type*, llvm::ConstantInt*> named_array;
        std::unordered_map<llvm::Type*, std::map<std::string, int>> named_record;
        std::unordered_set<std::string> shadowable_name;
        std::unordered_set<std::string> shadowed_name;
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
    std::map<std::string, int> getRecordMap(llvm::Type* struct_t) const;
    llvm::ConstantInt* getArrayOffset(llvm::Type* arr_t) const;
    llvm::Value* getVarSymbol(const std::string& name) const;
    llvm::BasicBlock* getLabelSymbol(const std::string& name) const;
    NamedConstant getConstant(const std::string& name) const;
    NamedType getType(const std::string& name) const;
    FuncVar genParamType(int scope = -1) const;
    std::vector<llvm::Value*> genParam(int scope) const;
    bool insertVar(const std::string& name, llvm::Value* ptr, bool shadowable = false);
    bool insertRecord(llvm::StructType* ty, const std::vector<std::string>& member_name);
    bool insertFunction(const std::string& name, llvm::Function* func, const std::vector<bool>& is_var, int scope_num);
    bool insertLabel(const std::string& name, llvm::BasicBlock* block);
    bool insertConstant(const std::string& name, llvm::Value* value, valueUnion value_v, bool shadowable = false);
    bool insertArray(llvm::Type* arr_t, llvm::ConstantInt* offset);
    bool insertType(const std::string& name, llvm::Type* type);
    bool hasName(const std::string& name, bool current_scope = true) const;
    bool hasShadowedVar(const std::string& name, int scope) const;
    inline int getScopeNum() const {return tables.size() - 1;}
    void popScope() ;
    void pushScope() ;

    SymbolTable(): tables(1) {};
    ~SymbolTable() = default;
};
