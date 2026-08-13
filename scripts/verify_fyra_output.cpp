#include "parser/Parser.h"
#include "ir/Module.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    std::ifstream is(argv[1]);
    if (!is.is_open()) return 1;

    try {
        parser::Parser p(is, parser::FileFormat::FYRA);
        auto mod = p.parseModule();

        if (!mod) {
            std::cerr << "Failed to parse: " << argv[1] << std::endl;
            return 1;
        }

        std::stringstream ss;
        mod->print(ss);
        std::string serialized = ss.str();

        std::stringstream ss_in(serialized);
        parser::Parser p2(ss_in, parser::FileFormat::FYRA);
        auto mod2 = p2.parseModule();

        if (!mod2) {
            std::cerr << "Failed round-trip parse for: " << argv[1] << std::endl;
            return 1;
        }

        // Semantic check placeholder (value relationships, instructions etc)
        // For now just structure count matching
        if (mod->getFunctions().size() != mod2->getFunctions().size()) {
            std::cerr << "Semantic mismatch for " << argv[1] << std::endl;
            return 1;
        }

        std::cout << "PASS: " << argv[1] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing " << argv[1] << ": " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
