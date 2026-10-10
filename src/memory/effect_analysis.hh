#pragma once
#include "../lir/lir.hh"
#include "region_analysis.hh"
#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace LM::Memory {
// Backend-independent, recomputable effects. Missing operations/targets are top.
enum RuntimeEffect : unsigned {
    Allocates = 1, Invalidates = 2, ObservableCleanup = 4,
    Escapes = 8, Mutates = 16, OpaqueRuntime = 32,
    AllRuntimeEffects = 63
};
inline unsigned instruction_runtime_effects(const LIR::LIR_Inst& in) {
    using Op = LIR::LIR_Op;
    if (!in.ownership.consumes.empty()) return AllRuntimeEffects;
    switch (in.op) {
    case Op::Nop: case Op::Label: case Op::Mov: case Op::Copy:
    case Op::Param: case Op::Jump: case Op::JumpIf: case Op::JumpIfFalse:
    case Op::Return: case Op::Ret: case Op::RegionEnter: case Op::RegionExit:
    case Op::RegionMove: return 0;
    case Op::LoadConst: return IS_PTR(in.const_val) ? static_cast<unsigned>(Allocates) : 0u;
    case Op::FrameGetField: return 0;
    case Op::FrameSetField: return Mutates | Escapes;
    case Op::NewFrame: return Allocates | ObservableCleanup;
    case Op::ListCreate: case Op::TupleCreate: return Allocates;
    // Numeric annotations do not exclude boxing, overflow or erased operands.
    case Op::Add: case Op::Sub: case Op::Mul: case Op::Div: case Op::Mod:
    case Op::Cast: return AllRuntimeEffects;
    default: return AllRuntimeEffects;
    }
}
class RuntimeEffectAnalysis {
    std::unordered_map<std::string, unsigned> effects_;
public:
    explicit RuntimeEffectAnalysis(const std::vector<const LIR::LIR_Function*>& functions) {
        std::unordered_map<std::string, const LIR::LIR_Function*> bodies;
        std::unordered_map<std::string, ScalarOperationProof> scalar;
        for (auto* fn : functions) if (fn) {
            bodies[fn->name] = fn; effects_[fn->name] = 0;
            scalar.emplace(fn->name, prove_scalar_operations(*fn));
        }
        // Finite monotone union lattice; recursive SCCs cannot cause nontermination.
        bool changed;
        do {
            changed = false;
            for (const auto& [name, fn] : bodies) {
                unsigned result = fn->instructions.empty() ? AllRuntimeEffects : 0u;
                for (auto parameter : fn->inferred_effects.parameters)
                    if (parameter & (Retain | Opaque | Consume)) result |= AllRuntimeEffects;
                for (size_t i = 0; i < fn->instructions.size(); ++i) {
                    const auto& in = fn->instructions[i];
                    if (in.op == LIR::LIR_Op::Call || in.op == LIR::LIR_Op::CallVoid) {
                        auto found = effects_.find(in.func_name);
                        result |= found == effects_.end() ? AllRuntimeEffects : found->second;
                        if (!in.ownership.consumes.empty()) result |= AllRuntimeEffects;
                    } else if (scalar.at(name).stores.count(i) && in.ownership.consumes.empty()) result |= Mutates;
                    else result |= instruction_runtime_effects(in);
                }
                result |= effects_[name];
                if (result != effects_[name]) { effects_[name] = result; changed = true; }
            }
        } while (changed);
    }
    unsigned effects(const std::string& name) const {
        auto found = effects_.find(name);
        return found == effects_.end() ? AllRuntimeEffects : found->second;
    }
    bool cannot_invalidate_or_publish(const std::string& name) const {
        // This query protects caller-owned objects across a call, not the
        // callee's own region cleanup. It is not a region-elimination proof.
        return !(effects(name) & (Invalidates | ObservableCleanup | Escapes | OpaqueRuntime));
    }
};
} // namespace LM::Memory
