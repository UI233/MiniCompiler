#include "SymbolTable.h"

int SymbolTable::getSymbolType(const std::string& name, bool current_scope) const
{
    int symbol_type = 0;
    if (current_scope)
    {
        if (tables.back().named_function.count(name))
            symbol_type |= FUNCTION;
        if(tables.back().named_variable.count(name))
            symbol_type |= VAR;
        if(tables.back().named_type.count(name))
            symbol_type |= TYPE;
        // if(tables.back().named_record.count(name))
        //     symbol_type |= RECORD;
        if (tables.back().named_label.count(name))
            symbol_type |= LABEL;
        // if (tables.back().named_array.count(name))
        //     symbol_type |= ARRAY;
        if (tables.back().named_constant.count(name))
            symbol_type |= CONST;
    }
    else
    {
        for (int i = tables.size() - 1; i >= 0 && symbol_type == 0; --i)
        {
            if (tables[i].named_function.count(name))
                symbol_type |= FUNCTION;
            if(tables[i].named_variable.count(name))
                symbol_type |= VAR;
            if(tables[i].named_type.count(name))
                symbol_type |= TYPE;
            // if(tables[i].named_record.count(name))
            //     symbol_type |= RECORD;
            if (tables[i].named_label.count(name))
                symbol_type |= LABEL;
            // if (tables[i].named_array.count(name))
            //     symbol_type |= ARRAY;
            if (tables[i].named_constant.count(name))
                symbol_type |= CONST;
        }
    }
    return symbol_type;
}

SymbolTable::NamedFunction SymbolTable::getFuncSymbol(const std::string& name) const
{
    if (getSymbolType(name, false) & FUNCTION)
    {
        for (int i = tables.size() - 1; i >= 0; --i)
            if (tables[i].named_function.count(name)) 
                return tables[i].named_function.find(name)->second;
    }
    return NamedFunction();
}

// SymbolTable::NamedStruct SymbolTable::getRecordSymbol(const std::string& name) const
// {
//     if (getSymbolType(name, false) | RECORD)
//     {
//         for (int i = tables.size() - 1; i >= 0; --i)
//             if (tables[i].named_record.count(name)) 
//                 return tables[i].named_record.find(name)->second;
//     }
//     else
//         return std::make_pair(nullptr, std::map<std::string, int>());
// }

// SymbolTable::NamedArray SymbolTable::getArraySymbol(const std::string& name) const
// {
//     if (getSymbolType(name, false) | ARRAY)
//     {
//         for (int i = tables.size() - 1; i >= 0; --i)
//             if (tables[i].named_array.count(name)) 
//                 return tables[i].named_array.find(name)->second;
//     }
//     else
//         return NamedArray();
// }

llvm::ConstantInt* SymbolTable::getArrayOffset(llvm::Type* arr_t) const
{
    for (int i = tables.size() - 1; i >= 0; --i) 
        if (tables[i].named_array.count(arr_t))
            return tables[i].named_array.find(arr_t)->second;
    return nullptr;
}

std::map<std::string, int> SymbolTable::getRecordMap(llvm::Type* struct_t) const
{
    for (int i = tables.size() - 1; i >= 0; --i) 
        if (tables[i].named_record.count(struct_t))
            return tables.back().named_record.find(struct_t)->second;
    return std::map<std::string, int>();
}

llvm::Value* SymbolTable::getVarSymbol(const std::string& name) const
{
    if (getSymbolType(name, true) & FUNCTION)
        return tables.back().named_variable.find("0" + name)->second;
    else if (getSymbolType(name, true) & VAR)
    {
        return tables.back().named_variable.find(name)->second;
        // for (int i = tables.size() - 1; i >= 0; --i)
        //     if (tables[i].named_variable.count(name)) 
        //         return tables[i].named_variable.find(name)->second;
    }
    return nullptr;
}

llvm::BasicBlock* SymbolTable::getLabelSymbol(const std::string& name) const
{
    if (getSymbolType(name) & LABEL)
    {
        for (int i = tables.size() - 1; i >= 0; --i)
            if (tables[i].named_label.count(name)) 
                return tables[i].named_label.find(name)->second;
    }
    return nullptr;
}

SymbolTable::NamedConstant SymbolTable::getConstant(const std::string& name) const
{
    if (getSymbolType(name, false) & CONST)
    {
        for (int i = tables.size() - 1; i >= 0; --i)
            if (tables[i].named_constant.count(name)) 
                return tables[i].named_constant.find(name)->second;
    }
    return std::make_pair(nullptr, valueUnion());
}

