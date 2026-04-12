#include "limitly.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/type_checker.hh"
#include "frontend/module_manager.hh"
#include <iostream>
#include <string>
#include <vector>

namespace LM {
    void LSP::run() {
        std::cerr << "Limitly LSP started (JSON Protocol)..." << std::endl;
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line == "exit") break;
            if (line.empty()) continue;

            try {
                Frontend::Scanner scanner(line);
                scanner.scanTokens();
                Frontend::Parser parser(scanner, false);
                auto ast = parser.parse();
                Frontend::ModuleManager::getInstance().resolve_all(ast, "lsp");
                auto res = Frontend::TypeCheckerFactory::check_program(ast, line, "lsp-input");

                std::cout << "{" << std::endl;
                std::cout << "  \"success\": " << (res.success ? "true" : "false") << "," << std::endl;
                std::cout << "  \"errors\": [" << std::endl;
                for (size_t i = 0; i < res.errors.size(); ++i) {
                    std::string err = res.errors[i];
                    size_t pos = 0;
                    while ((pos = err.find('\"', pos)) != std::string::npos) {
                        err.replace(pos, 1, "\\\"");
                        pos += 2;
                    }
                    std::cout << "    { \"message\": \"" << err << "\" }" << (i + 1 < res.errors.size() ? "," : "") << std::endl;
                }
                std::cout << "  ]" << std::endl;
                std::cout << "}" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "{ \"success\": false, \"errors\": [{ \"message\": \"" << e.what() << "\" }] }" << std::endl;
            }
            std::cout << std::endl;
        }
    }
}
