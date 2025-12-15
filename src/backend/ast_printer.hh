#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "../common/backend.hh"
#include "../frontend/ast.hh"
#include "../frontend/scanner.hh"
#include <memory>
#include <string>
#include <variant>

// AST Printer backend - for debugging and visualization
class ASTPrinter : public Backend {
public:
    ASTPrinter() = default;
    
    virtual void process(const std::shared_ptr<AST::Program>& program) override;
    
private:
    void printNode(const std::shared_ptr<AST::Node>& node, int indent = 0);
    std::string getIndentation(int indent) const;
    
    // Utility functions
    std::string tokenTypeToString(TokenType type) const;
    std::string valueToString(const std::variant<std::string, bool, std::nullptr_t>& value) const;
    std::string typeToString(const std::shared_ptr<AST::TypeAnnotation>& type) const;
};

#endif // AST_PRINTER_HH
