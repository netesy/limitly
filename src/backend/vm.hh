#ifndef VM_HH
#define VM_HH

#include <functional>
#include <unordered_set>

#include "../common/opcodes.hh"
#include "../frontend/ast.hh"
#include "../common/debugger.hh"
#include "memory.hh"
#include "value.hh"
#include "types.hh"
#include "functions.hh"
#include "classes.hh"
#include "type_system.hh"
#include "concurrency/scheduler.hh"
#include "concurrency/thread_pool.hh"
#include "concurrency/event_loop.hh"
#include "concurrency/concurrency_state.hh"
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
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
class TaskVM;

namespace backend {
    class VMMethodImplementation;
}

namespace builtin {
    class BuiltinFunctions;
}

// Virtual Machine class
class VM {
    friend class TaskVM;  // Allow TaskVM to access private members
    friend class builtin::BuiltinFunctions;  // Allow BuiltinFunctions to access private members
public:
    explicit VM(bool create_runtime = true);
    ~VM();
    
    // Execute bytecode
    ValuePtr execute(const std::vector<Instruction>& bytecode);
    
    // Pre-process bytecode to register lambda functions
    void preProcessBytecode(const std::vector<Instruction>& bytecode);
    
    // Set source information for enhanced error reporting
    void setSourceInfo(const std::string& sourceCode, const std::string& filePath) {
        this->sourceCode = sourceCode;
        this->filePath = filePath;
    }
    
    // Function to enable or disable debug output
    void setDebug(bool enable) { 
        debugMode = enable;
        debugOutput = enable;
    }
    
    // Register native function
    void registerNativeFunction(const std::string& name, std::function<ValuePtr(const std::vector<ValuePtr>&)> function);
    
    // Register builtin function (bypasses parameter validation)
    void registerBuiltinFunction(const std::string& name, std::function<ValuePtr(const std::vector<ValuePtr>&)> function);
    
    // Register VM-aware builtin function (for functions that need VM context)
    void registerVMBuiltinFunction(const std::string& name, std::function<ValuePtr(VM*, const std::vector<ValuePtr>&)> function);
    
    // Register user-defined function from AST
    void registerUserFunction(const std::shared_ptr<AST::FunctionDeclaration>& decl);
    
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
    
    // Source information for enhanced error reporting
    std::string sourceCode;
    std::string filePath;
    
    std::unordered_map<std::string, std::function<ValuePtr(const std::vector<ValuePtr>&)>> nativeFunctions;
    backend::FunctionRegistry functionRegistry; 
    backend::ClassRegistry classRegistry; // Class management
    std::unordered_map<std::string, backend::Function> userDefinedFunctions; // Use the proper Function struct

    ValuePtr lastException;
    
    // Current execution state
    const std::vector<Instruction>* bytecode;
    size_t ip; // Instruction pointer
    bool debugMode;
    bool debugOutput;
    
    // Helper methods
    ValuePtr pop();
    void push(const ValuePtr& value);
    ValuePtr peek(int distance = 0) const;
    std::string valueToString(const ValuePtr& value);

private:
    void error(const std::string& message) const;
    
    // Instruction handlers
    void handlePushInt(const Instruction& instruction);
    void handlePushUint64(const Instruction& instruction);
    void handlePushFloat(const Instruction& instruction);
    void handlePushString(const Instruction& instruction);
    void handlePushBool(const Instruction& instruction);
    void handlePushNull(const Instruction& instruction);
    void handlePop(const Instruction& instruction);
    void handleStoreVar(const Instruction& instruction);
    void handleLoadVar(const Instruction& instruction);
    void handleAdd(const Instruction& instruction);
    void handleSubtract(const Instruction& instruction);
    void handleMultiply(const Instruction& instruction);
    void handleDivide(const Instruction& instruction);
    void handleCall(const Instruction& instruction);
    void handleReturn(const Instruction& instruction);
    void handleJump(const Instruction& instruction);
    void handleJumpIfFalse(const Instruction& instruction);
    void handlePrint(const Instruction& instruction);
};

#endif // VM_HH