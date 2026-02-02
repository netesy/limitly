// test_parser.cpp - Parser testing utility
// Tests the scanner and parser on a given source file

#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/ast/printer.hh"
#include "frontend/cst/printer.hh"
#include "frontend/type_checker.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

using namespace LM;
using namespace LM::Frontend;

void printUsage(const char* programName) {
    std::cout << "Parser Testing Utility\n";
    std::cout << "Usage: " << programName << " <source_file> [options]\n";
    std::cout << "\nOptions:\n";
    std::cout << "  --tokens    Print tokens only\n";
    std::cout << "  --ast       Print AST (default)\n";
    std::cout << "  --cst       Print CST structure\n";
    std::cout << "  --types     Perform type checking\n";
    std::cout << "  --all       Print all outputs\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    bool printTokens = false;
    bool printAST = true;
    bool printCST = false;
    bool printTypes = false;

    // Parse options
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--tokens") {
            printTokens = true;
            printAST = false;
        } else if (arg == "--ast") {
            printAST = true;
        } else if (arg == "--cst") {
            printCST = true;
        } else if (arg == "--types") {
            printTypes = true;
        } else if (arg == "--all") {
            printTokens = true;
            printAST = true;
            printCST = true;
            printTypes = true;
        }
    }

    // Read source file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    file.close();

    try {
        // Scanning phase
        std::cout << "=== Scanning ===\n";
        Scanner scanner(source, filename);
        auto tokens = scanner.scanTokens();
        std::cout << "✓ Scanned " << tokens.size() << " tokens\n\n";

        // Print tokens if requested
        if (printTokens) {
            std::cout << "=== Tokens ===\n";
            for (size_t i = 0; i < tokens.size(); i++) {
                const auto& token = tokens[i];
                std::cout << "[" << i << "] Line " << token.line << ", Col " << token.column 
                         << ": " << scanner.tokenTypeToString(token.type) 
                         << " = '" << token.lexeme << "'\n";
            }
            std::cout << "\n";
        }

        // Parsing phase
        std::cout << "=== Parsing ===\n";
        Parser parser(scanner);
        auto program = parser.parse();
        
        if (Error::Debugger::hasError()) {
            std::cerr << "✗ Parse errors occurred\n";
            return 1;
        }
        
        std::cout << "✓ Parsing completed successfully\n";
        if (program) {
            std::cout << "✓ Program has " << program->statements.size() << " statements\n";
        }
        std::cout << "\n";

        // Print AST if requested
        if (printAST && program) {
            std::cout << "=== Abstract Syntax Tree ===\n";
            AST::Printer astPrinter;
            astPrinter.print(program);
            std::cout << "\n";
        }

        // Print CST if requested
        if (printCST) {
            std::cout << "=== Concrete Syntax Tree ===\n";
            std::cout << "CST mode: " << (parser.isCSTMode() ? "enabled" : "disabled") << "\n";
            std::cout << "CST nodes created: " << parser.getCSTNodeCount() << "\n";
            std::cout << "Trivia attachments: " << parser.getTriviaAttachmentCount() << "\n";
            std::cout << "\n";
        }

        // Type checking if requested
        if (printTypes && program) {
            std::cout << "=== Type Checking ===\n";
            TypeChecker typeChecker;
            bool typeCheckPassed = typeChecker.check(program, source, filename);
            
            if (typeCheckPassed) {
                std::cout << "✓ Type checking passed\n";
            } else {
                std::cout << "✗ Type checking failed\n";
            }
            std::cout << "\n";
        }

        // Save outputs to files
        std::string baseName = filename;
        size_t lastDot = baseName.find_last_of('.');
        if (lastDot != std::string::npos) {
            baseName = baseName.substr(0, lastDot);
        }

        // Save AST to file
        if (program) {
            std::string astFile = baseName + ".ast.txt";
            std::ofstream out(astFile);
            if (out.is_open()) {
                out << "AST for " << filename << "\n";
                out << "========================================\n\n";
                
                // Redirect cout to file temporarily
                std::streambuf* coutbuf = std::cout.rdbuf();
                std::cout.rdbuf(out.rdbuf());
                
                AST::Printer astPrinter;
                astPrinter.print(program);
                
                std::cout.rdbuf(coutbuf);
                out.close();
                std::cout << "AST saved to " << astFile << "\n";
            }
        }

        // Save tokens to file
        if (printTokens) {
            std::string tokensFile = baseName + ".tokens.txt";
            std::ofstream out(tokensFile);
            if (out.is_open()) {
                out << "Tokens for " << filename << "\n";
                out << "========================================\n\n";
                
                for (size_t i = 0; i < tokens.size(); i++) {
                    const auto& token = tokens[i];
                    out << "[" << i << "] Line " << token.line << ", Col " << token.column 
                       << ": " << scanner.tokenTypeToString(token.type) 
                       << " = '" << token.lexeme << "'\n";
                }
                out.close();
                std::cout << "Tokens saved to " << tokensFile << "\n";
            }
        }

        std::cout << "\n✓ Test completed successfully\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
