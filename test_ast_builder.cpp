#include "src/frontend/ast_builder.hh"
#include "src/frontend/cst.hh"
#include "src/frontend/scanner.hh"
#include <iostream>
#include <memory>

using namespace frontend;
using namespace CST;
using namespace AST;

// Helper function to create a simple CST for testing
std::unique_ptr<CST::Node> createSimpleCST() {
    // Create a simple program with a variable declaration: var x: int = 42;
    auto program = createNode(NodeKind::PROGRAM);
    
    // Create a variable declaration
    auto varDecl = createNode(NodeKind::VAR_DECLARATION);
    
    // Add "var" keyword token
    Token varToken;
    varToken.type = TokenType::VAR;
    varToken.lexeme = "var";
    varToken.line = 1;
    varToken.start = 0;
    varDecl->addToken(varToken);
    
    // Add whitespace
    Token wsToken1;
    wsToken1.type = TokenType::WHITESPACE;
    wsToken1.lexeme = " ";
    wsToken1.line = 1;
    wsToken1.start = 3;
    varDecl->addToken(wsToken1);
    
    // Add identifier node
    auto identifier = createNode(NodeKind::IDENTIFIER);
    Token identifierToken;
    identifierToken.type = TokenType::IDENTIFIER;
    identifierToken.lexeme = "x";
    identifierToken.line = 1;
    identifierToken.start = 4;
    identifier->addToken(identifierToken);
    varDecl->addNode(std::move(identifier));
    
    // Add colon token
    Token colonToken;
    colonToken.type = TokenType::COLON;
    colonToken.lexeme = ":";
    colonToken.line = 1;
    colonToken.start = 5;
    varDecl->addToken(colonToken);
    
    // Add whitespace
    Token wsToken2;
    wsToken2.type = TokenType::WHITESPACE;
    wsToken2.lexeme = " ";
    wsToken2.line = 1;
    wsToken2.start = 6;
    varDecl->addToken(wsToken2);
    
    // Add type annotation
    auto typeNode = createNode(NodeKind::PRIMITIVE_TYPE);
    Token typeToken;
    typeToken.type = TokenType::INT_TYPE;
    typeToken.lexeme = "int";
    typeToken.line = 1;
    typeToken.start = 7;
    typeNode->addToken(typeToken);
    varDecl->addNode(std::move(typeNode));
    
    // Add equals token
    Token equalsToken;
    equalsToken.type = TokenType::EQUAL;
    equalsToken.lexeme = " = ";
    equalsToken.line = 1;
    equalsToken.start = 10;
    varDecl->addToken(equalsToken);
    
    // Add initializer
    auto initializer = createNode(NodeKind::INITIALIZER);
    auto literal = createNode(NodeKind::LITERAL_EXPR);
    Token numberToken;
    numberToken.type = TokenType::NUMBER;
    numberToken.lexeme = "42";
    numberToken.line = 1;
    numberToken.start = 13;
    literal->addToken(numberToken);
    initializer->addNode(std::move(literal));
    varDecl->addNode(std::move(initializer));
    
    // Add semicolon
    Token semicolonToken;
    semicolonToken.type = TokenType::SEMICOLON;
    semicolonToken.lexeme = ";";
    semicolonToken.line = 1;
    semicolonToken.start = 15;
    varDecl->addToken(semicolonToken);
    
    program->addNode(std::move(varDecl));
    
    return program;
}

// Helper function to create a CST with error nodes
std::unique_ptr<CST::Node> createErrorCST() {
    auto program = createNode(NodeKind::PROGRAM);
    
    // Add an error node
    auto errorNode = createErrorNode("Syntax error: unexpected token", 0, 10);
    program->addNode(std::move(errorNode));
    
    // Add a missing node
    auto missingNode = createMissingNode(NodeKind::IDENTIFIER, "Missing variable name", 10, 10);
    program->addNode(std::move(missingNode));
    
    return program;
}

