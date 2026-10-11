#pragma once
#include "memory/effect_analysis.hh"
#include <optional>
#include <unordered_map>
#include <unordered_set>

namespace LM::Backend::Native {
struct FrameAccessProof {
    std::unordered_set<size_t> cached, establish;
    std::unordered_map<size_t, size_t> cached_sources;
};
// Reuse views of fresh frames and verified, read-borrowed parameters within
// straight-line intervals. Caller-owned borrows outlive the invocation; all
// potentially invalidating operations terminate the validated interval.
// The first successful checked access establishes liveness and a lower bound
// on field_count. A later equal/lower index therefore needs no new check.
inline FrameAccessProof prove_frame_views(const LIR::LIR_Function& function,
    const std::vector<const LIR::LIR_Function*>& functions, const Memory::RuntimeEffectAnalysis& effects) {
    using Op = LIR::LIR_Op;
    std::unordered_map<std::string, const LIR::LIR_Function*> targets;
    for (auto* fn : functions) if (fn) targets[fn->name] = fn;
    std::unordered_set<LIR::Reg> fresh;
    std::unordered_set<LIR::Reg> borrowed;
    for (LIR::Reg p = 0; p < function.param_count; ++p)
        if (p < function.ownership_parameters.size() && function.ownership_parameters[p] &&
            p < function.inferred_effects.parameters.size() &&
            function.inferred_effects.parameters[p] == Memory::Read)
            borrowed.insert(p);
    struct Checked { uint32_t index; size_t instruction; };
    std::unordered_map<LIR::Reg, Checked> checked;
    std::unordered_map<LIR::Reg, LIR::Reg> resolved;
    auto redefine = [&](LIR::Reg reg) {
        fresh.erase(reg); borrowed.erase(reg); checked.erase(reg);
        std::erase_if(resolved, [&](const auto& entry) {return entry.first == reg || entry.second == reg;});
    };
    FrameAccessProof proof;
    for (size_t i = 0; i < function.instructions.size(); ++i) {
        const auto& in = function.instructions[i];
        if (!in.ownership.consumes.empty()) { fresh.clear(); borrowed.clear(); checked.clear(); resolved.clear(); }
        switch (in.op) {
        case Op::NewFrame:
            redefine(in.dst); fresh.insert(in.dst); break;
        case Op::Mov: case Op::Copy: {
            if (in.dst == in.a) break;
            bool local = fresh.count(in.a);
            bool borrow = borrowed.count(in.a);
            auto previous = checked.find(in.a);
            std::optional<Checked> view = previous == checked.end() ? std::nullopt : std::optional(previous->second);
            redefine(in.dst);
            if (local) fresh.insert(in.dst);
            if (borrow) borrowed.insert(in.dst);
            if ((local || borrow) && view) checked[in.dst] = *view;
            break;
        }
        case Op::Nop: break;
        case Op::LoadConst: redefine(in.dst); break;
        case Op::RegionEnter: case Op::RegionExit:
            fresh.clear(); checked.clear(); resolved.clear(); break;
        case Op::RefResolve: {
            std::optional<Checked> view;
            auto old = resolved.find(in.a);
            if (old != resolved.end()) {
                auto found = checked.find(old->second);
                if (found != checked.end()) view = found->second;
            }
            redefine(in.dst);
            // Runtime resolution establishes generation and read permission.
            // A repeated resolution still executes its permission check. Only
            // the frame-address proof is shared, within the same safe interval.
            borrowed.insert(in.dst); resolved[in.a] = in.dst;
            if (view) checked[in.dst] = *view;
            break;
        }
        case Op::FrameGetField: {
            if (fresh.count(in.a) || borrowed.count(in.a)) {
                auto found = checked.find(in.a);
                if (found != checked.end() && in.b <= found->second.index) {
                    proof.cached.insert(i); proof.establish.insert(found->second.instruction);
                    proof.cached_sources[i] = found->second.instruction;
                } else checked[in.a] = {in.b, i};
            }
            redefine(in.dst);
            break;
        }
        case Op::Call: case Op::CallVoid: {
            auto target = targets.find(in.func_name);
            bool safe = target != targets.end() && effects.cannot_invalidate_or_publish(in.func_name);
            if (safe) {
                const auto& parameters = target->second->inferred_effects.parameters;
                for (size_t p = 0; p < in.call_args.size(); ++p)
                    if (fresh.count(in.call_args[p]) && (p >= parameters.size() ||
                        (parameters[p] & (Memory::Retain | Memory::Opaque | Memory::Consume)))) safe = false;
            }
            if (!safe) { fresh.clear(); borrowed.clear(); }
            checked.clear(); resolved.clear(); fresh.erase(in.dst); borrowed.erase(in.dst); break;
        }
        default: fresh.clear(); borrowed.clear(); checked.clear(); resolved.clear(); break;
        }
    }
    return proof;
}
}
