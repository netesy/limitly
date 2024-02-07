#include "stack.hh"
#include <iostream>
#include <thread>
#include <vector>

stackVM::stackVM()
    : ip(0)
{}

void stackVM::loadBytecode(const std::vector<Instruction> &bytecode)
{
    this->bytecode = bytecode;
}

void stackVM::execute()
{
    while (ip < bytecode.size()) {
        executeInstruction(bytecode[ip]);
        ip++;
    }
}

void stackVM::executeInstruction(const Instruction &instruction)
{
    switch (instruction.opcode) {
    // Arithmetic operations
    case Opcode::ADD:
        add();
        break;
    case Opcode::SUBTRACT:
        subtract();
        break;
    case Opcode::MULTIPLY:
        multiply();
        break;
    case Opcode::DIVIDE:
        divide();
        break;
    case Opcode::MODULUS:
        modulus();
        break;

        // Comparison operations
    case Opcode::EQUAL:
        equal();
        break;
    case Opcode::NOT_EQUAL:
        notEqual();
        break;
    case Opcode::LESS_THAN:
        lessThan();
        break;
    case Opcode::LESS_THAN_OR_EQUAL:
        lessThanOrEqual();
        break;
    case Opcode::GREATER_THAN:
        greaterThan();
        break;
    case Opcode::GREATER_THAN_OR_EQUAL:
        greaterThanOrEqual();
        break;

        // Logical operations
    case Opcode::AND:
        logicalAnd();
        break;
    case Opcode::OR:
        logicalOr();
        break;
    case Opcode::NOT:
        logicalNot();
        break;

        // Control flow operations
    case Opcode::JUMP:
        jump(instruction.lineNumber);
        break;
    case Opcode::JUMP_IF_TRUE:
        jumpIfTrue(instruction.lineNumber);
        break;
    case Opcode::JUMP_IF_FALSE:
        jumpIfFalse(instruction.lineNumber);
        break;
    case Opcode::RETURN:
        returnOpcode();
        break;

        // Variable operations
    case Opcode::DECLARE_VARIABLE:
        declareVariable();
        break;
    case Opcode::LOAD_VARIABLE:
        loadVariable();
        break;
    case Opcode::STORE_VARIABLE:
        storeVariable();
        break;

        // Function call operations
    case Opcode::DEFINE_FUNCTION:
        defineFunction(); // Implement defineFunction method
        break;
    case Opcode::INVOKE_FUNCTION:
        callFunction(instruction.lineNumber); // Pass function address
        break;
    case Opcode::RETURN_VALUE:
        returnValue();
        break;

        // Loop operations
    case Opcode::FOR_LOOP:
        forLoop(); // Implement forLoop method
        break;
    case Opcode::WHILE_LOOP:
        whileLoop(); // Implement whileLoop method
        break;

        // Error handling operations
    case Opcode::ATTEMPT:
        attemptOpcode(); // Implement attemptOpcode method
        break;
    case Opcode::HANDLE:
        handleOpcode(); // Implement handleOpcode method
        break;

        // Class operations
    case Opcode::DEFINE_CLASS:
        defineClass(); // Implement defineClass method
        break;
    case Opcode::CREATE_OBJECT:
        createObject(); // Implement createObject method
        break;
    case Opcode::METHOD_CALL:
        methodCall(); // Implement methodCall method
        break;

        // File I/O operations
    case Opcode::OPEN_FILE:
        openFile(); // Implement openFile method
        break;
    case Opcode::WRITE_FILE:
        writeFile(); // Implement writeFile method
        break;
    case Opcode::CLOSE_FILE:
        closeFile(); // Implement closeFile method
        break;

        // Concurrency operations
    case Opcode::PARALLEL:
        parallel(); // Implement parallel method
        break;
    case Opcode::CONCURRENT:
        concurrent(); // Implement concurrent method
        break;
    case Opcode::ASYNC:
        async(); // Implement async method
        break;

        // Generics operations
    case Opcode::GENERIC_FUNCTION:
        genericFunction(); // Implement genericFunction method
        break;
    case Opcode::GENERIC_TYPE:
        genericType(); // Implement genericType method
        break;

        // Pattern matching operations (potentially included)
    case Opcode::PATTERN_MATCH:
        patternMatch(); // Implement patternMatch method
        break;

        // Other operations
    case Opcode::NOP:
        // No operation, do nothing
        break;
    case Opcode::HALT:
        halt();
        break;

    default:
        // Handle unsupported opcode
        std::cerr << "Error: Unsupported opcode encountered." << std::endl;
        break;
    }
}

