#include "vm.hh"
#include "value.hh"  // For Value and ErrorValue definitions

// Forward declare ErrorValue from the global namespace
struct ErrorValue;
#include <iostream>
#include <thread>
#include <variant>
#include <limits>
#include <string>
#include <memory>
#include <functional>
#include <cstdint>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <type_traits>
#include <cassert>

// Enable C++17 features
#if __cplusplus < 201703L
#error "This code requires C++17 or later"
#endif

// Required for std::get with variants
#if __cplusplus >= 201703L
namespace std {
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
}
#endif

// Helper function to convert TypeTag to string
static std::string typeTagToString(TypeTag tag) {
    switch (tag) {
        case TypeTag::Nil: return "Nil";
        case TypeTag::Bool: return "Bool";
        case TypeTag::Int: return "Int";
        case TypeTag::Int8: return "Int8";
        case TypeTag::Int16: return "Int16";
        case TypeTag::Int32: return "Int32";
        case TypeTag::Int64: return "Int64";
        case TypeTag::UInt: return "UInt";
        case TypeTag::UInt8: return "UInt8";
        case TypeTag::UInt16: return "UInt16";
        case TypeTag::UInt32: return "UInt32";
        case TypeTag::UInt64: return "UInt64";
        case TypeTag::Float32: return "Float32";
        case TypeTag::Float64: return "Float64";
        case TypeTag::String: return "String";
        case TypeTag::List: return "List";
        case TypeTag::Dict: return "Dict";
        case TypeTag::Enum: return "Enum";
        case TypeTag::Function: return "Function";
        case TypeTag::Any: return "Any";
        case TypeTag::Sum: return "Sum";
        case TypeTag::Union: return "Union";
        case TypeTag::UserDefined: return "UserDefined";
        default: return "Unknown";
    }
}

int VM::matchCounter = 0;

// VM implementation
// VMUserDefinedFunction implementation
VMUserDefinedFunction::VMUserDefinedFunction(VM* vmInstance, const std::shared_ptr<AST::FunctionDeclaration>& decl, 
                                           size_t start, size_t end)
    : backend::UserDefinedFunction(decl), vm(vmInstance), startAddress(start), endAddress(end) {
}

VMUserDefinedFunction::VMUserDefinedFunction(VM* vmInstance, const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl,
                                           size_t start, size_t end)
    : backend::UserDefinedFunction(decl), vm(vmInstance), startAddress(start), endAddress(end) {
}

ValuePtr VMUserDefinedFunction::execute(const std::vector<ValuePtr>& args) {
    // This will be called by the VM's function call mechanism
    // The actual execution happens in the VM's handleCall method
    // This is just a placeholder that shouldn't be called directly
    return nullptr;
}

VM::VM(bool create_runtime)
    : memoryManager(1024u && 1024u), // 1MB initial memory
      region(std::make_unique<MemoryManager<>::Region>(memoryManager)),
      typeSystem(new TypeSystem(memoryManager, *region)),
      globals(std::make_shared<Environment>()),
      environment(globals),
      bytecode(nullptr),
      ip(0),
    debugMode(true),
    debugOutput(false),
      currentFunctionBeingDefined(""),
      insideFunctionDefinition(false),
      currentClassBeingDefined(""),
      insideClassDefinition(false) {
    
    if (create_runtime) {
        // Initialize and start the concurrency runtime
        scheduler = std::make_shared<Scheduler>();
        size_t num_threads = std::thread::hardware_concurrency();
        thread_pool = std::make_shared<ThreadPool>(num_threads > 0 ? num_threads : 2, scheduler);
        thread_pool->start();
        event_loop = std::make_shared<EventLoop>();
    }

    // Register native functions with correct signature
    registerNativeFunction("clock", [this](const std::vector<ValuePtr>& args) -> ValuePtr {
        if (args.size() != 0) {
            throw std::runtime_error("clock() takes no arguments");
        }
        return memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, 
            static_cast<double>(std::clock()) / CLOCKS_PER_SEC);
    });
    
    registerNativeFunction("sleep", [this](const std::vector<ValuePtr>& args) -> ValuePtr {
        if (args.size() != 1) {
            throw std::runtime_error("sleep() takes exactly one number argument");
        }
        
        // Convert the argument to a double value
        double seconds = 0.0;
        if (args[0]->type->tag == TypeTag::Float64) {
            seconds = *reinterpret_cast<const double*>(&args[0]->data);
        } else if (args[0]->type->tag == TypeTag::Int) {
            int32_t val = *reinterpret_cast<const int32_t*>(&args[0]->data);
            seconds = static_cast<double>(val);
        } else {
            throw std::runtime_error("sleep() argument must be a number (int or float)");
        }
        
        // Sleep for the specified number of seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(
            static_cast<int>(seconds * 1000)));
            
        return memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
    });
    
        // Register a native function for channel creation
        registerNativeFunction("channel", [this](const std::vector<ValuePtr>& args) -> ValuePtr {
                // Create a new Channel<ValuePtr> and wrap it in a VM value
                auto ch = std::make_shared<Channel<ValuePtr>>();
                // Use ANY_TYPE for now as channel's type
                return memoryManager.makeRef<Value>(*region, typeSystem->ANY_TYPE, ch);
        });

        // Register free functions for channel operations
        registerNativeFunction("send", [this](const std::vector<ValuePtr>& args) -> ValuePtr {
            if (args.size() != 2) throw std::runtime_error("send(channel, value) expects 2 args");
            auto chVal = args[0];
            if (!std::holds_alternative<std::shared_ptr<Channel<ValuePtr>>>(chVal->data)) {
                throw std::runtime_error("First argument to send must be a channel");
            }
            auto ch = std::get<std::shared_ptr<Channel<ValuePtr>>>(chVal->data);
            ch->send(args[1]);
            return memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
        });

        registerNativeFunction("receive", [this](const std::vector<ValuePtr>& args) -> ValuePtr {
            if (args.size() != 1) throw std::runtime_error("receive(channel) expects 1 arg");
            auto chVal = args[0];
            if (!std::holds_alternative<std::shared_ptr<Channel<ValuePtr>>>(chVal->data)) {
                throw std::runtime_error("Argument to receive must be a channel");
            }
            auto ch = std::get<std::shared_ptr<Channel<ValuePtr>>>(chVal->data);
            ValuePtr v;
            bool ok = ch->receive(v);
            if (!ok) return memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
            return v;
        });

        registerNativeFunction("close", [this](const std::vector<ValuePtr>& args) -> ValuePtr {
            if (args.size() != 1) throw std::runtime_error("close(channel) expects 1 arg");
            auto chVal = args[0];
            if (!std::holds_alternative<std::shared_ptr<Channel<ValuePtr>>>(chVal->data)) {
                throw std::runtime_error("Argument to close must be a channel");
            }
            auto ch = std::get<std::shared_ptr<Channel<ValuePtr>>>(chVal->data);
            ch->close();
            return memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
        });
}

VM::~VM() {
    if (thread_pool) {
        thread_pool->stop();
    }
    delete typeSystem;
}

// Register a native function both in the VM native map and the backend function registry
void VM::registerNativeFunction(const std::string& name, std::function<ValuePtr(const std::vector<ValuePtr>&)> function) {
    nativeFunctions[name] = function;

    // Register in the backend function registry with no parameters for now.
    std::vector<backend::Parameter> params;
    functionRegistry.registerNativeFunction(name, params, std::nullopt, function);
}

ValuePtr VM::execute(const std::vector<Instruction>& code) {
    this->bytecode = &code;
    ip = 0;
    const std::vector<Instruction>& bytecodeRef = *this->bytecode;
    
    try {
        bool verboseTracing = false; // set true manually for full opcode traces
        while (ip < bytecodeRef.size()) {
            const Instruction& instruction = bytecodeRef[ip];
            
            // Check if we need to start skipping function body
            if (!currentFunctionBeingDefined.empty() && !insideFunctionDefinition) {
                auto funcIt = userDefinedFunctions.find(currentFunctionBeingDefined);
                if (funcIt != userDefinedFunctions.end() && ip >= funcIt->second.startAddress) {
                    insideFunctionDefinition = true;
                }
            }
            
            // Skip execution if we're inside a function definition (except for END_FUNCTION)
            if (insideFunctionDefinition && instruction.opcode != Opcode::END_FUNCTION) {
                ip++;
                continue;
            }
            
            // Debug output for opcode values
            int opcodeValue = static_cast<int>(instruction.opcode);
            // Tracing is disabled by default to keep runtime output clean.
            
            try {
                switch (instruction.opcode) {
                    case Opcode::PUSH_INT:
                        handlePushInt(instruction);
                        break;
                    case Opcode::PUSH_FLOAT:
                        handlePushFloat(instruction);
                        break;
                    case Opcode::PUSH_STRING:
                        handlePushString(instruction);
                        break;
                    case Opcode::PUSH_BOOL:
                        handlePushBool(instruction);
                        break;
                    case Opcode::PUSH_NULL:
                        handlePushNull(instruction);
                        break;
                    case Opcode::POP:
                        handlePop(instruction);
                        break;
                    case Opcode::DUP:
                        handleDup(instruction);
                        break;
                    case Opcode::SWAP:
                        handleSwap(instruction);
                        break;
                    case Opcode::STORE_VAR:
                        handleStoreVar(instruction);
                        break;
                    case Opcode::LOAD_VAR:
                        handleLoadVar(instruction);
                        break;
                    case Opcode::STORE_TEMP:
                        handleStoreTemp(instruction);
                        break;
                    case Opcode::LOAD_TEMP:
                        handleLoadTemp(instruction);
                        break;
                    case Opcode::CLEAR_TEMP:
                        handleClearTemp(instruction);
                        break;
                    case Opcode::ADD:
                        handleAdd(instruction);
                        break;
                    case Opcode::SUBTRACT:
                        handleSubtract(instruction);
                        break;
                    case Opcode::MULTIPLY:
                        handleMultiply(instruction);
                        break;
                    case Opcode::DIVIDE:
                        handleDivide(instruction);
                        break;
                    case Opcode::MODULO:
                        handleModulo(instruction);
                        break;
                    case Opcode::NEGATE:
                        handleNegate(instruction);
                        break;
                    case Opcode::EQUAL:
                        handleEqual(instruction);
                        break;
                    case Opcode::NOT_EQUAL:
                        handleNotEqual(instruction);
                        break;
                    case Opcode::LESS:
                        handleLess(instruction);
                        break;
                    case Opcode::LESS_EQUAL:
                        handleLessEqual(instruction);
                        break;
                    case Opcode::GREATER:
                        handleGreater(instruction);
                        break;
                    case Opcode::GREATER_EQUAL:
                        handleGreaterEqual(instruction);
                        break;
                    case Opcode::AND:
                        handleAnd(instruction);
                        break;
                    case Opcode::OR:
                        handleOr(instruction);
                        break;
                    case Opcode::NOT:
                        handleNot(instruction);
                        break;
                    case Opcode::INTERPOLATE_STRING:
                        handleInterpolateString(instruction);
                        break;
                    case Opcode::CONCAT:
                        handleConcat(instruction);
                        break;
                    case Opcode::JUMP:
                        handleJump(instruction);
                        break;
                    case Opcode::JUMP_IF_TRUE:
                        handleJumpIfTrue(instruction);
                        break;
                    case Opcode::JUMP_IF_FALSE:
                        handleJumpIfFalse(instruction);
                        break;
                    case Opcode::CALL:
                        handleCall(instruction);
                        break;
                    case Opcode::RETURN:
                        handleReturn(instruction);
                        break;
                    case Opcode::BEGIN_FUNCTION:
                        handleBeginFunction(instruction);
                        break;
                    case Opcode::END_FUNCTION:
                        handleEndFunction(instruction);
                        break;
                    case Opcode::DEFINE_PARAM:
                        handleDefineParam(instruction);
                        break;
                    case Opcode::DEFINE_OPTIONAL_PARAM:
                        handleDefineOptionalParam(instruction);
                        break;
                    case Opcode::SET_DEFAULT_VALUE:
                        handleSetDefaultValue(instruction);
                        break;
                    case Opcode::PRINT:
                        handlePrint(instruction);
                        break;
                    case Opcode::CREATE_LIST:
                        handleCreateList(instruction);
                        break;
                    case Opcode::LIST_APPEND:
                        handleListAppend(instruction);
                        break;
                    case Opcode::CREATE_DICT:
                        handleCreateDict(instruction);
                        break;
                    case Opcode::DICT_SET:
                        handleDictSet(instruction);
                        break;
                    case Opcode::GET_INDEX:
                        handleGetIndex(instruction);
                        break;
                    case Opcode::SET_INDEX:
                        handleSetIndex(instruction);
                        break;
                    case Opcode::CREATE_RANGE:
                        handleCreateRange(instruction);
                        break;
                    case Opcode::GET_ITERATOR:
                        handleGetIterator(instruction);
                        break;
                    case Opcode::ITERATOR_HAS_NEXT:
                        handleIteratorHasNext(instruction);
                        break;
                    case Opcode::ITERATOR_NEXT:
                        handleIteratorNext(instruction);
                        break;
                    case Opcode::ITERATOR_NEXT_KEY_VALUE:
                        handleIteratorNextKeyValue(instruction);
                        break;
                    case Opcode::BEGIN_CLASS:
                        handleBeginClass(instruction);
                        break;
                    case Opcode::END_CLASS:
                        handleEndClass(instruction);
                        break;
                    case Opcode::SET_SUPERCLASS:
                        handleSetSuperclass(instruction);
                        break;
                    case Opcode::DEFINE_FIELD:
                        handleDefineField(instruction);
                        break;
                    case Opcode::DEFINE_ATOMIC:
                        handleDefineAtomic(instruction);
                        break;
                    case Opcode::LOAD_THIS:
                        handleLoadThis(instruction);
                        break;
                    case Opcode::LOAD_SUPER:
                        handleLoadSuper(instruction);
                        break;
                    case Opcode::GET_PROPERTY:
                        handleGetProperty(instruction);
                        break;
                    case Opcode::SET_PROPERTY:
                        handleSetProperty(instruction);
                        break;
                    case Opcode::BEGIN_SCOPE:
                        // No action needed for BEGIN_SCOPE in this implementation
                        break;
                    case Opcode::END_SCOPE:
                        // No action needed for END_SCOPE in this implementation
                        break;
                    case Opcode::MATCH_PATTERN:
                        handleMatchPattern(instruction);
                        break;
                    case Opcode::BEGIN_PARALLEL:
                        handleBeginParallel(instruction);
                        break;
                    case Opcode::END_PARALLEL:
                        handleEndParallel(instruction);
                        break;
                    case Opcode::BEGIN_CONCURRENT:
                        handleBeginConcurrent(instruction);
                        break;
                    case Opcode::END_CONCURRENT:
                        handleEndConcurrent(instruction);
                        break;
                        case Opcode::BEGIN_TRY:
                            handleBeginTry(instruction);
                            break;
                        case Opcode::END_TRY:
                            handleEndTry(instruction);
                            break;
                        case Opcode::BEGIN_HANDLER:
                            handleBeginHandler(instruction);
                            break;
                        case Opcode::END_HANDLER:
                            handleEndHandler(instruction);
                            break;
                        case Opcode::THROW:
                            handleThrow(instruction);
                            break;
                        case Opcode::STORE_EXCEPTION:
                            handleStoreException(instruction);
                            break;
                        case Opcode::AWAIT:
                            handleAwait(instruction);
                            break;
                        case Opcode::IMPORT:
                            handleImport(instruction);
                            break;
                        case Opcode::BEGIN_ENUM:
                            handleBeginEnum(instruction);
                            break;
                        case Opcode::END_ENUM:
                            handleEndEnum(instruction);
                            break;
                        case Opcode::DEFINE_ENUM_VARIANT:
                            handleDefineEnumVariant(instruction);
                            break;
                        case Opcode::DEFINE_ENUM_VARIANT_WITH_TYPE:
                            handleDefineEnumVariantWithType(instruction);
                            break;
                        case Opcode::DEBUG_PRINT:
                            handleDebugPrint(instruction);
                            break;
                        case Opcode::CHECK_ERROR:
                            handleCheckError(instruction);
                            break;
                        case Opcode::PROPAGATE_ERROR:
                            handlePropagateError(instruction);
                            break;
                        case Opcode::CONSTRUCT_ERROR:
                            handleConstructError(instruction);
                            break;
                        case Opcode::CONSTRUCT_OK:
                            handleConstructOk(instruction);
                            break;
                        case Opcode::IS_ERROR:
                            handleIsError(instruction);
                            break;
                        case Opcode::IS_SUCCESS:
                             handleIsSuccess(instruction);
                             break;    
                        case Opcode::UNWRAP_VALUE:
                             handleUnwrapValue(instruction);
                              break;         
                        case Opcode::BREAK:
                          //  handleBreak(instruction);
                            break;
                        case Opcode::CONTINUE:
                         //   handleContinue(instruction);
                            break;    
                        case Opcode::SET_RANGE_STEP:
                           // handleSetRangeStep(instruction);
                            break;
                        case Opcode::BEGIN_TASK:
                           // handleBeginTask(instruction);
                            break;    
                        case Opcode::END_TASK:
                          //  handleEndTask(instruction);
                            break;    
                        case Opcode::BEGIN_WORKER:
                           // handleBeginWorker(instruction);
                            break;    
                        case Opcode::END_WORKER:
                           // handleEndWorker(instruction);
                            break;    
                        case Opcode::STORE_ITERABLE:
                            //handleStoreIterable(instruction);
                            break;    
                        case Opcode::LOAD_CONST :
                           // handleLoadConst(instruction);
                            break;      
                        case Opcode::STORE_CONST:
                           // handleStoreConst(instruction);
                            break;      
                        case Opcode::LOAD_MEMBER:
                            //handleLoadMember(instruction);
                            break;      
                        case Opcode::STORE_MEMBER:
                          //  handleStoreMember(instruction);
                            break;
                         
                        case Opcode::HALT:
                            return stack.empty() ? memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE) : stack.back();
                        default:
                            error("Unknown opcode: " + std::to_string(static_cast<int>(instruction.opcode)));
                            break;        
     
                }
            } catch (const std::exception& e) {
                // Handle any exceptions that occur during instruction execution
                error("Error executing instruction: " + std::string(e.what()));
            }
            ip++;
        }
    } catch (const std::exception& e) {
        // Handle any exceptions that occur during execution
        error("Error executing bytecode: " + std::string(e.what()));
    }
    return nullptr;
}


