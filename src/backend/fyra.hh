// fyra.hh - Fyra Backend Integration
// Provides AOT and WebAssembly compilation through Fyra

#pragma once

#include "../lir/lir.hh"
#include "../frontend/ast.hh"
#include <string>
#include <memory>
#include <vector>

namespace ir { class Module; }

namespace LM::Backend::Fyra {

enum class CompileTarget {
    AOT,        // Ahead-of-time native compilation
    WASM,       // WebAssembly target
    WASI        // WebAssembly System Interface
};

enum class OptimizationLevel {
    O0,         // No optimization
    O1,         // Basic optimization
    O2,         // Standard optimization
    O3          // Aggressive optimization
};

struct FyraCompileOptions {
    CompileTarget target = CompileTarget::AOT;
    OptimizationLevel opt_level = OptimizationLevel::O2;
    std::string output_file;
    bool debug_info = false;
    bool verbose = false;
    std::string triple;  // Target triple (e.g., "x86_64-pc-windows-gnu")
};

struct CompileResult {
    bool success = false;
    std::string output_file;
    std::string error_message;
    std::vector<std::string> warnings;
};

class FyraCompiler {
public:
    FyraCompiler();
    ~FyraCompiler();
    
    // Compile AST to native code or WebAssembly
    CompileResult compile_ast(std::shared_ptr<Frontend::AST::Program> program,
                             const FyraCompileOptions& options);

    // Compile LIR to native code or WebAssembly
    CompileResult compile(const LIR::LIR_Function& lir_func,
                         const FyraCompileOptions& options);

    // Compile Fyra IR Module
    CompileResult compile_module(std::shared_ptr<ir::Module> module,
                               const FyraCompileOptions& options);
    
    // Compile to AOT executable (AST path)
    CompileResult compile_ast_aot(std::shared_ptr<Frontend::AST::Program> program,
                                 const std::string& output_file,
                                 OptimizationLevel opt_level = OptimizationLevel::O2);

    // Compile to AOT executable
    CompileResult compile_aot(const LIR::LIR_Function& lir_func,
                             const std::string& output_file,
                             OptimizationLevel opt_level = OptimizationLevel::O2);
    
    // Compile to WebAssembly
    CompileResult compile_wasm(const LIR::LIR_Function& lir_func,
                              const std::string& output_file,
                              OptimizationLevel opt_level = OptimizationLevel::O2);
    
    // Compile to WASI (WebAssembly System Interface)
    CompileResult compile_wasi(const LIR::LIR_Function& lir_func,
                              const std::string& output_file,
                              OptimizationLevel opt_level = OptimizationLevel::O2);
    
    // Set debug mode
    void set_debug_mode(bool debug) { debug_mode_ = debug; }
    
    // Get last error message
    std::string get_last_error() const { return last_error_; }
    
private:
    bool debug_mode_ = false;
    std::string last_error_;
    
    // Internal conversion from LIR to Fyra IR
    std::string convert_lir_to_fyra_ir(const LIR::LIR_Function& lir_func);
    
    // Invoke Fyra compiler
    CompileResult invoke_fyra(const std::string& ir_code,
                             const FyraCompileOptions& options);
};

} // namespace LM::Backend::Fyra
