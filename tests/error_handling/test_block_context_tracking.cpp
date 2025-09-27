/**
 * Unit tests for block context tracking system
 * Tests the enhanced error message generation for unclosed constructs
 */

#include "../../src/frontend/scanner.hh"
#include "../../src/frontend/parser.hh"
#include <iostream>
#include <cassert>

class BlockContextTests {
public:
    static void runAllTests() {
        std::cout << "Running Block Context Tracking Tests...\n" << std::endl;
        
        testUnclosedFunction();
        testUnclosedIfStatement();
        testUnclosedWhileLoop();
        testUnclosedForLoop();
        testUnclosedClass();
        testNestedBlocks();
        testProperlyClosedBlocks();
        testBlockCorrelation();
        
        std::cout << "\n✅ All Block Context Tracking Tests Passed!" << std::endl;
    }

private:
    static void testUnclosedFunction() {
        std::cout << "Test: Unclosed Function Block" << std::endl;
        
        std::string code = R"(
fn testFunction() {
    var x = 5;
    print(x);
)";
        
        Scanner scanner(code);
        scanner.scanTokens();
        Parser parser(scanner);
        auto ast = parser.parse();
        
        assert(parser.hadError());
        
        const auto& errors = parser.getErrors();
        assert(!errors.empty());
        
        bool foundFunctionContext = false;
        for (const auto& error : errors) {
            if (error.message.find("Unterminated function") != std::string::npos) {
                foundFunctionContext = true;
                break;
            }
        }
        
        assert(foundFunctionContext);
        std::cout << "✓ Correctly identified unterminated function\n" << std::endl;
    }
    
    static void testUnclosedIfStatement() {
        std::cout << "Test: Unclosed If Statement" << std::endl;
        
        std::string code = R"(
if (true) {
    print("hello");
)";
        
        Scanner scanner(code);
        scanner.scanTokens();
        Parser parser(scanner);
        auto ast = parser.parse();
        
        assert(parser.hadError());
        
        const auto& errors = parser.getErrors();
        assert(!errors.empty());
        
        bool foundIfContext = false;
        for (const auto& error : errors) {
            if (error.message.find("Unterminated if") != std::string::npos) {
                foundIfContext = true;
                break;
            }
        }
        
        assert(foundIfContext);
        std::cout << "✓ Correctly identified unterminated if statement\n" << std::endl;
    }
    
    static void testUnclosedWhileLoop() {
        std::cout << "Test: Unclosed While Loop" << std::endl;
        
        std::string code = R"(
while (true) {
    print("loop");
)";
        
        Scanner scanner(code);
        scanner.scanTokens();
        Parser parser(scanner);
        auto ast = parser.parse();
        
        assert(parser.hadError());
        
        const auto& errors = parser.getErrors();
        assert(!errors.empty());
        
        bool foundWhileContext = false;
        for (const auto& error : errors) {
            if (error.message.find("Unterminated while") != std::string::npos) {
                foundWhileContext = true;
                break;
            }
        }
        
        assert(foundWhileContext);
        std::cout << "✓ Correctly identified unterminated while loop\n" << std::endl;
    }
    
    static void testUnclosedForLoop() {
        std::cout << "Test: Unclosed For Loop" << std::endl;
        
        std::string code = R"(
for (var i = 0; i < 10; i++) {
    print(i);
)";
        
        Scanner scanner(code);
        scanner.scanTokens();
        Parser parser(scanner);
        auto ast = parser.parse();
        
        assert(parser.hadError());
        
        const auto& errors = parser.getErrors();
        assert(!errors.empty());
        
        bool foundForContext = false;
        for (const auto& error : errors) {
            if (error.message.find("Unterminated for") != std::string::npos) {
                foundForContext = true;
                break;
            }
        }
        
        assert(foundForContext);
        std::cout << "✓ Correctly identified unterminated for loop\n" << std::endl;
    }
    
    static void testUnclosedClass() {
        std::cout << "Test: Unclosed Class" << std::endl;
        
        std::string code = R"(
class TestClass {
    var field: int;
    
    fn method() {
        print("method");
    }
)";
        
        Scanner scanner(code);
        scanner.scanTokens();
        Parser parser(scanner);
        auto ast = parser.parse();
        
        assert(parser.hadError());
        
        const auto& errors = parser.getErrors();
        assert(!errors.empty());
        
        bool foundClassContext = false;
        for (const auto& error : errors) {
            if (error.message.find("Unterminated class") != std::string::npos) {
                foundClassContext = true;
                break;
            }
        }
        
        assert(foundClassContext);
        std::cout << "✓ Correctly identified unterminated class\n" << std::endl;
    }
    
    static void testNestedBlocks() {
        std::cout << "Test: Nested Blocks - Most Specific Context" << std::endl;
        
        std::string code = R"(
fn testFunction() {
    if (true) {
        print("hello");
    // Missing closing brace for if - should report if, not function
)";
        
        Scanner scanner(code);
        scanner.scanTokens();
        Parser parser(scanner);
        auto ast = parser.parse();
        
        assert(parser.hadError());
        
        const auto& errors = parser.getErrors();
        assert(!errors.empty());
        
        // Should report the most specific unclosed block (if, not function)
        bool foundIfContext = false;
        for (const auto& error : errors) {
            if (error.message.find("Unterminated if") != std::string::npos) {
                foundIfContext = true;
                break;
            }
        }
        
        assert(foundIfContext);
        std::cout << "✓ Correctly identified most specific unterminated block (if)\n" << std::endl;
    }
    
    static void testProperlyClosedBlocks() {
        std::cout << "Test: Properly Closed Blocks (No False Positives)" << std::endl;
        
        std::string code = R"(
fn properFunction() {
    if (true) {
        print("hello");
    }
    while (false) {
        print("loop");
    }
    for (var i = 0; i < 5; i++) {
        print(i);
    }
}
)";
        
        Scanner scanner(code);
        scanner.scanTokens();
        Parser parser(scanner);
        auto ast = parser.parse();
        
        assert(!parser.hadError());
        std::cout << "✓ No false positives for properly closed blocks\n" << std::endl;
    }
    
    static void testBlockCorrelation() {
        std::cout << "Test: Block Error Correlation with Opening Counterparts" << std::endl;
        
        std::string code = R"(
fn testFunction() {
    var x = 5;
)";
        
        Scanner scanner(code);
        scanner.scanTokens();
        Parser parser(scanner);
        auto ast = parser.parse();
        
        assert(parser.hadError());
        
        const auto& errors = parser.getErrors();
        assert(!errors.empty());
        
        // Check that the error message contains line number correlation
        bool foundLineCorrelation = false;
        for (const auto& error : errors) {
            if (error.message.find("starting at line") != std::string::npos) {
                foundLineCorrelation = true;
                break;
            }
        }
        
        assert(foundLineCorrelation);
        std::cout << "✓ Error correctly correlates with opening brace location\n" << std::endl;
    }
};

int main() {
    BlockContextTests::runAllTests();
    return 0;
}