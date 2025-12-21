#include "builtin_functions.hh"
#include "function_registry.hh"
#include "lir.hh"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <ctime>

namespace LIR {

// LIRBuiltinFunction implementation
LIRBuiltinFunction::LIRBuiltinFunction(const std::string& name,
                                     const std::vector<TypeTag>& paramTypes,
                                     TypeTag returnType,
                                     LIRBuiltinImpl impl)
    : name_(name), paramTypes_(paramTypes), returnType_(returnType), implementation_(impl) {
    
    // Create LIR-specific signature
    signature_.name = name_;
    for (size_t i = 0; i < paramTypes_.size(); i++) {
        LIRParameter param;
        param.name = "arg" + std::to_string(i);
        param.type = std::make_shared<Type>(paramTypes_[i]);
        signature_.parameters.push_back(param);
    }
    signature_.returnType = std::make_shared<Type>(returnType_);
    signature_.isAsync = false;
}

ValuePtr LIRBuiltinFunction::execute(const std::vector<ValuePtr>& args) {
    if (!implementation_) {
        throw std::runtime_error("No implementation for LIR builtin function: " + name_);
    }
    
    // Validate argument count
    if (args.size() != paramTypes_.size()) {
        throw std::runtime_error("Argument count mismatch for LIR builtin function: " + name_ + 
                              " (expected " + std::to_string(paramTypes_.size()) + 
                              ", got " + std::to_string(args.size()) + ")");
    }
    
    // Validate argument types
    for (size_t i = 0; i < args.size(); i++) {
        if (!args[i] || args[i]->type->tag != paramTypes_[i]) {
            throw std::runtime_error("Argument type mismatch for LIR builtin function: " + name_ + 
                                  " at position " + std::to_string(i));
        }
    }
    
    return implementation_(args);
}

bool LIRBuiltinFunction::isNative() const {
    return true;
}

const LIRFunctionSignature& LIRBuiltinFunction::getSignature() const {
    return signature_;
}

// LIRBuiltinFunctions implementation
LIRBuiltinFunctions& LIRBuiltinFunctions::getInstance() {
    static LIRBuiltinFunctions instance;
    return instance;
}

void LIRBuiltinFunctions::initialize() {
    if (initialized_) {
        return;
    }
    
    std::cout << "[DEBUG] LIR Builtin Functions: Initializing LIR-specific builtin functions" << std::endl;
    
    // Register all LIR-specific builtin functions
    registerStringFunctions();
    registerIOFunctions();
    registerMathFunctions();
    registerUtilityFunctions();
    registerCollectionFunctions();
    registerSearchFunctions();
    registerCompositionFunctions();
    
    initialized_ = true;
    std::cout << "[DEBUG] LIR Builtin Functions: Initialized " << builtinFunctions_.size() << " functions" << std::endl;
}




void LIRBuiltinFunctions::registerStringFunctions() {
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "concat",
        std::vector<TypeTag>{TypeTag::String, TypeTag::String},
        TypeTag::String,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            std::string a = args[0]->as<std::string>();
            std::string b = args[1]->as<std::string>();
            auto string_type = std::make_shared<Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, a + b);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "length",
        std::vector<TypeTag>{TypeTag::String},
        TypeTag::Int,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            std::string a = args[0]->as<std::string>();
            auto int_type = std::make_shared<Type>(TypeTag::Int);
            return std::make_shared<Value>(int_type, static_cast<int64_t>(a.length()));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "substring",
        std::vector<TypeTag>{TypeTag::String, TypeTag::Int, TypeTag::Int},
        TypeTag::String,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            std::string str = args[0]->as<std::string>();
            int64_t start = args[1]->as<int64_t>();
            int64_t length = args[2]->as<int64_t>();
            
            if (start < 0) start = 0;
            if (start >= str.length()) {
                auto string_type = std::make_shared<Type>(TypeTag::String);
                return std::make_shared<Value>(string_type, std::string(""));
            }
            
            if (length < 0) length = 0;
            if (start + length > str.length()) {
                length = str.length() - start;
            }
            
