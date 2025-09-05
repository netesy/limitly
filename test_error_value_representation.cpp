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

void test_error_value_construction() {
    std::cout << "\n=== Testing ErrorValue Construction ===" << std::endl;
    
    // Test basic error construction
    ErrorValue error1("TestError", "Test message");
    assert_test(error1.errorType == "TestError", "Basic error type");
    assert_test(error1.message == "Test message", "Basic error message");
    assert_test(error1.arguments.empty(), "Basic error no arguments");
    assert_test(error1.sourceLocation == 0, "Basic error default location");
    
    // Test error with arguments
    auto arg1 = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto arg2 = std::make_shared<Value>(std::make_shared<Type>(TypeTag::String), "test");
    std::vector<ValuePtr> args = {arg1, arg2};
    
    ErrorValue error2("ArgumentError", "Invalid arguments", args, 123);
    assert_test(error2.errorType == "ArgumentError", "Error with arguments type");
    assert_test(error2.message == "Invalid arguments", "Error with arguments message");
    assert_test(error2.arguments.size() == 2, "Error arguments count");
    assert_test(error2.sourceLocation == 123, "Error source location");
    
    // Test error toString
    std::string errorStr = error1.toString();
    assert_test(errorStr.find("TestError") != std::string::npos, "Error toString contains type");
    assert_test(errorStr.find("Test message") != std::string::npos, "Error toString contains message");
}

void test_error_union_construction() {
    std::cout << "\n=== Testing ErrorUnion Construction ===" << std::endl;
    
    // Test success union
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    ErrorUnion successUnion(successValue);
    
    assert_test(successUnion.isSuccess(), "Success union is success");
    assert_test(!successUnion.isError(), "Success union is not error");
    assert_test(successUnion.getTag() == ErrorUnion::Tag::SUCCESS, "Success union tag");
    assert_test(successUnion.getSuccessValue() == successValue, "Success union value");
    
    // Test error union
    ErrorValue errorValue("TestError", "Test message");
    ErrorUnion errorUnion(errorValue);
    
    assert_test(!errorUnion.isSuccess(), "Error union is not success");
    assert_test(errorUnion.isError(), "Error union is error");
    assert_test(errorUnion.getTag() == ErrorUnion::Tag::ERROR, "Error union tag");
    assert_test(errorUnion.getErrorValue().errorType == "TestError", "Error union error type");
    
    // Test error union with direct construction
    ErrorUnion directErrorUnion("DirectError", "Direct message");
    assert_test(directErrorUnion.isError(), "Direct error union is error");
    assert_test(directErrorUnion.getErrorType() == "DirectError", "Direct error union type");
    assert_test(directErrorUnion.getErrorMessage() == "Direct message", "Direct error union message");
}

void test_error_union_copy_move() {
    std::cout << "\n=== Testing ErrorUnion Copy/Move ===" << std::endl;
    
    try {
        // Test copy constructor with success
        auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
        ErrorUnion original(successValue);
        ErrorUnion copied(original);
        
        assert_test(copied.isSuccess(), "Copied success union is success");
        assert_test(copied.getSuccessValue() == successValue, "Copied success union value");
        
        // Test copy constructor with error
        ErrorValue errorValue("TestError", "Test message");
        ErrorUnion originalError(errorValue);
        ErrorUnion copiedError(originalError);
        
        assert_test(copiedError.isError(), "Copied error union is error");
        assert_test(copiedError.getErrorType() == "TestError", "Copied error union type");
        
        // Test assignment operator
        ErrorUnion assigned = original;
        assert_test(assigned.isSuccess(), "Assigned union is success");
        assert_test(assigned.getSuccessValue() == successValue, "Assigned union value");
    } catch (const std::exception& e) {
        std::cout << "Exception in copy/move test: " << e.what() << std::endl;
        throw;
    }
}

void test_error_union_safe_access() {
    std::cout << "\n=== Testing ErrorUnion Safe Access ===" << std::endl;
    
    // Test safe access with success
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto defaultValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 0);
    ErrorUnion successUnion(successValue);
    
    assert_test(successUnion.getSuccessValueOr(defaultValue) == successValue, "Success getSuccessValueOr");
    assert_test(successUnion.getErrorType().empty(), "Success getErrorType empty");
    assert_test(successUnion.getErrorMessage().empty(), "Success getErrorMessage empty");
    
    // Test safe access with error
    ErrorUnion errorUnion("TestError", "Test message");
    assert_test(errorUnion.getSuccessValueOr(defaultValue) == defaultValue, "Error getSuccessValueOr default");
    assert_test(errorUnion.getErrorType() == "TestError", "Error getErrorType");
    assert_test(errorUnion.getErrorMessage() == "Test message", "Error getErrorMessage");
}

