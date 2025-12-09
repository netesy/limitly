#include "vm.hh"
#include "value.hh"
#include "type_system.hh"
#include <iostream>

VM::VM(bool create_runtime)
    : typeSystem(new TypeSystem()),
      globals(std::make_shared<Environment>()),
      environment(globals),
      bytecode(nullptr),
      ip(0),
      debugMode(false),
      debugOutput(false) {
}

VM::~VM() {
    delete typeSystem;
}

ValuePtr VM::execute(const std::vector<Instruction>& code) {
    this->bytecode = &code;
    ip = 0;
    while (ip < code.size()) {
        const Instruction& instruction = code[ip];
        ip++;
        switch (instruction.opcode) {
            case Opcode::PUSH_INT: handlePushInt(instruction); break;
            case Opcode::PUSH_UINT64: handlePushUint64(instruction); break;
            case Opcode::PUSH_FLOAT: handlePushFloat(instruction); break;
            case Opcode::PUSH_STRING: handlePushString(instruction); break;
            case Opcode::PUSH_BOOL: handlePushBool(instruction); break;
            case Opcode::PUSH_NULL: handlePushNull(instruction); break;
            case Opcode::POP: handlePop(instruction); break;
            case Opcode::ADD: handleAdd(instruction); break;
            case Opcode::PRINT: handlePrint(instruction); break;
            case Opcode::HALT: return stack.empty() ? std::make_shared<Value>(typeSystem->NIL_TYPE) : pop();
            default: break;
        }
    }
    return stack.empty() ? std::make_shared<Value>(typeSystem->NIL_TYPE) : pop();
}

void VM::handlePushInt(const Instruction& instruction) {
    push(std::make_shared<Value>(typeSystem->INT64_TYPE, instruction.intValue));
}

void VM::handlePushUint64(const Instruction& instruction) {
    push(std::make_shared<Value>(typeSystem->UINT64_TYPE, instruction.uint64Value));
}

void VM::handlePushFloat(const Instruction& instruction) {
    push(std::make_shared<Value>(typeSystem->FLOAT64_TYPE, static_cast<double>(instruction.floatValue)));
}

void VM::handlePushString(const Instruction& instruction) {
    push(std::make_shared<Value>(typeSystem->STRING_TYPE, instruction.stringValue));
}

void VM::handlePushBool(const Instruction& instruction) {
    push(std::make_shared<Value>(typeSystem->BOOL_TYPE, instruction.boolValue));
}

void VM::handlePushNull(const Instruction& instruction) {
    push(std::make_shared<Value>(typeSystem->NIL_TYPE, nullptr));
}

void VM::handlePop(const Instruction& instruction) {
    pop();
}

void VM::handleAdd(const Instruction& instruction) {
    ValuePtr b = pop();
    ValuePtr a = pop();

    if (typeSystem->isNumericType(a->type) && typeSystem->isNumericType(b->type)) {
        if (std::holds_alternative<PrimitiveType>(a->type->data) && std::get<PrimitiveType>(a->type->data).name == "float64" ||
            std::holds_alternative<PrimitiveType>(b->type->data) && std::get<PrimitiveType>(b->type->data).name == "float64") {
            double result = (std::holds_alternative<long long>(a->data) ? static_cast<double>(std::get<long long>(a->data)) : std::get<double>(a->data)) +
                            (std::holds_alternative<long long>(b->data) ? static_cast<double>(std::get<long long>(b->data)) : std::get<double>(b->data));
            push(std::make_shared<Value>(typeSystem->FLOAT64_TYPE, result));
        } else if (std::holds_alternative<PrimitiveType>(a->type->data) && std::get<PrimitiveType>(a->type->data).name == "uint64" ||
                   std::holds_alternative<PrimitiveType>(b->type->data) && std::get<PrimitiveType>(b->type->data).name == "uint64") {
            unsigned long long result = (std::holds_alternative<unsigned long long>(a->data) ? std::get<unsigned long long>(a->data) : static_cast<unsigned long long>(std::get<long long>(a->data))) +
                                        (std::holds_alternative<unsigned long long>(b->data) ? std::get<unsigned long long>(b->data) : static_cast<unsigned long long>(std::get<long long>(b->data)));
            push(std::make_shared<Value>(typeSystem->UINT64_TYPE, result));
        } else {
            long long result = std::get<long long>(a->data) + std::get<long long>(b->data);
            push(std::make_shared<Value>(typeSystem->INT64_TYPE, result));
        }
    }
}

void VM::handlePrint(const Instruction& instruction) {
    ValuePtr value = pop();
    std::cout << valueToString(value) << std::endl;
}

std::string VM::valueToString(const ValuePtr& value) {
    if (!value) return "nil";
    return std::visit(
        [](auto&& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::nullptr_t>) return "nil";
            else if constexpr (std::is_same_v<T, bool>) return arg ? "true" : "false";
            else if constexpr (std::is_same_v<T, long long>) return std::to_string(arg);
            else if constexpr (std::is_same_v<T, unsigned long long>) return std::to_string(arg);
            else if constexpr (std::is_same_v<T, double>) return std::to_string(arg);
            else if constexpr (std::is_same_v<T, std::string>) return arg;
            else return "unprintable";
        },
        value->data
    );
}

ValuePtr VM::pop() {
    if (stack.empty()) {
        return std::make_shared<Value>(typeSystem->NIL_TYPE);
    }
    ValuePtr val = stack.back();
    stack.pop_back();
    return val;
}

void VM::push(const ValuePtr& value) {
    stack.push_back(value);
}

ValuePtr VM::peek(int distance) const {
    if (stack.size() <= static_cast<size_t>(distance)) {
        return std::make_shared<Value>(typeSystem->NIL_TYPE);
    }
    return stack[stack.size() - 1 - distance];
}

void VM::preProcessBytecode(const std::vector<Instruction>& code) {
    // Simplified
}

void VM::registerNativeFunction(const std::string& name, std::function<ValuePtr(const std::vector<ValuePtr>&)> function) {
    // Simplified
}

void VM::registerUserFunction(const std::shared_ptr<AST::FunctionDeclaration>& decl) {
    // Simplified
}
