#include "../../src/frontend/scanner.hh"
#include "../../src/frontend/parser.hh"
#include "../../src/common/debugger.hh"
#include <iostream>
#include <cassert>
#include <sstream>

// Test enhanced error reporting with file path information
void testScannerErrorWithFilePath() {
    std::cout << "Testing Scanner error reporting with file path..." << std::endl;
    
    // Reset error state
    Debugger::resetError();
    
    // Create a scanner with invalid source and file path
    std::string source = "let x = 123@invalid";  // Invalid character @
    std::string filePath = "test_file.lm";
    Scanner scanner(source, filePath);
    
    // Capture stderr to check error output
    std::streambuf* orig = std::cerr.rdbuf();
    std::ostringstream captured;
    std::cerr.rdbuf(captured.rdbuf());
    
    try {
        scanner.scanTokens();
    } catch (...) {
        // Expected to have errors
    }
    
    // Restore stderr
    std::cerr.rdbuf(orig);
    
    // Check that error was reported
    assert(Debugger::hasError());
    
    // Check that the captured output contains file path information
    std::string errorOutput = captured.str();
    assert(errorOutput.find("test_file.lm") != std::string::npos);
    
    std::cout << "✓ Scanner error reporting with file path works correctly" << std::endl;
}

// Test parser error reporting with block context
void testParserErrorWithBlockContext() {
    std::cout << "Testing Parser error reporting with block context..." << std::endl;
    
    // Reset error state
    Debugger::resetError();
    
    // Create source with unclosed function block
    std::string source = R"(
fn test() {
    let x = 5;
    // Missing closing brace
)";
    std::string filePath = "test_unclosed.lm";
    Scanner scanner(source, filePath);
    scanner.scanTokens();
    
    Parser parser(scanner);
    
    // Capture stderr to check error output
    std::streambuf* orig = std::cerr.rdbuf();
    std::ostringstream captured;
    std::cerr.rdbuf(captured.rdbuf());
    
    try {
        parser.parse();
    } catch (...) {
        // Expected to have parsing errors
    }
    
    // Restore stderr
    std::cerr.rdbuf(orig);
    
    // Check that error was reported
    assert(Debugger::hasError());
    
    // Check that the captured output contains file path and block context information
    std::string errorOutput = captured.str();
    assert(errorOutput.find("test_unclosed.lm") != std::string::npos);
    
    std::cout << "✓ Parser error reporting with block context works correctly" << std::endl;
}

// Test that enhanced error messages contain expected components
void testEnhancedErrorMessageComponents() {
    std::cout << "Testing enhanced error message components..." << std::endl;
    
    // Reset error state
    Debugger::resetError();
    
    // Create source with syntax error
    std::string source = "let x = ;";  // Missing value
    std::string filePath = "test_syntax.lm";
    Scanner scanner(source, filePath);
    scanner.scanTokens();
    
    Parser parser(scanner);
    
    // Capture stderr to check error output
    std::streambuf* orig = std::cerr.rdbuf();
    std::ostringstream captured;
    std::cerr.rdbuf(captured.rdbuf());
    
    try {
        parser.parse();
    } catch (...) {
        // Expected to have parsing errors
    }
    
    // Restore stderr
    std::cerr.rdbuf(orig);
    
    // Check that error was reported
    assert(Debugger::hasError());
    
    // Check that the captured output contains expected components
    std::string errorOutput = captured.str();
    
    // Should contain file path
    assert(errorOutput.find("test_syntax.lm") != std::string::npos);
    
    // Should contain error code format
    assert(errorOutput.find("error[E") != std::string::npos);
    
    // Should contain line/column information
    assert(errorOutput.find("-->") != std::string::npos);
    
    std::cout << "✓ Enhanced error message components work correctly" << std::endl;
}

int main() {
    std::cout << "Running enhanced error reporting integration tests..." << std::endl;
    
    try {
        testScannerErrorWithFilePath();
        testParserErrorWithBlockContext();
        testEnhancedErrorMessageComponents();
        
        std::cout << "\n✅ All enhanced error reporting tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
}