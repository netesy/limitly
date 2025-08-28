#include "frontend/ast.hh"
#include "frontend/scanner.hh"
#include <iostream>
#include <cassert>
#include <memory>

void test_complete_error_ast_integration() {
    std::cout << "Running test: Complete Error AST Integration... ";
    
    // Test 1: TypeAnnotation with fallible types
    AST::TypeAnnotation fallibleInt;
    fallibleInt.typeName = "int";
    fallibleInt.isFallible = true;
    fallibleInt.isPrimitive = true;
    
    AST::TypeAnnotation specificErrorType;
    specificErrorType.typeName = "string";
    specificErrorType.isFallible = true;
    specificErrorType.errorTypes = {"ParseError", "ValidationError"};
    
    // Test 2: FallibleExpr with complex nested expression
    auto callExpr = std::make_shared<AST::CallExpr>();
    callExpr->line = 1;
    
    auto callee = std::make_shared<AST::VariableExpr>();
    callee->name = "parseNumber";
    callee->line = 1;
    callExpr->callee = callee;
    
    auto arg = std::make_shared<AST::LiteralExpr>();
    arg->value = std::string("123");
    arg->line = 1;
    callExpr->arguments.push_back(arg);
    
    auto fallibleExpr = std::make_shared<AST::FallibleExpr>();
    fallibleExpr->expression = callExpr;
    fallibleExpr->line = 1;
    
    // Test 3: ErrorConstructExpr with multiple arguments
    auto errorExpr = std::make_shared<AST::ErrorConstructExpr>();
    errorExpr->errorType = "ValidationError";
    errorExpr->line = 1;
    
    auto errorMsg = std::make_shared<AST::LiteralExpr>();
    errorMsg->value = std::string("Invalid input");
    errorMsg->line = 1;
    
    auto errorCode = std::make_shared<AST::LiteralExpr>();
    errorCode->value = 400;
    errorCode->line = 1;
    
    errorExpr->arguments.push_back(errorMsg);
    errorExpr->arguments.push_back(errorCode);
    
    // Test 4: OkConstructExpr with complex value
    auto binaryExpr = std::make_shared<AST::BinaryExpr>();
    binaryExpr->left = std::make_shared<AST::LiteralExpr>();
    std::static_pointer_cast<AST::LiteralExpr>(binaryExpr->left)->value = 10;
    binaryExpr->left->line = 1;
    
    binaryExpr->op = TokenType::PLUS;
    
    binaryExpr->right = std::make_shared<AST::LiteralExpr>();
    std::static_pointer_cast<AST::LiteralExpr>(binaryExpr->right)->value = 5;
    binaryExpr->right->line = 1;
    binaryExpr->line = 1;
    
    auto okExpr = std::make_shared<AST::OkConstructExpr>();
    okExpr->value = binaryExpr;
    okExpr->line = 1;
    
    // Validate all constructions
    assert(fallibleInt.isFallible == true);
    assert(fallibleInt.errorTypes.empty());
    
    assert(specificErrorType.isFallible == true);
    assert(specificErrorType.errorTypes.size() == 2);
    assert(specificErrorType.errorTypes[0] == "ParseError");
    assert(specificErrorType.errorTypes[1] == "ValidationError");
    
    assert(fallibleExpr->expression != nullptr);
    auto extractedCall = std::dynamic_pointer_cast<AST::CallExpr>(fallibleExpr->expression);
    assert(extractedCall != nullptr);
    assert(extractedCall->arguments.size() == 1);
    
    assert(errorExpr->errorType == "ValidationError");
    assert(errorExpr->arguments.size() == 2);
    
    assert(okExpr->value != nullptr);
    auto extractedBinary = std::dynamic_pointer_cast<AST::BinaryExpr>(okExpr->value);
    assert(extractedBinary != nullptr);
    assert(extractedBinary->op == TokenType::PLUS);
    
    std::cout << "PASSED" << std::endl;
}

void test_error_tokens_integration() {
    std::cout << "Running test: Error Tokens Integration... ";
    
    // Test that the scanner properly recognizes error handling syntax
    Scanner scanner("err(ParseError) ok(result) someFunction()?");
    auto tokens = scanner.scanTokens();
    
    // Expected tokens: ERR, LEFT_PAREN, IDENTIFIER, RIGHT_PAREN, OK, LEFT_PAREN, IDENTIFIER, RIGHT_PAREN, IDENTIFIER, LEFT_PAREN, RIGHT_PAREN, QUESTION, EOF_TOKEN
    assert(tokens.size() == 13);
    assert(tokens[0].type == TokenType::ERR);
    assert(tokens[0].lexeme == "err");
    assert(tokens[4].type == TokenType::OK);
    assert(tokens[4].lexeme == "ok");
    assert(tokens[11].type == TokenType::QUESTION);
    assert(tokens[11].lexeme == "?");
    
    std::cout << "PASSED" << std::endl;
}

void test_nested_error_expressions() {
    std::cout << "Running test: Nested Error Expressions... ";
    
    // Test nested fallible expressions: someFunction()?.anotherFunction()?
    auto innerCall = std::make_shared<AST::CallExpr>();
    innerCall->callee = std::make_shared<AST::VariableExpr>();
    std::static_pointer_cast<AST::VariableExpr>(innerCall->callee)->name = "someFunction";
    innerCall->line = 1;
    
    auto innerFallible = std::make_shared<AST::FallibleExpr>();
    innerFallible->expression = innerCall;
    innerFallible->line = 1;
    
    auto memberAccess = std::make_shared<AST::MemberExpr>();
    memberAccess->object = innerFallible;
    memberAccess->name = "anotherFunction";
    memberAccess->line = 1;
    
    auto outerCall = std::make_shared<AST::CallExpr>();
    outerCall->callee = memberAccess;
    outerCall->line = 1;
    
    auto outerFallible = std::make_shared<AST::FallibleExpr>();
    outerFallible->expression = outerCall;
    outerFallible->line = 1;
    
    // Validate the nested structure
    assert(outerFallible->expression != nullptr);
    auto extractedCall = std::dynamic_pointer_cast<AST::CallExpr>(outerFallible->expression);
    assert(extractedCall != nullptr);
    
    auto extractedMember = std::dynamic_pointer_cast<AST::MemberExpr>(extractedCall->callee);
    assert(extractedMember != nullptr);
    assert(extractedMember->name == "anotherFunction");
    
    auto extractedInnerFallible = std::dynamic_pointer_cast<AST::FallibleExpr>(extractedMember->object);
    assert(extractedInnerFallible != nullptr);
    
    std::cout << "PASSED" << std::endl;
}

int main() {
    test_complete_error_ast_integration();
    test_error_tokens_integration();
    test_nested_error_expressions();
    
    std::cout << "\nAll comprehensive error handling AST tests passed!" << std::endl;
    return 0;
}