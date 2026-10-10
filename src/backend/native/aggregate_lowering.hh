#pragma once
#include "lir/lir.hh"
#include "lir/analysis.hh"
#include <optional>
#include <unordered_set>

namespace LM::Backend::Native {
// Private lowering proof, not a canonical LIR transformation. A factory's
// tuples have exactly two initialized fields and no observable local identity.
inline std::optional<std::unordered_set<LIR::Reg>> immediate_pair_factory(
    const LIR::LIR_Function& function) {
    using Op = LIR::LIR_Op;
    LIR::CFGAnalysis cfg(function); cfg.analyze();
    auto reachable = [&](size_t index) {
        auto* block = cfg.get_block(cfg.get_block_for_inst(index));
        return block && block->reachable;
    };
    std::unordered_set<LIR::Reg> pairs;
    for (size_t i = 0; i < function.instructions.size(); ++i) {
        const auto& create = function.instructions[i];
        if (!reachable(i) || create.op != Op::TupleCreate) continue;
        if (create.imm != 2 || !pairs.insert(create.dst).second) return {};
        unsigned initialized = 0;
        // Initialization must finish in straight-line code before cleanup.
        // Reads/arithmetic/calls are preserved; the tuple itself cannot be
        // observed by any of them (checked below). Non-immediate fields
        // materialize the ownership graph at their original store operation.
        std::unordered_map<LIR::Reg, int64_t> indices;
        for (size_t next = i + 1; initialized != 3; ++next) {
            if (next >= function.instructions.size() || !reachable(next)) return {};
            const auto& in = function.instructions[next];
            switch (in.op) {
            case Op::Jump: case Op::JumpIf: case Op::JumpIfFalse:
            case Op::Return: case Op::Ret: case Op::RegionEnter:
            case Op::RegionExit: case Op::RegionMove: case Op::TupleCreate: return {};
            default: break;
            }
            indices.erase(in.dst);
            if (in.op == Op::LoadConst && IS_INT(in.const_val))
                indices[in.dst] = UNBOX_INT(in.const_val);
            if (in.op != Op::TupleSet || in.dst != create.dst) continue;
            auto index = indices.find(in.a);
            if (index == indices.end()) return {};
            auto field = index->second;
            if (field < 0 || field > 1 || (initialized & (1u << field))) return {};
            initialized |= 1u << field;
        }
    }
    if (pairs.empty()) return {};
    bool returned = false;
    std::unordered_map<LIR::Reg, unsigned> writes;
    for (size_t index = 0; index < function.instructions.size(); ++index) {
        if (!reachable(index)) continue;
        const auto& in = function.instructions[index];
        for (auto arg : in.call_args) if (pairs.count(arg)) return {};
        // Only the two proven initialization stores are specialized. Later
        // mutation (including wide/dynamic indices) retains normal tuples.
        if (in.op == Op::TupleSet && pairs.count(in.dst) && ++writes[in.dst] > 2) return {};
        if (in.op == Op::Return || in.op == Op::Ret) {
            if (!pairs.count(in.a)) return {};
            returned = true;
        }
        if (pairs.count(in.dst) && in.op != Op::TupleCreate && in.op != Op::TupleSet) return {};
        if (pairs.count(in.a) && in.op != Op::RegionMove && in.op != Op::Return && in.op != Op::Ret) return {};
        if (pairs.count(in.b)) return {};
    }
    return returned ? std::optional(pairs) : std::nullopt;
}

// Copies are permitted because all observable uses are read-only projections.
// Mutable aliases, calls, erasure, identity tests, references and escapes fail.
inline bool pair_result_is_projected(const LIR::LIR_Function& function, LIR::Reg result) {
    using Op = LIR::LIR_Op;
    std::unordered_set<LIR::Reg> aliases{result};
    bool changed;
    do {
        changed = false;
        for (const auto& in : function.instructions)
            if ((in.op == Op::Mov || in.op == Op::Copy) && aliases.count(in.a))
                changed |= aliases.insert(in.dst).second;
    } while (changed);
    std::unordered_map<LIR::Reg, unsigned> definitions;
    bool projected = false;
    for (const auto& in : function.instructions) {
        for (auto arg : in.call_args) if (aliases.count(arg)) return false;
        if (aliases.count(in.dst)) {
            if (++definitions[in.dst] != 1) return false;
            if (in.dst != result && in.op != Op::Mov && in.op != Op::Copy) return false;
            if (in.dst == result && in.op != Op::Call) return false;
        }
        if (aliases.count(in.a)) {
            if (in.op == Op::TupleGet) projected = true;
            else if (in.op != Op::Mov && in.op != Op::Copy && in.op != Op::RegionMove) return false;
        }
        if (aliases.count(in.b)) return false;
    }
    return projected;
}
}