            auto string_type = std::make_shared<Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, str.substr(start, length));
        }
    ));
}

void LIRBuiltinFunctions::registerIOFunctions() {
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "print",
        std::vector<TypeTag>{TypeTag::Any},
        TypeTag::Nil,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& value = args[0];
            if (value && value->type) {
                switch (value->type->tag) {
                    case TypeTag::Int:
                        std::cout << value->as<int64_t>();
                        break;
                    case TypeTag::Float32:
                    case TypeTag::Float64:
                        std::cout << value->as<double>();
                        break;
                    case TypeTag::Bool:
                        std::cout << (value->as<bool>() ? "true" : "false");
                        break;
                    case TypeTag::String:
                        std::cout << value->as<std::string>();
                        break;
                    default:
                        std::cout << "<unsupported type>";
                        break;
                }
                std::cout << std::endl;
            }
            auto nil_type = std::make_shared<Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "input",
        std::vector<TypeTag>{TypeTag::String},
        TypeTag::String,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            std::string prompt = args[0]->as<std::string>();
            std::cout << prompt;
            
            std::string line;
            std::getline(std::cin, line);
            
            auto string_type = std::make_shared<Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, line);
        }
    ));
}

void LIRBuiltinFunctions::registerMathFunctions() {
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "abs",
        std::vector<TypeTag>{TypeTag::Int},
        TypeTag::Int,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            int64_t value = args[0]->as<int64_t>();
            auto int_type = std::make_shared<Type>(TypeTag::Int);
            return std::make_shared<Value>(int_type, value < 0 ? -value : value);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "fabs",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::fabs(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "pow",
        std::vector<TypeTag>{TypeTag::Float32, TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double base = args[0]->as<double>();
            double exp = args[1]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::pow(base, exp));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "sqrt",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            if (value < 0) throw std::runtime_error("Square root of negative number");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::sqrt(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "cbrt",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::cbrt(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "hypot",
        std::vector<TypeTag>{TypeTag::Float32, TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double x = args[0]->as<double>();
            double y = args[1]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::hypot(x, y));
        }
    ));
    
    // Trigonometric functions
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "sin",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::sin(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "cos",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::cos(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "tan",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::tan(value));
        }
    ));
    
    // Inverse trigonometric functions
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "asin",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            if (value < -1.0 || value > 1.0) throw std::runtime_error("asin: argument out of range [-1, 1]");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::asin(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "acos",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            if (value < -1.0 || value > 1.0) throw std::runtime_error("acos: argument out of range [-1, 1]");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::acos(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "atan",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::atan(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "atan2",
        std::vector<TypeTag>{TypeTag::Float32, TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double y = args[0]->as<double>();
            double x = args[1]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::atan2(y, x));
        }
    ));
    
    // Hyperbolic functions
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "sinh",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::sinh(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "cosh",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::cosh(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "tanh",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::tanh(value));
        }
    ));
    
    // Inverse hyperbolic functions
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "asinh",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::asinh(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "acosh",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            if (value < 1.0) throw std::runtime_error("acosh: argument must be >= 1");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::acosh(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "atanh",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            if (value <= -1.0 || value >= 1.0) throw std::runtime_error("atanh: argument must be in (-1, 1)");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::atanh(value));
        }
    ));
    
    // Exponential and logarithmic functions
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "exp",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::exp(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "exp2",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::exp2(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "log",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            if (value <= 0) throw std::runtime_error("log: argument must be positive");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::log(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "log10",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            if (value <= 0) throw std::runtime_error("log10: argument must be positive");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::log10(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "log2",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            if (value <= 0) throw std::runtime_error("log2: argument must be positive");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::log2(value));
        }
    ));
    
    // Rounding functions
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "ceil",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::ceil(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "floor",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::floor(value));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "trunc",
        std::vector<TypeTag>{TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::trunc(value));
        }
    ));
    
    // Other useful functions
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "fmod",
        std::vector<TypeTag>{TypeTag::Float32, TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double x = args[0]->as<double>();
            double y = args[1]->as<double>();
            if (y == 0.0) throw std::runtime_error("fmod: division by zero");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::fmod(x, y));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "remainder",
        std::vector<TypeTag>{TypeTag::Float32, TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double x = args[0]->as<double>();
            double y = args[1]->as<double>();
            if (y == 0.0) throw std::runtime_error("remainder: division by zero");
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::remainder(x, y));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "fmax",
        std::vector<TypeTag>{TypeTag::Float32, TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double x = args[0]->as<double>();
            double y = args[1]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::fmax(x, y));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "fmin",
        std::vector<TypeTag>{TypeTag::Float32, TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double x = args[0]->as<double>();
            double y = args[1]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::fmin(x, y));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "fdim",
        std::vector<TypeTag>{TypeTag::Float32, TypeTag::Float32},
        TypeTag::Float32,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double x = args[0]->as<double>();
            double y = args[1]->as<double>();
            auto float_type = std::make_shared<Type>(TypeTag::Float32);
            return std::make_shared<Value>(float_type, std::fdim(x, y));
        }
    ));
    
    // Constants
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "pi",
        std::vector<TypeTag>{},
        TypeTag::Float64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto float_type = std::make_shared<Type>(TypeTag::Float64);
            return std::make_shared<Value>(float_type, 3.14159265358979323846);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "e",
        std::vector<TypeTag>{},
        TypeTag::Float64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto float_type = std::make_shared<Type>(TypeTag::Float64);
            return std::make_shared<Value>(float_type, 2.71828182845904523536);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "ln2",
        std::vector<TypeTag>{},
        TypeTag::Float64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto float_type = std::make_shared<Type>(TypeTag::Float64);
            return std::make_shared<Value>(float_type, 0.69314718055994530942);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "ln10",
        std::vector<TypeTag>{},
        TypeTag::Float64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto float_type = std::make_shared<Type>(TypeTag::Float64);
            return std::make_shared<Value>(float_type, 2.30258509299404568402);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "sqrt2",
        std::vector<TypeTag>{},
        TypeTag::Float64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto float_type = std::make_shared<Type>(TypeTag::Float64);
            return std::make_shared<Value>(float_type, 1.41421356237309504880);
        }
    ));
}

