#pragma once

#include "lir.hh"
#include <vector>
#include <string>

namespace LM {
namespace LIR {

class Serializer {
public:
    /**
     * @brief Serialize LIR function to a binary buffer
     */
    static std::vector<uint8_t> serialize(const LIR_Function& func);

    /**
     * @brief Deserialize LIR function from a binary buffer
     */
    static LIR_Function deserialize(const std::vector<uint8_t>& buffer);
};

} // namespace LIR
} // namespace LM
