#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "common/backend.hh"
#include "backend/ast_printer.hh"
#include "backend/bytecode_printer.hh"
#include "backend/vm.hh"
// #include "backend/jit_backend.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include "lembed.hh"

void printUsage(const char* programName) {
    std::cout << "Limit Programming Language" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << programName << " <source_file>    - Execute a source file" << std::endl;
    std::cout << "  " << programName << " -ast <source_file> - Print the AST for a source file" << std::endl;
    std::cout << "  " << programName << " -tokens <source_file> - Print the tokens for a source file" << std::endl;
    std::cout << "  " << programName << " -bytecode <source_file> - Print the bytecode for a source file" << std::endl;
    std::cout << "  " << programName << " -debug <source_file> - Execute with debug output enabled" << std::endl;
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

void executeFile(const std::string& filename, bool printAst = false, bool printTokens = false, bool printBytecode = false, bool useJit = false, bool enableDebug = false) {
    try {
        // Read source file
        std::string source = readFile(filename);
        
        // Frontend: Lexical analysis (scanning)
        Scanner scanner(source, filename);
        scanner.scanTokens();
        
        // Print tokens if requested
        if (printTokens) {
            std::cout << "=== Tokens ===\n";
            for (const auto& token : scanner.getTokens()) {
                std::cout << scanner.tokenTypeToString(token.type) 
                          << ": '" << token.lexeme << "' (line " << token.line << ")\n";
            }
            std::cout << std::endl;
        }
        
        // Frontend: Syntax analysis (parsing)
        Parser parser(scanner, false); // Use legacy mode for optimal execution performance
        std::shared_ptr<AST::Program> ast = parser.parse();
        
        // Print AST if requested
        if (printAst) {
            std::cout << "=== AST ===\n";
            ASTPrinter printer;
            printer.process(ast);
            std::cout << std::endl;
        }

        // if (useJit) {
        //     std::cout << "=== JIT Backend ===\n";
        //     JitBackend jit;
        //     jit.process(ast);
        //     const char* output_filename = "jit_output";
        //     jit.compile(output_filename);
        //     std::cout << "Compiled to " << output_filename << ". Run ./" << output_filename << " to see the result.\n";
        // } else {

            // Backend: Generate bytecode
            VM vm;
            
            // Enable debug mode if requested
            if (enableDebug) {
                vm.setDebug(true);
            }
            
            BytecodeGenerator generator;
            generator.process(ast);
            generator.setSourceContext(source, filename);

            // Print bytecode if requested
            if (printBytecode) {
                BytecodePrinter::print(generator.getBytecode());
            }

            // Execute bytecode using the virtual machine
            try {
                // Set source information for enhanced error reporting
                vm.setSourceInfo(source, filename);
                ValuePtr result = vm.execute(generator.getBytecode());
                // Only print non-nil results
                if (result && (!result->type || result->type->tag != TypeTag::Nil)) {
                    std::cout << result->toString() << std::endl;
                }
                if (vm.getThreadPool()) {
                    vm.getThreadPool()->stop();
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        // }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void startRepl() {
    std::cout << "Limit Programming Language REPL (Interactive Mode)" << std::endl;
    std::cout << "Type 'exit' to quit, '.stack' to show stack, '.debug' to toggle debug mode" << std::endl;
    
    VM vm;
    bool debugMode = false;
    std::string line;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        
        // Handle special commands
        if (line == "exit") {
            break;
        } else if (line == ".stack") {
            vm.printStack();
            continue;
        } else if (line == ".debug") {
            debugMode = !debugMode;
            std::cout << "Debug mode " << (debugMode ? "enabled" : "disabled") << std::endl;
            continue;
        } else if (line.empty()) {
            continue;
        }
        
        try {
            // Frontend: Lexical analysis (scanning)
            Scanner scanner(line);
            scanner.scanTokens();
            
            // Frontend: Syntax analysis (parsing)
            Parser parser(scanner, false); // Use legacy mode for optimal REPL performance
            std::shared_ptr<AST::Program> ast = parser.parse();
            
            // Backend: Generate bytecode
            BytecodeGenerator generator;
            generator.process(ast);
            
            // Execute bytecode using the virtual machine
            try {
                // Set debug state based on debug mode
                #ifdef DEBUG
                bool oldDebug = Debugger::getInstance().isEnabled();
                Debugger::getInstance().setEnabled(debugMode);
                #endif
                
                // Set source information for enhanced error reporting
                vm.setSourceInfo(line, "<repl>");
                
                // Execute the bytecode
                ValuePtr result = vm.execute(generator.getBytecode());
                
                // Show stack after execution in debug mode
                if (debugMode) {
                    vm.printStack();
                }
                
                // Only print non-nil results
                if (result && (!result->type || result->type->tag != TypeTag::Nil)) {
                    std::cout << "=> " << result->toString() << std::endl;
                }
                
                #ifdef DEBUG
                // Restore debug state
                Debugger::getInstance().setEnabled(oldDebug);
                #endif
                
            } catch (const std::exception& e) {
                std::cerr << "Runtime error: " << e.what() << std::endl;
                if (debugMode) {
                    vm.printStack();
                }
            }
            
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
    } else if (arg == "-debug" && argc >= 3) {
        executeFile(argv[2], false, false, false, false, true);
    // } else if (arg == "-jit" && argc >= 3) {
    //     executeFile(argv[2], false, false, false, true);
    } else if (arg[0] == '-') {
        std::cerr << "Unknown option: " << arg << std::endl;
        printUsage(argv[0]);
        return 1;
    } else {
        executeFile(arg);
    }
    
    return 0;
}