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
// #include "backend/fyra.hh"
// #include "backend/fyra_ir_generator.hh"
#include <iostream>
#include <filesystem>
#include <set>

namespace fs = std::filesystem;
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

using namespace LM;

void printUsage(const char* programName) {
    std::cout << "Limit Programming Language\n";
    std::cout << "Usage:\n";
    std::cout << "  " << programName << " <source_file>           - Execute a source file\n";
    std::cout << "  " << programName << " -I <dir>                 - Add include directory\n";
    std::cout << "  " << programName << " -o <file>                - Specify output file\n";
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

void resolveImportsRecursive(const std::string& filename, const std::vector<std::string>& includePaths,
                            std::vector<std::shared_ptr<LM::Frontend::AST::Statement>>& all_statements,
                            std::set<std::string>& processed_files) {

    std::string source;
    try {
        source = readFile(filename);
    } catch (...) {
        return;
    }

    LM::Frontend::Scanner scanner(source, filename);
    scanner.scanTokens();
    LM::Frontend::Parser parser(scanner, false);
    std::shared_ptr<LM::Frontend::AST::Program> program = parser.parse();

    if (!program) return;

    for (const auto& stmt : program->statements) {
        if (auto importStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ImportStatement>(stmt)) {
            std::string importPath = importStmt->modulePath;
            if (importStmt->isStringLiteralPath && importPath.size() >= 2 &&
                ((importPath.front() == '\"' && importPath.back() == '\"') ||
                 (importPath.front() == '\'' && importPath.back() == '\''))) {
                importPath = importPath.substr(1, importPath.size() - 2);
            }

            std::string resolvedPath = "";
            fs::path currentDir = fs::path(filename).parent_path();
            if (fs::exists(currentDir / importPath)) {
                resolvedPath = (currentDir / importPath).string();
            } else {
                for (const auto& path : includePaths) {
                    if (fs::exists(fs::path(path) / importPath)) {
                        resolvedPath = (fs::path(path) / importPath).string();
                        break;
                    }
                }
            }

            if (!resolvedPath.empty()) {
                std::string absPath = fs::absolute(resolvedPath).string();
                if (processed_files.find(absPath) == processed_files.end()) {
                    processed_files.insert(absPath);
                    resolveImportsRecursive(resolvedPath, includePaths, all_statements, processed_files);
                }
            }
        } else {
            all_statements.push_back(stmt);
        }
    }
}

int executeFile(const std::string& filename, const std::vector<std::string>& includePaths,
                const std::string& outputPath = "",
                bool printAst = false, bool printCst = false,
                bool printTokens = false, bool useJit = false, bool jitDebug = false, 
                bool enableDebug = false, bool printLir = false, bool useAot = false,
                bool useWasm = false, bool useWasi = false, bool printFyraIr = false) {
    try {
        std::string source = readFile(filename);
        
        LM::Frontend::Scanner scanner(source, filename);
        scanner.scanTokens();
        
        if (printTokens) {
            std::cout << "=== Tokens ===\n";
            for (const auto& token : scanner.getTokens()) {
                std::cout << scanner.tokenTypeToString(token.type) 
                          << ": '" << token.lexeme << "' (line " << token.line << ")\n";
            }
            std::cout << "\n";
        }
        
        bool useCSTMode = printCst;
        LM::Frontend::Parser parser(scanner, useCSTMode);
        std::shared_ptr<LM::Frontend::AST::Program> ast = parser.parse();

        if (!ast) return 1;

        std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> all_statements;
        std::set<std::string> processed_files;
        processed_files.insert(fs::absolute(filename).string());

        std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> main_file_statements;

        for (const auto& stmt : ast->statements) {
            if (auto importStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ImportStatement>(stmt)) {
                std::string importPath = importStmt->modulePath;
                if (importStmt->isStringLiteralPath && importPath.size() >= 2 &&
                    ((importPath.front() == '\"' && importPath.back() == '\"') ||
                     (importPath.front() == '\'' && importPath.back() == '\''))) {
                    importPath = importPath.substr(1, importPath.size() - 2);
                }

                std::string resolvedPath = "";
                fs::path currentDir = fs::path(filename).parent_path();
                if (fs::exists(currentDir / importPath)) {
                    resolvedPath = (currentDir / importPath).string();
                } else {
                    for (const auto& path : includePaths) {
                        if (fs::exists(fs::path(path) / importPath)) {
                            resolvedPath = (fs::path(path) / importPath).string();
                            break;
                        }
                    }
                }

                if (!resolvedPath.empty()) {
                    std::string absPath = fs::absolute(resolvedPath).string();
                    if (processed_files.find(absPath) == processed_files.end()) {
                        processed_files.insert(absPath);
                        resolveImportsRecursive(resolvedPath, includePaths, all_statements, processed_files);
                    }
                }
            } else {
                main_file_statements.push_back(stmt);
            }
        }

        // Append main file statements after imports
        for (auto& stmt : main_file_statements) {
            all_statements.push_back(stmt);
        }
        ast->statements = all_statements;
        
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
        
        auto memory_check_result = LM::Frontend::MemoryCheckerFactory::check_program(
            type_check_result.program, source, filename);
        if (!memory_check_result.success) {
            return 1;
        }
        
        ast = memory_check_result.program;
        
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

        if (printCst) {
            std::cout << "=== CST ===\n";
            const Frontend::CST::Node* cstRoot = parser.getCST();
            if (cstRoot) {
                std::cout << Frontend::CST::Printer::printCST(cstRoot) << "\n";
            }
        }

        if (printAst) {
            std::cout << "=== AST ===\n";
            LM::Frontend::AST::ASTPrinter printer;
            printer.process(ast);
            std::cout << "\n";
        }

        if (printFyraIr) {
            std::cerr << "Fyra IR generation is currently disabled due to missing backend files.\n";
            return 1;
        }

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

        if (printLir) {
            std::cout << "Generated LIR function with " << lir_function->instructions.size() << " instructions\n";
            std::cout << "CFG generation completed with " << lir_function->cfg->blocks.size() << " blocks\n";
            
            LIR::Disassembler disassemble(*lir_function, true);
            std::cout << "\n=== LIR Disassembly ===\n";
            std::cout << disassemble.disassemble() << std::endl;
            
            std::cout << "\n=== Detailed Instruction Analysis with Types ===\n";
            for (size_t i = 0; i < lir_function->instructions.size(); ++i) {
                const auto& inst = lir_function->instructions[i];
                std::cout << "[" << i << "] " << inst.to_string();
                std::cout << " [result_type=" << static_cast<int>(inst.result_type);
                if (inst.type_a != LIR::Type::Void) std::cout << ", type_a=" << static_cast<int>(inst.type_a);
                if (inst.type_b != LIR::Type::Void) std::cout << ", type_b=" << static_cast<int>(inst.type_b);
                std::cout << "]\n";
            }
            return 0;
        }

        if (useAot || useWasm || useWasi) {
            std::cerr << "Fyra-based compilation is currently disabled.\n";
            return 1;
        } else if (useJit) {
            try {
                LM::Backend::JIT::Compiler::JITBackend jit;
                jit.set_debug_mode(enableDebug || jitDebug);
                jit.process_function(*lir_function);
                
                if (jitDebug) {
                    return jit.execute_compiled_function();
                } else {
                    std::string output_filename = outputPath.empty() ? filename : outputPath;
                    if (outputPath.empty()) {
                        size_t dot_pos = output_filename.rfind(".lm");
                        if (dot_pos != std::string::npos) output_filename.erase(dot_pos);
                        #ifdef _WIN32
                            output_filename += ".exe";
                        #endif
                    }
                    
                    auto result = jit.compile(LM::Backend::JIT::Compiler::CompileMode::ToExecutable, output_filename);
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
                LM::Backend::VM::Register::RegisterVM register_vm;
                auto& func_manager = LIR::LIRFunctionManager::getInstance();
                std::vector<LIR::LIRParameter> main_params;
                auto main_lir_func = func_manager.createFunction("__top_level_wrapper__", main_params, LIR::Type::I64, nullptr);
                main_lir_func->setInstructions(lir_function->instructions);
                
                register_vm.execute_lir_function(*main_lir_func);
                
                bool should_print_result = false;
                for (const auto& inst : main_lir_func->getInstructions()) {
                    if (inst.op == LIR::LIR_Op::Return) {
                        should_print_result = true;
                        break;
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
    std::cout << "Type 'exit' to quit\n\n";
    
    LIR::FunctionUtils::initializeFunctions();
    LM::Backend::VM::Register::RegisterVM register_vm;
    std::string line;
    
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line) || line == "exit") break;
        if (line.empty()) continue;
        
        try {
            LM::Frontend::Scanner scanner(line);
            scanner.scanTokens();
            LM::Frontend::Parser parser(scanner, false);
            auto ast = parser.parse();
            if (!ast) continue;
            auto tcr = LM::Frontend::TypeCheckerFactory::check_program(ast);
            if (!tcr.success) continue;
            auto mcr = LM::Frontend::MemoryCheckerFactory::check_program(tcr.program);
            if (!mcr.success) continue;
            auto potcr = LM::Frontend::TypeCheckerFactory::check_program(mcr.program);
            if (!potcr.success) continue;
            LIR::Generator lg;
            auto lf = lg.generate_program(potcr);
            if (!lf) continue;
            register_vm.execute_function(*lf);
            auto result = register_vm.get_register(0);
            if (!std::holds_alternative<std::nullptr_t>(result)) std::cout << "=> " << register_vm.to_string(result) << "\n";
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
    
    std::vector<std::string> includePaths;
    std::string sourceFile;
    std::string outputPath;
    bool printAst = false, printCst = false, printTokens = false, useJit = false, jitDebug = false, enableDebug = false, printLir = false, useAot = false, useWasm = false, useWasi = false, printFyraIr = false, repl = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-repl") repl = true;
        else if (arg == "-ast") printAst = true;
        else if (arg == "-cst") printCst = true;
        else if (arg == "-tokens") printTokens = true;
        else if (arg == "-lir") printLir = true;
        else if (arg == "-fyra-ir") printFyraIr = true;
        else if (arg == "-jit") useJit = true;
        else if (arg == "-jit-debug") { useJit = true; jitDebug = true; }
        else if (arg == "-aot") useAot = true;
        else if (arg == "-wasm") useWasm = true;
        else if (arg == "-wasi") useWasi = true;
        else if (arg == "-debug") enableDebug = true;
        else if (arg == "-I") {
            if (i + 1 < argc) includePaths.push_back(argv[++i]);
            else { std::cerr << "Error: -I requires a directory path\n"; return 1; }
        } else if (arg == "-o") {
            if (i + 1 < argc) outputPath = argv[++i];
            else { std::cerr << "Error: -o requires a filename\n"; return 1; }
        } else if (arg[0] == '-') {
            std::cerr << "Unknown option: " << arg << "\n";
            printUsage(argv[0]);
            return 1;
        } else sourceFile = arg;
    }

    if (repl) { startRepl(); return 0; }
    if (sourceFile.empty()) { std::cerr << "Error: No source file specified\n"; printUsage(argv[0]); return 1; }
    return executeFile(sourceFile, includePaths, outputPath, printAst, printCst, printTokens, useJit, jitDebug, enableDebug, printLir, useAot, useWasm, useWasi, printFyraIr);
}