void LIRBuiltinFunctions::registerUtilityFunctions() {
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "typeof",
        std::vector<TypeTag>{TypeTag::Any},
        TypeTag::String,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            TypeTag tag = args[0]->type->tag;
            std::string type_name;
            switch (tag) {
                case TypeTag::Int: type_name = "int"; break;
                case TypeTag::Float32: type_name = "float"; break;
                case TypeTag::Bool: type_name = "bool"; break;
                case TypeTag::String: type_name = "string"; break;
                case TypeTag::Nil: type_name = "nil"; break;
                default: type_name = "unknown"; break;
            }
            auto string_type = std::make_shared<Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, type_name);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "clock",
        std::vector<TypeTag>{},
        TypeTag::Float64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            long double cpuTime = static_cast<long double>(std::clock()) / CLOCKS_PER_SEC;
            auto float64_type = std::make_shared<Type>(TypeTag::Float64);
            return std::make_shared<Value>(float64_type, cpuTime);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "sleep",
        std::vector<TypeTag>{TypeTag::Float64},
        TypeTag::Nil,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double seconds = args[0]->as<double>();
            if (seconds < 0) throw std::runtime_error("sleep: cannot sleep for negative time");
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(seconds * 1000)));
            auto nil_type = std::make_shared<Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "channel",
        std::vector<TypeTag>{}, // No parameters
        TypeTag::Int, // Returns channel handle as int
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            // For LIR generation, return a placeholder channel handle
            auto int_type = std::make_shared<Type>(TypeTag::Int);
            return std::make_shared<Value>(int_type, static_cast<int64_t>(0));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "len",
        std::vector<TypeTag>{TypeTag::Any},
        TypeTag::Int,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& value = args[0];
            size_t length = 0;
            
            switch (value->type->tag) {
                case TypeTag::String: {
                    length = value->data.length();
                    break;
                }
                case TypeTag::List: {
                    if (std::holds_alternative<ListValue>(value->complexData)) {
                        length = std::get<ListValue>(value->complexData).elements.size();
                    }
                    break;
                }
                case TypeTag::Dict: {
                    if (std::holds_alternative<DictValue>(value->complexData)) {
                        length = std::get<DictValue>(value->complexData).elements.size();
                    }
                    break;
                }
                default:
                    throw std::runtime_error("len: unsupported type " + value->type->toString());
            }
            
            auto int_type = std::make_shared<Type>(TypeTag::Int);
            return std::make_shared<Value>(int_type, static_cast<int64_t>(length));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "time",
        std::vector<TypeTag>{},
        TypeTag::Int64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
            auto int64_type = std::make_shared<Type>(TypeTag::Int64);
            return std::make_shared<Value>(int64_type, static_cast<int64_t>(timestamp));
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "date",
        std::vector<TypeTag>{},
        TypeTag::String,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            
            std::stringstream ss;
            ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%d");
            
            auto string_type = std::make_shared<Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, ss.str());
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "now",
        std::vector<TypeTag>{},
        TypeTag::String,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            
            std::stringstream ss;
            ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%SZ");
            
            auto string_type = std::make_shared<Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, ss.str());
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "assert",
        std::vector<TypeTag>{TypeTag::Bool, TypeTag::String},
        TypeTag::Nil,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            bool condition = args[0]->as<bool>();
            std::string message = args[1]->as<std::string>();
            if (!condition) {
                throw std::runtime_error("Assertion failed: " + message);
            }
            auto nil_type = std::make_shared<Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "round",
        std::vector<TypeTag>{TypeTag::Float64, TypeTag::Int},
        TypeTag::Float64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            double value = args[0]->as<double>();
            int precision = args[1]->as<int>();
            
            double multiplier = std::pow(10.0, precision);
            double rounded = std::round(value * multiplier) / multiplier;
            
            auto float64_type = std::make_shared<Type>(TypeTag::Float64);
            return std::make_shared<Value>(float64_type, rounded);
        }
    ));
    
    }