void test_error_union_factory_methods() {
    std::cout << "\n=== Testing ErrorUnion Factory Methods ===" << std::endl;
    
    // Test success factory
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto successUnion = ErrorUnion::success(successValue);
    
    assert_test(successUnion.isSuccess(), "Factory success is success");
    assert_test(successUnion.getSuccessValue() == successValue, "Factory success value");
    
    // Test error factory
    auto errorUnion = ErrorUnion::error("FactoryError", "Factory message");
    assert_test(errorUnion.isError(), "Factory error is error");
    assert_test(errorUnion.getErrorType() == "FactoryError", "Factory error type");
    assert_test(errorUnion.getErrorMessage() == "Factory message", "Factory error message");
    
    // Test error factory with ErrorValue
    ErrorValue errorValue("ValueError", "Value message");
    auto errorUnion2 = ErrorUnion::error(errorValue);
    assert_test(errorUnion2.isError(), "Factory error from ErrorValue is error");
    assert_test(errorUnion2.getErrorType() == "ValueError", "Factory error from ErrorValue type");
}

void test_error_utils_creation() {
    std::cout << "\n=== Testing ErrorUtils Creation Functions ===" << std::endl;
    
    // Test basic error creation
    auto error = ErrorUtils::createError("TestError", "Test message");
    assert_test(ErrorUtils::isError(error), "Created error is error");
    assert_test(ErrorUtils::getErrorType(error) == "TestError", "Created error type");
    assert_test(ErrorUtils::getErrorMessage(error) == "Test message", "Created error message");
    
    // Test error creation with arguments
    auto arg1 = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    std::vector<ValuePtr> args = {arg1};
    auto errorWithArgs = ErrorUtils::createError("ArgError", "Arg message", args, 123);
    
    assert_test(ErrorUtils::isError(errorWithArgs), "Error with args is error");
    assert_test(ErrorUtils::getErrorArguments(errorWithArgs).size() == 1, "Error args count");
    assert_test(ErrorUtils::getErrorLocation(errorWithArgs) == 123, "Error location");
    
    // Test success creation
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto errorUnionType = std::make_shared<Type>(TypeTag::ErrorUnion);
    auto success = ErrorUtils::createSuccess(successValue, errorUnionType);
    
    assert_test(ErrorUtils::isSuccess(success), "Created success is success");
    assert_test(!ErrorUtils::isError(success), "Created success is not error");
}

void test_error_utils_inspection() {
    std::cout << "\n=== Testing ErrorUtils Inspection Functions ===" << std::endl;
    
    // Test with error value
    auto error = ErrorUtils::createError("InspectError", "Inspect message");
    
    assert_test(ErrorUtils::isError(error), "isError with error");
    assert_test(!ErrorUtils::isSuccess(error), "isSuccess with error");
    
    const auto& errorValue = ErrorUtils::getError(error);
    assert_test(errorValue.errorType == "InspectError", "getError type");
    assert_test(errorValue.message == "Inspect message", "getError message");
    
    const auto* errorPtr = ErrorUtils::getErrorSafe(error);
    assert_test(errorPtr != nullptr, "getErrorSafe not null");
    assert_test(errorPtr->errorType == "InspectError", "getErrorSafe type");
    
    // Test with success value
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    
    assert_test(!ErrorUtils::isError(successValue), "isError with success");
    assert_test(ErrorUtils::isSuccess(successValue), "isSuccess with success");
    assert_test(ErrorUtils::getErrorType(successValue).empty(), "getErrorType with success");
    assert_test(ErrorUtils::getErrorMessage(successValue).empty(), "getErrorMessage with success");
    assert_test(ErrorUtils::getErrorArguments(successValue).empty(), "getErrorArguments with success");
    assert_test(ErrorUtils::getErrorLocation(successValue) == 0, "getErrorLocation with success");
    
    const auto* successErrorPtr = ErrorUtils::getErrorSafe(successValue);
    assert_test(successErrorPtr == nullptr, "getErrorSafe with success is null");
}

void test_error_utils_wrapping() {
    std::cout << "\n=== Testing ErrorUtils Wrapping Functions ===" << std::endl;
    
    auto errorUnionType = std::make_shared<Type>(TypeTag::ErrorUnion);
    
    // Test success wrapping
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto wrappedSuccess = ErrorUtils::wrapAsSuccess(successValue, errorUnionType);
    
    assert_test(wrappedSuccess->type->tag == TypeTag::ErrorUnion, "Wrapped success type");
    assert_test(ErrorUtils::isSuccess(wrappedSuccess), "Wrapped success is success");
    
    // Test error wrapping
    ErrorValue errorValue("WrapError", "Wrap message");
    auto wrappedError = ErrorUtils::wrapAsError(errorValue, errorUnionType);
    
    assert_test(wrappedError->type->tag == TypeTag::ErrorUnion, "Wrapped error type");
    assert_test(ErrorUtils::isError(wrappedError), "Wrapped error is error");
    assert_test(ErrorUtils::getErrorType(wrappedError) == "WrapError", "Wrapped error type name");
    
    // Test ErrorUnion creation
    ErrorUnion errorUnion = ErrorUnion::success(successValue);
    auto unionValue = ErrorUtils::createErrorUnion(errorUnion, errorUnionType);
    
    assert_test(unionValue->type->tag == TypeTag::ErrorUnion, "ErrorUnion value type");
    assert_test(ErrorUtils::isSuccess(unionValue), "ErrorUnion value is success");
}

