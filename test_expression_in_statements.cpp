#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include <iostream>

int main() {
    // Test expressions within statement contexts
    std::vector<std::string> testCases = {
        "var x = y + z * w;",           // Binary expressions with precedence
        "var result = -value;",         // Unary expression
        "var output = func(a, b, c);",  // Function call
        "var prop = obj.property;",     // Member access
        "var calc = (x + y) * z;",      // Grouping expression
        "var item = arr[index];",       // Index expression
        "var num = 42;",                // Literal
        "var name = variable;",         // Variable
        
        // Error recovery test cases
        "var bad = x +;",               // Missing right operand
        "var neg = -;",                 // Missing unary operand
        "var call = func(;",            // Missing closing paren in call
        "var member = obj.;",           // Missing member name
        "var group = (x + y;",          // Missing closing paren in grouping
    };
    
    for (const auto& testCase : testCases) {
        std::cout << "\n=== Testing: \"" << testCase << "\" ===" << std::endl;
        
        try {
            Scanner scanner(testCase);
            CST::CSTParser parser(scanner);
            
            auto cst = parser.parse();
            
            if (parser.hasErrors()) {
                std::cout << "Errors found (" << parser.getErrorCount() << "):" << std::endl;
                for (const auto& error : parser.getErrors()) {
                    std::cout << "  - " << error.message << std::endl;
                }
            } else {
                std::cout << "Parsed successfully!" << std::endl;
            }
            
            if (cst) {
                std::cout << "CST created with kind: " << static_cast<int>(cst->kind) 
                         << " (" << cst->children.size() << " children)" << std::endl;
            }
            
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    
    return 0;
}