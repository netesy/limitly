#pragma once
#include <string>
#include <vector>
#include <memory>

namespace LM {
    struct CompileOptions {
        std::string target = "linux";
        std::string arch = "x86_64";
        int opt_level = 2;
        std::string output_file;
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
    };

    class Compiler {
    public:
        static int executeFile(const std::string& filename, const CompileOptions& options);
    };

    class Formatter {
    public:
        static std::string format(const std::string& source);
    };
}