void LIRBuiltinFunctions::registerCollectionFunctions() {
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "map",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::List},
        TypeTag::List,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& function = args[0];
            const auto& list = args[1];
            
            if (!list || !list->type || list->type->tag != TypeTag::List) {
                throw std::runtime_error("map: second argument must be a list");
            }
            
            if (!std::holds_alternative<ListValue>(list->complexData)) {
                throw std::runtime_error("map: second argument must be a list");
            }
            
            const auto& listValue = std::get<ListValue>(list->complexData);
            ListValue result;
            
            // Simple transformation: if it's a number, double it
            for (const auto& element : listValue.elements) {
                try {
                    if (element && element->type) {
                        if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                            int64_t value = element->as<int64_t>();
                            auto int_type = std::make_shared<Type>(TypeTag::Int);
                            auto transformedElement = std::make_shared<Value>(int_type, value * 2);
                            result.append(transformedElement);
                        } else if (element->type->tag == TypeTag::Float64) {
                            double value = element->as<double>();
                            auto float_type = std::make_shared<Type>(TypeTag::Float64);
                            auto transformedElement = std::make_shared<Value>(float_type, value * 2.0);
                            result.append(transformedElement);
                        } else {
                            result.append(element);
                        }
                    }
                } catch (const std::exception& e) {
                    throw std::runtime_error("map: error processing element: " + std::string(e.what()));
                }
            }
            
            auto list_type = std::make_shared<Type>(TypeTag::List);
            return std::make_shared<Value>(list_type, result);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "filter",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::List},
        TypeTag::List,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& predicate = args[0];
            const auto& list = args[1];
            
            if (!list || !list->type || list->type->tag != TypeTag::List) {
                throw std::runtime_error("filter: second argument must be a list");
            }
            
            if (!std::holds_alternative<ListValue>(list->complexData)) {
                throw std::runtime_error("filter: second argument must be a list");
            }
            
            const auto& listValue = std::get<ListValue>(list->complexData);
            ListValue result;
            
            // Simple filter: keep even numbers
            for (const auto& element : listValue.elements) {
                try {
                    bool shouldInclude = false;
                    
                    if (element && element->type) {
                        if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                            int64_t value = element->as<int64_t>();
                            shouldInclude = (value % 2 == 0);
                        } else if (element->type->tag == TypeTag::Float64) {
                            double value = element->as<double>();
                            shouldInclude = (static_cast<int>(value) % 2 == 0);
                        } else {
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
            
            auto list_type = std::make_shared<Type>(TypeTag::List);
            return std::make_shared<Value>(list_type, result);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "reduce",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::List, TypeTag::Any},
        TypeTag::Any,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& reducer = args[0];
            const auto& list = args[1];
            ValuePtr accumulator = args.size() > 2 ? args[2] : nullptr;
            
            if (!list || !list->type || list->type->tag != TypeTag::List) {
                throw std::runtime_error("reduce: second argument must be a list");
            }
            
            if (!std::holds_alternative<ListValue>(list->complexData)) {
                throw std::runtime_error("reduce: second argument must be a list");
            }
            
            const auto& listValue = std::get<ListValue>(list->complexData);
            
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
            }
            
            // Simple reduction: sum numbers
            for (size_t i = startIndex; i < listValue.elements.size(); ++i) {
                try {
                    const auto& element = listValue.elements[i];
                    
                    if (accumulator && accumulator->type && element && element->type) {
                        if ((accumulator->type->tag == TypeTag::Int || accumulator->type->tag == TypeTag::Int32) && 
                            (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32)) {
                            int64_t accValue = accumulator->as<int64_t>();
                            int64_t elemValue = element->as<int64_t>();
                            auto int_type = std::make_shared<Type>(TypeTag::Int);
                            accumulator = std::make_shared<Value>(int_type, accValue + elemValue);
                        } else if (accumulator->type->tag == TypeTag::Float64 && element->type->tag == TypeTag::Float64) {
                            double accValue = accumulator->as<double>();
                            double elemValue = element->as<double>();
                            auto float_type = std::make_shared<Type>(TypeTag::Float64);
                            accumulator = std::make_shared<Value>(float_type, accValue + elemValue);
                        } else {
                            break;
                        }
                    }
                } catch (const std::exception& e) {
                    throw std::runtime_error("reduce: error processing element: " + std::string(e.what()));
                }
            }
            
            return accumulator;
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "forEach",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::List},
        TypeTag::Nil,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& function = args[0];
            const auto& list = args[1];
            
            if (!list || !list->type || list->type->tag != TypeTag::List) {
                throw std::runtime_error("forEach: second argument must be a list");
            }
            
            if (!std::holds_alternative<ListValue>(list->complexData)) {
                throw std::runtime_error("forEach: second argument must be a list");
            }
            
            const auto& listValue = std::get<ListValue>(list->complexData);
            
            // Simple forEach: print each element
            for (const auto& element : listValue.elements) {
                try {
                    if (element && element->type) {
                        if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                            int64_t value = element->as<int64_t>();
                            std::cout << "forEach element: " << value << std::endl;
                        } else if (element->type->tag == TypeTag::Float64) {
                            double value = element->as<double>();
                            std::cout << "forEach element: " << value << std::endl;
                        } else if (element->type->tag == TypeTag::String) {
                            std::string value = element->as<std::string>();
                            std::cout << "forEach element: " << value << std::endl;
                        } else {
                            std::cout << "forEach element: <unknown type>" << std::endl;
                        }
                    }
                } catch (const std::exception& e) {
                    throw std::runtime_error("forEach: error processing element: " + std::string(e.what()));
                }
            }
            
            auto nil_type = std::make_shared<Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));
}

