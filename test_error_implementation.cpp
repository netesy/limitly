#include "backend/value.hh"
#include "backend/types.hh"
#include "backend/memory.hh"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "Testing Error Value Implementation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test 1: Basic ErrorValue creation
    std::cout << "1. Testing ErrorValue creation..." << std::endl;
    ErrorValue basicError("DivisionByZero", "Cannot divide by zero");
    assert(basicError.errorType == "DivisionByZero");
    assert(basicError.message == "Cannot divide by zero");
    std::cout << "   ✓ Basic ErrorValue created successfully" << std::endl;
    
    // Test 2: ErrorUnion helper class
    std::cout << "2. Testing ErrorUnion helper class..." << std::endl;
    auto successValue = typeSystem.createValue(typeSystem.INT_TYPE);
    successValue->data = int32_t(42);
    
    ErrorUnion successUnion = ErrorUnion::success(successValue);
    assert(successUnion.isSuccess());
    assert(!successUnion.isError());
    std::cout << "   ✓ Success ErrorUnion created" << std::endl;
    
    ErrorUnion errorUnion = ErrorUnion::error("TestError", "Test message");
    assert(!errorUnion.isSuccess());
    assert(errorUnion.isError());
    assert(errorUnion.getErrorType() == "TestError");
    std::cout << "   ✓ Error ErrorUnion created" << std::endl;
    
    // Test 3: ErrorUtils functions
    std::cout << "3. Testing ErrorUtils functions..." << std::endl;
    auto errorValue = ErrorUtils::createError("TestError", "Test message");
    assert(ErrorUtils::isError(errorValue));
    assert(ErrorUtils::getErrorType(errorValue) == "TestError");
    assert(ErrorUtils::getErrorMessage(errorValue) == "Test message");
    std::cout << "   ✓ ErrorUtils functions working" << std::endl;
    
    // Test 4: Error union type creation
    std::cout << "4. Testing error union type creation..." << std::endl;
    auto errorUnionType = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, {"TestError"}, false);
    assert(errorUnionType->tag == TypeTag::ErrorUnion);
    std::cout << "   ✓ Error union type created" << std::endl;
    
    // Test 5: Value integration
    std::cout << "5. Testing Value integration..." << std::endl;
    auto value = std::make_shared<Value>(typeSystem.INT_TYPE);
    value->data = ErrorValue("IntError", "Integer error");
    assert(std::holds_alternative<ErrorValue>(value->data));
    std::cout << "   ✓ ErrorValue integrated with Value system" << std::endl;
    
    std::cout << "\n✅ All error value implementation tests passed!" << std::endl;
    return 0;
}