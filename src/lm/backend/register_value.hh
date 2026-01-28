#ifndef LM_LM_BACKEND_HH
#define REGISTER_VALUE_H

#include <variant>
#include <string>
#include <cstdint>

namespace LM {
namespace Backend {


namespace Register {

// Register value type
using RegisterValue = std::variant<int64_t, uint64_t, double, bool, std::string, std::nullptr_t>;

} // namespace Register




} // namespace LM
} // namespace Backend

#endif // LM_LM_BACKEND_HH
