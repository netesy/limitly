// fyra.cpp - Fyra Backend Integration Implementation

#include "fyra.hh"
#include "fyra_ir_generator.hh"
#include "builder.hh"
#include "codegen/CodeGen.h"
#include "target/core/TargetResolver.h"
#include "target/core/TargetInfo.h"
#include "target/core/TargetDescriptor.h"
#include "target/artifact/executable/elf.hh"
#include "target/artifact/executable/pe.hh"
#include "ir/IRContext.h"
#include "ir/Module.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <optional>

namespace LM::Backend::Fyra {

FyraCompiler::FyraCompiler() : context_(std::make_shared<ir::IRContext>()) {
}

FyraCompiler::~FyraCompiler() {
}

std::string FyraCompiler::get_target_triple(Platform platform, Architecture arch) {
    std::string triple;
    switch (arch) {
        case Architecture::X86_64: triple = "x86_64"; break;
        case Architecture::AArch64: triple = "aarch64"; break;
        case Architecture::WASM32: triple = "wasm32"; break;
        case Architecture::RISCV64: triple = "riscv64"; break;
        default: triple = "unknown"; break;
    }
    triple += "-";
    switch (platform) {
        case Platform::Windows: triple += "pc-windows-msvc"; break;
        case Platform::Linux: triple += "unknown-linux-gnu"; break;
        case Platform::MacOS: triple += "apple-macosx"; break;
        case Platform::WASM: triple += "unknown-unknown"; break;
        default: triple += "unknown-unknown"; break;
    }
    return triple;
}

CompileResult FyraCompiler::compile_ast(std::shared_ptr<Frontend::AST::Program> program,
                                       const FyraCompileOptions& options) {
    FyraIRGenerator generator;
    auto module = generator.generate_from_ast(program);
    if (generator.has_errors()) {
        CompileResult result;
        result.success = false;
        result.error_message = "AST to Fyra IR generation failed: " + generator.get_errors().front();
        return result;
    }
    return compile_module(module, options);
}

CompileResult FyraCompiler::compile(const LIR::LIR_Function& lir_func,
                                   const FyraCompileOptions& options) {
    LIRToFyraIRBuilder builder(context_);
    auto module = builder.build(lir_func);
    if (builder.has_errors()) {
        CompileResult result;
        result.success = false;
        result.error_message = "LIR to Fyra IR lowering failed: " + builder.get_errors().front();
        return result;
    }
    return compile_module(module, options);
}

CompileResult FyraCompiler::compile_module(std::shared_ptr<ir::Module> module,
                                         const FyraCompileOptions& options) {
    CompileResult result;
    try {
        // Map platform/arch to target resolver
        ::target::Arch target_arch;
        ::target::OS target_os;

        switch (options.arch) {
            case Architecture::X86_64: target_arch = ::target::Arch::X64; break;
            case Architecture::AArch64: target_arch = ::target::Arch::AArch64; break;
            case Architecture::WASM32: target_arch = ::target::Arch::WASM32; break;
            case Architecture::RISCV64: target_arch = ::target::Arch::RISCV64; break;
            default: target_arch = ::target::Arch::X64; break;
        }

        switch (options.platform) {
            case Platform::Windows: target_os = ::target::OS::Windows; break;
            case Platform::Linux: target_os = ::target::OS::Linux; break;
            case Platform::MacOS: target_os = ::target::OS::MacOS; break;
            case Platform::WASM: target_os = ::target::OS::WASI; break;
            default: target_os = ::target::OS::Linux; break;
        }

        std::unique_ptr<::codegen::target::TargetInfo> targetInfo = 
            ::codegen::target::TargetResolver::resolve({target_arch, target_os, std::nullopt});

        if (!targetInfo) {
            result.success = false;
            result.error_message = "Unsupported target platform or architecture";
            return result;
        }

        ::codegen::CodeGen generator(*module, std::move(targetInfo), nullptr);
        generator.emit(true);

        std::map<std::string, std::vector<uint8_t>> sections;
        sections[".text"] = generator.getAssembler().getCode();
        sections[".data"] = generator.getRodataAssembler().getCode();

        if (options.platform == Platform::Windows) {
            PEGenerator pe_gen(true); // 64-bit
            std::vector<PEGenerator::Symbol> symbols;
            for (const auto& sym : generator.getSymbols()) {
                symbols.push_back({sym.name, sym.value, sym.size, static_cast<uint8_t>(sym.type), static_cast<uint8_t>(sym.binding), sym.sectionName});
            }
            std::vector<PEGenerator::Relocation> relocs;
            for (const auto& reloc : generator.getRelocations()) {
                relocs.push_back({reloc.offset, reloc.type, reloc.addend, reloc.symbolName, reloc.sectionName});
            }
            if (!pe_gen.generateFromCode(sections, symbols, relocs, options.output_file)) {
                result.success = false;
                result.error_message = "PE generation failed: " + pe_gen.getLastError();
                return result;
            }
        } else if (options.platform == Platform::Linux) {
            ElfGenerator elf_gen(options.output_file);
            elf_gen.setMachine(62); // EM_X86_64
            elf_gen.setBaseAddress(0x400000);

            std::vector<ElfGenerator::Symbol> symbols;
            for (const auto& sym : generator.getSymbols()) {
                symbols.push_back({sym.name, sym.value, sym.size, static_cast<uint8_t>(sym.type), static_cast<uint8_t>(sym.binding), sym.sectionName});
            }

            std::vector<ElfGenerator::Relocation> relocs;
            for (const auto& reloc : generator.getRelocations()) {
                relocs.push_back({reloc.offset, reloc.type, reloc.addend, reloc.symbolName, reloc.sectionName});
            }

            if (!elf_gen.generateFromCode(sections, symbols, relocs, options.output_file)) {
                result.success = false;
                result.error_message = "ELF generation failed: " + elf_gen.getLastError();
                return result;
            }
        } else {
            result.success = false;
            result.error_message = "Unsupported platform for AOT compilation";
            return result;
        }

        result.success = true;
        result.output_file = options.output_file;
        return result;
    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = std::string("Fyra compilation error: ") + e.what();
        last_error_ = result.error_message;
    }
    return result;
}

CompileResult FyraCompiler::compile_ast_aot(std::shared_ptr<Frontend::AST::Program> program,
                                           const std::string& output_file, Platform platform,
                                           Architecture arch, OptimizationLevel opt_level, bool dump_intermediate) {
    FyraCompileOptions options;
    options.target = CompileTarget::AOT; options.platform = platform; options.arch = arch;
    options.output_file = output_file; options.opt_level = opt_level; options.debug_info = debug_mode_;
    options.dump_intermediate = dump_intermediate; options.triple = get_target_triple(platform, arch);
    return compile_ast(program, options);
}

CompileResult FyraCompiler::compile_aot(const LIR::LIR_Function& lir_func,
                                       const std::string& output_file, Platform platform,
                                       Architecture arch, OptimizationLevel opt_level, bool dump_intermediate) {
    FyraCompileOptions options;
    options.target = CompileTarget::AOT; options.platform = platform; options.arch = arch;
    options.output_file = output_file; options.opt_level = opt_level; options.debug_info = debug_mode_;
    options.dump_intermediate = dump_intermediate; options.triple = get_target_triple(platform, arch);
    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_wasm(const LIR::LIR_Function& lir_func,
                                        const std::string& output_file, OptimizationLevel opt_level, bool dump_intermediate) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASM; options.platform = Platform::WASM; options.arch = Architecture::WASM32;
    options.output_file = output_file; options.opt_level = opt_level; options.dump_intermediate = dump_intermediate;
    options.triple = get_target_triple(Platform::WASM, Architecture::WASM32); options.debug_info = debug_mode_;
    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_wasi(const LIR::LIR_Function& lir_func,
                                        const std::string& output_file, OptimizationLevel opt_level, bool dump_intermediate) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASI; options.platform = Platform::WASM; options.arch = Architecture::WASM32;
    options.output_file = output_file; options.opt_level = opt_level; options.debug_info = debug_mode_;
    options.dump_intermediate = dump_intermediate; options.triple = get_target_triple(Platform::WASM, Architecture::WASM32);
    return compile(lir_func, options);
}

CompileResult FyraCompiler::invoke_fyra(const std::string& ir_code, const FyraCompileOptions& options) {
    return CompileResult();
}

} // namespace LM::Backend::Fyra
