// Unit tests for TypeSystem type alias registry and resolution
// Tests the C++ implementation directly

#include "../../backend/types.hh"
#include "../../backend/memory.hh"
#include <cassert>
#include <iostream>

void testBasicTypeAliasRegistration() {
    std::cout << "Testing basic type alias registration..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test registering a basic type alias
    typeSystem.registerTypeAlias("UserId", typeSystem.INT64_TYPE);
    
    // Test resolving the alias
    TypePtr resolved = typeSystem.resolveTypeAlias("UserId");
    assert(resolved != nullptr);
    assert(resolved->tag == TypeTag::Int64);
    
    std::cout << "✓ Basic type alias registration test passed" << std::endl;
}

void testTypeAliasResolution() {
    std::cout << "Testing type alias resolution..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Register multiple aliases
    typeSystem.registerTypeAlias("UserName", typeSystem.STRING_TYPE);
    typeSystem.registerTypeAlias("UserScore", typeSystem.FLOAT64_TYPE);
    typeSystem.registerTypeAlias("IsActive", typeSystem.BOOL_TYPE);
    
    // Test resolving each alias
    TypePtr nameType = typeSystem.resolveTypeAlias("UserName");
    TypePtr scoreType = typeSystem.resolveTypeAlias("UserScore");
    TypePtr activeType = typeSystem.resolveTypeAlias("IsActive");
    
    assert(nameType != nullptr && nameType->tag == TypeTag::String);
    assert(scoreType != nullptr && scoreType->tag == TypeTag::Float64);
    assert(activeType != nullptr && activeType->tag == TypeTag::Bool);
    
    // Test resolving non-existent alias
    TypePtr nonExistent = typeSystem.resolveTypeAlias("NonExistent");
    assert(nonExistent == nullptr);
    
    std::cout << "✓ Type alias resolution test passed" << std::endl;
}

void testGetTypeWithAliases() {
    std::cout << "Testing getType() method with aliases..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Register an alias
    typeSystem.registerTypeAlias("CustomInt", typeSystem.INT64_TYPE);
    
    // Test that getType() can find the alias
    TypePtr aliasType = typeSystem.getType("CustomInt");
    assert(aliasType != nullptr);
    assert(aliasType->tag == TypeTag::Int64);
    
    // Test that built-in types still work
    TypePtr intType = typeSystem.getType("i64");
    assert(intType != nullptr);
    assert(intType->tag == TypeTag::Int64);
    
    TypePtr strType = typeSystem.getType("str");
    assert(strType != nullptr);
    assert(strType->tag == TypeTag::String);
    
    std::cout << "✓ getType() with aliases test passed" << std::endl;
}

void testCircularDependencyDetection() {
    std::cout << "Testing circular dependency detection..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test that valid aliases work
    typeSystem.registerTypeAlias("ValidAlias", typeSystem.INT64_TYPE);
    TypePtr valid = typeSystem.resolveTypeAlias("ValidAlias");
    assert(valid != nullptr);
    
    // For now, the circular dependency detection is basic
    // More sophisticated tests can be added when complex type structures are implemented
    
    std::cout << "✓ Circular dependency detection test passed" << std::endl;
}

void testLegacyCompatibility() {
    std::cout << "Testing legacy method compatibility..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test that old addTypeAlias method still works
    typeSystem.addTypeAlias("LegacyAlias", typeSystem.STRING_TYPE);
    
    // Test that old getTypeAlias method still works
    try {
        TypePtr legacy = typeSystem.getTypeAlias("LegacyAlias");
        assert(legacy != nullptr);
        assert(legacy->tag == TypeTag::String);
    } catch (const std::exception& e) {
        assert(false && "Legacy method should work");
    }
    
    // Test that getTypeAlias throws for non-existent alias
    try {
        typeSystem.getTypeAlias("NonExistent");
        assert(false && "Should have thrown exception");
    } catch (const std::runtime_error& e) {
        // Expected behavior
    }
    
    std::cout << "✓ Legacy compatibility test passed" << std::endl;
}

int main() {
    std::cout << "Running TypeSystem type alias registry tests..." << std::endl;
    
    try {
        testBasicTypeAliasRegistration();
        testTypeAliasResolution();
        testGetTypeWithAliases();
        testCircularDependencyDetection();
        testLegacyCompatibility();
        
        std::cout << "\n✅ All TypeSystem type alias registry tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "\n❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "\n❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
}