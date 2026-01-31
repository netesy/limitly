#ifndef AST_PRINTER_H
#define AST_PRINTER_H


#include "../ast.hh"
#include "../scanner.hh"
#include <memory>
#include <string>
#include <variant>

namespace LM {
namespace Frontend {
namespace AST {

// AST Printer backend - for debugging and visualization
class ASTPrinter {
public:
    ASTPrinter() = default;
    
    void process(const std::shared_ptr<AST::Program>& program);
    
private:
    void printNode(const std::shared_ptr<AST::Node>& node, int indent = 0);
    std::string getIndentation(int indent) const;
    
    // Utility functions
    std::string tokenTypeToString(TokenType type) const;
    std::string valueToString(const std::variant<std::string, bool, std::nullptr_t>& value) const;
    std::string typeToString(const std::shared_ptr<AST::TypeAnnotation>& type) const;
    std::string typePtrToString(const TypePtr& type) const;
};

} // namespace AST
} // namespace Frontend
} // namespace LM

#endif // AST_PRINTER_HH
