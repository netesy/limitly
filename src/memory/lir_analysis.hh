#pragma once
#include "../lir/lir.hh"
#include "reference_flags.hh"
#include <unordered_set>

namespace LM::Memory {
inline bool valid_reference_instruction(const LIR::LIR_Inst& inst) {
    using Op = LIR::LIR_Op;
    const bool create = inst.op == Op::RefCreate;
    const bool resolve = inst.op == Op::RefResolve;
    const bool release = inst.op == Op::RefRelease;
    const bool consume = inst.op == Op::OwnershipConsume;
    const bool move = inst.op == Op::RefMove;
    if (!create && !resolve && !release && !consume && !move) return true;
    if (inst.a == UINT32_MAX || inst.b != UINT32_MAX || !inst.call_args.empty()) return false;
    if (move) return inst.dst != UINT32_MAX && !(inst.imm & ~ReferenceMoveMask) && inst.result_type == LIR::Type::U64;
    if (create || resolve)
        return inst.dst != UINT32_MAX && inst.imm <= (ReferenceWritable | ReferenceNullable) &&
               inst.result_type == (create ? LIR::Type::U64 : LIR::Type::Ptr);
    return inst.dst == UINT32_MAX && (release ? !(inst.imm & ~ReferenceNullable) : inst.imm == 0) && inst.result_type == LIR::Type::Void;
}

// The frontend's semantic facts remain authoritative. A native ABI type is
// not an ownership proof: an annotated scalar can receive an erased alias.
// Unknown synthesized/opaque callable parameters therefore stay unspecified.
inline void infer_lir_effects(LIR::LIR_Function& function) {
    if (function.memory_effects.parameters.empty())
        function.memory_effects.parameters.assign(function.param_count, Ownership::Unspecified);
    if (function.param_count && function.inferred_effects.parameters.size() == function.param_count) {
        function.memory_effects.parameters.clear();
        for (auto effects : function.inferred_effects.parameters)
            function.memory_effects.parameters.push_back(effects & Consume ? Ownership::Owned :
                effects & Opaque ? Ownership::Unspecified : effects & Mutate ? Ownership::WriteBorrow : Ownership::ReadBorrow);
        if (function.inferred_effects.return_aliases.size() == 1) {
            function.memory_effects.result = Ownership::ReadBorrow;
            function.memory_effects.borrowed_parameter = *function.inferred_effects.return_aliases.begin();
        }
    }
}
// Erase only a closed borrow of a freshly allocated list, with no intervening
// instructions and no other token uses. An unknown call or alias defeats proof.
inline bool eliminate_proven_local_borrows(LIR::LIR_Function& function) {
    using Op = LIR::LIR_Op;
    auto& code = function.instructions;
    bool changed = false;
    for (size_t i = 0; i + 3 < code.size(); ++i) {
        const auto& allocation = code[i];
        const auto& create = code[i + 1];
        const auto& resolve = code[i + 2];
        const auto& release = code[i + 3];
        if (allocation.op != Op::ListCreate || create.op != Op::RefCreate ||
            resolve.op != Op::RefResolve || release.op != Op::RefRelease ||
            allocation.dst == UINT32_MAX || create.a != allocation.dst || create.dst == UINT32_MAX ||
            create.dst == allocation.dst || resolve.dst == create.dst ||
            create.b != UINT32_MAX || resolve.b != UINT32_MAX || release.b != UINT32_MAX ||
            release.dst != UINT32_MAX || release.imm != 0 ||
            resolve.a != create.dst || release.a != create.dst ||
            resolve.imm > create.imm || create.imm > 1) continue;
        size_t uses = 0;
        for (const auto& inst : code) {
            if (inst.a == create.dst) ++uses;
            if (inst.b == create.dst) ++uses;
            for (auto arg : inst.call_args) if (arg == create.dst) ++uses;
        }
        if (uses != 2) continue;
        auto owner = allocation.dst;
        code[i + 2] = LIR::LIR_Inst(Op::Mov, LIR::Type::Ptr, resolve.dst, owner, UINT32_MAX);
        code[i + 1] = LIR::LIR_Inst{};
        code[i + 3] = LIR::LIR_Inst{};
        changed = true;
    }
    return changed;
}
} // namespace LM::Memory