int stackVM::pop()
{
    if (stack.empty()) {
        // Handle stack underflow error
        std::cerr << "Error: Stack underflow." << std::endl;
        return 0; // Return default value for now
    }
    int value = stack.back();
    stack.pop_back();
    return value;
}

void stackVM::push(int value)
{
    stack.push_back(value);
}

std::string stackVM::popVariableName()
{
    if (variables.empty()) {
        std::cerr << "Error: No variable name on stack." << std::endl;
        return ""; // Return empty string for now
    }

    auto lastVariable = variables.rbegin();          // Get reverse iterator to the last element
    std::string variableName = lastVariable->first;  // Access the key (variable name)
    variables.erase(std::next(lastVariable).base()); // Erase the last element from the map

    return variableName;
}

// Arithmetic operations
void stackVM::add()
{
    int b = pop();
    int a = pop();
    push(a + b);
}

void stackVM::subtract()
{
    int b = pop();
    int a = pop();
    push(a - b);
}

void stackVM::multiply()
{
    int b = pop();
    int a = pop();
    push(a * b);
}

void stackVM::divide()
{
    int b = pop();
    int a = pop();
    if (b == 0) {
        // Handle division by zero error
        std::cerr << "Error: Division by zero." << std::endl;
        push(0); // Push default value for now
    } else {
        push(a / b);
    }
}

void stackVM::modulus()
{
    int b = pop();
    int a = pop();
    if (b == 0) {
        // Handle division by zero error
        std::cerr << "Error: Division by zero." << std::endl;
        push(0); // Push default value for now
    } else {
        push(a % b);
    }
}

// Comparison operations
void stackVM::equal()
{
    int b = pop();
    int a = pop();
    push(a == b ? 1 : 0);
}

void stackVM::notEqual()
{
    int b = pop();
    int a = pop();
    push(a != b ? 1 : 0);
}

void stackVM::lessThan()
{
    int b = pop();
    int a = pop();
    push(a < b ? 1 : 0);
}

void stackVM::lessThanOrEqual()
{
    int b = pop();
    int a = pop();
    push(a <= b ? 1 : 0);
}

void stackVM::greaterThan()
{
    int b = pop();
    int a = pop();
    push(a > b ? 1 : 0);
}

void stackVM::greaterThanOrEqual()
{
    int b = pop();
    int a = pop();
    push(a >= b ? 1 : 0);
}

// Logical operations
void stackVM::logicalAnd()
{
    int b = pop();
    int a = pop();
    push((a != 0) && (b != 0) ? 1 : 0);
}

void stackVM::logicalOr()
{
    int b = pop();
    int a = pop();
    push((a != 0) || (b != 0) ? 1 : 0);
}

void stackVM::logicalNot()
{
    int a = pop();
    push(a == 0 ? 1 : 0);
}

// Control flow operations
void stackVM::jump(uint32_t lineNumber)
{
    ip = lineNumber;
}

void stackVM::jumpIfTrue(uint32_t lineNumber)
{
    int condition = pop();
    if (condition != 0) {
        ip = lineNumber;
    }
}

void stackVM::jumpIfFalse(uint32_t lineNumber)
{
    int condition = pop();
    if (condition == 0) {
        ip = lineNumber;
    }
}

