#pragma once

#include "lir.hh"
#include <set>
#include <vector>

namespace LM {
namespace LIR {

class Optimizer {
public:
    explicit Optimizer(LIR_Function& func) : func_(func) {}

    /**
     * @brief Run all enabled optimizations
     * @return true if any change was made
     */
    bool optimize();

    /**
     * @brief Perform Dead Code Elimination with CFG-based liveness analysis
     * @return true if instructions were removed
     */
    bool dead_code_elimination();

    /**
     * @brief Remove unreachable code after unconditional jumps and returns
     * @return true if instructions were removed
     */
    bool remove_unreachable_code();

    /**
     * @brief Perform Dead Code Elimination using simple backward pass
     * @return true if instructions were removed
     */
    bool dead_code_elimination_simple();

    /**
     * @brief Perform Peephole Optimization
     * @return true if changes were made
     */
    bool peephole_optimize();

    /**
     * @brief Perform Constant Folding
     * @return true if changes were made
     */
    bool constant_folding();

private:
    LIR_Function& func_;

    /**
     * @brief Check if an instruction has side effects
     * @param inst The instruction to check
     * @return true if the instruction has side effects
     */
    bool has_instruction_side_effects(const LIR_Inst& inst) const;
};

} // namespace LIR
} // namespace LM
