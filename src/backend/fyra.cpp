// fyra.cpp - Fyra Backend Integration Implementation

#include "fyra.hh"
#include "fyra_ir_generator.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

namespace LM::Backend::Fyra {

FyraCompiler::FyraCompiler() {
    // Initialize Fyra compiler
    // This will be expanded as Fyra integration develops
}

FyraCompiler::~FyraCompiler() {
    // Cleanup if needed
}

std::string FyraCompiler::convert_lir_to_fyra_ir(const LIR::LIR_Function& lir_func) {
    std::stringstream ir;
    
    // Convert LIR instructions to Fyra IR format
    // This is a placeholder - actual conversion will depend on Fyra's IR format
    
    ir << "// Fyra IR generated from LIR\n";
    ir << "// Function: " << lir_func.name << "\n";
    ir << "// Instructions: " << lir_func.instructions.size() << "\n\n";
    
    // Iterate through LIR instructions and convert to Fyra IR
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        const auto& inst = lir_func.instructions[i];
        
        // Convert each LIR instruction to Fyra IR
        // This is a simplified placeholder
        ir << "// [" << i << "] " << inst.to_string() << "\n";
    }
    
    return ir.str();
}

CompileResult FyraCompiler::compile(const LIR::LIR_Function& lir_func,
                                   const FyraCompileOptions& options) {
    CompileResult result;
    
    try {
        // Convert LIR to Fyra IR
        std::string fyra_ir = convert_lir_to_fyra_ir(lir_func);
        
        if (debug_mode_) {
            std::cout << "Generated Fyra IR:\n" << fyra_ir << "\n";
        }
        
        // Invoke Fyra compiler
        result = invoke_fyra(fyra_ir, options);
        
    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = std::string("Fyra compilation error: ") + e.what();
        last_error_ = result.error_message;
    }
    
    return result;
}

CompileResult FyraCompiler::compile_ir(const FyraIRFunction& ir_func,
                                      const FyraCompileOptions& options) {
    if (debug_mode_) {
        std::cout << "Generated Fyra IR:\n" << ir_func.to_ir_string() << "\n";
    }
    return invoke_fyra(ir_func.to_ir_string(), options);
}

CompileResult FyraCompiler::compile_aot(const LIR::LIR_Function& lir_func,
                                       const std::string& output_file,
                                       OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::AOT;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    
    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_ir_aot(const FyraIRFunction& ir_func,
                                          const std::string& output_file,
                                          OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::AOT;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    return compile_ir(ir_func, options);
}

CompileResult FyraCompiler::compile_wasm(const LIR::LIR_Function& lir_func,
                                        const std::string& output_file,
                                        OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASM;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    
    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_ir_wasm(const FyraIRFunction& ir_func,
                                           const std::string& output_file,
                                           OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASM;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    return compile_ir(ir_func, options);
}

CompileResult FyraCompiler::compile_wasi(const LIR::LIR_Function& lir_func,
                                        const std::string& output_file,
                                        OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASI;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    
    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_ir_wasi(const FyraIRFunction& ir_func,
                                           const std::string& output_file,
                                           OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASI;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    return compile_ir(ir_func, options);
}

CompileResult FyraCompiler::invoke_fyra(const std::string& ir_code,
                                       const FyraCompileOptions& options) {
    CompileResult result;
    
    try {
        // Create temporary IR file
        std::string temp_ir_file = "temp_fyra_ir.ll";
        std::ofstream ir_file(temp_ir_file);
        ir_file << ir_code;
        ir_file.close();
        
        // Build Fyra command line
        std::string cmd = "fyra";
        
        // Add target
        switch (options.target) {
            case CompileTarget::AOT:
                cmd += " --target aot";
                break;
            case CompileTarget::WASM:
                cmd += " --target wasm";
                break;
            case CompileTarget::WASI:
                cmd += " --target wasi";
                break;
        }
        
        // Add optimization level
        switch (options.opt_level) {
            case OptimizationLevel::O0:
                cmd += " -O0";
                break;
            case OptimizationLevel::O1:
                cmd += " -O1";
                break;
            case OptimizationLevel::O2:
                cmd += " -O2";
                break;
            case OptimizationLevel::O3:
                cmd += " -O3";
                break;
        }
        
        // Add output file
        cmd += " -o " + options.output_file;
        
        // Add debug info if requested
        if (options.debug_info) {
            cmd += " -g";
        }
        
        // Add input file
        cmd += " " + temp_ir_file;
        
        if (options.verbose) {
            std::cout << "Executing: " << cmd << "\n";
        }
        
        // Execute Fyra compiler
        int exit_code = std::system(cmd.c_str());
        
        // Clean up temporary file
        fs::remove(temp_ir_file);
        
        if (exit_code == 0) {
            result.success = true;
            result.output_file = options.output_file;
        } else {
            result.success = false;
            result.error_message = "Fyra compiler exited with code " + std::to_string(exit_code);
            last_error_ = result.error_message;
        }
        
    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = std::string("Failed to invoke Fyra: ") + e.what();
        last_error_ = result.error_message;
    }
    
    return result;
}

} // namespace LM::Backend::Fyra
