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

// Conservative effect inference: opaque calls/branches erase knowledge, rather
// than treating missing facts as a proof. This is separate from capability checks.
inline void infer_lir_effects(LIR::LIR_Function& function) {
    using Op = LIR::LIR_Op;
    function.memory_effects.parameters.assign(function.param_count, Ownership::ReadBorrow);
    for (uint32_t i = 0; i < function.param_count; ++i) {
        auto type = function.get_register_abi_type(i);
        if (type != LIR::Type::Ptr && function.register_types.count(i))
            function.memory_effects.parameters[i] = Ownership::Value;
    }
    bool opaque = false;
    for (const auto& inst : function.instructions) {
        switch (inst.op) {
            case Op::Nop: case Op::Label: case Op::LoadConst:
            case Op::Mov: case Op::RegionEnter: case Op::RegionExit:
            case Op::RegionMove: case Op::Return: case Op::Ret:
            case Op::ListIndex: case Op::ListLen: case Op::DictGet:
            case Op::DictHas: case Op::DictLen: case Op::TupleGet:
            case Op::TupleLen: case Op::FrameGetField: break;
            default: opaque = true; break;
        }
    }
    if (opaque) for (auto& effect : function.memory_effects.parameters)
        if (effect != Ownership::Value) effect = Ownership::Unspecified;
    function.memory_effects.result = Ownership::Unspecified;
    function.memory_effects.borrowed_parameter = UINT32_MAX;
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
