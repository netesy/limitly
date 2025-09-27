#include "backend/ast_printer.hh"
#include "backend/bytecode_printer.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "common/backend.hh"
#include "backend/vm.hh"
#include "common/opcodes.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <algorithm>

// Function to print all opcode values and names (for debugging)
void printOpcodeValues() {
    std::cout << "Opcode values and names:" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Use BytecodePrinter for detailed bytecode output" << std::endl;
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
        
        // Print tokens to stdout
        std::cout << "=== Tokens ===\n";
        for (const auto& token : scanner.getTokens()) {
            std::cout << "Line " << token.line << ": "
                      << scanner.tokenTypeToString(token.type)
                      << " = '" << token.lexeme << "'\n";
        }
        std::cout << std::endl;
        
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
        
        // Print bytecode to console
        BytecodePrinter::print(generator.getBytecode());
        
        // Output bytecode to file
        std::string bytecodeFilename = std::string(argv[1]) + ".bytecode.txt";
        std::ofstream bytecodeFile(bytecodeFilename);
        if (bytecodeFile.is_open()) {
            bytecodeFile << "Bytecode for " << argv[1] << "\n";
            bytecodeFile << "========================================\n\n";
            
            // Use BytecodePrinter for file output too
            BytecodePrinter::print(generator.getBytecode(), bytecodeFile);
            
            std::cout << "Bytecode output saved to " << bytecodeFilename << std::endl;
        } else {
            std::cerr << "Warning: Could not open " << bytecodeFilename << " for writing" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}