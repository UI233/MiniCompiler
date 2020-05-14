#include "SymbolTable.h"

SymbolTable::SymbolType SymbolTable::getSymbolType(const std::string& name) const
{
    if (named_function.count(name))
        return FUNCTION;
    else if(named_variable.count(name))
        return VAR;
    else if(named_record.count(name))
        return RECORD;
    else if (named_label.count(name))
        return LABEL;
    else
        return OTHER;
}

llvm::Function* SymbolTable::getFuncSymbol(const std::string& name) const
{
    switch (getSymbolType(name))
    {
    case FUNCTION:
        return named_function.find(name)->second;
        break;
    default:
        return nullptr;
        break;
    }
}

SymbolTable::NamedStruct SymbolTable::getRecordSymbol(const std::string& name) const
{
    switch (getSymbolType(name))
    {
    case RECORD:
        return named_record.find(name)->second;
        break;
    default:
        return std::make_pair(nullptr, std::vector<std::string>());
        break;
    }
}

llvm::Value* SymbolTable::getVarSymbol(const std::string& name) const
{
    switch (getSymbolType(name))
    {
    case VAR:
        return named_variable.find(name)->second;
        break;
    default:
        return nullptr;
        break;
    }
}

llvm::BasicBlock* SymbolTable::getLabelSymbol(const std::string& name) const
{
    switch (getSymbolType(name))
    {
    case LABEL:
        return named_label.find(name)->second;
        break;
    default:
        return nullptr;
        break;
    }
}

bool SymbolTable::hasName(const std::string& name) const
{
    return named_function.count(name) || named_record.count(name) || named_variable.count(name);
}
