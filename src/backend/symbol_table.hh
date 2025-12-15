#pragma once

#include "types.hh"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

struct Symbol {
    std::string name;
    TypePtr type;
    int line;
    // Add any other symbol information you need
};

// Function signature information for error type checking
struct FunctionSignature {
    std::string name;
    std::vector<TypePtr> paramTypes;
    std::vector<bool> optionalParams;  // Track which parameters are optional
    std::vector<bool> hasDefaultValues; // Track which parameters have default values
    TypePtr returnType;
    bool canFail = false;
    std::vector<std::string> errorTypes;
    int line;
    
    // Default constructor for use in containers
    FunctionSignature() : name(""), paramTypes(), optionalParams(), hasDefaultValues(), 
                         returnType(nullptr), canFail(false), errorTypes(), line(0) {}
    
    FunctionSignature(const std::string& n, const std::vector<TypePtr>& params, 
                     TypePtr ret, bool fail = false, 
                     const std::vector<std::string>& errors = {}, int ln = 0,
                     const std::vector<bool>& optional = {}, const std::vector<bool>& defaults = {})
        : name(n), paramTypes(params), optionalParams(optional), hasDefaultValues(defaults),
          returnType(ret), canFail(fail), errorTypes(errors), line(ln) {}
          
    // Helper method to get minimum required arguments
    size_t getMinRequiredArgs() const {
        size_t minArgs = paramTypes.size();
        for (size_t i = 0; i < optionalParams.size(); ++i) {
            if (optionalParams[i] || (i < hasDefaultValues.size() && hasDefaultValues[i])) {
                minArgs = i;
                break;
            }
        }
        return minArgs;
    }
    
    // Helper method to check if argument count is valid
    bool isValidArgCount(size_t argCount) const {
        size_t minArgs = getMinRequiredArgs();
        size_t maxArgs = paramTypes.size();
        return argCount >= minArgs && argCount <= maxArgs;
    }
};

class SymbolTable {
public:
    SymbolTable();

    void enterScope();
    void exitScope();

    TypePtr getType(const std::string& name);

    void addVariable(const std::string& name, TypePtr type, int line);
    Symbol* findVariable(const std::string& name);

    void addFunction(const std::string& name, const FunctionSignature& signature);
    FunctionSignature* findFunction(const std::string& name);

    bool isInGlobalScope() const;

private:
    std::vector<std::unordered_map<std::string, Symbol>> variableScopeStack;
    std::vector<std::unordered_map<std::string, FunctionSignature>> functionScopeStack;
};
