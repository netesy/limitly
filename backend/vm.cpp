#include "vm.hh"
#include <iostream>
#include <thread>
#include <variant>

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

VM::VM()
    : memoryManager(1024 * 1024), // 1MB initial memory
      region(std::make_unique<MemoryManager<>::Region>(memoryManager)),
      typeSystem(new TypeSystem(memoryManager, *region)),
      globals(std::make_shared<Environment>()),
      environment(globals),
      bytecode(nullptr),
      ip(0),
      debugMode(false),
      debugOutput(false),
      currentFunctionBeingDefined(""),
      insideFunctionDefinition(false) {
    
    // Register native functions
    registerNativeFunction("clock", [this](const std::vector<ValuePtr>&) -> ValuePtr {
        auto result = memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, static_cast<double>(std::clock()) / CLOCKS_PER_SEC);
        return result;
    });
    
    registerNativeFunction("sleep", [this](const std::vector<ValuePtr>& args) -> ValuePtr {
        if (args.size() != 1) {
            throw std::runtime_error("sleep() takes exactly one number argument");
        }
        
        double seconds = 0.0;
        
        // Extract the seconds value based on the type
        if (std::holds_alternative<double>(args[0]->data)) {
            seconds = std::get<double>(args[0]->data);
        } else if (std::holds_alternative<float>(args[0]->data)) {
            seconds = std::get<float>(args[0]->data);
        } else if (std::holds_alternative<int32_t>(args[0]->data)) {
            seconds = std::get<int32_t>(args[0]->data);
        } else if (std::holds_alternative<int64_t>(args[0]->data)) {
            seconds = std::get<int64_t>(args[0]->data);
        } else {
            throw std::runtime_error("sleep() argument must be a number");
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(seconds * 1000)));
        return memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
    });
}

VM::~VM() {
    delete typeSystem;
}

