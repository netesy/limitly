#include <iostream>
#include <cassert>
#include <memory>
#include "src/backend/value.hh"

int main() {
    std::cout << "Testing basic error value functionality..." << std::endl;
    
    try {
        // Test 1: Basic ErrorValue construction
        ErrorValue error1("TestError", "Test message");
        assert(error1.errorType == "TestError");
        assert(error1.message == "Test message");
        std::cout << "✓ Basic ErrorValue construction works" << std::endl;
        
        // Test 2: ErrorValue toString
        std::string errorStr = error1.toString();
        assert(errorStr.find("TestError") != std::string::npos);
        std::cout << "✓ ErrorValue toString works: " << errorStr << std::endl;
        
        // Test 3: ErrorUnion with success
        auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
        ErrorUnion successUnion(successValue);
        assert(successUnion.isSuccess());
        assert(!successUnion.isError());
        std::cout << "✓ ErrorUnion success construction works" << std::endl;
        
        // Test 4: ErrorUnion with error
        ErrorUnion errorUnion("TestError", "Test message");
        assert(errorUnion.isError());
        assert(!errorUnion.isSuccess());
        assert(errorUnion.getErrorType() == "TestError");
        std::cout << "✓ ErrorUnion error construction works" << std::endl;
        
        // Test 5: ErrorUtils functions
        auto error = ErrorUtils::createError("UtilError", "Util message");
        assert(ErrorUtils::isError(error));
        assert(ErrorUtils::getErrorType(error) == "UtilError");
        std::cout << "✓ ErrorUtils functions work" << std::endl;
        
        // Test 6: Built-in error creation
        auto divError = ErrorUtils::createDivisionByZeroError();
        assert(ErrorUtils::getErrorType(divError) == "DivisionByZero");
        std::cout << "✓ Built-in error creation works" << std::endl;
        
        std::cout << "\n🎉 All basic error value tests passed!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}