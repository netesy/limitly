#include "verifier.hh"
#include <iostream>
#include <algorithm>
#include <unordered_map>

namespace LM {
namespace LIR {

bool Verifier::verify(const LIR_Function& func, std::vector<std::string>& errors) {
    bool success = true;
    
    for (const auto& inst : func.instructions) {
        if (!verify_instruction(inst, func, errors)) {
            success = false;
        }
    }
    
    if (!verify_control_flow(func, errors)) {
        success = false;
    }
    
    if (!detect_infinite_loops(func, errors)) {
        success = false;
    }

    // H27: conservative dataflow-ish checks. `verify_terminators` emits
    // warnings (not errors) so it does not flip `success`, but
    // `verify_use_before_def` is a hard error — reading an undefined
    // register is always a real bug.
    if (!verify_use_before_def(func, errors)) {
        success = false;
    }
    (void)verify_terminators(func, errors);
    
    return success;
}

bool Verifier::verify_instruction(const LIR_Inst& inst, const LIR_Function& func, std::vector<std::string>& errors) {
    if (inst.dst != UINT32_MAX && inst.dst >= func.register_count) {
        errors.push_back("Instruction " + lir_op_to_string(inst.op) + " uses invalid destination register " + std::to_string(inst.dst));
        return false;
    }
    
    if (inst.a != UINT32_MAX && inst.a >= func.register_count) {
        errors.push_back("Instruction " + lir_op_to_string(inst.op) + " uses invalid a register " + std::to_string(inst.a));
        return false;
    }
    
    if (inst.b != UINT32_MAX && inst.b >= func.register_count) {
        errors.push_back("Instruction " + lir_op_to_string(inst.op) + " uses invalid b register " + std::to_string(inst.b));
        return false;
    }
    
    for (Reg arg : inst.call_args) {
        if (arg >= func.register_count) {
            errors.push_back("Instruction " + lir_op_to_string(inst.op) + " uses invalid argument register " + std::to_string(arg));
            return false;
        }
    }
    
    return true;
}

bool Verifier::verify_control_flow(const LIR_Function& func, std::vector<std::string>& errors) {
    std::unordered_set<uint32_t> labels;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Label) {
            labels.insert(inst.imm);
        }
    }
    
    bool success = true;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
            if (labels.find(inst.imm) == labels.end()) {
                errors.push_back("Function " + func.name + " has jump to undefined label " + std::to_string(inst.imm));
                success = false;
            }
        }
    }
    
    return success;
}

bool Verifier::detect_infinite_loops(const LIR_Function& func, std::vector<std::string>& errors) {
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.op == LIR_Op::Jump) {
            uint32_t target_label = inst.imm;
            if (i > 0 && func.instructions[i-1].op == LIR_Op::Label && func.instructions[i-1].imm == target_label) {
                errors.push_back("Infinite loop detected in function " + func.name + ": self-jump at instruction " + std::to_string(i));
                return false;
            }
        }
    }
    
    return true;
}

