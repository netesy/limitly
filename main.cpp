#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "backend.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void printUsage(const char* programName) {
    std::cout << "Limit Programming Language" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << programName << " <source_file>    - Execute a source file" << std::endl;
    std::cout << "  " << programName << " -ast <source_file> - Print the AST for a source file" << std::endl;
    std::cout << "  " << programName << " -tokens <source_file> - Print the tokens for a source file" << std::endl;
    std::cout << "  " << programName << " -bytecode <source_file> - Print the bytecode for a source file" << std::endl;
    std::cout << "  " << programName << " -repl           - Start the REPL (interactive mode)" << std::endl;
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void executeFile(const std::string& filename, bool printAst = false, bool printTokens = false, bool printBytecode = false) {
    try {
        // Read source file
        std::string source = readFile(filename);
        
        // Frontend: Lexical analysis (scanning)
        Scanner scanner(source);
        scanner.scanTokens();
        
        // Print tokens if requested
        if (printTokens) {
            std::cout << "=== Tokens ===\n";
            for (const auto& token : scanner.tokens) {
                std::cout << scanner.tokenTypeToString(token.type) 
                          << ": '" << token.lexeme << "' (line " << token.line << ")\n";
            }
            std::cout << std::endl;
        }
        
        // Frontend: Syntax analysis (parsing)
        Parser parser(scanner);
        std::shared_ptr<AST::Program> ast = parser.parse();
        
        // Print AST if requested
        if (printAst) {
            std::cout << "=== AST ===\n";
            ASTPrinter printer;
            printer.process(ast);
            std::cout << std::endl;
        }
        
        // Backend: Generate bytecode
        BytecodeGenerator generator;
        generator.process(ast);
        
        // Print bytecode if requested
        if (printBytecode) {
            std::cout << "=== Bytecode ===\n";
            std::cout << "Generated " << generator.getBytecode().size() << " instructions\n";
            // TODO: Implement bytecode disassembler and print instructions
            std::cout << std::endl;
        }
        
        // TODO: Execute bytecode using a virtual machine
        std::cout << "Execution not yet implemented." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void startRepl() {
    std::cout << "Limit Programming Language REPL (Interactive Mode)" << std::endl;
    std::cout << "Type 'exit' to quit" << std::endl;
    
    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        
        if (line == "exit") {
            break;
        }
        
        try {
            // Frontend: Lexical analysis (scanning)
            Scanner scanner(line);
            scanner.scanTokens();
            
            // Frontend: Syntax analysis (parsing)
            Parser parser(scanner);
            std::shared_ptr<AST::Program> ast = parser.parse();
            
            // Backend: Generate bytecode
            BytecodeGenerator generator;
            generator.process(ast);
            
            // TODO: Execute bytecode using a virtual machine
            std::cout << "Execution not yet implemented." << std::endl;
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string arg = argv[1];
    
    if (arg == "-repl") {
        startRepl();
    } else if (arg == "-ast" && argc >= 3) {
        executeFile(argv[2], true, false, false);
    } else if (arg == "-tokens" && argc >= 3) {
        executeFile(argv[2], false, true, false);
    } else if (arg == "-bytecode" && argc >= 3) {
        executeFile(argv[2], false, false, true);
    } else if (arg[0] == '-') {
        std::cerr << "Unknown option: " << arg << std::endl;
        printUsage(argv[0]);
        return 1;
    } else {
        executeFile(arg);
    }
    
    return 0;
}