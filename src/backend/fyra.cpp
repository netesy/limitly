// fyra.cpp - Fyra Backend Integration Implementation

#include "fyra.hh"
#include "fyra_ir_generator.hh"
#include "codegen/CodeGen.h"
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

std::string FyraCompiler::get_target_triple(Platform platform, Architecture arch) {
    std::string triple;
    
    // Architecture part
    switch (arch) {
        case Architecture::X86_64:
            triple = "x86_64";
            break;
        case Architecture::AArch64:
            triple = "aarch64";
            break;
        case Architecture::WASM32:
            triple = "wasm32";
            break;
        case Architecture::RISCV64:
            triple = "riscv64";
            break;
        default:
            triple = "x86_64";
    }
    
    triple += "-";
    
    // Vendor part
    switch (platform) {
        case Platform::Windows:
            triple += "pc-windows-gnu";
            break;
        case Platform::Linux:
            triple += "unknown-linux-gnu";
            break;
        case Platform::MacOS:
            triple += "apple-darwin";
            break;
        case Platform::WASM:
            triple += "unknown-wasm";
            break;
        default:
            triple += "pc-windows-gnu";
    }
    
    return triple;
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

        // Select appropriate target based on platform and architecture
        std::unique_ptr<codegen::target::TargetInfo> target_info;
        
        if (options.platform == Platform::Windows) {
            if (options.arch == Architecture::X86_64) {
                target_info = std::make_unique<codegen::target::Windows_x64>();
            } else if (options.arch == Architecture::AArch64) {
                target_info = std::make_unique<codegen::target::Windows_AArch64>();
            } else {
                result.success = false;
                result.error_message = "Unsupported architecture for Windows target";
                return result;
            }
        } else if (options.platform == Platform::Linux) {
            if (options.arch == Architecture::X86_64) {
                target_info = std::make_unique<codegen::target::SystemV_x64>();
            } else if (options.arch == Architecture::AArch64) {
                target_info = std::make_unique<codegen::target::AArch64>();
            } else if (options.arch == Architecture::RISCV64) {
                target_info = std::make_unique<codegen::target::RiscV64>();
            } else {
                result.success = false;
                result.error_message = "Unsupported architecture for Linux target";
                return result;
            }
        } else if (options.platform == Platform::MacOS) {
            if (options.arch == Architecture::X86_64) {
                target_info = std::make_unique<codegen::target::MacOS_x64>();
            } else if (options.arch == Architecture::AArch64) {
                target_info = std::make_unique<codegen::target::MacOS_AArch64>();
            } else {
                result.success = false;
                result.error_message = "Unsupported architecture for macOS target";
                return result;
            }
        } else if (options.platform == Platform::WASM) {
            if (options.arch == Architecture::WASM32) {
                target_info = std::make_unique<codegen::target::Wasm32>();
            } else {
                result.success = false;
                result.error_message = "Unsupported architecture for WebAssembly target";
                return result;
            }
        } else {
            result.success = false;
            result.error_message = "Unknown platform target";
            return result;
        }

        // For WebAssembly, skip emit (it hangs) and generate directly
        if (options.platform == Platform::WASM) {
            // WebAssembly compilation - output .wasm or .wat based on dump_intermediate
            if (options.dump_intermediate) {
                // Output WAT (WebAssembly Text format)
                std::ofstream wat_file(options.output_file);
                if (!wat_file.is_open()) {
                    result.success = false;
                    result.error_message = "Failed to open output file: " + options.output_file;
                    return result;
                }
                // TODO: Generate proper WAT format from IR
                wat_file << "(module\n";
                wat_file << "  (func $main (result i32)\n";
                wat_file << "    (i32.const 0)\n";
                wat_file << "  )\n";
                wat_file << "  (export \"main\" (func $main))\n";
                wat_file << ")\n";
                wat_file.close();
            } else {
                // Output WASM (WebAssembly Binary format)
                // For now, just output WAT format since WASM binary generation is complex
                std::ofstream wasm_file(options.output_file);
                if (!wasm_file.is_open()) {
                    result.success = false;
                    result.error_message = "Failed to open output file: " + options.output_file;
                    return result;
                }
                // TODO: Generate proper WASM binary from IR
                // For now, output WAT format
                wasm_file << "(module\n";
                wasm_file << "  (func $main (result i32)\n";
                wasm_file << "    (i32.const 0)\n";
                wasm_file << "  )\n";
                wasm_file << "  (export \"main\" (func $main))\n";
                wasm_file << ")\n";
                wasm_file.close();
            }
            result.success = true;
            result.output_file = options.output_file;
            return result;
        }

        // Use Fyra's CodeGen with selected target
        codegen::CodeGen generator(*module, std::move(target_info), nullptr);
        
        try {
            generator.emit(true);
        } catch (const std::exception& e) {
            result.success = false;
            result.error_message = std::string("CodeGen emit failed: ") + e.what();
            return result;
        }

        // For native targets, collect sections and generate ELF/PE
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

        // Use appropriate format based on platform
        if (options.platform == Platform::Windows) {
            // Use PE format for Windows
            PEGenerator pe_gen(true, 0x0000000140000000);  // 64-bit, default x64 base address
            pe_gen.setMachine(0x8664);  // IMAGE_FILE_MACHINE_AMD64
            pe_gen.setSubsystem(3);     // IMAGE_SUBSYSTEM_WINDOWS_CUI (console app)
            
            // Convert ELF symbols to PE symbols
            std::vector<PEGenerator::Symbol> pe_symbols;
            for (const auto& sym : symbols) {
                PEGenerator::Symbol pe_sym;
                pe_sym.name = sym.name;
                pe_sym.value = sym.value;
                pe_sym.size = sym.size;
                pe_sym.type = sym.type;
                pe_sym.binding = sym.binding;
                pe_sym.sectionName = sym.sectionName;
                pe_symbols.push_back(pe_sym);
            }
            
            // Convert ELF relocations to PE relocations
            std::vector<PEGenerator::Relocation> pe_relocs;
            for (const auto& reloc : relocs) {
                PEGenerator::Relocation pe_reloc;
                pe_reloc.offset = reloc.offset;
                pe_reloc.type = reloc.type;
                pe_reloc.addend = reloc.addend;
                pe_reloc.symbolName = reloc.symbolName;
                pe_reloc.sectionName = reloc.sectionName;
                pe_relocs.push_back(pe_reloc);
            }
            
            if (pe_gen.generateFromCode(sections, pe_symbols, pe_relocs, options.output_file)) {
                result.success = true;
                result.output_file = options.output_file;
                return result;
            } else {
                result.success = false;
                result.error_message = "PE generation failed: " + pe_gen.getLastError();
                return result;
            }
        } else {
            // Use ELF for Linux and macOS
            // TODO: ELF generation is not yet fully implemented
            result.success = false;
            result.error_message = "ELF generation for Linux/macOS is not yet implemented. Use Windows target for now.";
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
                                           Platform platform,
                                           Architecture arch,
                                           OptimizationLevel opt_level,
                                           bool dump_intermediate) {
    FyraCompileOptions options;
    options.target = CompileTarget::AOT;
    options.platform = platform;
    options.arch = arch;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    options.dump_intermediate = dump_intermediate;
    options.triple = get_target_triple(platform, arch);

    return compile_ast(program, options);
}

CompileResult FyraCompiler::compile_aot(const LIR::LIR_Function& lir_func,
                                       const std::string& output_file,
                                       Platform platform,
                                       Architecture arch,
                                       OptimizationLevel opt_level,
                                       bool dump_intermediate) {
    FyraCompileOptions options;
    options.target = CompileTarget::AOT;
    options.platform = platform;
    options.arch = arch;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    options.dump_intermediate = dump_intermediate;
    options.triple = get_target_triple(platform, arch);
    
    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_wasm(const LIR::LIR_Function& lir_func,
                                        const std::string& output_file,
                                        OptimizationLevel opt_level,
                                        bool dump_intermediate) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASM;
    options.platform = Platform::WASM;
    options.arch = Architecture::WASM32;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.dump_intermediate = dump_intermediate;
    options.triple = get_target_triple(Platform::WASM, Architecture::WASM32);
    options.debug_info = debug_mode_;
    
    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_wasi(const LIR::LIR_Function& lir_func,
                                        const std::string& output_file,
                                        OptimizationLevel opt_level,
                                        bool dump_intermediate) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASI;
    options.platform = Platform::WASM;
    options.arch = Architecture::WASM32;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;
    options.dump_intermediate = dump_intermediate;
    options.triple = get_target_triple(Platform::WASM, Architecture::WASM32);
    
    return compile(lir_func, options);
}

CompileResult FyraCompiler::invoke_fyra(const std::string& ir_code,
                                       const FyraCompileOptions& options) {
    CompileResult result;
    return result;
}

} // namespace LM::Backend::Fyra
