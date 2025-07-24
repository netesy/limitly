#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include <string>
#include <vector>

// Bytecode operation codes
enum class Opcode {
    // Stack operations
    PUSH_INT,           // Push integer onto stack
    PUSH_FLOAT,         // Push float onto stack
    PUSH_STRING,        // Push string onto stack
    PUSH_BOOL,          // Push boolean onto stack
    PUSH_NULL,          // Push null onto stack
    POP,                // Pop value from stack
    DUP,                // Duplicate top value on stack
    SWAP,               // Swap top two values on stack

    // Variable operations
    STORE_VAR,          // Store value in variable
    LOAD_VAR,           // Load variable onto stack
    STORE_TEMP,         // Store value in temporary variable
    LOAD_TEMP,          // Load temporary variable onto stack
    CLEAR_TEMP,         // Clear temporary variable
    LOAD_THIS,          // Load 'this' reference onto stack
   
    // Arithmetic operations
    ADD,                // Add top two values
    SUBTRACT,           // Subtract top value from second value
    MULTIPLY,           // Multiply top two values
    DIVIDE,             // Divide second value by top value
    POWER,              // Raise second value to the power of top value
    MODULO,             // Modulo second value by top value
    NEGATE,             // Negate top value

    // Comparison operations
    EQUAL,              // Check if top two values are equal
    NOT_EQUAL,          // Check if top two values are not equal
    LESS,               // Check if second value is less than top value
    LESS_EQUAL,         // Check if second value is less than or equal to top value
    GREATER,            // Check if second value is greater than top value
    GREATER_EQUAL,      // Check if second value is greater than or equal to top value

    // Logical operations
    AND,                // Logical AND of top two values
    OR,                 // Logical OR of top two values
    NOT,                // Logical NOT of top value

    // Control flow operations
    JUMP,               // Jump to offset
    JUMP_IF_TRUE,       // Jump to offset if top value is true
    JUMP_IF_FALSE,      // Jump to offset if top value is false
    CALL,               // Call function
    RETURN,             // Return from function

    // Function operations
    BEGIN_FUNCTION,     // Begin function definition
    END_FUNCTION,       // End function definition
    DEFINE_PARAM,       // Define function parameter
    DEFINE_OPTIONAL_PARAM, // Define optional function parameter
    SET_DEFAULT_VALUE,  // Set default value for optional parameter

    // Class operations
    BEGIN_CLASS,        // Begin class definition
    END_CLASS,          // End class definition
    GET_PROPERTY,       // Get property from object
    SET_PROPERTY,       // Set property on object

    // Collection operations
    CREATE_LIST,        // Create empty list
    LIST_APPEND,        // Append value to list
    CREATE_DICT,        // Create empty dictionary
    CREATE_RANGE,       //
    SET_RANGE_STEP,     //
    DICT_SET,           // Set key-value pair in dictionary
    GET_INDEX,          // Get value at index
    SET_INDEX,          // Set value at index

    // Iterator operations
    GET_ITERATOR,       // Get iterator for iterable
    ITERATOR_HAS_NEXT,  // Check if iterator has next item
    ITERATOR_NEXT,      // Get next item from iterator
    ITERATOR_NEXT_KEY_VALUE, // Get next key-value pair from iterator

    // Scope operations
    BEGIN_SCOPE,        // Begin new scope
    END_SCOPE,          // End current scope

    // Exception handling operations
    BEGIN_TRY,          // Begin try block
    END_TRY,            // End try block
    BEGIN_HANDLER,      // Begin exception handler
    END_HANDLER,        // End exception handler
    THROW,              // Throw exception
    STORE_EXCEPTION,    // Store exception in variable

    // Concurrency operations
    BEGIN_PARALLEL,     // Begin parallel block
    END_PARALLEL,       // End parallel block
    BEGIN_CONCURRENT,   // Begin concurrent block
    END_CONCURRENT,     // End concurrent block
    AWAIT,              // Await async result

    // Pattern matching operations
    MATCH_PATTERN,      // Match value against pattern

    // Module operations
    IMPORT,             // Import module

    // Enum operations
    BEGIN_ENUM,         // Begin enum definition
    END_ENUM,           // End enum definition
    DEFINE_ENUM_VARIANT, // Define enum variant
    DEFINE_ENUM_VARIANT_WITH_TYPE, // Define enum variant with type

    // I/O operations
    PRINT,              // Print values

    // Debug operations
    DEBUG_PRINT,        // Print debug information

    // Memory operations
    LOAD_CONST,         // Load constant onto stack
    STORE_CONST,        // Store constant onto stack
    LOAD_MEMBER,        // Load member onto stack
    STORE_MEMBER,       // Store member onto stack
};

// Instruction structure
struct Instruction {
    Opcode opcode;
    uint32_t line;
    int32_t intValue = 0;
    float floatValue = 0.0f;
    bool boolValue = false;
    std::string stringValue;
};

// Bytecode is a vector of instructions
using Bytecode = std::vector<Instruction>;

#endif // OPCODES_H
