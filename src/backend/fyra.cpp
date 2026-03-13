// fyra.cpp - Fyra Backend Integration Implementation

#include "fyra.hh"
#include "fyra_ir_generator.hh"
#include "codegen/CodeGen.h"
#include "codegen/target/TargetInfo.h"
#include "codegen/target/SystemV_x64.h"
#include "codegen/execgen/elf.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

namespace LM::Backend::Fyra {

FyraCompiler::FyraCompiler() {
}

FyraCompiler::~FyraCompiler() {
}

std::string FyraCompiler::convert_lir_to_fyra_ir(const LIR::LIR_Function& lir_func, TranslationReport& report) {
    std::stringstream ir;
    ir << "// Fyra IR generated from LIR\n// Function: " << lir_func.name << "\n\n";
    return ir.str();
}

CompileResult FyraCompiler::compile_ast(std::shared_ptr<Frontend::AST::Program> program,
                                       const FyraCompileOptions& options) {
    FyraIRGenerator generator;
    auto module = generator.generate_from_ast(program);

    if (!module) {
        CompileResult result;
        result.success = false;
        result.error_message = "Failed to generate Fyra IR from AST";
        if (generator.has_errors()) {
             result.error_message += ": " + generator.get_errors()[0];
        }
        return result;
    }

    return compile_module(module, options);
}

CompileResult FyraCompiler::compile(const LIR::LIR_Function& lir_func,
                                   const FyraCompileOptions& options) {
    CompileResult result;
    result.success = false;
    result.error_message = "LIR to Fyra IR path is deprecated. Use AST to Fyra IR instead.";
    return result;
}

CompileResult FyraCompiler::compile_module(std::shared_ptr<ir::Module> module,
                                         const FyraCompileOptions& options) {
    CompileResult result;
    
    try {
        if (!module) {
            result.success = false;
            result.error_message = "Null module";
            return result;
        }

        // Use Fyra's CodeGen directly
        auto target_info = std::make_unique<codegen::target::SystemV_x64>();
        codegen::CodeGen generator(*module, std::move(target_info), nullptr);
        
        generator.emit(true);

        // Collect sections from assembler
        std::map<std::string, std::vector<uint8_t>> sections;
        sections[".text"] = generator.getAssembler().getCode();
        sections[".data"] = generator.getRodataAssembler().getCode();

        // Collect symbols
        std::vector<ElfGenerator::Symbol> symbols;
        for (const auto& sym : generator.getSymbols()) {
            ElfGenerator::Symbol elf_sym;
            elf_sym.name = sym.name;
            elf_sym.value = sym.value;
            elf_sym.size = sym.size;
            elf_sym.type = sym.type;
            elf_sym.binding = sym.binding;
            elf_sym.sectionName = sym.sectionName;
            symbols.push_back(elf_sym);
        }

        // Collect relocations
        std::vector<ElfGenerator::Relocation> relocs;
        for (const auto& reloc : generator.getRelocations()) {
            ElfGenerator::Relocation elf_reloc;
            elf_reloc.offset = reloc.offset;
            elf_reloc.type = reloc.type;
            elf_reloc.addend = reloc.addend;
            elf_reloc.symbolName = reloc.symbolName;
            elf_reloc.sectionName = reloc.sectionName;
            relocs.push_back(elf_reloc);
        }

        ElfGenerator elf_gen(options.output_file);
        // Entry point should be _start, which is emitted by targetInfo->emitStartFunction
        elf_gen.setEntryPointName("_start");
        if (elf_gen.generateFromCode(sections, symbols, relocs, options.output_file)) {
            result.success = true;
            result.output_file = options.output_file;
            return result;
        } else {
            result.success = false;
            result.error_message = "ELF generation failed: " + elf_gen.getLastError();
            return result;
        }
        
    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = std::string("Fyra compilation error: ") + e.what();
        last_error_ = result.error_message;
    }
    
    return result;
}

CompileResult FyraCompiler::compile_ast_aot(std::shared_ptr<Frontend::AST::Program> program,
                                           const std::string& output_file,
                                           OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::AOT;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;

    return compile_ast(program, options);
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

CompileResult FyraCompiler::invoke_fyra(const std::string& ir_code,
                                       const FyraCompileOptions& options) {
    CompileResult result;
    return result;
}

} // namespace LM::Backend::Fyra
