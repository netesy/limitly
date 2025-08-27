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
    bool in_concurrent_block = false;

    struct ParseError {
        std::string message;
        int line;
        int column;
        std::string codeContext;
    };
    std::vector<ParseError> errors;
    static constexpr size_t MAX_ERRORS = 20;

public:
    const std::vector<ParseError>& getErrors() const { return errors; }
    bool hadError() const { return !errors.empty(); }

    // Helper to create a placeholder error expression
    std::shared_ptr<AST::LiteralExpr> makeErrorExpr() {
        auto errorExpr = std::make_shared<AST::LiteralExpr>();
        errorExpr->line = peek().line;
        errorExpr->value = nullptr; // Use null as a placeholder
        return errorExpr;
    };

    // Helper methods
    Token peek();
    Token previous();
    Token advance();
    bool check(TokenType type);
    bool match(std::initializer_list<TokenType> types);
    bool isAtEnd();
    Token consume(TokenType type, const std::string &message);
    void synchronize();
    void error(const std::string &message, bool suppressException = false);
    std::vector<Token> collectAnnotations();

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
    std::shared_ptr<AST::Statement> breakStatement();
    std::shared_ptr<AST::Statement> continueStatement();
    std::shared_ptr<AST::FunctionDeclaration> function(const std::string &kind);
    std::shared_ptr<AST::Statement> returnStatement();
    std::shared_ptr<AST::ClassDeclaration> classDeclaration();
    std::shared_ptr<AST::Statement> attemptStatement();
    std::shared_ptr<AST::Statement> parallelStatement();
    std::shared_ptr<AST::Statement> concurrentStatement();
    std::shared_ptr<AST::Statement> taskStatement();
    std::shared_ptr<AST::Statement> workerStatement();
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

    // Concurrency parsing helper
    void parseConcurrencyParams(
        std::string& channel,
        std::string& mode,
        std::string& cores,
        std::string& onError,
        std::string& timeout,
        std::string& grace,
        std::string& onTimeout
    );

    // Type parsing methods
    std::shared_ptr<AST::TypeAnnotation> parseTypeAnnotation();
    std::shared_ptr<AST::TypeAnnotation> parseStructuralType(const std::string& typeName = "");
    bool isPrimitiveType(TokenType type);
    std::string tokenTypeToString(TokenType type);

    // Parsing methods for expressions
    std::shared_ptr<AST::Expression> expression();
    std::shared_ptr<AST::Expression> assignment();
    std::shared_ptr<AST::Expression> logicalOr();
    std::shared_ptr<AST::Expression> logicalAnd();
    std::shared_ptr<AST::Expression> equality();
    std::shared_ptr<AST::Expression> comparison();
    std::shared_ptr<AST::Expression> term();
    std::shared_ptr<AST::Expression> factor();
    std::shared_ptr<AST::Expression> power();
    std::shared_ptr<AST::Expression> unary();
    std::shared_ptr<AST::Expression> call();
    std::shared_ptr<AST::Expression> primary();
    std::shared_ptr<AST::Expression> finishCall(std::shared_ptr<AST::Expression> callee);
    std::shared_ptr<AST::InterpolatedStringExpr> interpolatedString();

    // Type annotation parsing
};

#endif // PARSER_H
