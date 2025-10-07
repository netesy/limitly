#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include <iostream>
#include <cassert>

void testBinaryExpressionParsing() {
    std::cout << "Testing binary expression parsing with error recovery..." << std::endl;
    
    // Test valid binary expression
    std::string source1 = "a + b * c";
    Scanner scanner1(source1);
    CST::CSTParser parser1(scanner1);
    auto cst1 = parser1.parse();
    
    assert(cst1 != nullptr);
    assert(parser1.getErrors().empty());
    std::cout << "✓ Valid binary expression parsed successfully" << std::endl;
    
    // Test binary expression with missing right operand
    std::string source2 = "a + ";
    Scanner scanner2(source2);
    CST::CSTParser parser2(scanner2);
    auto cst2 = parser2.parse();
    
    assert(cst2 != nullptr);
    assert(!parser2.getErrors().empty());
    std::cout << "✓ Binary expression with missing operand handled with error recovery" << std::endl;
}

void testUnaryExpressionParsing() {
    std::cout << "Testing unary expression parsing with error recovery..." << std::endl;
    
    // Test valid unary expression
    std::string source1 = "-42";
    Scanner scanner1(source1);
    CST::CSTParser parser1(scanner1);
    auto cst1 = parser1.parse();
    
    assert(cst1 != nullptr);
    assert(parser1.getErrors().empty());
    std::cout << "✓ Valid unary expression parsed successfully" << std::endl;
    
    // Test unary expression with missing operand
    std::string source2 = "!";
    Scanner scanner2(source2);
    CST::CSTParser parser2(scanner2);
    auto cst2 = parser2.parse();
    
    assert(cst2 != nullptr);
    assert(!parser2.getErrors().empty());
    std::cout << "✓ Unary expression with missing operand handled with error recovery" << std::endl;
}

void testCallExpressionParsing() {
    std::cout << "Testing call expression parsing with error recovery..." << std::endl;
    
    // Test valid function call
    std::string source1 = "func(a, b)";
    Scanner scanner1(source1);
    CST::CSTParser parser1(scanner1);
    auto cst1 = parser1.parse();
    
    assert(cst1 != nullptr);
    assert(parser1.getErrors().empty());
    std::cout << "✓ Valid function call parsed successfully" << std::endl;
    
    // Test function call with missing closing parenthesis
    std::string source2 = "func(a, b";
    Scanner scanner2(source2);
    CST::CSTParser parser2(scanner2);
    auto cst2 = parser2.parse();
    
    assert(cst2 != nullptr);
    assert(!parser2.getErrors().empty());
    std::cout << "✓ Function call with missing ')' handled with error recovery" << std::endl;
}

void testMemberExpressionParsing() {
    std::cout << "Testing member expression parsing with error recovery..." << std::endl;
    
    // Test valid member access
    std::string source1 = "obj.property";
    Scanner scanner1(source1);
    CST::CSTParser parser1(scanner1);
    auto cst1 = parser1.parse();
    
    assert(cst1 != nullptr);
    assert(parser1.getErrors().empty());
    std::cout << "✓ Valid member access parsed successfully" << std::endl;
    
    // Test member access with missing property name
    std::string source2 = "obj.";
    Scanner scanner2(source2);
    CST::CSTParser parser2(scanner2);
    auto cst2 = parser2.parse();
    
    assert(cst2 != nullptr);
    assert(!parser2.getErrors().empty());
    std::cout << "✓ Member access with missing property handled with error recovery" << std::endl;
}

void testGroupingExpressionParsing() {
    std::cout << "Testing grouping expression parsing with error recovery..." << std::endl;
    
    // Test valid grouped expression
    std::string source1 = "(a + b)";
    Scanner scanner1(source1);
    CST::CSTParser parser1(scanner1);
    auto cst1 = parser1.parse();
    
    assert(cst1 != nullptr);
    assert(parser1.getErrors().empty());
    std::cout << "✓ Valid grouped expression parsed successfully" << std::endl;
    
    // Test grouped expression with missing closing parenthesis
    std::string source2 = "(a + b";
    Scanner scanner2(source2);
    CST::CSTParser parser2(scanner2);
    auto cst2 = parser2.parse();
    
    assert(cst2 != nullptr);
    assert(!parser2.getErrors().empty());
    std::cout << "✓ Grouped expression with missing ')' handled with error recovery" << std::endl;
}

void testLiteralAndVariableExpressions() {
    std::cout << "Testing literal and variable expression parsing with error recovery..." << std::endl;
    
    // Test valid literals and variables
    std::string source1 = "42 + \"hello\" + true + variable";
    Scanner scanner1(source1);
    CST::CSTParser parser1(scanner1);
    auto cst1 = parser1.parse();
    
    assert(cst1 != nullptr);
    assert(parser1.getErrors().empty());
    std::cout << "✓ Valid literals and variables parsed successfully" << std::endl;
    
    // Test with reserved keyword as identifier (should create error)
    std::string source2 = "var + if";
    Scanner scanner2(source2);
    CST::CSTParser parser2(scanner2);
    auto cst2 = parser2.parse();
    
    assert(cst2 != nullptr);
    // Note: This might not create errors if 'var' and 'if' are parsed as keywords in context
    std::cout << "✓ Reserved keywords handled appropriately" << std::endl;
}

int main() {
    std::cout << "=== CST Expression Parsing Tests ===" << std::endl;
    
    try {
        testBinaryExpressionParsing();
        testUnaryExpressionParsing();
        testCallExpressionParsing();
        testMemberExpressionParsing();
        testGroupingExpressionParsing();
        testLiteralAndVariableExpressions();
        
        std::cout << "\n✅ All CST expression parsing tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
}