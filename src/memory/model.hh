#pragma once
#include <cstdint>
#include <vector>

namespace LM::Memory {
// Shared by the compiler, persisted LIR and both runtime adapters.
enum class Ownership : uint8_t { Unspecified, Value, Owned, ReadBorrow, WriteBorrow };
struct FunctionEffects {
    // Unspecified means no proof, never permission to erase checks.
    std::vector<Ownership> parameters;
    Ownership result = Ownership::Unspecified;
    uint32_t borrowed_parameter = UINT32_MAX;
};


// These facts are the language contract, not C++ template instantiations that
// pretend to prove the behavior of a separate language's program.
constexpr bool same_generation(uint64_t captured, uint64_t current) {
    return captured == current;
}
constexpr bool borrow_outlives_owner(int owner_depth, int borrow_depth) {
    return borrow_depth < owner_depth;
}
constexpr bool unavailable_on_join(bool left_moved, bool right_moved) {
    return left_moved || right_moved;
}
} // namespace LM::Memory
