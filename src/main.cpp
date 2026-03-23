// main.cpp - Limit Programming Language Interpreter
// Main entry point for the Limit language interpreter

#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/cst/printer.hh"
#include "frontend/ast/printer.hh"
#include "frontend/type_checker.hh"
#include "frontend/memory_checker.hh"
#include "frontend/ast.hh"
#include <set>
#include <algorithm>
#include "lir/generator.hh"
#include "lir/functions.hh"
// #include "backend/jit/jit.hh"
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
    std::cout << "\n  Execution (Register VM):\n";
    std::cout << "    " << programName << " run [options] <source_file>\n";
    std::cout << "      Options:\n";
    std::cout << "        -debug                Enable debug output\n";
    std::cout << "\n  Compilation (AOT/WASM):\n";
    std::cout << "    " << programName << " build [options] <source_file>\n";
    std::cout << "      Options:\n";
    std::cout << "        -target <target>      Target platform (windows, linux, macos, wasm)\n";
    std::cout << "        -o <output>           Output file name\n";
    std::cout << "        -O <level>            Optimization level (0, 1, 2, 3)\n";
    std::cout << "        -d                    Output intermediate files (.s for native, .wat for wasm)\n";
    std::cout << "\n  Debugging:\n";
    std::cout << "    " << programName << " -ast <source_file>      Print the AST\n";
    std::cout << "    " << programName << " -cst <source_file>      Print the CST\n";
    std::cout << "    " << programName << " -tokens <source_file>   Print tokens\n";
    std::cout << "    " << programName << " -lir <source_file>      Print the LIR (Low-level IR)\n";
    std::cout << "    " << programName << " -fyra-ir <source_file>  Print the Fyra IR\n";
    std::cout << "\n  Interactive:\n";
    std::cout << "    " << programName << " -repl                   Start interactive REPL\n";
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

void resolveImports(std::shared_ptr<LM::Frontend::AST::Program> program, const std::string& currentPath, std::set<std::string>& loadedModules) {
    std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> moduleDeclarations;
    
    // Find all imports in the current program
    for (const auto& stmt : program->statements) {
        if (auto importStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ImportStatement>(stmt)) {
            std::string modulePath = importStmt->modulePath;
            if (loadedModules.count(modulePath)) continue;

            // Convert dot notation to path
            std::string filePath = modulePath;
            std::replace(filePath.begin(), filePath.end(), '.', '/');
            filePath += ".lm";

            std::string source;
            try {
                source = readFile(filePath);
            } catch (...) {
                // If not found at root, try relative to currentPath? 
                // For now, let's just stick to root-relative for tests
                continue;
            }

            LM::Frontend::Scanner scanner(source, filePath);
            scanner.scanTokens();
            LM::Frontend::Parser parser(scanner);
            auto moduleAst = parser.parse();

            loadedModules.insert(modulePath);
            // Recursively resolve imports for this module
            resolveImports(moduleAst, filePath, loadedModules);

            // Wrap module AST in a ModuleDeclaration
            auto modDecl = std::make_shared<LM::Frontend::AST::ModuleDeclaration>();
            modDecl->name = modulePath;
            for (auto& s : moduleAst->statements) {
                if (auto func = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(s)) {
                    if (func->visibility == LM::Frontend::AST::VisibilityLevel::Public)
                        modDecl->publicMembers.push_back(s);
                    else
                        modDecl->privateMembers.push_back(s);
                } else if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(s)) {
                    if (var->visibility == LM::Frontend::AST::VisibilityLevel::Public)
                        modDecl->publicMembers.push_back(s);
                    else
                        modDecl->privateMembers.push_back(s);
                } else {
                    modDecl->privateMembers.push_back(s);
                }
            }
            moduleDeclarations.push_back(modDecl);
        }
    }

    // Prepend module declarations to the program
    if (!moduleDeclarations.empty()) {
        program->statements.insert(program->statements.begin(), moduleDeclarations.begin(), moduleDeclarations.end());
    }
}

