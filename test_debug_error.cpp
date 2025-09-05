#include <iostream>
#include "src/backend/value.hh"

int main() {
    std::cout << "Debug test starting..." << std::endl;
    
    try {
        std::cout << "Creating success value..." << std::endl;
        auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
        std::cout << "Success value created" << std::endl;
        
        std::cout << "Creating ErrorUnion with success..." << std::endl;
        ErrorUnion original(successValue);
        std::cout << "ErrorUnion created, is success: " << original.isSuccess() << std::endl;
        
        std::cout << "About to call copy constructor..." << std::endl;
        std::cout.flush();  // Force output
        
        ErrorUnion copied(original);
        
        std::cout << "Copy constructor completed!" << std::endl;
        std::cout << "Copied is success: " << copied.isSuccess() << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown exception caught" << std::endl;
        return 1;
    }
}