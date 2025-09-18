#ifndef BYTECODE_PRINTER_H
#define BYTECODE_PRINTER_H

#include "../opcodes.hh"
#include <vector>
#include <iostream>
#include <string>

class BytecodePrinter {
public:
    // Print bytecode instructions to stdout
    static void print(const std::vector<Instruction>& bytecode);
    
    // Print bytecode instructions to a stream
    static void print(const std::vector<Instruction>& bytecode, std::ostream& out);
    
private:
    // Convert opcode to string representation
    static std::string opcodeToString(Opcode opcode);
    
    // Format instruction for display
    static std::string formatInstruction(const Instruction& instruction, size_t index);
};

#endif // BYTECODE_PRINTER_H