ValuePtr VM::execute(const std::vector<Instruction>& bytecode) {
    this->bytecode = &bytecode;
    ip = 0;
    
    try {
        while (ip < bytecode.size()) {
            const Instruction& instruction = bytecode[ip];
            
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
                case Opcode::LOAD_THIS:
                    handleLoadThis(instruction);
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
                default:
                    error("Unknown opcode: " + std::to_string(static_cast<int>(instruction.opcode)));
                    break;
            }
            
            ip++;
        }
    } catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
    }
    return stack.empty() ? memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE) : stack.back();
}
void VM::registerNativeFunction(const std::string& name, std::function<ValuePtr(const std::vector<ValuePtr>&)> function) {
    nativeFunctions[name] = function;
    
    // Also register with the function registry for consistency
    std::vector<backend::Parameter> params; // Empty for now, could be enhanced
    functionRegistry.registerNativeFunction(name, params, std::nullopt, function);
}

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
    (void)instruction; // Mark as unused
    ValuePtr value = pop();
    environment->define(instruction.stringValue, value);
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
        error("Both operands must be numbers for division");
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
        error("Division by " + zeroType + " is not allowed");
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
            error("Floating-point division resulted in infinity");
        }
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, aVal / bVal));
    } else {
        // Integer division with check for INT_MIN / -1 overflow
        int32_t aVal = std::get<int32_t>(a->data);
        int32_t bVal = std::get<int32_t>(b->data);
        
        if (aVal == std::numeric_limits<int32_t>::min() && bVal == -1) {
            error("Integer division overflow");
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
    
    // Collect arguments from the stack (in reverse order)
    std::vector<ValuePtr> args;
    args.reserve(argCount);
    for (int i = 0; i < argCount; i++) {
        args.insert(args.begin(), pop()); // Insert at beginning to maintain order
    }
    
    // Check if this is a method call (function name starts with "method:")
    if (funcName.substr(0, 7) == "method:") {
        std::string methodName = funcName.substr(7); // Remove "method:" prefix
        
        // The object should be the last argument (pushed first due to our calling convention)
        if (args.empty()) {
            error("Method call without object");
            return;
        }
        
        // Get the object (last argument)
        ValuePtr objectValue = args.back();
        std::vector<ValuePtr> methodArgs(args.begin(), args.end() - 1); // Remove object from args
        
        // Check if the object is an ObjectInstance
        if (std::holds_alternative<ObjectInstancePtr>(objectValue->data)) {
            auto objectInstance = std::get<ObjectInstancePtr>(objectValue->data);
            
            // Call the method on the object
            try {
                ValuePtr result = objectInstance->callMethod(methodName, methodArgs);
                push(result);
                return;
            } catch (const std::exception& e) {
                error("Method call failed: " + std::string(e.what()));
                return;
            }
        } else {
            error("Cannot call method on non-object value");
            return;
        }
    }
    
    // Check if this is a class constructor call
    if (classRegistry.hasClass(funcName)) {
        // Create instance of the class
        auto instance = classRegistry.createInstance(funcName);
        
        // TODO: Call constructor method if it exists (e.g., "init")
        // For now, just create the instance and push it
        auto objectType = std::make_shared<Type>(TypeTag::Object);
        push(memoryManager.makeRef<Value>(*region, objectType, instance));
        return;
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
        error("RETURN outside of function call");
        return;
    }
    
    // The return value should already be on the stack
    ValuePtr returnValue;
    if (!stack.empty()) {
        returnValue = pop();
    } else {
        // No explicit return value, use nil
        returnValue = memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
    }
    
    // Pop the call frame and return to the caller
    backend::CallFrame frame = callStack.back();
    callStack.pop_back();
    
    // Restore the environment
    auto prevEnv = frame.getPreviousEnvironment<Environment>();
    if (prevEnv) {
        environment = prevEnv;
    } else {
        environment = globals; // Fallback
    }
    
    // Push the return value
    push(returnValue);
    
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
    currentFunctionBeingDefined = funcName;
    
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
    
    // Store the function
    userDefinedFunctions[funcName] = func;
    
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
    
    // Create a basic class definition
    auto classDef = std::make_shared<backend::ClassDefinition>(className);
    
    // Register the class
    classRegistry.registerClass(classDef);
    
    // TODO: We'll need to collect methods and fields as we encounter them
    // For now, just register an empty class
}
void VM::handleEndClass(const Instruction& /*unused*/) {
    // End of class definition
    // TODO: Finalize class definition
}
void VM::handleLoadThis(const Instruction& /*unused*/) {
    // Load 'this' reference onto the stack
    // For now, we'll need to implement a way to track the current object instance
    // This will be enhanced when we implement proper object instantiation
    
    // TODO: Get current object instance from call frame or context
    // For now, push null as placeholder
    push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
}
void VM::handleGetProperty(const Instruction& instruction) {
    // Get property name from instruction
    std::string propertyName = instruction.stringValue;
    
    // Pop the object from the stack
    ValuePtr object = pop();
    
    // TODO: Implement proper property access
    // For now, just push null as placeholder
    push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
}
void VM::handleSetProperty(const Instruction& instruction) {
    // Get property name from instruction
    std::string propertyName = instruction.stringValue;
    
    // Pop the value and object from the stack
    ValuePtr value = pop();
    ValuePtr object = pop();
    
    // TODO: Implement proper property setting
    // For now, just continue execution
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
void VM::handleBeginTry(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleBeginHandler(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleEndHandler(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleThrow(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleStoreException(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleBeginParallel(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleEndParallel(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleBeginConcurrent(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleEndConcurrent(const Instruction& /*unused*/) { error("Not implemented"); }

void VM::handleMatchPattern(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleImport(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleBeginEnum(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleEndEnum(const Instruction& /*unused*/) { error("Not implemented"); }
void VM::handleDefineEnumVariant(const Instruction& /*unused*/) { error("Not implemented"); }

void VM::handleDebugPrint(const Instruction& instruction) {
    (void)instruction; // Mark as unused
    if (stack.empty()) {
        std::cerr << "[DEBUG] Stack is empty" << std::endl;
    } else {
        ValuePtr value = stack.back(); // Peek at the top value without popping
        std::cerr << "[DEBUG] Stack top: " << valueToString(value) << std::endl;
    }
}
