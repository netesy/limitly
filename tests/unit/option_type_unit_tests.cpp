// Unit tests for Option type implementation
// Tests the TypeSystem Option type methods directly

#include <cassert>
#include <iostream>
#include <memory>
#include "../../src/backend/types.hh"
#include "../../src/backend/memory.hh"

void testOptionTypeCreation() {
    std::cout << "Testing Option type creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test createOptionType with different value types
    auto intOptionType = typeSystem.createOptionType(typeSystem.INT_TYPE);
    assert(typeSystem.isUnionType(intOptionType));
    
    auto stringOptionType = typeSystem.createOptionType(typeSystem.STRING_TYPE);
    assert(typeSystem.isUnionType(stringOptionType));
    
    auto boolOptionType = typeSystem.createOptionType(typeSystem.BOOL_TYPE);
    assert(typeSystem.isUnionType(boolOptionType));
    
    std::cout << "✓ Option type creation tests passed" << std::endl;
}

void testSomeValueCreation() {
    std::cout << "Testing Some value creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create Some values with different types
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto someInt = typeSystem.createSome(typeSystem.INT_TYPE, intValue);
    
    assert(someInt != nullptr);
    assert(typeSystem.isSome(someInt));
    assert(!typeSystem.isNone(someInt));
    
    auto stringValue = memManager.makeRef<Value>(region, typeSystem.STRING_TYPE, "hello");
    auto someString = typeSystem.createSome(typeSystem.STRING_TYPE, stringValue);
    
    assert(someString != nullptr);
    assert(typeSystem.isSome(someString));
    assert(!typeSystem.isNone(someString));
    
    std::cout << "✓ Some value creation tests passed" << std::endl;
}

void testNoneValueCreation() {
    std::cout << "Testing None value creation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create None values for different types
    auto noneInt = typeSystem.createNone(typeSystem.INT_TYPE);
    
    assert(noneInt != nullptr);
    assert(!typeSystem.isSome(noneInt));
    assert(typeSystem.isNone(noneInt));
    
    auto noneString = typeSystem.createNone(typeSystem.STRING_TYPE);
    
    assert(noneString != nullptr);
    assert(!typeSystem.isSome(noneString));
    assert(typeSystem.isNone(noneString));
    
    std::cout << "✓ None value creation tests passed" << std::endl;
}

void testOptionValueExtraction() {
    std::cout << "Testing Option value extraction..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test extracting value from Some
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto someInt = typeSystem.createSome(typeSystem.INT_TYPE, intValue);
    
    auto extractedValue = typeSystem.extractSomeValue(someInt);
    assert(extractedValue != nullptr);
    assert(extractedValue->type->tag == TypeTag::Int);
    
    // Test that extracting from None throws exception
    auto noneInt = typeSystem.createNone(typeSystem.INT_TYPE);
    
    bool exceptionThrown = false;
    try {
        typeSystem.extractSomeValue(noneInt);
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    
    std::cout << "✓ Option value extraction tests passed" << std::endl;
}

void testOptionPatternMatching() {
    std::cout << "Testing Option pattern matching..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    TypeMatcher matcher(&typeSystem, memManager, region);
    
    // Create Option values
    auto intValue = memManager.makeRef<Value>(region, typeSystem.INT_TYPE, 42);
    auto someInt = typeSystem.createSome(typeSystem.INT_TYPE, intValue);
    auto noneInt = typeSystem.createNone(typeSystem.INT_TYPE);
    
    // Test pattern matching
    assert(matcher.isSome(someInt));
    assert(!matcher.isNone(someInt));
    
    assert(!matcher.isSome(noneInt));
    assert(matcher.isNone(noneInt));
    
    // Test type name introspection
    assert(matcher.getTypeName(someInt) == "Some");
    assert(matcher.getTypeName(noneInt) == "None");
    
    // Test field access
    assert(matcher.canAccessField(someInt, "kind"));
    assert(matcher.canAccessField(someInt, "value"));
    assert(matcher.canAccessField(noneInt, "kind"));
    assert(!matcher.canAccessField(noneInt, "value"));
    
    std::cout << "✓ Option pattern matching tests passed" << std::endl;
}

void testErrorHandlingCompatibility() {
    std::cout << "Testing error handling system compatibility..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test that Option types are fallible (compatible with ? operator)
    auto optionType = typeSystem.createOptionType(typeSystem.INT_TYPE);
    assert(typeSystem.isFallibleType(optionType));
    
    // Test that Option types require explicit handling
    assert(typeSystem.requiresExplicitHandling(optionType));
    
    // Test creating fallible types (compatible with Type?ErrorType syntax)
    auto fallibleType = typeSystem.createFallibleType(typeSystem.INT_TYPE, {"ParseError", "NetworkError"});
    assert(typeSystem.isUnionType(fallibleType));
    assert(typeSystem.isFallibleType(fallibleType));
    
    std::cout << "✓ Error handling compatibility tests passed" << std::endl;
}

int main() {
    std::cout << "Running Option type unit tests..." << std::endl;
    
    try {
        testOptionTypeCreation();
        testSomeValueCreation();
        testNoneValueCreation();
        testOptionValueExtraction();
        testOptionPatternMatching();
        testErrorHandlingCompatibility();
        
        std::cout << "\n✅ All Option type tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "\n❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}