#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <string>
#include "src/backend/value.hh"

// Test helper function
void assert_test(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << "✓ " << test_name << " passed" << std::endl;
    } else {
        std::cout << "✗ " << test_name << " FAILED" << std::endl;
        exit(1);
    }
}

void test_error_value_struct() {
    std::cout << "\n=== Testing ErrorValue Struct ===" << std::endl;
    
    // Test basic construction
    ErrorValue error1;
    assert_test(error1.errorType.empty(), "Default ErrorValue has empty type");
    assert_test(error1.message.empty(), "Default ErrorValue has empty message");
    assert_test(error1.arguments.empty(), "Default ErrorValue has no arguments");
    assert_test(error1.sourceLocation == 0, "Default ErrorValue has zero location");
    
    // Test parameterized construction
    auto arg1 = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto arg2 = std::make_shared<Value>(std::make_shared<Type>(TypeTag::String), "test");
    std::vector<ValuePtr> args = {arg1, arg2};
    
    ErrorValue error2("TestError", "Test message", args, 123);
    assert_test(error2.errorType == "TestError", "ErrorValue type set correctly");
    assert_test(error2.message == "Test message", "ErrorValue message set correctly");
    assert_test(error2.arguments.size() == 2, "ErrorValue arguments count correct");
    assert_test(error2.sourceLocation == 123, "ErrorValue source location correct");
    
    // Test toString method
    std::string errorStr = error2.toString();
    assert_test(errorStr.find("TestError") != std::string::npos, "toString contains error type");
    assert_test(errorStr.find("Test message") != std::string::npos, "toString contains message");
}

void test_error_union_helper() {
    std::cout << "\n=== Testing ErrorUnion Helper Class ===" << std::endl;
    
    // Test success construction
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    ErrorUnion successUnion(successValue);
    
    assert_test(successUnion.isSuccess(), "Success union reports isSuccess");
    assert_test(!successUnion.isError(), "Success union reports not isError");
    assert_test(successUnion.getTag() == ErrorUnion::Tag::SUCCESS, "Success union has correct tag");
    assert_test(successUnion.getSuccessValue() == successValue, "Success union returns correct value");
    
    // Test error construction
    ErrorValue errorValue("TestError", "Test message");
    ErrorUnion errorUnion(errorValue);
    
    assert_test(!errorUnion.isSuccess(), "Error union reports not isSuccess");
    assert_test(errorUnion.isError(), "Error union reports isError");
    assert_test(errorUnion.getTag() == ErrorUnion::Tag::ERROR, "Error union has correct tag");
    assert_test(errorUnion.getErrorValue().errorType == "TestError", "Error union returns correct error");
    
    // Test direct error construction
    ErrorUnion directError("DirectError", "Direct message");
    assert_test(directError.isError(), "Direct error construction works");
    assert_test(directError.getErrorType() == "DirectError", "Direct error has correct type");
    assert_test(directError.getErrorMessage() == "Direct message", "Direct error has correct message");
    
    // Test safe access methods
    assert_test(successUnion.getSuccessValueOr(nullptr) == successValue, "getSuccessValueOr with success");
    assert_test(errorUnion.getSuccessValueOr(successValue) == successValue, "getSuccessValueOr with error");
    assert_test(successUnion.getErrorType().empty(), "Success union has empty error type");
    assert_test(errorUnion.getErrorType() == "TestError", "Error union has correct error type");
    
    // Test factory methods
    auto factorySuccess = ErrorUnion::success(successValue);
    assert_test(factorySuccess.isSuccess(), "Factory success method works");
    
    auto factoryError = ErrorUnion::error("FactoryError", "Factory message");
    assert_test(factoryError.isError(), "Factory error method works");
    assert_test(factoryError.getErrorType() == "FactoryError", "Factory error has correct type");
}

