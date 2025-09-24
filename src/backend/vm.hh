#ifndef VM_H
#define VM_H

#include "../opcodes.hh"
#include "../frontend/ast.hh"
#include "../debugger.hh"
#include "memory.hh"
#include "value.hh"
#include "types.hh"
#include "functions.hh"
#include "classes.hh"
#include "concurrency/scheduler.hh"
#include "concurrency/thread_pool.hh"
#include "concurrency/event_loop.hh"
#include "concurrency/concurrency_state.hh"
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
    
    // Error handling state - optimized for zero-cost success path
    struct ErrorFrame {
        size_t handlerAddress;      // Bytecode address of error handler
        size_t stackBase;           // Stack position when frame created
        TypePtr expectedErrorType;  // Expected error type for this frame
        std::string functionName;   // Function name for debugging
        
        // Optimization: pack small data for better cache efficiency
        ErrorFrame(size_t addr, size_t base, TypePtr type, const std::string& name = "")
            : handlerAddress(addr), stackBase(base), expectedErrorType(type), functionName(name) {}
    };
    
    // Optimized error frame stack - use small vector optimization for common case
    static constexpr size_t INLINE_ERROR_FRAMES = 8;  // Most functions have shallow error nesting
    std::vector<ErrorFrame> errorFrames;
    
    // Performance counters for zero-cost validation
    struct ErrorHandlingStats {
        size_t successPathExecutions = 0;
        size_t errorPathExecutions = 0;
        size_t errorFramePushes = 0;
        size_t errorFramePops = 0;
        size_t errorValueAllocations = 0;
        size_t errorValuePoolHits = 0;
        size_t errorValuePoolMisses = 0;
        
        void reset() {
            successPathExecutions = 0;
            errorPathExecutions = 0;
            errorFramePushes = 0;
            errorFramePops = 0;
            errorValueAllocations = 0;
            errorValuePoolHits = 0;
            errorValuePoolMisses = 0;
        }
        
        double getSuccessPathRatio() const {
            size_t total = successPathExecutions + errorPathExecutions;
            return total > 0 ? static_cast<double>(successPathExecutions) / total : 0.0;
        }
        
        double getPoolHitRatio() const {
            size_t total = errorValuePoolHits + errorValuePoolMisses;
            return total > 0 ? static_cast<double>(errorValuePoolHits) / total : 0.0;
        }
    };
    mutable ErrorHandlingStats errorStats;
    
    // Error value pool for reducing allocations - optimized for performance
    struct ErrorValuePool {
        std::vector<std::unique_ptr<ErrorValue>> pool;
        std::vector<bool> inUse;  // Track which slots are in use
        size_t nextFreeIndex = 0;
        static constexpr size_t POOL_SIZE = 64;  // Increased pool size for better performance
        static constexpr size_t POOL_GROWTH_SIZE = 16;  // Grow pool in chunks
        
        ErrorValuePool() {
            pool.reserve(POOL_SIZE);
            inUse.reserve(POOL_SIZE);
        }
        
        ErrorValue* acquire() {
            // Fast path: check if we have a free slot at nextFreeIndex
            if (nextFreeIndex < pool.size() && !inUse[nextFreeIndex]) {
                inUse[nextFreeIndex] = true;
                return pool[nextFreeIndex++].get();
            }
            
            // Slower path: find first free slot
            for (size_t i = 0; i < pool.size(); ++i) {
                if (!inUse[i]) {
                    inUse[i] = true;
                    nextFreeIndex = i + 1;
                    return pool[i].get();
                }
            }
            
            // No free slots, grow the pool
            if (pool.size() < POOL_SIZE) {
                size_t oldSize = pool.size();
                size_t newSize = std::min(POOL_SIZE, oldSize + POOL_GROWTH_SIZE);
                
                pool.resize(newSize);
                inUse.resize(newSize, false);
                
                for (size_t i = oldSize; i < newSize; ++i) {
                    pool[i] = std::make_unique<ErrorValue>();
                }
                
                inUse[oldSize] = true;
                nextFreeIndex = oldSize + 1;
                return pool[oldSize].get();
            }
            
            // Pool exhausted, allocate new (fallback)
            return new ErrorValue();
        }
        
        void release(ErrorValue* error) {
            if (!error) return;
            
            // Find the error in our pool
            for (size_t i = 0; i < pool.size(); ++i) {
                if (pool[i].get() == error) {
                    // Reset the error value for reuse
                    error->errorType.clear();
                    error->message.clear();
                    error->arguments.clear();
                    error->sourceLocation = 0;
                    
                    inUse[i] = false;
                    nextFreeIndex = std::min(nextFreeIndex, i);
                    return;
                }
            }
            
            // Not from our pool, delete it
            delete error;
        }
        
        void clear() {
            std::fill(inUse.begin(), inUse.end(), false);
            nextFreeIndex = 0;
        }
        
        size_t getUsedCount() const {
            return std::count(inUse.begin(), inUse.end(), true);
        }
        
        size_t getTotalCount() const {
            return pool.size();
        }
    };
    ErrorValuePool errorPool;
    std::unordered_map<std::string, std::function<ValuePtr(const std::vector<ValuePtr>&)>> nativeFunctions;
    // Removed duplicate userFunctions map - using functionRegistry instead
    backend::FunctionRegistry functionRegistry; // New function abstraction layer
    backend::ClassRegistry classRegistry; // Class management
    std::unordered_map<std::string, backend::Function> userDefinedFunctions; // Use the proper Function struct
    std::vector<ValuePtr> tempValues;
    ValuePtr lastException;
    
    // Task iteration state
    std::string currentTaskLoopVar;
    ValuePtr currentTaskIterable;
    
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

    // Module loading state
    struct ImportState {
        std::string modulePath;
        std::optional<std::string> alias;
        std::optional<AST::ImportFilterType> filterType;
        std::vector<std::string> filterIdentifiers;
    };
    ImportState currentImportState;
    std::unordered_map<std::string, ValuePtr> loadedModules;
    
    // Module function handling
    struct ModuleFunctionInfo {
        backend::Function functionInfo;
        std::shared_ptr<Environment> moduleEnv;
        std::vector<Instruction> moduleBytecode;
    };
    std::unordered_map<Environment*, std::unordered_map<std::string, backend::Function>> moduleUserDefinedFunctions;
    std::unordered_map<std::string, ModuleFunctionInfo> moduleFunctions_;

    // Concurrency runtime - replaced with integrated state
    std::unique_ptr<ConcurrencyState> concurrency_state;
    
    // Helper methods
    ValuePtr pop();
    void push(const ValuePtr& value);
    ValuePtr peek(int distance = 0) const;
    std::string valueToString(const ValuePtr& value);
    
    // Error handling helper methods
    void pushErrorFrame(size_t handlerAddr, TypePtr errorType, const std::string& functionName = "");
    void popErrorFrame();
    bool propagateError(ValuePtr errorValue);
    ValuePtr handleError(ValuePtr errorValue, const std::string& expectedType = "");
    bool functionCanFail(const std::string& functionName) const;
    
    // Error value creation helpers - optimized for performance
    ValuePtr createErrorValue(const std::string& errorType, const std::string& message = "", 
                             const std::vector<ValuePtr>& args = {});
    ValuePtr createSuccessValue(ValuePtr value);
    bool isErrorFrame(size_t frameIndex) const;
    
    // Zero-cost success path optimizations
    inline bool hasErrorFrames() const noexcept { return !errorFrames.empty(); }
    inline bool isSuccessPath() const noexcept { return errorFrames.empty(); }
    
    // Fast error checking without virtual calls - optimized for branch prediction
    inline bool isErrorValue(const ValuePtr& value) const noexcept {
        // Most values are not errors, so optimize for the success case
        if (!value) [[unlikely]] return false;
        if (!value->type) [[unlikely]] return false;
        
        // Fast path for non-error union types
        if (value->type->tag != TypeTag::ErrorUnion) [[likely]] {
            return std::holds_alternative<ErrorValue>(value->data);
        }
        
        // Error union path
        return std::holds_alternative<ErrorValue>(value->data);
    }
    
    // Optimized error union operations
    ValuePtr createOptimizedErrorUnion(ValuePtr successValue, const std::string& errorType = "");
    ValuePtr createPooledErrorValue(const std::string& errorType, const std::string& message = "");
    void releasePooledError(ValuePtr errorValue);
    
    // Performance monitoring methods
    void recordSuccessPath() const { ++errorStats.successPathExecutions; }
    void recordErrorPath() const { ++errorStats.errorPathExecutions; }
    const ErrorHandlingStats& getErrorStats() const { return errorStats; }
    void resetErrorStats() { errorStats.reset(); }
    
