#include "vm.hh"
#include <iostream>
#include <sstream>
#include <thread>
#include <future>

// VM implementation
VM::VM() : ip(0) {
    // Initialize memory manager and region
    region = std::make_unique<MemoryManager<>::Region>(memoryManager);
    
    // Initialize type system
    typeSystem = new TypeSystem(memoryManager, *region);
    
    // Initialize environment
    globals = std::make_shared<Environment>();
    environment = globals;
    
    // Register native functions
    registerNativeFunction("clock", [this](const std::vector<ValuePtr>& args) -> ValuePtr {
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
                case Opcode::PRINT:
                    handlePrint(instruction);
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

void VM::error(const std::string& message) const {
    throw std::runtime_error(message);
}

// Instruction handlers
void VM::handlePushInt(const Instruction& instruction) {
    push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, instruction.intValue));
}

void VM::handlePushFloat(const Instruction& instruction) {
    push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, instruction.floatValue));
}

void VM::handlePushString(const Instruction& instruction) {
    push(memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, instruction.stringValue));
}

void VM::handlePushBool(const Instruction& instruction) {
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, instruction.boolValue));
}

void VM::handlePushNull(const Instruction& instruction) {
    push(memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE));
}

void VM::handlePop(const Instruction& instruction) {
    pop();
}

void VM::handleDup(const Instruction& instruction) {
    push(peek());
}

void VM::handleSwap(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    push(b);
    push(a);
}

void VM::handleStoreVar(const Instruction& instruction) {
    ValuePtr value = peek();
    environment->define(instruction.stringValue, value);
}

void VM::handleLoadVar(const Instruction& instruction) {
    try {
        ValuePtr value = environment->get(instruction.stringValue);
        push(value);
    } catch (const std::exception& e) {
        error("Undefined variable '" + instruction.stringValue + "'");
    }
}

void VM::handleStoreTemp(const Instruction& instruction) {
    tempValue = peek();
}

void VM::handleLoadTemp(const Instruction& instruction) {
    push(tempValue);
}

void VM::handleClearTemp(const Instruction& instruction) {
    tempValue = memoryManager.makeRef<Value>(*region, typeSystem->NIL_TYPE);
}

void VM::handleAdd(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    // String concatenation
    if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        std::string result = std::get<std::string>(a->data) + std::get<std::string>(b->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->STRING_TYPE, result));
        return;
    }
    
    // Numeric addition
    if (a->type->tag == TypeTag::Float64 || b->type->tag == TypeTag::Float64) {
        // Convert to double if needed
        double aVal = (a->type->tag == TypeTag::Float64) ? 
            std::get<double>(a->data) : 
            static_cast<double>(std::get<int32_t>(a->data));
        
        double bVal = (b->type->tag == TypeTag::Float64) ? 
            std::get<double>(b->data) : 
            static_cast<double>(std::get<int32_t>(b->data));
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, aVal + bVal));
    } else {
        // Integer addition
        int32_t aVal = std::get<int32_t>(a->data);
        int32_t bVal = std::get<int32_t>(b->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, aVal + bVal));
    }
}

void VM::handleSubtract(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    // Numeric subtraction
    if (a->type->tag == TypeTag::Float64 || b->type->tag == TypeTag::Float64) {
        // Convert to double if needed
        double aVal = (a->type->tag == TypeTag::Float64) ? 
            std::get<double>(a->data) : 
            static_cast<double>(std::get<int32_t>(a->data));
        
        double bVal = (b->type->tag == TypeTag::Float64) ? 
            std::get<double>(b->data) : 
            static_cast<double>(std::get<int32_t>(b->data));
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, aVal - bVal));
    } else {
        // Integer subtraction
        int32_t aVal = std::get<int32_t>(a->data);
        int32_t bVal = std::get<int32_t>(b->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, aVal - bVal));
    }
}

void VM::handleMultiply(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    // String multiplication (string * int)
    if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::Int) {
        std::string str = std::get<std::string>(a->data);
        int32_t count = std::get<int32_t>(b->data);
        
        std::string result;
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
    } else {
        // Integer multiplication
        int32_t aVal = std::get<int32_t>(a->data);
        int32_t bVal = std::get<int32_t>(b->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, aVal * bVal));
    }
}

