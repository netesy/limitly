#include "backend/ast_printer.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "backend.hh"
#include "opcodes.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <algorithm>

// Map opcode enum values to their string representations
const std::unordered_map<Opcode, std::string> OPCODE_NAMES = {
    // Stack operations
    {Opcode::PUSH_INT, "PUSH_INT"},
    {Opcode::PUSH_FLOAT, "PUSH_FLOAT"},
    {Opcode::PUSH_STRING, "PUSH_STRING"},
    {Opcode::PUSH_BOOL, "PUSH_BOOL"},
    {Opcode::PUSH_NULL, "PUSH_NULL"},
    {Opcode::POP, "POP"},
    {Opcode::DUP, "DUP"},
    {Opcode::SWAP, "SWAP"},
    
    // Variable operations
    {Opcode::STORE_VAR, "STORE_VAR"},
    {Opcode::LOAD_VAR, "LOAD_VAR"},
    {Opcode::STORE_TEMP, "STORE_TEMP"},
    {Opcode::LOAD_TEMP, "LOAD_TEMP"},
    {Opcode::CLEAR_TEMP, "CLEAR_TEMP"},
    {Opcode::LOAD_THIS, "LOAD_THIS"},
    
    // Arithmetic operations
    {Opcode::ADD, "ADD"},
    {Opcode::SUBTRACT, "SUBTRACT"},
    {Opcode::MULTIPLY, "MULTIPLY"},
    {Opcode::DIVIDE, "DIVIDE"},
    {Opcode::POWER, "POWER"},
    {Opcode::MODULO, "MODULO"},
    {Opcode::NEGATE, "NEGATE"},
    
    // Comparison operations
    {Opcode::EQUAL, "EQUAL"},
    {Opcode::NOT_EQUAL, "NOT_EQUAL"},
    {Opcode::LESS, "LESS"},
    {Opcode::LESS_EQUAL, "LESS_EQUAL"},
    {Opcode::GREATER, "GREATER"},
    {Opcode::GREATER_EQUAL, "GREATER_EQUAL"},
    
    // String operations
    {Opcode::INTERPOLATE_STRING, "INTERPOLATE_STRING"},
    {Opcode::CONCAT, "CONCAT"},
    
    // Logical operations
    {Opcode::AND, "AND"},
    {Opcode::OR, "OR"},
    {Opcode::NOT, "NOT"},
    
    // Control flow operations
    {Opcode::JUMP, "JUMP"},
    {Opcode::JUMP_IF_TRUE, "JUMP_IF_TRUE"},
    {Opcode::JUMP_IF_FALSE, "JUMP_IF_FALSE"},
    {Opcode::CALL, "CALL"},
    {Opcode::RETURN, "RETURN"},
    
    // Function operations
    {Opcode::BEGIN_FUNCTION, "BEGIN_FUNCTION"},
    {Opcode::END_FUNCTION, "END_FUNCTION"},
    {Opcode::DEFINE_PARAM, "DEFINE_PARAM"},
    {Opcode::DEFINE_OPTIONAL_PARAM, "DEFINE_OPTIONAL_PARAM"},
    {Opcode::SET_DEFAULT_VALUE, "SET_DEFAULT_VALUE"},
    
    // Class operations
    {Opcode::BEGIN_CLASS, "BEGIN_CLASS"},
    {Opcode::END_CLASS, "END_CLASS"},
    {Opcode::GET_PROPERTY, "GET_PROPERTY"},
    {Opcode::SET_PROPERTY, "SET_PROPERTY"},
    
    // Collection operations
    {Opcode::CREATE_LIST, "CREATE_LIST"},
    {Opcode::LIST_APPEND, "LIST_APPEND"},
    {Opcode::CREATE_DICT, "CREATE_DICT"},
    {Opcode::CREATE_RANGE, "CREATE_RANGE"},
    {Opcode::SET_RANGE_STEP, "SET_RANGE_STEP"},
    {Opcode::DICT_SET, "DICT_SET"},
    {Opcode::GET_INDEX, "GET_INDEX"},
    {Opcode::SET_INDEX, "SET_INDEX"},
    
    // Iterator operations
    {Opcode::GET_ITERATOR, "GET_ITERATOR"},
    {Opcode::ITERATOR_HAS_NEXT, "ITERATOR_HAS_NEXT"},
    {Opcode::ITERATOR_NEXT, "ITERATOR_NEXT"},
    {Opcode::ITERATOR_NEXT_KEY_VALUE, "ITERATOR_NEXT_KEY_VALUE"},
    
    // Scope operations
    {Opcode::BEGIN_SCOPE, "BEGIN_SCOPE"},
    {Opcode::END_SCOPE, "END_SCOPE"},
    
    // Exception handling operations
    {Opcode::BEGIN_TRY, "BEGIN_TRY"},
    {Opcode::END_TRY, "END_TRY"},
    {Opcode::BEGIN_HANDLER, "BEGIN_HANDLER"},
    {Opcode::END_HANDLER, "END_HANDLER"},
    {Opcode::THROW, "THROW"},
    {Opcode::STORE_EXCEPTION, "STORE_EXCEPTION"},
    
    // Concurrency operations
    {Opcode::BEGIN_PARALLEL, "BEGIN_PARALLEL"},
    {Opcode::END_PARALLEL, "END_PARALLEL"},
    {Opcode::BEGIN_CONCURRENT, "BEGIN_CONCURRENT"},
    {Opcode::END_CONCURRENT, "END_CONCURRENT"},
    {Opcode::AWAIT, "AWAIT"},
    
    // Pattern matching operations
    {Opcode::MATCH_PATTERN, "MATCH_PATTERN"},
    
    // Module operations
    {Opcode::IMPORT, "IMPORT"},
    
    // Enum operations
    {Opcode::BEGIN_ENUM, "BEGIN_ENUM"},
    {Opcode::END_ENUM, "END_ENUM"},
    {Opcode::DEFINE_ENUM_VARIANT, "DEFINE_ENUM_VARIANT"},
    {Opcode::DEFINE_ENUM_VARIANT_WITH_TYPE, "DEFINE_ENUM_VARIANT_WITH_TYPE"},
    
    // I/O operations
    {Opcode::PRINT, "PRINT"},
    
    // Debug operations
    {Opcode::DEBUG_PRINT, "DEBUG_PRINT"},

    // Memory operations
    {Opcode::LOAD_CONST, "LOAD_CONST"},
    {Opcode::STORE_CONST, "STORE_CONST"},
    {Opcode::LOAD_MEMBER, "LOAD_MEMBER"},
    {Opcode::STORE_MEMBER, "STORE_MEMBER"}
};