//     nativeFunctions[name] = function;
    
//     // Also register with the function registry for consistency
//     std::vector<backend::Parameter> params; // Empty for now, could be enhanced
//     functionRegistry.registerNativeFunction(name, params, std::nullopt, function);
// }

void VM::registerUserFunction(const std::shared_ptr<AST::FunctionDeclaration>& decl) {
    functionRegistry.registerFunction(decl);
}

void VM::registerUserFunction(const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl) {
    functionRegistry.registerFunction(decl);
}

ValuePtr VM::pop() {
    if (stack.empty()) {
        error("Stack underflow");
    }
    
    ValuePtr value = stack.back();
    stack.pop_back();
    return value;
}

void VM::push(const ValuePtr& value) {
    stack.push_back(value);
}

ValuePtr VM::peek(int distance) const {
    if (stack.size() <= static_cast<size_t>(distance)) {
        error("Stack underflow");
    }
    
    return stack[stack.size() - 1 - distance];
}

void VM::printStack() const {
    if (stack.empty()) {
        std::cout << "Stack is empty" << std::endl;
        return;
    }
    
    std::cout << "=== Stack (" << stack.size() << " items) ===" << std::endl;
    for (int i = stack.size() - 1; i >= 0; --i) {
        std::cout << "[" << i << "]: " << stack[i]->toString();
        if (stack[i]->type) {
            std::cout << " (" << stack[i]->type->toString() << ")";
        }
        std::cout << std::endl;
    }
    std::cout << "====================" << std::endl;
}

void VM::error(const std::string& message) const {
    throw std::runtime_error(message);
}

// Error handling helper methods
void VM::pushErrorFrame(size_t handlerAddr, TypePtr errorType, const std::string& functionName) {
    ErrorFrame frame;
    frame.handlerAddress = handlerAddr;
    frame.stackBase = stack.size();
    frame.expectedErrorType = errorType;
    frame.functionName = functionName;
    errorFrames.push_back(frame);
    // debug: pushErrorFrame logging removed to reduce noise
}

void VM::popErrorFrame() {
    if (!errorFrames.empty()) {
        errorFrames.pop_back();
    }
}

bool VM::propagateError(ValuePtr errorValue) {
    if (!errorValue) return false;

    // Extract error type string
    std::string errorType;
    if (auto ev = errorValue->getErrorValue()) {
        errorType = ev->errorType;
    } else if (errorValue->type && errorValue->type->tag == TypeTag::ErrorUnion) {
        if (auto ev = errorValue->getErrorValue()) errorType = ev->errorType;
        else return false;
    } else {
        return false;
    }

    if (errorFrames.empty()) {
        // No error frames available
        return false;
    }

    // Walk frames from top to bottom
    while (!errorFrames.empty()) {
        ErrorFrame frame = errorFrames.back();

    // checking frame

        // Wildcard frame matches any error
        if (!frame.expectedErrorType) {
            // Consume the frame so it won't be reused
            errorFrames.pop_back();
            ip = frame.handlerAddress - 1;
            while (stack.size() > frame.stackBase) stack.pop_back();
            push(errorValue);
            return true;
        }

        // ErrorUnion expected type treats as wildcard
        if (frame.expectedErrorType->tag == TypeTag::ErrorUnion) {
            errorFrames.pop_back();
            ip = frame.handlerAddress - 1;
            while (stack.size() > frame.stackBase) stack.pop_back();
            push(errorValue);
            return true;
        }

        // Try to match user-defined or named type
        bool matched = false;
        if (frame.expectedErrorType->tag == TypeTag::UserDefined) {
            if (std::holds_alternative<UserDefinedType>(frame.expectedErrorType->extra)) {
                const UserDefinedType& ud = std::get<UserDefinedType>(frame.expectedErrorType->extra);
                if (ud.name == errorType) matched = true;
            }
        } else if (frame.expectedErrorType->toString() == errorType) {
            matched = true;
        }

        if (matched) {
            errorFrames.pop_back();
            ip = frame.handlerAddress - 1;
            while (stack.size() > frame.stackBase) stack.pop_back();
            push(errorValue);
            return true;
        }

        // No match: pop and continue
    // frame did not match; popping frame
        errorFrames.pop_back();
    }

    return false;
}

ValuePtr VM::handleError(ValuePtr errorValue, const std::string& expectedType) {
    // Check if the error type matches the expected type
    if (!expectedType.empty()) {
        if (auto errorVal = std::get_if<ErrorValue>(&errorValue->data)) {
            if (errorVal->errorType != expectedType) {
                // Error type mismatch, continue propagation
                return errorValue;
            }
        }
    }
    
    return errorValue;
}

bool VM::functionCanFail(const std::string& functionName) const {
    // New/primary registry
    if (auto function = functionRegistry.getFunction(functionName)) {
        const auto& signature = function->getSignature();

        // 1) Explicit throws flag wins.
        if (signature.throws) {
            return true;
        }

        // 2) Return type from the AST annotation, if present.
        if (signature.returnType.has_value()) {
            const auto& annot = *signature.returnType; // shared_ptr<AST::TypeAnnotation>

            // If your TypeAnnotation already carries fallibility, use it directly:
            if (annot && annot->isFallible) {
                return true;
            }

            // (Optional) If your TypeAnnotation encodes error unions explicitly,
            // check that too (adjust field/enum names to your AST):
            // if (annot && annot->kind == AST::TypeAnnotation::Kind::ErrorUnion) {
            //     return true;
            // }
        }

        // (Optional, if you later add a resolved/runtime type alongside the AST):
        // if (auto resolved = function->getResolvedReturnType()) { // optional<TypePtr>
        //     return resolved.value()->tag == TypeTag::ErrorUnion;
        // }
    }

    // Legacy registry fallback
    if (auto it = userDefinedFunctions.find(functionName);
        it != userDefinedFunctions.end()) {
        const backend::Function& func = it->second;
        if (func.returnType) {
            return func.returnType->tag == TypeTag::ErrorUnion;
        }
    }

    return false;
}



// Instruction handlers
void VM::handlePushInt(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, instruction.intValue));
}

void VM::handlePushFloat(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, static_cast<double>(instruction.floatValue)));
}

void VM::handlePushString(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    push(memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, instruction.stringValue));
}

void VM::handlePushBool(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, instruction.boolValue));
}

void VM::handlePushNull(const Instruction& /*unused*/) {
    push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
}

void VM::handlePop(const Instruction& /*unused*/) {
    pop();
}

void VM::handleDup(const Instruction& /*unused*/) {
    push(peek());
}

void VM::handleSwap(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    push(b);
    push(a);
}

void VM::handleStoreVar(const Instruction& instruction) {
    ValuePtr value = pop();
    // If variable already exists and is an AtomicValue, perform atomic store
    try {
        ValuePtr existing = environment->get(instruction.stringValue);
        // Detect AtomicValue stored inside Value::data
        if (std::holds_alternative<AtomicValue>(existing->data)) {
            // Expect the incoming value to be an integer
            int64_t incoming = 0;
            if (value->type && (value->type->tag == TypeTag::Int || value->type->tag == TypeTag::Int64)) {
                if (value->type->tag == TypeTag::Int) incoming = static_cast<int64_t>(std::get<int32_t>(value->data));
                else incoming = std::get<int64_t>(value->data);
            } else {
                error("Cannot store non-integer into atomic variable");
            }
            AtomicValue& av = std::get<AtomicValue>(existing->data);
            av.inner->store(incoming);
            return;
        }
    } catch (...) {
        // variable doesn't exist yet; fallthrough to define
    }

    environment->define(instruction.stringValue, value);
}

void VM::handleDefineAtomic(const Instruction& instruction) {
    // Pop the initializer value and create an AtomicValue wrapper
    ValuePtr initVal = pop();
    int64_t initial = 0;
    if (initVal && initVal->type && (initVal->type->tag == TypeTag::Int || initVal->type->tag == TypeTag::Int64)) {
        if (initVal->type->tag == TypeTag::Int) initial = static_cast<int64_t>(std::get<int32_t>(initVal->data));
        else initial = std::get<int64_t>(initVal->data);
    } else if (initVal && initVal->type && initVal->type->tag == TypeTag::Float64) {
        // allow float to be truncated
        initial = static_cast<int64_t>(std::get<double>(initVal->data));
    } else if (!initVal) {
        initial = 0;
    } else {
        error("Invalid initializer for atomic variable");
    }

    AtomicValue av(initial);
    // Wrap in a VM Value with ANY_TYPE (no dedicated atomic type yet)
    auto v = memoryManager.makeRef<Value>(*region, typeSystem->ANY_TYPE, av);
    environment->define(instruction.stringValue, v);
}

void VM::handleLoadVar(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    try {
        ValuePtr value = environment->get(instruction.stringValue);
        push(value);
    } catch (const std::exception& e) {
        error("Undefined variable '" + instruction.stringValue + "'");
    }
}

void VM::handleStoreTemp(const Instruction& instruction) {
    // Store the top value in a temporary variable at the specified index
    int index = instruction.intValue;
    
    // Ensure the tempValues vector is large enough
    if (index >= static_cast<int>(tempValues.size())) {
        tempValues.resize(index + 1, memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
    }
    
    tempValues[index] = pop();
}

void VM::handleLoadTemp(const Instruction& instruction) {
    // Load the temporary value from the specified index onto the stack
    int index = instruction.intValue;
    
    if (index < 0 || index >= static_cast<int>(tempValues.size())) {
        error("Invalid temporary variable index: " + std::to_string(index));
        return;
    }
    
    push(tempValues[index]);
}

void VM::handleClearTemp(const Instruction& instruction) {
    // Clear the temporary value at the specified index
    int index = instruction.intValue;
    
    if (index >= 0 && index < static_cast<int>(tempValues.size())) {
        tempValues[index] = memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
    }
}

// Helper function to convert a value to its string representation
std::string VM::valueToString(const ValuePtr& value) {
    if (!value) {
        return "nil";
    }
    // Use the Value's getRawString() method for string operations (no quotes)
    return value->getRawString();
}

void VM::handleAdd(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();

    // Atomic-aware addition: if left operand is an AtomicValue, perform atomic fetch_add
    if (std::holds_alternative<AtomicValue>(a->data)) {
        if (!(b->type && (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64))) {
            error("Cannot add non-integer to atomic variable");
        }
        int64_t bVal = (b->type->tag == TypeTag::Int) ? static_cast<int64_t>(std::get<int32_t>(b->data)) : std::get<int64_t>(b->data);
        AtomicValue& av = std::get<AtomicValue>(a->data);
        int64_t prev = av.inner->fetch_add(bVal);
        int64_t result = prev + bVal;
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT64_TYPE, result));
        return;
    }

    // String concatenation (if either operand is a string, convert the other to string)
    if (a->type->tag == TypeTag::String || b->type->tag == TypeTag::String) {
        std::string strA = valueToString(a);
        std::string strB = valueToString(b);
        std::string result = strA + strB;
        push(memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, std::move(result)));
        return;
    }

    // Check if either operand is a number for numeric addition
    bool aIsNumeric = (a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64 || a->type->tag == TypeTag::Float64);
    bool bIsNumeric = (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64 || b->type->tag == TypeTag::Float64);

    if (aIsNumeric && bIsNumeric) {
        // Numeric addition - promote to double if either operand is double
        if (a->type->tag == TypeTag::Float64 || b->type->tag == TypeTag::Float64) {
            // Convert to double if needed
            double aVal = (a->type->tag == TypeTag::Float64) ? 
                std::get<double>(a->data) : 
                static_cast<double>(std::get<int32_t>(a->data));

            double bVal = (b->type->tag == TypeTag::Float64) ? 
                std::get<double>(b->data) : 
                static_cast<double>(std::get<int32_t>(b->data));

            // Check for floating-point edge cases
            double result = aVal + bVal;
            push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, result));
        } else {
            // Integer addition with mixed int32/int64 support
            int64_t aVal, bVal;
            
            // Convert both operands to int64_t
            if (a->type->tag == TypeTag::Int) {
                aVal = static_cast<int64_t>(std::get<int32_t>(a->data));
            } else {
                aVal = std::get<int64_t>(a->data);
            }
            
            if (b->type->tag == TypeTag::Int) {
                bVal = static_cast<int64_t>(std::get<int32_t>(b->data));
            } else {
                bVal = std::get<int64_t>(b->data);
            }

            // Check for integer overflow using well-defined behavior
            if ((bVal > 0 && aVal > std::numeric_limits<int64_t>::max() - bVal) ||
                (bVal < 0 && aVal < std::numeric_limits<int64_t>::min() - bVal)) {
                error("Integer addition overflow");
            }

            push(memoryManager.makeRef<Value>(*region, typeSystem->INT64_TYPE, aVal + bVal));
        }
    } else {
        // If we get here, the operands are not compatible for addition
        error("Cannot add operands of types " + 
              typeTagToString(a->type->tag) + " and " + 
              typeTagToString(b->type->tag));
    }
}

