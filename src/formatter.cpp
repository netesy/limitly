#include "limitly.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/cst.hh"
#include <sstream>
#include <iostream>
#include <vector>

namespace LM {
    namespace {
        void formatNode(const Frontend::CST::Node* node, std::stringstream& ss, int& indent) {
            if (!node) return;
            for (const auto& element : node->elements) {
                if (std::holds_alternative<Frontend::Token>(element)) {
                    const auto& token = std::get<Frontend::Token>(element);
                    std::string lex = token.lexeme;
                    if (lex == "{") {
                        ss << " {\n"; indent++;
                        for(int i=0; i<indent; ++i) ss << "    ";
                    } else if (lex == "}") {
                        if (indent > 0) indent--;
                        ss << "\n";
                        for(int i=0; i<indent; ++i) ss << "    ";
                        ss << "}\n";
                        for(int i=0; i<indent; ++i) ss << "    ";
                    } else if (lex == ";") {
                        ss << ";\n";
                        for(int i=0; i<indent; ++i) ss << "    ";
                    } else if (lex == "(" || lex == "[" || lex == ".") {
                        ss << lex;
                    } else if (lex == ")" || lex == "]" || lex == ",") {
                        ss << lex << " ";
                    } else {
                        ss << lex << " ";
                    }
                } else if (std::holds_alternative<std::unique_ptr<Frontend::CST::Node>>(element)) {
                    formatNode(std::get<std::unique_ptr<Frontend::CST::Node>>(element).get(), ss, indent);
                }
            }
        }
    }

    std::string Formatter::format(const std::string& source) {
        try {
            Frontend::Scanner scanner(source);
            scanner.scanTokens();
            Frontend::Parser parser(scanner, true);
            parser.parse();
            const auto* cst = parser.getCST();
            if (!cst) return source;
            std::stringstream ss;
            int indent = 0;
            formatNode(cst, ss, indent);

            std::string res = ss.str();
            std::stringstream in(res);
            std::stringstream out;
            std::string line;
            while(std::getline(in, line)) {
                size_t first = line.find_first_not_of(" \t");
                if (first == std::string::npos) {
                    if (!line.empty()) out << "\n";
                    continue;
                }
                size_t last = line.find_last_not_of(" \t");
                out << line.substr(0, last+1) << "\n";
            }
            return out.str();
        } catch (...) { return source; }
    }
}
