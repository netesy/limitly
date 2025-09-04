#include "../../src/backend/value.hh"
#include "../../src/backend/types.hh"
#include "../../src/backend/memory.hh"
#include <cassert>
#include <iostream>

int main() {
    try {
        std::cout << "Testing basic ErrorValue creation..." << std::endl;
        
        // Test basic error value creation
        ErrorValue basicError("DivisionByZero", "Cannot divide by zero");
        assert(basicError.errorType == "DivisionByZero");
        assert(basicError.message == "Cannot divide by zero");
        
        std::cout << "✓ Basic ErrorValue creation test passed" << std::endl;
        
        std::cout << "Testing ErrorUnion success case..." << std::endl;
        
        MemoryManager<> memManager;
        MemoryManager<>::Region region(memManager);
        TypeSystem typeSystem(memManager, region);
        
        // Test success ErrorUnion
        auto successValue = typeSystem.createValue(typeSystem.INT_TYPE);
        successValue->data = int32_t(42);
        
        ErrorUnion successUnion = ErrorUnion::success(successValue);
        assert(successUnion.isSuccess());
        assert(!successUnion.isError());
        
        std::cout << "✓ ErrorUnion success test passed" << std::endl;
        
        std::cout << "Testing ErrorUnion error case..." << std::endl;
        
        // Test error ErrorUnion
        ErrorUnion errorUnion = ErrorUnion::error("TestError", "Test message");
        assert(!errorUnion.isSuccess());
        assert(errorUnion.isError());
        assert(errorUnion.getErrorType() == "TestError");
        assert(errorUnion.getErrorMessage() == "Test message");
        
        std::cout << "✓ ErrorUnion error test passed" << std::endl;
        
        std::cout << "\n✅ All simple error value tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}