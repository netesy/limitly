#include "lymar.hh"
#include "frontend/module_manager.hh"
#include "lyra_api.hh"
#include "config_parser.hh"
#include "cli_update.hh"
#include "linter.hh"
#include "doc_generator.hh"
#include "benchmark_runner.hh"
#include "profiler.hh"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <functional>
#include <map>

static std::map<std::string, std::filesystem::file_time_type> collect_file_mtimes(const std::string& entry_file) {
    std::map<std::string, std::filesystem::file_time_type> mtimes;
    std::error_code ec;
    if (std::filesystem::exists(entry_file, ec)) {
        mtimes[entry_file] = std::filesystem::last_write_time(entry_file, ec);
    }
    auto watch_dir = [&](const std::filesystem::path& dir) {
        if (!std::filesystem::exists(dir, ec)) return;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(dir, std::filesystem::directory_options::skip_permission_denied, ec)) {
            if (entry.is_regular_file()) {
                auto ext = entry.path().extension().string();
                if (ext == ".lm" || ext == ".c" || ext == ".cpp" || ext == ".h" || ext == ".nol") {
                    mtimes[entry.path().string()] = entry.last_write_time(ec);
                }
            }
        }
    };
    if (std::filesystem::exists("src", ec)) watch_dir("src");
    if (std::filesystem::exists("lymar.nol", ec)) mtimes["lymar.nol"] = std::filesystem::last_write_time("lymar.nol", ec);
    return mtimes;
}

static int run_watch_loop(const std::function<int()>& execute_step, const std::string& entry_file, const std::string& action_label) {
    int res = execute_step();
    std::cout << "[WATCH] Watching for file changes (press Ctrl+C to exit)...\n";
    std::cout.flush();

    auto last_mtimes = collect_file_mtimes(entry_file);
    const bool once = (std::getenv("LYMAR_WATCH_ONCE") != nullptr);
    if (once) {
        std::cout << "[WATCH] LYMAR_WATCH_ONCE set, exiting watch loop.\n";
        return res;
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        auto current_mtimes = collect_file_mtimes(entry_file);
        bool changed = false;
        std::string changed_file;

        for (const auto& [file, time] : current_mtimes) {
            auto it = last_mtimes.find(file);
            if (it == last_mtimes.end() || it->second != time) {
                changed = true;
                changed_file = file;
                break;
            }
        }
        if (!changed && current_mtimes.size() != last_mtimes.size()) {
            changed = true;
            changed_file = "files modified";
        }

        if (changed) {
            std::cout << "\n[WATCH] Change detected (" << changed_file << "), " << action_label << "...\n";
            std::cout.flush();
            res = execute_step();
            last_mtimes = current_mtimes;
            std::cout << "[WATCH] Watching for file changes (press Ctrl+C to exit)...\n";
            std::cout.flush();
        }
    }
    return res;
}