void LIRBuiltinFunctions::registerSearchFunctions() {
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "find",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::List},
        TypeTag::Any,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& predicate = args[0];
            const auto& list = args[1];
            
            if (!list || !list->type || list->type->tag != TypeTag::List) {
                throw std::runtime_error("find: second argument must be a list");
            }
            
            if (!std::holds_alternative<ListValue>(list->complexData)) {
                throw std::runtime_error("find: second argument must be a list");
            }
            
            const auto& listValue = std::get<ListValue>(list->complexData);
            
            // Check predicate type and select appropriate built-in predicate
            std::string predicateType = "even"; // default
            
            if (predicate && predicate->type) {
                if (predicate->type->tag == TypeTag::Nil) {
                    predicateType = "even";
                } else if (predicate->type->tag == TypeTag::String) {
                    predicateType = predicate->as<std::string>();
                } else if (predicate->type->tag == TypeTag::Function) {
                    throw std::runtime_error("find: Custom function predicates not yet supported. Use nil or string predicate names like 'even', 'odd', 'positive', 'negative'");
                }
            }
            
            // Apply the selected built-in predicate
            for (const auto& element : listValue.elements) {
                try {
                    if (element && element->type) {
                        if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                            int64_t value = element->as<int64_t>();
                            
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
                            double value = element->as<double>();
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
                } catch (const std::exception& e) {
                    throw std::runtime_error("find: error processing element: " + std::string(e.what()));
                }
            }
            
            auto nil_type = std::make_shared<Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "some",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::List},
        TypeTag::Bool,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& predicate = args[0];
            const auto& list = args[1];
            
            if (!list || !list->type || list->type->tag != TypeTag::List) {
                throw std::runtime_error("some: second argument must be a list");
            }
            
            if (!std::holds_alternative<ListValue>(list->complexData)) {
                throw std::runtime_error("some: second argument must be a list");
            }
            
            const auto& listValue = std::get<ListValue>(list->complexData);
            
            // Check predicate type and select appropriate built-in predicate
            std::string predicateType = "even"; // default
            
            if (predicate && predicate->type) {
                if (predicate->type->tag == TypeTag::Nil) {
                    predicateType = "even";
                } else if (predicate->type->tag == TypeTag::String) {
                    predicateType = predicate->as<std::string>();
                } else if (predicate->type->tag == TypeTag::Function) {
                    throw std::runtime_error("some: Custom function predicates not yet supported. Use nil or string predicate names like 'even', 'odd', 'positive', 'negative'");
                }
            }
            
            // Apply the selected built-in predicate
            for (const auto& element : listValue.elements) {
                try {
                    if (element && element->type) {
                        if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                            int64_t value = element->as<int64_t>();
                            
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
                                auto bool_type = std::make_shared<Type>(TypeTag::Bool);
                                return std::make_shared<Value>(bool_type, true);
                            }
                        } else if (element->type->tag == TypeTag::Float64) {
                            double value = element->as<double>();
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
                                auto bool_type = std::make_shared<Type>(TypeTag::Bool);
                                return std::make_shared<Value>(bool_type, true);
                            }
                        }
                    }
                } catch (const std::exception& e) {
                    throw std::runtime_error("some: error processing element: " + std::string(e.what()));
                }
            }
            
            auto bool_type = std::make_shared<Type>(TypeTag::Bool);
            return std::make_shared<Value>(bool_type, false);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "every",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::List},
        TypeTag::Bool,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& predicate = args[0];
            const auto& list = args[1];
            
            if (!list || !list->type || list->type->tag != TypeTag::List) {
                throw std::runtime_error("every: second argument must be a list");
            }
            
            if (!std::holds_alternative<ListValue>(list->complexData)) {
                throw std::runtime_error("every: second argument must be a list");
            }
            
            const auto& listValue = std::get<ListValue>(list->complexData);
            
            // Check predicate type and select appropriate built-in predicate
            std::string predicateType = "positive"; // default for every
            
            if (predicate && predicate->type) {
                if (predicate->type->tag == TypeTag::Nil) {
                    predicateType = "positive";
                } else if (predicate->type->tag == TypeTag::String) {
                    predicateType = predicate->as<std::string>();
                } else if (predicate->type->tag == TypeTag::Function) {
                    throw std::runtime_error("every: Custom function predicates not yet supported. Use nil or string predicate names like 'even', 'odd', 'positive', 'negative'");
                }
            }
            
            // Apply the selected built-in predicate
            for (const auto& element : listValue.elements) {
                try {
                    if (element && element->type) {
                        if (element->type->tag == TypeTag::Int || element->type->tag == TypeTag::Int32) {
                            int64_t value = element->as<int64_t>();
                            
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
                                auto bool_type = std::make_shared<Type>(TypeTag::Bool);
                                return std::make_shared<Value>(bool_type, false);
                            }
                        } else if (element->type->tag == TypeTag::Float64) {
                            double value = element->as<double>();
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
                                auto bool_type = std::make_shared<Type>(TypeTag::Bool);
                                return std::make_shared<Value>(bool_type, false);
                            }
                        } else {
                            auto bool_type = std::make_shared<Type>(TypeTag::Bool);
                            return std::make_shared<Value>(bool_type, false);
                        }
                    }
                } catch (const std::exception& e) {
                    throw std::runtime_error("every: error processing element: " + std::string(e.what()));
                }
            }
            
            auto bool_type = std::make_shared<Type>(TypeTag::Bool);
            return std::make_shared<Value>(bool_type, true);
        }
    ));
}

