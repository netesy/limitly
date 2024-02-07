#pragma once

#include "opcodes.hh"
#include <cstdint>
#include <fstream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

struct Frame
{
    int returnAddress;
    size_t basePointer; // Base pointer for the stack
};

// Define a structure to hold metadata about a function
struct FunctionMetadata
{
    std::string name;                  // Name of the function
    std::vector<Instruction> bytecode; // Bytecode instructions for the function
    // Add any additional metadata about the function as needed
};

class stackVM
{
public:
    stackVM();
    void loadBytecode(const std::vector<Instruction> &bytecode);
    void execute();

private:
    std::vector<Instruction> bytecode;
    std::vector<int> stack;
    std::map<std::string, int> variables;
    std::map<std::string, FunctionMetadata> functions;
    std::ofstream fileStream; // Declare file stream as a member variable
    uint32_t ip; // Instruction pointer
    std::vector<Frame> callStack; // Call stack for function calls
    size_t pc;                    // Program counter

    void executeInstruction(const Instruction &instruction);
    int pop();
    void push(int value);
    std::string popVariableName();

    //helper functions
    void add();
    void subtract();
    void multiply();
    void divide();
    void modulus();

    void equal();
    void notEqual();
    void lessThan();
    void lessThanOrEqual();
    void greaterThan();
    void greaterThanOrEqual();

    void logicalAnd();
    void logicalOr();
    void logicalNot();

    void jump(uint32_t lineNumber);
    void jumpIfTrue(uint32_t lineNumber);
    void jumpIfFalse(uint32_t lineNumber);
    void forLoop();
    void whileLoop();
    void returnOpcode();

    void declareVariable();
    void loadVariable();
    void storeVariable();

    void defineFunction();
    uint32_t findFunctionEnd(uint32_t start);
    //    void invokeFunction(uint32_t);
    void callFunction(int functionAddress);
    void returnValue();

    void halt();

    void attemptOpcode();
    void handleOpcode();

    void defineClass();
    void createObject();
    void methodCall();

    void openFile();
    void writeFile();
    void closeFile();

    void parallel();
    void concurrent();
    void async();

    void genericFunction();
    void genericType();
    void patternMatch();
};
