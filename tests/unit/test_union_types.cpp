#include "../../src/backend/types.hh"
#include "../../src/backend/memory.hh"
#include <cassert>
#include <iostream>
#include <vector>

// Test helper function
void assert_true(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "ASSERTION FAILED: " << message << std::endl;
        exit(1);
    }
    std::cout << "PASS: " << message << std::endl;
}

void test_createUnionType() {
    std::cout << "\n=== Testing createUnionType() ===" << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test creating union type with multiple types
    std::vector<TypePtr> types = {
        typeSystem.INT_TYPE,
        typeSystem.STRING_TYPE,
        typeSystem.BOOL_TYPE
    };
    
    TypePtr unionType = typeSystem.createUnionType(types);
    assert_true(unionType != nullptr, "Union type should be created");
    assert_true(unionType->tag == TypeTag::Union, "Created type should be Union");
    
    // Test getting union variants
    auto variants = typeSystem.getUnionVariants(unionType);
    assert_true(variants.size() == 3, "Union should have 3 variants");
    assert_true(variants[0]->tag == TypeTag::Int, "First variant should be Int");
    assert_true(variants[1]->tag == TypeTag::String, "Second variant should be String");
    assert_true(variants[2]->tag == TypeTag::Bool, "Third variant should be Bool");
    
    // Test empty union type (should throw)
    try {
        typeSystem.createUnionType({});
        assert_true(false, "Empty union should throw exception");
    } catch (const std::runtime_error&) {
        assert_true(true, "Empty union correctly throws exception");
    }
}

void test_isUnionType() {
    std::cout << "\n=== Testing isUnionType() ===" << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test with union type
    std::vector<TypePtr> types = {typeSystem.INT_TYPE, typeSystem.STRING_TYPE};
    TypePtr unionType = typeSystem.createUnionType(types);
    assert_true(typeSystem.isUnionType(unionType), "Should identify union type correctly");
    
    // Test with non-union type
    assert_true(!typeSystem.isUnionType(typeSystem.INT_TYPE), "Should identify non-union type correctly");
    assert_true(!typeSystem.isUnionType(typeSystem.STRING_TYPE), "Should identify non-union type correctly");
    
    // Test with null type
    assert_true(!typeSystem.isUnionType(nullptr), "Should handle null type safely");
}

void test_unionTypeCompatibility() {
    std::cout << "\n=== Testing union type compatibility ===" << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create union type: int | string
    std::vector<TypePtr> unionTypes = {typeSystem.INT_TYPE, typeSystem.STRING_TYPE};
    TypePtr unionType = typeSystem.createUnionType(unionTypes);
    
    // Test compatibility: int should be compatible with int|string
    assert_true(typeSystem.isCompatible(typeSystem.INT_TYPE, unionType), 
                "Int should be compatible with int|string union");
    
    // Test compatibility: string should be compatible with int|string
    assert_true(typeSystem.isCompatible(typeSystem.STRING_TYPE, unionType), 
                "String should be compatible with int|string union");
    
    // Test compatibility: bool should not be compatible with int|string
    assert_true(!typeSystem.isCompatible(typeSystem.BOOL_TYPE, unionType), 
                "Bool should not be compatible with int|string union");
    
    // Test union to specific type compatibility
    assert_true(typeSystem.isCompatible(unionType, typeSystem.INT_TYPE), 
                "int|string union should be compatible with int");
    assert_true(typeSystem.isCompatible(unionType, typeSystem.STRING_TYPE), 
                "int|string union should be compatible with string");
}

void test_createUnionValue() {
    std::cout << "\n=== Testing createUnionValue() ===" << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create union type: int | string
    std::vector<TypePtr> unionTypes = {typeSystem.INT_TYPE, typeSystem.STRING_TYPE};
    TypePtr unionType = typeSystem.createUnionType(unionTypes);
    
    // Create an int value
    ValuePtr intValue = typeSystem.createValue(typeSystem.INT_TYPE);
    intValue->data = int32_t(42);
    
    // Create union value with int variant
    ValuePtr unionValue = typeSystem.createUnionValue(unionType, typeSystem.INT_TYPE, intValue);
    assert_true(unionValue != nullptr, "Union value should be created");
    assert_true(unionValue->type->tag == TypeTag::Union, "Union value should have Union type");
    
    // Test getting active variant type
    TypePtr activeType = typeSystem.getActiveVariantType(unionValue);
    assert_true(activeType->tag == TypeTag::Int, "Active variant should be Int");
    
    // Test invalid variant type
    try {
        typeSystem.createUnionValue(unionType, typeSystem.BOOL_TYPE, intValue);
        assert_true(false, "Invalid variant should throw exception");
    } catch (const std::runtime_error&) {
        assert_true(true, "Invalid variant correctly throws exception");
    }
}