public:
    // Debugging methods
    void printStack() const;
    void printErrorStats() const;
    
    std::shared_ptr<ThreadPool> getThreadPool() { 
        return concurrency_state ? concurrency_state->runtime->getThreadPool() : nullptr; 
    }
    
    // Additional concurrency accessors
    ConcurrencyState* getConcurrencyState() { return concurrency_state.get(); }
    ConcurrencyRuntime* getConcurrencyRuntime() { 
        return concurrency_state ? concurrency_state->runtime.get() : nullptr; 
    }

private:
    void error(const std::string& message) const;
    
    // Helper function for iterator creation
    std::shared_ptr<IteratorValue> createIterator(ValuePtr iterable);
    bool hasNext(std::shared_ptr<IteratorValue> iterator);
    ValuePtr next(std::shared_ptr<IteratorValue> iterator);
    
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
    void handlePushFunction(const Instruction& instruction);
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
    void handleIteratorCreate(const Instruction& instruction);
    void handleIteratorHasNext(const Instruction& instruction);
    void handleIteratorNext(const Instruction& instruction);
    void handleIteratorNextKeyValue(const Instruction& instruction);
    void handleBeginScope(const Instruction& instruction);
    void handleEndScope(const Instruction& instruction);
    
    // Helper function for value comparison
    bool valuesEqual(const ValuePtr& a, const ValuePtr& b) const;
    
    // Helper function for parameter binding in function calls
    bool bindFunctionParameters(const backend::Function& func, const std::vector<ValuePtr>& args, 
                               std::shared_ptr<Environment> funcEnv, const std::string& funcName);
    
    // Helper function for consistent call frame management
    void createAndPushCallFrame(const std::string& funcName, size_t returnAddress, 
                               std::shared_ptr<Environment> funcEnv);
    
    // Concurrency helper methods
    void parseBlockParameters(const std::string& paramString, BlockExecutionState& state);
    void waitForTasksToComplete(BlockExecutionState& state);
    void collectTaskResults(BlockExecutionState& state);
    void handleCollectedErrors(BlockExecutionState& state);
    void cleanupBlockResources(BlockExecutionState& state);
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
    void handleBeginTask(const Instruction& instruction);
    void handleEndTask(const Instruction& instruction);
    void handleStoreIterable(const Instruction& instruction);
    void handleAwait(const Instruction& instruction);
    void handleMatchPattern(const Instruction& instruction);
    
    // Destructuring pattern helpers
    bool handleDictPatternMatch(const ValuePtr& value);
    bool handleListPatternMatch(const ValuePtr& value);
    bool handleTuplePatternMatch(const ValuePtr& value);
    void clearDictPatternFromStack();
    void clearListPatternFromStack();
    
    // Error pattern matching helpers
    bool handleValPatternMatch(const ValuePtr& value);
    bool handleErrPatternMatch(const ValuePtr& value);
    bool handleErrorTypePatternMatch(const ValuePtr& value);
    
    void handleImportModule(const Instruction& instruction);
    void handleImportAlias(const Instruction& instruction);
    void handleImportFilterShow(const Instruction& instruction);
    void handleImportFilterHide(const Instruction& instruction);
    void handleImportAddIdentifier(const Instruction& instruction);
    void handleImportExecute(const Instruction& instruction);
    void executeFunction(ValuePtr functionValue, const std::vector<ValuePtr>& args);
    void handleBeginEnum(const Instruction& instruction);
    void handleEndEnum(const Instruction& instruction);
    void handleDefineEnumVariant(const Instruction& instruction);
    void handleDefineEnumVariantWithType(const Instruction& instruction);
    void handlePrint(const Instruction& instruction);
    void handleDebugPrint(const Instruction& instruction);
    void handleDefineAtomic(const Instruction& instruction);
    
    // Error handling instruction handlers
    void handleCheckError(const Instruction& instruction);
    void handlePropagateError(const Instruction& instruction);
    void handleConstructError(const Instruction& instruction);
    void handleConstructOk(const Instruction& instruction);
    void handleIsError(const Instruction& instruction);
    void handleIsSuccess(const Instruction& instruction);
    void handleUnwrapValue(const Instruction& instruction);
};

// VM-specific user-defined function implementation
class VMUserDefinedFunction : public backend::UserDefinedFunction {
    friend class VM;
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
    
    std::unordered_map<std::string, ValuePtr> getAllSymbols() {
        std::lock_guard<std::mutex> lock(mutex);
        return values; // Return a copy
    }
    
    void remove(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = values.find(name);
        if (it != values.end()) {
            values.erase(it);
        } else {
            throw std::runtime_error("Symbol '" + name + "' not found");
        }
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