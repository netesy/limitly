#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include <iostream>

int main() {
    // Test various expression parsing scenarios
    std::vector<std::string> testCases = {
        "x + y * z",           // Binary expressions with precedence
        "-x",                  // Unary expression
        "fn_name(a, b, c)",    // Function call
        "obj.property",        // Member access
        "(x + y) * z",         // Grouping expression
        "arr[index]",          // Index expression
        "42",                  // Literal
        "variable",            // Variable
        
        // Error recovery test cases
        "x +",                 // Missing right operand
        "-",                   // Missing unary operand
        "fn_name(",            // Missing closing paren in call
        "obj.",                // Missing member name
        "(x + y",              // Missing closing paren in grouping
        "",                    // Empty expression
    };
    
    for (const auto& testCase : testCases) {
        std::cout << "\n=== Testing: \"" << testCase << "\" ===" << std::endl;
        
        try {
            Scanner scanner(testCase);
            CST::CSTParser parser(scanner);
            
            auto cst = parser.parse();
            
            if (parser.hasErrors()) {
                std::cout << "Errors found:" << std::endl;
                for (const auto& error : parser.getErrors()) {
                    std::cout << "  - " << error.message << std::endl;
                }
            } else {
                std::cout << "Parsed successfully!" << std::endl;
            }
            
            if (cst) {
                std::cout << "CST created with kind: " << static_cast<int>(cst->kind) << std::endl;
            }
            
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    
    return 0;
}