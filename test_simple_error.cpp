#include <iostream>
#include "src/backend/value.hh"

int main() {
    std::cout << "Testing simple error operations..." << std::endl;
    
    try {
        // Test 1: Basic ErrorValue creation
        std::cout << "1. Creating ErrorValue..." << std::endl;
        ErrorValue error("TestError", "Test message");
        std::cout << "   Error type: " << error.errorType << std::endl;
        std::cout << "   Error message: " << error.message << std::endl;
        
        // Test 2: ErrorUnion with success
        std::cout << "2. Creating ErrorUnion with success..." << std::endl;
        auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
        ErrorUnion successUnion(successValue);
        std::cout << "   Is success: " << successUnion.isSuccess() << std::endl;
        
        // Test 3: ErrorUnion with error
        std::cout << "3. Creating ErrorUnion with error..." << std::endl;
        ErrorUnion errorUnion(error);
        std::cout << "   Is error: " << errorUnion.isError() << std::endl;
        
        // Test 4: Copy constructor
        std::cout << "4. Testing copy constructor..." << std::endl;
        ErrorUnion copied(successUnion);
        std::cout << "   Copied is success: " << copied.isSuccess() << std::endl;
        
        // Test 5: Assignment operator
        std::cout << "5. Testing assignment operator..." << std::endl;
        ErrorUnion assigned(errorUnion);  // Initialize with error first
        std::cout << "   Before assignment - is error: " << assigned.isError() << std::endl;
        assigned = successUnion;  // Now assign success
        std::cout << "   After assignment - is success: " << assigned.isSuccess() << std::endl;
        
        std::cout << "All tests completed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }
}