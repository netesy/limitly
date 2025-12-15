#include "symbol_table.hh"

SymbolTable::SymbolTable() {
    // Start with a global scope
    enterScope();
}

void SymbolTable::enterScope() {
    variableScopeStack.emplace_back();
    functionScopeStack.emplace_back();
}

void SymbolTable::exitScope() {
    if (!variableScopeStack.empty()) {
        variableScopeStack.pop_back();
    }
    if (!functionScopeStack.empty()) {
        functionScopeStack.pop_back();
    }
}


TypePtr SymbolTable::getType(const std::string& name) {
    // First check variables
    for (auto it = variableScopeStack.rbegin(); it != variableScopeStack.rend(); ++it) {
        auto& scope = *it;
        auto symbolIt = scope.find(name);
        if (symbolIt != scope.end()) {
            return symbolIt->second.type;
        }
    }
    // Then check functions (return their return type)
    for (auto it = functionScopeStack.rbegin(); it != functionScopeStack.rend(); ++it) {
        auto& scope = *it;
        auto funcIt = scope.find(name);
        if (funcIt != scope.end()) {
            return funcIt->second.returnType;
        }
    }
    return nullptr;
}

void SymbolTable::addVariable(const std::string& name, TypePtr type, int line) {
    if (!variableScopeStack.empty()) {
        variableScopeStack.back()[name] = {name, type, line};
    }
}

Symbol* SymbolTable::findVariable(const std::string& name) {
    for (auto it = variableScopeStack.rbegin(); it != variableScopeStack.rend(); ++it) {
        auto& scope = *it;
        auto symbolIt = scope.find(name);
        if (symbolIt != scope.end()) {
            return &symbolIt->second;
        }
    }
    return nullptr;
}

void SymbolTable::addFunction(const std::string& name, const FunctionSignature& signature) {
    if (!functionScopeStack.empty()) {
        functionScopeStack.back()[name] = signature;
    }
}

FunctionSignature* SymbolTable::findFunction(const std::string& name) {
    for (auto it = functionScopeStack.rbegin(); it != functionScopeStack.rend(); ++it) {
        auto& scope = *it;
        auto signatureIt = scope.find(name);
        if (signatureIt != scope.end()) {
            return &signatureIt->second;
        }
    }
    return nullptr;
}

bool SymbolTable::isInGlobalScope() const {
    return variableScopeStack.size() == 1;
}