// Helper function to get opcode name
std::string getOpcodeName(Opcode opcode) {
    auto it = OPCODE_NAMES.find(opcode);
    if (it != OPCODE_NAMES.end()) {
        return it->second;
    }
    return "OP_" + std::to_string(static_cast<int>(opcode));
}

// Function to print all opcode values and names
void printOpcodeValues() {
    std::cout << "Opcode values and names:" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    // Create a vector of pairs to sort the opcodes by their numeric values
    std::vector<std::pair<int, std::string>> opcodeList;
    for (const auto& pair : OPCODE_NAMES) {
        opcodeList.push_back({static_cast<int>(pair.first), pair.second});
    }
    
    // Sort by opcode value
    std::sort(opcodeList.begin(), opcodeList.end(), 
        [](const auto& a, const auto& b) { return a.first < b.first; });
    
    // Print sorted opcodes
    for (const auto& [value, name] : opcodeList) {
        std::cout << std::setw(3) << value << ": " << name << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

int main(int argc, char* argv[]) {
    // Check for --list-opcodes flag
    if (argc > 1 && std::string(argv[1]) == "--list-opcodes") {
        printOpcodeValues();
        return 0;
    }
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <source_file>" << std::endl;
        std::cout << "       " << argv[0] << " --list-opcodes" << std::endl;
        return 1;
    }
    
    // Read source file
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    try {
        // Frontend: Lexical analysis (scanning)
        //std::cout << "=== Scanning ===\n";
        Scanner scanner(source);
        scanner.scanTokens();
        
        // Output tokens to file
        std::string tokensFilename = std::string(argv[1]) + ".tokens.txt";
        std::ofstream tokensFile(tokensFilename);
        if (tokensFile.is_open()) {
            tokensFile << "Tokens for " << argv[1] << "\n";
            tokensFile << "========================================\n\n";
            for (const auto& token : scanner.getTokens()) {
                tokensFile << "Line " << token.line << ": " 
                          << scanner.tokenTypeToString(token.type) 
                          << " = '" << token.lexeme << "'\n";
            }
            std::cout << "Tokens output saved to " << tokensFilename << std::endl;
        } else {
            std::cerr << "Warning: Could not open " << tokensFilename << " for writing" << std::endl;
        }
        
        // Frontend: Syntax analysis (parsing)
        std::cout << "=== Parsing ===\n";
        Parser parser(scanner);
        std::shared_ptr<AST::Program> ast = parser.parse();
        std::cout << "Parsing completed successfully!\n\n";
        
        // Backend: Print AST to console and file
        std::cout << "=== AST Structure ===\n";
        ASTPrinter printer;
        
        // Print to console
        printer.process(ast);
        std::cout << std::endl;
        
        // Save to file
        std::string outputFilename = std::string(argv[1]) + ".ast.txt";
        std::ofstream outFile(outputFilename);
        if (outFile.is_open()) {
            // Redirect cout to file
            std::streambuf *coutbuf = std::cout.rdbuf();
            std::cout.rdbuf(outFile.rdbuf());
            
            // Print AST to file
            std::cout << "AST for " << argv[1] << "\n";
            std::cout << "========================================\n\n";
            printer.process(ast);
            
            // Restore cout
            std::cout.rdbuf(coutbuf);
            
            std::cout << "AST output saved to " << outputFilename << std::endl;
        } else {
            std::cerr << "Warning: Could not open " << outputFilename << " for writing" << std::endl;
        }
        
        // Backend: Generate bytecode
        std::cout << "=== Bytecode Generation ===\n";
        BytecodeGenerator generator;
        generator.process(ast);
        
        // Output bytecode to file
        std::string bytecodeFilename = std::string(argv[1]) + ".bytecode.txt";
        std::ofstream bytecodeFile(bytecodeFilename);
        if (bytecodeFile.is_open()) {
            bytecodeFile << "Bytecode for " << argv[1] << "\n";
            bytecodeFile << "========================================\n\n";
            bytecodeFile << "Total instructions: " << generator.getBytecode().size() << "\n\n";
            
            int count = 1;
            for (const auto& instruction : generator.getBytecode()) {
                bytecodeFile << std::setw(4) << count++ << ": "
                           << std::setw(20) << std::left << getOpcodeName(instruction.opcode)
                           << " (line " << instruction.line << ")";
                
                // Add any additional instruction details here if available
                // Note: Instruction operand access removed as it's not part of the Instruction struct
                
                bytecodeFile << "\n";
            }
            
            std::cout << "Bytecode output saved to " << bytecodeFilename << std::endl;
            
            // Also print first 10 instructions to console
            std::cout << "\nFirst 10 instructions:\n";
            count = 0;
            for (const auto& instruction : generator.getBytecode()) {
                if (count++ >= 10) break;
                std::cout << "  " << std::setw(20) << std::left << getOpcodeName(instruction.opcode)
                      << " (line " << instruction.line << ")\n";
            }
        } else {
            std::cerr << "Warning: Could not open " << bytecodeFilename << " for writing" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}