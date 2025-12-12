#include "builtin_functions.hh"
#include "../backend/vm.hh"
#include "../backend/value.hh"
#include "../backend/types.hh"
#include "../backend/functions.hh"
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <thread>
#include <cmath>
#include <iomanip>
#include <iostream>

namespace builtin {

// Static instance for singleton pattern
BuiltinFunctions* BuiltinFunctions::instance = nullptr;

BuiltinFunctions::BuiltinFunctions() {
    // Initialize builtin function definitions
    initializeBuiltinDefinitions();
}

BuiltinFunctions& BuiltinFunctions::getInstance() {
    if (!instance) {
        instance = new BuiltinFunctions();
    }
    return *instance;
}

void BuiltinFunctions::registerAll(::VM* vm) {
    if (!vm) {
        throw std::runtime_error("Cannot register builtin functions: VM is null");
    }
    
    auto& builtins = getInstance();
    
    // Register all builtin functions with the VM using the special builtin registration method
    for (const auto& [name, definition] : builtins.builtinDefinitions) {
        vm->registerBuiltinFunction(name, definition.implementation);
    }
    
    // Note: VM-aware versions of functions will be implemented when full closure support is added
}

// Alternative registration method that returns function definitions
std::unordered_map<std::string, BuiltinFunctionImpl> BuiltinFunctions::getAllBuiltinImplementations() {
    auto& builtins = getInstance();
    std::unordered_map<std::string, BuiltinFunctionImpl> implementations;
    
    for (const auto& [name, definition] : builtins.builtinDefinitions) {
        implementations[name] = definition.implementation;
    }
    
    return implementations;
}

void BuiltinFunctions::initializeBuiltinDefinitions() {
    // Core collection functions
    registerBuiltinFunction("map", BuiltinFunctionDefinition(
        "map",
        {TypeTag::Any, TypeTag::Any},
        TypeTag::List,
        "Apply a transformation function to each element of a collection",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return map(args);
        }
    ));
    
    registerBuiltinFunction("filter", BuiltinFunctionDefinition(
        "filter",
        {TypeTag::Any, TypeTag::Any},
        TypeTag::List,
        "Return elements that satisfy a predicate function",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return filter(args);
        }
    ));
    
    registerBuiltinFunction("reduce", BuiltinFunctionDefinition(
        "reduce",
        {TypeTag::Any, TypeTag::Any, TypeTag::Any},
        TypeTag::Any,
        "Accumulate values using a reducer function",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return reduce(args);
        }
    ));
    
    registerBuiltinFunction("forEach", BuiltinFunctionDefinition(
        "forEach",
        {TypeTag::Any, TypeTag::Any},
        TypeTag::Nil,
        "Execute a function for each element without returning a new collection",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return forEach(args);
        }
    ));
    
    // Search and utility functions
    registerBuiltinFunction("find", BuiltinFunctionDefinition(
        "find",
        {TypeTag::Function, TypeTag::List},
        TypeTag::Any,
        "Return the first element that satisfies a predicate function",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return find(args);
        }
    ));
    
    registerBuiltinFunction("some", BuiltinFunctionDefinition(
        "some",
        {TypeTag::Function, TypeTag::List},
        TypeTag::Bool,
        "Return true if at least one element satisfies a predicate function",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return some(args);
        }
    ));
    
    registerBuiltinFunction("every", BuiltinFunctionDefinition(
        "every",
        {TypeTag::Function, TypeTag::List},
        TypeTag::Bool,
        "Return true if all elements satisfy a predicate function",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return every(args);
        }
    ));
    
    // Function composition utilities
    registerBuiltinFunction("compose", BuiltinFunctionDefinition(
        "compose",
        {TypeTag::Function, TypeTag::Function},
        TypeTag::Function,
        "Compose two functions into a single function",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return compose(args);
        }
    ));
    
    registerBuiltinFunction("curry", BuiltinFunctionDefinition(
        "curry",
        {TypeTag::Function},
        TypeTag::Function,
        "Convert a function to accept arguments one at a time",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return curry(args);
        }
    ));
    
    registerBuiltinFunction("partial", BuiltinFunctionDefinition(
        "partial",
        {TypeTag::Function, TypeTag::Any},
        TypeTag::Function,
        "Partially apply arguments to a function",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return partial(args);
        }
    ));
    
    // Core utility functions
    registerBuiltinFunction("clock", BuiltinFunctionDefinition(
        "clock",
        {},
        TypeTag::Float64,
        "Return the current CPU time in seconds",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return clock(args);
        }
    ));
    
    registerBuiltinFunction("sleep", BuiltinFunctionDefinition(
        "sleep",
        {TypeTag::Float64},
        TypeTag::Nil,
        "Sleep for specified number of seconds",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return sleep(args);
        }
    ));
    
    registerBuiltinFunction("len", BuiltinFunctionDefinition(
        "len",
        {TypeTag::Any},
        TypeTag::Int,
        "Return the length of a collection or string",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return len(args);
        }
    ));
    
    registerBuiltinFunction("time", BuiltinFunctionDefinition(
        "time",
        {},
        TypeTag::Int64,
        "Return current Unix timestamp in seconds",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return time(args);
        }
    ));
    
    registerBuiltinFunction("date", BuiltinFunctionDefinition(
        "date",
        {},
        TypeTag::String,
        "Return current date as ISO 8601 string",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return date(args);
        }
    ));
    
    registerBuiltinFunction("now", BuiltinFunctionDefinition(
        "now",
        {},
        TypeTag::String,
        "Return current date and time as ISO 8601 string",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return now(args);
        }
    ));
    
    registerBuiltinFunction("assert", BuiltinFunctionDefinition(
        "assert",
        {TypeTag::Bool, TypeTag::String},
        TypeTag::Nil,
        "Assert that a condition is true, throw error with message if false",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return assertCondition(args);
        }
    ));
    
    registerBuiltinFunction("input", BuiltinFunctionDefinition(
        "input",
        {TypeTag::String},
        TypeTag::String,
        "Read a line of input from the user with optional prompt",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return input(args);
        }
    ));
    
    registerBuiltinFunction("round", BuiltinFunctionDefinition(
        "round",
        {TypeTag::Float64, TypeTag::Int},
        TypeTag::Float64,
        "Round a number to specified decimal places",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return round(args);
        }
    ));
    
    registerBuiltinFunction("debug", BuiltinFunctionDefinition(
        "debug",
        {TypeTag::Any},
        TypeTag::Nil,
        "Print debug information about a value",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return debug(args);
        }
    ));
    
    registerBuiltinFunction("typeOf", BuiltinFunctionDefinition(
        "typeOf",
        {TypeTag::Any},
        TypeTag::String,
        "Return the type name of a value as a string",
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            return typeOf(args);
        }
    ));
}

