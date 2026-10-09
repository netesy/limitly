#pragma once
#include <cstdint>

namespace LM::Memory {
// Canonical reference modes. A nullable reference represents nil as token zero;
// only explicitly nullable operations accept it. Ordinary tokens stay strict.
inline constexpr uint64_t ReferenceWritable = 1;
inline constexpr uint64_t ReferenceNullable = 2;
// RefMove uses the high immediate bit as nullable mode; lexical IDs use 31 bits.
inline constexpr uint64_t ReferenceMoveNullable = uint64_t{1} << 31;
inline constexpr uint64_t ReferenceRegionMask = ReferenceMoveNullable - 1;
inline constexpr uint64_t ReferenceMoveMask = UINT32_MAX;
}