void VM::handleSubtract(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();

    // Atomic-aware subtraction
    if (std::holds_alternative<AtomicValue>(a->data)) {
        if (!(b->type && (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64))) {
            error("Cannot subtract non-integer from atomic variable");
        }
        int64_t bVal = (b->type->tag == TypeTag::Int) ? static_cast<int64_t>(std::get<int32_t>(b->data)) : std::get<int64_t>(b->data);
        AtomicValue& av = std::get<AtomicValue>(a->data);
        int64_t prev = av.inner->fetch_sub(bVal);
        int64_t result = prev - bVal;
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT64_TYPE, result));
        return;
    }
    
    // Check if either operand is a number for numeric subtraction
    bool aIsNumeric = (a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64 || a->type->tag == TypeTag::Float64);
    bool bIsNumeric = (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64 || b->type->tag == TypeTag::Float64);
    
    if (!aIsNumeric || !bIsNumeric) {
        error("Both operands must be numbers for subtraction");
    }
    
    // Numeric subtraction - promote to double if either operand is double
    if (a->type->tag == TypeTag::Float64 || b->type->tag == TypeTag::Float64) {
        // Convert to double if needed
        double aVal = (a->type->tag == TypeTag::Float64) ? 
            std::get<double>(a->data) : 
            static_cast<double>(std::get<int32_t>(a->data));
        
        double bVal = (b->type->tag == TypeTag::Float64) ? 
            std::get<double>(b->data) : 
            static_cast<double>(std::get<int32_t>(b->data));
        
        // Check for floating-point edge cases
        double result = aVal - bVal;
        if (std::isinf(result)) {
            error("Floating-point subtraction resulted in infinity");
        }
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, result));
    } else {
        // Integer subtraction with mixed int32/int64 support
        int64_t aVal, bVal;
        
        // Convert both operands to int64_t
        if (a->type->tag == TypeTag::Int) {
            aVal = static_cast<int64_t>(std::get<int32_t>(a->data));
        } else {
            aVal = std::get<int64_t>(a->data);
        }
        
        if (b->type->tag == TypeTag::Int) {
            bVal = static_cast<int64_t>(std::get<int32_t>(b->data));
        } else {
            bVal = std::get<int64_t>(b->data);
        }
        
        // Check for integer overflow
        if ((bVal > 0 && aVal < std::numeric_limits<int64_t>::min() + bVal) ||
            (bVal < 0 && aVal > std::numeric_limits<int64_t>::max() + bVal)) {
            error("Integer subtraction overflow");
        }
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT64_TYPE, aVal - bVal));
    }
}

void VM::handleMultiply(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    // String multiplication (string * int or int * string)
    if ((a->type->tag == TypeTag::String && b->type->tag == TypeTag::Int) ||
        (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::String)) {
        
        std::string str;
        int32_t count;
        
        if (a->type->tag == TypeTag::String) {
            str = std::get<std::string>(a->data);
            count = std::get<int32_t>(b->data);
        } else {
            str = std::get<std::string>(b->data);
            count = std::get<int32_t>(a->data);
        }
        
        if (count < 0) {
            error("String repetition count cannot be negative");
        }
        
        std::string result;
        result.reserve(str.length() * count);
        
        for (int i = 0; i < count; ++i) {
            result += str;
        }
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, result));
        return;
    }
    
    // Numeric multiplication
    if (a->type->tag == TypeTag::Float64 || b->type->tag == TypeTag::Float64) {
        // Convert to double if needed
        double aVal = (a->type->tag == TypeTag::Float64) ? 
            std::get<double>(a->data) : 
            static_cast<double>(std::get<int32_t>(a->data));
        
        double bVal = (b->type->tag == TypeTag::Float64) ? 
            std::get<double>(b->data) : 
            static_cast<double>(std::get<int32_t>(b->data));
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, aVal * bVal));
    } else if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && 
               (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        // Integer multiplication with mixed int32/int64 support
        int64_t aVal, bVal;
        
        // Convert both operands to int64_t
        if (a->type->tag == TypeTag::Int) {
            aVal = static_cast<int64_t>(std::get<int32_t>(a->data));
        } else {
            aVal = std::get<int64_t>(a->data);
        }
        
        if (b->type->tag == TypeTag::Int) {
            bVal = static_cast<int64_t>(std::get<int32_t>(b->data));
        } else {
            bVal = std::get<int64_t>(b->data);
        }
        
        int64_t result = aVal * bVal;
        
        // Check for overflow
        if (result > std::numeric_limits<int64_t>::max() || 
            result < std::numeric_limits<int64_t>::min()) {
            error("Integer multiplication overflow");
        }
        
        // Return as int64 to maintain precision
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT64_TYPE, result));
    } else {
        error("Invalid operands for multiplication");
    }
}

void VM::handleDivide(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    // Check for non-numeric operands
    bool aIsNumeric = (a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Float64);
    bool bIsNumeric = (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Float64);
    
    if (!aIsNumeric || !bIsNumeric) {
        // Create and push error value
        auto errorType = typeSystem->getType("DivisionByZero");
        auto errorValue = memoryManager.makeRef<Value>(*region, errorType);
        ErrorValue errorVal("TypeError", "Both operands must be numbers for division");
        errorValue->data = errorVal;
        push(errorValue);
        return;
    }
    
    // Check for division by zero with better error message
    bool isZero = false;
    std::string zeroType;
    
    if (b->type->tag == TypeTag::Float64) {
        double bVal = std::get<double>(b->data);
        isZero = bVal == 0.0;
        zeroType = isZero ? "floating-point zero" : "";
    } else {
        int32_t bVal = std::get<int32_t>(b->data);
        isZero = bVal == 0;
        zeroType = isZero ? "integer zero" : "";
    }
    
    if (isZero) {
        // Create and push error value
        auto errorType = typeSystem->getType("DivisionByZero");
        auto errorValue = memoryManager.makeRef<Value>(*region, errorType);
        ErrorValue errorVal("DivisionByZero", "Division by " + zeroType + " is not allowed");
        errorValue->data = errorVal;
        push(errorValue);
        return;
    }
    
    // Numeric division - always promote to double if either operand is double
    if (a->type->tag == TypeTag::Float64 || b->type->tag == TypeTag::Float64) {
        double aVal = (a->type->tag == TypeTag::Float64) ? 
            std::get<double>(a->data) : 
            static_cast<double>(std::get<int32_t>(a->data));
        
        double bVal = (b->type->tag == TypeTag::Float64) ? 
            std::get<double>(b->data) : 
            static_cast<double>(std::get<int32_t>(b->data));
        
        // Check for floating-point edge cases
        if (std::isinf(aVal / bVal)) {
            // Create and push error value
            auto errorType = typeSystem->getType("ArithmeticError");
            auto errorValue = memoryManager.makeRef<Value>(*region, errorType);
            ErrorValue errorVal("ArithmeticError", "Floating-point division resulted in infinity");
            errorValue->data = errorVal;
            push(errorValue);
            return;
        }
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, aVal / bVal));
    } else {
        // Integer division with check for INT_MIN / -1 overflow
        int32_t aVal = std::get<int32_t>(a->data);
        int32_t bVal = std::get<int32_t>(b->data);
        
        if (aVal == std::numeric_limits<int32_t>::min() && bVal == -1) {
            // Create and push error value
            auto errorType = typeSystem->getType("ArithmeticError");
            auto errorValue = memoryManager.makeRef<Value>(*region, errorType);
            ErrorValue errorVal("ArithmeticError", "Integer division overflow");
            errorValue->data = errorVal;
            push(errorValue);
            return;
        }
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, aVal / bVal));
    }
}

void VM::handleModulo(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    // Type checking
    if (a->type->tag != TypeTag::Int || b->type->tag != TypeTag::Int) {
        error("Modulo operation requires integer operands");
    }
    
    // Check for modulo by zero
    int32_t bVal = std::get<int32_t>(b->data);
    if (bVal == 0) {
        error("Modulo by zero");
    }
    
    // Integer modulo
    int32_t aVal = std::get<int32_t>(a->data);
    push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, aVal % bVal));
}

void VM::handleNegate(const Instruction& /*unused*/) {
    ValuePtr a = pop();
    
    if (a->type->tag == TypeTag::Float64) {
        double val = std::get<double>(a->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, -val));
    } else {
        int32_t val = std::get<int32_t>(a->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, -val));
    }
}

void VM::handleEqual(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Handle mixed integer types
    if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && 
        (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        // Convert both to int64_t for comparison
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = aVal == bVal;
    }
    // Handle mixed integer/float comparisons
    else if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && b->type->tag == TypeTag::Float64) {
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        result = static_cast<double>(aVal) == std::get<double>(b->data);
    }
    else if (a->type->tag == TypeTag::Float64 && (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = std::get<double>(a->data) == static_cast<double>(bVal);
    }
    // Handle same-type comparisons
    else if (a->type->tag == b->type->tag) {
        switch (a->type->tag) {
            case TypeTag::Float64:
                result = std::get<double>(a->data) == std::get<double>(b->data);
                break;
            case TypeTag::Bool:
                result = std::get<bool>(a->data) == std::get<bool>(b->data);
                break;
            case TypeTag::String:
                result = std::get<std::string>(a->data) == std::get<std::string>(b->data);
                break;
            case TypeTag::Nil:
                result = true; // nil == nil
                break;
            default:
                result = false; // Objects are compared by reference
                break;
        }
    }
    else {
        result = false; // Different types are not equal
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleNotEqual(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = true;
    
    // Handle mixed integer types
    if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && 
        (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        // Convert both to int64_t for comparison
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = aVal != bVal;
    }
    // Handle mixed integer/float comparisons
    else if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && b->type->tag == TypeTag::Float64) {
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        result = static_cast<double>(aVal) != std::get<double>(b->data);
    }
    else if (a->type->tag == TypeTag::Float64 && (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = std::get<double>(a->data) != static_cast<double>(bVal);
    }
    // Handle same-type comparisons
    else if (a->type->tag == b->type->tag) {
        switch (a->type->tag) {
            case TypeTag::Float64:
                result = std::get<double>(a->data) != std::get<double>(b->data);
                break;
            case TypeTag::Bool:
                result = std::get<bool>(a->data) != std::get<bool>(b->data);
                break;
            case TypeTag::String:
                result = std::get<std::string>(a->data) != std::get<std::string>(b->data);
                break;
            case TypeTag::Nil:
                result = false; // nil != nil is false
                break;
            default:
                result = true; // Objects are compared by reference
                break;
        }
    }
    else {
        result = true; // Different types are not equal
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleLess(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types - handle mixed integer types
    if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && 
        (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        // Convert both to int64_t for comparison
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = aVal < bVal;
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Float64) {
        result = std::get<double>(a->data) < std::get<double>(b->data);
    } else if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && b->type->tag == TypeTag::Float64) {
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        result = static_cast<double>(aVal) < std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = std::get<double>(a->data) < static_cast<double>(bVal);
    } else if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        result = std::get<std::string>(a->data) < std::get<std::string>(b->data);
    } else {
        error("Cannot compare values of different types");
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleLessEqual(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types - handle mixed integer types
    if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && 
        (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        // Convert both to int64_t for comparison
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = aVal <= bVal;
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Float64) {
        result = std::get<double>(a->data) <= std::get<double>(b->data);
    } else if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && b->type->tag == TypeTag::Float64) {
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        result = static_cast<double>(aVal) <= std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = std::get<double>(a->data) <= static_cast<double>(bVal);
    } else if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        result = std::get<std::string>(a->data) <= std::get<std::string>(b->data);
    } else {
        error("Cannot compare values of different types");
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleGreater(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types - handle mixed integer types
    if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && 
        (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        // Convert both to int64_t for comparison
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = aVal > bVal;
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Float64) {
        result = std::get<double>(a->data) > std::get<double>(b->data);
    } else if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && b->type->tag == TypeTag::Float64) {
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        result = static_cast<double>(aVal) > std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = std::get<double>(a->data) > static_cast<double>(bVal);
    } else if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        result = std::get<std::string>(a->data) > std::get<std::string>(b->data);
    } else {
        error("Cannot compare values of different types");
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleGreaterEqual(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types - handle mixed integer types
    if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && 
        (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        // Convert both to int64_t for comparison
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = aVal >= bVal;
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Float64) {
        result = std::get<double>(a->data) >= std::get<double>(b->data);
    } else if ((a->type->tag == TypeTag::Int || a->type->tag == TypeTag::Int64) && b->type->tag == TypeTag::Float64) {
        int64_t aVal = (a->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(a->data)) : 
            std::get<int64_t>(a->data);
        result = static_cast<double>(aVal) >= std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && (b->type->tag == TypeTag::Int || b->type->tag == TypeTag::Int64)) {
        int64_t bVal = (b->type->tag == TypeTag::Int) ? 
            static_cast<int64_t>(std::get<int32_t>(b->data)) : 
            std::get<int64_t>(b->data);
        result = std::get<double>(a->data) >= static_cast<double>(bVal);
    } else if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        result = std::get<std::string>(a->data) >= std::get<std::string>(b->data);
    } else {
        error("Cannot compare values of different types");
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleAnd(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool aVal = false;
    bool bVal = false;
    
    // Convert to boolean
    if (a->type->tag == TypeTag::Bool) {
        aVal = std::get<bool>(a->data);
    } else if (a->type->tag == TypeTag::Int) {
        aVal = std::get<int32_t>(a->data) != 0;
    } else if (a->type->tag == TypeTag::Float64) {
        aVal = std::get<double>(a->data) != 0.0;
    } else if (a->type->tag == TypeTag::String) {
        aVal = !std::get<std::string>(a->data).empty();
    } else if (a->type->tag == TypeTag::Nil) {
        aVal = false;
    } else {
        aVal = true; // Objects are truthy
    }
    
    if (b->type->tag == TypeTag::Bool) {
        bVal = std::get<bool>(b->data);
    } else if (b->type->tag == TypeTag::Int) {
        bVal = std::get<int32_t>(b->data) != 0;
    } else if (b->type->tag == TypeTag::Float64) {
        bVal = std::get<double>(b->data) != 0.0;
    } else if (b->type->tag == TypeTag::String) {
        bVal = !std::get<std::string>(b->data).empty();
    } else if (b->type->tag == TypeTag::Nil) {
        bVal = false;
    } else {
        bVal = true; // Objects are truthy
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, aVal && bVal));
}

void VM::handleOr(const Instruction& /*unused*/) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool aVal = false;
    bool bVal = false;
    
    // Convert to boolean
    if (a->type->tag == TypeTag::Bool) {
        aVal = std::get<bool>(a->data);
    } else if (a->type->tag == TypeTag::Int) {
        aVal = std::get<int32_t>(a->data) != 0;
    } else if (a->type->tag == TypeTag::Float64) {
        aVal = std::get<double>(a->data) != 0.0;
    } else if (a->type->tag == TypeTag::String) {
        aVal = !std::get<std::string>(a->data).empty();
    } else if (a->type->tag == TypeTag::Nil) {
        aVal = false;
    } else {
        aVal = true; // Objects are truthy
    }
    
    if (b->type->tag == TypeTag::Bool) {
        bVal = std::get<bool>(b->data);
    } else if (b->type->tag == TypeTag::Int) {
        bVal = std::get<int32_t>(b->data) != 0;
    } else if (b->type->tag == TypeTag::Float64) {
        bVal = std::get<double>(b->data) != 0.0;
    } else if (b->type->tag == TypeTag::String) {
        bVal = !std::get<std::string>(b->data).empty();
    } else if (b->type->tag == TypeTag::Nil) {
        bVal = false;
    } else {
        bVal = true; // Objects are truthy
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, aVal || bVal));
}

void VM::handleNot(const Instruction& /*unused*/) {
    if (stack.empty()) {
        error("Stack underflow in NOT operation");
        return;
    }

    ValuePtr value = pop();
    
    // Convert value to boolean
    bool boolValue = false;
    if (std::holds_alternative<bool>(value->data)) {
        boolValue = std::get<bool>(value->data);
    } else if (std::holds_alternative<int32_t>(value->data)) {
        boolValue = std::get<int32_t>(value->data) != 0;
    } else if (std::holds_alternative<int64_t>(value->data)) {
        boolValue = std::get<int64_t>(value->data) != 0;
    } else if (std::holds_alternative<double>(value->data)) {
        boolValue = std::get<double>(value->data) != 0.0;
    } else if (std::holds_alternative<float>(value->data)) {
        boolValue = std::get<float>(value->data) != 0.0f;
    } else if (std::holds_alternative<std::string>(value->data)) {
        boolValue = !std::get<std::string>(value->data).empty();
    } else if (std::holds_alternative<std::monostate>(value->data)) {
        boolValue = false; // null is falsy
    } else {
        error("Cannot perform NOT operation on type: " + typeTagToString(value->type->tag));
        return;
    }
    
    auto result = memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, !boolValue);
    push(result);
}

void VM::handleInterpolateString(const Instruction& instruction) {
    // The number of parts is stored in the intValue field
    int32_t numParts = instruction.intValue;
    
    if (stack.size() < static_cast<size_t>(numParts)) {
        error("Stack underflow in string interpolation");
        return;
    }
    
    // Pop all parts from the stack
    std::vector<ValuePtr> parts;
    parts.reserve(numParts);
    for (int i = 0; i < numParts; ++i) {
        parts.push_back(pop());
    }
    
    // Concatenate all parts in reverse order (since we popped them)
    std::string result;
    for (auto it = parts.rbegin(); it != parts.rend(); ++it) {
        result += valueToString(*it);
    }
    
    // Push the result string onto the stack
    auto resultValue = memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, result);
    push(resultValue);
}