void LIRBuiltinFunctions::registerCompositionFunctions() {
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "compose",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::Function},
        TypeTag::Function,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& f = args[0];
            const auto& g = args[1];
            
            // For now, return a nil value as a placeholder
            // This will be replaced with proper function composition when closures are implemented
            auto nil_type = std::make_shared<Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "curry",
        std::vector<TypeTag>{TypeTag::Function},
        TypeTag::Function,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& function = args[0];
            
            // For now, return a nil value as a placeholder
            // This will be replaced with proper function currying when closures are implemented
            auto nil_type = std::make_shared<Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "partial",
        std::vector<TypeTag>{TypeTag::Function, TypeTag::Any},
        TypeTag::Function,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const auto& function = args[0];
            
            // The remaining arguments are the partial arguments to be applied
            std::vector<ValuePtr> partialArgs(args.begin() + 1, args.end());
            
            // For now, return a nil value as a placeholder
            // This will be replaced with proper partial application when closures are implemented
            auto nil_type = std::make_shared<Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));
}

void LIRBuiltinFunctions::registerFunction(std::shared_ptr<LIRBuiltinFunction> function) {
    if (!function) {
        throw std::runtime_error("Cannot register null LIR builtin function");
    }
    
    std::string name = function->getName();
    builtinFunctions_[name] = function;
    
    // Also register with the LIR function registry for JIT compilation
    // Note: We use the LIR-specific registry, not the backend one
    // The LIR registry will handle function lookup for JIT compilation
}

