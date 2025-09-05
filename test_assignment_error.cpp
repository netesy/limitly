#include <iostream>
#include "src/backend/value.hh"

int main() {
    std::cout << "Testing assignment operator..." << std::endl;
    
    try {
        std::cout << "Creating success value..." << std::endl;
        auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
        
        std::cout << "Creating original ErrorUnion..." << std::endl;
        ErrorUnion original(successValue);
        
        std::cout << "Creating error for assignment target..." << std::endl;
        ErrorValue errorValue("TestError", "Test message");
        ErrorUnion assigned(errorValue);  // Start with error
        
        std::cout << "Before assignment - assigned is error: " << assigned.isError() << std::endl;
        
        std::cout << "About to perform assignment..." << std::endl;
        std::cout.flush();
        
        assigned = original;  // This might be the problem
        
        std::cout << "Assignment completed!" << std::endl;
        std::cout << "After assignment - assigned is success: " << assigned.isSuccess() << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown exception caught" << std::endl;
        return 1;
    }
}