void VM::handleConcat(const Instruction& /*unused*/) {
    if (stack.size() < 2) {
        error("Stack underflow in CONCAT operation");
        return;
    }
    
    // Pop the two top values
    ValuePtr right = pop();
    ValuePtr left = pop();
    
    // Convert both values to strings
    std::string leftStr = valueToString(left);
    std::string rightStr = valueToString(right);
    
    // Concatenate the strings
    std::string result = leftStr + rightStr;
    
    // Push the result back onto the stack
    auto resultValue = memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, result);
    push(resultValue);
}

void VM::handleJump(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    ip += instruction.intValue;
}

void VM::handleJumpIfTrue(const Instruction& instruction) {
    if (stack.empty()) {
        error("Stack underflow in JUMP_IF_TRUE");
        return;
    }
    
    ValuePtr condition = pop();
    if (!condition || !condition->type) {
        error("Invalid condition in JUMP_IF_TRUE");
        return;
    }
    
    bool condVal = false;
    
    try {
        // Convert to boolean
        if (condition->type->tag == TypeTag::Bool) {
            condVal = std::get<bool>(condition->data);
        } else if (condition->type->tag == TypeTag::Int) {
            condVal = std::get<int32_t>(condition->data) != 0;
        } else if (condition->type->tag == TypeTag::Float64) {
            condVal = std::get<double>(condition->data) != 0.0;
        } else if (condition->type->tag == TypeTag::String) {
            condVal = !std::get<std::string>(condition->data).empty();
        } else if (condition->type->tag == TypeTag::Nil) {
            condVal = false;
        } else {
            condVal = true; // Objects are truthy
        }
    } catch (const std::bad_variant_access&) {
        error("Invalid data type in condition for JUMP_IF_TRUE");
        return;
    }
    
    if (condVal) {
        ip += instruction.intValue;
    }
}

void VM::handleJumpIfFalse(const Instruction& instruction) {
    if (stack.empty()) {
        error("Stack underflow in JUMP_IF_FALSE");
        return;
    }
    
    ValuePtr condition = pop();
    if (!condition || !condition->type) {
        error("Invalid condition in JUMP_IF_FALSE");
        return;
    }
    
    bool condVal = false;
    
    try {
        // Convert to boolean
        if (condition->type->tag == TypeTag::Bool) {
            condVal = std::get<bool>(condition->data);
        } else if (condition->type->tag == TypeTag::Int) {
            condVal = std::get<int32_t>(condition->data) != 0;
        } else if (condition->type->tag == TypeTag::Float64) {
            condVal = std::get<double>(condition->data) != 0.0;
        } else if (condition->type->tag == TypeTag::String) {
            condVal = !std::get<std::string>(condition->data).empty();
        } else if (condition->type->tag == TypeTag::Nil) {
            condVal = false;
        } else {
            condVal = true; // Objects are truthy
        }
    } catch (const std::bad_variant_access&) {
        error("Invalid data type in condition for JUMP_IF_FALSE");
        return;
    }
    
    if (!condVal) {
        ip += instruction.intValue;
    }
}

