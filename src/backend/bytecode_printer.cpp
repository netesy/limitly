#include "bytecode_printer.hh"
#include <iomanip>
#include <sstream>

void BytecodePrinter::print(const std::vector<Instruction>& bytecode) {
    print(bytecode, std::cout);
}

void BytecodePrinter::print(const std::vector<Instruction>& bytecode, std::ostream& out) {
    out << "=== Bytecode ===\n";
    out << "Generated " << bytecode.size() << " instructions\n\n";
    
    for (size_t i = 0; i < bytecode.size(); ++i) {
        out << formatInstruction(bytecode[i], i) << "\n";
    }
    out << std::endl;
}

std::string BytecodePrinter::opcodeToString(Opcode opcode) {
    switch (opcode) {
        case Opcode::PUSH_INT: return "PUSH_INT";
        case Opcode::PUSH_FLOAT: return "PUSH_FLOAT";
        case Opcode::PUSH_STRING: return "PUSH_STRING";
        case Opcode::PUSH_BOOL: return "PUSH_BOOL";
        case Opcode::PUSH_NULL: return "PUSH_NULL";
        case Opcode::POP: return "POP";
        case Opcode::DUP: return "DUP";
        case Opcode::SWAP: return "SWAP";
        case Opcode::STORE_VAR: return "STORE_VAR";
        case Opcode::LOAD_VAR: return "LOAD_VAR";
        case Opcode::STORE_TEMP: return "STORE_TEMP";
        case Opcode::LOAD_TEMP: return "LOAD_TEMP";
        case Opcode::CLEAR_TEMP: return "CLEAR_TEMP";
        case Opcode::ADD: return "ADD";
        case Opcode::SUBTRACT: return "SUBTRACT";
        case Opcode::MULTIPLY: return "MULTIPLY";
        case Opcode::DIVIDE: return "DIVIDE";
        case Opcode::MODULO: return "MODULO";
        case Opcode::NEGATE: return "NEGATE";
        case Opcode::EQUAL: return "EQUAL";
        case Opcode::NOT_EQUAL: return "NOT_EQUAL";
        case Opcode::LESS: return "LESS";
        case Opcode::LESS_EQUAL: return "LESS_EQUAL";
        case Opcode::GREATER: return "GREATER";
        case Opcode::GREATER_EQUAL: return "GREATER_EQUAL";
        case Opcode::AND: return "AND";
        case Opcode::OR: return "OR";
        case Opcode::NOT: return "NOT";
        case Opcode::INTERPOLATE_STRING: return "INTERPOLATE_STRING";
        case Opcode::CONCAT: return "CONCAT";
        case Opcode::JUMP: return "JUMP";
        case Opcode::JUMP_IF_TRUE: return "JUMP_IF_TRUE";
        case Opcode::JUMP_IF_FALSE: return "JUMP_IF_FALSE";
        case Opcode::CALL: return "CALL";
        case Opcode::RETURN: return "RETURN";
        case Opcode::BEGIN_FUNCTION: return "BEGIN_FUNCTION";
        case Opcode::END_FUNCTION: return "END_FUNCTION";
        case Opcode::DEFINE_PARAM: return "DEFINE_PARAM";
        case Opcode::DEFINE_OPTIONAL_PARAM: return "DEFINE_OPTIONAL_PARAM";
        case Opcode::SET_DEFAULT_VALUE: return "SET_DEFAULT_VALUE";
        case Opcode::PUSH_FUNCTION: return "PUSH_FUNCTION";
        case Opcode::PRINT: return "PRINT";
        case Opcode::CREATE_LIST: return "CREATE_LIST";
        case Opcode::LIST_APPEND: return "LIST_APPEND";
        case Opcode::CREATE_DICT: return "CREATE_DICT";
        case Opcode::DICT_SET: return "DICT_SET";
        case Opcode::GET_INDEX: return "GET_INDEX";
        case Opcode::SET_INDEX: return "SET_INDEX";
        case Opcode::CREATE_RANGE: return "CREATE_RANGE";
        case Opcode::GET_ITERATOR: return "GET_ITERATOR";
        case Opcode::ITERATOR_HAS_NEXT: return "ITERATOR_HAS_NEXT";
        case Opcode::ITERATOR_NEXT: return "ITERATOR_NEXT";
        case Opcode::ITERATOR_NEXT_KEY_VALUE: return "ITERATOR_NEXT_KEY_VALUE";
        case Opcode::BEGIN_CLASS: return "BEGIN_CLASS";
        case Opcode::END_CLASS: return "END_CLASS";
        case Opcode::SET_SUPERCLASS: return "SET_SUPERCLASS";
        case Opcode::DEFINE_FIELD: return "DEFINE_FIELD";
        case Opcode::DEFINE_ATOMIC: return "DEFINE_ATOMIC";
        case Opcode::LOAD_THIS: return "LOAD_THIS";
        case Opcode::LOAD_SUPER: return "LOAD_SUPER";
        case Opcode::GET_PROPERTY: return "GET_PROPERTY";
        case Opcode::SET_PROPERTY: return "SET_PROPERTY";
        case Opcode::BEGIN_SCOPE: return "BEGIN_SCOPE";
        case Opcode::END_SCOPE: return "END_SCOPE";
        case Opcode::MATCH_PATTERN: return "MATCH_PATTERN";
        case Opcode::BEGIN_PARALLEL: return "BEGIN_PARALLEL";
        case Opcode::END_PARALLEL: return "END_PARALLEL";
        case Opcode::BEGIN_CONCURRENT: return "BEGIN_CONCURRENT";
        case Opcode::END_CONCURRENT: return "END_CONCURRENT";
        case Opcode::BEGIN_TRY: return "BEGIN_TRY";
        case Opcode::END_TRY: return "END_TRY";
        case Opcode::BEGIN_HANDLER: return "BEGIN_HANDLER";
        case Opcode::END_HANDLER: return "END_HANDLER";
        case Opcode::THROW: return "THROW";
        case Opcode::STORE_EXCEPTION: return "STORE_EXCEPTION";
        case Opcode::AWAIT: return "AWAIT";
        case Opcode::IMPORT_MODULE: return "IMPORT_MODULE";
        case Opcode::IMPORT_ALIAS: return "IMPORT_ALIAS";
        case Opcode::IMPORT_FILTER_SHOW: return "IMPORT_FILTER_SHOW";
        case Opcode::IMPORT_FILTER_HIDE: return "IMPORT_FILTER_HIDE";
        case Opcode::IMPORT_ADD_IDENTIFIER: return "IMPORT_ADD_IDENTIFIER";
        case Opcode::IMPORT_EXECUTE: return "IMPORT_EXECUTE";
        case Opcode::BEGIN_ENUM: return "BEGIN_ENUM";
        case Opcode::END_ENUM: return "END_ENUM";
        case Opcode::DEFINE_ENUM_VARIANT: return "DEFINE_ENUM_VARIANT";
        case Opcode::DEFINE_ENUM_VARIANT_WITH_TYPE: return "DEFINE_ENUM_VARIANT_WITH_TYPE";
        case Opcode::DEBUG_PRINT: return "DEBUG_PRINT";
        case Opcode::CHECK_ERROR: return "CHECK_ERROR";
        case Opcode::PROPAGATE_ERROR: return "PROPAGATE_ERROR";
        case Opcode::CONSTRUCT_ERROR: return "CONSTRUCT_ERROR";
        case Opcode::CONSTRUCT_OK: return "CONSTRUCT_OK";
        case Opcode::IS_ERROR: return "IS_ERROR";
        case Opcode::IS_SUCCESS: return "IS_SUCCESS";
        case Opcode::UNWRAP_VALUE: return "UNWRAP_VALUE";
        
        // Closure operations
        case Opcode::CREATE_CLOSURE: return "CREATE_CLOSURE";
        case Opcode::CAPTURE_VAR: return "CAPTURE_VAR";
        case Opcode::PUSH_LAMBDA: return "PUSH_LAMBDA";
        case Opcode::CALL_CLOSURE: return "CALL_CLOSURE";
        
        // Higher-order function operations
        case Opcode::PUSH_FUNCTION_REF: return "PUSH_FUNCTION_REF";
        case Opcode::CALL_HIGHER_ORDER: return "CALL_HIGHER_ORDER";
        
        case Opcode::BREAK: return "BREAK";
        case Opcode::CONTINUE: return "CONTINUE";
        case Opcode::SET_RANGE_STEP: return "SET_RANGE_STEP";
        case Opcode::BEGIN_TASK: return "BEGIN_TASK";
        case Opcode::END_TASK: return "END_TASK";
        case Opcode::BEGIN_WORKER: return "BEGIN_WORKER";
        case Opcode::END_WORKER: return "END_WORKER";
        case Opcode::STORE_ITERABLE: return "STORE_ITERABLE";
        case Opcode::LOAD_CONST: return "LOAD_CONST";
        case Opcode::STORE_CONST: return "STORE_CONST";
        case Opcode::LOAD_MEMBER: return "LOAD_MEMBER";
        case Opcode::STORE_MEMBER: return "STORE_MEMBER";
        case Opcode::HALT: return "HALT";
        default: return "UNKNOWN";
    }
}

