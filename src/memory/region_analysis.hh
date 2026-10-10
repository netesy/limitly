#pragma once
#include "../lir/lir.hh"
#include "../lir/analysis.hh"
#include "../backend/vm/vm_value.hh"
#include "aot_value_kind.hh"
#include <optional>
#include <deque>

namespace LM::Memory {
// Flow-sensitive actual kinds, derived from instructions rather than source
// annotations. Union joins and finite bit sets make loops converge. Undef is a
// real obligation; a definition on only one branch never proves a safe use.
inline std::optional<AOTValueKind> scalar_return_kind(const LIR::LIR_Function& function) {
    using Op = LIR::LIR_Op;
    constexpr unsigned integer = 1, boolean = 2, undefined = 4;
    if (function.instructions.empty() || function.param_count || !function.ownership_captures.empty()) return {};
    for (const auto& inst : function.instructions) {
        if (!inst.ownership.consumes.empty()) return {};
        switch (inst.op) {
        case Op::LoadConst: if (!IS_BOOL(inst.const_val) && !IS_INT(inst.const_val)) return {}; break;
        case Op::Nop: case Op::Label: case Op::Mov:
        case Op::CmpEQ: case Op::CmpNEQ: case Op::CmpLT: case Op::CmpLE: case Op::CmpGT: case Op::CmpGE:
        case Op::Jump: case Op::JumpIf: case Op::JumpIfFalse:
        case Op::RegionEnter: case Op::RegionExit: case Op::RegionMove:
        case Op::Return: case Op::Ret: break;
        default: return {}; // Includes unknown calls, arithmetic overflow, and every memory effect.
        }
    }
    LIR::CFGAnalysis cfg(function); cfg.analyze();
    const auto& blocks = cfg.get_blocks();
    if (blocks.empty()) return {};
    using State = std::unordered_map<LIR::Reg, unsigned>;
    auto kind = [&](const State& state, LIR::Reg reg) {
        auto found = state.find(reg); return found == state.end() ? undefined : found->second;
    };
    std::vector<std::optional<State>> inputs(blocks.size()); inputs[0] = State{};
    std::deque<uint32_t> pending{0};
    std::vector<bool> queued(blocks.size(), false); queued[0] = true;
    while (!pending.empty()) {
        auto index = pending.front(); pending.pop_front(); queued[index] = false;
        auto state = *inputs[index];
        const auto& block = blocks[index];
        for (size_t i = block.start_inst_idx; i < block.end_inst_idx; ++i) {
            const auto& inst = function.instructions[i];
            if (inst.op == Op::LoadConst) state[inst.dst] = IS_BOOL(inst.const_val) ? boolean : integer;
            else if (inst.op == Op::Mov) state[inst.dst] = kind(state, inst.a);
            else if (inst.op >= Op::CmpEQ && inst.op <= Op::CmpGE) state[inst.dst] = boolean;
        }
        for (auto next : block.successors) {
            bool changed = false;
            if (!inputs[next]) { inputs[next] = state; changed = true; }
            else {
                auto joined = *inputs[next];
                for (auto [reg, value] : state) joined[reg] = kind(*inputs[next], reg) | value;
                for (auto [reg, value] : *inputs[next]) joined[reg] = value | kind(state, reg);
                if (joined != *inputs[next]) { inputs[next] = std::move(joined); changed = true; }
            }
            if (changed && !queued[next]) { queued[next] = true; pending.push_back(next); }
        }
    }
    unsigned returned = 0;
    for (size_t index = 0; index < blocks.size(); ++index) {
        if (!inputs[index]) continue;
        auto state = *inputs[index];
        const auto& block = blocks[index];
        for (size_t i = block.start_inst_idx; i < block.end_inst_idx; ++i) {
            const auto& inst = function.instructions[i];
            auto valid = [&](LIR::Reg reg) { auto value = kind(state, reg); return value && !(value & undefined); };
            switch (inst.op) {
            case Op::LoadConst: state[inst.dst] = IS_BOOL(inst.const_val) ? boolean : integer; break;
            case Op::Mov: if (!valid(inst.a)) return {}; state[inst.dst] = kind(state, inst.a); break;
            case Op::CmpEQ: case Op::CmpNEQ: case Op::CmpLT: case Op::CmpLE: case Op::CmpGT: case Op::CmpGE:
                if (!valid(inst.a) || !valid(inst.b)) return {};
                // Mixed-kind comparison needs the dynamic kind side channel.
                // Boolean ordering also retains its existing runtime semantics.
                if (kind(state, inst.a) != kind(state, inst.b) ||
                    (kind(state, inst.a) != integer && kind(state, inst.a) != boolean) ||
                    (kind(state, inst.a) == boolean && inst.op != Op::CmpEQ && inst.op != Op::CmpNEQ)) return {};
                state[inst.dst] = boolean; break;
            case Op::RegionMove: if (!valid(inst.a)) return {}; break;
            case Op::JumpIf: case Op::JumpIfFalse:
                if (kind(state, inst.a) != boolean || block.successors.size() != 2) return {};
                break;
            case Op::Jump: if (block.successors.size() != 1) return {}; break;
            case Op::Return: case Op::Ret:
                if (!valid(inst.a)) return {};
                returned |= kind(state, inst.a); break;
            default: break;
            }
        }
        auto last = function.instructions[block.end_inst_idx - 1].op;
        if (block.successors.empty() && last != Op::Return && last != Op::Ret) return {};
    }
    if (returned == boolean) return AOTValueKind::Boolean;
    if (returned == integer) return AOTValueKind::Integer;
    return {}; // Mixed return kinds need the dynamic callable boundary.
}

// A closed, backend-independent proof. Every unlisted operation is unknown.
// In particular arithmetic can allocate on overflow, and calls may run
// finalizers, retain aliases, allocate or reenter the compiler runtime.
inline bool proven_scalar_leaf(const LIR::LIR_Function& function) {
    using Op = LIR::LIR_Op;
    if (!scalar_return_kind(function)) return false;
    // Parameter annotations alone do not prove actual kinds through `any` or
    // opaque callable boundaries. Until those obligations are represented,
    // retain the entire dynamic contract for every parameterized function.
    if (function.instructions.empty() || function.param_count != 0 ||
        !function.ownership_captures.empty()) return false;
    for (const auto& inst : function.instructions) {
        if (!inst.ownership.consumes.empty()) return false;
        switch (inst.op) {
        case Op::LoadConst:
            if (!IS_BOOL(inst.const_val) && !IS_INT(inst.const_val)) return false;
            break;
        case Op::Return: case Op::Ret: break;
        case Op::Nop: case Op::Label: case Op::Mov:
        case Op::CmpEQ: case Op::CmpNEQ: case Op::CmpLT: case Op::CmpLE:
        case Op::CmpGT: case Op::CmpGE:
        case Op::Jump: case Op::JumpIf: case Op::JumpIfFalse:
        case Op::RegionEnter: case Op::RegionExit: case Op::RegionMove: break;
        default: return false;
        }
    }
    // The register placement proof is deliberately SSA-shaped: each definition
    // dominates every use and no parameter or temporary is reassigned.
    LIR::CFGAnalysis cfg(function); cfg.analyze();
    bool returns_boolean = false;
    for (const auto& block : cfg.get_blocks()) {
        if (!block.reachable) continue;
        const auto op = function.instructions[block.end_inst_idx - 1].op;
        if (op == Op::Return || op == Op::Ret) returns_boolean = true;
        else if (block.successors.empty()) return false;
        if (op == Op::Jump && block.successors.size() != 1) return false;
        if ((op == Op::JumpIf || op == Op::JumpIfFalse) && block.successors.size() != 2) return false;
    }
    // Falling off a body returns nil, which cannot use a boolean boundary.
    if (!returns_boolean) return false;
    LIR::DominatorAnalysis dominators(function, cfg); dominators.analyze();
    std::unordered_map<LIR::Reg, size_t> definitions;
    for (LIR::Reg p = 0; p < function.param_count; ++p) definitions[p] = SIZE_MAX;
    for (size_t i = 0; i < function.instructions.size(); ++i) {
        const auto& inst = function.instructions[i];
        switch (inst.op) {
        case Op::LoadConst: case Op::Mov: case Op::CmpEQ: case Op::CmpNEQ:
        case Op::CmpLT: case Op::CmpLE: case Op::CmpGT: case Op::CmpGE:
            if (inst.dst == UINT32_MAX || !definitions.emplace(inst.dst, i).second) return false;
            break;
        default: break;
        }
    }
    for (size_t i = 0; i < function.instructions.size(); ++i) {
        const auto& inst = function.instructions[i];
        auto available = [&](LIR::Reg reg) {
            auto definition = definitions.find(reg);
            if (definition == definitions.end()) return false;
            if (definition->second == SIZE_MAX) return true;
            if (definition->second >= i) return false;
            auto source = cfg.get_block_for_inst(definition->second);
            auto destination = cfg.get_block_for_inst(i);
            return source == destination ? definition->second < i : dominators.dominates(source, destination);
        };
        switch (inst.op) {
        case Op::Mov: case Op::JumpIf: case Op::JumpIfFalse: case Op::Return:
        case Op::Ret: case Op::RegionMove:
            if (!available(inst.a)) return false;
            break;
        case Op::CmpEQ: case Op::CmpNEQ: case Op::CmpLT: case Op::CmpLE:
        case Op::CmpGT: case Op::CmpGE:
            if (!available(inst.a) || !available(inst.b)) return false;
            break;
        default: break;
        }
    }
    return true;
}
inline bool runtime_regions_proven_unnecessary(const LIR::LIR_Function& function) {
    if (!scalar_return_kind(function)) return false;
    for (const auto& inst : function.instructions)
        if (inst.op == LIR::LIR_Op::RegionEnter || inst.op == LIR::LIR_Op::RegionExit ||
            inst.op == LIR::LIR_Op::RegionMove) return false;
    return true;
}
inline bool proven_closed_boolean_boundary(const LIR::LIR_Function& function) {
    // Declared boolean parameters can still receive erased values. The dynamic
    // callable boundary must preserve their actual kinds and returned aliases.
    return scalar_return_kind(function) == AOTValueKind::Boolean && runtime_regions_proven_unnecessary(function);
}
inline bool eliminate_scalar_leaf_regions(LIR::LIR_Function& function) {
    if (!scalar_return_kind(function)) return false;
    bool changed = false;
    for (auto& inst : function.instructions) {
        if (inst.op == LIR::LIR_Op::RegionEnter || inst.op == LIR::LIR_Op::RegionExit ||
            inst.op == LIR::LIR_Op::RegionMove) {
            // Keep positions/labels and ownership facts intact.
            inst.op = LIR::LIR_Op::Nop;
            changed = true;
        }
    }
    return changed;
}
}
