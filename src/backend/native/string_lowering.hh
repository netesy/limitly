#pragma once
#include "lir/lir.hh"
#include "lir/analysis.hh"
#include <unordered_map>

namespace LM::Backend::Native {
struct SubstringComparison { size_t comparison; LIR::Reg needle; };
inline std::unordered_map<size_t, SubstringComparison> prove_substring_comparisons(const LIR::LIR_Function& function) {
    using Op = LIR::LIR_Op;
    std::unordered_map<size_t, SubstringComparison> result;
    LIR::CFGAnalysis cfg(function); cfg.analyze();
    LIR::DominatorAnalysis dominators(function, cfg); dominators.analyze();
    for (const auto& in : function.instructions)
        if (in.op == Op::RefCreate || in.op == Op::RefResolve || in.op == Op::RefMove ||
            in.op == Op::RefRelease || in.op == Op::OwnershipConsume) return result;
    for (size_t i = 0; i < function.instructions.size(); ++i) {
        const auto& call = function.instructions[i];
        if ((call.op != Op::CallBuiltin && call.op != Op::Call) || call.func_name != "_builtin_substring" ||
            call.call_args.size() != 3 || call.dst == UINT32_MAX || !call.ownership.consumes.empty()) continue;
        size_t j = i + 1;
        while (j < function.instructions.size() && function.instructions[j].op == Op::Nop &&
               function.instructions[j].ownership.consumes.empty()) ++j;
        if (j == function.instructions.size()) continue;
        const auto& compare = function.instructions[j];
        if ((compare.op != Op::CmpEQ && compare.op != Op::CmpNEQ) ||
            (compare.a != call.dst && compare.b != call.dst) || !compare.ownership.consumes.empty()) continue;
        auto needle = compare.a == call.dst ? compare.b : compare.a;
        if (needle == call.dst) continue;
        bool available = needle < function.param_count;
        for (size_t before = 0; before < i; ++before)
            if (function.instructions[before].dst == needle &&
                dominators.dominates(cfg.get_block_for_inst(before), cfg.get_block_for_inst(i))) available = true;
        if (!available) continue;
        unsigned uses = 0;
        bool overwritten = false;
        for (size_t k = 0; k < function.instructions.size(); ++k) {
            const auto& in = function.instructions[k];
            if (k != i && in.dst == call.dst) overwritten = true;
            if (in.a == call.dst) ++uses;
            if (in.b == call.dst) ++uses;
            for (auto arg : in.call_args) if (arg == call.dst) ++uses;
        }
        if (uses == 1 && !overwritten) result[i] = {j, needle};
    }
    return result;
}
}
