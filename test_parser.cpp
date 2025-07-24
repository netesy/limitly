#include "backend/ast_printer.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "backend.hh"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <source_file>" << std::endl;
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
        
        // Print tokens (optional)
        // std::cout << "Tokens:\n";
        // for (const auto& token : scanner.tokens) {
        //     std::cout << "  " << scanner.tokenTypeToString(token.type) 
        //               << ": '" << token.lexeme << "' (line " << token.line << ")\n";
        // }
        // std::cout << std::endl;
        
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
        
        // Print bytecode (simplified)
        std::cout << "Bytecode generated: " << generator.getBytecode().size() << " instructions\n";
        std::cout << "First 10 instructions:\n";
        int count = 0;
        for (const auto& instruction : generator.getBytecode()) {
            if (count++ >= 10) break;
            std::cout << "  " << static_cast<int>(instruction.opcode) 
                      << " (line " << instruction.line << ")\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}