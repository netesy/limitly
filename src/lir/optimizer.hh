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
     * @brief Perform Dead Code Elimination
     * @return true if instructions were removed
     */
    bool dead_code_elimination();

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
};

} // namespace LIR
} // namespace LM