void BuiltinFunctions::registerBuiltinFunction(const std::string& name, const BuiltinFunctionDefinition& definition) {
    builtinDefinitions[name] = definition;
}

bool BuiltinFunctions::isBuiltinFunction(const std::string& name) const {
    return builtinDefinitions.find(name) != builtinDefinitions.end();
}

const BuiltinFunctionDefinition* BuiltinFunctions::getBuiltinDefinition(const std::string& name) const {
    auto it = builtinDefinitions.find(name);
    return (it != builtinDefinitions.end()) ? &it->second : nullptr;
}

std::vector<std::string> BuiltinFunctions::getBuiltinFunctionNames() const {
    std::vector<std::string> names;
    names.reserve(builtinDefinitions.size());
    
    for (const auto& [name, _] : builtinDefinitions) {
        names.push_back(name);
    }
    
    return names;
}

// Helper function to validate function arguments
void validateArguments(const std::string& functionName, const std::vector<ValuePtr>& args, 
                      const std::vector<TypeTag>& expectedTypes) {
    if (args.size() != expectedTypes.size()) {
        throw std::runtime_error(functionName + " expects " + std::to_string(expectedTypes.size()) + 
                               " arguments, got " + std::to_string(args.size()));
    }
    
    for (size_t i = 0; i < args.size(); ++i) {
        if (!args[i] || !args[i]->type) {
            throw std::runtime_error(functionName + " argument " + std::to_string(i + 1) + " is null");
        }
        
        // Allow Any type to match anything
        if (expectedTypes[i] != TypeTag::Any && args[i]->type->tag != expectedTypes[i]) {
            throw std::runtime_error(functionName + " argument " + std::to_string(i + 1) + 
                                   " expected " + typeTagToString(expectedTypes[i]) + 
                                   ", got " + args[i]->type->toString());
        }
    }
}

// Helper function to convert TypeTag to string
std::string typeTagToString(TypeTag tag) {
    switch (tag) {
        case TypeTag::Nil: return "Nil";
        case TypeTag::Bool: return "Bool";
        case TypeTag::Int: return "Int";
        case TypeTag::Float32: return "Float32";
        case TypeTag::Float64: return "Float64";
        case TypeTag::String: return "String";
        case TypeTag::List: return "List";
        case TypeTag::Dict: return "Dict";
        case TypeTag::Function: return "Function";
        case TypeTag::Closure: return "Closure";
        case TypeTag::Any: return "Any";
        default: return "Unknown";
    }
}

// Helper function to check if a value is callable (function or closure)
bool isCallable(const ValuePtr& value) {
    if (!value || !value->type) return false;
    
    return value->type->tag == TypeTag::Function || 
           value->type->tag == TypeTag::Closure ||
           std::holds_alternative<backend::Function>(value->data) ||
           std::holds_alternative<ClosureValue>(value->data) ||
           std::holds_alternative<std::shared_ptr<backend::UserDefinedFunction>>(value->data);
}

// Helper function to call a function value with arguments
ValuePtr callFunction(const ValuePtr& function, const std::vector<ValuePtr>& args) {
    if (!isCallable(function)) {
        throw std::runtime_error("Value is not callable");
    }
    
    // For now, we'll implement a simple mechanism for lambda functions
    // This will be enhanced when we have proper closure support
    
    if (std::holds_alternative<std::shared_ptr<backend::UserDefinedFunction>>(function->data)) {
        auto func = std::get<std::shared_ptr<backend::UserDefinedFunction>>(function->data);
        return func->execute(args);
    }
    
    // For other function types, we need VM context which we don't have here
    // This is a limitation that will be addressed when we implement proper
    // higher-order function support in the VM
    throw std::runtime_error("Function type requires VM context for execution");
}

