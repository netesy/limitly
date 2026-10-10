#pragma once
#include <cmath>
#include <cstdint>

namespace LM::Memory {
// Truncation is defined only within the signed 64-bit range. Invalid erased
// numeric conversions use the same zero fallback as nonnumeric as_i64 inputs.
inline int64_t truncate_i64(double number) {
    if (!std::isfinite(number) || number < -0x1p63 || number >= 0x1p63) return 0;
    return static_cast<int64_t>(number);
}
}
