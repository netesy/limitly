#include "limitly.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/cst/printer.hh"
#include "frontend/ast/printer.hh"
#include "frontend/type_checker.hh"
#include "frontend/memory_checker.hh"
#include "frontend/module_manager.hh"
#include "lir/generator.hh"
#include "lir/functions.hh"
#include "backend/vm/register.hh"
#include "backend/fyra/fyra.hh"
#include "backend/fyra/builder.hh"
#include "ir/IRContext.h"
#include "ir/Module.h"
#include "ir/Function.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace LM {

static std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int Compiler::executeFile(const std::string& filename, const CompileOptions& options) {
    try {
        std::string source = readFile(filename);
        LM::Frontend::Scanner scanner(source, filename);
        scanner.scanTokens();

        if (options.print_tokens) {
            std::cout << "=== Tokens ===\n";
            for (const auto& token : scanner.getTokens()) {
                std::cout << scanner.tokenTypeToString(token.type)
                          << ": '" << token.lexeme << "' (line " << token.line << ")\n";
            }
            std::cout << "\n";
        }

        LM::Frontend::Parser parser(scanner, options.print_cst);
        std::shared_ptr<LM::Frontend::AST::Program> ast = parser.parse();

        LM::Frontend::ModuleManager::getInstance().resolve_all(ast, "root");

        auto type_check_result = LM::Frontend::TypeCheckerFactory::check_program(ast, source, filename);
        if (!type_check_result.success) return 1;

        auto memory_check_result = LM::Frontend::MemoryCheckerFactory::check_program(type_check_result.program, source, filename);
        if (!memory_check_result.success) return 1;
        ast = memory_check_result.program;

        auto post_opt_type_check = LM::Frontend::TypeCheckerFactory::check_program(ast, source, filename);
        if (!post_opt_type_check.success) return 1;

        if (options.print_cst) {
            std::cout << "=== CST ===\n";
            const auto* cstRoot = parser.getCST();
            if (cstRoot) std::cout << Frontend::CST::Printer::printCST(cstRoot) << "\n";
        }

        if (options.print_ast) {
            std::cout << "=== AST ===\n";
            LM::Frontend::AST::ASTPrinter printer;
            printer.process(ast);
            std::cout << "\n";
        }

        std::cout << "[DEBUG] Starting LIR generation..." << std::endl;
        LIR::Generator lir_generator;
        lir_generator.set_import_aliases(post_opt_type_check.import_aliases);
        lir_generator.set_registered_modules(post_opt_type_check.registered_modules);

        auto lir_function = lir_generator.generate_program(post_opt_type_check);
        if (!lir_function) {
            std::cerr << "[ERROR] LIR generation failed" << std::endl;
            return 1;
        }
        std::cout << "[DEBUG] LIR generation complete. Instructions: " << lir_function->instructions.size() << std::endl;

        if (options.print_lir) {
             std::cout << "\n=== Final LIR ===\n";
             for (size_t i = 0; i < lir_function->instructions.size(); ++i) {
                 std::cout << i << ": " << lir_function->instructions[i].to_string() << "\n";
             }
        }

        if (options.use_aot || options.use_wasm || options.use_wasi || options.print_fyra_ir) {
            auto ir_context = std::make_shared<ir::IRContext>();
            LM::Backend::Fyra::LIRToFyraIRBuilder builder(ir_context);
            auto fyra_ir_module = builder.build(*lir_function);
            if (!fyra_ir_module || builder.has_errors()) return 1;

            if (options.print_fyra_ir) {
                for (const auto& func : fyra_ir_module->getFunctions()) { if (func) { func->print(std::cout); std::cout << "\n"; } }
                return 0;
            }

            LM::Backend::Fyra::FyraCompiler fyra;
            fyra.set_debug_mode(options.debug);

            LM::Backend::Fyra::FyraCompileOptions fyra_options;
            fyra_options.platform = (options.target == "windows" ? LM::Backend::Fyra::Platform::Windows : LM::Backend::Fyra::Platform::Linux);
            fyra_options.arch = LM::Backend::Fyra::Architecture::X86_64;
            fyra_options.opt_level = (LM::Backend::Fyra::OptimizationLevel)options.opt_level;
            fyra_options.output_file = options.output_file;

            auto result = fyra.compile(*lir_function, fyra_options);
            return result.success ? 0 : 1;
        } else {
            std::cout << "[DEBUG] Starting VM execution..." << std::endl;
            LM::Backend::VM::Register::RegisterVM register_vm;
            register_vm.execute_function(*lir_function);
            std::cout << "[DEBUG] VM execution complete." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

std::string Formatter::format(const std::string& source) {
    return source;
}

}
