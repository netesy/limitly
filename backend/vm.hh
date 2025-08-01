#ifndef VM_H
#define VM_H

#include "../opcodes.hh"
#include "../debugger.hh"
#include "memory.hh"
#include "value.hh"
#include "types.hh"
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <memory>
#include <variant>
#include <string>
#include <iostream>
#include <functional>

// Forward declarations
class Environment;
struct CallFrame;

// Function definition for user-defined functions
struct Function {
    std::string name;
    // std::vector<std::string> parameters;
    // std::vector<std::string> optionalParameters;
    // std::map<std::string, ValuePtr> defaultValues;
    std::vector<std::pair<std::string, TypePtr>> parameters;  // name and type
    std::vector<std::pair<std::string, TypePtr>> optionalParameters;
    std::map<std::string, std::pair<ValuePtr, TypePtr>> defaultValues;
    size_t startAddress;
    size_t endAddress;
    TypePtr returnType;
    
    Function() : startAddress(0), endAddress(0), returnType(nullptr) {}
    
    Function(const std::string& n, size_t start) 
        : name(n), startAddress(start), endAddress(0), returnType(nullptr) {}
};

// Virtual Machine class
class VM {
public:
    VM();
    ~VM();
    
    // Execute bytecode
    ValuePtr execute(const std::vector<Instruction>& bytecode);
    
    // Function to enable or disable debug output
    void setDebug(bool enable) { 
        debugMode = enable;
        debugOutput = enable;
    }
    
    // Register native function
    void registerNativeFunction(const std::string& name, std::function<ValuePtr(const std::vector<ValuePtr>&)> function);
    
private:
    // Memory management
    MemoryManager<> memoryManager;
    std::unique_ptr<MemoryManager<>::Region> region;
    TypeSystem* typeSystem;
    
    // VM state
    std::vector<ValuePtr> stack;
    std::vector<CallFrame> callStack;
    std::shared_ptr<Environment> globals;
    std::shared_ptr<Environment> environment;
    std::unordered_map<std::string, std::function<ValuePtr(const std::vector<ValuePtr>&)>> nativeFunctions;
    std::unordered_map<std::string, Function> userFunctions;
    std::vector<ValuePtr> tempValues;
    ValuePtr lastException;
    
    // Current execution state
    const std::vector<Instruction>* bytecode;
    size_t ip; // Instruction pointer
    bool debugMode;
    bool debugOutput;
    std::string currentFunctionBeingDefined; // Track which function is currently being defined
    bool insideFunctionDefinition; // Track if we're currently inside a function definition
    
    // Helper methods
    ValuePtr pop();
    void push(const ValuePtr& value);
    ValuePtr peek(int distance = 0) const;
    std::string valueToString(const ValuePtr& value);
    
public:
    // Debugging methods
    void printStack() const;
    
private:
    void error(const std::string& message) const;
    