void VM::handleCall(const Instruction& instruction) {
    // Get the function name from the instruction
    const std::string& funcName = instruction.stringValue;
    int argCount = instruction.intValue;
    
    // Determine if this is a method-like call so we can extract the callee
    bool isMethodLike = (funcName.substr(0, 7) == "method:" || funcName.substr(0, 6) == "super:");

    // Potential callee (may be recovered from stack or args)
    ValuePtr callee = nullptr;

    // Collect arguments from the stack (in reverse order). For method calls
    // the callee may be located below the arguments on the stack. If the
    // stack layout allows, extract the callee first without destroying the
    // argument order; otherwise fall back to the legacy pop-then-recover
    // approach.
    std::vector<ValuePtr> args;
    args.reserve(argCount);

    if (isMethodLike && stack.size() >= static_cast<size_t>(argCount) + 1) {
        // Callee is directly beneath the arguments: located at
        // stack[stack.size() - argCount - 1]. Extract it and remove that
        // element while preserving the rest of the stack for argument pops.
        size_t calleeIndex = stack.size() - argCount - 1;
        callee = stack[calleeIndex];

        // Erase the callee from the stack
        stack.erase(stack.begin() + calleeIndex);

        // Now pop arguments normally (they were above the callee)
        for (int i = 0; i < argCount; ++i) {
            args.insert(args.begin(), pop());
        }
    } else {
        // Only pop arguments if there are any
        if (argCount > 0) {
            // Check if we have enough values on the stack
            if (static_cast<int>(stack.size()) < argCount) {
                error("Not enough arguments on stack for function call: expected " + 
                      std::to_string(argCount) + ", got " + std::to_string(stack.size()));
                return;
            }
            
            for (int i = 0; i < argCount; i++) {
                args.insert(args.begin(), pop()); // Insert at beginning to maintain order
            }
        }
    }

    // For method calls and constructor calls, the callee may be on the stack
    // or (in some call conventions) included as the last argument. We'll
    // attempt to recover it from either location so the VM tolerates both
    // conventions.
   // ValuePtr callee = nullptr;
    
    // Check if this function can fail and push an error frame if needed
    bool canFail = functionCanFail(funcName);
    size_t errorHandlerAddress = 0;
    if (canFail) {
        // The error handler address is the next instruction after the call
        errorHandlerAddress = ip + 1;
        // Push an error frame with the handler address. Use nullptr to indicate
        // a wildcard expectedErrorType so this frame will accept any error.
        pushErrorFrame(errorHandlerAddress, nullptr, funcName);
    }
    
    if (funcName.substr(0, 7) == "method:" || funcName.substr(0, 6) == "super:") {
        // Method or super call - the object may be provided as a separate
        // callee value on the stack, or some compilers place the object as
        // the last argument. Try both: prefer an explicit callee on the
        // stack, otherwise recover from args.back().
        if (!stack.empty()) {
            // Prefer an explicit callee left on the stack
            callee = pop();
        } else if (!args.empty()) {
            // Recover callee from the last argument (common alternate convention)
            callee = args.back();
            args.pop_back();
        } else {
            if (debugMode) {
                std::cerr << "[DEBUG] method call without callee: funcName='" << funcName << "' stackSize=" << stack.size() << " argsSize=" << args.size() << std::endl;
            }
            error("Method call without object");
            return;
        }
    } else {
        // Simple function call - no callee required
    }
    
    // Check if this is a constructor call (callee is a class definition)
    if (callee && callee->type && callee->type->tag == TypeTag::Class) {
        try {
            // Get the class definition
            auto classDef = std::get<std::shared_ptr<backend::ClassDefinition>>(callee->data);
            
            // Create a new instance
            auto instance = std::make_shared<backend::ObjectInstance>(classDef);
            
            // Push 'this' onto the stack
            auto thisValue = memoryManager.makeRef<Value>(*region, typeSystem->OBJECT_TYPE);
            thisValue->data = instance;
            push(thisValue);
            
            // Look up and call the constructor if it exists
            if (auto constructor = classDef->getMethod("init")) {
                // Push 'this' as the first argument
                args.insert(args.begin(), thisValue);
                
                // Call the constructor
                constructor->implementation->execute(args);
                
                // If we get here, the constructor succeeded
                if (canFail) {
                    popErrorFrame();
                }
                
                // Push the new instance onto the stack
                push(thisValue);
                return;
            }
            
            // If no constructor is found, just push the new instance onto the stack
            push(thisValue);
            return;
        } catch (const std::exception& e) {
            error("Error in constructor: " + std::string(e.what()));
        }
    }
    
    // Check if this is a super method call (function name starts with "super:")
    if (funcName.substr(0, 6) == "super:") {
        std::string methodName = funcName.substr(6); // Remove "super:" prefix
        
        // Determine the object value. Prefer an explicitly recovered callee
        // (extracted above) when available, otherwise fall back to the
        // last-argument convention.
        ValuePtr objectValue = nullptr;
        std::vector<ValuePtr> methodArgs;
        if (callee) {
            objectValue = callee;
            methodArgs = args; // args were already extracted (callee removed earlier)
        } else {
            if (args.empty()) {
                error("Super method call without object");
                return;
            }
            objectValue = args.back();
            methodArgs = std::vector<ValuePtr>(args.begin(), args.end() - 1); // Remove object from args
        }
        
        // If the object is a Channel, provide native channel methods (send/receive/close)
        if (std::holds_alternative<std::shared_ptr<Channel<ValuePtr>>>(objectValue->data)) {
            auto ch = std::get<std::shared_ptr<Channel<ValuePtr>>>(objectValue->data);
            if (methodName == "send") {
                if (methodArgs.size() < 1) {
                    error("Channel.send expects 1 argument");
                    return;
                }
                ch->send(methodArgs[0]);
                push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
                if (canFail) popErrorFrame();
                return;
            } else if (methodName == "close") {
                ch->close();
                push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
                if (canFail) popErrorFrame();
                return;
            } else if (methodName == "receive") {
                ValuePtr v;
                bool ok = ch->receive(v);
                if (!ok) push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
                else push(v);
                if (canFail) popErrorFrame();
                return;
            } else {
                error("Unknown channel method: " + methodName);
                return;
            }
        }
        // Check if the object is an ObjectInstance
        if (std::holds_alternative<ObjectInstancePtr>(objectValue->data)) {
            auto objectInstance = std::get<ObjectInstancePtr>(objectValue->data);
            std::string className = objectInstance->getClassName();
            
            // For super calls, we need to look in the superclass
            auto classDef = classRegistry.getClass(className);
            if (!classDef) {
                error("Class definition not found: " + className);
                return;
            }
            
            auto superClass = classDef->getSuperClass();
            if (!superClass) {
                error("No superclass found for class: " + className);
                return;
            }
            
            std::string superClassName = superClass->getName();
            std::string methodKey = superClassName + "::" + methodName;
            auto methodIt = userDefinedFunctions.find(methodKey);
            
            if (methodIt != userDefinedFunctions.end()) {
                // Found the super method, execute it
                const backend::Function& method = methodIt->second;
                
                // Create a new environment for the method
                auto methodEnv = std::make_shared<Environment>(environment);
                
                // Bind 'this' parameter (implicit first parameter)
                methodEnv->define("this", objectValue);
                
                // Bind method parameters
                size_t paramIndex = 0;
                for (const auto& param : method.parameters) {
                    if (paramIndex < methodArgs.size()) {
                        methodEnv->define(param.first, methodArgs[paramIndex]);
                        paramIndex++;
                    }
                }
                
                // Create call frame
                backend::CallFrame frame(methodKey, ip, nullptr);
                frame.setPreviousEnvironment(environment);
                callStack.push_back(frame);
                
                // Switch to method environment
                environment = methodEnv;
                
                // Jump to method start
                ip = method.startAddress - 1; // -1 because ip will be incremented
                return;
            } else {
                error("Super method not found: " + methodKey);
                return;
            }
        } else {
            error("Super method call on non-object");
            return;
        }
    }
    
    // Check if this is a method call (function name starts with "method:")
    if (funcName.substr(0, 7) == "method:") {
        std::string methodName = funcName.substr(7); // Remove "method:" prefix
        
        // Determine the object value. Prefer an explicitly recovered callee
        // (extracted above) when available, otherwise fall back to the
        // last-argument convention.
        ValuePtr objectValue = nullptr;
        std::vector<ValuePtr> methodArgs;
        if (callee) {
            objectValue = callee;
            methodArgs = args; // args were already extracted (callee removed earlier)
        } else {
            if (args.empty()) {
                error("Method call without object");
                return;
            }
            objectValue = args.back();
            methodArgs = std::vector<ValuePtr>(args.begin(), args.end() - 1); // Remove object from args
        }
        
        // Check if the object is an ObjectInstance
        if (std::holds_alternative<ObjectInstancePtr>(objectValue->data)) {
            auto objectInstance = std::get<ObjectInstancePtr>(objectValue->data);
            std::string className = objectInstance->getClassName();
            
            // Look for the method in the VM's function registry
            std::string methodKey = className + "::" + methodName;
            auto methodIt = userDefinedFunctions.find(methodKey);
            
            if (methodIt != userDefinedFunctions.end()) {
                // Found the method, execute it
                const backend::Function& method = methodIt->second;
                
                // Create a new environment for the method
                auto methodEnv = std::make_shared<Environment>(environment);
                
                // Bind 'this' parameter (implicit first parameter)
                methodEnv->define("this", objectValue);
                
                // Bind method parameters
                size_t paramIndex = 0;
                for (const auto& param : method.parameters) {
                    if (paramIndex < methodArgs.size()) {
                        methodEnv->define(param.first, methodArgs[paramIndex]);
                        paramIndex++;
                    }
                }
                
                // Create call frame
                backend::CallFrame frame(methodKey, ip, nullptr);
                frame.setPreviousEnvironment(environment);
                callStack.push_back(frame);
                
                // Switch to method environment
                environment = methodEnv;
                
                // Jump to method start
                ip = method.startAddress - 1; // -1 because ip will be incremented
                return;
            } else {
                error("Method call failed: Method '" + methodName + "' not found in class '" + className + "'");
                return;
            }
        } else {
            if (debugMode) {
                std::cerr << "[DEBUG] Cannot call method '" << methodName << "' on non-object value" << std::endl;
            }
            // Fallback: if this is a channel-like value and methodName matches
            // our native channel functions, call the free-function variant so
            // member-style syntax 'ch.send(x)' works.
            if (std::holds_alternative<std::shared_ptr<Channel<ValuePtr>>>(objectValue->data)) {
                if (methodName == "send" || methodName == "receive" || methodName == "close") {
                    // Prepare args: channel as first parameter followed by methodArgs
                    std::vector<ValuePtr> nativeArgs;
                    nativeArgs.push_back(objectValue);
                    for (auto &a : methodArgs) nativeArgs.push_back(a);

                    auto nativeIt = nativeFunctions.find(methodName);
                    if (nativeIt != nativeFunctions.end()) {
                        ValuePtr res = nativeIt->second(nativeArgs);
                        push(res);
                        if (canFail) popErrorFrame();
                        return;
                    }
                }
            }
            error("Cannot call method on non-object value");
            return;
        }
    }
    
    // Check if this is a class constructor call
    if (classRegistry.hasClass(funcName)) {
        // Create instance of the class
        auto instance = classRegistry.createInstance(funcName);
        auto objectType = std::make_shared<Type>(TypeTag::Object);
        auto objectValue = memoryManager.makeRef<Value>(*region, objectType, instance);
        
        // Initialize fields with default values
        const auto& fields = instance->getClassDefinition()->getFields();
        for (const auto& field : fields) {
            std::string fieldKey = funcName + "::" + field.name;
            auto defaultValueIt = fieldDefaultValues.find(fieldKey);
            if (defaultValueIt != fieldDefaultValues.end()) {
                instance->setField(field.name, defaultValueIt->second);
            }
        }
        
        // Check if the class has an "init" method (constructor)
        std::string initMethodKey = funcName + "::init";
        auto initMethodIt = userDefinedFunctions.find(initMethodKey);
        
        if (initMethodIt != userDefinedFunctions.end()) {
            // Call the init method with the provided arguments
            const backend::Function& initMethod = initMethodIt->second;
            
            // Create a new environment for the constructor
            auto constructorEnv = std::make_shared<Environment>(environment);
            
            // Bind 'this' parameter (implicit first parameter)
            constructorEnv->define("this", objectValue);
            
            // Bind constructor parameters
            size_t paramIndex = 0;
            for (const auto& param : initMethod.parameters) {
                if (paramIndex < args.size()) {
                    constructorEnv->define(param.first, args[paramIndex]);
                    paramIndex++;
                }
            }
            
            // Create call frame for constructor
            backend::CallFrame frame(initMethodKey, ip, nullptr);
            frame.setPreviousEnvironment(environment);
            callStack.push_back(frame);
            
            // Switch to constructor environment
            environment = constructorEnv;
            
            // Jump to constructor start
            ip = initMethod.startAddress - 1; // -1 because ip will be incremented
            
            // The constructor will return, and we need to make sure the object is on the stack
            // We'll handle this in the return handler
            return;
        } else {
            // No constructor, just return the instance
            push(objectValue);
            return;
        }
    }
    
    // Try to get function from the new registry first
    auto function = functionRegistry.getFunction(funcName);
    if (function) {
        const auto& signature = function->getSignature();
        
        // Validate arguments
        if (!backend::FunctionUtils::validateArguments(signature, args)) {
            error("Function " + funcName + " expects " + std::to_string(signature.getMinParamCount()) + 
                  " to " + std::to_string(signature.getTotalParamCount()) + " arguments, got " + std::to_string(args.size()));
            return;
        }
        
        // Apply default values for missing optional parameters
        auto adjustedArgs = backend::FunctionUtils::applyDefaults(signature, args);
        
        if (function->isNative()) {
            // Execute native function directly
            ValuePtr result = function->execute(adjustedArgs);
            push(result);
            return;
        } else {
            // User-defined function - need to execute in VM context
            // Create a new environment for the function
            auto funcEnv = std::make_shared<Environment>(environment);
            
            // Bind parameters to the environment
            size_t paramIndex = 0;
            
            // Bind required parameters
            for (const auto& param : signature.parameters) {
                if (paramIndex < adjustedArgs.size()) {
                    funcEnv->define(param.name, adjustedArgs[paramIndex]);
                    paramIndex++;
                }
            }
            
            // Bind optional parameters
            for (const auto& param : signature.optionalParameters) {
                if (paramIndex < adjustedArgs.size()) {
                    funcEnv->define(param.name, adjustedArgs[paramIndex]);
                    paramIndex++;
                } else if (param.defaultValue) {
                    // TODO: Evaluate default value expression
                    // For now, use nil as placeholder
                    funcEnv->define(param.name, memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
                }
            }
            
            // Create call frame using the new CallFrame from functions.hh
            backend::CallFrame frame(funcName, ip, function);
            frame.bindParameters(adjustedArgs);
            frame.setPreviousEnvironment(environment);
            
            // Push call frame
            callStack.push_back(frame);

            // call frame pushed (debug output removed)
            
            // Switch to function environment
            environment = funcEnv;
            
            // For user-defined functions, we need to find the start address
            auto funcIt = userDefinedFunctions.find(funcName);
            if (funcIt != userDefinedFunctions.end()) {
                // Jump to function start
                ip = funcIt->second.startAddress - 1; // -1 because ip will be incremented
                return;
            } else {
                error("User-defined function " + funcName + " not found in bytecode");
                return;
            }
        }
    }
    
    // Fallback to legacy native function handling
    auto nativeIt = nativeFunctions.find(funcName);
    if (nativeIt != nativeFunctions.end()) {
        // Call the native function and push the result
        push(nativeIt->second(args));
        return;
    }
    
    // Handle user-defined functions
    auto funcIt = userDefinedFunctions.find(funcName);
    if (funcIt != userDefinedFunctions.end()) {
        const backend::Function& func = funcIt->second;
        
        // Create a new environment for the function
        auto funcEnv = std::make_shared<Environment>(environment);
        
        // Check argument count
        size_t requiredParams = func.parameters.size();
        size_t totalParams = requiredParams + func.optionalParameters.size();
        
        if (args.size() < requiredParams || args.size() > totalParams) {
            error("Function " + funcName + " expects " + std::to_string(requiredParams) + 
                  " to " + std::to_string(totalParams) + " arguments, got " + std::to_string(args.size()));
            return;
        }
        
        // Bind required parameters
        for (size_t i = 0; i < requiredParams && i < args.size(); i++) {
            funcEnv->define(func.parameters[i].first, args[i]); // Use .first for parameter name
        }
        
        // Bind optional parameters
        for (size_t i = 0; i < func.optionalParameters.size(); i++) {
            const std::string& paramName = func.optionalParameters[i].first; // Use .first for parameter name
            size_t argIndex = requiredParams + i;
            
            if (argIndex < args.size()) {
                // Use provided argument
                funcEnv->define(paramName, args[argIndex]);
            } else {
                // Use default value
                // Use default value if available
                auto defaultIt = func.defaultValues.find(paramName);
                if (defaultIt != func.defaultValues.end()) {
                    funcEnv->define(paramName, defaultIt->second.first); // Use .first for the ValuePtr
                } else {
                    // No default value, use nil
                    funcEnv->define(paramName, memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
                }
            }
        }
        
        // Create legacy call frame
        backend::CallFrame frame(funcName, ip, nullptr);
        frame.setPreviousEnvironment(environment);
        
        // Push call frame
        callStack.push_back(frame);
        
        // Switch to function environment
        environment = funcEnv;
        
        // Jump to function start
        // Jump to function start
        ip = func.startAddress - 1; // -1 because ip will be incremented
        return; // Exit early for user-defined functions
        return;
    }
    
    error("Function not found: " + funcName);
}

void VM::handleReturn(const Instruction& /*unused*/) {
    if (callStack.empty()) {
        // RETURN outside of function call - treated as no-op (debug output removed)
        // Push nil as a safe fallback and continue execution
        push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
        return;
    }
    
    // Pop the call frame and get function info
    backend::CallFrame frame = callStack.back();
    callStack.pop_back();

    // handleReturn: popped call frame (debug output removed)
    
    // Check if this is a constructor return
    bool isConstructor = frame.functionName.find("::init") != std::string::npos;
    
    ValuePtr returnValue;
    if (isConstructor) {
        // For constructors, return the 'this' object instead of the return value
        // Pop any explicit return value from the stack (constructors shouldn't return values)
        if (!stack.empty()) {
            pop(); // Discard explicit return value
        }
        
        // Get the 'this' object from the environment
        auto thisValue = environment->get("this");
        if (thisValue) {
            returnValue = thisValue;
        } else {
            error("Constructor missing 'this' reference");
            return;
        }
    } else {
        // Regular function return
        if (!stack.empty()) {
            returnValue = pop();
        } else {
            // No explicit return value, use nil
            returnValue = memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
        }
    }
    
    // Restore the environment
    auto prevEnv = frame.getPreviousEnvironment<Environment>();
    if (prevEnv) {
        environment = prevEnv;
    } else {
        environment = globals; // Fallback
    }
    
    // Push the return value
    // handleReturn: pushing return value (debug output removed)
    push(returnValue);
    
    // If an error frame was pushed for this function call, decide whether to pop it.
    // We should only pop the frame on a *successful* return. If the function
    // returned an error union (or direct ErrorValue), keep the frame so the
    // caller can inspect/propagate the error.
    bool returnedError = false;
    if (returnValue) {
        if (returnValue->isError()) returnedError = true;
        else if (returnValue->type && returnValue->type->tag == TypeTag::ErrorUnion) {
            // If the ErrorUnion actually contains an ErrorValue, treat as error
            if (std::holds_alternative<ErrorValue>(returnValue->data)) returnedError = true;
        }
    }

    if (!errorFrames.empty()) {
        ErrorFrame& top = errorFrames.back();
        if (top.functionName == frame.functionName) {
            if (returnedError) {
                if (debugOutput) std::cerr << "[DEBUG] handleReturn: function returned error; keeping error frame for function='" << frame.functionName << "'" << std::endl;
            } else {
                if (debugOutput) std::cerr << "[DEBUG] handleReturn: popping error frame for function='" << frame.functionName << "'" << std::endl;
                popErrorFrame();
            }
        }
    }

    // Return to the caller
    ip = frame.returnAddress;
}

void VM::handlePrint(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    int argCount = instruction.intValue;
    std::vector<ValuePtr> args;
    
    // Pop all arguments from the stack
    for (int i = 0; i < argCount; ++i) {
        args.insert(args.begin(), pop());
    }
    
    // Print all arguments separated by spaces
    for (size_t i = 0; i < args.size(); ++i) {
        if (i > 0) {
            std::cout << " ";
        }
        // Ensure the value is converted to a string
        if (args[i] && args[i]->type && args[i]->type->tag == TypeTag::String) {
            // If it's already a string, just print it
            std::cout << valueToString(args[i]);
        } else {
            // Otherwise, convert it to a string first
            std::string strValue = valueToString(args[i]);
            std::cout << strValue;
        }
    }
    std::cout << std::endl;
    
    // Print is a statement, not an expression - don't push a result
}

void VM::handleBeginFunction(const Instruction& instruction) {
    // Create a new function definition
    const std::string& funcName = instruction.stringValue;
    
    // If we're inside a class definition, use the full method key
    if (insideClassDefinition && !currentClassBeingDefined.empty()) {
        currentFunctionBeingDefined = currentClassBeingDefined + "::" + funcName;
    } else {
        currentFunctionBeingDefined = funcName;
    }
    
    // Create a new Function struct
    backend::Function func(funcName, 0); // Will set start address later
    
    // Don't skip parameter definition instructions - let them execute normally
    // Just find where the function body starts for later use
    size_t bodyStart = ip + 1;
    while (bodyStart < bytecode->size()) {
        const Instruction& inst = (*bytecode)[bodyStart];
        if (inst.opcode == Opcode::DEFINE_PARAM || 
            inst.opcode == Opcode::DEFINE_OPTIONAL_PARAM ||
            inst.opcode == Opcode::PUSH_STRING ||
            inst.opcode == Opcode::PUSH_INT ||
            inst.opcode == Opcode::PUSH_FLOAT ||
            inst.opcode == Opcode::PUSH_BOOL ||
            inst.opcode == Opcode::SET_DEFAULT_VALUE) {
            // These are parameter definition instructions, continue
            bodyStart++;
        } else {
            // Found the start of the actual function body
            break;
        }
    }
    
    // Set the function start address to the beginning of the actual body
    func.startAddress = bodyStart;
    
    // If we're inside a class definition, this is a method
    if (insideClassDefinition && !currentClassBeingDefined.empty()) {
        // This is a class method - we'll handle it differently
        // For now, still store it as a regular function but mark it as a method
        std::string methodKey = currentClassBeingDefined + "::" + funcName;
        userDefinedFunctions[methodKey] = func;
        
        // Also add it to the class definition
        auto classDef = classRegistry.getClass(currentClassBeingDefined);
        if (classDef) {
            // Create a method implementation
            // For now, we'll create a placeholder - the actual method execution
            // will be handled by the VM when the method is called
            // TODO: Create proper method implementation
        }
    } else {
        // Regular function
        userDefinedFunctions[funcName] = func;
    }
    
    // Continue with normal execution to process parameter definitions
    // The function body will be skipped later when we encounter END_FUNCTION
}

void VM::handleEndFunction(const Instruction& /*unused*/) {
    // Check if we're currently defining a function
    if (!currentFunctionBeingDefined.empty()) {
        // This is the end of function definition, not function execution
        auto funcIt = userDefinedFunctions.find(currentFunctionBeingDefined);
        if (funcIt != userDefinedFunctions.end()) {
            funcIt->second.endAddress = ip;
        }
        currentFunctionBeingDefined.clear();
        insideFunctionDefinition = false;
        return;
    }
    
    // This is during function execution - return from a function call
    if (callStack.empty()) {
        error("END_FUNCTION reached outside of function call");
        return;
    }
    
    // Pop the call frame and return to the caller
    backend::CallFrame frame = callStack.back();
    callStack.pop_back();

    if (debugOutput) {
        std::cerr << "[DEBUG] handleEndFunction: popped call frame for '" << frame.functionName << "' new_callStack_size=" << callStack.size() << " ip=" << ip << std::endl;
    }
    
    // Restore the environment
    auto prevEnv = frame.getPreviousEnvironment<Environment>();
    if (prevEnv) {
        environment = prevEnv;
    } else {
        environment = globals; // Fallback
    }
    
    // If there's no explicit return value on the stack, push nil
    if (stack.empty()) {
        push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
    }
    
    // Return to the caller
    ip = frame.returnAddress;
}

void VM::handleDefineParam(const Instruction& instruction) {
    // Add parameter to the current function being defined
    if (!currentFunctionBeingDefined.empty()) {
        auto funcIt = userDefinedFunctions.find(currentFunctionBeingDefined);
        if (funcIt != userDefinedFunctions.end()) {
            funcIt->second.parameters.push_back(std::make_pair(instruction.stringValue, nullptr));
        }
    }
}

void VM::handleDefineOptionalParam(const Instruction& instruction) {
    // Add optional parameter to the current function being defined
    if (!currentFunctionBeingDefined.empty()) {
        auto funcIt = userDefinedFunctions.find(currentFunctionBeingDefined);
        if (funcIt != userDefinedFunctions.end()) {
            funcIt->second.optionalParameters.push_back(std::make_pair(instruction.stringValue, nullptr));
        }
    }
}

void VM::handleSetDefaultValue(const Instruction& /*unused*/) {
    // Set default value for the last optional parameter
    if (currentFunctionBeingDefined.empty()) {
        error("SET_DEFAULT_VALUE outside of function definition");
        return;
    }
    
    auto funcIt = userDefinedFunctions.find(currentFunctionBeingDefined);
    if (funcIt != userDefinedFunctions.end() && !funcIt->second.optionalParameters.empty()) {
        backend::Function& currentFunc = funcIt->second;
        std::string paramName = currentFunc.optionalParameters.back().first; // Get the parameter name
        ValuePtr defaultValue = pop();
        TypePtr paramType = currentFunc.optionalParameters.back().second; // Get the parameter type
        currentFunc.defaultValues[paramName] = std::make_pair(defaultValue, paramType);
    }
}
void VM::handleBeginClass(const Instruction& instruction) {
    // Get the class name from the instruction
    std::string className = instruction.stringValue;
    
    // Track that we're now inside a class definition
    currentClassBeingDefined = className;
    insideClassDefinition = true;
    
    // Create a basic class definition
    auto classDef = std::make_shared<backend::ClassDefinition>(className);
    
    // Register the class (we'll add methods to it as we encounter them)
    classRegistry.registerClass(classDef);
}
void VM::handleEndClass(const Instruction& /*unused*/) {
    // End of class definition
    insideClassDefinition = false;
    currentClassBeingDefined = "";
}

void VM::handleSetSuperclass(const Instruction& instruction) {
    // Get the superclass name from the instruction
    std::string superClassName = instruction.stringValue;
    
    // Get the current class being defined
    if (!insideClassDefinition || currentClassBeingDefined.empty()) {
        error("SET_SUPERCLASS outside of class definition");
        return;
    }
    
    auto classDef = classRegistry.getClass(currentClassBeingDefined);
    if (!classDef) {
        error("Class definition not found: " + currentClassBeingDefined);
        return;
    }
    
    // Get the superclass definition
    auto superClassDef = classRegistry.getClass(superClassName);
    if (!superClassDef) {
        error("Superclass not found: " + superClassName);
        return;
    }
    
    // Set the superclass
    classDef->setSuperClass(superClassDef);
}

void VM::handleDefineField(const Instruction& instruction) {
    // Get the field name from the instruction
    std::string fieldName = instruction.stringValue;
    
    // Pop the default value from the stack
    ValuePtr defaultValue = pop();
    
    // Get the current class being defined
    if (!insideClassDefinition || currentClassBeingDefined.empty()) {
        error("DEFINE_FIELD outside of class definition");
        return;
    }
    
    auto classDef = classRegistry.getClass(currentClassBeingDefined);
    if (!classDef) {
        error("Class definition not found: " + currentClassBeingDefined);
        return;
    }
    
    // Create a class field
    // Note: We need to convert the runtime value back to an AST expression
    // For now, we'll create a simple literal expression
    std::shared_ptr<AST::Expression> defaultExpr = nullptr;
    
    // TODO: Convert runtime value to AST expression
    // This is a simplified approach - in a full implementation, we'd need
    // to properly convert runtime values back to AST expressions
    
    backend::ClassField field(fieldName, nullptr, defaultExpr);
    classDef->addField(field);
    
    // Store the runtime default value in a temporary map for object initialization
    // We'll use this during object creation
    fieldDefaultValues[currentClassBeingDefined + "::" + fieldName] = defaultValue;
}
void VM::handleLoadThis(const Instruction& /*unused*/) {
    // Load 'this' reference onto the stack
    try {
        ValuePtr thisValue = environment->get("this");
        push(thisValue);
    } catch (const std::exception& e) {
        error("'this' reference not available in current context");
    }
}

void VM::handleLoadSuper(const Instruction& /*unused*/) {
    // Load 'super' reference onto the stack
    // For now, 'super' is the same as 'this' but with different method resolution
    // In a full implementation, this would create a special super object
    try {
        ValuePtr thisValue = environment->get("this");
        push(thisValue);
    } catch (const std::exception& e) {
        // Try to find 'this' in parent environments
        auto currentEnv = environment;
        while (currentEnv != nullptr) {
            try {
                ValuePtr thisValue = currentEnv->get("this");
                push(thisValue);
                return;
            } catch (const std::exception&) {
                currentEnv = currentEnv->enclosing;
            }
        }
        error("'super' reference not available in current context");
    }
}
void VM::handleGetProperty(const Instruction& instruction) {
    // Get property name from instruction
    std::string propertyName = instruction.stringValue;
    
    // Pop the object from the stack
    ValuePtr object = pop();
    
    // Check if the object is an ObjectInstance
    if (std::holds_alternative<ObjectInstancePtr>(object->data)) {
        auto objectInstance = std::get<ObjectInstancePtr>(object->data);
        
        try {
            ValuePtr propertyValue = objectInstance->getField(propertyName);
            push(propertyValue);
        } catch (const std::exception& e) {
            error("Property access failed: " + std::string(e.what()));
        }
    } else {
        error("Cannot access property on non-object value");
    }
}
void VM::handleSetProperty(const Instruction& instruction) {
    // Get property name from instruction
    std::string propertyName = instruction.stringValue;
    
    // Pop the value and object from the stack
    ValuePtr value = pop();
    ValuePtr object = pop();
    
    // Check if the object is an ObjectInstance
    if (std::holds_alternative<ObjectInstancePtr>(object->data)) {
        auto objectInstance = std::get<ObjectInstancePtr>(object->data);
        
        try {
            // If the property doesn't exist yet, create it
            if (!objectInstance->hasField(propertyName)) {
                objectInstance->defineField(propertyName, value);
            } else {
                objectInstance->setField(propertyName, value);
            }
            
            // Push the assigned value back onto the stack for assignment expressions
            push(value);
        } catch (const std::exception& e) {
            error("Property assignment failed: " + std::string(e.what()));
        }
    } else {
        error("Cannot set property on non-object value");
    }
}

void VM::handleCreateList(const Instruction& instruction) {
    // Get the number of elements to include in the list from the instruction
    int32_t count = instruction.intValue;
    
    // Create a new list
    auto list = memoryManager.makeRef<Value>(*region, typeSystem->LIST_TYPE);
    auto listValue = ListValue();
    
    // Pop 'count' elements from the stack and add them to the list
    for (int32_t i = 0; i < count; i++) {
        ValuePtr element = pop();
        listValue.elements.push_back(element);
    }
    
    // Since we popped elements in reverse order, reverse the list to maintain the correct order
    std::reverse(listValue.elements.begin(), listValue.elements.end());
    
    // Store the list in the value and push it onto the stack
    list->data = listValue;
    push(list);
}

// Helper function to compare two values for equality
bool VM::valuesEqual(const ValuePtr& a, const ValuePtr& b) const {
    if (!a && !b) return true;
    if (!a || !b) return false;
    
    // Compare by type first
    if (a->type->tag != b->type->tag) {
        return false;
    }
    
    // Compare by value content based on type
    switch (a->type->tag) {
        case TypeTag::Bool:
            return std::get<bool>(a->data) == std::get<bool>(b->data);
        case TypeTag::Int:
            return std::get<int32_t>(a->data) == std::get<int32_t>(b->data);
        case TypeTag::Float64:
            return std::get<double>(a->data) == std::get<double>(b->data);
        case TypeTag::String:
            return std::get<std::string>(a->data) == std::get<std::string>(b->data);
        case TypeTag::Nil:
            return true; // All nil values are equal
        default:
            // For complex types, fall back to pointer comparison
            return a.get() == b.get();
    }
}

void VM::handleListAppend(const Instruction& /*unused*/) {
    // Pop the value to append
    ValuePtr value = pop();
    
    // Pop the list
    ValuePtr listVal = pop();
    
    // Check if it's actually a list
    if (!std::holds_alternative<ListValue>(listVal->data)) {
        error("Cannot append to non-list value");
        return;
    }
    
    // Get the list data
    auto& listData = std::get<ListValue>(listVal->data);
    
    // Append the value
    listData.elements.push_back(value);
    
    // Push the modified list back onto the stack
    push(listVal);
}

void VM::handleCreateDict(const Instruction& instruction) {
    // Get the number of key-value pairs to include in the dictionary
    int32_t count = instruction.intValue;
    
    // Create a new dictionary
    auto dict = memoryManager.makeRef<Value>(*region, typeSystem->DICT_TYPE);
    auto dictValue = DictValue();
    
    // Pop 'count' key-value pairs from the stack and add them to the dictionary
    // Stack layout: [key1, value1, key2, value2, ..., keyN, valueN] (top)
    for (int32_t i = 0; i < count; i++) {
        ValuePtr value = pop();  // Pop value first (it's on top)
        ValuePtr key = pop();    // Then pop key
        
        // For now, we'll use the first key if there are duplicates
        // In a real implementation, we might want to handle this differently
        bool keyExists = false;
        for (auto& [existingKey, existingValue] : dictValue.elements) {
            if (valuesEqual(existingKey, key)) {
                existingValue = value; // Update existing key
                keyExists = true;
                break;
            }
        }
        
        if (!keyExists) {
            dictValue.elements[key] = value;
        }
    }
    
    // Store the dictionary in the value and push it onto the stack
    dict->data = dictValue;
    push(dict);
}

void VM::handleDictSet(const Instruction& /*unused*/) {
    // Pop the value to set
    ValuePtr value = pop();
    
    // Pop the key
    ValuePtr key = pop();
    
    // Pop the dictionary
    ValuePtr dictVal = pop();
    
    // Check if it's actually a dictionary
    if (!std::holds_alternative<DictValue>(dictVal->data)) {
        error("Cannot set key on non-dictionary value");
        return;
    }
    
    // Get the dictionary data
    auto& dictData = std::get<DictValue>(dictVal->data);
    
    // Find existing key and update, or add new key
    bool keyExists = false;
    for (auto& [existingKey, existingValue] : dictData.elements) {
        if (valuesEqual(existingKey, key)) {
            existingValue = value; // Update existing key
            keyExists = true;
            break;
        }
    }
    
    if (!keyExists) {
        dictData.elements[key] = value;
    }
    
    // Push the modified dictionary back onto the stack
    push(dictVal);
}

void VM::handleGetIndex(const Instruction& /*unused*/) {
    // Pop the index
    ValuePtr index = pop();
    
    // Pop the container (list or dictionary)
    ValuePtr container = pop();
    
    if (std::holds_alternative<ListValue>(container->data)) {
        // Handle list indexing
        auto& listData = std::get<ListValue>(container->data);
        
        // Check if index is an integer
        if (!std::holds_alternative<int32_t>(index->data)) {
            error("List index must be an integer");
            return;
        }
        
        int32_t idx = std::get<int32_t>(index->data);
        
        // Check bounds
        if (idx < 0 || idx >= static_cast<int32_t>(listData.elements.size())) {
            error("List index out of bounds");
            return;
        }
        
        // Push the element at the index
        push(listData.elements[idx]);
        
    } else if (std::holds_alternative<DictValue>(container->data)) {
        // Handle dictionary indexing
        auto& dictData = std::get<DictValue>(container->data);
        
        // Find the key in the dictionary by comparing values
        ValuePtr foundValue = nullptr;
        for (const auto& [key, value] : dictData.elements) {
            if (valuesEqual(key, index)) {
                foundValue = value;
                break;
            }
        }
        
        if (!foundValue) {
            error("Key not found in dictionary");
            return;
        }
        
        // Push the value for the key
        push(foundValue);
        
    } else {
        error("Cannot index non-container value");
    }
}

void VM::handleSetIndex(const Instruction& /*unused*/) {
    // Pop the value to set
    ValuePtr value = pop();
    
    // Pop the index
    ValuePtr index = pop();
    
    // Pop the container (list or dictionary)
    ValuePtr container = pop();
    
    if (std::holds_alternative<ListValue>(container->data)) {
        // Handle list indexing
        auto& listData = std::get<ListValue>(container->data);
        
        // Check if index is an integer
        if (!std::holds_alternative<int32_t>(index->data)) {
            error("List index must be an integer");
            return;
        }
        
        int32_t idx = std::get<int32_t>(index->data);
        
        // Check bounds
        if (idx < 0 || idx >= static_cast<int32_t>(listData.elements.size())) {
            error("List index out of bounds");
            return;
        }
        
        // Set the element at the index
        listData.elements[idx] = value;
        
    } else if (std::holds_alternative<DictValue>(container->data)) {
        // Handle dictionary indexing
        auto& dictData = std::get<DictValue>(container->data);
        
        // Find existing key and update, or add new key
        bool keyExists = false;
        for (auto& [existingKey, existingValue] : dictData.elements) {
            if (valuesEqual(existingKey, index)) {
                existingValue = value; // Update existing key
                keyExists = true;
                break;
            }
        }
        
        if (!keyExists) {
            dictData.elements[index] = value;
        }
        
    } else {
        error("Cannot index non-container value");
    }
    
    // Push the modified container back onto the stack
    push(container);
}

void VM::handleCreateRange(const Instruction& instruction) {
    // Get the step value (default is 1 if not specified)
    int64_t step = 1;
    if (instruction.intValue != 0) {
        step = instruction.intValue;
    }

    // Get end value from stack
    auto endVal = pop();
    // Get start value from stack
    auto startVal = pop();

    // Extract integer values
    int64_t start, end;
    
    if (std::holds_alternative<int8_t>(startVal->data)) {
        start = std::get<int8_t>(startVal->data);
    } else if (std::holds_alternative<int16_t>(startVal->data)) {
        start = std::get<int16_t>(startVal->data);
    } else if (std::holds_alternative<int32_t>(startVal->data)) {
        start = std::get<int32_t>(startVal->data);
    } else if (std::holds_alternative<int64_t>(startVal->data)) {
        start = std::get<int64_t>(startVal->data);
    } else {
        error("Range start must be an integer");
        return;
    }

    if (std::holds_alternative<int8_t>(endVal->data)) {
        end = std::get<int8_t>(endVal->data);
    } else if (std::holds_alternative<int16_t>(endVal->data)) {
        end = std::get<int16_t>(endVal->data);
    } else if (std::holds_alternative<int32_t>(endVal->data)) {
        end = std::get<int32_t>(endVal->data);
    } else if (std::holds_alternative<int64_t>(endVal->data)) {
        end = std::get<int64_t>(endVal->data);
    } else {
        error("Range end must be an integer");
        return;
    }

    // Create a list to hold the range values
    ListValue rangeList;
    
    if (step > 0) {
        for (int64_t i = start; i < end; i += step) {
            auto val = memoryManager.makeRef<Value>(*region, typeSystem->INT64_TYPE, i);
            rangeList.elements.push_back(val);
        }
    } else if (step < 0) {
        for (int64_t i = start; i > end; i += step) {
            auto val = memoryManager.makeRef<Value>(*region, typeSystem->INT64_TYPE, i);
            rangeList.elements.push_back(val);
        }
    }
    
    // Push the range list onto the stack
    auto result = memoryManager.makeRef<Value>(*region, typeSystem->LIST_TYPE, rangeList);
    push(result);
}

void VM::handleGetIterator(const Instruction& /*unused*/) {
    // Get the iterable from the stack
    auto iterable = pop();
    
    // Create an iterator for the iterable
    if (std::holds_alternative<ListValue>(iterable->data)) {
        // For lists, create a list iterator
        auto iterator = std::make_shared<IteratorValue>(
            IteratorValue::IteratorType::LIST,
            iterable
        );
        // Wrap the iterator in a Value and push it onto the stack
        auto iteratorValue = memoryManager.makeRef<Value>(
            *region,
            typeSystem->ANY_TYPE,
            iterator
        );
        push(iteratorValue);
    } else if (std::holds_alternative<DictValue>(iterable->data)) {
        // For dictionaries, we'll use the same approach as lists for now
        // but with a different iterator type
        auto iterator = std::make_shared<IteratorValue>(
            IteratorValue::IteratorType::LIST, // TODO: Add DICT iterator type
            iterable
        );
        // Wrap the iterator in a Value and push it onto the stack
        auto iteratorValue = memoryManager.makeRef<Value>(
            *region,
            typeSystem->ANY_TYPE,
            iterator
        );
        push(iteratorValue);
    } else if (std::holds_alternative<IteratorValuePtr>(iterable->data)) {
        // If it's already an iterator, just push it back
        push(iterable);
    } else if (std::holds_alternative<std::shared_ptr<Channel<ValuePtr>>>(iterable->data)) {
        // Create a channel-backed iterator
        auto iterator = std::make_shared<IteratorValue>(
            IteratorValue::IteratorType::CHANNEL,
            iterable
        );
        auto iteratorValue = memoryManager.makeRef<Value>(
            *region,
            typeSystem->ANY_TYPE,
            iterator
        );
        push(iteratorValue);
    } else {
        error("Type is not iterable");
    }
}

void VM::handleIteratorHasNext(const Instruction& /*unused*/) {
    // Get the iterator from the stack
    auto iteratorVal = pop();
    
    // Check if the value is an iterator
    if (!std::holds_alternative<IteratorValuePtr>(iteratorVal->data)) {
        error("Expected iterator value");
        return;
    }
    
    auto iterator = std::get<IteratorValuePtr>(iteratorVal->data);
    bool hasNext = iterator->hasNext();
    
    // Push the result back onto the stack
    auto result = memoryManager.makeRef<Value>(
        *region,
        typeSystem->BOOL_TYPE,
        hasNext
    );
    push(result);
}

void VM::handleIteratorNext(const Instruction& /*unused*/) {
    // Get the iterator from the stack
    auto iteratorVal = pop();
    
    // Check if the value is an iterator
    if (!std::holds_alternative<IteratorValuePtr>(iteratorVal->data)) {
        error("Expected iterator value");
        return;
    }
    
    auto iterator = std::get<IteratorValuePtr>(iteratorVal->data);
    
    if (!iterator->hasNext()) {
        error("No more elements in iterator");
        return;
    }
    
    // Get the next value and push it onto the stack
    ValuePtr nextValue = iterator->next();
    push(nextValue);
}

void VM::handleIteratorNextKeyValue(const Instruction& /*unused*/) {
    // For now, we'll just call handleIteratorNext for both key and value
    // In a real implementation, we would need to handle dictionary iteration differently
    Instruction nextInstr;
    nextInstr.opcode = Opcode::ITERATOR_NEXT;
    nextInstr.intValue = 0;
    nextInstr.boolValue = false;
    handleIteratorNext(nextInstr);
}

void VM::handleBeginScope(const Instruction& /*unused*/) {
    // Create a new environment that extends the current one
    environment = std::make_shared<Environment>(environment);
}

void VM::handleEndScope(const Instruction& /*unused*/) {
    // Restore the previous environment
    if (environment && environment->enclosing) {
        environment = environment->enclosing;
    }
}

void VM::handleBeginParallel(const Instruction& instruction) {
    // Find the end of the parallel block
    size_t block_start_ip = ip + 1;
    size_t block_end_ip = block_start_ip;
    int nesting_level = 0;
    
    while (block_end_ip < bytecode->size()) {
        const auto& instr = (*bytecode)[block_end_ip];
        if (instr.opcode == Opcode::BEGIN_PARALLEL) {
            nesting_level++;
        } else if (instr.opcode == Opcode::END_PARALLEL) {
            if (nesting_level == 0) {
                break;
            }
            nesting_level--;
        }
        block_end_ip++;
    }

    if (block_end_ip >= bytecode->size()) {
        error("Unmatched BEGIN_PARALLEL");
        return;
    }

    // Extract the bytecode for the parallel block
    std::vector<Instruction> block_bytecode(
        bytecode->begin() + block_start_ip,
        bytecode->begin() + block_end_ip
    );

    // Get the number of cores to use (from instruction parameters)
    int cores = instruction.intValue > 0 ? instruction.intValue : std::thread::hardware_concurrency();
    std::string mode = instruction.stringValue.empty() ? "fork-join" : instruction.stringValue;

    if (debugMode) {
        std::cout << "[DEBUG] Starting parallel block with " << cores << " cores, mode: " << mode << std::endl;
    }

    // Create multiple tasks for parallel execution
    std::vector<Task> tasks;
    for (int i = 0; i < cores && i < 4; ++i) { // Limit to 4 parallel tasks for safety
        Task task = [this, block_bytecode, i]() {
            try {
                // Create a new VM for this task without creating a new runtime
                VM task_vm(false);

                // Share the concurrency runtime components
                task_vm.scheduler = this->scheduler;
                task_vm.thread_pool = this->thread_pool;
                task_vm.event_loop = this->event_loop;

                // Each task gets a new memory region and environment.
                // The VM constructor creates a new region.
                // The new environment inherits from the current environment to capture local variables.
                task_vm.globals = this->globals;
                task_vm.environment = std::make_shared<Environment>(this->environment);
                
                // Set debug mode
                task_vm.setDebug(this->debugMode);

                if (debugMode) {
                    std::cout << "[DEBUG] Parallel task " << i << " starting execution" << std::endl;
                }

                // Execute the bytecode block
                task_vm.execute(block_bytecode);

                if (debugMode) {
                    std::cout << "[DEBUG] Parallel task " << i << " completed" << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Parallel task " << i << " failed: " << e.what() << std::endl;
            }
        };
        
        tasks.push_back(std::move(task));
    }

    // Submit all tasks to the scheduler
    for (auto& task : tasks) {
        scheduler->submit(std::move(task));
    }

    // Skip the main VM's instruction pointer past the parallel block
    ip = block_end_ip;
}

void VM::handleEndParallel(const Instruction& /*unused*/) {
    // This is now a no-op. The thread pool manages thread lifecycle.
}

void VM::handleBeginConcurrent(const Instruction& instruction) {
    // Find the end of the concurrent block
    size_t block_start_ip = ip + 1;
    size_t block_end_ip = block_start_ip;
    int nesting_level = 0;
    
    while (block_end_ip < bytecode->size()) {
        const auto& instr = (*bytecode)[block_end_ip];
        if (instr.opcode == Opcode::BEGIN_CONCURRENT) {
            nesting_level++;
        } else if (instr.opcode == Opcode::END_CONCURRENT) {
            if (nesting_level == 0) {
                break;
            }
            nesting_level--;
        }
        block_end_ip++;
    }

    if (block_end_ip >= bytecode->size()) {
        error("Unmatched BEGIN_CONCURRENT");
        return;
    }

    // Extract the bytecode for the concurrent block
    std::vector<Instruction> block_bytecode(
        bytecode->begin() + block_start_ip,
        bytecode->begin() + block_end_ip
    );

    std::string mode = instruction.stringValue.empty() ? "async" : instruction.stringValue;

    if (debugMode) {
        std::cout << "[DEBUG] Starting concurrent block, mode: " << mode << std::endl;
    }

    // Create a task for concurrent execution
    Task task = [this, block_bytecode, mode]() {
        try {
            // Create a new VM for this task without creating a new runtime
            VM task_vm(false);

            // Share the concurrency runtime components
            task_vm.scheduler = this->scheduler;
            task_vm.thread_pool = this->thread_pool;
            task_vm.event_loop = this->event_loop;

            // Each task gets a new memory region and environment.
            // The VM constructor creates a new region.
            // The new environment inherits from the current environment to capture local variables.
            task_vm.globals = this->globals;
            task_vm.environment = std::make_shared<Environment>(this->environment);
            
            // Set debug mode
            task_vm.setDebug(this->debugMode);

            if (debugMode) {
                std::cout << "[DEBUG] Concurrent task starting execution" << std::endl;
            }

            // Execute the bytecode block
            task_vm.execute(block_bytecode);

            if (debugMode) {
                std::cout << "[DEBUG] Concurrent task completed" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Concurrent task failed: " << e.what() << std::endl;
        }
    };

    // Submit the task to the scheduler for asynchronous execution
    scheduler->submit(std::move(task));

    // Skip the main VM's instruction pointer past the concurrent block
    ip = block_end_ip;
}

void VM::handleEndConcurrent(const Instruction& /*unused*/) {
    // This is a no-op, similar to handleEndParallel.
}

void VM::handleMatchPattern(const Instruction& /*unused*/) {
    if (matchCounter++ > 100) {
        error("Match operation limit exceeded. Possible infinite loop.");
        return;
    }

    ValuePtr pattern = pop();
    ValuePtr value = pop();

    bool match = false;

    // Wildcard pattern (null/nil)
    if (pattern->type->tag == TypeTag::Nil) {
        match = true;
    }
    // Type matching with string patterns
    else if (pattern->type->tag == TypeTag::String) {
        std::string typeName = std::get<std::string>(pattern->data);
        
        // Handle special destructuring patterns
        if (typeName == "__dict_pattern__") {
            match = handleDictPatternMatch(value);
        }
        else if (typeName == "__list_pattern__") {
            match = handleListPatternMatch(value);
        }
        else if (typeName == "__tuple_pattern__") {
            match = handleTuplePatternMatch(value);
        }
        // Handle wildcard string pattern
        else if (typeName == "_") {
            match = true;
        }
        // Type name matching
        else {
            std::string valueTypeName;
            switch(value->type->tag) {
                case TypeTag::Int: 
                case TypeTag::Int32: 
                case TypeTag::Int64: 
                    valueTypeName = "int"; 
                    break;
                case TypeTag::Float32:
                case TypeTag::Float64: 
                    valueTypeName = "float"; 
                    break;
                case TypeTag::String: 
                    valueTypeName = "str"; 
                    break;
                case TypeTag::Bool: 
                    valueTypeName = "bool"; 
                    break;
                case TypeTag::List: 
                    valueTypeName = "list"; 
                    break;
                case TypeTag::Dict: 
                    valueTypeName = "dict"; 
                    break;
                case TypeTag::Nil:
                    valueTypeName = "nil";
                    break;
                default: 
                    valueTypeName = "unknown"; 
                    break;
            }

            // Direct type matching
            if (typeName == valueTypeName) {
                match = true;
            }
            // Generic type matching (basic support)
            else if (value->type->tag == TypeTag::List && 
                     (typeName.find("list") == 0 || typeName == "array")) {
                match = true;
            }
            else if (value->type->tag == TypeTag::Dict && 
                     (typeName.find("dict") == 0 || typeName == "map" || typeName == "object")) {
                match = true;
            }
            // Range matching
            else if (typeName == "range" && value->type->tag == TypeTag::List) {
                // Check if it's a range-like list (could be enhanced)
                match = true;
            }
        }
    }
    // List pattern matching
    else if (pattern->type->tag == TypeTag::List && value->type->tag == TypeTag::List) {
        // For now, just check if both are lists - could be enhanced for structural matching
        match = true;
    }
    // Dictionary pattern matching
    else if (pattern->type->tag == TypeTag::Dict && value->type->tag == TypeTag::Dict) {
        // For now, just check if both are dicts - could be enhanced for structural matching
        match = true;
    }
    // Exact value matching
    else {
        match = valuesEqual(pattern, value);
    }

    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, match));
}

bool VM::handleDictPatternMatch(const ValuePtr& value) {
    // Stack layout (from top to bottom):
    // - pattern marker ("__dict_pattern__") [already popped]
    // - rest binding name
    // - has rest element (bool)
    // - field binding names and keys (pairs)
    // - number of fields
    
    if (value->type->tag != TypeTag::Dict) {
        // Clear the pattern data from stack and return false
        clearDictPatternFromStack();
        return false;
    }
    
    // Pop rest element info
    ValuePtr restBindingName = pop();
    ValuePtr hasRestElement = pop();
    
    // Pop number of fields
    ValuePtr numFieldsValue = pop();
    int numFields = std::get<int32_t>(numFieldsValue->data);
    
    // Get the dictionary data
    auto dictData = std::get<DictValue>(value->data);
    
    // Pop and process field patterns
    std::vector<std::pair<std::string, std::string>> fieldPatterns;
    for (int i = 0; i < numFields; i++) {
        ValuePtr bindingName = pop();
        ValuePtr keyName = pop();
        fieldPatterns.push_back({
            std::get<std::string>(keyName->data),
            std::get<std::string>(bindingName->data)
        });
    }
    
    // Check if all required fields exist
    for (const auto& [key, binding] : fieldPatterns) {
        // Create a string key value for lookup
        auto keyValue = memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, key);
        auto foundValue = dictData.get(keyValue);
        
        if (!foundValue) {
            return false; // Required field missing
        }
        
        // Bind the field value to the binding name
        environment->define(binding, foundValue);
    }
    
    // Handle rest element if present
    if (std::get<bool>(hasRestElement->data)) {
        std::string restBinding = std::get<std::string>(restBindingName->data);
        
        // Create a new dictionary with remaining fields
        DictValue restDict;
        for (const auto& [keyPtr, val] : dictData.elements) {
            // Check if this key was matched
            bool isMatched = false;
            if (keyPtr->type->tag == TypeTag::String) {
                std::string keyStr = std::get<std::string>(keyPtr->data);
                for (const auto& [patternKey, _] : fieldPatterns) {
                    if (keyStr == patternKey) {
                        isMatched = true;
                        break;
                    }
                }
            }
            if (!isMatched) {
                restDict.elements[keyPtr] = val;
            }
        }
        
        // Create and bind the rest dictionary
        auto restValue = memoryManager.makeRef<Value>(*region, typeSystem->DICT_TYPE, restDict);
        environment->define(restBinding, restValue);
    }
    
    return true;
}

bool VM::handleListPatternMatch(const ValuePtr& value) {
    // Stack layout (from top to bottom):
    // - pattern marker ("__list_pattern__") [already popped]
    // - pattern elements
    // - number of elements
    
    if (value->type->tag != TypeTag::List) {
        // Clear the pattern data from stack and return false
        clearListPatternFromStack();
        return false;
    }
    
    // Pop number of elements
    ValuePtr numElementsValue = pop();
    int numElements = std::get<int32_t>(numElementsValue->data);
    
    // Get the list data
    auto listData = std::get<ListValue>(value->data);
    
    // Check if list has the expected number of elements
    if (static_cast<int>(listData.elements.size()) != numElements) {
        // Clear remaining pattern elements from stack
        for (int i = 0; i < numElements; i++) {
            pop();
        }
        return false;
    }
    
    // Pop and match pattern elements (in reverse order)
    std::vector<ValuePtr> patterns;
    for (int i = 0; i < numElements; i++) {
        patterns.insert(patterns.begin(), pop());
    }
    
    // Match each element
    for (int i = 0; i < numElements; i++) {
        ValuePtr pattern = patterns[i];
        ValuePtr element = listData.elements[i];
        
        // Handle variable binding patterns
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(
            std::reinterpret_pointer_cast<AST::Expression>(pattern))) {
            // This is a simplified check - in a full implementation,
            // we'd need to track pattern types differently
            // For now, assume string patterns are variable bindings
            if (pattern->type->tag == TypeTag::String) {
                std::string varName = std::get<std::string>(pattern->data);
                if (varName != "_") {
                    environment->define(varName, element);
                }
            }
        }
        // For other patterns, we'd need recursive matching
    }
    
    return true;
}