void stackVM::forLoop()
{
    // Stack manipulation to get loop parameters (start, end, step)
    int step = pop();
    int end = pop();
    int start = pop();

    // Variable to keep track of loop index
    int i = start;

    // Loop from start to end with the specified step
    while (i < end) {
        // Execute loop body
        // Loop body can contain any bytecode instructions inside the bytecode vector
        // Execute bytecode instructions from 'startLoop' index to 'endLoop' index
        uint32_t startLoop = ip + 1;         // Start of loop body (current instruction index + 1)
        uint32_t endLoop = startLoop + step; // End of loop body
        for (ip = startLoop; ip < endLoop; ip++) {
            executeInstruction(bytecode[ip]);
        }

        // Increment loop index by step
        i += step;
    }
}

void stackVM::whileLoop()
{
    // Get the loop condition from the stack
    int condition = pop();

    // Start of loop body (next instruction after the current one)
    uint32_t startLoop = ip + 1;

    // Execute loop body while the condition is true
    while (condition != 0) {
        // Loop body can contain any bytecode instructions inside the bytecode vector
        // Execute bytecode instructions from 'startLoop' index to 'endLoop' index
        for (ip = startLoop; ip < bytecode.size(); ip++) {
            executeInstruction(bytecode[ip]);
        }

        // Evaluate loop condition again after executing the loop body
        condition = pop();
    }
}

void stackVM::returnOpcode()
{
    // Retrieve the return value from the stack
    int returnValue = stack.back();
    stack.pop_back();

    // Pop the frame from the call stack
    callStack.pop_back();

    // Restore the program counter to the address of the calling instruction
    pc = callStack.back().returnAddress;

    // Push the return value onto the stack
    stack.push_back(returnValue);
}

// Variable operations
void stackVM::declareVariable()
{
    int value = pop();
    std::string variableName = popVariableName();
    variables[variableName] = value;
}

void stackVM::loadVariable()
{
    std::string variableName = popVariableName();
    int value = variables[variableName];
    push(value);
}

void stackVM::storeVariable()
{
    int value = pop();
    std::string variableName = popVariableName();
    variables[variableName] = value;
}

void stackVM::defineFunction()
{
    // Function name is assumed to be the next bytecode instruction
    // Additional metadata about the function (e.g., parameters) can be extracted from the bytecode
    Instruction functionInstruction = bytecode[ip + 1];
    std::string functionName = ""; // Extract function name from functionInstruction

    // Define a structure to hold function metadata
    FunctionMetadata functionMetadata;
    functionMetadata.name = functionName;

    // Find the end of the function's bytecode instructions
    uint32_t functionEnd = findFunctionEnd(
        ip + 2); // Start searching from the next instruction after the function instruction

    // Extract bytecode instructions for the function
    std::vector<Instruction> functionBytecode(bytecode.begin() + ip + 2,
                                              bytecode.begin() + functionEnd);

    // Store the function's bytecode instructions and metadata
    functionMetadata.bytecode = functionBytecode;
    functions[functionName] = functionMetadata;

    // Set the instruction pointer to the end of the function definition
    ip = functionEnd;
}

uint32_t stackVM::findFunctionEnd(uint32_t start)
{
    // Loop through bytecode instructions starting from 'start' index
    // and find the opcode that indicates the end of the function definition
    for (uint32_t i = start; i < bytecode.size(); i++) {
        if (bytecode[i].opcode == Opcode::RETURN) {
            return i; // Found the 'RETURN' opcode, indicating the end of the function definition
        }
    }
    // If the end of the function definition is not found, return the size of the bytecode vector
    return bytecode.size();
}

void stackVM::callFunction(int functionAddress)
{
    Frame frame;
    frame.returnAddress = pc;         // Store return address
    frame.basePointer = stack.size(); // Set base pointer for the stack

    callStack.push_back(frame); // Push frame onto the call stack
    pc = functionAddress;       // Set program counter to function address
}

