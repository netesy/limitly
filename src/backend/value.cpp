#include "value.hh"
#include "vm.hh"  // For Environment class definition
#include "types.hh"
#include <sstream>

// ClosureValue method implementations

void ClosureValue::cleanup() {
    // Clear captured environment to help with garbage collection
    if (capturedEnvironment) {
        // Remove references to captured variables to break potential cycles
        for (const auto& varName : capturedVariables) {
            try {
                capturedEnvironment->remove(varName);
            } catch (const std::runtime_error&) {
                // Variable might already be removed, continue cleanup
            }
        }
    }
    capturedVariables.clear();
}

bool ClosureValue::hasMemoryLeaks() const {
    if (!capturedEnvironment) return false;
    
    // Check if captured environment has circular references
    auto symbols = capturedEnvironment->getAllSymbols();
    for (const auto& [name, value] : symbols) {
        if (value && value->type && value->type->tag == TypeTag::Closure) {
            // Found another closure in captured variables - potential cycle
            return true;
        }
    }
    return false;
}

size_t ClosureValue::getMemoryUsage() const {
    size_t usage = sizeof(ClosureValue);
    usage += functionName.size();
    usage += capturedVariables.size() * sizeof(std::string);
    for (const auto& var : capturedVariables) {
        usage += var.size();
    }
    
    // Estimate captured environment size
    if (capturedEnvironment) {
        auto symbols = capturedEnvironment->getAllSymbols();
        usage += symbols.size() * (sizeof(std::string) + sizeof(ValuePtr));
    }
    
    return usage;
}

std::string ClosureValue::toString() const {
    std::ostringstream oss;
    oss << "Closure(" << functionName << ", captures: [";
    for (size_t i = 0; i < capturedVariables.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << capturedVariables[i];
    }
    oss << "])";
    return oss.str();
}
// ErrorValue method implementations

std::string ErrorValue::toString() const {
    std::ostringstream oss;
    oss << "Error(" << errorType;
    if (!message.empty()) {
        oss << ": " << message;
    }
    if (!arguments.empty()) {
        oss << ", args: [";
        for (size_t i = 0; i < arguments.size(); ++i) {
            if (i > 0) oss << ", ";
            if (arguments[i]) {
                oss << arguments[i]->toString();
            } else {
                oss << "null";
            }
        }
        oss << "]";
    }
    oss << ")";
    return oss.str();
}

// TupleType toString implementation
std::string TupleType::toString() const {
    std::ostringstream oss;
    oss << "(";
    for (size_t i = 0; i < elementTypes.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << (elementTypes[i] ? elementTypes[i]->toString() : "unknown");
    }
    oss << ")";
    return oss.str();
}

// TupleValue toString implementation
std::string TupleValue::toString() const {
    std::ostringstream oss;
    oss << "(";
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i > 0) oss << ", ";
        if (elements[i]) {
            oss << elements[i]->toString();
        } else {
            oss << "nil";
        }
    }
    oss << ")";
    return oss.str();
}