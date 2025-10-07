#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "src/frontend/cst_parser.hh"
#include "src/frontend/cst_printer.hh"
#include "src/frontend/ast_builder.hh"
#include "src/error/console_formatter.hh"

class CSTTestRunner {
private:
    int totalTests = 0;
    int passedTests = 0;
    int failedTests = 0;
    
public:
    void runTest(const std::string& filePath) {
        totalTests++;
        std::cout << "\n=== Testing: " << filePath << " ===\n";
        
        try {
            // Read source file
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cout << "❌ FAIL: Could not open file\n";
                failedTests++;
                return;
            }
            
            std::string source((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
            file.close();
            
            // Test CST parsing
            CSTConfig config;
            config.preserveWhitespace = true;
            config.preserveComments = true;
            config.enableErrorRecovery = true;
            
            CSTParser parser(source, config);
            auto parseResult = parser.parse();
            
            std::cout << "CST Parse Result:\n";
            std::cout << "  - Success: " << (parseResult.success ? "Yes" : "No") << "\n";
            std::cout << "  - Errors: " << parseResult.errors.size() << "\n";
            std::cout << "  - CST Root: " << (parseResult.cst ? "Created" : "None") << "\n";
            
            // Print errors if any
            if (!parseResult.errors.empty()) {
                std::cout << "\nErrors found:\n";
                for (const auto& error : parseResult.errors) {
                    std::cout << "  Line " << error.line << ": " << error.message << "\n";
                }
            }
            
            // Test AST building if CST was created
            if (parseResult.cst) {
                std::cout << "\nTesting AST conversion...\n";
                ASTBuilder builder;
                auto ast = builder.buildAST(parseResult.cst);
                std::cout << "  - AST Created: " << (ast ? "Yes" : "No") << "\n";
                
                if (ast) {
                    std::cout << "  - AST Type: " << ast->getTypeName() << "\n";
                }
            }
            
            // Test round-trip (CST -> source reconstruction)
            if (parseResult.cst) {
                std::cout << "\nTesting round-trip reconstruction...\n";
                CSTConfig printConfig;
                printConfig.preserveWhitespace = true;
                printConfig.preserveComments = true;
                
                CSTPrinter printer(printConfig);
                std::string reconstructed = printer.print(parseResult.cst);
                
                bool roundTripSuccess = (reconstructed == source);
                std::cout << "  - Round-trip: " << (roundTripSuccess ? "✓ PASS" : "❌ FAIL") << "\n";
                
                if (!roundTripSuccess) {
                    std::cout << "  - Original length: " << source.length() << "\n";
                    std::cout << "  - Reconstructed length: " << reconstructed.length() << "\n";
                }
            }
            
            // Determine overall test result
            bool testPassed = parseResult.success || parseResult.cst != nullptr;
            if (testPassed) {
                std::cout << "\n✓ PASS: CST parsing completed\n";
                passedTests++;
            } else {
                std::cout << "\n❌ FAIL: CST parsing failed\n";
                failedTests++;
            }
            
        } catch (const std::exception& e) {
            std::cout << "❌ FAIL: Exception - " << e.what() << "\n";
            failedTests++;
        }
    }
    
    void runDirectory(const std::string& dirPath) {
        std::cout << "\n=== Running CST tests in directory: " << dirPath << " ===\n";
        
        try {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(dirPath)) {
                if (entry.is_regular_file() && entry.path().extension() == ".lm") {
                    runTest(entry.path().string());
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Error scanning directory: " << e.what() << "\n";
        }
    }
    
    void printSummary() {
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "CST Test Summary:\n";
        std::cout << "  Total tests: " << totalTests << "\n";
        std::cout << "  Passed: " << passedTests << "\n";
        std::cout << "  Failed: " << failedTests << "\n";
        std::cout << "  Success rate: " << (totalTests > 0 ? (passedTests * 100 / totalTests) : 0) << "%\n";
        std::cout << std::string(50, '=') << "\n";
    }
};

int main(int argc, char* argv[]) {
    std::cout << "=== CST Parser Test Runner ===\n";
    
    CSTTestRunner runner;
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file_or_directory>\n";
        std::cout << "Examples:\n";
        std::cout << "  " << argv[0] << " tests/basic/variables.lm\n";
        std::cout << "  " << argv[0] << " tests/basic/\n";
        std::cout << "  " << argv[0] << " tests/\n";
        return 1;
    }
    
    std::string path = argv[1];
    
    if (std::filesystem::is_directory(path)) {
        runner.runDirectory(path);
    } else if (std::filesystem::is_regular_file(path)) {
        runner.runTest(path);
    } else {
        std::cout << "Error: Path does not exist or is not accessible: " << path << "\n";
        return 1;
    }
    
    runner.printSummary();
    return 0;
}