
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/cst_printer.hh"
#include "common/backend.hh"
#include "backend/ast_printer.hh"
#include "backend/bytecode_printer.hh"
#include "backend/vm/vm.hh"
#include "lir/generator.hh"
#include "backend/jit/jit.hh"
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
    std::cout << "  " << programName << " -cst <source_file> - Print the CST for a source file" << std::endl;
    std::cout << "  " << programName << " -tokens <source_file> - Print the tokens for a source file" << std::endl;
    std::cout << "  " << programName << " -bytecode <source_file> - Print the bytecode for a source file" << std::endl;
    std::cout << "  " << programName << " -jit <source_file>    - JIT compile a source file" << std::endl;
    std::cout << "  " << programName << " -jit-debug <source_file> - JIT compile and run directly (debug mode)" << std::endl;
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

int executeFile(const std::string& filename, bool printAst = false, bool printCst = false, bool printTokens = false, bool printBytecode = false, bool useJit = false, bool jitDebug = false, bool enableDebug = false) {
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
        bool useCSTMode = printCst; // Use CST mode if CST printing is requested
        Parser parser(scanner, useCSTMode);
        std::shared_ptr<AST::Program> ast = parser.parse();
        
        // Print CST if requested
        if (printCst) {
            std::cout << "=== CST ===\n";
            const CST::Node* cstRoot = parser.getCST();
            if (cstRoot) {
                std::cout << CST::Printer::printCST(cstRoot) << std::endl;
            } else {
                std::cout << "No CST available (parser not in CST mode)" << std::endl;
            }
        }
        
        // Print AST if requested
        if (printAst) {
            std::cout << "=== AST ===\n";
            ASTPrinter printer;
            printer.process(ast);
            std::cout << std::endl;
        }

        if (useJit) {
            try {
                // Generate LIR from AST
                LIR::Generator lir_generator;
                auto lir_function = lir_generator.generate_program(*ast);
                
                if (!lir_function) {
                    std::cerr << "Failed to generate LIR function\n";
                    return 1;
                }
                
                if (lir_generator.has_errors()) {
                    std::cerr << "LIR generation errors:\n";
                    for (const auto& error : lir_generator.get_errors()) {
                        std::cerr << "  " << error << std::endl;
                    }
                    return 1;
                }
                
                std::cout << "Generated LIR function with " << lir_function->instructions.size() << " instructions\n";
                
                // Initialize JIT backend
                JIT::JITBackend jit;
                
                // Process the LIR function with JIT
                jit.process_function(*lir_function);
                
                if (jitDebug) {
                    std::cout << "=== JIT Debug Mode - Running Directly ===\n";
                    auto result = jit.compile(JIT::CompileMode::ToMemory);
                    if (result.success) {
                        std::cout << "JIT compilation successful, executing...\n";
                        int exit_code = jit.execute_compiled_function();
                        std::cout << "JIT execution completed with exit code: " << exit_code << std::endl;
                        return exit_code;
                    } else {
                        std::cerr << "JIT compilation failed: " << result.error_message << std::endl;
                        return 1;
                    }
                } else {
                    std::string output_filename = filename;
                    size_t dot_pos = output_filename.rfind(".lm");
                    if (dot_pos != std::string::npos) {
                        output_filename.erase(dot_pos);
                    }
                    // Add platform-specific executable extension
                    #ifdef _WIN32
                        output_filename += ".exe";
                    #endif
                    
                    std::cout << "Compiling to executable: " << output_filename << "\n";
                    auto result = jit.compile(JIT::CompileMode::ToExecutable, output_filename);
                    if (result.success) {
                        std::cout << "Compiled to " << result.output_file << ". Run ./" << result.output_file << " to see the result.\n";
                    } else {
                        std::cerr << "JIT compilation failed: " << result.error_message << std::endl;
                        return 1;
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "JIT Error: " << e.what() << std::endl;
                return 1;
            } catch (...) {
                std::cerr << "Unknown JIT error occurred" << std::endl;
                return 1;
            }
        } else {

            // Backend: Generate bytecode
            VM vm;
            
            // Enable debug mode if requested
            if (enableDebug) {
                vm.setDebug(true);
            }
            
            BytecodeGenerator generator;
            generator.setSourceContext(source, filename);
            generator.process(ast);

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
                return 1;
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
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
        return 0;
    } else if (arg == "-ast" && argc >= 3) {
        return executeFile(argv[2], true, false, false, false);
    } else if (arg == "-cst" && argc >= 3) {
        return executeFile(argv[2], false, true, false, false);
    } else if (arg == "-tokens" && argc >= 3) {
        return executeFile(argv[2], false, false, true, false);
    } else if (arg == "-bytecode" && argc >= 3) {
        return executeFile(argv[2], false, false, false, true);
    } else if (arg == "-jit" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, true, false);
    } else if (arg == "-jit-debug" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, true, true);
    } else if (arg == "-debug" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, false, true);
    } else if (arg[0] == '-') {
        std::cerr << "Unknown option: " << arg << std::endl;
        printUsage(argv[0]);
        return 1;
    } else {
        return executeFile(arg);
    }
}