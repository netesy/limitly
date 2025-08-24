#include "frontend/parser.hh"
#include "frontend/scanner.hh"
#include "backend/jit_backend.hh"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    std::cout << "Source loaded, creating scanner..." << std::endl;

    Scanner scanner(source);
    Parser parser(scanner);
    auto program = parser.parse();

    if (parser.hadError()) {
        std::cerr << "Parsing failed." << std::endl;
        return 1;
    }

    JitBackend backend;
    backend.process(program);
    backend.compile(argv[2]);

    std::cout << "Compilation successful." << std::endl;

    return 0;
}
