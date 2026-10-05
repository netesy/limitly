#include "lymar.hh"
#include "frontend/module_manager.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

void printUsage(const char* programName) {
    std::cout << "Limit Programming Language\n";
    std::cout << "Usage:\n";
    std::cout << "\n  Execution (Register VM):\n";
    std::cout << "    " << programName << " run [options] <source_file>\n";
    std::cout << "      Options:\n";
    std::cout << "        -I <include_dir>      Add directory to module search path\n";
    std::cout << "        -debug                Enable debug output\n";
    std::cout << "        --verify=strict       Reject unproved contracts/refinements\n";
    std::cout << "        --verify=hybrid       Keep runtime checks for unknown proofs (default)\n";
    std::cout << "\n  Compilation (AOT/WASM):\n";
#ifdef FYRA_AVAILABLE
    std::cout << "    " << programName << " build [options] <source_file>\n";
    std::cout << "      Options:\n";
    std::cout << "        -I <include_dir>      Add directory to module search path\n";
    std::cout << "        -target <target>      Target platform (windows, linux, macos, wasm)\n";
    std::cout << "        -o <output>           Output file name\n";
    std::cout << "        -O <level>            Optimization level (0, 1, 2, 3)\n";
    std::cout << "        -c, --obj             Emit object file (.o/.obj)\n";
    std::cout << "        -static, --static-lib Emit static library (.a/.lib)\n";
    std::cout << "        -shared, --dylib      Emit dynamic/shared library (.so/.dll/.dylib)\n";
    std::cout << "        -S, --asm             Emit assembly source (.s/.wat)\n";
    std::cout << "        --exe                 Emit executable (default)\n";
    std::cout << "        -s, --strip           Strip symbol table and debug metadata\n";
#else
    std::cout << "    (AOT/WASM compilation disabled - Fyra backend not available)\n";
#endif
    std::cout << "\n  Tooling:\n";
    std::cout << "    " << programName << " -lsp                 Start LSP server\n";
    std::cout << "    " << programName << " -format <file>       Format a source file\n";
    std::cout << "\n  Debugging:\n";
    std::cout << "    " << programName << " -ast <source_file>      Print the AST\n";
    std::cout << "    " << programName << " -cst <source_file>      Print the CST\n";
    std::cout << "    " << programName << " -tokens <source_file>   Print tokens\n";
    std::cout << "    " << programName << " -lir <source_file>      Print the LIR (Low-level IR)\n";
#ifdef FYRA_AVAILABLE
    std::cout << "    " << programName << " -fyra-ir <source_file>  Print the Fyra IR\n";
#endif
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // Default to REPL if no arguments provided
        std::cout << "Limit Programming Language REPL (planned feature)\n";
        return 0;
    }
    
    std::string command = argv[1];
    LM::CompileOptions options;
    std::string source_file;

    if (command == "-lsp") {
        LM::LSP::run();
        return 0;
    }

    if (command == "help" || command == "--help" || command == "-h") {
        printUsage(argv[0]);
        return 0;
    }

    if (command == "-format" && argc >= 3) {
        std::ifstream file(argv[2]);
        if (!file.is_open()) return 1;
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::cout << LM::Formatter::format(buffer.str()) << std::endl;
        return 0;
    }

    if (command == "-ast" && argc >= 3) { options.print_ast = true; return LM::Compiler::executeFile(argv[2], options); }
    if (command == "-cst" && argc >= 3) { options.print_cst = true; return LM::Compiler::executeFile(argv[2], options); }
    if (command == "-tokens" && argc >= 3) { options.print_tokens = true; return LM::Compiler::executeFile(argv[2], options); }
    if (command == "-lir" && argc >= 3) { options.print_lir = true; return LM::Compiler::executeFile(argv[2], options); }
#ifdef FYRA_AVAILABLE
    if (command == "-fyra-ir" && argc >= 3) { options.print_fyra_ir = true; return LM::Compiler::executeFile(argv[2], options); }