bool VM::handleTuplePatternMatch(const ValuePtr& value) {
    // Stack layout (from top to bottom):
    // - pattern marker ("__tuple_pattern__") [already popped]
    // - pattern elements
    // - number of elements
    
    // For now, treat tuples as lists
    // In a full implementation, tuples would be a separate type
    return handleListPatternMatch(value);
}

void VM::clearDictPatternFromStack() {
    // Clear dict pattern data from stack when match fails
    ValuePtr restBindingName = pop();
    ValuePtr hasRestElement = pop();
    ValuePtr numFieldsValue = pop();
    int numFields = std::get<int32_t>(numFieldsValue->data);
    
    // Pop field patterns
    for (int i = 0; i < numFields * 2; i++) {
        pop();
    }
}

void VM::clearListPatternFromStack() {
    // Clear list pattern data from stack when match fails
    ValuePtr numElementsValue = pop();
    int numElements = std::get<int32_t>(numElementsValue->data);
    
    // Pop pattern elements
    for (int i = 0; i < numElements; i++) {
        pop();
    }
}

void VM::handleBeginTry(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Beginning try block at line " << instruction.line << std::endl;
    }
    // For now, just mark the beginning of a try block
    // In a full implementation, this would set up exception handling context
}

void VM::handleEndTry(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Ending try block at line " << instruction.line << std::endl;
    }
    // Clean up exception handling context
}

