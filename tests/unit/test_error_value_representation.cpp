#include "backend/value.hh"
#include "backend/types.hh"
#include "backend/memory.hh"
#include <cassert>
#include <iostream>

void testErrorValueCreation() {
    std::cout << "Testing ErrorValue creation..." << std::endl;
    
    // Test basic error value creation
    ErrorValue basicError("DivisionByZero", "Cannot divide by zero");
    assert(basicError.errorType == "DivisionByZero");
    assert(basicError.message == "Cannot divide by zero");
    assert(basicError.arguments.empty());
    assert(basicError.sourceLocation == 0);
    
    // Test error value with arguments
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    auto arg1 = typeSystem.createValue(typeSystem.INT_TYPE);
    arg1->data = int32_t(42);
    auto arg2 = typeSystem.createValue(typeSystem.STRING_TYPE);
    arg2->data = std::string("test");
    
    ErrorValue errorWithArgs("CustomError", "Error with arguments", {arg1, arg2}, 123);
    assert(errorWithArgs.errorType == "CustomError");
    assert(errorWithArgs.message == "Error with arguments");
    assert(errorWithArgs.arguments.size() == 2);
    assert(errorWithArgs.sourceLocation == 123);
    
    // Test error value toString
    std::string errorStr = basicError.toString();
    assert(errorStr.find("DivisionByZero") != std::string::npos);
    assert(errorStr.find("Cannot divide by zero") != std::string::npos);
    
    std::cout << "✓ ErrorValue creation tests passed" << std::endl;
}

void testErrorUnionHelperClass() {
    std::cout << "Testing ErrorUnion helper class..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test success ErrorUnion
    auto successValue = typeSystem.createValue(typeSystem.INT_TYPE);
    successValue->data = int32_t(42);
    
    ErrorUnion successUnion = ErrorUnion::success(successValue);
    assert(successUnion.isSuccess());
    assert(!successUnion.isError());
    assert(successUnion.getTag() == ErrorUnion::Tag::SUCCESS);
    assert(successUnion.getSuccessValue() == successValue);
    
    // Test error ErrorUnion
    ErrorUnion errorUnion = ErrorUnion::error("TestError", "Test message");
    assert(!errorUnion.isSuccess());
    assert(errorUnion.isError());
    assert(errorUnion.getTag() == ErrorUnion::Tag::ERROR);
    assert(errorUnion.getErrorType() == "TestError");
    assert(errorUnion.getErrorMessage() == "Test message");
    
    // Test copy constructor
    ErrorUnion copiedSuccess(successUnion);
    assert(copiedSuccess.isSuccess());
    assert(copiedSuccess.getSuccessValue() == successValue);
    
    ErrorUnion copiedError(errorUnion);
    assert(copiedError.isError());
    assert(copiedError.getErrorType() == "TestError");
    
    // Test move constructor
    ErrorUnion movedSuccess(std::move(copiedSuccess));
    assert(movedSuccess.isSuccess());
    
    // Test safe access methods
    auto defaultValue = typeSystem.createValue(typeSystem.INT_TYPE);
    defaultValue->data = int32_t(0);
    
    assert(successUnion.getSuccessValueOr(defaultValue) == successValue);
    assert(errorUnion.getSuccessValueOr(defaultValue) == defaultValue);
    
    std::cout << "✓ ErrorUnion helper class tests passed" << std::endl;
}

void testErrorUnionValueConversion() {
    std::cout << "Testing ErrorUnion to Value conversion..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Create error union type
    auto errorUnionType = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, {"TestError"}, false);
    
    // Test success value conversion
    auto successValue = typeSystem.createValue(typeSystem.INT_TYPE);
    successValue->data = int32_t(42);
    
    ErrorUnion successUnion = ErrorUnion::success(successValue);
    auto convertedSuccess = successUnion.toValue(errorUnionType);
    
    assert(convertedSuccess->type == errorUnionType);
    assert(std::holds_alternative<int32_t>(convertedSuccess->data));
    assert(std::get<int32_t>(convertedSuccess->data) == 42);
    
    // Test error value conversion
    ErrorUnion errorUnion = ErrorUnion::error("TestError", "Test message");
    auto convertedError = errorUnion.toValue(errorUnionType);
    
    assert(convertedError->type == errorUnionType);
    assert(std::holds_alternative<ErrorValue>(convertedError->data));
    
    auto& errorValue = std::get<ErrorValue>(convertedError->data);
    assert(errorValue.errorType == "TestError");
    assert(errorValue.message == "Test message");
    
    std::cout << "✓ ErrorUnion to Value conversion tests passed" << std::endl;
}

