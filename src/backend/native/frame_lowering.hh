#pragma once
#include "memory/effect_analysis.hh"
#include <unordered_map>
#include <unordered_set>

namespace LM::Backend::Native {
struct FrameAccessProof {
    std::unordered_set<size_t> cached, establish;
    std::unordered_set<LIR::Reg> views;
};
// Reuse only views of fresh, unpublished frames within straight-line intervals.
// The first successful checked access establishes liveness and a lower bound
// on field_count. A later equal/lower index therefore needs no new check.
inline FrameAccessProof prove_frame_views(const LIR::LIR_Function& function,
    const std::vector<const LIR::LIR_Function*>& functions, const Memory::RuntimeEffectAnalysis& effects) {
    using Op = LIR::LIR_Op;
    std::unordered_map<std::string, const LIR::LIR_Function*> targets;
    for (auto* fn : functions) if (fn) targets[fn->name] = fn;
    std::unordered_set<LIR::Reg> fresh;
    struct Checked { uint32_t index; size_t instruction; };
    std::unordered_map<LIR::Reg, Checked> checked;
    FrameAccessProof proof;
    for (size_t i = 0; i < function.instructions.size(); ++i) {
        const auto& in = function.instructions[i];
        if (!in.ownership.consumes.empty()) { fresh.clear(); checked.clear(); }
        switch (in.op) {
        case Op::NewFrame:
            fresh.insert(in.dst); checked.erase(in.dst); break;
        case Op::Mov: case Op::Copy: {
            bool local = fresh.count(in.a);
            fresh.erase(in.dst); checked.erase(in.dst);
            if (local) fresh.insert(in.dst);
            break;
        }
        case Op::Nop: break;
        case Op::LoadConst: fresh.erase(in.dst); checked.erase(in.dst); break;
        case Op::FrameGetField: {
            if (fresh.count(in.a)) {
                auto found = checked.find(in.a);
                if (found != checked.end() && in.b <= found->second.index) {
                    proof.cached.insert(i); proof.establish.insert(found->second.instruction); proof.views.insert(in.a);
                } else checked[in.a] = {in.b, i};
            }
            fresh.erase(in.dst); checked.erase(in.dst);
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
            if (!safe) fresh.clear();
            checked.clear(); fresh.erase(in.dst); break;
        }
        default: fresh.clear(); checked.clear(); break;
        }
    }
    return proof;
}
}
