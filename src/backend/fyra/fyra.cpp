// fyra.cpp - Fyra Backend Integration Implementation

#include "fyra.hh"
#include "fyra_ir_generator.hh"
#include "builder.hh"
#include "codegen/CodeGen.h"
#include "codegen/InstructionFusion.h"
#include "codegen/target/TargetInfo.h"
#include "codegen/target/SystemV_x64.h"
#include "codegen/target/Windows_x64.h"
#include "codegen/target/Windows_AArch64.h"
#include "codegen/target/MacOS_x64.h"
#include "codegen/target/MacOS_AArch64.h"
#include "codegen/target/AArch64.h"
#include "codegen/target/RiscV64.h"
#include "codegen/target/Wasm32.h"
#include "codegen/execgen/elf.hh"
#include "codegen/execgen/pe.hh"
#include "codegen/execgen/macho.hh"
#include "ir/IRContext.h"
#include "ir/Module.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

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
        std::unique_ptr<codegen::target::TargetInfo> targetInfo;
        if (options.platform == Platform::Windows) {
            targetInfo = std::make_unique<codegen::target::Windows_x64>();
        } else if (options.platform == Platform::Linux) {
            targetInfo = std::make_unique<codegen::target::SystemV_x64>();
        } else if (options.platform == Platform::MacOS) {
            if (options.arch == Architecture::AArch64) {
                targetInfo = std::make_unique<codegen::target::MacOS_AArch64>();
            } else {
                targetInfo = std::make_unique<codegen::target::MacOS_x64>();
            }
        } else if (options.platform == Platform::WASM) {
            targetInfo = std::make_unique<codegen::target::Wasm32>();
        }

        if (!targetInfo) {
            result.success = false;
            result.error_message = "Unsupported target platform or architecture";
            return result;
        }

        codegen::CodeGen generator(*module, std::move(targetInfo));
        switch (options.opt_level) {
            case OptimizationLevel::O0: generator.fusionCoordinator->setOptimizationLevel(0); break;
            case OptimizationLevel::O1: generator.fusionCoordinator->setOptimizationLevel(1); break;
            case OptimizationLevel::O2: generator.fusionCoordinator->setOptimizationLevel(2); break;
            case OptimizationLevel::O3: generator.fusionCoordinator->setOptimizationLevel(3); break;
        }
        generator.emit(true);

        std::map<std::string, std::vector<uint8_t>> sections;
        sections[".text"] = generator.getAssembler().getCode();
        sections[".data"] = generator.getRodataAssembler().getCode();

        std::vector<ElfGenerator::Symbol> symbols;
        for (const auto& sym : generator.getSymbols()) {
            ElfGenerator::Symbol elf_sym;
            elf_sym.name = sym.name; elf_sym.value = sym.value; elf_sym.size = sym.size;
            elf_sym.type = sym.type; elf_sym.binding = sym.binding; elf_sym.sectionName = sym.sectionName;
            symbols.push_back(elf_sym);
        }

        std::vector<ElfGenerator::Relocation> relocs;
        for (const auto& reloc : generator.getRelocations()) {
            ElfGenerator::Relocation elf_reloc;
            elf_reloc.offset = reloc.offset; elf_reloc.type = reloc.type; elf_reloc.addend = reloc.addend;
            elf_reloc.symbolName = reloc.symbolName; elf_reloc.sectionName = reloc.sectionName;
            relocs.push_back(elf_reloc);
        }

        if (options.platform == Platform::Windows) {
            PEGenerator pe_gen(true, 0x0000000140000000);
            pe_gen.setMachine(0x8664); pe_gen.setSubsystem(3);
            std::vector<PEGenerator::Symbol> pe_symbols;
            for (const auto& sym : symbols) {
                PEGenerator::Symbol pe_sym;
                pe_sym.name = sym.name; pe_sym.value = sym.value; pe_sym.size = sym.size;
                pe_sym.type = sym.type; pe_sym.binding = sym.binding; pe_sym.sectionName = sym.sectionName;
                pe_symbols.push_back(pe_sym);
            }
            std::vector<PEGenerator::Relocation> pe_relocs;
            for (const auto& reloc : relocs) {
                PEGenerator::Relocation pe_reloc;
                pe_reloc.offset = reloc.offset; pe_reloc.type = reloc.type; pe_reloc.addend = reloc.addend;
                pe_reloc.symbolName = reloc.symbolName; pe_reloc.sectionName = reloc.sectionName;
                pe_relocs.push_back(pe_reloc);
            }
            if (pe_gen.generateFromCode(sections, pe_symbols, pe_relocs, options.output_file)) {
                result.success = true; result.output_file = options.output_file; return result;
            } else {
                result.success = false; result.error_message = "PE generation failed: " + pe_gen.getLastError(); return result;
            }
        } else if (options.platform == Platform::Linux) {
            ElfGenerator elf_gen(options.output_file, true);
            elf_gen.setEntryPointName("_start");
            if (options.arch == Architecture::X86_64) elf_gen.setMachine(62);
            else if (options.arch == Architecture::AArch64) elf_gen.setMachine(183);
            else if (options.arch == Architecture::RISCV64) elf_gen.setMachine(243);
            if (elf_gen.generateFromCode(sections, symbols, relocs, options.output_file)) {
                result.success = true; result.output_file = options.output_file; return result;
            } else {
                result.success = false; result.error_message = "ELF generation failed: " + elf_gen.getLastError(); return result;
            }
        } else if (options.platform == Platform::MacOS) {
            MachOGenerator macho_gen(options.output_file);
            if (options.arch == Architecture::X86_64) macho_gen.setCpuType(0x01000007);
            else if (options.arch == Architecture::AArch64) macho_gen.setCpuType(0x0100000C);
            std::vector<MachOGenerator::Symbol> macho_symbols;
            for (const auto& sym : symbols) {
                MachOGenerator::Symbol macho_sym;
                macho_sym.name = sym.name; macho_sym.value = sym.value; macho_sym.size = sym.size;
                macho_sym.type = sym.type; macho_sym.binding = sym.binding; macho_sym.sectionName = sym.sectionName;
                macho_symbols.push_back(macho_sym);
            }
            std::vector<MachOGenerator::Relocation> macho_relocs;
            for (const auto& reloc : relocs) {
                MachOGenerator::Relocation macho_reloc;
                macho_reloc.offset = reloc.offset; macho_reloc.type = reloc.type; macho_reloc.addend = reloc.addend;
                macho_reloc.symbolName = reloc.symbolName; macho_reloc.sectionName = reloc.sectionName;
                macho_relocs.push_back(macho_reloc);
            }
            if (macho_gen.generateFromCode(sections, macho_symbols, macho_relocs, options.output_file)) {
                result.success = true; result.output_file = options.output_file; return result;
            } else {
                result.success = false; result.error_message = "Mach-O generation failed: " + macho_gen.getLastError(); return result;
            }
        } else {
            result.success = false; result.error_message = "Unsupported platform for AOT compilation"; return result;
        }
    } catch (const std::exception& e) {
        result.success = false; result.error_message = std::string("Fyra compilation error: ") + e.what(); last_error_ = result.error_message;
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
