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

    /**
     * @brief Remove redundant consecutive calls to the same function at entry point
     * @return true if instructions were removed
     */
    bool remove_redundant_entry_calls();

    /**
     * @brief Remove redundant consecutive memory loads and stores
     * @return true if changes were made
     */
    bool redundant_memory_elimination();

    /**
     * @brief Perform small leaf function inlining
     * @return true if changes were made
     */
    bool function_inlining();

    /**
     * @brief Perform Copy Propagation across basic blocks using def-use analysis
     * @return true if copies were propagated
     */
    bool copy_propagation();

    /**
     * @brief Perform Global Value Numbering across basic block sequences
     * @return true if changes were made
     */
    bool global_value_numbering();

    /**
     * @brief Eliminate empty generational check region enter/exit pairs
     * @return true if changes were made
     */
    bool generational_check_hoisting();

    /**
     * @brief Remove unused/orphaned label instructions not targeted by any jump
     * @return true if labels were removed
     */
    bool prune_orphaned_labels();

    /**
     * @brief Perform tail-call optimization converting tail recursive calls into jumps
     * @return true if tail calls were optimized
     */
    bool tail_call_optimization();

    /**
     * @brief Hoist loop-invariant operations before loop entry labels
     * @return true if instructions were hoisted
     */
    bool loop_invariant_code_motion();

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
