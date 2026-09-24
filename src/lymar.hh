#pragma once
#include <string>
#include <vector>
#include <memory>

namespace LM {
    enum class ArtifactType {
        Executable,
        Object,
        StaticLibrary,
        SharedLibrary,
        Assembly
    };

    struct CompileOptions {
#ifdef _WIN32
        std::string target = "windows";
#else
        std::string target = "linux";
#endif
        std::string arch = "x86_64";
        int opt_level = 2;
        std::string output_file;
        ArtifactType artifact_type = ArtifactType::Executable;
        bool debug = false;
        bool use_aot = false;
        bool use_wasm = false;
        bool use_wasi = false;
        bool dump_intermediate = false;
        bool print_ast = false;
        bool print_cst = false;
        bool print_tokens = false;
        bool print_lir = false;
        bool print_fyra_ir = false;
        bool disable_opt = false;
        bool strip = false;
        bool strict_verification = false;
        std::vector<std::string> include_dirs;
    };

    class Compiler {
    public:
        static int executeFile(const std::string& filename, const CompileOptions& options);
    };

    class Formatter {
    public:
        static std::string format(const std::string& source);
    };

    class LSP {
    public:
        static void run();
    };
}