void test_unionTypeFlattening() {
    std::cout << "\n=== Testing union type flattening ===" << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create nested union: (int | string) | bool
    std::vector<TypePtr> innerTypes = {typeSystem.INT_TYPE, typeSystem.STRING_TYPE};
    TypePtr innerUnion = typeSystem.createUnionType(innerTypes);
    
    std::vector<TypePtr> outerTypes = {innerUnion, typeSystem.BOOL_TYPE};
    TypePtr flattenedUnion = typeSystem.createUnionType(outerTypes);
    
    // Should flatten to int | string | bool
    auto variants = typeSystem.getUnionVariants(flattenedUnion);
    assert_true(variants.size() == 3, "Flattened union should have 3 variants");
    
    // Check that all expected types are present
    bool hasInt = false, hasString = false, hasBool = false;
    for (const auto& variant : variants) {
        if (variant->tag == TypeTag::Int) hasInt = true;
        else if (variant->tag == TypeTag::String) hasString = true;
        else if (variant->tag == TypeTag::Bool) hasBool = true;
    }
    
    assert_true(hasInt && hasString && hasBool, "Flattened union should contain all expected types");
}

void test_unionTypeDuplicateRemoval() {
    std::cout << "\n=== Testing union type duplicate removal ===" << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create union with duplicates: int | string | int | bool | string
    std::vector<TypePtr> typesWithDuplicates = {
        typeSystem.INT_TYPE,
        typeSystem.STRING_TYPE,
        typeSystem.INT_TYPE,
        typeSystem.BOOL_TYPE,
        typeSystem.STRING_TYPE
    };
    
    TypePtr unionType = typeSystem.createUnionType(typesWithDuplicates);
    auto variants = typeSystem.getUnionVariants(unionType);
    
    assert_true(variants.size() == 3, "Union should remove duplicates and have 3 unique variants");
    
    // Check that all expected types are present (no duplicates)
    bool hasInt = false, hasString = false, hasBool = false;
    for (const auto& variant : variants) {
        if (variant->tag == TypeTag::Int) {
            assert_true(!hasInt, "Int should appear only once");
            hasInt = true;
        } else if (variant->tag == TypeTag::String) {
            assert_true(!hasString, "String should appear only once");
            hasString = true;
        } else if (variant->tag == TypeTag::Bool) {
            assert_true(!hasBool, "Bool should appear only once");
            hasBool = true;
        }
    }
    
    assert_true(hasInt && hasString && hasBool, "All unique types should be present");
}

void test_getCommonTypeWithUnions() {
    std::cout << "\n=== Testing getCommonType with unions ===" << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test common type between int and string should create union
    TypePtr commonType = typeSystem.getCommonType(typeSystem.INT_TYPE, typeSystem.STRING_TYPE);
    assert_true(commonType->tag == TypeTag::Union, "Common type of int and string should be union");
    
    auto variants = typeSystem.getUnionVariants(commonType);
    assert_true(variants.size() == 2, "Common union should have 2 variants");
    
    // Test common type between union and compatible type
    std::vector<TypePtr> unionTypes = {typeSystem.INT_TYPE, typeSystem.STRING_TYPE};
    TypePtr unionType = typeSystem.createUnionType(unionTypes);
    
    TypePtr commonWithInt = typeSystem.getCommonType(unionType, typeSystem.INT_TYPE);
    assert_true(commonWithInt->tag == TypeTag::Union, "Common type should remain union");
    assert_true(typeSystem.getUnionVariants(commonWithInt).size() == 2, "Should not add duplicate variant");
}

int main() {
    std::cout << "Running Union Type Tests..." << std::endl;
    
    try {
        test_createUnionType();
        test_isUnionType();
        test_unionTypeCompatibility();
        test_createUnionValue();
        test_unionTypeFlattening();
        test_unionTypeDuplicateRemoval();
        test_getCommonTypeWithUnions();
        
        std::cout << "\n=== ALL UNION TYPE TESTS PASSED ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}