#include "handlers.hh"
#include "config_parser.hh"
#include "process_helper.hh"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

int handle_run(int argc, char** argv) {
    PackageMetadata meta = ConfigParser::parse("luminar.toml");
    if (meta.name.empty()) {
        std::cerr << "error: could not find luminar.toml or package name\n";
        return 1;
    }

    std::string entry_point = "src/main.lm";
    std::vector<std::string> forwarded_args;
    bool forwarding = false;

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--") {
            forwarding = true;
            continue;
        }
        if (forwarding) {
            forwarded_args.push_back(arg);
        } else {
            // If not forwarding and not starting with -, assume it's the entry point
            if (arg[0] != '-') {
                entry_point = arg;
            }
        }
    }

    if (!fs::exists(entry_point)) {
        std::cerr << "error: entry point '" << entry_point << "' not found\n";
        return 1;
    }

    // Find the absolute path to the compiler
    char* root_dir = getenv("REPOROOT");
    std::string compiler_path = root_dir ? std::string(root_dir) + "/bin/limitly" : "../bin/limitly";

    if (!fs::exists(compiler_path)) {
        compiler_path = "./bin/limitly";
        if (!fs::exists(compiler_path)) {
            compiler_path = "../bin/limitly";
             if (!fs::exists(compiler_path)) {
                compiler_path = "limitly";
             }
        }
    }

    std::vector<std::string> args;
    for (const auto& arg : forwarded_args) {
        args.push_back(arg);
    }
    args.push_back(entry_point);

    return Lyra::run_command(compiler_path, args);
}