void test_error_utils_unwrapping() {
    std::cout << "\n=== Testing ErrorUtils Unwrapping Functions ===" << std::endl;
    
    // Test unwrapping success
    auto successValue = std::make_shared<Value>(std::make_shared<Type>(TypeTag::Int), 42);
    auto unwrapped = ErrorUtils::unwrapSuccess(successValue);
    assert_test(unwrapped == successValue, "Unwrap success returns same value");
    
    auto unwrappedSafe = ErrorUtils::unwrapSuccessSafe(successValue);
    assert_test(unwrappedSafe == successValue, "Unwrap success safe returns same value");
    
    // Test unwrapping error (should throw)
    auto error = ErrorUtils::createError("UnwrapError", "Cannot unwrap");
    
    bool threwException = false;
    try {
        ErrorUtils::unwrapSuccess(error);
    } catch (const std::runtime_error&) {
        threwException = true;
    }
    assert_test(threwException, "Unwrap error throws exception");
    
    auto unwrappedErrorSafe = ErrorUtils::unwrapSuccessSafe(error);
    assert_test(unwrappedErrorSafe == nullptr, "Unwrap error safe returns null");
}

void test_builtin_error_creation() {
    std::cout << "\n=== Testing Built-in Error Creation ===" << std::endl;
    
    // Test built-in error types
    auto divError = ErrorUtils::createDivisionByZeroError();
    assert_test(ErrorUtils::getErrorType(divError) == "DivisionByZero", "Division by zero error type");
    
    auto indexError = ErrorUtils::createIndexOutOfBoundsError("Index 5 out of bounds");
    assert_test(ErrorUtils::getErrorType(indexError) == "IndexOutOfBounds", "Index out of bounds error type");
    assert_test(ErrorUtils::getErrorMessage(indexError) == "Index 5 out of bounds", "Index error custom message");
    
    auto nullError = ErrorUtils::createNullReferenceError();
    assert_test(ErrorUtils::getErrorType(nullError) == "NullReference", "Null reference error type");
    
    auto typeError = ErrorUtils::createTypeConversionError("Cannot convert string to int");
    assert_test(ErrorUtils::getErrorType(typeError) == "TypeConversion", "Type conversion error type");
    assert_test(ErrorUtils::getErrorMessage(typeError) == "Cannot convert string to int", "Type error custom message");
    
    auto ioError = ErrorUtils::createIOError("File not found");
    assert_test(ErrorUtils::getErrorType(ioError) == "IOError", "IO error type");
    assert_test(ErrorUtils::getErrorMessage(ioError) == "File not found", "IO error custom message");
}

void test_error_type_compatibility() {
    std::cout << "\n=== Testing Error Type Compatibility ===" << std::endl;
    
    // Test error type compatibility
    assert_test(ErrorUtils::areErrorTypesCompatible("TestError", "TestError"), "Same error types compatible");
    assert_test(!ErrorUtils::areErrorTypesCompatible("TestError", "OtherError"), "Different error types not compatible");
    assert_test(!ErrorUtils::areErrorTypesCompatible("", "TestError"), "Empty and non-empty not compatible");
    assert_test(ErrorUtils::areErrorTypesCompatible("", ""), "Empty types compatible");
}

void test_value_integration() {
    std::cout << "\n=== Testing Value Integration ===" << std::endl;
    
    // Test ErrorValue in Value variant
    auto errorType = std::make_shared<Type>(TypeTag::UserDefined);
    ErrorValue errorValue("IntegrationError", "Integration message");
    Value errorValueWrapper(errorType, errorValue);
    
    assert_test(std::holds_alternative<ErrorValue>(errorValueWrapper.data), "ErrorValue in Value variant");
    
    // Test toString integration
    std::string errorStr = errorValueWrapper.toString();
    assert_test(errorStr.find("IntegrationError") != std::string::npos, "ErrorValue toString in Value");
    
    std::string rawStr = errorValueWrapper.getRawString();
    assert_test(rawStr.find("IntegrationError") != std::string::npos, "ErrorValue getRawString in Value");
}

int main() {
    std::cout << "Running Error Value Representation Tests..." << std::endl;
    
    try {
        test_error_value_construction();
        test_error_union_construction();
        test_error_union_copy_move();
        test_error_union_safe_access();
        test_error_union_factory_methods();
        test_error_utils_creation();
        test_error_utils_inspection();
        test_error_utils_wrapping();
        test_error_utils_unwrapping();
        test_builtin_error_creation();
        test_error_type_compatibility();
        test_value_integration();
        
        std::cout << "\n🎉 All error value representation tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "\n💥 Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}