int main() {
    std::cout << "Testing Unified CST→AST Converter with Type Resolution...\n\n";
    
    // Test 1: Early type resolution for declarations
    std::cout << "Test 1: Early Type Resolution for Declarations\n";
    std::cout << "===============================================\n";
    
    auto cst = createSimpleCST();
    std::cout << "CST structure:\n" << cst->toString() << "\n";
    
    BuildConfig config;
    config.insertErrorNodes = true;
    config.insertMissingNodes = true;
    config.preserveSourceMapping = true;
    config.enableEarlyTypeResolution = true;
    config.deferExpressionTypes = true;
    config.resolveBuiltinTypes = true;
    
    ASTBuilder builder(config);
    auto ast = builder.buildAST(*cst);
    
    if (ast) {
        std::cout << "AST transformation successful!\n";
        std::cout << "Number of statements: " << ast->statements.size() << "\n";
        std::cout << "Transformed nodes: " << builder.getTransformedNodeCount() << "\n";
        std::cout << "Source mappings: " << builder.getSourceMappings().size() << "\n";
        std::cout << "Deferred resolutions: " << builder.getDeferredResolutions().size() << "\n";
        
        if (!ast->statements.empty()) {
            auto varDecl = std::dynamic_pointer_cast<VarDeclaration>(ast->statements[0]);
            if (varDecl) {
                std::cout << "Variable name: " << varDecl->name << "\n";
                if (varDecl->type) {
                    auto type = *varDecl->type;
                    std::cout << "Variable type: " << type->typeName << "\n";
                    std::cout << "Is primitive: " << (type->isPrimitive ? "yes" : "no") << "\n";
                    std::cout << "Type resolved immediately: " << (type->typeName != "deferred" ? "yes" : "no") << "\n";
                }
            }
        }
        
        // Show type resolution context
        const auto& typeContext = builder.getTypeContext();
        std::cout << "Builtin types registered: " << typeContext.builtinTypes.size() << "\n";
        std::cout << "Declared types: " << typeContext.declaredTypes.size() << "\n";
    } else {
        std::cout << "AST transformation failed!\n";
    }
    
    if (builder.hasErrors()) {
        std::cout << "Errors during transformation:\n";
        for (const auto& error : builder.getErrors()) {
            std::cout << "  - " << error.message << "\n";
        }
    }
    
    std::cout << "\n";
    
    // Test 2: Deferred type resolution for expressions
    std::cout << "\nTest 2: Deferred Type Resolution for Expressions\n";
    std::cout << "================================================\n";
    
    // Create a CST with expressions that should have deferred types
    auto exprCST = createNode(NodeKind::PROGRAM);
    auto binaryExpr = createNode(NodeKind::BINARY_EXPR);
    
    // Left operand: variable
    auto leftVar = createNode(NodeKind::VARIABLE_EXPR);
    Token leftToken;
    leftToken.type = TokenType::IDENTIFIER;
    leftToken.lexeme = "x";
    leftVar->addToken(leftToken);
    binaryExpr->addNode(std::move(leftVar));
    
    // Operator
    Token opToken;
    opToken.type = TokenType::PLUS;
    opToken.lexeme = "+";
    binaryExpr->addToken(opToken);
    
    // Right operand: literal
    auto rightLit = createNode(NodeKind::LITERAL_EXPR);
    Token rightToken;
    rightToken.type = TokenType::NUMBER;
    rightToken.lexeme = "5";
    rightLit->addToken(rightToken);
    binaryExpr->addNode(std::move(rightLit));
    
    auto exprStmt = createNode(NodeKind::EXPRESSION_STATEMENT);
    exprStmt->addNode(std::move(binaryExpr));
    exprCST->addNode(std::move(exprStmt));
    
    ASTBuilder exprBuilder(config);
    auto exprAST = exprBuilder.buildAST(*exprCST);
    
    if (exprAST) {
        std::cout << "Expression AST transformation successful!\n";
        std::cout << "Deferred type resolutions: " << exprBuilder.getDeferredResolutions().size() << "\n";
        
        for (const auto& deferred : exprBuilder.getDeferredResolutions()) {
            std::cout << "Deferred: " << deferred.contextInfo << " (strategy: ";
            switch (deferred.strategy) {
                case TypeResolutionStrategy::DEFERRED:
                    std::cout << "DEFERRED";
                    break;
                case TypeResolutionStrategy::IMMEDIATE:
                    std::cout << "IMMEDIATE";
                    break;
                default:
                    std::cout << "OTHER";
                    break;
            }
            std::cout << ")\n";
        }
    }
    
    std::cout << "\n";
    
    // Test 3: Error recovery
    std::cout << "Test 3: Error recovery\n";
    std::cout << "======================\n";
    
    auto errorCST = createErrorCST();
    std::cout << "Error CST structure:\n" << errorCST->toString() << "\n";
    
    ASTBuilder errorBuilder(config);
    auto errorAST = errorBuilder.buildAST(*errorCST);
    
    if (errorAST) {
        std::cout << "Error AST transformation successful!\n";
        std::cout << "Number of statements: " << errorAST->statements.size() << "\n";
        std::cout << "Error nodes: " << errorBuilder.getErrorNodeCount() << "\n";
        std::cout << "Missing nodes: " << errorBuilder.getMissingNodeCount() << "\n";
    }
    
    if (errorBuilder.hasErrors()) {
        std::cout << "Errors during error recovery:\n";
        for (const auto& error : errorBuilder.getErrors()) {
            std::cout << "  - " << error.message << "\n";
        }
    }
    
    std::cout << "\n";
    
    // Test 4: Configuration options
    std::cout << "\nTest 4: Type Resolution Configuration\n";
    std::cout << "====================================\n";
    
    BuildConfig noTypeResolutionConfig;
    noTypeResolutionConfig.enableEarlyTypeResolution = false;
    noTypeResolutionConfig.deferExpressionTypes = false;
    
    ASTBuilder noTypeBuilder(noTypeResolutionConfig);
    auto noTypeAST = noTypeBuilder.buildAST(*cst);
    
    std::cout << "No type resolution result: " << (noTypeAST ? "Success" : "Failed") << "\n";
    std::cout << "Builtin types registered: " << noTypeBuilder.getTypeContext().builtinTypes.size() << "\n";
    std::cout << "Deferred resolutions: " << noTypeBuilder.getDeferredResolutions().size() << "\n";
    
    if (noTypeAST && !noTypeAST->statements.empty()) {
        auto varDecl = std::dynamic_pointer_cast<VarDeclaration>(noTypeAST->statements[0]);
        if (varDecl && varDecl->type) {
            std::cout << "Variable type without early resolution: " << (*varDecl->type)->typeName << "\n";
        }
    }
    
    std::cout << "\nAll tests completed!\n";
    
    return 0;
}