void printUsage(const char* programName) {
    std::cout << "Lymar Programming Language\n";
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
    std::cout << "        -arch <arch>          Architecture (x86_64, aarch64, riscv64, wasm32)\n";
    std::cout << "        -o <output>           Output file name\n";
    std::cout << "        -O <level>            Optimization level (0, 1, 2, 3)\n";
    std::cout << "        -c, --obj             Emit object file (.o/.obj)\n";
    std::cout << "        -static, --static-lib Emit static library (.a/.lib)\n";
    std::cout << "        -shared, --dylib      Emit dynamic/shared library (.so/.dll/.dylib)\n";
    std::cout << "        -S, --asm             Emit assembly source (.s/.wat)\n";
    std::cout << "        --exe                 Emit executable (default)\n";
    std::cout << "        -s, --strip           Strip symbol table and debug metadata\n";
    std::cout << "        --native <file>       Compile/link foreign .c/.cpp source (repeatable)\n";
    std::cout << "        --native-include <dir>  Include dir for native source compilation\n";
    std::cout << "        --native-cflag <flag>   Extra flag for the native compiler (repeatable)\n";
    std::cout << "        --native-link <lib>     Extra library for the native link (repeatable)\n";
    std::cout << "        --bind-header <file.h>  Parse C header and generate FFI bindings (repeatable)\n";
    std::cout << "        --bind-lib <path>       Library path for generated bindings (paired with --bind-header)\n";
    std::cout << "        --bind-namespace <name> Override module name for generated bindings\n";
#else
    std::cout << "    (AOT/WASM compilation disabled - Fyra backend not available)\n";
#endif
    std::cout << "\n  Package Management (Lyra):\n";
    std::cout << "    " << programName << " init                 Initialize a new package\n";
    std::cout << "    " << programName << " update               Update package dependencies and lockfile\n";
    std::cout << "    " << programName << " add <pkg>            Add a package dependency\n";
    std::cout << "    " << programName << " publish              Publish package to index\n";
    std::cout << "    " << programName << " pack                 Package project into tarball\n";
    std::cout << "    " << programName << " install <tarball>    Install package tarball\n";
    std::cout << "    " << programName << " deps / tree / why   Display dependency analysis\n";
    std::cout << "    " << programName << " doctor / env / audit Diagnostics and audit\n";
    std::cout << "\n  Tooling:\n";
    std::cout << "    " << programName << " test [options] [filter] Run project tests (parallel, filtered)\n";
    std::cout << "    " << programName << " lint [options] [files]  Run linter & static analysis\n";
    std::cout << "    " << programName << " doc [options] [files]   Generate documentation from docstrings\n";
    std::cout << "    " << programName << " bench [options] [files] Run performance benchmarks\n";
    std::cout << "    " << programName << " profile [options] <file> Profile runtime execution and hotspots\n";
    std::cout << "    " << programName << " up [--check] [--version TAG] [--prefix DIR] Update compiler from GitHub releases\n";
    std::cout << "    " << programName << " -lsp                 Start LSP server\n";
    std::cout << "    " << programName << " -dap [--port PORT]   Start DAP server\n";
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
        std::cout << "Lymar Programming Language REPL (planned feature)\n";
        return 0;
    }
    
    std::string command = argv[1];
    if (command == "up") {
        try { return update_lymar(argc, argv); }
        catch (const std::exception& error) { std::cerr << "Update failed: " << error.what() << '\n'; return 1; }
    }
    LM::CompileOptions options;
    std::string source_file;
    std::vector<std::string> package_features;

    if (command == "-lsp") {
        LM::LSP::run();
        return 0;
    }

    if (command == "-dap" || command == "dap") {
        int port = 0;
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if ((arg == "--port" || arg == "-port" || arg == "-p") && i + 1 < argc) {
                port = std::stoi(argv[++i]);
            }
        }
        LM::DapRunner::run(port);
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

    if (command == "test") return Lyra::handle_test(argc, argv);
    if (command == "lint" || command == "-lint") return LM::Linter::run(argc, argv);
    if (command == "doc" || command == "-doc") return LM::DocGenerator::run(argc, argv);
    if (command == "bench" || command == "-bench") return LM::BenchmarkRunner::run(argc, argv);
    if (command == "profile" || command == "-profile") return LM::Profiler::run(argc, argv);

    try {
    // Package management subcommands forwarded in-process to Lyra
    if (command == "init") return Lyra::handle_init();
    if (command == "update") return Lyra::handle_update(argc, argv);
    if (command == "add") return Lyra::handle_add(argc, argv);
    if (command == "link") return Lyra::handle_link(argc, argv);
    if (command == "publish") return Lyra::handle_publish(argc, argv);
    if (command == "pack") return Lyra::handle_pack(argc, argv);
    if (command == "install") return Lyra::handle_install(argc, argv);
    if (command == "search") return Lyra::handle_search(argc, argv);
    if (command == "info") return Lyra::handle_info(argc, argv);
    if (command == "deps") return Lyra::handle_deps(argc, argv);
    if (command == "tree") return Lyra::handle_tree(argc, argv);
    if (command == "why") return Lyra::handle_why(argc, argv);
    if (command == "doctor") return Lyra::handle_doctor();
    if (command == "env") return Lyra::handle_env();
    if (command == "audit") return Lyra::handle_audit(argc, argv);
    if (command == "clean") return Lyra::handle_clean();

    } catch (const std::exception& error) {
        std::cerr << "Package command failed: " << error.what() << '\n';
        return 1;
    }

    if (command == "run") {
        // Anything after `--` belongs to the program, so a script can receive
        // arguments that look like compiler flags. Before `--`, the first
        // non-flag token is the script and later ones are program arguments.
        bool passthrough = false;
        bool watch_mode = false;
        std::vector<std::string> trailing;
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (passthrough) { options.program_args.push_back(arg); continue; }
            if (arg == "--") { passthrough = true; continue; }
            if (arg == "--watch" || arg == "-w") watch_mode = true;
            else if (arg == "-I" && i + 1 < argc) options.include_dirs.push_back(argv[++i]);
            else if (arg == "--bind-header" && i + 1 < argc) options.bind_headers.push_back(argv[++i]);
            else if (arg == "--bind-lib" && i + 1 < argc) options.bind_lib_paths.push_back(argv[++i]);
            else if (arg == "--bind-namespace" && i + 1 < argc) options.bind_namespaces.push_back(argv[++i]);
            else if (arg == "--features" && i + 1 < argc) {
                std::stringstream input(argv[++i]);
                std::string feature;
                while (std::getline(input, feature, ',')) package_features.push_back(feature);
            }
            else if (arg == "-debug") options.debug = true;
            else if (arg == "--profile" || arg == "-profile") options.profile = true;
            else if (arg.rfind("--flamegraph=", 0) == 0) {
                options.profile = true;
                options.profile_flamegraph = arg.substr(13);
            }
            else if (arg.rfind("--sort=", 0) == 0) {
                options.profile_sort = arg.substr(7);
            }
            else if (arg.rfind("--top=", 0) == 0) {
                options.profile_top = std::stoul(arg.substr(6));
            }
            else if (arg == "--json") {
                options.profile_json = true;
            }
            else if (arg == "--no-cache") {
                options.no_cache = true;
            }
            else if (arg == "--verify=strict") options.strict_verification = true;
            else if (arg == "--verify=hybrid") options.strict_verification = false;
            else if (arg[0] != '-') { if (source_file.empty()) source_file = arg; else trailing.push_back(arg); }
        }
        options.program_args.insert(options.program_args.begin(), trailing.begin(), trailing.end());
        if (source_file.empty() && std::filesystem::exists("lymar.nol")) source_file = "src/main.lm";
        if (source_file.empty()) return 1;
        // Merge [native] bind headers from project manifest (run mode)
        if (std::filesystem::exists("lymar.nol")) {
            auto native_meta = ConfigParser::parse("lymar.nol");
            options.bind_headers.insert(options.bind_headers.end(),
                native_meta.bind_headers.begin(), native_meta.bind_headers.end());
            options.bind_lib_paths.insert(options.bind_lib_paths.end(),
                native_meta.bind_lib_paths.begin(), native_meta.bind_lib_paths.end());
        }
        // In-process Lyra dependency resolution
        try {
            auto pkg_dirs = Lyra::resolve_package_include_dirs(".", package_features);
            options.include_dirs.insert(options.include_dirs.end(), pkg_dirs.begin(), pkg_dirs.end());
        } catch (const std::exception& error) {
            std::cerr << "Package resolution failed: " << error.what() << '\n';
            return 1;
        }

        if (watch_mode) {
            return run_watch_loop([&]() {
                return LM::Compiler::executeFile(source_file, options);
            }, source_file, "restarting");
        }
        return LM::Compiler::executeFile(source_file, options);
    }

    if (command == "build") {
#ifdef FYRA_AVAILABLE
        options.use_aot = true;
        bool watch_mode = false;
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "--watch" || arg == "-w") watch_mode = true;
            else if (arg == "-I" && i + 1 < argc) options.include_dirs.push_back(argv[++i]);
            else if (arg == "--native" && i + 1 < argc) options.native_sources.push_back(argv[++i]);
            else if (arg == "--native-include" && i + 1 < argc) options.native_include_dirs.push_back(argv[++i]);
            else if (arg == "--native-cflag" && i + 1 < argc) options.native_cflags.push_back(argv[++i]);
            else if (arg == "--native-link" && i + 1 < argc) options.native_link_libs.push_back(argv[++i]);
            else if (arg == "--bind-header" && i + 1 < argc) options.bind_headers.push_back(argv[++i]);
            else if (arg == "--bind-lib" && i + 1 < argc) options.bind_lib_paths.push_back(argv[++i]);
            else if (arg == "--bind-namespace" && i + 1 < argc) options.bind_namespaces.push_back(argv[++i]);
            else if (arg == "--features" && i + 1 < argc) {
                std::stringstream input(argv[++i]);
                std::string feature;
                while (std::getline(input, feature, ',')) package_features.push_back(feature);
            }
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
            else if ((arg == "-arch" || arg == "--arch") && i + 1 < argc) options.arch = argv[++i];
            else if (arg == "x86_64" || arg == "aarch64" || arg == "riscv64" || arg == "wasm32") options.arch = arg;
            else if (arg == "0" || arg == "1" || arg == "2" || arg == "3") options.opt_level = std::stoi(arg);
            else if (arg[0] != '-') source_file = arg;
        }
        if (source_file.empty() && std::filesystem::exists("lymar.nol")) source_file = "src/main.lm";
        if (source_file.empty()) return 1;
        if (options.arch != "x86_64" && options.arch != "aarch64" &&
            options.arch != "riscv64" && options.arch != "wasm32") {
            std::cerr << "Unsupported architecture: " << options.arch << '\n';
            return 1;
        }
        // Project builds pick up the manifest's [native] foreign sources and
        // link options; explicit --native flags stay additive on top.
        if (std::filesystem::exists("lymar.nol")) {
            auto native_meta = ConfigParser::parse("lymar.nol");
            options.native_sources.insert(options.native_sources.end(),
                native_meta.native_sources.begin(), native_meta.native_sources.end());
            options.native_include_dirs.insert(options.native_include_dirs.end(),
                native_meta.native_include_dirs.begin(), native_meta.native_include_dirs.end());
            options.native_cflags.insert(options.native_cflags.end(),
                native_meta.native_cflags.begin(), native_meta.native_cflags.end());
            options.native_link_libs.insert(options.native_link_libs.end(),
                native_meta.native_link_libs.begin(), native_meta.native_link_libs.end());
            options.bind_headers.insert(options.bind_headers.end(),
                native_meta.bind_headers.begin(), native_meta.bind_headers.end());
            options.bind_lib_paths.insert(options.bind_lib_paths.end(),
                native_meta.bind_lib_paths.begin(), native_meta.bind_lib_paths.end());
        }
        // In-process Lyra dependency resolution
        try {
            auto pkg_dirs = Lyra::resolve_package_include_dirs(".", package_features);
            options.include_dirs.insert(options.include_dirs.end(), pkg_dirs.begin(), pkg_dirs.end());
        } catch (const std::exception& error) {
            std::cerr << "Package resolution failed: " << error.what() << '\n';
            return 1;
        }
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
        auto do_build = [&]() -> int {
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
                    std::string mod_name = source_file;
                    size_t dot = mod_name.rfind(".lm");
                    if (dot != std::string::npos) mod_name.erase(dot);
                    std::replace(mod_name.begin(), mod_name.end(), '/', '.');

                    auto mod = LM::Frontend::ModuleManager::getInstance().get_module(mod_name);
                    if (!mod) {
                        mod = LM::Frontend::ModuleManager::getInstance().load_module(mod_name);
                    }

                    std::string kind = (options.artifact_type == LM::ArtifactType::SharedLibrary) ? "shared" : "static";
                    LM::Frontend::CompiledModuleMeta meta = LM::Frontend::ModuleManager::getInstance().generate_metadata(
                        mod, options.target, options.arch, kind, options.output_file
                    );

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
        };

        if (watch_mode) {
            return run_watch_loop(do_build, source_file, "rebuilding");
        }
        return do_build();
#else
        std::cerr << "Error: 'build' command requires Fyra backend (not available).\n";
        std::cerr << "Please use 'run' command with the register VM instead.\n";
        return 1;
#endif
    }

    // Legacy form: `lymar app.lm [args...]` runs the script directly.
    if (command[0] != '-') {
        for (int i = 2; i < argc; i++) options.program_args.push_back(argv[i]);
        return LM::Compiler::executeFile(command, options);
    }

    return 0;
}