    // Instruction handlers
    void handlePushInt(const Instruction& instruction);
    void handlePushFloat(const Instruction& instruction);
    void handlePushString(const Instruction& instruction);
    void handlePushBool(const Instruction& instruction);
    void handlePushNull(const Instruction& instruction);
    void handlePop(const Instruction& instruction);
    void handleDup(const Instruction& instruction);
    void handleSwap(const Instruction& instruction);
    void handleStoreVar(const Instruction& instruction);
    void handleLoadVar(const Instruction& instruction);
    void handleStoreTemp(const Instruction& instruction);
    void handleLoadTemp(const Instruction& instruction);
    void handleClearTemp(const Instruction& instruction);
    void handleAdd(const Instruction& instruction);
    void handleSubtract(const Instruction& instruction);
    void handleMultiply(const Instruction& instruction);
    void handleDivide(const Instruction& instruction);
    void handleModulo(const Instruction& instruction);
    void handleNegate(const Instruction& instruction);
    void handleEqual(const Instruction& instruction);
    void handleNotEqual(const Instruction& instruction);
    void handleLess(const Instruction& instruction);
    void handleLessEqual(const Instruction& instruction);
    void handleGreater(const Instruction& instruction);
    void handleGreaterEqual(const Instruction& instruction);
    void handleAnd(const Instruction& instruction);
    void handleOr(const Instruction& instruction);
    void handleNot(const Instruction& instruction);
    void handleInterpolateString(const Instruction& instruction);
    void handleConcat(const Instruction& instruction);
    void handleJump(const Instruction& instruction);
    void handleJumpIfTrue(const Instruction& instruction);
    void handleJumpIfFalse(const Instruction& instruction);
    void handleCall(const Instruction& instruction);
    void handleReturn(const Instruction& instruction);
    void handleBeginFunction(const Instruction& instruction);
    void handleEndFunction(const Instruction& instruction);
    void handleDefineParam(const Instruction& instruction);
    void handleDefineOptionalParam(const Instruction& instruction);
    void handleSetDefaultValue(const Instruction& instruction);
    void handleBeginClass(const Instruction& instruction);
    void handleEndClass(const Instruction& instruction);
    void handleGetProperty(const Instruction& instruction);
    void handleSetProperty(const Instruction& instruction);
    void handleCreateList(const Instruction& instruction);
    void handleListAppend(const Instruction& instruction);
    void handleCreateDict(const Instruction& instruction);
    void handleCreateRange(const Instruction& instruction);
    void handleDictSet(const Instruction& instruction);
    void handleGetIndex(const Instruction& instruction);
    void handleSetIndex(const Instruction& instruction);
    void handleGetIterator(const Instruction& instruction);
    void handleIteratorHasNext(const Instruction& instruction);
    void handleIteratorNext(const Instruction& instruction);
    void handleIteratorNextKeyValue(const Instruction& instruction);
    void handleBeginScope(const Instruction& instruction);
    void handleEndScope(const Instruction& instruction);
    
    // Helper function for value comparison
    bool valuesEqual(const ValuePtr& a, const ValuePtr& b) const;
    void handleBeginTry(const Instruction& instruction);
    void handleEndTry(const Instruction& instruction);
    void handleBeginHandler(const Instruction& instruction);
    void handleEndHandler(const Instruction& instruction);
    void handleThrow(const Instruction& instruction);
    void handleStoreException(const Instruction& instruction);
    void handleBeginParallel(const Instruction& instruction);
    void handleEndParallel(const Instruction& instruction);
    void handleBeginConcurrent(const Instruction& instruction);
    void handleEndConcurrent(const Instruction& instruction);
    void handleAwait(const Instruction& instruction);
    void handleMatchPattern(const Instruction& instruction);
    void handleImport(const Instruction& instruction);
    void handleBeginEnum(const Instruction& instruction);
    void handleEndEnum(const Instruction& instruction);
    void handleDefineEnumVariant(const Instruction& instruction);
    void handleDefineEnumVariantWithType(const Instruction& instruction);
    void handlePrint(const Instruction& instruction);
    void handleDebugPrint(const Instruction& instruction);
};

// Environment for variable scopes
class Environment {
public:
    Environment(std::shared_ptr<Environment> enclosing = nullptr) : enclosing(enclosing) {}
    
    void define(const std::string& name, const ValuePtr& value) {
        values[name] = value;
    }
    
    ValuePtr get(const std::string& name) {
        auto it = values.find(name);
        if (it != values.end()) {
            return it->second;
        }
        
        if (enclosing) {
            return enclosing->get(name);
        }
        
        throw std::runtime_error("Undefined variable '" + name + "'");
    }

   
    void assign(const std::string& name, const ValuePtr& value) {
        auto it = values.find(name);
        if (it != values.end()) {
            it->second = value;
            return;
        }
        
        if (enclosing) {
            enclosing->assign(name, value);
            return;
        }
        
        throw std::runtime_error("Undefined variable '" + name + "'");
    }
    
    std::shared_ptr<Environment> enclosing;
    
private:
    std::unordered_map<std::string, ValuePtr> values;
};

// Call frame for function calls
struct CallFrame {
    std::string functionName;
    size_t returnAddress;
    size_t basePointer;
    std::shared_ptr<Environment> environment;
};

#endif // VM_H