std::string BytecodePrinter::formatInstruction(const Instruction& instruction, size_t index) {
    std::ostringstream oss;
    
    // Format: [index] OPCODE operands
    oss << std::setw(4) << index << ": ";
    oss << std::setw(20) << std::left << opcodeToString(instruction.opcode);
    
    // Add operands based on instruction type and opcode
    switch (instruction.opcode) {
        case Opcode::PUSH_INT:
        case Opcode::JUMP:
        case Opcode::JUMP_IF_TRUE:
        case Opcode::JUMP_IF_FALSE:
            oss << " " << instruction.intValue;
            break;
            
        case Opcode::PUSH_FLOAT:
            oss << " " << instruction.floatValue;
            break;
            
        case Opcode::PUSH_BOOL:
            oss << " " << (instruction.boolValue ? "true" : "false");
            break;
            
        case Opcode::PUSH_STRING:
        case Opcode::STORE_VAR:
        case Opcode::LOAD_VAR:
        case Opcode::BEGIN_FUNCTION:
        case Opcode::CALL:
        case Opcode::IMPORT_MODULE:
        case Opcode::IMPORT_ALIAS:
        case Opcode::GET_PROPERTY:
        case Opcode::SET_PROPERTY:
        case Opcode::BEGIN_CLASS:
        case Opcode::DEFINE_FIELD:
        case Opcode::CAPTURE_VAR:
        case Opcode::PUSH_FUNCTION_REF:
            if (!instruction.stringValue.empty()) {
                oss << " \"" << instruction.stringValue << "\"";
            }
            break;
            
        case Opcode::CREATE_CLOSURE:
        case Opcode::CALL_CLOSURE:
        case Opcode::CALL_HIGHER_ORDER:
            // These might have both int and string values
            if (!instruction.stringValue.empty()) {
                oss << " \"" << instruction.stringValue << "\"";
            }
            if (instruction.intValue != 0) {
                oss << " " << instruction.intValue;
            }
            break;
            
        default:
            // No operands for most instructions
            break;
    }
    
    return oss.str();
}