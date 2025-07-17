#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>
#include <string>
#include <variant>
#include <optional>
#include <unordered_map>
#include "scanner.hh"
#include "ast.hh"

// Frontend parser class - responsible for parsing tokens into AST
class Parser {
public:
    Parser(Scanner &scanner) : scanner(scanner), current(0) {}

    std::shared_ptr<AST::Program> parse();

private:
    Scanner &scanner;
    size_t current;

    // Helper methods
    Token peek();
    Token previous();
    Token advance();
    bool check(TokenType type);
    bool match(std::initializer_list<TokenType> types);
    bool isAtEnd();
    Token consume(TokenType type, const std::string &message);
    void synchronize();
    void error(const std::string &message);

    // Parsing methods for statements
    std::shared_ptr<AST::Statement> declaration();
    std::shared_ptr<AST::Statement> varDeclaration();
    std::shared_ptr<AST::Statement> statement();
    std::shared_ptr<AST::Statement> expressionStatement();
    std::shared_ptr<AST::Statement> printStatement();
    std::shared_ptr<AST::Statement> ifStatement();
    std::shared_ptr<AST::BlockStatement> block();
    std::shared_ptr<AST::Statement> forStatement();
    std::shared_ptr<AST::Statement> whileStatement();
    std::shared_ptr<AST::FunctionDeclaration> function(const std::string &kind);
    std::shared_ptr<AST::Statement> returnStatement();
    std::shared_ptr<AST::ClassDeclaration> classDeclaration();
    std::shared_ptr<AST::Statement> attemptStatement();
    std::shared_ptr<AST::Statement> parallelStatement();
    std::shared_ptr<AST::Statement> concurrentStatement();
    std::shared_ptr<AST::Statement> importStatement();
    std::shared_ptr<AST::EnumDeclaration> enumDeclaration();
    std::shared_ptr<AST::Statement> matchStatement();
    std::shared_ptr<AST::Statement> typeDeclaration();
    std::shared_ptr<AST::Statement> traitDeclaration();
    std::shared_ptr<AST::Statement> interfaceDeclaration();
    std::shared_ptr<AST::Statement> moduleDeclaration();
    std::shared_ptr<AST::Statement> iterStatement();
    std::shared_ptr<AST::Statement> unsafeBlock();
    std::shared_ptr<AST::Statement> contractStatement();
    std::shared_ptr<AST::Statement> comptimeStatement();

    // Parsing methods for expressions
    std::shared_ptr<AST::Expression> expression();
    std::shared_ptr<AST::Expression> assignment();
    std::shared_ptr<AST::Expression> logicalOr();
    std::shared_ptr<AST::Expression> logicalAnd();
    std::shared_ptr<AST::Expression> equality();
    std::shared_ptr<AST::Expression> comparison();
    std::shared_ptr<AST::Expression> term();
    std::shared_ptr<AST::Expression> factor();
    std::shared_ptr<AST::Expression> unary();
    std::shared_ptr<AST::Expression> call();
    std::shared_ptr<AST::Expression> primary();
    std::shared_ptr<AST::Expression> finishCall(std::shared_ptr<AST::Expression> callee);
    
    // Type annotation parsing
    AST::TypeAnnotation parseTypeAnnotation();
};

#endif // PARSER_H