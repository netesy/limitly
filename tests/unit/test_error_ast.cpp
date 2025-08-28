#include "frontend/ast.hh"
#include <iostream>
#include <cassert>
#include <memory>

void test_fallible_expr_construction() {
    std::cout << "Running test: FallibleExpr Construction... ";
    
    // Create a simple variable expression to wrap
    auto varExpr = std::make_shared<AST::VariableExpr>();
    varExpr->name = "someFunction";
    varExpr->line = 1;
    
    // Create a fallible expression
    auto fallibleExpr = std::make_shared<AST::FallibleExpr>();
    fallibleExpr->expression = varExpr;
    fallibleExpr->elseHandler = nullptr;  // No else handler
    fallibleExpr->elseVariable = "";      // No error variable
    fallibleExpr->line = 1;
    
    // Validate construction
    assert(fallibleExpr->expression != nullptr);
    assert(fallibleExpr->elseHandler == nullptr);
    assert(fallibleExpr->elseVariable.empty());
    
    std::cout << "PASSED" << std::endl;
}

void test_fallible_expr_with_else_handler() {
    std::cout << "Running test: FallibleExpr with Else Handler... ";
    
    // Create a simple variable expression to wrap
    auto varExpr = std::make_shared<AST::VariableExpr>();
    varExpr->name = "fallibleFunction";
    varExpr->line = 1;
    
    // Create an else handler block
    auto elseBlock = std::make_shared<AST::BlockStatement>();
    elseBlock->line = 1;
    
    // Create a fallible expression with else handler
    auto fallibleExpr = std::make_shared<AST::FallibleExpr>();
    fallibleExpr->expression = varExpr;
    fallibleExpr->elseHandler = elseBlock;
    fallibleExpr->elseVariable = "error";
    fallibleExpr->line = 1;
    
    // Validate construction
    assert(fallibleExpr->expression != nullptr);
    assert(fallibleExpr->elseHandler != nullptr);
    assert(fallibleExpr->elseVariable == "error");
    
    std::cout << "PASSED" << std::endl;
}

void test_error_construct_expr() {
    std::cout << "Running test: ErrorConstructExpr Construction... ";
    
    // Create error construction expression
    auto errorExpr = std::make_shared<AST::ErrorConstructExpr>();
    errorExpr->errorType = "DivisionByZero";
    errorExpr->line = 1;
    
    // Add some arguments
    auto arg1 = std::make_shared<AST::LiteralExpr>();
    arg1->value = std::string("Division by zero occurred");
    arg1->line = 1;
    
    auto arg2 = std::make_shared<AST::LiteralExpr>();
    arg2->value = 42;
    arg2->line = 1;
    
    errorExpr->arguments.push_back(arg1);
    errorExpr->arguments.push_back(arg2);
    
    // Validate construction
    assert(errorExpr->errorType == "DivisionByZero");
    assert(errorExpr->arguments.size() == 2);
    assert(errorExpr->arguments[0] != nullptr);
    assert(errorExpr->arguments[1] != nullptr);
    
    std::cout << "PASSED" << std::endl;
}

void test_ok_construct_expr() {
    std::cout << "Running test: OkConstructExpr Construction... ";
    
    // Create success value
    auto valueExpr = std::make_shared<AST::LiteralExpr>();
    valueExpr->value = 100;
    valueExpr->line = 1;
    
    // Create ok construction expression
    auto okExpr = std::make_shared<AST::OkConstructExpr>();
    okExpr->value = valueExpr;
    okExpr->line = 1;
    
    // Validate construction
    assert(okExpr->value != nullptr);
    
    std::cout << "PASSED" << std::endl;
}

void test_type_annotation_error_extensions() {
    std::cout << "Running test: TypeAnnotation Error Extensions... ";
    
    // Test basic fallible type (Type?)
    AST::TypeAnnotation fallibleType;
    fallibleType.typeName = "int";
    fallibleType.isFallible = true;
    fallibleType.isPrimitive = true;
    
    assert(fallibleType.typeName == "int");
    assert(fallibleType.isFallible == true);
    assert(fallibleType.errorTypes.empty());  // Generic error type
    
    // Test specific error types (Type?Error1, Error2)
    AST::TypeAnnotation specificErrorType;
    specificErrorType.typeName = "string";
    specificErrorType.isFallible = true;
    specificErrorType.errorTypes.push_back("ParseError");
    specificErrorType.errorTypes.push_back("ValidationError");
    
    assert(specificErrorType.typeName == "string");
    assert(specificErrorType.isFallible == true);
    assert(specificErrorType.errorTypes.size() == 2);
    assert(specificErrorType.errorTypes[0] == "ParseError");
    assert(specificErrorType.errorTypes[1] == "ValidationError");
    
    std::cout << "PASSED" << std::endl;
}

void test_error_ast_node_inheritance() {
    std::cout << "Running test: Error AST Node Inheritance... ";
    
    // Test that error handling nodes properly inherit from Expression
    auto fallibleExpr = std::make_shared<AST::FallibleExpr>();
    auto errorExpr = std::make_shared<AST::ErrorConstructExpr>();
    auto okExpr = std::make_shared<AST::OkConstructExpr>();
    
    // These should compile and work due to inheritance
    AST::Expression* basePtr1 = fallibleExpr.get();
    AST::Expression* basePtr2 = errorExpr.get();
    AST::Expression* basePtr3 = okExpr.get();
    
    assert(basePtr1 != nullptr);
    assert(basePtr2 != nullptr);
    assert(basePtr3 != nullptr);
    
    std::cout << "PASSED" << std::endl;
}

void test_complex_fallible_expression() {
    std::cout << "Running test: Complex Fallible Expression... ";
    
    // Create a complex expression: someFunction(arg1, arg2)?
    auto funcCall = std::make_shared<AST::CallExpr>();
    funcCall->line = 1;
    
    // Set up the callee
    auto callee = std::make_shared<AST::VariableExpr>();
    callee->name = "someFunction";
    callee->line = 1;
    funcCall->callee = callee;
    
    // Add arguments
    auto arg1 = std::make_shared<AST::LiteralExpr>();
    arg1->value = 10;
    arg1->line = 1;
    
    auto arg2 = std::make_shared<AST::LiteralExpr>();
    arg2->value = std::string("test");
    arg2->line = 1;
    
    funcCall->arguments.push_back(arg1);
    funcCall->arguments.push_back(arg2);
    
    // Wrap in fallible expression
    auto fallibleExpr = std::make_shared<AST::FallibleExpr>();
    fallibleExpr->expression = funcCall;
    fallibleExpr->elseHandler = nullptr;
    fallibleExpr->elseVariable = "";
    fallibleExpr->line = 1;
    
    // Validate the complex structure
    assert(fallibleExpr->expression != nullptr);
    auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(fallibleExpr->expression);
    assert(callExpr != nullptr);
    assert(callExpr->arguments.size() == 2);
    
    std::cout << "PASSED" << std::endl;
}

int main() {
    test_fallible_expr_construction();
    test_fallible_expr_with_else_handler();
    test_error_construct_expr();
    test_ok_construct_expr();
    test_type_annotation_error_extensions();
    test_error_ast_node_inheritance();
    test_complex_fallible_expression();
    
    std::cout << "\nAll error handling AST tests passed!" << std::endl;
    return 0;
}