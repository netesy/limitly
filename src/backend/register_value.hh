#ifndef REGISTER_VALUE_H
#define REGISTER_VALUE_H

#include <variant>
#include <string>
#include <cstdint>

namespace LM {
namespace Backend {

// Register value type
using RegisterValue = std::variant<int64_t, uint64_t, double, bool, std::string, std::nullptr_t>;

} // namespace Backend
} // namespace LM

#endif // REGISTER_VALUE_H