void testErrorUtilityFunctions() {
    std::cout << "Testing error utility functions..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test createError
    auto errorValue = ErrorUtils::createError("TestError", "Test message");
    assert(ErrorUtils::isError(errorValue));
    assert(!ErrorUtils::isSuccess(errorValue));
    assert(ErrorUtils::getErrorType(errorValue) == "TestError");
    assert(ErrorUtils::getErrorMessage(errorValue) == "Test message");
    
    // Test createSuccess
    auto successValue = typeSystem.createValue(typeSystem.INT_TYPE);
    successValue->data = int32_t(42);
    auto errorUnionType = typeSystem.createErrorUnionType(typeSystem.INT_TYPE, {"TestError"}, false);
    
    auto wrappedSuccess = ErrorUtils::createSuccess(successValue, errorUnionType);
    assert(ErrorUtils::isSuccess(wrappedSuccess));
    assert(!ErrorUtils::isError(wrappedSuccess));
    
    // Test error extraction
    const ErrorValue& extractedError = ErrorUtils::getError(errorValue);
    assert(extractedError.errorType == "TestError");
    assert(extractedError.message == "Test message");
    
    // Test safe error extraction
    const ErrorValue* safeError = ErrorUtils::getErrorSafe(errorValue);
    assert(safeError != nullptr);
    assert(safeError->errorType == "TestError");
    
    const ErrorValue* safeErrorFromSuccess = ErrorUtils::getErrorSafe(wrappedSuccess);
    assert(safeErrorFromSuccess == nullptr);
    
    // Test wrapping functions
    ErrorValue testError("WrapError", "Wrap test");
    auto wrappedError = ErrorUtils::wrapAsError(testError, errorUnionType);
    assert(ErrorUtils::isError(wrappedError));
    assert(ErrorUtils::getErrorType(wrappedError) == "WrapError");
    
    // Test unwrapping functions
    auto unwrappedSuccess = ErrorUtils::unwrapSuccess(wrappedSuccess, typeSystem.INT_TYPE);
    assert(std::holds_alternative<int32_t>(unwrappedSuccess->data));
    assert(std::get<int32_t>(unwrappedSuccess->data) == 42);
    
    // Test safe unwrapping
    auto safeUnwrapped = ErrorUtils::unwrapSuccessSafe(wrappedSuccess, typeSystem.INT_TYPE);
    assert(safeUnwrapped != nullptr);
    
    auto safeUnwrappedFromError = ErrorUtils::unwrapSuccessSafe(wrappedError, typeSystem.INT_TYPE);
    assert(safeUnwrappedFromError == nullptr);
    
    std::cout << "✓ Error utility functions tests passed" << std::endl;
}

void testErrorValueManipulation() {
    std::cout << "Testing error value manipulation..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test error value with complex arguments
    auto listArg = typeSystem.createValue(typeSystem.LIST_TYPE);
    ListValue listValue;
    auto elem1 = typeSystem.createValue(typeSystem.INT_TYPE);
    elem1->data = int32_t(1);
    auto elem2 = typeSystem.createValue(typeSystem.INT_TYPE);
    elem2->data = int32_t(2);
    listValue.elements = {elem1, elem2};
    listArg->data = listValue;
    
    auto dictArg = typeSystem.createValue(typeSystem.DICT_TYPE);
    DictValue dictValue;
    auto key = typeSystem.createValue(typeSystem.STRING_TYPE);
    key->data = std::string("key");
    auto value = typeSystem.createValue(typeSystem.STRING_TYPE);
    value->data = std::string("value");
    dictValue.elements[key] = value;
    dictArg->data = dictValue;
    
    ErrorValue complexError("ComplexError", "Error with complex args", {listArg, dictArg}, 456);
    
    assert(complexError.arguments.size() == 2);
    assert(ErrorUtils::getErrorArguments(ErrorUtils::createError("ComplexError", "Error with complex args", {listArg, dictArg}, 456)).size() == 2);
    
    // Test error location tracking
    assert(complexError.sourceLocation == 456);
    assert(ErrorUtils::getErrorLocation(ErrorUtils::createError("LocationError", "Test", {}, 789)) == 789);
    
    std::cout << "✓ Error value manipulation tests passed" << std::endl;
}

void testErrorUnionIntegration() {
    std::cout << "Testing ErrorUnion integration with existing systems..." << std::endl;
    
    MemoryManager<> memManager;
    MemoryManager<>::Region region(memManager);
    TypeSystem typeSystem(memManager, region);
    
    // Test integration with error union types
    auto errorUnionType = typeSystem.createErrorUnionType(typeSystem.STRING_TYPE, {"ParseError", "ValidationError"}, false);
    
    // Create success case
    auto successValue = typeSystem.createValue(typeSystem.STRING_TYPE);
    successValue->data = std::string("success");
    
    ErrorUnion successUnion = ErrorUnion::success(successValue);
    auto successAsValue = ErrorUtils::createErrorUnionValue(successUnion, errorUnionType);
    
    assert(successAsValue->type == errorUnionType);
    assert(std::holds_alternative<std::string>(successAsValue->data));
    assert(std::get<std::string>(successAsValue->data) == "success");
    
    // Create error case
    ErrorUnion errorUnion = ErrorUnion::error("ParseError", "Invalid syntax");
    auto errorAsValue = ErrorUtils::createErrorUnionValue(errorUnion, errorUnionType);
    
    assert(errorAsValue->type == errorUnionType);
    assert(std::holds_alternative<ErrorValue>(errorAsValue->data));
    
    auto& errorVal = std::get<ErrorValue>(errorAsValue->data);
    assert(errorVal.errorType == "ParseError");
    assert(errorVal.message == "Invalid syntax");
    
    // Test type system compatibility
    assert(typeSystem.checkType(successAsValue, errorUnionType));
    assert(typeSystem.checkType(errorAsValue, errorUnionType));
    
    std::cout << "✓ ErrorUnion integration tests passed" << std::endl;
}

int main() {
    try {
        testErrorValueCreation();
        testErrorUnionHelperClass();
        testErrorUnionValueConversion();
        testErrorUtilityFunctions();
        testErrorValueManipulation();
        testErrorUnionIntegration();
        
        std::cout << "\n✅ All error value representation tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}