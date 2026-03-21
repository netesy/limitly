#include <iostream>
#include <string>
#include <vector>
#include "handlers.hh"
#include "config_parser.hh"

void print_help() {
    std::cout << "Lyra - Luminar (Limitly) Package Manager\n\n";
    std::cout << "Usage:\n";
    std::cout << "  lyra <command> [arguments]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  init    Initialize a new project\n";
    std::cout << "  run     Run the current project\n";
    std::cout << "  build   Build the current project\n";
    std::cout << "  help    Show this help message\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_help();
        return 0;
    }

    std::string command = argv[1];

    if (command == "help" || command == "--help" || command == "-h") {
        print_help();
        return 0;
    }

    if (command == "init") {
        return handle_init();
    } else if (command == "run") {
        return handle_run(argc, argv);
    } else if (command == "build") {
        return handle_build(argc, argv);
    }

    std::cerr << "error: unknown command '" << command << "'\n\n";
    print_help();
    return 1;
}