void test_value_variant_integration() {
    std::cout << "\n=== Testing Value Variant Integration ===" << std::endl;
    
    // Test ErrorValue in Value variant
    auto errorType = std::make_shared<Type>(TypeTag::UserDefined);
    ErrorValue errorValue("IntegrationError", "Integration test");
    Value errorValueWrapper(errorType, errorValue);
    
    assert_test(std::holds_alternative<ErrorValue>(errorValueWrapper.data), "ErrorValue stored in Value variant");
    
    // Test toString integration
    std::string errorStr = errorValueWrapper.toString();
    assert_test(errorStr.find("IntegrationError") != std::string::npos, "Value toString works with ErrorValue");
    
    std::string rawStr = errorValueWrapper.getRawString();
    assert_test(rawStr.find("IntegrationError") != std::string::npos, "Value getRawString works with ErrorValue");
    
    // Test ErrorUnion type in Value
    auto errorUnionType = std::make_shared<Type>(TypeTag::ErrorUnion);
    ErrorUnionType unionTypeData;
    unionTypeData.successType = std::make_shared<Type>(TypeTag::Int);
    unionTypeData.errorTypes = {"TestError", "OtherError"};
    unionTypeData.isGenericError = false;
    
    errorUnionType->extra = unionTypeData;
    
    Value unionValue(errorUnionType);
    assert_test(unionValue.type->tag == TypeTag::ErrorUnion, "ErrorUnion type stored correctly");
    
    if (auto unionExtra = std::get_if<ErrorUnionType>(&unionValue.type->extra)) {
        assert_test(unionExtra->successType->tag == TypeTag::Int, "ErrorUnion success type correct");
        assert_test(unionExtra->errorTypes.size() == 2, "ErrorUnion error types count correct");
        assert_test(!unionExtra->isGenericError, "ErrorUnion generic flag correct");
    }
}

void test_error_construction_methods() {
    std::cout << "\n=== Testing Error Construction Methods ===" << std::endl;
    
    // Test basic error creation
    auto error1 = ErrorUtils::createError("TestError", "Test message");
    assert_test(ErrorUtils::isError(error1), "createError produces error value");
    assert_test(ErrorUtils::getErrorType(error1) == "TestError", "createError sets correct type");
    assert_test(ErrorUtils::getErrorMessage(error1) == "Test message", "createError sets correct message");
    
    // Test error creation with arguments
    auto arg = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    std::vector<ValuePtr> args = {arg};
    auto error2 = ErrorUtils::createError("ArgError", "Arg message", args, 123);
    
    assert_test(ErrorUtils::getErrorArguments(error2).size() == 1, "createError with args works");
    assert_test(ErrorUtils::getErrorLocation(error2) == 123, "createError sets location");
    
    // Test success creation
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto errorUnionType = std::make_shared<Type>(TypeTag::ErrorUnion);
    auto success = ErrorUtils::createSuccess(successValue, errorUnionType);
    
    assert_test(ErrorUtils::isSuccess(success), "createSuccess produces success value");
    assert_test(success->type->tag == TypeTag::ErrorUnion, "createSuccess has correct type");
    
    // Test built-in error creation
    auto divError = ErrorUtils::createDivisionByZeroError();
    assert_test(ErrorUtils::getErrorType(divError) == "DivisionByZero", "Division by zero error type");
    
    auto indexError = ErrorUtils::createIndexOutOfBoundsError("Custom message");
    assert_test(ErrorUtils::getErrorType(indexError) == "IndexOutOfBounds", "Index error type");
    assert_test(ErrorUtils::getErrorMessage(indexError) == "Custom message", "Index error custom message");
    
    auto nullError = ErrorUtils::createNullReferenceError();
    assert_test(ErrorUtils::getErrorType(nullError) == "NullReference", "Null reference error type");
    
    auto typeError = ErrorUtils::createTypeConversionError("Type error");
    assert_test(ErrorUtils::getErrorType(typeError) == "TypeConversion", "Type conversion error type");
    
    auto ioError = ErrorUtils::createIOError("IO error");
    assert_test(ErrorUtils::getErrorType(ioError) == "IOError", "IO error type");
}

void test_error_inspection_methods() {
    std::cout << "\n=== Testing Error Inspection Methods ===" << std::endl;
    
    // Test with error value
    auto error = ErrorUtils::createError("InspectError", "Inspect message");
    
    assert_test(ErrorUtils::isError(error), "isError detects error correctly");
    assert_test(!ErrorUtils::isSuccess(error), "isSuccess detects error correctly");
    
    const auto& errorValue = ErrorUtils::getError(error);
    assert_test(errorValue.errorType == "InspectError", "getError returns correct error");
    
    const auto* errorPtr = ErrorUtils::getErrorSafe(error);
    assert_test(errorPtr != nullptr, "getErrorSafe returns non-null for error");
    assert_test(errorPtr->errorType == "InspectError", "getErrorSafe returns correct error");
    
    // Test with success value
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    
    assert_test(!ErrorUtils::isError(successValue), "isError detects success correctly");
    assert_test(ErrorUtils::isSuccess(successValue), "isSuccess detects success correctly");
    
    assert_test(ErrorUtils::getErrorType(successValue).empty(), "getErrorType empty for success");
    assert_test(ErrorUtils::getErrorMessage(successValue).empty(), "getErrorMessage empty for success");
    assert_test(ErrorUtils::getErrorArguments(successValue).empty(), "getErrorArguments empty for success");
    assert_test(ErrorUtils::getErrorLocation(successValue) == 0, "getErrorLocation zero for success");
    
    const auto* successErrorPtr = ErrorUtils::getErrorSafe(successValue);
    assert_test(successErrorPtr == nullptr, "getErrorSafe returns null for success");
}

