// main.cpp - Limit Programming Language Interpreter
// Main entry point for the Limit language interpreter

#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/cst/printer.hh"
#include "frontend/ast/printer.hh"
#include "frontend/type_checker.hh"
#include "frontend/memory_checker.hh"
#include "frontend/ast.hh"
#include "lir/generator.hh"
#include "lir/functions.hh"
#include "backend/jit/jit.hh"
#include "backend/vm/register.hh"
#include "backend/fyra.hh"
#include "backend/fyra_ir_generator.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

using namespace LM;

void printUsage(const char* programName) {
    std::cout << "Limit Programming Language\n";
    std::cout << "Usage:\n";
    std::cout << "  " << programName << " <source_file>           - Execute a source file\n";
    std::cout << "  " << programName << " -ast <source_file>      - Print the AST\n";
    std::cout << "  " << programName << " -cst <source_file>      - Print the CST\n";
    std::cout << "  " << programName << " -tokens <source_file>   - Print tokens\n";
    std::cout << "  " << programName << " -lir <source_file>      - Print the LIR (Low-level IR)\n";
    std::cout << "  " << programName << " -fyra-ir <source_file>  - Print the Fyra IR\n";
    std::cout << "  " << programName << " -jit <source_file>      - JIT compile to executable\n";
    std::cout << "  " << programName << " -jit-debug <source_file> - JIT compile and run directly\n";
    std::cout << "  " << programName << " -aot <source_file>      - AOT compile with Fyra\n";
    std::cout << "  " << programName << " -wasm <source_file>     - Compile to WebAssembly\n";
    std::cout << "  " << programName << " -wasi <source_file>     - Compile to WASI\n";
    std::cout << "  " << programName << " -debug <source_file>    - Execute with debug output\n";
    std::cout << "  " << programName << " -repl                   - Start interactive REPL\n";
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

int executeFile(const std::string& filename, bool printAst = false, bool printCst = false, 
                bool printTokens = false, bool useJit = false, bool jitDebug = false, 
                bool enableDebug = false, bool printLir = false, bool useAot = false,
                bool useWasm = false, bool useWasi = false, bool printFyraIr = false) {
    try {
        // Initialize LIR function systems
        // Note: Temporarily disabled due to crash in BuiltinUtils::initializeBuiltins()
        // LIR::FunctionUtils::initializeFunctions();
        
        // Read source file
        std::string source = readFile(filename);
        
        // Frontend: Lexical analysis (scanning)
        LM::Frontend::Scanner scanner(source, filename);
        scanner.scanTokens();
        
        // Print tokens if requested
        if (printTokens) {
            std::cout << "=== Tokens ===\n";
            for (const auto& token : scanner.getTokens()) {
                std::cout << scanner.tokenTypeToString(token.type) 
                          << ": '" << token.lexeme << "' (line " << token.line << ")\n";
            }
            std::cout << "\n";
        }
        
        // Frontend: Syntax analysis (parsing)
        bool useCSTMode = printCst;
        LM::Frontend::Parser parser(scanner, useCSTMode);
        std::shared_ptr<LM::Frontend::AST::Program> ast = parser.parse();
        
        // Phase 1: Type checking
        auto type_check_result = LM::Frontend::TypeCheckerFactory::check_program(ast, source, filename);
        if (!type_check_result.success) {
            std::cerr << "Type checking failed\n";
            if (!type_check_result.errors.empty()) {
                for (const auto& err : type_check_result.errors) {
                    std::cerr << "  " << err << "\n";
                }
            }
            return 1;
        }
        
        // Phase 2: Memory safety analysis
        auto memory_check_result = LM::Frontend::MemoryCheckerFactory::check_program(
            type_check_result.program, source, filename);
        if (!memory_check_result.success) {
            return 1;
        }
        
        ast = memory_check_result.program;
        
        // Phase 3: Post-optimization verification
        auto post_opt_type_check = LM::Frontend::TypeCheckerFactory::check_program(ast, source, filename);
        if (!post_opt_type_check.success) {
            std::cerr << "Post-optimization type checking failed\n";
             if (!post_opt_type_check.errors.empty()) {
                for (const auto& err : post_opt_type_check.errors) {
                    std::cerr << "  " << err << "\n";
                }
            }
            return 1;
        }
        
        if (!post_opt_type_check.program) {
            std::cerr << "Post-optimization type check returned null program\n";
            return 1;
        }

        // Print CST if requested
        if (printCst) {
            std::cout << "=== CST ===\n";
            const Frontend::CST::Node* cstRoot = parser.getCST();
            if (cstRoot) {
                std::cout << Frontend::CST::Printer::printCST(cstRoot) << "\n";
            } else {
                std::cout << "No CST available (parser not in CST mode)\n";
            }
        }

        // Print AST if requested
        if (printAst) {
            std::cout << "=== AST ===\n";
            LM::Frontend::AST::ASTPrinter printer;
            printer.process(ast);
            std::cout << "\n";
        }

        // Generate Fyra IR if requested (before LIR generation)
        if (printFyraIr) {
            try {
                std::cout << "Starting Fyra IR generation..." << std::endl;
                LM::Backend::Fyra::FyraIRGenerator fyra_ir_gen;
                auto fyra_ir_module = fyra_ir_gen.generate_from_ast(post_opt_type_check.program);
                std::cout << "Fyra IR generation finished." << std::endl;
                
                if (!fyra_ir_module) {
                    std::cerr << "Failed to generate Fyra IR\n";
                    return 1;
                }
                
                if (fyra_ir_gen.has_errors()) {
                    std::cerr << "Fyra IR generation errors:\n";
                    for (const auto& error : fyra_ir_gen.get_errors()) {
                        std::cerr << "  " << error << "\n";
                    }
                    return 1;
                }
                
                std::cout << "=== Fyra IR ===\n";
                // ir::Module doesn't have to_ir_string, we need to print it somehow or just acknowledge success for now
                std::cout << "Fyra IR module generated successfully.\n";
                return 0;
            } catch (const std::exception& e) {
                std::cerr << "Fyra IR generation error: " << e.what() << "\n";
                return 1;
            }
        }

        // Generate LIR once for all backends
        LIR::Generator lir_generator;
        auto lir_function = lir_generator.generate_program(post_opt_type_check);
        
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

        // Print LIR if requested
        if (printLir) {
            std::cout << "Generated LIR function with " << lir_function->instructions.size() << " instructions\n";
            std::cout << "CFG generation completed with " << lir_function->cfg->blocks.size() << " blocks\n";
            
            // Initialize and run LIR disassembler
            LIR::Disassembler disassemble(*lir_function, true);
            std::cout << "\n=== LIR Disassembly ===\n";
            std::cout << disassemble.disassemble() << std::endl;
            
            std::cout << "\n=== Detailed Instruction Analysis with Types ===\n";
            for (size_t i = 0; i < lir_function->instructions.size(); ++i) {
                const auto& inst = lir_function->instructions[i];
                std::cout << "[" << i << "] " << inst.to_string();
                
                // Show types
                std::cout << " [result_type=" << static_cast<int>(inst.result_type);
                if (inst.type_a != LIR::Type::Void) {
                    std::cout << ", type_a=" << static_cast<int>(inst.type_a);
                }
                if (inst.type_b != LIR::Type::Void) {
                    std::cout << ", type_b=" << static_cast<int>(inst.type_b);
                }
                std::cout << "]\n";
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
            
            return 0;
        }

        if (useAot || useWasm || useWasi) {
            try {
                // Initialize Fyra compiler
                LM::Backend::Fyra::FyraCompiler fyra;
                fyra.set_debug_mode(enableDebug);
                
                std::string output_filename = filename;
                size_t dot_pos = output_filename.rfind(".lm");
                if (dot_pos != std::string::npos) {
                    output_filename.erase(dot_pos);
                }
                
                LM::Backend::Fyra::CompileResult result;
                
                if (useAot) {
                    #ifdef _WIN32
                        output_filename += ".exe";
                    #endif
                    result = fyra.compile_ast_aot(post_opt_type_check.program, output_filename);
                    std::cout << "AOT compilation with Fyra (Direct AST Path)\n";
                } else if (useWasm) {
                    output_filename += ".wasm";
                    // result = fyra.compile_wasm(*lir_function, output_filename);
                    std::cout << "WebAssembly compilation with Fyra (Direct AST Path - Placeholder)\n";
                } else if (useWasi) {
                    output_filename += ".wasi";
                    // result = fyra.compile_wasi(*lir_function, output_filename);
                    std::cout << "WASI compilation with Fyra (Direct AST Path - Placeholder)\n";
                }
                
                if (result.success) {
                    std::cout << "Compiled to " << result.output_file << "\n";
                } else {
                    std::cerr << "Fyra compilation failed: " << result.error_message << "\n";
                    return 1;
                }
            } catch (const std::exception& e) {
                std::cerr << "Fyra Error: " << e.what() << "\n";
                return 1;
            }
        } else if (useJit) {
            try {
                // Initialize JIT backend
                LM::Backend::JIT::Compiler::JITBackend jit;
                jit.set_debug_mode(enableDebug || jitDebug);
                jit.process_function(*lir_function);
                
                if (jitDebug) {
                    int exit_code = jit.execute_compiled_function();
                    return exit_code;
                } else {
                    std::string output_filename = filename;
                    size_t dot_pos = output_filename.rfind(".lm");
                    if (dot_pos != std::string::npos) {
                        output_filename.erase(dot_pos);
                    }
                    #ifdef _WIN32
                        output_filename += ".exe";
                    #endif
                    
                    auto result = jit.compile(LM::Backend::JIT::Compiler::CompileMode::ToExecutable, 
                                            output_filename);
                    if (result.success) {
                        std::cout << "Compiled to " << result.output_file << "\n";
                    } else {
                        std::cerr << "JIT compilation failed: " << result.error_message << "\n";
                        return 1;
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "JIT Error: " << e.what() << "\n";
                return 1;
            }
        } else {
           
            try {
                // Backend: Use register interpreter
                LM::Backend::VM::Register::RegisterVM register_vm;
                std::shared_ptr<LIR::LIRFunction> main_lir_func;
                auto& func_manager = LIR::LIRFunctionManager::getInstance();
                
                std::vector<LIR::LIRParameter> main_params;
                main_lir_func = func_manager.createFunction("__top_level_wrapper__", main_params, LIR::Type::I64, nullptr);
                main_lir_func->setInstructions(lir_function->instructions);
                
                register_vm.execute_lir_function(*main_lir_func);
                
                // Check for explicit return statement
                bool should_print_result = false;
                if (main_lir_func && !main_lir_func->getInstructions().empty()) {
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
                        std::cout << register_vm.to_string(result) << "\n";
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Runtime error: " << e.what() << "\n";
                return 1;
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}

void startRepl() {
    std::cout << "Limit Programming Language REPL\n";
    std::cout << "Type 'exit' to quit, '.registers' to show register state\n\n";
    
    // Initialize LIR function systems
    LIR::FunctionUtils::initializeFunctions();
    
    LM::Backend::VM::Register::RegisterVM register_vm;
    std::string line;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        
        // Handle special commands
        if (line == "exit") {
            break;
        } else if (line == ".registers") {
            std::cout << "Register state:\n";
            for (size_t i = 0; i < 10; ++i) {
                auto reg_val = register_vm.get_register(i);
                if (!std::holds_alternative<std::nullptr_t>(reg_val)) {
                    std::cout << "  r" << i << ": " << register_vm.to_string(reg_val) << "\n";
                }
            }
            continue;
        } else if (line.empty()) {
            continue;
        }
        
        try {
            // Frontend: Lexical analysis
            LM::Frontend::Scanner scanner(line);
            scanner.scanTokens();
            
            // Frontend: Syntax analysis
            LM::Frontend::Parser parser(scanner, false);
            std::shared_ptr<LM::Frontend::AST::Program> ast = parser.parse();
            
            // Type checking
            auto type_check_result = LM::Frontend::TypeCheckerFactory::check_program(ast);
            if (!type_check_result.success) {
                continue;
            }
            
            // Memory safety analysis
            auto memory_check_result = LM::Frontend::MemoryCheckerFactory::check_program(
                type_check_result.program);
            if (!memory_check_result.success) {
                continue;
            }
            
            ast = memory_check_result.program;
            
            // Post-optimization verification
            auto post_opt_type_check = LM::Frontend::TypeCheckerFactory::check_program(ast);
            if (!post_opt_type_check.success) {
                continue;
            }
            
            // Backend: Generate LIR and execute
            LIR::Generator lir_generator;
            auto lir_function = lir_generator.generate_program(post_opt_type_check);
            
            if (!lir_function) {
                std::cerr << "Failed to generate LIR function\n";
                continue;
            }
            
            // Execute using register interpreter
            try {
                register_vm.execute_function(*lir_function);
                
                auto result = register_vm.get_register(0);
                if (!std::holds_alternative<std::nullptr_t>(result)) {
                    std::cout << "=> " << register_vm.to_string(result) << "\n";
                }
            } catch (const std::exception& e) {
                std::cerr << "Runtime error: " << e.what() << "\n";
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
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
        return executeFile(argv[2], true, false, false, false, false, false, false, false, false, false);
    } else if (arg == "-cst" && argc >= 3) {
        return executeFile(argv[2], false, true, false, false, false, false, false, false, false, false);
    } else if (arg == "-tokens" && argc >= 3) {
        return executeFile(argv[2], false, false, true, false, false, false, false, false, false, false);
    } else if (arg == "-lir" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, false, true, false, false, false, false);
    } else if (arg == "-fyra-ir" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, false, false, false, false, false, true);
    } else if (arg == "-jit" && argc >= 3) {
        return executeFile(argv[2], false, false, false, true, false, false, false, false, false, false, false);
    } else if (arg == "-jit-debug" && argc >= 3) {
        return executeFile(argv[2], false, false, false, true, true, false, false, false, false, false, false);
    } else if (arg == "-aot" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, false, false, true, false, false, false);
    } else if (arg == "-wasm" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, false, false, false, true, false, false);
    } else if (arg == "-wasi" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, false, false, false, false, true, false);
    } else if (arg == "-debug" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, true, false, false, false, false, false);
    } else if (arg[0] == '-') {
        std::cerr << "Unknown option: " << arg << "\n";
        printUsage(argv[0]);
        return 1;
    } else {
        return executeFile(arg, false, false, false, false, false, false, false, false, false, false, false);
    }
}
