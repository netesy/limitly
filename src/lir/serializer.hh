#pragma once

#include "lir.hh"
#include <vector>
#include <string>
#include <cstdint>

namespace LM {
namespace LIR {

class Serializer {
public:
    /**
     * @brief Serialize an LIR function to a tagged binary buffer ("LIR1" format).
     *
     * Round-trips every field of LIR_Inst: op, result_type, type_a, type_b,
     * dst, a, b, imm, const_val (tagged union covering NIL/TRUE/FALSE/SMI and
     * all heap-allocated numeric/string/box variants), func_name, type_name,
     * call_args, call_arg_types, loc, and comment.
     */
    static std::vector<uint8_t> serialize(const LIR_Function& func);

    /**
     * @brief Deserialize an LIR function from a tagged binary buffer.
     *
     * Reconstructs a fully equivalent LIR_Function. Throws std::runtime_error
     * on malformed input (bad magic, unsupported version, truncated buffer).
     */
    static LIR_Function deserialize(const std::vector<uint8_t>& buffer);
};

} // namespace LIR
} // namespace LM