// ============================================================================
// H27: conservative, linear / flow-insensitive use-before-def check.
//
// Walks `func.instructions` in order, maintaining a set of registers that
// have been "defined" so far. The set is seeded with the function's parameter
// registers [0, param_count). For each instruction:
//   * every register read in `a`, `b`, or `call_args` must already be in the
//     defined set (or be `UINT32_MAX`, meaning "no register"),
//   * then `dst` is added to the defined set (if it is a real register).
//
// This is intentionally conservative — it is flow-insensitive in the sense
// that it ignores jumps/labels and just walks the linear instruction list,
// so it can produce false negatives for paths that dominate through jumps.
// It does not produce false positives on legitimate straight-line code.
//
// A handful of opcodes (Store, MemoryStore, FrameSetField, PrintX, etc.)
// semantically treat `dst` as a source rather than a destination. We still
// mark `dst` as defined for those, which is a false-negative (we'd miss a
// use-before-def of dst) but never a false-positive.
// ============================================================================
bool Verifier::verify_use_before_def(const LIR_Function& func, std::vector<std::string>& errors) {
    // Empty bodies and stubs (e.g., intrinsics with no LIR) are fine.
    if (func.instructions.empty()) return true;

    std::unordered_set<Reg> defined;
    defined.reserve(func.register_count + 8);

    // Parameter registers are live at function entry.
    for (uint32_t i = 0; i < func.param_count && i < func.register_count; ++i) {
        defined.insert(i);
    }

    auto is_real_reg = [](Reg r) {
        return r != UINT32_MAX;
    };

    bool ok = true;
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];

        // Skip the check entirely for pseudo-ops that don't read registers.
        // Label/Jump/FuncDef/BeginModule/EndModule/ImportModule/ExportSymbol
        // carry metadata only.
        if (inst.op == LIR_Op::Label ||
            inst.op == LIR_Op::FuncDef ||
            inst.op == LIR_Op::BeginModule ||
            inst.op == LIR_Op::EndModule ||
            inst.op == LIR_Op::ImportModule ||
            inst.op == LIR_Op::ExportSymbol) {
            // Still, if FuncDef declares a register, mark it defined.
            if (is_real_reg(inst.dst) && inst.dst < func.register_count) {
                defined.insert(inst.dst);
            }
            continue;
        }

        // Collect all read registers for this instruction.
        auto check_use = [&](Reg r) {
            if (!is_real_reg(r)) return;
            if (r >= func.register_count) return; // already flagged by verify_instruction
            if (defined.find(r) == defined.end()) {
                errors.push_back("Function " + func.name + " instruction " +
                                 std::to_string(i) + " (" + lir_op_to_string(inst.op) +
                                 ") reads undefined register r" + std::to_string(r));
                ok = false;
            }
        };
        check_use(inst.a);
        check_use(inst.b);
        for (Reg arg : inst.call_args) check_use(arg);

        // Mark destination as defined (over-permissive for ops that use dst
        // as a source — see the comment above).
        if (is_real_reg(inst.dst) && inst.dst < func.register_count) {
            defined.insert(inst.dst);
        }
    }
    return ok;
}

// ============================================================================
// H27: conservative missing-return / terminator check.
//
// Emits *warnings* (not errors) for two situations:
//   1. A non-empty function with no `Return`/`Ret` instruction anywhere —
//      such a function either falls off the end (UB) or relies on implicit
//      void return.
//   2. A non-empty function whose final instruction is not a terminator
//      (Return / Ret / Jump / JumpIf / JumpIfFalse). This usually means the
//      function falls off the end of its last basic block.
//
// Warnings are pushed to `errors` with a `[warning]` prefix but do not flip
// the boolean return value, so they don't break existing valid LIR.
// ============================================================================
bool Verifier::verify_terminators(const LIR_Function& func, std::vector<std::string>& errors) {
    if (func.instructions.empty()) return true;

    auto is_terminator = [](LIR_Op op) {
        return op == LIR_Op::Return || op == LIR_Op::Ret ||
               op == LIR_Op::Jump   || op == LIR_Op::JumpIf ||
               op == LIR_Op::JumpIfFalse;
    };

    // Check 1: at least one return.
    bool has_return = false;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Return || inst.op == LIR_Op::Ret) {
            has_return = true;
            break;
        }
    }
    if (!has_return) {
        errors.push_back("[warning] Function " + func.name +
                         " has no Return/Ret instruction; control may fall off the end");
    }

    // Check 2: last instruction is a terminator.
    const LIR_Inst& last = func.instructions.back();
    if (!is_terminator(last.op)) {
        errors.push_back("[warning] Function " + func.name +
                         " does not end with a terminator (last op = " +
                         lir_op_to_string(last.op) + "); control may fall off the end");
    }

    // Warnings never fail the verifier.
    return true;
}

} // namespace LIR
} // namespace LM
