// Comprehensive tests for Result type implementation
// Tests all requirements and edge cases for Result type functionality

#include <cassert>
#include <iostream>
#include <memory>
#include "../../src/src/backend/types.hh"
#include "../../src/src/backend/memory.hh"

void testResultTypeRequirement31() {
    std::cout << "Testing Requirement 3.1: Result type should support Success variant with a value and Error variant with error information..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test Result type creation with different success and error types
    auto intStringResultType = typeSystem.createResultType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE);
    auto stringIntResultType = typeSystem.createResultType(typeSystem.STRING_TYPE, typeSystem.INT_TYPE);
    auto boolFloatResultType = typeSystem.createResultType(typeSystem.BOOL_TYPE, typeSystem.FLOAT64_TYPE);
    
    // Verify all Result types are union types
    assert(typeSystem.isUnionType(intStringResultType));
    assert(typeSystem.isUnionType(stringIntResultType));
    assert(typeSystem.isUnionType(boolFloatResultType));
    
    // Test Success variant creation
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successInt = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    assert(typeSystem.isSuccess(successInt));
    assert(!typeSystem.isError(successInt));
    
    // Test Error variant creation
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Something went wrong");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    assert(!typeSystem.isSuccess(errorResult));
    assert(typeSystem.isError(errorResult));
    
    std::cout << "✓ Requirement 3.1 tests passed" << std::endl;
}

void testResultTypeRequirement32() {
    std::cout << "Testing Requirement 3.2: Result type should enforce proper handling of both variants..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test that Result types require explicit handling
    auto resultType = typeSystem.createResultType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE);
    assert(typeSystem.requiresExplicitHandling(resultType));
    
    // Test that Result types are fallible (compatible with ? operator)
    assert(typeSystem.isFallibleType(resultType));
    
    // Test pattern matching requirements
    TypeMatcher matcher(&typeSystem, memManager, region);
    
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successResult = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Error occurred");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    
    // Verify pattern matching works correctly
    assert(matcher.isSuccess(successResult));
    assert(!matcher.isError(successResult));
    assert(!matcher.isSuccess(errorResult));
    assert(matcher.isError(errorResult));
    
    std::cout << "✓ Requirement 3.2 tests passed" << std::endl;
}

