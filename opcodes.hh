//opcodes.h
#pragma once
#include <cstdint>
#include <string>
#include <vector>

enum class Opcode {
    // Arithmetic operations
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULUS,

    // Comparison operations
    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,

    // Logical operations
    AND,
    OR,
    NOT,

    // Control flow operations
    JUMP,
    JUMP_IF_TRUE,
    JUMP_IF_FALSE,
    RETURN,

    // Variable operations
    DECLARE_VARIABLE,
    LOAD_VARIABLE,
    STORE_VARIABLE,

    // Other operations
    NOP,   // No operation
    HALT,  // Halt execution
    PRINT, // Print

    // Function definition and invocation
    DEFINE_FUNCTION,
    INVOKE_FUNCTION,
    RETURN_VALUE,

    // Loop operations
    FOR_LOOP,
    WHILE_LOOP,

    // Error handling operations
    ATTEMPT,
    HANDLE,

    // Class operations
    DEFINE_CLASS,
    CREATE_OBJECT,
    METHOD_CALL,

    // File I/O operations
    OPEN_FILE,
    WRITE_FILE,
    CLOSE_FILE,

    // Concurrency operations
    PARALLEL,
    CONCURRENT,
    ASYNC,

    // Generics operations
    GENERIC_FUNCTION,
    GENERIC_TYPE,

    // Pattern matching operations (potentially included)
    PATTERN_MATCH,

    // Additional operations for saving, retrieving values, and string manipulation
    LOAD_VALUE,     // Load value from memory
    STORE_VALUE,    // Store value to memory
    LOAD_STR,       // Load strings from memory
    STORE_STR,      // Store strings to memory
    CONCATENATE_STR // Concatenate strings
};

// Define a struct to represent bytecode instructions
struct Instruction
{
    Opcode opcode;
    uint32_t lineNumber; // Line number in the source code
    // Additional fields for operands, labels, etc.
    // Add any other metadata needed for debugging or bytecode generation

    // Fields for saving values
    int32_t intValue; // For integer values
    float floatValue; // For floating-point values
    bool boolValue;   // For boolean values

    // Fields for saving strings
    std::string stringValue; // For string values

    // Constructor for instructions with integer value
    Instruction(Opcode op, uint32_t line, int32_t value)
        : opcode(op)
        , lineNumber(line)
        , intValue(value)
    {}

    // Constructor for instructions with floating-point value
    Instruction(Opcode op, uint32_t line, float value)
        : opcode(op)
        , lineNumber(line)
        , floatValue(value)
    {}

    // Constructor for instructions with boolean value
    Instruction(Opcode op, uint32_t line, bool value)
        : opcode(op)
        , lineNumber(line)
        , boolValue(value)
    {}

    // Constructor for instructions with string value
    Instruction(Opcode op, uint32_t line, const std::string &value)
        : opcode(op)
        , lineNumber(line)
        , stringValue(value)
    {}

    // Constructor for instructions without value
    Instruction(Opcode op, uint32_t line)
        : opcode(op)
        , lineNumber(line)
    {}
};

// Define a vector type to hold bytecode instructions
using Bytecode = std::vector<Instruction>;