void VM::handleDivide(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    // Check for division by zero
    bool isZero = false;
    
    if (b->type->tag == TypeTag::Float64) {
        isZero = std::get<double>(b->data) == 0.0;
    } else {
        isZero = std::get<int32_t>(b->data) == 0;
    }
    
    if (isZero) {
        error("Division by zero");
    }
    
    // Numeric division
    if (a->type->tag == TypeTag::Float64 || b->type->tag == TypeTag::Float64) {
        // Convert to double if needed
        double aVal = (a->type->tag == TypeTag::Float64) ? 
            std::get<double>(a->data) : 
            static_cast<double>(std::get<int32_t>(a->data));
        
        double bVal = (b->type->tag == TypeTag::Float64) ? 
            std::get<double>(b->data) : 
            static_cast<double>(std::get<int32_t>(b->data));
        
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, aVal / bVal));
    } else {
        // Integer division
        int32_t aVal = std::get<int32_t>(a->data);
        int32_t bVal = std::get<int32_t>(b->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, aVal / bVal));
    }
}

void VM::handleModulo(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    // Check for modulo by zero
    if (std::get<int32_t>(b->data) == 0) {
        error("Modulo by zero");
    }
    
    // Integer modulo
    int32_t aVal = std::get<int32_t>(a->data);
    int32_t bVal = std::get<int32_t>(b->data);
    push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, aVal % bVal));
}

void VM::handleNegate(const Instruction& instruction) {
    ValuePtr a = pop();
    
    if (a->type->tag == TypeTag::Float64) {
        double val = std::get<double>(a->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->FLOAT64_TYPE, -val));
    } else {
        int32_t val = std::get<int32_t>(a->data);
        push(memoryManager.makeRef<Value>(*region, typeSystem->INT_TYPE, -val));
    }
}

