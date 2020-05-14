#include "SymbolTable.h"

int SymbolTable::getSymbolType(const std::string& name) const
{
    int symbol_type = 0;
    if (named_function.count(name))
        symbol_type |= FUNCTION;
    if(named_variable.count(name))
        symbol_type |= VAR;
    if(named_record.count(name))
        symbol_type |= RECORD;
    if (named_label.count(name))
        symbol_type |= LABEL;
    if (named_array.count(name))
        symbol_type |= ARRAY;
    return symbol_type;
}

SymbolTable::NamedFunction SymbolTable::getFuncSymbol(const std::string& name) const
{
    if (getSymbolType(name) | FUNCTION)
        return named_function.find(name)->second;
    else
        return NamedFunction();
}

SymbolTable::NamedStruct SymbolTable::getRecordSymbol(const std::string& name) const
{
    if (getSymbolType(name) | RECORD)
        return named_record.find(name)->second;
    else
        return std::make_pair(nullptr, std::map<std::string, int>());
}

SymbolTable::NamedArray SymbolTable::getArraySymbol(const std::string& name) const
{
    if (getSymbolType(name) | ARRAY)
        return named_array.find(name)->second;
    else
        return NamedArray();

}

llvm::Value* SymbolTable::getVarSymbol(const std::string& name) const
{
    if (getSymbolType(name) | VAR)
        return named_variable.find(name)->second;
    else
        return nullptr;
}

llvm::BasicBlock* SymbolTable::getLabelSymbol(const std::string& name) const
{
    if (getSymbolType(name) | LABEL)
        return named_label.find(name)->second;
    else
        return nullptr;
}

bool SymbolTable::hasName(const std::string& name) const
{
    return named_function.count(name) || named_record.count(name) || named_variable.count(name);
}
