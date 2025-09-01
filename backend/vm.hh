#ifndef VM_H
#define VM_H

#include "../opcodes.hh"
#include "../debugger.hh"
#include "memory.hh"
#include "value.hh"
#include "types.hh"
#include "functions.hh"
#include "classes.hh"
#include "concurrency/scheduler.hh"
#include "concurrency/thread_pool.hh"
#include "concurrency/event_loop.hh"
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <memory>
#include <variant>
#include <string>
#include <iostream>
#include <functional>
#include <thread>
#include <mutex>

// Forward declarations
class Environment;
struct CallFrame;
class VM;

// Virtual Machine class
class VM {
public:
    explicit VM(bool create_runtime = true);
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
    
    // Register user-defined function from AST
    void registerUserFunction(const std::shared_ptr<AST::FunctionDeclaration>& decl);
    void registerUserFunction(const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl);
    
private:
    // Memory management
    MemoryManager<> memoryManager;
    std::unique_ptr<MemoryManager<>::Region> region;
    TypeSystem* typeSystem;
    
    // VM state
    std::vector<ValuePtr> stack;
    std::vector<backend::CallFrame> callStack; // Use the new CallFrame from functions.hh
    std::shared_ptr<Environment> globals;
    std::shared_ptr<Environment> environment;
    std::unordered_map<std::string, std::function<ValuePtr(const std::vector<ValuePtr>&)>> nativeFunctions;
    // Removed duplicate userFunctions map - using functionRegistry instead
    backend::FunctionRegistry functionRegistry; // New function abstraction layer
    backend::ClassRegistry classRegistry; // Class management
    std::unordered_map<std::string, backend::Function> userDefinedFunctions; // Use the proper Function struct
    std::vector<ValuePtr> tempValues;
    ValuePtr lastException;
    
    // Current execution state
    const std::vector<Instruction>* bytecode;
    size_t ip; // Instruction pointer
    bool debugMode;
    bool debugOutput;
    static int matchCounter;
    std::string currentFunctionBeingDefined; // Track which function is currently being defined
    bool insideFunctionDefinition; // Track if we're currently inside a function definition
    std::string currentClassBeingDefined; // Track which class is currently being defined
    bool insideClassDefinition; // Track if we're currently inside a class definition
    
    // Map to store runtime default values for class fields
    std::unordered_map<std::string, ValuePtr> fieldDefaultValues;

    // Concurrency runtime
    std::shared_ptr<Scheduler> scheduler;
    std::shared_ptr<ThreadPool> thread_pool;
    std::shared_ptr<EventLoop> event_loop;
    
    // Helper methods
    ValuePtr pop();
    void push(const ValuePtr& value);
    ValuePtr peek(int distance = 0) const;
    std::string valueToString(const ValuePtr& value);
    
public:
    // Debugging methods
    void printStack() const;
    
    std::shared_ptr<ThreadPool> getThreadPool() { return thread_pool; }

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
    void handleSetSuperclass(const Instruction& instruction);
    void handleDefineField(const Instruction& instruction);
    void handleLoadThis(const Instruction& instruction);
    void handleLoadSuper(const Instruction& instruction);
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

// VM-specific user-defined function implementation
class VMUserDefinedFunction : public backend::UserDefinedFunction {
private:
    VM* vm;
    size_t startAddress;
    size_t endAddress;
    
public:
    VMUserDefinedFunction(VM* vmInstance, const std::shared_ptr<AST::FunctionDeclaration>& decl, 
                         size_t start, size_t end);
    VMUserDefinedFunction(VM* vmInstance, const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl,
                         size_t start, size_t end);
    
    ValuePtr execute(const std::vector<ValuePtr>& args) override;
    
    size_t getStartAddress() const { return startAddress; }
    size_t getEndAddress() const { return endAddress; }
    void setEndAddress(size_t end) { endAddress = end; }
};

// Environment for variable scopes
class Environment {
public:
    Environment(std::shared_ptr<Environment> enclosing = nullptr) : enclosing(enclosing) {}
    
    void define(const std::string& name, const ValuePtr& value) {
        std::lock_guard<std::mutex> lock(mutex);
        values[name] = value;
    }
    
    ValuePtr get(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = values.find(name);
        if (it != values.end()) {
            return it->second;
        }
        
        if (enclosing) {
            // The recursive call will lock the enclosing environment
            return enclosing->get(name);
        }
        
        throw std::runtime_error("Undefined variable '" + name + "'");
    }

   
    void assign(const std::string& name, const ValuePtr& value) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = values.find(name);
        if (it != values.end()) {
            it->second = value;
            return;
        }
        
        if (enclosing) {
            // The recursive call will lock the enclosing environment
            enclosing->assign(name, value);
            return;
        }
        
        throw std::runtime_error("Undefined variable '" + name + "'");
    }
    
    std::shared_ptr<Environment> enclosing;
    
private:
    std::unordered_map<std::string, ValuePtr> values;
    std::mutex mutex;
};

// Legacy call frame for backward compatibility during transition
struct LegacyCallFrame {
    std::string functionName;
    size_t returnAddress;
    size_t basePointer;
    std::shared_ptr<Environment> environment;
};

#endif // VM_H