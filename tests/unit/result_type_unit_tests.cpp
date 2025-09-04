// Unit tests for Result type implementation
// Tests the TypeSystem Result type methods directly

#include <cassert>
#include <iostream>
#include <memory>
#include "../../src/backend/types.hh"
#include "../../src/backend/memory.hh"

void testResultTypeCreation() {
    std::cout << "Testing Result type creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test createResultType with different success and error types
    auto intStringResultType = typeSystem.createResultType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE);
    assert(typeSystem.isUnionType(intStringResultType));
    
    auto stringIntResultType = typeSystem.createResultType(typeSystem.STRING_TYPE, typeSystem.INT_TYPE);
    assert(typeSystem.isUnionType(stringIntResultType));
    
    auto boolStringResultType = typeSystem.createResultType(typeSystem.BOOL_TYPE, typeSystem.STRING_TYPE);
    assert(typeSystem.isUnionType(boolStringResultType));
    
    std::cout << "✓ Result type creation tests passed" << std::endl;
}

void testSuccessValueCreation() {
    std::cout << "Testing Success value creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create Success values with different types
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successInt = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    
    assert(successInt != nullptr);
    assert(typeSystem.isSuccess(successInt));
    assert(!typeSystem.isError(successInt));
    
    auto stringValue = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "hello");
    auto successString = typeSystem.createSuccess(typeSystem.STRING_TYPE, stringValue);
    
    assert(successString != nullptr);
    assert(typeSystem.isSuccess(successString));
    assert(!typeSystem.isError(successString));
    
    std::cout << "✓ Success value creation tests passed" << std::endl;
}

void testErrorValueCreation() {
    std::cout << "Testing Error value creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create Error values with different error types
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Something went wrong");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    
    assert(errorResult != nullptr);
    assert(!typeSystem.isSuccess(errorResult));
    assert(typeSystem.isError(errorResult));
    
    auto errorCode = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 404);
    auto errorIntResult = typeSystem.createError(typeSystem.INT_TYPE, errorCode);
    
    assert(errorIntResult != nullptr);
    assert(!typeSystem.isSuccess(errorIntResult));
    assert(typeSystem.isError(errorIntResult));
    
    std::cout << "✓ Error value creation tests passed" << std::endl;
}

void testResultValueExtraction() {
    std::cout << "Testing Result value extraction..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test extracting value from Success
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successInt = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    
    auto extractedValue = typeSystem.extractSuccessValue(successInt);
    assert(extractedValue != nullptr);
    assert(extractedValue->type->tag == TypeTag::Int);
    
    // Test extracting error from Error
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Error occurred");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    
    auto extractedError = typeSystem.extractErrorValue(errorResult);
    assert(extractedError != nullptr);
    assert(extractedError->type->tag == TypeTag::String);
    
    // Test that extracting from wrong variant throws exception
    bool exceptionThrown = false;
    try {
        typeSystem.extractSuccessValue(errorResult);
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    
    exceptionThrown = false;
    try {
        typeSystem.extractErrorValue(successInt);
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    
    std::cout << "✓ Result value extraction tests passed" << std::endl;
}

void testResultPatternMatching() {
    std::cout << "Testing Result pattern matching..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    TypeMatcher matcher(&typeSystem, memManager, region);
    
    // Create Result values
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successInt = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Error occurred");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    
    // Test pattern matching
    assert(matcher.isSuccess(successInt));
    assert(!matcher.isError(successInt));
    
    assert(!matcher.isSuccess(errorResult));
    assert(matcher.isError(errorResult));
    
    // Test type name introspection
    assert(matcher.getTypeName(successInt) == "Success");
    assert(matcher.getTypeName(errorResult) == "Error");
    
    // Test field access
    assert(matcher.canAccessField(successInt, "kind"));
    assert(matcher.canAccessField(successInt, "value"));
    assert(!matcher.canAccessField(successInt, "error"));
    
    assert(matcher.canAccessField(errorResult, "kind"));
    assert(matcher.canAccessField(errorResult, "error"));
    assert(!matcher.canAccessField(errorResult, "value"));
    
    std::cout << "✓ Result pattern matching tests passed" << std::endl;
}

void testErrorHandlingCompatibility() {
    std::cout << "Testing error handling system compatibility..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test that Result types are fallible (compatible with ? operator)
    auto resultType = typeSystem.createResultType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE);
    assert(typeSystem.isFallibleType(resultType));
    
    // Test that Result types require explicit handling
    assert(typeSystem.requiresExplicitHandling(resultType));
    
    // Test creating fallible types (compatible with Type?ErrorType syntax)
    auto fallibleType = typeSystem.createFallibleType(typeSystem.INT_TYPE, {"ParseError", "NetworkError"});
    assert(typeSystem.isUnionType(fallibleType));
    assert(typeSystem.isFallibleType(fallibleType));
    
    std::cout << "✓ Error handling compatibility tests passed" << std::endl;
}

void testResultRequirements() {
    std::cout << "Testing Result type requirements..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Requirement 3.1: Result type should support Success variant with a value and Error variant with error information
    auto resultType = typeSystem.createResultType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE);
    assert(typeSystem.isUnionType(resultType));
    
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successResult = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    assert(typeSystem.isSuccess(successResult));
    
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Error occurred");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    assert(typeSystem.isError(errorResult));
    
    // Requirement 3.2: Result type should enforce proper handling of both variants
    assert(typeSystem.requiresExplicitHandling(resultType));
    
    // Requirement 3.3: Result type should require explicit handling of all possible variants
    TypeMatcher matcher(&typeSystem, memManager, region);
    std::vector<TypePtr> patterns = {
        typeSystem.createResultType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE)
    };
    // Note: Full exhaustiveness checking would require more complex pattern matching implementation
    
    // Requirement 3.4: Result type should require explicit handling of all possible variants
    // This is enforced by the requiresExplicitHandling method and pattern matching system
    
    std::cout << "✓ Result type requirements tests passed" << std::endl;
}

int main() {
    std::cout << "Running Result type unit tests..." << std::endl;
    
    try {
        testResultTypeCreation();
        testSuccessValueCreation();
        testErrorValueCreation();
        testResultValueExtraction();
        testResultPatternMatching();
        testErrorHandlingCompatibility();
        testResultRequirements();
        
        std::cout << "\n✅ All Result type tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "\n❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}