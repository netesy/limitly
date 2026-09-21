#pragma once

#include "lir.hh"
#include <vector>
#include <unordered_map>
#include <string>

namespace LM {
namespace LIR {

class AlgebraicSimplifier {
public:
    AlgebraicSimplifier() = default;

    // Check whether an instruction is pure and safe for local algebraic simplification
    static bool is_pure_instruction(const LIR_Inst& inst);

    // Perform pure basic-block local expression algebraic simplification
    bool optimize_function(LIR_Function& func);
};

} // namespace LIR
} // namespace LM
