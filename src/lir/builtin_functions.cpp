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
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <mutex>

namespace LM {
namespace LIR {

namespace {
    std::mutex g_file_table_mutex;
    int64_t g_next_file_handle = 1;
    std::unordered_map<int64_t, std::shared_ptr<std::fstream>> g_file_table;

    std::ios_base::openmode parse_open_mode(const std::string& mode) {
        if (mode == "r" || mode == "read") return std::ios::in;
        if (mode == "w" || mode == "write") return std::ios::out | std::ios::trunc;
        if (mode == "a" || mode == "append") return std::ios::out | std::ios::app;
        if (mode == "r+") return std::ios::in | std::ios::out;
        if (mode == "w+") return std::ios::in | std::ios::out | std::ios::trunc;
        if (mode == "a+") return std::ios::in | std::ios::out | std::ios::app;
        throw std::runtime_error("file_open: unsupported mode '" + mode + "'");
    }
}

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
        param.type = typeTagToLIRType(paramTypes_[i]);
        signature_.parameters.push_back(param);
    }
    signature_.returnType = typeTagToLIRType(returnType_);
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
        if (!args[i]) {
            throw std::runtime_error("Argument type mismatch for LIR builtin function: " + name_ + 
                                  " at position " + std::to_string(i) + " (null argument)");
        }
        
        TypeTag expected = paramTypes_[i];
        TypeTag actual = args[i]->type->tag;
        
        bool type_compatible = (expected == actual) || (expected == TypeTag::Any);
        
        if (!type_compatible && 
            (expected == TypeTag::Int || expected == TypeTag::Int32 || expected == TypeTag::Int64) &&
            (actual == TypeTag::Int || actual == TypeTag::Int32 || actual == TypeTag::Int64)) {
            type_compatible = true;
        }
        
        if (!type_compatible &&
            (expected == TypeTag::Float32 || expected == TypeTag::Float64) &&
            (actual == TypeTag::Float32 || actual == TypeTag::Float64)) {
            type_compatible = true;
        }
        
