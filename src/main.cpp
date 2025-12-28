
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/cst_printer.hh"
#include "frontend/type_checker.hh"
#include "frontend/ast.hh"
#include "common/backend.hh"
#include "backend/ast_printer.hh"
#include "backend/bytecode_printer.hh"
#include "backend/vm/vm.hh"
#include "backend/register/register.hh"
#include "lir/generator.hh"
#include "lir/functions.hh"
#include "backend/jit/jit.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

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
        
        // AST Optimization (before type checking)
        AST::ASTOptimizer optimizer;
        ast = optimizer.optimize(ast);
        
        // Print optimization statistics
        const auto& stats = optimizer.getStats();
        std::cout << "=== AST Optimization Statistics ===\n";
        std::cout << "Constant folds: " << stats.constant_folds << "\n";
        std::cout << "Constant propagations: " << stats.constant_propagations << "\n";
        std::cout << "Dead code eliminated: " << stats.dead_code_eliminated << "\n";
        std::cout << "Branches simplified: " << stats.branches_simplified << "\n";
        std::cout << "Interpolations lowered: " << stats.interpolations_lowered << "\n";
        std::cout << "Algebraic simplifications: " << stats.algebraic_simplifications << "\n";
        std::cout << "Strings canonicalized: " << stats.strings_canonicalized << "\n";
        std::cout << std::endl;
        
        // Print AST after optimization if debug mode is enabled
        if (enableDebug || jitDebug) {
            std::cout << "=== AST After Optimization ===\n";
            ASTPrinter printer_after;
            printer_after.process(ast);
            std::cout << std::endl;
        }
        
        // Print optimization statistics if debug mode is enabled
        if (enableDebug || jitDebug) {
            const auto& stats = optimizer.getStats();
            std::cout << "=== AST Optimization Statistics ===\n";
            std::cout << "Constant folds: " << stats.constant_folds << "\n";
            std::cout << "Constant propagations: " << stats.constant_propagations << "\n";
            std::cout << "Dead code eliminated: " << stats.dead_code_eliminated << "\n";
            std::cout << "Branches simplified: " << stats.branches_simplified << "\n";
            std::cout << "Interpolations lowered: " << stats.interpolations_lowered << "\n";
            std::cout << "Algebraic simplifications: " << stats.algebraic_simplifications << "\n";
            std::cout << "Strings canonicalized: " << stats.strings_canonicalized << "\n";
        }
        
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
        
        // Type checking
        auto type_check_result = TypeCheckerFactory::check_program(ast, source, filename);
        if (!type_check_result.success) {
            return 1;
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
                // Generate LIR from optimized AST
                LIR::Generator lir_generator;
                auto lir_function = lir_generator.generate_program(type_check_result);
                
                // Initialize and run LIR disassembler
                LIR::Disassembler disassemble(*lir_function, true);
                std::cout << "\n=== LIR Disassembly ===\n";
                std::cout << disassemble.disassemble() << std::endl;
                
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
                std::cout << "CFG generation completed with " << lir_function->cfg->blocks.size() << " blocks\n";
                
                if (jitDebug || enableDebug) {
                    std::cout << "\n=== LIR Instructions ===\n";
                    for (size_t i = 0; i < lir_function->instructions.size(); ++i) {
                        const auto& inst = lir_function->instructions[i];
                        std::cout << "[" << i << "] " << inst.to_string() << "\n";
                    }
                    
                    // Display individual function LIR instructions
                    auto& lir_func_manager = LIR::LIRFunctionManager::getInstance();
                    auto function_names = lir_func_manager.getFunctionNames();
                    
                    std::cout << "\n=== Function LIR Instructions ===\n";
                    for (const auto& func_name : function_names) {
                        auto lir_func = lir_func_manager.getFunction(func_name);
                        if (lir_func) {
                            std::cout << "\n" << func_name << ":\n";
                            const auto& instructions = lir_func->getInstructions();
                            for (size_t i = 0; i < instructions.size(); ++i) {
                                const auto& inst = instructions[i];
                                std::cout << "[" << i << "] " << inst.to_string() << "\n";
                            }
                        }
                    }
                    
                    std::cout << "\n=== CFG Blocks ===\n";
                    for (size_t i = 0; i < lir_function->cfg->blocks.size(); ++i) {
                        const auto& block = lir_function->cfg->blocks[i];
                        std::cout << "Block " << block->id << ": " << block->label << " (";
                        if (block->is_entry) std::cout << "entry ";
                        if (block->is_exit) std::cout << "exit ";
                        std::cout << ")\n";
                    }
                    std::cout << "\n";
                }
                
                // Initialize JIT backend only after LIR and CFG is complete
                JIT::JITBackend jit;
                jit.set_debug_mode(true); // Enable debug to see what's happening
                
                // Process the main LIR function with JIT (now that CFG is fully built)
                jit.process_function(*lir_function);
                
                // Process all user-defined LIR functions that were registered
                auto& lir_func_manager = LIR::LIRFunctionManager::getInstance();
                auto function_names = lir_func_manager.getFunctionNames();
                
                std::cout << "Registering " << function_names.size() << " user-defined LIR functions with JIT..." << std::endl;
                
                for (const auto& func_name : function_names) {
                    auto lir_func = lir_func_manager.getFunction(func_name);
                    if (lir_func) {
                        std::cout << "JIT registering function: " << func_name << std::endl;
                        // TODO: Register function with JIT backend
                        // For now, the JIT will resolve calls via function ID
                    }
                }
                
                if (jitDebug) {
                    std::cout << "=== JIT Debug Mode - Running Directly ===\n";
                    int exit_code = jit.execute_compiled_function();
                    std::cout << "JIT execution completed with exit code: " << exit_code << std::endl;
                    return exit_code;
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

            // Backend: Use register interpreter instead of VM
            Register::RegisterVM register_vm;
            
            // Enable debug mode if requested
            if (enableDebug) {
                std::cout << "Debug mode enabled for register interpreter\n";
            }
            
            // Generate LIR from optimized AST and execute with register interpreter
            LIR::Generator lir_generator;
            auto lir_function = lir_generator.generate_program(type_check_result);
            
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
            
            // Show LIR disassembly
            std::cout << "\n=== LIR Disassembly ===\n";
            LIR::Disassembler disassemble(*lir_function, true);
            std::cout << disassemble.disassemble() << std::endl;
            
            // Execute using register interpreter with the new LIRFunctionManager
            try {
                // Register the main function in LIRFunctionManager if it exists
                std::shared_ptr<LIR::LIRFunction> main_lir_func;
                if (lir_function) {
                    auto& func_manager = LIR::LIRFunctionManager::getInstance();
                    
                    // Convert the old LIR function to new LIRFunction format
                    std::vector<LIR::LIRParameter> main_params;
                    main_lir_func = func_manager.createFunction("main", main_params, LIR::Type::I64, nullptr);
                    main_lir_func->setInstructions(lir_function->instructions);
                    
                    register_vm.execute_lir_function(*main_lir_func);
                } else {
                    std::cerr << "No LIR function generated\n";
                    return 1;
                }
                
                // Check if the function has an explicit return statement
                // For scripts, we only print the return value if there's an explicit return
                bool should_print_result = false;
                if (main_lir_func && !main_lir_func->getInstructions().empty()) {
                    // Look for a Return instruction (explicit return)
                    // Ret instruction is used for implicit returns
                    for (const auto& inst : main_lir_func->getInstructions()) {
                        if (inst.op == LIR::LIR_Op::Return) {
                            should_print_result = true;
                            break;
                        }
                    }
                }
                
                if (should_print_result) {
                    auto result = register_vm.get_register(0);
                    if (!std::holds_alternative<std::nullptr_t>(result)) {
                        std::cout << register_vm.to_string(result) << std::endl;
                    }
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
    std::cout << "Type 'exit' to quit, '.registers' to show register state, '.debug' to toggle debug mode" << std::endl;
    
    Register::RegisterVM register_vm;
    bool debugMode = false;
    std::string line;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        
        // Handle special commands
        if (line == "exit") {
            break;
        } else if (line == ".registers") {
            std::cout << "Current register state:\n";
            for (size_t i = 0; i < 10; ++i) {
                auto reg_val = register_vm.get_register(i);
                if (!std::holds_alternative<std::nullptr_t>(reg_val)) {
                    std::cout << "  r" << i << ": " << register_vm.to_string(reg_val) << std::endl;
                }
            }
            continue;
        } else if (line == ".stack") {
            std::cout << ".stack command not supported with register interpreter. Use .registers to see register state.\n";
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
            
            // AST Optimization (always run, before type checking)
            AST::ASTOptimizer optimizer;
            ast = optimizer.optimize(ast);
            
            // Type checking
            auto type_check_result = TypeCheckerFactory::check_program(ast);
            if (!type_check_result.success) {
                std::cerr << "Type checking errors:\n";
                for (const auto& error : type_check_result.errors) {
                    std::cerr << "  " << error << std::endl;
                }
                continue;
            }
            
            // Print optimization statistics in debug mode
            if (debugMode) {
                const auto& stats = optimizer.getStats();
                if (stats.constant_folds > 0 || stats.constant_propagations > 0 || 
                    stats.dead_code_eliminated > 0 || stats.branches_simplified > 0) {
                    std::cout << "AST Optimizations: ";
                    if (stats.constant_folds > 0) std::cout << stats.constant_folds << " folds ";
                    if (stats.constant_propagations > 0) std::cout << stats.constant_propagations << " props ";
                    if (stats.dead_code_eliminated > 0) std::cout << stats.dead_code_eliminated << " dead ";
                    if (stats.branches_simplified > 0) std::cout << stats.branches_simplified << " branches ";
                    std::cout << "\n";
                }
            }
            
            // Backend: Generate LIR and execute with register interpreter
            LIR::Generator lir_generator;
            auto lir_function = lir_generator.generate_program(type_check_result);
            
            if (!lir_function) {
                std::cerr << "Failed to generate LIR function\n";
                continue;
            }
            
            // Execute using register interpreter
            try {
                register_vm.execute_function(*lir_function);
                
                // Get result from register 0 (conventional return register)
                auto result = register_vm.get_register(0);
                if (!std::holds_alternative<std::nullptr_t>(result)) {
                    std::cout << "=> " << register_vm.to_string(result) << std::endl;
                }
                
                // Show registers after execution in debug mode
                if (debugMode) {
                    std::cout << "Register state after execution:\n";
                    for (size_t i = 0; i < 10; ++i) { // Show first 10 registers
                        auto reg_val = register_vm.get_register(i);
                        if (!std::holds_alternative<std::nullptr_t>(reg_val)) {
                            std::cout << "  r" << i << ": " << register_vm.to_string(reg_val) << std::endl;
                        }
                    }
                }
                
            } catch (const std::exception& e) {
                std::cerr << "Runtime error: " << e.what() << std::endl;
                if (debugMode) {
                    std::cout << "Register state after error:\n";
                    for (size_t i = 0; i < 10; ++i) {
                        auto reg_val = register_vm.get_register(i);
                        if (!std::holds_alternative<std::nullptr_t>(reg_val)) {
                            std::cout << "  r" << i << ": " << register_vm.to_string(reg_val) << std::endl;
                        }
                    }
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