void test_error_wrapping_methods() {
    std::cout << "\n=== Testing Error Wrapping Methods ===" << std::endl;
    
    auto errorUnionType = std::make_shared<Type>(TypeTag::ErrorUnion);
    
    // Test success wrapping
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto wrappedSuccess = ErrorUtils::wrapAsSuccess(successValue, errorUnionType);
    
    assert_test(wrappedSuccess->type->tag == TypeTag::ErrorUnion, "Wrapped success has union type");
    assert_test(ErrorUtils::isSuccess(wrappedSuccess), "Wrapped success is success");
    
    // Test error wrapping
    ErrorValue errorValue("WrapError", "Wrap message");
    auto wrappedError = ErrorUtils::wrapAsError(errorValue, errorUnionType);
    
    assert_test(wrappedError->type->tag == TypeTag::ErrorUnion, "Wrapped error has union type");
    assert_test(ErrorUtils::isError(wrappedError), "Wrapped error is error");
    assert_test(ErrorUtils::getErrorType(wrappedError) == "WrapError", "Wrapped error has correct type");
    
    // Test ErrorUnion creation
    ErrorUnion errorUnion = ErrorUnion::success(successValue);
    auto unionValue = ErrorUtils::createErrorUnion(errorUnion, errorUnionType);
    
    assert_test(unionValue->type->tag == TypeTag::ErrorUnion, "ErrorUnion value has correct type");
    assert_test(ErrorUtils::isSuccess(unionValue), "ErrorUnion value is success");
}

void test_error_unwrapping_methods() {
    std::cout << "\n=== Testing Error Unwrapping Methods ===" << std::endl;
    
    // Test unwrapping success
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto unwrapped = ErrorUtils::unwrapSuccess(successValue);
    assert_test(unwrapped == successValue, "unwrapSuccess returns same value for success");
    
    auto unwrappedSafe = ErrorUtils::unwrapSuccessSafe(successValue);
    assert_test(unwrappedSafe == successValue, "unwrapSuccessSafe returns same value for success");
    
    // Test unwrapping error
    auto error = ErrorUtils::createError("UnwrapError", "Cannot unwrap");
    
    bool threwException = false;
    try {
        ErrorUtils::unwrapSuccess(error);
    } catch (const std::runtime_error&) {
        threwException = true;
    }
    assert_test(threwException, "unwrapSuccess throws for error");
    
    auto unwrappedErrorSafe = ErrorUtils::unwrapSuccessSafe(error);
    assert_test(unwrappedErrorSafe == nullptr, "unwrapSuccessSafe returns null for error");
}

void test_error_type_compatibility() {
    std::cout << "\n=== Testing Error Type Compatibility ===" << std::endl;
    
    assert_test(ErrorUtils::areErrorTypesCompatible("TestError", "TestError"), "Same types compatible");
    assert_test(!ErrorUtils::areErrorTypesCompatible("TestError", "OtherError"), "Different types not compatible");
    assert_test(!ErrorUtils::areErrorTypesCompatible("", "TestError"), "Empty and non-empty not compatible");
    assert_test(ErrorUtils::areErrorTypesCompatible("", ""), "Empty types compatible");
}

int main() {
    std::cout << "Running Comprehensive Error Value Representation Tests..." << std::endl;
    
    try {
        test_error_value_struct();
        test_error_union_helper();
        test_value_variant_integration();
        test_error_construction_methods();
        test_error_inspection_methods();
        test_error_wrapping_methods();
        test_error_unwrapping_methods();
        test_error_type_compatibility();
        
        std::cout << "\n🎉 All comprehensive error value tests passed!" << std::endl;
        std::cout << "\nTask 4 Implementation Summary:" << std::endl;
        std::cout << "✓ ErrorValue struct with error type, message, arguments, and source location" << std::endl;
        std::cout << "✓ ErrorValue integrated into Value variant" << std::endl;
        std::cout << "✓ ErrorUnion helper class for efficient tagged union operations" << std::endl;
        std::cout << "✓ Error value construction and inspection methods in ErrorUtils namespace" << std::endl;
        std::cout << "✓ Built-in error types (DivisionByZero, IndexOutOfBounds, etc.)" << std::endl;
        std::cout << "✓ Error wrapping and unwrapping utilities" << std::endl;
        std::cout << "✓ Type compatibility checking" << std::endl;
        std::cout << "✓ Comprehensive unit tests covering all functionality" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cout << "\n💥 Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}