void VM::handleBeginHandler(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Beginning exception handler for type: " << instruction.stringValue << std::endl;
    }
    // Set up handler for specific exception type
}

void VM::handleEndHandler(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Ending exception handler at line " << instruction.line << std::endl;
    }
    // Clean up handler context
}

void VM::handleThrow(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Throwing exception at line " << instruction.line << std::endl;
    }
    
    // Pop the exception value from the stack
    ValuePtr exception = pop();
    lastException = exception;
    
    // For now, just throw a runtime error with the exception value
    std::string message = "Exception thrown: " + valueToString(exception);
    error(message);
}

void VM::handleStoreException(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Storing exception in variable: " << instruction.stringValue << std::endl;
    }
    
    // Store the last exception in the specified variable
    if (lastException) {
        environment->define(instruction.stringValue, lastException);
    } else {
        environment->define(instruction.stringValue, memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
    }
}

void VM::handleAwait(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Awaiting async result at line " << instruction.line << std::endl;
    }
    
    // Pop the awaitable value from the stack
    ValuePtr awaitable = pop();
    
    // For now, just return the value as-is
    // In a full implementation, this would handle async/await semantics
    push(awaitable);
}

void VM::handleImport(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Importing module: " << instruction.stringValue << std::endl;
    }
    
    // For now, just create a placeholder module object
    // In a full implementation, this would load and execute the module
    ValuePtr module = memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
    environment->define(instruction.stringValue, module);
}

