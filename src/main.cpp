#include "limitly.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void printUsage(const char* programName) {
    std::cout << "Limit Programming Language\n";
    std::cout << "Usage:\n";
    std::cout << "\n  Execution (Register VM):\n";
    std::cout << "    " << programName << " run [options] <source_file>\n";
    std::cout << "      Options:\n";
    std::cout << "        -debug                Enable debug output\n";
    std::cout << "\n  Compilation (AOT/WASM):\n";
    std::cout << "    " << programName << " build [options] <source_file>\n";
    std::cout << "      Options:\n";
    std::cout << "        -target <target>      Target platform (windows, linux, macos, wasm)\n";
    std::cout << "        -o <output>           Output file name\n";
    std::cout << "        -O <level>            Optimization level (0, 1, 2, 3)\n";
    std::cout << "\n  Tooling:\n";
    std::cout << "    " << programName << " -lsp                 Start LSP server\n";
    std::cout << "    " << programName << " -format <file>       Format a source file\n";
    std::cout << "\n  Debugging:\n";
    std::cout << "    " << programName << " -ast <source_file>      Print the AST\n";
    std::cout << "    " << programName << " -cst <source_file>      Print the CST\n";
    std::cout << "    " << programName << " -tokens <source_file>   Print tokens\n";
    std::cout << "    " << programName << " -fyra-ir <source_file>  Print the Fyra IR\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string command = argv[1];
    LM::CompileOptions options;
    std::string source_file;

    if (command == "-lsp") {
        LM::LSP::run();
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
    if (command == "-fyra-ir" && argc >= 3) { options.print_fyra_ir = true; return LM::Compiler::executeFile(argv[2], options); }

    if (command == "run") {
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-debug") options.debug = true;
            else if (arg[0] != '-') source_file = arg;
        }
        if (source_file.empty()) return 1;
        return LM::Compiler::executeFile(source_file, options);
    }

    if (command == "build") {
        options.use_aot = true;
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-target" && i + 1 < argc) options.target = argv[++i];
            else if (arg == "-o" && i + 1 < argc) options.output_file = argv[++i];
            else if (arg == "-O" && i + 1 < argc) options.opt_level = std::stoi(argv[++i]);
            else if (arg[0] != '-') source_file = arg;
        }
        if (source_file.empty()) return 1;
        if (options.output_file.empty()) {
            options.output_file = source_file;
            size_t dot = options.output_file.rfind(".lm");
            if (dot != std::string::npos) options.output_file.erase(dot);
            if (options.target == "windows") options.output_file += ".exe";
        }
        return LM::Compiler::executeFile(source_file, options);
    }

    if (command[0] != '-') return LM::Compiler::executeFile(command, options);

    return 0;
}
