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

// toString() method moved to value.cpp to avoid multiple definitions
// ClosureValueFactory implementation is in value.hh as inline functions