void VM::handleEqual(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types
    if (a->type->tag != b->type->tag) {
        result = false;
    } else {
        switch (a->type->tag) {
            case TypeTag::Int:
                result = std::get<int32_t>(a->data) == std::get<int32_t>(b->data);
                break;
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
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleNotEqual(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = true;
    
    // Compare based on types
    if (a->type->tag != b->type->tag) {
        result = true;
    } else {
        switch (a->type->tag) {
            case TypeTag::Int:
                result = std::get<int32_t>(a->data) != std::get<int32_t>(b->data);
                break;
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
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleLess(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types
    if (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::Int) {
        result = std::get<int32_t>(a->data) < std::get<int32_t>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Float64) {
        result = std::get<double>(a->data) < std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::Float64) {
        result = static_cast<double>(std::get<int32_t>(a->data)) < std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Int) {
        result = std::get<double>(a->data) < static_cast<double>(std::get<int32_t>(b->data));
    } else if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        result = std::get<std::string>(a->data) < std::get<std::string>(b->data);
    } else {
        error("Cannot compare values of different types");
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleLessEqual(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types
    if (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::Int) {
        result = std::get<int32_t>(a->data) <= std::get<int32_t>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Float64) {
        result = std::get<double>(a->data) <= std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::Float64) {
        result = static_cast<double>(std::get<int32_t>(a->data)) <= std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Int) {
        result = std::get<double>(a->data) <= static_cast<double>(std::get<int32_t>(b->data));
    } else if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        result = std::get<std::string>(a->data) <= std::get<std::string>(b->data);
    } else {
        error("Cannot compare values of different types");
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleGreater(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types
    if (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::Int) {
        result = std::get<int32_t>(a->data) > std::get<int32_t>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Float64) {
        result = std::get<double>(a->data) > std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::Float64) {
        result = static_cast<double>(std::get<int32_t>(a->data)) > std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Int) {
        result = std::get<double>(a->data) > static_cast<double>(std::get<int32_t>(b->data));
    } else if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        result = std::get<std::string>(a->data) > std::get<std::string>(b->data);
    } else {
        error("Cannot compare values of different types");
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleGreaterEqual(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();
    
    bool result = false;
    
    // Compare based on types
    if (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::Int) {
        result = std::get<int32_t>(a->data) >= std::get<int32_t>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Float64) {
        result = std::get<double>(a->data) >= std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Int && b->type->tag == TypeTag::Float64) {
        result = static_cast<double>(std::get<int32_t>(a->data)) >= std::get<double>(b->data);
    } else if (a->type->tag == TypeTag::Float64 && b->type->tag == TypeTag::Int) {
        result = std::get<double>(a->data) >= static_cast<double>(std::get<int32_t>(b->data));
    } else if (a->type->tag == TypeTag::String && b->type->tag == TypeTag::String) {
        result = std::get<std::string>(a->data) >= std::get<std::string>(b->data);
    } else {
        error("Cannot compare values of different types");
    }
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, result));
}

void VM::handleAnd(const Instruction& instruction) {
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

void VM::handleOr(const Instruction& instruction) {
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

void VM::handleNot(const Instruction& instruction) {
    ValuePtr a = pop();
    
    bool aVal = false;
    
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
    
    push(memoryManager.makeRef<Value>(*region, typeSystem->BOOL_TYPE, !aVal));
}

void VM::handleJump(const Instruction& instruction) {
    ip += instruction.intValue;
}

void VM::handleJumpIfTrue(const Instruction& instruction) {
    ValuePtr condition = pop();
    
    bool condVal = false;
    
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
    
    if (condVal) {
        ip += instruction.intValue;
    }
}

void VM::handleJumpIfFalse(const Instruction& instruction) {
    ValuePtr condition = pop();
    
    bool condVal = false;
    
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
    
    if (!condVal) {
        ip += instruction.intValue;
    }
}

void VM::handleCall(const Instruction& instruction) {
    // TODO: Implement function calls
    error("Function calls not implemented yet");
}

void VM::handleReturn(const Instruction& instruction) {
    // TODO: Implement function returns
    error("Function returns not implemented yet");
}

void VM::handlePrint(const Instruction& instruction) {
    int argCount = instruction.intValue;
    std::vector<ValuePtr> args;
    
    for (int i = 0; i < argCount; ++i) {
        args.insert(args.begin(), pop());
    }
    
    for (size_t i = 0; i < args.size(); ++i) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << args[i]->toString();
    }
    
    std::cout << std::endl;
}

// Placeholder implementations for other handlers
void VM::handleBeginFunction(const Instruction& instruction) { error("Not implemented"); }
void VM::handleEndFunction(const Instruction& instruction) { error("Not implemented"); }
void VM::handleDefineParam(const Instruction& instruction) { error("Not implemented"); }
void VM::handleDefineOptionalParam(const Instruction& instruction) { error("Not implemented"); }
void VM::handleSetDefaultValue(const Instruction& instruction) { error("Not implemented"); }
void VM::handleBeginClass(const Instruction& instruction) { error("Not implemented"); }
void VM::handleEndClass(const Instruction& instruction) { error("Not implemented"); }
void VM::handleGetProperty(const Instruction& instruction) { error("Not implemented"); }
void VM::handleSetProperty(const Instruction& instruction) { error("Not implemented"); }
void VM::handleCreateList(const Instruction& instruction) { error("Not implemented"); }
void VM::handleListAppend(const Instruction& instruction) { error("Not implemented"); }
void VM::handleCreateDict(const Instruction& instruction) { error("Not implemented"); }
void VM::handleDictSet(const Instruction& instruction) { error("Not implemented"); }
void VM::handleGetIndex(const Instruction& instruction) { error("Not implemented"); }
void VM::handleSetIndex(const Instruction& instruction) { error("Not implemented"); }
void VM::handleGetIterator(const Instruction& instruction) { error("Not implemented"); }
void VM::handleIteratorHasNext(const Instruction& instruction) { error("Not implemented"); }
void VM::handleIteratorNext(const Instruction& instruction) { error("Not implemented"); }
void VM::handleIteratorNextKeyValue(const Instruction& instruction) { error("Not implemented"); }
void VM::handleBeginScope(const Instruction& instruction) { error("Not implemented"); }
void VM::handleEndScope(const Instruction& instruction) { error("Not implemented"); }
void VM::handleBeginTry(const Instruction& instruction) { error("Not implemented"); }
void VM::handleEndTry(const Instruction& instruction) { error("Not implemented"); }
void VM::handleBeginHandler(const Instruction& instruction) { error("Not implemented"); }
void VM::handleEndHandler(const Instruction& instruction) { error("Not implemented"); }
void VM::handleThrow(const Instruction& instruction) { error("Not implemented"); }
void VM::handleStoreException(const Instruction& instruction) { error("Not implemented"); }
void VM::handleBeginParallel(const Instruction& instruction) { error("Not implemented"); }
void VM::handleEndParallel(const Instruction& instruction) { error("Not implemented"); }
void VM::handleBeginConcurrent(const Instruction& instruction) { error("Not implemented"); }
void VM::handleEndConcurrent(const Instruction& instruction) { error("Not implemented"); }
void VM::handleAwait(const Instruction& instruction) { error("Not implemented"); }
void VM::handleMatchPattern(const Instruction& instruction) { error("Not implemented"); }
void VM::handleImport(const Instruction& instruction) { error("Not implemented"); }
void VM::handleBeginEnum(const Instruction& instruction) { error("Not implemented"); }
void VM::handleEndEnum(const Instruction& instruction) { error("Not implemented"); }
void VM::handleDefineEnumVariant(const Instruction& instruction) { error("Not implemented"); }
void VM::handleDefineEnumVariantWithType(const Instruction& instruction) { error("Not implemented"); }
void VM::handleDebugPrint(const Instruction& instruction) { error("Not implemented"); }