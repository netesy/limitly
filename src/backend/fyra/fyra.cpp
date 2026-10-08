// fyra.cpp - Fyra Backend Integration Implementation

#include "fyra.hh"
#include <chrono>
#include "fyra_ir_generator.hh"
#include "builder.hh"
#include "backend/native/emitter.hh"
#include "fyra/BackendBuilder.h"
#include "target/core/TargetDescriptor.h"
#include "ir/IRContext.h"
#include "ir/Module.h"
#include "frontend/module_manager.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <optional>
#include <filesystem>

namespace LM::Backend::Fyra {

FyraCompiler::FyraCompiler() : context_(std::make_shared<ir::IRContext>()) {
}

FyraCompiler::~FyraCompiler() {
}

std::string FyraCompiler::get_target_triple(Platform platform, Architecture arch, ArtifactKind kind) {
    std::string arch_str;
    switch (arch) {
        case Architecture::X86_64: arch_str = "x64"; break;
        case Architecture::AArch64: arch_str = "aarch64"; break;
        case Architecture::WASM32: arch_str = "wasm32"; break;
        case Architecture::RISCV64: arch_str = "riscv64"; break;
        default: arch_str = "x64"; break;
    }
    std::string platform_str;
    switch (platform) {
        case Platform::Windows: platform_str = "windows"; break;
        case Platform::Linux: platform_str = "linux"; break;
        case Platform::MacOS: platform_str = "macos"; break;
        case Platform::WASM: platform_str = "wasi"; break;
        default: platform_str = "linux"; break;
    }
    std::string artifact_str = "bin";
    if (platform == Platform::WASM || arch == Architecture::WASM32) {
        artifact_str = "wasm";
    } else if (kind == ArtifactKind::StaticLibrary) {
        artifact_str = "static";
    } else if (kind == ArtifactKind::SharedLibrary) {
        artifact_str = "shared";
    }
    return arch_str + "-" + platform_str + "-" + artifact_str;
}

static std::string resolve_target_triple(const FyraCompileOptions& options) {
    if (!options.triple.empty()) {
        auto desc = target::TargetDescriptor::fromString(options.triple);
        if (desc.has_value()) {
            if (options.artifact_kind == ArtifactKind::StaticLibrary) {
                desc->artifact = target::Artifact::StaticLibrary;
            } else if (options.artifact_kind == ArtifactKind::SharedLibrary) {
                desc->artifact = target::Artifact::SharedLibrary;
            }
            return desc->toString();
        }
        // Normalize common GNU/LLVM triples
        std::string arch = "x64";
        if (options.triple.find("aarch64") != std::string::npos || options.triple.find("arm64") != std::string::npos) arch = "aarch64";
        else if (options.triple.find("wasm") != std::string::npos) arch = "wasm32";
        else if (options.triple.find("riscv") != std::string::npos) arch = "riscv64";

        std::string os = "linux";
        if (options.triple.find("windows") != std::string::npos || options.triple.find("win32") != std::string::npos) os = "windows";
        else if (options.triple.find("darwin") != std::string::npos || options.triple.find("macos") != std::string::npos || options.triple.find("apple") != std::string::npos) os = "macos";
        else if (options.triple.find("wasi") != std::string::npos) os = "wasi";

        std::string artifact = (os == "wasi" || arch == "wasm32") ? "wasm" : "bin";
        if (options.artifact_kind == ArtifactKind::StaticLibrary) artifact = "static";
        else if (options.artifact_kind == ArtifactKind::SharedLibrary) artifact = "shared";
        return arch + "-" + os + "-" + artifact;
    }
    return FyraCompiler::get_target_triple(options.platform, options.arch, options.artifact_kind);
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
#if defined(__linux__) && defined(__x86_64__)
    // Shared VM modules use the canonical tagged object ABI. Lower their LIR
    // directly through the host compiler, keeping control flow native while
    // sharing the VM runtime rather than maintaining a second heap layout.
    if (options.artifact_kind == ArtifactKind::SharedLibrary &&
        options.platform == Platform::Linux && options.arch == Architecture::X86_64 &&
        !options.exported_module.empty() && options.triple.empty()) {
        CompileResult result;
        result.success = Native::emit_shared_module(lir_func, options.exported_module,
            options.output_file, static_cast<int>(options.opt_level), result.error_message);
        return result;
    }
#endif
    LIRToFyraIRBuilder builder(context_);
    auto module = builder.build(lir_func, options.exported_module);
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
    if (!module) {
        result.success = false;
        result.error_message = "Null module provided for compilation";
        last_error_ = result.error_message;
        return result;
    }

    try {
        ::fyra::BackendBuilder backend(*module);

        std::string target_triple = resolve_target_triple(options);
        backend.target(target_triple);
        backend.validate(false);

        ::fyra::OptimizationLevel opt_level = ::fyra::OptimizationLevel::O2;
        switch (options.opt_level) {
            case OptimizationLevel::O0: opt_level = ::fyra::OptimizationLevel::O0; break;
            case OptimizationLevel::O1: opt_level = ::fyra::OptimizationLevel::O1; break;
            case OptimizationLevel::O2: opt_level = ::fyra::OptimizationLevel::O2; break;
            case OptimizationLevel::O3: opt_level = ::fyra::OptimizationLevel::O2; break;
        }
        backend.optimize(opt_level);

        // Automatically link discovered precompiled static libraries
        auto all_mods = LM::Frontend::ModuleManager::getInstance().get_all_modules();
        for (const auto& [mname, mptr] : all_mods) {
            LM::Frontend::CompiledModuleMeta meta;
            if (LM::Frontend::ModuleManager::getInstance().find_compiled_module(mname, "", "static", meta)) {
                if (std::filesystem::exists(meta.artifact_path)) {
                    backend.addStaticLibrary(meta.artifact_path);
                }
            }
        }

        bool is_wasm = (options.target == CompileTarget::WASM || options.target == CompileTarget::WASI ||
                        options.arch == Architecture::WASM32 || options.platform == Platform::WASM ||
                        target_triple.find("wasm") != std::string::npos);

        if (options.platform == Platform::Windows || target_triple.find("windows") != std::string::npos || target_triple.find("win") != std::string::npos) {
            backend.importSymbol("ExitProcess", "kernel32.dll");
            backend.importSymbol("VirtualAlloc", "kernel32.dll");
            backend.importSymbol("VirtualFree", "kernel32.dll");
            backend.importSymbol("VirtualProtect", "kernel32.dll");
            backend.importSymbol("GetStdHandle", "kernel32.dll");
            backend.importSymbol("WriteFile", "kernel32.dll");
            backend.importSymbol("ReadFile", "kernel32.dll");
            backend.importSymbol("Sleep", "kernel32.dll");
            backend.importSymbol("CreateProcessA", "kernel32.dll");
            backend.importSymbol("GetCommandLineA", "kernel32.dll");
            backend.importSymbol("GetCurrentProcessId", "kernel32.dll");
            backend.importSymbol("MapViewOfFile", "kernel32.dll");
            backend.importSymbol("CreateThread", "kernel32.dll");
            backend.importSymbol("WaitForSingleObject", "kernel32.dll");
            backend.importSymbol("CloseHandle", "kernel32.dll");
        }

        if (options.dump_intermediate) {
            if (is_wasm) {
                backend.emitWAT(options.output_file + ".wat");
            } else {
                backend.emitAssembly(options.output_file + ".s");
            }
        }

        ::fyra::BuildResult build_res;
        if (is_wasm) {
            if (options.artifact_kind == ArtifactKind::Assembly) {
                build_res = backend.emitWAT(options.output_file);
            } else {
                build_res = backend.emitWasm(options.output_file);
            }
        } else {
            switch (options.artifact_kind) {
                case ArtifactKind::Object:
                    build_res = backend.emitObject(options.output_file);
                    break;
                case ArtifactKind::StaticLibrary:
                    build_res = backend.emitStaticLibrary(options.output_file);
                    break;
                case ArtifactKind::SharedLibrary:
#if defined(__linux__)
                    if (options.arch == Architecture::X86_64 && options.platform == Platform::Linux) {
                        // Use the host linker for ELF shared objects. Its program
                        // headers explicitly declare a non-executable stack, unlike
                        // the raw backend DSO writer, which recent loaders reject.
                        const auto temporary = options.output_file + ".lymar-" +
                            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".s";
                        build_res = backend.emitAssembly(temporary);
                        if (build_res.success) {
                            auto quote = [](const std::string& path) {
                                std::string result = "'";
                                for (char c : path) result += c == '\'' ? "'\\''" : std::string(1, c);
                                return result + "'";
                            };
                            const std::string command = "cc -shared -Wl,-z,noexecstack " + quote(temporary) +
                                " -o " + quote(options.output_file);
                            if (std::system(command.c_str()) != 0) {
                                build_res.success = false;
                                build_res.errors.push_back("Host linker failed to produce the shared library");
                            }
                        }
                        std::filesystem::remove(temporary);
                    } else
#endif
                    build_res = backend.emitSharedLibrary(options.output_file);
                    break;
                case ArtifactKind::Assembly:
                    build_res = backend.emitAssembly(options.output_file);
                    break;
                case ArtifactKind::Executable:
                default:
#if defined(__linux__) && defined(__x86_64__)
                    if (options.arch == Architecture::X86_64 && options.platform == Platform::Linux) {
                        // Fyra emits the program's machine code; the host linker
                        // supplies the private ownership runtime and normal C++
                        // process teardown, rather than embedding a VM executor.
                        const auto temporary = options.output_file + ".lymar-" +
                            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".o";
                        build_res = backend.emitObject(temporary);
                        if (build_res.success) {
                            auto quote = [](const std::string& value) {
                                std::string result = "'";
                                for (char c : value) result += c == '\'' ? "'\\''" : std::string(1, c);
                                return result + "'";
                            };
                            auto binary = std::filesystem::read_symlink("/proc/self/exe");
                            const char* runtime_override = std::getenv("LYMAR_AOT_RUNTIME");
                            auto runtime = runtime_override && *runtime_override
                                ? std::filesystem::path(runtime_override)
                                : binary.parent_path() / "liblymar_aot.a";
                            const char* configured = std::getenv("LYMAR_AOT_CXX");
                            std::string command = quote(configured && *configured ? configured : "g++") +
                                " -no-pie -Wl,-z,noexecstack " + quote(temporary);
                            for (const auto& [name, imported] : all_mods) {
                                LM::Frontend::CompiledModuleMeta meta;
                                if (LM::Frontend::ModuleManager::getInstance().find_compiled_module(name, "", "static", meta)
                                    && std::filesystem::exists(meta.artifact_path)) command += " " + quote(meta.artifact_path);
                            }
                            command += " " + quote(runtime.string()) + " -o " + quote(options.output_file);
                            if (!std::filesystem::exists(runtime) || std::system(command.c_str()) != 0) {
                                build_res.success = false;
                                build_res.errors.push_back("Host linker failed to link the standalone AOT ownership runtime: " + runtime.string());
                            }
                        }
                        std::filesystem::remove(temporary);
                    } else
#endif
                    {
                        if (module->getFunction("lymar_aot_call_enter")) {
                            build_res.success = false;
                            build_res.errors.push_back("Standalone region runtime linking is supported on Linux x86_64; emit an object/static library and link a target-built liblymar_aot.a for other targets");
                        } else build_res = backend.emitExecutable(options.output_file);
                    }
                    break;
            }
        }

        if (!build_res.success) {
            result.success = false;
            std::string err_msg;
            for (const auto& err : build_res.errors) {
                if (!err_msg.empty()) err_msg += "; ";
                err_msg += err;
            }
            if (err_msg.empty()) {
                err_msg = "Fyra compilation failed";
            }
            result.error_message = err_msg;
            result.warnings = build_res.warnings;
            last_error_ = result.error_message;
            return result;
        }

        result.success = true;
        result.output_file = options.output_file;
        result.warnings = build_res.warnings;
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