#endif

    if (command == "run") {
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-I" && i + 1 < argc) options.include_dirs.push_back(argv[++i]);
            else if (arg == "-debug") options.debug = true;
            else if (arg == "--verify=strict") options.strict_verification = true;
            else if (arg == "--verify=hybrid") options.strict_verification = false;
            else if (arg[0] != '-') source_file = arg;
        }
        if (source_file.empty()) {
            return 1;
        }
        return LM::Compiler::executeFile(source_file, options);
    }

    if (command == "build") {
#ifdef FYRA_AVAILABLE
        options.use_aot = true;
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-I" && i + 1 < argc) options.include_dirs.push_back(argv[++i]);
            else if (arg == "-target" && i + 1 < argc) options.target = argv[++i];
            else if (arg == "--verify=strict") options.strict_verification = true;
            else if (arg == "--verify=hybrid") options.strict_verification = false;
            else if (arg == "-o" && i + 1 < argc) options.output_file = argv[++i];
            else if (arg == "-O" && i + 1 < argc) options.opt_level = std::stoi(argv[++i]);
            else if (arg == "-s" || arg == "--strip") options.strip = true;
            else if (arg == "-c" || arg == "--obj" || arg == "--object") options.artifact_type = LM::ArtifactType::Object;
            else if (arg == "-static" || arg == "--static" || arg == "--static-lib") options.artifact_type = LM::ArtifactType::StaticLibrary;
            else if (arg == "-shared" || arg == "--shared" || arg == "--dylib" || arg == "--dynamic") options.artifact_type = LM::ArtifactType::SharedLibrary;
            else if (arg == "-S" || arg == "--asm" || arg == "--assembly") options.artifact_type = LM::ArtifactType::Assembly;
            else if (arg == "--exe" || arg == "-bin") options.artifact_type = LM::ArtifactType::Executable;
            else if ((arg == "-type" || arg == "--type") && i + 1 < argc) {
                std::string type_val = argv[++i];
                if (type_val == "obj" || type_val == "object") options.artifact_type = LM::ArtifactType::Object;
                else if (type_val == "static" || type_val == "lib") options.artifact_type = LM::ArtifactType::StaticLibrary;
                else if (type_val == "shared" || type_val == "dylib" || type_val == "dynamic") options.artifact_type = LM::ArtifactType::SharedLibrary;
                else if (type_val == "asm" || type_val == "assembly") options.artifact_type = LM::ArtifactType::Assembly;
                else if (type_val == "exe" || type_val == "bin" || type_val == "executable") options.artifact_type = LM::ArtifactType::Executable;
            }
            else if (arg == "windows" || arg == "linux" || arg == "macos" || arg == "wasm") options.target = arg;
            else if (arg == "x86_64" || arg == "aarch64" || arg == "wasm32") options.arch = arg;
            else if (arg == "0" || arg == "1" || arg == "2" || arg == "3") options.opt_level = std::stoi(arg);
            else if (arg[0] != '-') source_file = arg;
        }
        if (source_file.empty()) return 1;
        if (options.output_file.empty()) {
            options.output_file = source_file;
            size_t dot = options.output_file.rfind(".lm");
            if (dot != std::string::npos) options.output_file.erase(dot);

            bool is_windows = (options.target == "windows");
            bool is_macos = (options.target == "macos");
            bool is_wasm = (options.target == "wasm");

            switch (options.artifact_type) {
                case LM::ArtifactType::Object:
                    options.output_file += is_windows ? ".obj" : ".o";
                    break;
                case LM::ArtifactType::StaticLibrary:
                    options.output_file += is_windows ? ".lib" : ".a";
                    break;
                case LM::ArtifactType::SharedLibrary:
                    options.output_file += is_windows ? ".dll" : (is_macos ? ".dylib" : ".so");
                    break;
                case LM::ArtifactType::Assembly:
                    options.output_file += is_wasm ? ".wat" : ".s";
                    break;
                case LM::ArtifactType::Executable:
                default:
                    if (is_wasm) options.output_file += ".wasm";
                    else if (is_windows) options.output_file += ".exe";
                    break;
            }
        }
        int result = LM::Compiler::executeFile(source_file, options);
        std::cout << "Build result: " << result << std::endl;
        if (result == 0) {
            std::string label = "Executable";
            switch (options.artifact_type) {
                case LM::ArtifactType::Object: label = "Object file"; break;
                case LM::ArtifactType::StaticLibrary: label = "Static library"; break;
                case LM::ArtifactType::SharedLibrary: label = "Shared library"; break;
                case LM::ArtifactType::Assembly: label = "Assembly file"; break;
                default: label = "Executable"; break;
            }
            std::cout << label << " built successfully: " << options.output_file << std::endl;

            // Automatically output precompiled metadata file if building a library
            if (options.artifact_type == LM::ArtifactType::StaticLibrary || options.artifact_type == LM::ArtifactType::SharedLibrary) {
                LM::Frontend::CompiledModuleMeta meta;
                std::string mod_name = source_file;
                size_t dot = mod_name.rfind(".lm");
                if (dot != std::string::npos) mod_name.erase(dot);
                std::replace(mod_name.begin(), mod_name.end(), '/', '.');
                meta.module_name = mod_name;

                meta.abi_version = "1.0.0";
                meta.target_triple = options.target + "-" + options.arch;
                meta.architecture = options.arch;
                meta.os = options.target;
                meta.artifact_kind = (options.artifact_type == LM::ArtifactType::SharedLibrary) ? "shared" : "static";
                meta.artifact_path = options.output_file;

                auto mod_ptr = LM::Frontend::ModuleManager::getInstance().load_module(source_file);
                if (!mod_ptr) mod_ptr = LM::Frontend::ModuleManager::getInstance().get_module(source_file);

                if (mod_ptr) {
                    for (const auto& sym : mod_ptr->public_symbols) {
                        meta.exports.push_back(sym);
                        meta.export_signatures[sym] = "fn()";
                    }
                    for (const auto& dep : mod_ptr->dependencies) {
                        meta.dependencies.push_back(dep);
                    }
                    std::hash<std::string> hasher;
                    std::stringstream hash_ss;
                    hash_ss << std::hex << hasher(mod_ptr->source);
                    meta.source_hash = hash_ss.str();
                } else {
                    std::ifstream src_file(source_file);
                    if (src_file.is_open()) {
                        std::stringstream src_buf;
                        src_buf << src_file.rdbuf();
                        std::hash<std::string> hasher;
                        std::stringstream hash_ss;
                        hash_ss << std::hex << hasher(src_buf.str());
                        meta.source_hash = hash_ss.str();
                    } else {
                        meta.source_hash = "00000000";
                    }
                    meta.exports.push_back(mod_name);
                    meta.export_signatures[mod_name] = "fn()";
                }

                std::string meta_path = options.output_file + ".meta";
                std::ofstream meta_file(meta_path);
                if (meta_file.is_open()) {
                    meta_file << meta.serialize();
                    meta_file.close();
                    std::cout << "Metadata emitted to: " << meta_path << std::endl;
                }
            }
        } else {
            std::cout << "Build failed" << std::endl;
        }
        return result;
#else
        std::cerr << "Error: 'build' command requires Fyra backend (not available).\n";
        std::cerr << "Please use 'run' command with the register VM instead.\n";
        return 1;
#endif
    }

    if (command[0] != '-') return LM::Compiler::executeFile(command, options);

    return 0;
}