        if (!type_compatible) {
            throw std::runtime_error("Argument type mismatch for LIR builtin function: " + name_ + 
                                  " at position " + std::to_string(i) + 
                                  " (expected " + std::to_string(static_cast<int>(expected)) + 
                                  ", got " + std::to_string(static_cast<int>(actual)) + ")");
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
LIRBuiltinFunctions* LIRBuiltinFunctions::instance = nullptr;

LIRBuiltinFunctions& LIRBuiltinFunctions::getInstance() {
    if (!instance) {
        instance = new LIRBuiltinFunctions();
    }
    return *instance;
}

void LIRBuiltinFunctions::initialize() {
    if (initialized_) {
        return;
    }
    
    registerIOFunctions();      // print, input
    registerUtilityFunctions(); // typeof, clock, sleep, time, assert, channel
    
    initialized_ = true;
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
                    case TypeTag::Int64:
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
                    case TypeTag::Nil:
                        std::cout << "nil";
                        break;
                    default:
                        std::cout << "<unsupported type>";
                        break;
                }
                std::cout << std::endl;
            }
            auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
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
            auto string_type = std::make_shared<::Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, line);
        }
    ));

    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "file_open",
        std::vector<TypeTag>{TypeTag::String, TypeTag::String},
        TypeTag::Int64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const std::string path = args[0]->as<std::string>();
            const std::string mode = args[1]->as<std::string>();

            auto file = std::make_shared<std::fstream>();
            file->open(path, parse_open_mode(mode));
            if (!file->is_open()) {
                throw std::runtime_error("file_open: failed to open '" + path + "'");
            }

            std::lock_guard<std::mutex> lock(g_file_table_mutex);
            const int64_t handle = g_next_file_handle++;
            g_file_table[handle] = file;

            auto int64_type = std::make_shared<::Type>(TypeTag::Int64);
            return std::make_shared<Value>(int64_type, handle);
        }
    ));

    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "file_read",
        std::vector<TypeTag>{TypeTag::Int64},
        TypeTag::String,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const int64_t handle = args[0]->as<int64_t>();

            std::shared_ptr<std::fstream> file;
            {
                std::lock_guard<std::mutex> lock(g_file_table_mutex);
                auto it = g_file_table.find(handle);
                if (it == g_file_table.end()) {
                    throw std::runtime_error("file_read: invalid file handle");
                }
                file = it->second;
            }

            file->clear();
            file->seekg(0, std::ios::beg);
            std::ostringstream buffer;
            buffer << file->rdbuf();

            auto string_type = std::make_shared<::Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, buffer.str());
        }
    ));

    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "file_write",
        std::vector<TypeTag>{TypeTag::Int64, TypeTag::String},
        TypeTag::Nil,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const int64_t handle = args[0]->as<int64_t>();
            const std::string content = args[1]->as<std::string>();

            std::shared_ptr<std::fstream> file;
            {
                std::lock_guard<std::mutex> lock(g_file_table_mutex);
                auto it = g_file_table.find(handle);
                if (it == g_file_table.end()) {
                    throw std::runtime_error("file_write: invalid file handle");
                }
                file = it->second;
            }

            file->clear();
            (*file) << content;
            file->flush();

            auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));

    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "file_close",
        std::vector<TypeTag>{TypeTag::Int64},
        TypeTag::Nil,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const int64_t handle = args[0]->as<int64_t>();

            std::shared_ptr<std::fstream> file;
            {
                std::lock_guard<std::mutex> lock(g_file_table_mutex);
                auto it = g_file_table.find(handle);
                if (it == g_file_table.end()) {
                    auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
                    return std::make_shared<Value>(nil_type);
                }
                file = it->second;
                g_file_table.erase(it);
            }

            if (file->is_open()) {
                file->close();
            }

            auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));

    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "file_exists",
        std::vector<TypeTag>{TypeTag::String},
        TypeTag::Bool,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const std::string path = args[0]->as<std::string>();
            const bool exists = std::filesystem::exists(path);
            auto bool_type = std::make_shared<::Type>(TypeTag::Bool);
            return std::make_shared<Value>(bool_type, exists);
        }
    ));

    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "file_delete",
        std::vector<TypeTag>{TypeTag::String},
        TypeTag::Bool,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            const std::string path = args[0]->as<std::string>();
            const bool removed = std::filesystem::remove(path);
            auto bool_type = std::make_shared<::Type>(TypeTag::Bool);
            return std::make_shared<Value>(bool_type, removed);
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
                case TypeTag::Int: 
                case TypeTag::Int64: type_name = "int"; break;
                case TypeTag::Float32:
                case TypeTag::Float64: type_name = "float"; break;
                case TypeTag::Bool: type_name = "bool"; break;
                case TypeTag::String: type_name = "string"; break;
                case TypeTag::Nil: type_name = "nil"; break;
                case TypeTag::ErrorUnion: type_name = "Type?"; break;
                case TypeTag::Function: type_name = "function"; break;
                default: type_name = "unknown"; break;
            }
            auto string_type = std::make_shared<::Type>(TypeTag::String);
            return std::make_shared<Value>(string_type, type_name);
        }
    ));
    
    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "clock",
        std::vector<TypeTag>{},
        TypeTag::Float64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            long double cpuTime = static_cast<long double>(std::clock()) / CLOCKS_PER_SEC;
            auto float64_type = std::make_shared<::Type>(TypeTag::Float64);
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
            auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));

    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "time",
        std::vector<TypeTag>{},
        TypeTag::Int64,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
            auto int64_type = std::make_shared<::Type>(TypeTag::Int64);
            return std::make_shared<Value>(int64_type, static_cast<int64_t>(timestamp));
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
            auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
            return std::make_shared<Value>(nil_type);
        }
    ));

    registerFunction(std::make_shared<LIRBuiltinFunction>(
        "channel",
        std::vector<TypeTag>{},
        TypeTag::Channel,
        [](const std::vector<ValuePtr>& args) -> ValuePtr {
            auto channel_type = std::make_shared<::Type>(TypeTag::Channel);
            return std::make_shared<Value>(channel_type, static_cast<int64_t>(0));
        }
    ));
}

void LIRBuiltinFunctions::registerFunction(std::shared_ptr<LIRBuiltinFunction> function) {
    if (!function) {
        throw std::runtime_error("Cannot register null LIR builtin function");
    }
    builtinFunctions_[function->getName()] = function;
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

namespace BuiltinUtils {
    void initializeBuiltins() { LIRBuiltinFunctions::getInstance().initialize(); }
    std::vector<std::string> getBuiltinFunctionNames() { return LIRBuiltinFunctions::getInstance().getFunctionNames(); }
    bool isBuiltinFunction(const std::string& name) { return LIRBuiltinFunctions::getInstance().hasFunction(name); }
    ValuePtr callBuiltinFunction(const std::string& name, const std::vector<ValuePtr>& args) {
        auto func = LIRBuiltinFunctions::getInstance().getFunction(name);
        if (!func) throw std::runtime_error("LIR builtin function not found: " + name);
        return func->execute(args);
    }
}

} // namespace LIR
} // namespace LM