int executeFile(const std::string& filename, bool printAst = false, bool printCst = false, 
                bool printTokens = false, bool useJit = false, bool jitDebug = false, 
                bool enableDebug = false, bool printLir = false, bool useAot = false,
                bool useWasm = false, bool useWasi = false, bool printFyraIr = false,
                const std::string& platform = "linux", int opt_level = 2, bool dump_intermediate = false) {
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
        
        // Note: Import resolution is now handled by the type checker

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
        std::cerr << "DEBUG: Post-optimization type check completed\n";
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
        
        std::cerr << "DEBUG: About to generate LIR\n";

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
        if (printFyraIr || useAot || useWasm || useWasi) {
            try {
                std::cerr << "Starting Fyra IR generation..." << std::endl;
                auto fyra_ir_gen = std::make_shared<LM::Backend::Fyra::FyraIRGenerator>();
                auto fyra_ir_module = fyra_ir_gen->generate_from_ast(post_opt_type_check.program);
                std::cerr << "Fyra IR generation finished." << std::endl;
                
                if (!fyra_ir_module) {
                    std::cerr << "Failed to generate Fyra IR\n";
                    return 1;
                }
                
                if (fyra_ir_gen->has_errors()) {
                    std::cerr << "Fyra IR generation errors:\n";
                    for (const auto& error : fyra_ir_gen->get_errors()) {
                        std::cerr << "  " << error << "\n";
                    }
                    return 1;
                }

                if (printFyraIr) {
                    std::cout << "=== Fyra IR Module Created Successfully ===\n";
                    if (fyra_ir_module) {
                        for (const auto& func : fyra_ir_module->getFunctions()) {
                            if (func) {
                                func->print(std::cout);
                                std::cout << "\n";
                            }
                        }
                    }
                    return 0;
                }

                if (useAot || useWasm || useWasi) {
                    // Initialize Fyra compiler
                    LM::Backend::Fyra::FyraCompiler fyra;
                    fyra.set_debug_mode(enableDebug);
                    
                    std::string output_filename = filename;
                    size_t dot_pos = output_filename.rfind(".lm");
                    if (dot_pos != std::string::npos) {
                        output_filename.erase(dot_pos);
                    }
                    
                    // Convert platform string to enum
                    LM::Backend::Fyra::Platform fyra_platform = LM::Backend::Fyra::Platform::Linux;
                    if (platform == "linux") {
                        fyra_platform = LM::Backend::Fyra::Platform::Linux;
                    } else if (platform == "macos") {
                        fyra_platform = LM::Backend::Fyra::Platform::MacOS;
                    } else if (platform == "wasm") {
                        fyra_platform = LM::Backend::Fyra::Platform::WASM;
                    } else if (platform == "windows") {
                        fyra_platform = LM::Backend::Fyra::Platform::Windows;
                    }
                    
                    // Convert optimization level
                    LM::Backend::Fyra::OptimizationLevel fyra_opt = LM::Backend::Fyra::OptimizationLevel::O2;
                    if (opt_level == 0) {
                        fyra_opt = LM::Backend::Fyra::OptimizationLevel::O0;
                    } else if (opt_level == 1) {
                        fyra_opt = LM::Backend::Fyra::OptimizationLevel::O1;
                    } else if (opt_level == 3) {
                        fyra_opt = LM::Backend::Fyra::OptimizationLevel::O3;
                    }
                    
                    LM::Backend::Fyra::FyraCompileOptions options;
                    options.platform = fyra_platform;
                    options.arch = (fyra_platform == LM::Backend::Fyra::Platform::WASM ? LM::Backend::Fyra::Architecture::WASM32 : LM::Backend::Fyra::Architecture::X86_64);
                    options.opt_level = fyra_opt;
                    options.dump_intermediate = dump_intermediate;
                    options.output_file = output_filename;
                    if (useAot && fyra_platform == LM::Backend::Fyra::Platform::Windows) options.output_file += ".exe";
                    else if (useWasm || useWasi) options.output_file += dump_intermediate ? ".wat" : (useWasm ? ".wasm" : ".wasi");

                    auto result = fyra.compile_module(fyra_ir_module, options);
                    
                    if (result.success) {
                        std::cout << "Compiled to " << result.output_file << "\n";
                        return 0;
                    } else {
                        std::cerr << "Fyra compilation failed: " << result.error_message << "\n";
                        return 1;
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Fyra Error: " << e.what() << "\n";
                return 1;
            }
        }

        // Generate LIR once for all backends
        std::cerr << "DEBUG: Creating LIR generator\n";
        LIR::Generator lir_generator;
        std::cerr << "DEBUG: Setting import aliases\n";
        lir_generator.set_import_aliases(post_opt_type_check.import_aliases);
        std::cerr << "DEBUG: Setting registered modules\n";
        lir_generator.set_registered_modules(post_opt_type_check.registered_modules);
        std::cerr << "DEBUG: Calling generate_program\n";
        
        std::unique_ptr<LIR::LIR_Function> lir_function;
        try {
            lir_function = lir_generator.generate_program(post_opt_type_check);
            std::cerr << "DEBUG: generate_program returned\n";
        } catch (const std::exception& e) {
            std::cerr << "ERROR in generate_program: " << e.what() << "\n";
            return 1;
        } catch (...) {
            std::cerr << "ERROR: Unknown exception in generate_program\n";
            return 1;
        }
        
        if (!lir_function) {
            std::cerr << "Failed to generate LIR function\n";
            return 1;
        }
        
        std::cerr << "DEBUG: LIR function generated successfully\n";
        
        if (lir_generator.has_errors()) {
            std::cerr << "LIR generation errors:\n";
            for (const auto& error : lir_generator.get_errors()) {
                std::cerr << "  " << error << std::endl;
            }
            return 1;
        }
        
        std::cerr << "DEBUG: No LIR errors\n";

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

        if (useJit) {
            std::cerr << "JIT compilation is currently disabled.\n";
            return 1;
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
            
            // Note: Import resolution is now handled by the type checker

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
            lir_generator.set_import_aliases(post_opt_type_check.import_aliases);
            lir_generator.set_registered_modules(post_opt_type_check.registered_modules);
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
    
    std::string command = argv[1];
    
    // Handle REPL
    if (command == "-repl") {
        startRepl();
        return 0;
    }
    
    // Handle debugging commands (legacy)
    if (command == "-ast" && argc >= 3) {
        return executeFile(argv[2], true, false, false, false, false, false, false, false, false, false);
    } else if (command == "-cst" && argc >= 3) {
        return executeFile(argv[2], false, true, false, false, false, false, false, false, false, false);
    } else if (command == "-tokens" && argc >= 3) {
        return executeFile(argv[2], false, false, true, false, false, false, false, false, false, false);
    } else if (command == "-lir" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, false, true, false, false, false, false);
    } else if (command == "-fyra-ir" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, false, false, false, false, false, true);
    } else if (command == "-debug" && argc >= 3) {
        return executeFile(argv[2], false, false, false, false, false, true, false, false, false, false, false);
    }
    
    // Handle 'run' command
    if (command == "run") {
        if (argc < 3) {
            std::cerr << "Error: 'run' command requires a source file\n";
            std::cerr << "Usage: " << argv[0] << " run [options] <source_file>\n";
            return 1;
        }
        
        std::string source_file;
        bool enable_debug = false;
        
        // Parse options
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-debug") {
                enable_debug = true;
            } else if (arg[0] != '-') {
                source_file = arg;
            }
        }
        
        if (source_file.empty()) {
            std::cerr << "Error: No source file specified\n";
            return 1;
        }
        
        // Execute with register VM
        return executeFile(source_file, false, false, false, false, false, enable_debug, false, false, false, false, false);
    }
    
    // Handle 'build' command
    if (command == "build") {
        if (argc < 2) {
            std::cerr << "Error: 'build' command requires a source file\n";
            std::cerr << "Usage: " << argv[0] << " build [target] [arch] [opt_level] <source_file> [-d]\n";
            std::cerr << "Targets: windows, linux, macos, wasm (default: current platform)\n";
            std::cerr << "Arch: x86_64, aarch64, wasm32, riscv64 (default: x86_64)\n";
            std::cerr << "Opt level: 0, 1, 2, 3 (default: 2)\n";
            return 1;
        }
        
        // Determine default target based on host platform
        std::string default_target;
        #ifdef _WIN32
            default_target = "windows";
        #elif defined(__APPLE__)
            default_target = "macos";
        #else
            default_target = "linux";
        #endif
        
        std::string target = default_target;
        std::string arch = "x86_64";
        int opt_level = 2;
        std::string source_file;
        bool dump_intermediate = false;
        
        // Parse positional arguments and flags
        int positional_count = 0;
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            
            if (arg == "-d") {
                dump_intermediate = true;
            } else if (arg[0] == '-') {
                // Unknown flag
                std::cerr << "Error: Unknown flag '" << arg << "'\n";
                return 1;
            } else if (positional_count >= 3) {
                // Source file already set, ignore additional arguments
                continue;
            } else {
                // Positional argument
                if (positional_count == 0) {
                    // Could be target or source file
                    if (arg == "windows" || arg == "linux" || arg == "macos" || arg == "wasm") {
                        target = arg;
                        positional_count++;
                    } else {
                        // It's the source file
                        source_file = arg;
                        positional_count = 3;  // Mark source file as found
                    }
                } else if (positional_count == 1) {
                    // Could be arch or source file
                    if (arg == "x86_64" || arg == "aarch64" || arg == "wasm32" || arg == "riscv64") {
                        arch = arg;
                        positional_count++;
                    } else {
                        // It's the source file
                        source_file = arg;
                        positional_count = 3;  // Mark source file as found
                    }
                } else if (positional_count == 2) {
                    // Could be opt_level or source file
                    if (arg.length() == 1 && arg[0] >= '0' && arg[0] <= '3') {
                        opt_level = std::stoi(arg);
                        positional_count++;
                    } else {
                        // It's the source file
                        source_file = arg;
                        positional_count = 3;  // Mark source file as found
                    }
                }
            }
        }
        
        if (source_file.empty()) {
            std::cerr << "Error: No source file specified\n";
            return 1;
        }
        
        // Validate target
        if (target != "windows" && target != "linux" && target != "macos" && target != "wasm") {
            std::cerr << "Error: Invalid target '" << target << "'\n";
            std::cerr << "Valid targets: windows, linux, macos, wasm\n";
            return 1;
        }
        
        // Validate arch
        if (arch != "x86_64" && arch != "aarch64" && arch != "wasm32" && arch != "riscv64") {
            std::cerr << "Error: Invalid architecture '" << arch << "'\n";
            std::cerr << "Valid architectures: x86_64, aarch64, wasm32, riscv64\n";
            return 1;
        }
        
        // Validate opt_level
        if (opt_level < 0 || opt_level > 3) {
            std::cerr << "Error: Invalid optimization level '" << opt_level << "'\n";
            std::cerr << "Valid levels: 0, 1, 2, 3\n";
            return 1;
        }
        
        // Generate intermediate file extension based on target
        std::string intermediate_ext;
        if (target == "wasm") {
            intermediate_ext = ".wat";
        } else {
            intermediate_ext = ".s";
        }
        
        // If -d flag is set, output intermediate file instead of binary
        if (dump_intermediate) {
            std::string output_file = source_file;
            size_t dot_pos = output_file.rfind(".lm");
            if (dot_pos != std::string::npos) {
                output_file.erase(dot_pos);
            }
            output_file += intermediate_ext;
            std::cout << "Dumping intermediate " << intermediate_ext << " file to: " << output_file << "\n";
            // TODO: Implement intermediate file output
            return 0;
        }
        
        // Compile based on target
        bool use_aot = (target != "wasm");
        bool use_wasm = (target == "wasm");
        
        return executeFile(source_file, false, false, false, false, false, false, false, use_aot, use_wasm, false, false, target, opt_level, dump_intermediate);
    }
    
    // Handle legacy single file execution (backward compatibility)
    if (command[0] != '-') {
        return executeFile(command, false, false, false, false, false, false, false, false, false, false, false);
    }
    
    // Unknown option
    std::cerr << "Unknown option: " << command << "\n";
    printUsage(argv[0]);
    return 1;
}