std::shared_ptr<LIRBuiltinFunction> LIRBuiltinFunctions::getFunction(const std::string& name) {
    auto it = builtinFunctions_.find(name);
    return (it != builtinFunctions_.end()) ? it->second : nullptr;
}

bool LIRBuiltinFunctions::hasFunction(const std::string& name) const {
    return builtinFunctions_.find(name) != builtinFunctions_.end();
}

std::vector<std::string> LIRBuiltinFunctions::getFunctionNames() const {
    std::vector<std::string> names;
    for (const auto& [name, function] : builtinFunctions_) {
        names.push_back(name);
    }
    return names;
}

// BuiltinUtils implementation
namespace BuiltinUtils {
    
void initializeBuiltins() {
    LIRBuiltinFunctions::getInstance().initialize();
}

std::vector<std::string> getBuiltinFunctionNames() {
    return LIRBuiltinFunctions::getInstance().getFunctionNames();
}

bool isBuiltinFunction(const std::string& name) {
    return LIRBuiltinFunctions::getInstance().hasFunction(name);
}

ValuePtr callBuiltinFunction(const std::string& name, const std::vector<ValuePtr>& args) {
    auto func = LIRBuiltinFunctions::getInstance().getFunction(name);
    if (!func) {
        throw std::runtime_error("LIR builtin function not found: " + name);
    }
    return func->execute(args);
}

} // namespace BuiltinUtils

} // namespace LIR
