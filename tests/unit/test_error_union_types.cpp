#include "../../backend/types.hh"
#include "../../backend/memory.hh"
#include <cassert>
#include <iostream>

void testErrorUnionTypeCreation() {
    std::cout << "Testing error union type creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test creating a generic error union (int?)
    auto intErrorUnion = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, {}, true);
    assert(intErrorUnion->tag == TypeTag::ErrorUnion);
    
    auto errorUnionDetails = std::get<ErrorUnionType>(intErrorUnion->extra);
    assert(errorUnionDetails.successType == typeSystem.INT_TYPE);
    assert(errorUnionDetails.isGenericError == true);
    assert(errorUnionDetails.errorTypes.empty());
    
    // Test creating a specific error union (int?DivisionByZero, IndexOutOfBounds)
    std::vector<std::string> specificErrors = {"DivisionByZero", "IndexOutOfBounds"};
    auto specificErrorUnion = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, specificErrors, false);
    
    auto specificDetails = std::get<ErrorUnionType>(specificErrorUnion->extra);
    assert(specificDetails.successType == typeSystem.INT_TYPE);
    assert(specificDetails.isGenericError == false);
    assert(specificDetails.errorTypes.size() == 2);
    assert(specificDetails.errorTypes[0] == "DivisionByZero");
    assert(specificDetails.errorTypes[1] == "IndexOutOfBounds");
    
    std::cout << "✓ Error union type creation tests passed" << std::endl;
}

void testErrorTypeRegistry() {
    std::cout << "Testing error type registry..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test built-in error types are registered
    assert(typeSystem.isErrorType("DivisionByZero"));
    assert(typeSystem.isErrorType("IndexOutOfBounds"));
    assert(typeSystem.isErrorType("NullReference"));
    assert(typeSystem.isErrorType("TypeConversion"));
    assert(typeSystem.isErrorType("IOError"));
    assert(typeSystem.isErrorType("ParseError"));
    assert(typeSystem.isErrorType("NetworkError"));
    
    // Test non-existent error type
    assert(!typeSystem.isErrorType("NonExistentError"));
    
    // Test getting error types
    auto divByZeroType = typeSystem.getErrorType("DivisionByZero");
    assert(divByZeroType != nullptr);
    
    // Test registering custom error type
    auto customErrorType = std::make_shared<Type>(TypeTag::UserDefined);
    typeSystem.registerUserError("CustomError", customErrorType);
    assert(typeSystem.isErrorType("CustomError"));
    assert(typeSystem.getErrorType("CustomError") == customErrorType);
    
    std::cout << "✓ Error type registry tests passed" << std::endl;
}

void testErrorUnionCompatibility() {
    std::cout << "Testing error union type compatibility..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create different error union types
    auto genericIntError = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, {}, true);
    auto specificIntError = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, {"DivisionByZero"}, false);
    auto multipleIntError = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, {"DivisionByZero", "IndexOutOfBounds"}, false);
    auto stringError = typeSystem.createErrorUnionType(typeSystem.STRING_TYPE, {"ParseError"}, false);
    
    // Test compatibility between error unions
    assert(typeSystem.isCompatible(specificIntError, genericIntError)); // specific -> generic
    assert(typeSystem.isCompatible(multipleIntError, genericIntError)); // multiple -> generic
    assert(!typeSystem.isCompatible(genericIntError, specificIntError)); // generic -> specific (not allowed)
    assert(typeSystem.isCompatible(specificIntError, multipleIntError)); // subset -> superset
    assert(!typeSystem.isCompatible(multipleIntError, specificIntError)); // superset -> subset (not allowed)
    assert(!typeSystem.isCompatible(specificIntError, stringError)); // different success types
    
    // Test compatibility from success type to error union
    assert(typeSystem.isCompatible(typeSystem.INT_TYPE, genericIntError));
    assert(typeSystem.isCompatible(typeSystem.INT_TYPE, specificIntError));
    assert(!typeSystem.isCompatible(typeSystem.STRING_TYPE, specificIntError));
    
    std::cout << "✓ Error union compatibility tests passed" << std::endl;
}

void testErrorValueCreation() {
    std::cout << "Testing error value creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create error value
    ErrorValue errorVal("DivisionByZero", "Cannot divide by zero", {}, 42);
    assert(errorVal.errorType == "DivisionByZero");
    assert(errorVal.message == "Cannot divide by zero");
    assert(errorVal.arguments.empty());
    assert(errorVal.sourceLocation == 42);
    
    // Test error value toString
    std::string errorStr = errorVal.toString();
    assert(errorStr.find("DivisionByZero") != std::string::npos);
    assert(errorStr.find("Cannot divide by zero") != std::string::npos);
    
    // Create error value with arguments
    auto arg1 = typeSystem.createValue(typeSystem.INT_TYPE);
    arg1->data = int32_t(10);
    auto arg2 = typeSystem.createValue(typeSystem.STRING_TYPE);
    arg2->data = std::string("test");
    
    ErrorValue errorWithArgs("CustomError", "Error with args", {arg1, arg2}, 0);
    assert(errorWithArgs.arguments.size() == 2);
    
    std::cout << "✓ Error value creation tests passed" << std::endl;
}

void testErrorUnionValueCreation() {
    std::cout << "Testing error union value creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create error union type
    auto intErrorUnion = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, {"DivisionByZero"}, false);
    
    // Create success value for error union (should default to success)
    auto successValue = typeSystem.createValue(intErrorUnion);
    assert(successValue->type == intErrorUnion);
    
    // The value should contain the default value of the success type (int32_t(0))
    assert(std::holds_alternative<int32_t>(successValue->data));
    assert(std::get<int32_t>(successValue->data) == 0);
    
    std::cout << "✓ Error union value creation tests passed" << std::endl;
}

int main() {
    try {
        testErrorUnionTypeCreation();
        testErrorTypeRegistry();
        testErrorUnionCompatibility();
        testErrorValueCreation();
        testErrorUnionValueCreation();
        
        std::cout << "\n✅ All error union type tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}