SymbolTable::NamedType SymbolTable::getType(const std::string& name) const
{
    if (getSymbolType(name, false) & TYPE)
    {
        for (int i = tables.size() - 1; i >= 0; --i)
            if (tables[i].named_type.count(name)) 
                return tables[i].named_type.find(name)->second;
    }
    return nullptr;
}

bool SymbolTable::insertVar(const std::string& name, llvm::Value* ptr, bool shadowable)
{
    if (hasName(name) && !tables.back().shadowable_name.count(name))
        return false;
    if (tables.back().named_variable.count(name))
    {
        tables.back().named_variable.erase(name);
        tables.back().shadowed_name.insert(name);
    }
    if (shadowable)
        tables.back().shadowable_name.insert(name);
    tables.back().named_variable.insert(std::make_pair(name, ptr));
    return true;
}

bool SymbolTable::insertRecord(llvm::StructType* ty, const std::vector<std::string>& member_name)
{
    // if (hasName(name))
    //     return false;
    NamedStruct member_map;
    member_map.first = ty;
    for (int i = 0; i < member_name.size(); ++i)
    {
        if (member_map.second.count(member_name[i]))
            return false;
        member_map.second.insert(std::make_pair(member_name[i], i));
    }
    tables.back().named_record.insert(std::make_pair(ty, member_map.second));
    // tables.back().named_type.insert(std::make_pair(ty, member_map));
    return true;
}

bool SymbolTable::insertFunction(const std::string& name, llvm::Function* func, const std::vector<bool>& is_var, int scope_num)
{
    if (hasName(name))
        return false;
    tables.back().named_function.insert(std::make_pair(name, std::make_tuple(func, is_var, scope_num)));
    return true;
}

bool SymbolTable::insertLabel(const std::string& name, llvm::BasicBlock* block)
{
    if (hasName(name, false))
        return false;
    tables.back().named_label.insert(std::make_pair(name, block));
    return true;
}

bool SymbolTable::insertConstant(const std::string& name, llvm::Value* value, valueUnion value_v, bool shadowable)
{
    if (hasName(name, false) && !tables.back().shadowable_name.count(name))
        return false;
    if (tables.back().named_constant.count(name))
    {
        tables.back().named_constant.erase(name);
        tables.back().shadowed_name.insert(name);
    }
    if (shadowable)
        tables.back().shadowable_name.insert(name);
    tables.back().named_constant.insert(std::make_pair(name, NamedConstant(value, value_v)));
    return true;
}

bool SymbolTable::insertArray(llvm::Type* arr_t, llvm::ConstantInt* offset)
{
    // if (hasName(name, false))
    //     return false;
    tables.back().named_array.insert(std::make_pair(arr_t, offset));
    // tables.back().named_variable.insert(std::make_pair(name, arr));
    return true;
}

bool SymbolTable::insertType(const std::string& name, llvm::Type* type) 
{
    if (hasName(name, false))
        return false;
    tables.back().named_type.insert(std::make_pair(name, type));
    return true;
}

bool SymbolTable::hasShadowedVar(const std::string& name, int scope) const
{
    if (scope >= tables.size())
        return false;
    return tables[scope].shadowed_name.count(name);
}

bool SymbolTable::hasName(const std::string& name, bool current_scope) const
{
    return getSymbolType(name, current_scope) != 0;
}

void SymbolTable::popScope()
{
    tables.pop_back();
}

void SymbolTable::pushScope()
{
    SymbolTable::Table a;
    tables.push_back(a);
}

FuncVar SymbolTable::genParamType(int scope) const
{
    if (scope == -1)
        scope = tables.size() - 1;
    std::vector<llvm::Type*> elements_ty;
    std::vector<std::string> param_names;
    for (auto& v: tables[scope].named_variable)
    {
        elements_ty.push_back(v.second->getType());
        param_names.push_back(v.first);
    }
    std::vector<std::string> constant_name;
    std::vector<valueUnion> constant_value;
    for (auto& v: tables[scope].named_constant)
    {
        constant_name.push_back(v.first);
        constant_value.push_back(v.second.second);
        elements_ty.push_back(v.second.first->getType());
    }
    llvm::Type* struct_ty = elements_ty.size() == 0 ? nullptr : llvm::StructType::create(elements_ty);
    return FuncVar(struct_ty, param_names, constant_name, constant_value);
}


std::vector<llvm::Value*> SymbolTable::genParam(int scope) const
{
    std::vector<llvm::Value*> params;
    for (auto& v: tables[scope].named_variable)
        params.push_back(v.second);
    for (auto& v: tables[scope].named_constant)
        params.push_back(v.second.first);
    return params;
}