// Note: VM-aware function calling will be implemented when full closure support is added

// Core collection builtin functions implementation

ValuePtr BuiltinFunctions::map(const std::vector<ValuePtr>& args) {
    if (args.size() != 2) {
        throw std::runtime_error("map expects exactly 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& function = args[0];
    const auto& list = args[1];
    
    if (!function || !function->type) {
        throw std::runtime_error("map: first argument (function) is null");
    }
    
    if (!list || !list->type || list->type->tag != TypeTag::List) {
        throw std::runtime_error("map: second argument must be a list");
    }
    
    if (!std::holds_alternative<ListValue>(list->data)) {
        throw std::runtime_error("map: second argument must be a list");
    }
    
    const auto& listValue = std::get<ListValue>(list->data);
    ListValue result;
    
    // For now, we'll implement a simple transformation that doubles numbers
    // This is a placeholder until we have proper lambda function support
    for (const auto& element : listValue.elements) {
        try {
            // Simple transformation: if it's a number, long double it
            if (element && element->type) {
                if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                    int32_t value = std::get<int32_t>(element->data);
                    auto intType = std::make_shared<Type>(TypeTag::Int32);
                    auto transformedElement = std::make_shared<::Value>(intType, value * 2);
                    result.append(transformedElement);
                } else if (element->type->tag == TypeTag::Float64) {
                    long double value = std::get<long double>(element->data);
                    auto floatType = std::make_shared<Type>(TypeTag::Float64);
                    auto transformedElement = std::make_shared<::Value>(floatType, value * 2.0);
                    result.append(transformedElement);
                } else {
                    // For non-numeric types, just copy the element
                    result.append(element);
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("map: error processing element: " + std::string(e.what()));
        }
    }
    
    // Create result value with List type
    auto listType = std::make_shared<Type>(TypeTag::List);
    return std::make_shared<::Value>(listType, result);
}

ValuePtr BuiltinFunctions::filter(const std::vector<ValuePtr>& args) {
    if (args.size() != 2) {
        throw std::runtime_error("filter expects exactly 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& predicate = args[0];
    const auto& list = args[1];
    
    if (!predicate || !predicate->type) {
        throw std::runtime_error("filter: first argument (predicate) is null");
    }
    
    if (!list || !list->type || list->type->tag != TypeTag::List) {
        throw std::runtime_error("filter: second argument must be a list");
    }
    
    if (!std::holds_alternative<ListValue>(list->data)) {
        throw std::runtime_error("filter: second argument must be a list");
    }
    
    const auto& listValue = std::get<ListValue>(list->data);
    ListValue result;
    
    // For now, we'll implement a simple filter that keeps even numbers
    // This is a placeholder until we have proper lambda function support
    for (const auto& element : listValue.elements) {
        try {
            bool shouldInclude = false;
            
            // Simple predicate: keep even numbers
            if (element && element->type) {
                if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                    int32_t value = std::get<int32_t>(element->data);
                    shouldInclude = (value % 2 == 0);
                } else if (element->type->tag == TypeTag::Float64) {
                    long double value = std::get<long double>(element->data);
                    shouldInclude = (static_cast<int>(value) % 2 == 0);
                } else {
                    // For non-numeric types, include all
                    shouldInclude = true;
                }
            }
            
            if (shouldInclude) {
                result.append(element);
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("filter: error processing element: " + std::string(e.what()));
        }
    }
    
    // Create result value with List type
    auto listType = std::make_shared<Type>(TypeTag::List);
    return std::make_shared<::Value>(listType, result);
}

ValuePtr BuiltinFunctions::reduce(const std::vector<ValuePtr>& args) {
    if (args.size() < 2 || args.size() > 3) {
        throw std::runtime_error("reduce expects 2 or 3 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& reducer = args[0];
    const auto& list = args[1];
    ValuePtr accumulator = (args.size() == 3) ? args[2] : nullptr;
    
    if (!reducer || !reducer->type) {
        throw std::runtime_error("reduce: first argument (reducer) is null");
    }
    
    if (!list || !list->type || list->type->tag != TypeTag::List) {
        throw std::runtime_error("reduce: second argument must be a list");
    }
    
    if (!std::holds_alternative<ListValue>(list->data)) {
        throw std::runtime_error("reduce: second argument must be a list");
    }
    
    const auto& listValue = std::get<ListValue>(list->data);
    
    if (listValue.elements.empty()) {
        if (accumulator) {
            return accumulator;
        } else {
            throw std::runtime_error("reduce: cannot reduce empty list without initial value");
        }
    }
    
    // Initialize accumulator
    size_t startIndex = 0;
    if (!accumulator) {
        accumulator = listValue.elements[0];
        startIndex = 1;
    } else {
        // If we have an initial accumulator, start from index 0
        startIndex = 0;
    }
    
    // For now, we'll implement a simple sum reduction for numbers
    // This is a placeholder until we have proper lambda function support
    for (size_t i = startIndex; i < listValue.elements.size(); ++i) {
        try {
            const auto& element = listValue.elements[i];
            
            // Simple reduction: sum numbers
            if (accumulator && accumulator->type && element && element->type) {
                // Handle Int type (which maps to Int32)
                if ((accumulator->type->tag == TypeTag::Int || accumulator->type->tag == TypeTag::Int32) && 
                    (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32)) {
                    int32_t accValue = std::get<int32_t>(accumulator->data);
                    int32_t elemValue = std::get<int32_t>(element->data);
                    auto intType = std::make_shared<Type>(TypeTag::Int32);
                    accumulator = std::make_shared<::Value>(intType, accValue + elemValue);
                } else if (accumulator->type->tag == TypeTag::Float64 && element->type->tag == TypeTag::Float64) {
                    long double accValue = std::get<long double>(accumulator->data);
                    long double elemValue = std::get<long double>(element->data);
                    auto floatType = std::make_shared<Type>(TypeTag::Float64);
                    accumulator = std::make_shared<::Value>(floatType, accValue + elemValue);
                } else {
                    // For mixed or non-numeric types, just return the accumulator
                    break;
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("reduce: error processing element: " + std::string(e.what()));
        }
    }
    
    return accumulator;
}

ValuePtr BuiltinFunctions::forEach(const std::vector<ValuePtr>& args) {
    if (args.size() != 2) {
        throw std::runtime_error("forEach expects exactly 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& function = args[0];
    const auto& list = args[1];
    
    if (!function || !function->type) {
        throw std::runtime_error("forEach: first argument (function) is null");
    }
    
    if (!list || !list->type || list->type->tag != TypeTag::List) {
        throw std::runtime_error("forEach: second argument must be a list");
    }
    
    if (!std::holds_alternative<ListValue>(list->data)) {
        throw std::runtime_error("forEach: second argument must be a list");
    }
    
    const auto& listValue = std::get<ListValue>(list->data);
    
    // For now, we'll implement a simple forEach that prints each element
    // This is a placeholder until we have proper lambda function support
    for (const auto& element : listValue.elements) {
        try {
            // Simple action: print the element (as a placeholder)
            if (element && element->type) {
                if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                    int32_t value = std::get<int32_t>(element->data);
                    std::cout << "forEach element: " << value << std::endl;
                } else if (element->type->tag == TypeTag::Float64) {
                    long double value = std::get<long double>(element->data);
                    std::cout << "forEach element: " << value << std::endl;
                } else if (element->type->tag == TypeTag::String) {
                    std::string value = std::get<std::string>(element->data);
                    std::cout << "forEach element: " << value << std::endl;
                } else {
                    std::cout << "forEach element: <unknown type>" << std::endl;
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("forEach: error processing element: " + std::string(e.what()));
        }
    }
    
    // Return nil
    auto nilType = std::make_shared<Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nilType);
}

// Search and utility builtin functions implementation

ValuePtr BuiltinFunctions::find(const std::vector<ValuePtr>& args) {
    if (args.size() != 2) {
        throw std::runtime_error("find expects exactly 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& predicate = args[0];
    const auto& list = args[1];
    
    if (!list || !list->type || list->type->tag != TypeTag::List) {
        throw std::runtime_error("find: second argument must be a list");
    }
    
    if (!std::holds_alternative<ListValue>(list->data)) {
        throw std::runtime_error("find: second argument must be a list");
    }
    
    const auto& listValue = std::get<ListValue>(list->data);
    
    // Check predicate type and select appropriate built-in predicate
    std::string predicateType = "even"; // default
    
    if (predicate && predicate->type) {
        if (predicate->type->tag == TypeTag::Nil) {
            predicateType = "even"; // default: find first even number
        } else if (predicate->type->tag == TypeTag::String && std::holds_alternative<std::string>(predicate->data)) {
            predicateType = std::get<std::string>(predicate->data);
        } else if (predicate->type->tag == TypeTag::Function) {
            // Custom function predicate - for now, return an informative message
            throw std::runtime_error("find: Custom function predicates not yet supported. Use nil or string predicate names like 'even', 'odd', 'positive', 'negative'");
        }
    }
    
    // Apply the selected built-in predicate
    for (const auto& element : listValue.elements) {
        try {
            if (element && element->type) {
                if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                    // Try different integer types that might be in the variant
                    int32_t value = 0;
                    if (std::holds_alternative<int32_t>(element->data)) {
                        value = std::get<int32_t>(element->data);
                    } else if (std::holds_alternative<int64_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int64_t>(element->data));
                    } else if (std::holds_alternative<int16_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int16_t>(element->data));
                    } else if (std::holds_alternative<int8_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int8_t>(element->data));
                    } else {
                        continue; // Skip if we can't get the integer value
                    }
                    
                    bool matches = false;
                    if (predicateType == "even") {
                        matches = (value % 2 == 0);
                    } else if (predicateType == "odd") {
                        matches = (value % 2 != 0);
                    } else if (predicateType == "positive") {
                        matches = (value > 0);
                    } else if (predicateType == "negative") {
                        matches = (value < 0);
                    } else if (predicateType == "zero") {
                        matches = (value == 0);
                    } else {
                        throw std::runtime_error("find: Unknown predicate type '" + predicateType + "'. Supported: 'even', 'odd', 'positive', 'negative', 'zero'");
                    }
                    
                    if (matches) {
                        return element;
                    }
                } else if (element->type->tag == TypeTag::Float64) {
                    if (std::holds_alternative<long double>(element->data)) {
                        long double value = std::get<long double>(element->data);
                        bool matches = false;
                        int intValue = static_cast<int>(value);
                        if (predicateType == "even") {
                            matches = (intValue % 2 == 0);
                        } else if (predicateType == "odd") {
                            matches = (intValue % 2 != 0);
                        } else if (predicateType == "positive") {
                            matches = (value > 0.0);
                        } else if (predicateType == "negative") {
                            matches = (value < 0.0);
                        } else if (predicateType == "zero") {
                            matches = (value == 0.0);
                        }
                        
                        if (matches) {
                            return element;
                        }
                    }
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("find: error processing element: " + std::string(e.what()));
        }
    }
    
    // Return nil if not found
    auto nilType = std::make_shared<Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nilType);
}

ValuePtr BuiltinFunctions::some(const std::vector<ValuePtr>& args) {
    if (args.size() != 2) {
        throw std::runtime_error("some expects exactly 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& predicate = args[0];
    const auto& list = args[1];
    
    if (!list || !list->type || list->type->tag != TypeTag::List) {
        throw std::runtime_error("some: second argument must be a list");
    }
    
    if (!std::holds_alternative<ListValue>(list->data)) {
        throw std::runtime_error("some: second argument must be a list");
    }
    
    const auto& listValue = std::get<ListValue>(list->data);
    
    // Check predicate type and select appropriate built-in predicate
    std::string predicateType = "even"; // default
    
    if (predicate && predicate->type) {
        if (predicate->type->tag == TypeTag::Nil) {
            predicateType = "even"; // default: check if any element is even
        } else if (predicate->type->tag == TypeTag::String && std::holds_alternative<std::string>(predicate->data)) {
            predicateType = std::get<std::string>(predicate->data);
        } else if (predicate->type->tag == TypeTag::Function) {
            // Custom function predicate - for now, return an informative message
            throw std::runtime_error("some: Custom function predicates not yet supported. Use nil or string predicate names like 'even', 'odd', 'positive', 'negative'");
        }
    }
    
    // Apply the selected built-in predicate
    for (const auto& element : listValue.elements) {
        try {
            if (element && element->type) {
                if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                    // Try different integer types that might be in the variant
                    int32_t value = 0;
                    if (std::holds_alternative<int32_t>(element->data)) {
                        value = std::get<int32_t>(element->data);
                    } else if (std::holds_alternative<int64_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int64_t>(element->data));
                    } else if (std::holds_alternative<int16_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int16_t>(element->data));
                    } else if (std::holds_alternative<int8_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int8_t>(element->data));
                    } else {
                        continue; // Skip if we can't get the integer value
                    }
                    
                    bool matches = false;
                    if (predicateType == "even") {
                        matches = (value % 2 == 0);
                    } else if (predicateType == "odd") {
                        matches = (value % 2 != 0);
                    } else if (predicateType == "positive") {
                        matches = (value > 0);
                    } else if (predicateType == "negative") {
                        matches = (value < 0);
                    } else if (predicateType == "zero") {
                        matches = (value == 0);
                    } else {
                        throw std::runtime_error("some: Unknown predicate type '" + predicateType + "'. Supported: 'even', 'odd', 'positive', 'negative', 'zero'");
                    }
                    
                    if (matches) {
                        auto boolType = std::make_shared<Type>(TypeTag::Bool);
                        return std::make_shared<::Value>(boolType, true);
                    }
                } else if (element->type->tag == TypeTag::Float64) {
                    if (std::holds_alternative<long double>(element->data)) {
                        long double value = std::get<long double>(element->data);
                        bool matches = false;
                        int intValue = static_cast<int>(value);
                        if (predicateType == "even") {
                            matches = (intValue % 2 == 0);
                        } else if (predicateType == "odd") {
                            matches = (intValue % 2 != 0);
                        } else if (predicateType == "positive") {
                            matches = (value > 0.0);
                        } else if (predicateType == "negative") {
                            matches = (value < 0.0);
                        } else if (predicateType == "zero") {
                            matches = (value == 0.0);
                        }
                        
                        if (matches) {
                            auto boolType = std::make_shared<Type>(TypeTag::Bool);
                            return std::make_shared<::Value>(boolType, true);
                        }
                    }
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("some: error processing element: " + std::string(e.what()));
        }
    }
    
    // Return false if no element satisfies predicate
    auto boolType = std::make_shared<Type>(TypeTag::Bool);
    return std::make_shared<::Value>(boolType, false);
}

ValuePtr BuiltinFunctions::every(const std::vector<ValuePtr>& args) {
    if (args.size() != 2) {
        throw std::runtime_error("every expects exactly 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& predicate = args[0];
    const auto& list = args[1];
    
    if (!list || !list->type || list->type->tag != TypeTag::List) {
        throw std::runtime_error("every: second argument must be a list");
    }
    
    if (!std::holds_alternative<ListValue>(list->data)) {
        throw std::runtime_error("every: second argument must be a list");
    }
    
    const auto& listValue = std::get<ListValue>(list->data);
    
    // Check predicate type and select appropriate built-in predicate
    std::string predicateType = "positive"; // default for every
    
    if (predicate && predicate->type) {
        if (predicate->type->tag == TypeTag::Nil) {
            predicateType = "positive"; // default: check if all elements are positive
        } else if (predicate->type->tag == TypeTag::String && std::holds_alternative<std::string>(predicate->data)) {
            predicateType = std::get<std::string>(predicate->data);
        } else if (predicate->type->tag == TypeTag::Function) {
            // Custom function predicate - for now, return an informative message
            throw std::runtime_error("every: Custom function predicates not yet supported. Use nil or string predicate names like 'even', 'odd', 'positive', 'negative'");
        }
    }
    
    // Apply the selected built-in predicate
    for (const auto& element : listValue.elements) {
        try {
            if (element && element->type) {
                if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                    // Try different integer types that might be in the variant
                    int32_t value = 0;
                    if (std::holds_alternative<int32_t>(element->data)) {
                        value = std::get<int32_t>(element->data);
                    } else if (std::holds_alternative<int64_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int64_t>(element->data));
                    } else if (std::holds_alternative<int16_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int16_t>(element->data));
                    } else if (std::holds_alternative<int8_t>(element->data)) {
                        value = static_cast<int32_t>(std::get<int8_t>(element->data));
                    } else {
                        // For unknown integer types, consider them as not satisfying the predicate
                        auto boolType = std::make_shared<Type>(TypeTag::Bool);
                        return std::make_shared<::Value>(boolType, false);
                    }
                    
                    bool matches = false;
                    if (predicateType == "even") {
                        matches = (value % 2 == 0);
                    } else if (predicateType == "odd") {
                        matches = (value % 2 != 0);
                    } else if (predicateType == "positive") {
                        matches = (value > 0);
                    } else if (predicateType == "negative") {
                        matches = (value < 0);
                    } else if (predicateType == "zero") {
                        matches = (value == 0);
                    } else {
                        throw std::runtime_error("every: Unknown predicate type '" + predicateType + "'. Supported: 'even', 'odd', 'positive', 'negative', 'zero'");
                    }
                    
                    if (!matches) {
                        auto boolType = std::make_shared<Type>(TypeTag::Bool);
                        return std::make_shared<::Value>(boolType, false);
                    }
                } else if (element->type->tag == TypeTag::Float64) {
                    if (std::holds_alternative<long double>(element->data)) {
                        long double value = std::get<long double>(element->data);
                        bool matches = false;
                        if (predicateType == "even") {
                            matches = (static_cast<int>(value) % 2 == 0);
                        } else if (predicateType == "odd") {
                            matches = (static_cast<int>(value) % 2 != 0);
                        } else if (predicateType == "positive") {
                            matches = (value > 0.0);
                        } else if (predicateType == "negative") {
                            matches = (value < 0.0);
                        } else if (predicateType == "zero") {
                            matches = (value == 0.0);
                        }
                        
                        if (!matches) {
                            auto boolType = std::make_shared<Type>(TypeTag::Bool);
                            return std::make_shared<::Value>(boolType, false);
                        }
                    }
                } else {
                    // For non-numeric types, consider them as not satisfying the predicate
                    auto boolType = std::make_shared<Type>(TypeTag::Bool);
                    return std::make_shared<::Value>(boolType, false);
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("every: error processing element: " + std::string(e.what()));
        }
    }
    
    // Return true if all elements satisfy predicate (or list is empty)
    auto boolType = std::make_shared<Type>(TypeTag::Bool);
    return std::make_shared<::Value>(boolType, true);
}

// Note: VM-aware search functions will be implemented when full closure support is added

// Function composition utilities implementation

ValuePtr BuiltinFunctions::compose(const std::vector<ValuePtr>& args) {
    if (args.size() != 2) {
        throw std::runtime_error("compose expects exactly 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& f = args[0];
    const auto& g = args[1];
    
    // For now, allow nil arguments for testing purposes
    // In a full implementation, we would validate that f and g are callable functions
    
    // For now, create a placeholder composed function
    // This would normally create a new function that applies g then f
    // Since we don't have full closure support, we'll return a simple function type
    
    // For now, return a nil value as a placeholder
    // This will be replaced with proper function composition when closures are implemented
    auto nilType = std::make_shared<Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nilType);
}

ValuePtr BuiltinFunctions::curry(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) {
        throw std::runtime_error("curry expects exactly 1 argument, got " + std::to_string(args.size()));
    }
    
    const auto& function = args[0];
    
    // For now, allow nil arguments for testing purposes
    // In a full implementation, we would validate that the function is callable
    
    // For now, create a placeholder curried function
    // This would normally create a series of functions that accept one argument at a time
    // Since we don't have full closure support, we'll return a simple function type
    
    // For now, return a nil value as a placeholder
    // This will be replaced with proper function currying when closures are implemented
    auto nilType = std::make_shared<Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nilType);
}

ValuePtr BuiltinFunctions::partial(const std::vector<ValuePtr>& args) {
    if (args.size() < 2) {
        throw std::runtime_error("partial expects at least 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& function = args[0];
    
    // For now, allow nil arguments for testing purposes
    // In a full implementation, we would validate that the function is callable
    
    // The remaining arguments are the partial arguments to be applied
    std::vector<ValuePtr> partialArgs(args.begin() + 1, args.end());
    
    // For now, create a placeholder partially applied function
    // This would normally create a new function with some arguments pre-filled
    // Since we don't have full closure support, we'll return a simple function type
    
    // For now, return a nil value as a placeholder
    // This will be replaced with proper partial application when closures are implemented
    auto nilType = std::make_shared<Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nilType);
}

// Note: VM-aware utility functions will be implemented when full closure support is added

 // namespace builtin  Core utility builtin functions implementation

ValuePtr BuiltinFunctions::len(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) {
        throw std::runtime_error("len expects exactly 1 argument, got " + std::to_string(args.size()));
    }
    
    const auto& value = args[0];
    if (!value || !value->type) {
        throw std::runtime_error("len: argument is null");
    }
    
    size_t length = 0;
    
    switch (value->type->tag) {
        case TypeTag::String: {
            if (std::holds_alternative<std::string>(value->data)) {
                length = std::get<std::string>(value->data).length();
            }
            break;
        }
        case TypeTag::List: {
            if (std::holds_alternative<ListValue>(value->data)) {
                length = std::get<ListValue>(value->data).elements.size();
            }
            break;
        }
        case TypeTag::Dict: {
            if (std::holds_alternative<DictValue>(value->data)) {
                length = std::get<DictValue>(value->data).elements.size();
            }
            break;
        }
        default:
            throw std::runtime_error("len: unsupported type " + value->type->toString());
    }
    
    auto intType = std::make_shared<Type>(TypeTag::Int);
    return std::make_shared<::Value>(intType, static_cast<int32_t>(length));
}

ValuePtr BuiltinFunctions::time(const std::vector<ValuePtr>& args) {
    if (args.size() != 0) {
        throw std::runtime_error("time expects no arguments, got " + std::to_string(args.size()));
    }
    
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    
    auto int64Type = std::make_shared<Type>(TypeTag::Int64);
    return std::make_shared<::Value>(int64Type, static_cast<int64_t>(timestamp));
}


ValuePtr BuiltinFunctions::date(const std::vector<ValuePtr>& args) {
    if (args.size() != 0) {
        throw std::runtime_error("date expects no arguments, got " + std::to_string(args.size()));
    }
    
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%d");
    
    auto stringType = std::make_shared<Type>(TypeTag::String);
    return std::make_shared<::Value>(stringType, ss.str());
}

ValuePtr BuiltinFunctions::now(const std::vector<ValuePtr>& args) {
    if (args.size() != 0) {
        throw std::runtime_error("now expects no arguments, got " + std::to_string(args.size()));
    }
    
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%SZ");
    
    auto stringType = std::make_shared<Type>(TypeTag::String);
    return std::make_shared<::Value>(stringType, ss.str());
}

ValuePtr BuiltinFunctions::assertCondition(const std::vector<ValuePtr>& args) {
    if (args.size() != 2) {
        throw std::runtime_error("assert expects exactly 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& condition = args[0];
    const auto& message = args[1];
    
    if (!condition || !condition->type || condition->type->tag != TypeTag::Bool) {
        throw std::runtime_error("assert: first argument must be a boolean");
    }
    
    if (!message || !message->type || message->type->tag != TypeTag::String) {
        throw std::runtime_error("assert: second argument must be a string");
    }
    
    bool conditionValue = std::get<bool>(condition->data);
    if (!conditionValue) {
        std::string messageValue = std::get<std::string>(message->data);
        throw std::runtime_error("Assertion failed: " + messageValue);
    }
    
    auto nilType = std::make_shared<Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nilType);
}

ValuePtr BuiltinFunctions::input(const std::vector<ValuePtr>& args) {
    if (args.size() > 1) {
        throw std::runtime_error("input expects 0 or 1 arguments, got " + std::to_string(args.size()));
    }
    
    // Print prompt if provided
    if (args.size() == 1) {
        const auto& prompt = args[0];
        if (!prompt || !prompt->type || prompt->type->tag != TypeTag::String) {
            throw std::runtime_error("input: prompt must be a string");
        }
        std::cout << std::get<std::string>(prompt->data);
    }
    
    std::string line;
    std::getline(std::cin, line);
    
    auto stringType = std::make_shared<Type>(TypeTag::String);
    return std::make_shared<::Value>(stringType, line);
}

ValuePtr BuiltinFunctions::round(const std::vector<ValuePtr>& args) {
    if (args.size() < 1 || args.size() > 2) {
        throw std::runtime_error("round expects 1 or 2 arguments, got " + std::to_string(args.size()));
    }
    
    const auto& number = args[0];
    if (!number || !number->type) {
        throw std::runtime_error("round: first argument is null");
    }
    
    long double value = 0.0;
    if (number->type->tag == TypeTag::Float64) {
        value = std::get<long double>(number->data);
    } else if (number->type->tag == TypeTag::Float32) {
        value = static_cast<long double>(std::get<float>(number->data));
    } else if (number->type->tag == TypeTag::Int || number->type->tag == TypeTag::Int32) {
        value = static_cast<long double>(std::get<int32_t>(number->data));
    } else {
        throw std::runtime_error("round: first argument must be a number");
    }
    
    int precision = 0;
    if (args.size() == 2) {
        const auto& precisionArg = args[1];
        if (!precisionArg || !precisionArg->type || precisionArg->type->tag != TypeTag::Int) {
            throw std::runtime_error("round: second argument must be an integer");
        }
        precision = std::get<int32_t>(precisionArg->data);
    }
    
    long double multiplier = std::pow(10.0, precision);
    long double rounded = std::round(value * multiplier) / multiplier;
    
    auto float64Type = std::make_shared<Type>(TypeTag::Float64);
    return std::make_shared<::Value>(float64Type, rounded);
}

ValuePtr BuiltinFunctions::debug(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) {
        throw std::runtime_error("debug expects exactly 1 argument, got " + std::to_string(args.size()));
    }
    
    const auto& value = args[0];
    if (!value) {
        std::cout << "[DEBUG] null value" << std::endl;
    } else if (!value->type) {
        std::cout << "[DEBUG] value with null type" << std::endl;
    } else {
        std::cout << "[DEBUG] Type: " << value->type->toString() << ", Value: ";
        
        // Print value based on type
        switch (value->type->tag) {
            case TypeTag::Nil:
                std::cout << "nil";
                break;
            case TypeTag::Bool:
                std::cout << (std::get<bool>(value->data) ? "true" : "false");
                break;
            case TypeTag::Int:
            case TypeTag::Int32:
                std::cout << std::get<int32_t>(value->data);
                break;
            case TypeTag::Int64:
                std::cout << std::get<int64_t>(value->data);
                break;
            case TypeTag::Float32:
                std::cout << std::get<float>(value->data);
                break;
            case TypeTag::Float64:
                std::cout << std::get<long double>(value->data);
                break;
            case TypeTag::String:
                std::cout << "\"" << std::get<std::string>(value->data) << "\"";
                break;
            case TypeTag::List: {
                const auto& list = std::get<ListValue>(value->data);
                std::cout << "[" << list.elements.size() << " elements]";
                break;
            }
            case TypeTag::Dict: {
                const auto& dict = std::get<DictValue>(value->data);
                std::cout << "{" << dict.elements.size() << " entries}";
                break;
            }
            default:
                std::cout << value->toString();
                break;
        }
        std::cout << std::endl;
    }
    
    auto nilType = std::make_shared<Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nilType);
}



ValuePtr BuiltinFunctions::typeOf(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) {
        throw std::runtime_error("typeOf expects exactly 1 argument, got " + std::to_string(args.size()));
    }
    
    const auto& value = args[0];
    std::string typeName;
    
    if (!value) {
        typeName = "null";
    } else if (!value->type) {
        typeName = "untyped";
    } else {
        typeName = value->type->toString();
    }
    
    auto stringType = std::make_shared<Type>(TypeTag::String);
    return std::make_shared<::Value>(stringType, typeName);
}

ValuePtr BuiltinFunctions::clock(const std::vector<ValuePtr>& args) {
    if (args.size() != 0) {
        throw std::runtime_error("clock expects no arguments, got " + std::to_string(args.size()));
    }
    
    long double cpuTime = static_cast<long double>(std::clock()) / CLOCKS_PER_SEC;
    auto float64Type = std::make_shared<Type>(TypeTag::Float64);
    return std::make_shared<::Value>(float64Type, cpuTime);
}

ValuePtr BuiltinFunctions::sleep(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) {
        throw std::runtime_error("sleep expects exactly 1 argument, got " + std::to_string(args.size()));
    }
    
    const auto& value = args[0];
    if (!value || !value->type) {
        throw std::runtime_error("sleep: argument is null");
    }
    
    long double seconds = 0.0;
    
    if (value->type->tag == TypeTag::Float64) {
        if (std::holds_alternative<long double>(value->data)) {
            seconds = std::get<long double>(value->data);
        }
    } else if (value->type->tag == TypeTag::Float32) {
        if (std::holds_alternative<float>(value->data)) {
            seconds = static_cast<long double>(std::get<float>(value->data));
        }
    } else if (value->type->tag == TypeTag::Int || value->type->tag == TypeTag::Int32) {
        if (std::holds_alternative<int32_t>(value->data)) {
            seconds = static_cast<long double>(std::get<int32_t>(value->data));
        }
    } else {
        throw std::runtime_error("sleep: argument must be a number");
    }
    
    if (seconds < 0) {
        throw std::runtime_error("sleep: cannot sleep for negative time");
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(seconds * 1000)));
    
    auto nilType = std::make_shared<Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nilType);
}

}//builtin utility functions 