void VM::handleBeginEnum(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Beginning enum definition: " << instruction.stringValue << std::endl;
    }
    
    // Start enum definition - for now just track the name
    currentClassBeingDefined = instruction.stringValue;
    insideClassDefinition = true;
}

void VM::handleEndEnum(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Ending enum definition at line " << instruction.line << std::endl;
    }
    
    // End enum definition
    currentClassBeingDefined = "";
    insideClassDefinition = false;
}

void VM::handleDefineEnumVariant(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Defining enum variant: " << instruction.stringValue << std::endl;
    }
    
    // For now, just create a simple enum variant value
    // In a full implementation, this would create proper enum types
    ValuePtr variant = memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, instruction.stringValue);
    environment->define(instruction.stringValue, variant);
}

void VM::handleDefineEnumVariantWithType(const Instruction& instruction) {
    if (debugMode) {
        std::cout << "[DEBUG] Defining typed enum variant: " << instruction.stringValue << std::endl;
    }
    
    // For now, just create a simple enum variant value with type info
    // In a full implementation, this would create proper typed enum variants
    ValuePtr variant = memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, instruction.stringValue);
    environment->define(instruction.stringValue, variant);
}

void VM::handleDebugPrint(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    // debug print removed
}

// Error handling instruction implementations
void VM::handleCheckError(const Instruction& instruction) {
    if (stack.empty()) {
        error("Stack underflow in CHECK_ERROR");
        return;
    }
    
    // Peek the top value without consuming it. CHECK_ERROR should push a boolean
    // indicating whether the value is an error union / error value. The bytecode
    // typically uses CHECK_ERROR followed by JUMP_IF_FALSE to decide whether to
    // handle/propagate the error while leaving the original union on the stack
    // for later UNWRAP_VALUE or PROPAGATE_ERROR.
    ValuePtr value = peek();

    bool isError = false;
    if (value && value->type) {
        if (value->type->tag == TypeTag::ErrorUnion) {
            isError = std::holds_alternative<ErrorValue>(value->data);
        } else if (std::holds_alternative<ErrorValue>(value->data)) {
            isError = true;
        }
    }

    // handleCheckError debug output removed

    // Push the boolean result onto the stack for the subsequent JUMP_IF_FALSE
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, isError));
}

void VM::handlePropagateError(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    
    ValuePtr error_value;
    if (stack.empty()) {
        if (lastException) {
            // Use the last exception if available
            error_value = lastException;
            lastException = nullptr;
            
            // using last exception
        } else {
            // no error value to propagate
            return; // No error to propagate, just return
        }
    } else {
        error_value = stack.back(); // Peek at the top value
        
        // found error value on stack
    }
    
    if (!error_value) {
        // attempted to propagate null error value
        return;
    }
    
    // Verify this is actually an error value
    if (!error_value->isError()) {
        // not an error value; not propagating
        return; // Not an error value, don't propagate
    }

    std::string errorType = "UnknownError";
    if (const auto* errorVal = error_value->getErrorValue()) {
        errorType = errorVal->errorType;
    }
    
    // If we got here, we have a valid error value to propagate
    // propagating error (log suppressed)
    
    // Remove the error value from the stack if it was there
    if (!stack.empty() && stack.back() == error_value) {
        stack.pop_back();
    }
    
    // Clear any previous exception since we're handling it now
    lastException = nullptr;
    
    // Try to propagate the error using the error frame stack
    // If no error frame exists, let propagateError return false and treat as unhandled
    
    // Now propagate the error
    if (!propagateError(error_value)) {
        // If propagation failed, try to get error information
        std::string errorMsg = "Unhandled error";
        
        try {
            if (auto errorVal = std::get_if<::ErrorValue>(&error_value->data)) {
                errorMsg = "Unhandled error: " + errorVal->errorType;
                if (!errorVal->message.empty()) {
                    errorMsg += " - " + errorVal->message;
                }
            }
        } catch (const std::exception& e) {
            // suppress diagnostic here
        }
        
        error(errorMsg);
    }
    // If propagation succeeded, execution will continue at the error handler
}

void VM::handleConstructError(const Instruction& instruction) {
    std::string errorType = instruction.stringValue;
    int32_t argCount = instruction.intValue;
    
    if (stack.size() < static_cast<size_t>(argCount)) {
        error("Stack underflow in CONSTRUCT_ERROR");
        return;
    }
    
    // Pop arguments from stack
    std::vector<ValuePtr> args;
    args.reserve(argCount);
    for (int i = 0; i < argCount; i++) {
        args.push_back(pop());
    }
    std::reverse(args.begin(), args.end());  // Maintain correct order
    
    // Create error message
    std::string errorMessage;
    if (!args.empty() && args[0]->type->tag == TypeTag::String) {
        errorMessage = std::get<std::string>(args[0]->data);
    } else {
        errorMessage = "Error occurred";
    }
    
    // Look up error type in the type system
    TypePtr errorTypePtr = typeSystem->getType(errorType);
    if (!errorTypePtr) {
        error("Unknown error type: " + errorType);
        return;
    }
    
    // Create error value with proper type information
    ErrorValue errorVal(errorType, errorMessage, args, ip);
    ValuePtr errorValue = memoryManager.makeRef<Value>(*region, errorTypePtr);
    errorValue->data = errorVal;
    
    // Create error union type
    auto errorUnionType = memoryManager.makeRef<Type>(*region, TypeTag::ErrorUnion);
    ErrorUnionType errorUnionDetails;
    errorUnionDetails.successType = typeSystem->NIL_TYPE;
    errorUnionDetails.errorTypes = {errorType};
    errorUnionDetails.isGenericError = false;
    errorUnionType->extra = errorUnionDetails;
    
    // Create the final value with the error union type
    ValuePtr result = memoryManager.makeRef<Value>(*region, errorUnionType);
    result->data = errorVal;
    
    if (debugOutput) {
        std::cerr << "[DEBUG] handleConstructError: created error '" << errorType << "' message='" << errorMessage << "'" << std::endl;
    }

    push(result);
}

void VM::handleConstructOk(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    if (stack.empty()) {
        error("Stack underflow in CONSTRUCT_OK");
        return;
    }
    
    ValuePtr successValue = pop();
    
    // Create error union type that wraps the success value
    auto errorUnionType = memoryManager.makeRef<Type>(*region, TypeTag::ErrorUnion);
    ErrorUnionType errorUnionDetails;
    errorUnionDetails.successType = successValue->type;
    errorUnionDetails.errorTypes = {}; // No specific error types for generic ok()
    errorUnionDetails.isGenericError = true;
    errorUnionType->extra = errorUnionDetails;
    
    // Create a new value with the error union type but containing the success data
    ValuePtr okValue = memoryManager.makeRef<Value>(*region, errorUnionType);
    okValue->data = successValue->data; // Copy the success value's data
    if (debugOutput) {
        std::cerr << "[DEBUG] handleConstructOk: created ok value of type " << (successValue->type ? successValue->type->toString() : "(unknown)") << std::endl;
    }

    push(okValue);
}

void VM::handleIsError(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    if (stack.empty()) {
        error("Stack underflow in IS_ERROR");
        return;
    }
    
    ValuePtr value = pop();
    
    bool isError = false;
    
    // Check if the value is an error in various forms
    if (value->type->tag == TypeTag::ErrorUnion) {
        // Check if the error union contains an ErrorValue
        isError = std::holds_alternative<ErrorValue>(value->data);
    } else if (std::holds_alternative<ErrorValue>(value->data)) {
        // Direct ErrorValue
        isError = true;
    }
    // For all other types, isError remains false
    
    // Push boolean result onto stack
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, isError));
}

void VM::handleIsSuccess(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    if (stack.empty()) {
        error("Stack underflow in IS_SUCCESS");
        return;
    }
    
    ValuePtr value = pop();
    
    bool isSuccess = true; // Default to success for non-error types
    
    // Check if the value is NOT an error
    if (value->type->tag == TypeTag::ErrorUnion) {
        // For error unions, success means NOT containing an ErrorValue
        isSuccess = !std::holds_alternative<ErrorValue>(value->data);
    } else if (std::holds_alternative<ErrorValue>(value->data)) {
        // Direct ErrorValue is not success
        isSuccess = false;
    }
    // For all other types, isSuccess remains true
    
    // Push boolean result onto stack
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, isSuccess));
}

void VM::handleUnwrapValue(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    if (stack.empty()) {
        // Always emit this diagnostic; it's critical when debugging unwrap/value errors
        std::cerr << "[DEBUG] UNWRAP_VALUE underflow: callStack=" << callStack.size() << " errorFrames=" << errorFrames.size() << " ip=" << ip << std::endl;
        error("Stack underflow in UNWRAP_VALUE");
        return;
    }
    
    ValuePtr value = pop();
    
    // Check if this is an error that should be propagated
    if (value->type->tag == TypeTag::ErrorUnion) {
        if (std::holds_alternative<ErrorValue>(value->data)) {
            // This is an error - propagate it
            push(value); // Put the error back on stack for propagation
            if (debugOutput) {
                std::cerr << "[DEBUG] handleUnwrapValue: found error, attempting propagate: " << valueToString(value) << std::endl;
            }
            if (!propagateError(value)) {
                // No error handler found
                if (auto errorVal = std::get_if<ErrorValue>(&value->data)) {
                    error("Unhandled error during unwrap: " + errorVal->errorType + 
                          (errorVal->message.empty() ? "" : " - " + errorVal->message));
                } else {
                    error("Unhandled error during unwrap: " + valueToString(value));
                }
            }
            return; // Execution continues at error handler or terminates
        } else {
            // This is a success value in an error union - extract the actual value
            // Create a new value with the original success type
            if (auto errorUnionDetails = std::get_if<ErrorUnionType>(&value->type->extra)) {
                ValuePtr unwrappedValue = memoryManager.makeRef<Value>(*region, errorUnionDetails->successType);
                unwrappedValue->data = value->data; // Copy the data
                push(unwrappedValue);
            } else {
                // Fallback: push the value as-is
                push(value);
            }
        }
    } else if (std::holds_alternative<ErrorValue>(value->data)) {
        // Direct error value - propagate it
        push(value);
        if (!propagateError(value)) {
            if (auto errorVal = std::get_if<ErrorValue>(&value->data)) {
                error("Unhandled error during unwrap: " + errorVal->errorType + 
                      (errorVal->message.empty() ? "" : " - " + errorVal->message));
            } else {
                error("Unhandled error during unwrap: " + valueToString(value));
            }
        }
    } else {
        // Not an error union or error, just push the value back (it's already "unwrapped")
        push(value);
    }
}