void testResultTypeRequirement33() {
    std::cout << "Testing Requirement 3.3: Result type should require explicit handling of all possible variants..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    TypeMatcher matcher(&typeSystem, memManager, region);
    
    // Create Result values
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successResult = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Error occurred");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    
    // Test that accessing wrong variant throws exception (enforces explicit handling)
    bool exceptionThrown = false;
    try {
        typeSystem.extractSuccessValue(errorResult);
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    
    exceptionThrown = false;
    try {
        typeSystem.extractErrorValue(successResult);
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    
    // Test safe field access (requires checking variant first)
    assert(matcher.canAccessField(successResult, "kind"));
    assert(matcher.canAccessField(successResult, "value"));
    assert(!matcher.canAccessField(successResult, "error"));
    
    assert(matcher.canAccessField(errorResult, "kind"));
    assert(matcher.canAccessField(errorResult, "error"));
    assert(!matcher.canAccessField(errorResult, "value"));
    
    std::cout << "✓ Requirement 3.3 tests passed" << std::endl;
}

void testResultTypeRequirement34() {
    std::cout << "Testing Requirement 3.4: Result type should require explicit handling of all possible variants..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    TypeMatcher matcher(&typeSystem, memManager, region);
    
    // Test type introspection for debugging and reflection
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successResult = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Error occurred");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    
    // Test runtime type information
    assert(matcher.getTypeName(successResult) == "Success");
    assert(matcher.getTypeName(errorResult) == "Error");
    
    // Test field name introspection
    auto successFieldNames = matcher.getFieldNames(successResult);
    assert(successFieldNames.size() == 2);
    assert(std::find(successFieldNames.begin(), successFieldNames.end(), "kind") != successFieldNames.end());
    assert(std::find(successFieldNames.begin(), successFieldNames.end(), "value") != successFieldNames.end());
    
    auto errorFieldNames = matcher.getFieldNames(errorResult);
    assert(errorFieldNames.size() == 2);
    assert(std::find(errorFieldNames.begin(), errorFieldNames.end(), "kind") != errorFieldNames.end());
    assert(std::find(errorFieldNames.begin(), errorFieldNames.end(), "error") != errorFieldNames.end());
    
    // Test field type introspection
    auto kindFieldType = matcher.getFieldType(successResult, "kind");
    assert(kindFieldType->tag == TypeTag::String);
    
    auto valueFieldType = matcher.getFieldType(successResult, "value");
    assert(valueFieldType->tag == TypeTag::Int);
    
    std::cout << "✓ Requirement 3.4 tests passed" << std::endl;
}

void testErrorHandlingSystemCompatibility() {
    std::cout << "Testing error handling system compatibility..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test that Result types map to error handling system's Type?ErrorType syntax
    auto resultType = typeSystem.createResultType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE);
    
    // Test that createSuccess() is compatible with ok() from error handling system
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto successResult = typeSystem.createSuccess(typeSystem.INT_TYPE, intValue);
    assert(typeSystem.isSuccess(successResult));
    
    // Test that createError() is compatible with err() from error handling system
    auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Network timeout");
    auto errorResult = typeSystem.createError(typeSystem.STRING_TYPE, errorMessage);
    assert(typeSystem.isError(errorResult));
    
    // Test fallible type creation (compatible with Type?ErrorType syntax)
    auto fallibleType = typeSystem.createFallibleType(typeSystem.INT_TYPE, {"ParseError", "NetworkError"});
    assert(typeSystem.isUnionType(fallibleType));
    assert(typeSystem.isFallibleType(fallibleType));
    
    std::cout << "✓ Error handling system compatibility tests passed" << std::endl;
}

void testResultTypeEdgeCases() {
    std::cout << "Testing Result type edge cases..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test Result with complex types
    auto listType = std::make_shared<Type>(TypeTag::List);
    auto dictType = std::make_shared<Type>(TypeTag::Dict);
    
    auto complexResultType = typeSystem.createResultType(listType, dictType);
    assert(typeSystem.isUnionType(complexResultType));
    
    // Test Result with same success and error types
    auto sameTypeResult = typeSystem.createResultType(typeSystem.STRING_TYPE, typeSystem.STRING_TYPE);
    assert(typeSystem.isUnionType(sameTypeResult));
    
    // Test nested Result types
    auto innerResultType = typeSystem.createResultType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE);
    auto nestedResultType = typeSystem.createResultType(innerResultType, typeSystem.STRING_TYPE);
    assert(typeSystem.isUnionType(nestedResultType));
    
    std::cout << "✓ Result type edge cases tests passed" << std::endl;
}

void testResultTypePerformance() {
    std::cout << "Testing Result type performance..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test creating many Result values
    const int numResults = 1000;
    std::vector<ValuePtr> results;
    results.reserve(numResults);
    
    for (int i = 0; i < numResults; ++i) {
        if (i % 2 == 0) {
            auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, i);
            results.push_back(typeSystem.createSuccess(typeSystem.INT_TYPE, intValue));
        } else {
            auto errorMessage = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "Error " + std::to_string(i));
            results.push_back(typeSystem.createError(typeSystem.STRING_TYPE, errorMessage));
        }
    }
    
    // Test pattern matching performance
    int successCount = 0;
    int errorCount = 0;
    
    for (const auto& result : results) {
        if (typeSystem.isSuccess(result)) {
            successCount++;
        } else if (typeSystem.isError(result)) {
            errorCount++;
        }
    }
    
    assert(successCount == numResults / 2);
    assert(errorCount == numResults / 2);
    
    std::cout << "✓ Result type performance tests passed" << std::endl;
}

int main() {
    std::cout << "Running comprehensive Result type tests..." << std::endl;
    
    try {
        testResultTypeRequirement31();
        testResultTypeRequirement32();
        testResultTypeRequirement33();
        testResultTypeRequirement34();
        testErrorHandlingSystemCompatibility();
        testResultTypeEdgeCases();
        testResultTypePerformance();
        
        std::cout << "\n✅ All comprehensive Result type tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "\n❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}