void stackVM::returnValue()
{
    if (callStack.empty()) {
        std::cerr << "Error: Empty call stack. Cannot return from function." << std::endl;
        return;
    }

    Frame frame = callStack.back(); // Get top frame from call stack
    callStack.pop_back();           // Pop frame from call stack
    pc = frame.returnAddress;       // Set program counter to return address

    // Adjust stack to remove function's local variables and parameters
    stack.resize(frame.basePointer);
}

void stackVM::halt()
{
    // Implement halt operation
}

//Error handling
void stackVM::attemptOpcode()
{
    // Push the current instruction pointer (ip) onto the call stack
    callStack.push_back(Frame{static_cast<int>(ip), stack.size()});

    // Increment the IP to execute the next instruction
    ip++;
    // Execute the next instruction (which should be the beginning of the try block)
    //    executeInstruction(bytecode[ip]);
}

void stackVM::handleOpcode()
{
    // Check if the call stack is empty
    if (callStack.empty()) {
        std::cerr << "Error: Empty call stack. Cannot handle exception." << std::endl;
        return;
    }

    // Pop the previous frame (the beginning of the attempt block) from the call stack
    Frame attemptFrame = callStack.back();
    callStack.pop_back();

    // Get the line number of the handle block from the next instruction
    uint32_t handleBlockLineNumber = bytecode[ip + 1].lineNumber;

    // Set the instruction pointer (IP) to the handle block's line number
    ip = handleBlockLineNumber;

    // Execute the handle block's instruction
    executeInstruction(bytecode[ip]);
}

//
void stackVM::defineClass() {}

void stackVM::createObject() {}

void stackVM::methodCall() {}

// File I/O operations
void stackVM::openFile()
{
    // Pop the filename from the stack
    std::string filename = popVariableName();

    // Open the file in write mode
    fileStream.open(filename, std::ios::out);

    // Check if the file is opened successfully
    if (!fileStream.is_open()) {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
    }
}

void stackVM::writeFile()
{
    // Check if the file stream is open
    if (fileStream.is_open()) {
        // Pop the data to be written from the stack
        std::string data = popVariableName();

        // Write the data to the file
        fileStream << data << std::endl;
    } else {
        std::cerr << "Error: No open file to write" << std::endl;
    }
}

void stackVM::closeFile()
{
    // Check if the file stream is open
    if (fileStream.is_open()) {
        // Close the file
        fileStream.close();
    } else {
        std::cerr << "Error: No open file to close" << std::endl;
    }
}

//
void stackVM::parallel()
{
    // Create a vector to store threads
    std::vector<std::thread> threads;

    // Iterate through the bytecode instructions
    for (const Instruction &instruction : bytecode) {
        // Create a new thread for each instruction and execute it
        threads.emplace_back([this, instruction]() { executeInstruction(instruction); });
    }

    // Wait for all threads to complete
    for (std::thread &thread : threads) {
        thread.join();
    }
}

void stackVM::concurrent()
{
    // Create a vector to store threads
    std::vector<std::thread> threads;

    // Iterate through the bytecode instructions
    for (const Instruction &instruction : bytecode) {
        // Create a new thread for each instruction and execute it
        threads.emplace_back([this, instruction]() { executeInstruction(instruction); });
    }

    // Detach all threads to allow them to run independently
    for (std::thread &thread : threads) {
        thread.detach();
    }
}

void stackVM::async()
{
    // Start a new thread to execute bytecode instructions asynchronously
    std::thread([this]() {
        // Iterate through the bytecode instructions and execute each one
        for (const Instruction &instruction : bytecode) {
            executeInstruction(instruction);
        }
    }).detach();
}

//
void stackVM::genericFunction() {}

void stackVM::genericType() {}

void stackVM::patternMatch() {}
