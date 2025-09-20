#include "../../src/backend/type_checker.hh"
#include "../../src/backend/types.hh"
#include "../../src/backend/memory.hh"
#include "../../src/frontend/parser.hh"
#include "../../src/frontend/scanner.hh"
#include <cassert>
#include <iostream>
#include <sstream>

// Helper function to parse code and return AST
std::shared_ptr<AST::Program> parseCode(const std::string& code) {
    Scanner scanner(code);
    scanner.scanTokens();
    Parser parser(scanner);
    return parser.parse();
}

// Test basic error union type checking
void testErrorUnionTypeChecking() {
    std::cout << "Testing error union type checking..." << std::endl;
    
    MemoryManager<> memoryManager;
    auto region = memoryManager.createRegion();
    TypeSystem typeSystem(memoryManager, region);
    TypeChecker typeChecker(typeSystem);
    
    std::string code = R"(
        fn divide(a: int, b: int): int?DivisionByZero {
            if (b == 0) {
                return err(DivisionByZero);
            }
            return ok(a / b);
        }
    )";
    
    auto program = parseCode(code);
    auto errors = typeChecker.checkProgram(program);
    
    // Should have no errors for valid error union function
    assert(errors.empty());
    std::cout << "✓ Error union type checking passed" << std::endl;
}

// Test unhandled fallible expression detection
void testUnhandledFallibleExpression() {
    std::cout << "Testing unhandled fallible expression detection..." << std::endl;
    
    MemoryManager<> memoryManager;
    auto region = memoryManager.createRegion();
    TypeSystem typeSystem(memoryManager, region);
    TypeChecker typeChecker(typeSystem);
    
    std::string code = R"(
        fn divide(a: int, b: int): int?DivisionByZero {
            return ok(a / b);
        }
        
        fn test(): void {
            divide(10, 2);  // Unhandled fallible expression
        }
    )";
    
    auto program = parseCode(code);
    auto errors = typeChecker.checkProgram(program);
    
    // Should have error for unhandled fallible expression
    assert(!errors.empty());
    bool foundUnhandledError = false;
    for (const auto& error : errors) {
        if (error.message.find("Unhandled fallible expression") != std::string::npos) {
            foundUnhandledError = true;
            break;
        }
    }
    assert(foundUnhandledError);
    std::cout << "✓ Unhandled fallible expression detection passed" << std::endl;
}

// Test error type propagation validation
void testErrorTypePropagation() {
    std::cout << "Testing error type propagation validation..." << std::endl;
    
    MemoryManager<> memoryManager;
    auto region = memoryManager.createRegion();
    TypeSystem typeSystem(memoryManager, region);
    TypeChecker typeChecker(typeSystem);
    
    std::string code = R"(
        fn divide(a: int, b: int): int?DivisionByZero {
            return ok(a / b);
        }
        
        fn incompatiblePropagate(x: int, y: int): int?IndexOutOfBounds {
            var result = divide(x, y)?;  // Incompatible error types
            return ok(result);
        }
    )";
    
    auto program = parseCode(code);
    auto errors = typeChecker.checkProgram(program);
    
    // Should have error for incompatible error type propagation
    assert(!errors.empty());
    bool foundIncompatibleError = false;
    for (const auto& error : errors) {
        if (error.message.find("Error type incompatible") != std::string::npos) {
            foundIncompatibleError = true;
            break;
        }
    }
    assert(foundIncompatibleError);
    std::cout << "✓ Error type propagation validation passed" << std::endl;
}

// Test non-fallible function with ? operator
void testNonFallibleWithPropagation() {
    std::cout << "Testing non-fallible function with ? operator..." << std::endl;
    
    MemoryManager<> memoryManager;
    auto region = memoryManager.createRegion();
    TypeSystem typeSystem(memoryManager, region);
    TypeChecker typeChecker(typeSystem);
    
    std::string code = R"(
        fn divide(a: int, b: int): int?DivisionByZero {
            return ok(a / b);
        }
        
        fn nonFallible(x: int, y: int): int {
            var result = divide(x, y)?;  // Cannot propagate in non-fallible function
            return result;
        }
    )";
    
    auto program = parseCode(code);
    auto errors = typeChecker.checkProgram(program);
    
    // Should have error for using ? in non-fallible function
    assert(!errors.empty());
    bool foundNonFallibleError = false;
    for (const auto& error : errors) {
        if (error.message.find("Cannot propagate error in non-fallible function") != std::string::npos) {
            foundNonFallibleError = true;
            break;
        }
    }
    assert(foundNonFallibleError);
    std::cout << "✓ Non-fallible function with ? operator test passed" << std::endl;
}

// Test function call argument type checking
void testFunctionCallTypeChecking() {
    std::cout << "Testing function call argument type checking..." << std::endl;
    
    MemoryManager<> memoryManager;
    auto region = memoryManager.createRegion();
    TypeSystem typeSystem(memoryManager, region);
    TypeChecker typeChecker(typeSystem);
    
    std::string code = R"(
        fn divide(a: int, b: int): int?DivisionByZero {
            return ok(a / b);
        }
        
        fn test(): void {
            divide("hello", "world");  // Wrong argument types
        }
    )";
    
    auto program = parseCode(code);
    auto errors = typeChecker.checkProgram(program);
    
    // Should have error for wrong argument types
    assert(!errors.empty());
    bool foundArgumentError = false;
    for (const auto& error : errors) {
        if (error.message.find("type mismatch") != std::string::npos) {
            foundArgumentError = true;
            break;
        }
    }
    assert(foundArgumentError);
    std::cout << "✓ Function call argument type checking passed" << std::endl;
}

// Test valid error handling patterns
void testValidErrorHandling() {
    std::cout << "Testing valid error handling patterns..." << std::endl;
    
    MemoryManager<> memoryManager;
    auto region = memoryManager.createRegion();
    TypeSystem typeSystem(memoryManager, region);
    TypeChecker typeChecker(typeSystem);
    
    std::string code = R"(
        fn divide(a: int, b: int): int?DivisionByZero {
            return ok(a / b);
        }
        
        fn safeDivide(x: int, y: int): int?DivisionByZero {
            var result = divide(x, y)?;  // Valid propagation
            return ok(result);
        }
        
        fn handleWithMatch(x: int, y: int): int {
            match divide(x, y) {
                val result => return result;
                err DivisionByZero => return 0;
            }
        }
    )";
    
    auto program = parseCode(code);
    auto errors = typeChecker.checkProgram(program);
    
    // Should have no errors for valid error handling
    assert(errors.empty());
    std::cout << "✓ Valid error handling patterns test passed" << std::endl;
}

int main() {
    std::cout << "Running type checker unit tests..." << std::endl;
    
    try {
        testErrorUnionTypeChecking();
        testUnhandledFallibleExpression();
        testErrorTypePropagation();
        testNonFallibleWithPropagation();
        testFunctionCallTypeChecking();
        testValidErrorHandling();
        
        std::cout << "\n✅ All type checker tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
}