#include "value.hh"
#include "functions.hh"
#include "types.hh"

// ClosureValue method implementations

// ValuePtr ClosureValue::execute(const std::vector<ValuePtr>& args) {
//     // For now, delegate to the underlying function
//     // This will be enhanced when we implement the VM closure execution
//     if (function) {
//         return function->execute(args);
//     }
//     throw std::runtime_error("Cannot execute closure: no function defined");
// }

std::string ClosureValue::toString() const {
    std::string result = "<closure";
    if (!functionName.empty()) {
        result += ":" + functionName;
    }
    if (!capturedVariables.empty()) {
        result += " captures[";
        for (size_t i = 0; i < capturedVariables.size(); ++i) {
            if (i > 0) result += ", ";
            result += capturedVariables[i];
        }
        result += "]";
    }
    result += ">";
    return result;
}
// ClosureValueFactory implementation is in value.hh as inline functions