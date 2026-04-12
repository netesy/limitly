#include "limitly.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/cst/printer.hh"

namespace LM {
    std::string Formatter::format(const std::string& source) {
        return source;
    }
}
