#include "verifier.hh"
#include "analysis.hh"
#include <deque>
#include <optional>
#include "../memory/lir_analysis.hh"
#include <iostream>
#include <algorithm>
#include <unordered_map>

namespace LM {
namespace LIR {

bool Verifier::verify(const LIR_Function& func, std::vector<std::string>& errors) {
    bool success = verify_memory_regions(func, errors);
    if (!verify_ownership(func, errors)) success = false;
    if ((!func.memory_effects.parameters.empty() && func.memory_effects.parameters.size() != func.param_count) ||
        (func.memory_effects.borrowed_parameter != UINT32_MAX && func.memory_effects.borrowed_parameter >= func.param_count)) {
        errors.push_back("Invalid function memory effects: " + func.name);
        success = false;
    }
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
    if (!verify_bit_vector_semantics(func, errors)) {
        success = false;
    }
    if (!verify_float_arithmetic_semantics(func, errors)) {
        success = false;
    }
    if (!verify_collections_and_strings(func, errors)) {
        success = false;
    }
    if (!verify_enums_unions_and_contracts(func, errors)) {
        success = false;
    }
    (void)verify_terminators(func, errors);
    
    return success;
}

bool Verifier::verify_ownership(const LIR_Function& func, std::vector<std::string>& errors) {
    CFGAnalysis cfg(func); cfg.analyze();
    const auto& blocks = cfg.get_blocks();
    if (blocks.empty()) return true;
    struct Binding {
        unsigned availability = 1; // Uninitialized / live / consumed path bits.
        bool stale = false;
        std::set<Memory::Identity> aliases;
        bool operator==(const Binding&) const = default;
    };
    using State = std::map<Memory::Identity, Binding>;
    State initial;
    for (auto id : func.ownership_parameters) initial[id].availability = 2;
    for (auto id : func.ownership_captures) initial[id].availability = 2;
    std::vector<std::optional<State>> inputs(blocks.size()); inputs[0] = initial;
    std::deque<uint32_t> queue{0};
    std::vector<bool> queued(blocks.size(), false); queued[0] = true;
    // Inputs are joined immediately. One pending visit consumes the newest
    // input, so duplicate queue entries add work without adding information.
    auto enqueue = [&](uint32_t block) {
        if (!queued[block]) {queue.push_back(block); queued[block] = true;}
    };
    auto transfer = [&](State state, const AnalysisBlock& block, bool diagnose) {
        auto fail = [&](size_t index, const std::string& text) {
            errors.push_back("Function " + func.name + " instruction " + std::to_string(index) + ": " + text);
        };
        for (size_t i = block.start_inst_idx; i < block.end_inst_idx; ++i) {
            const auto& event = func.instructions[i].ownership;
            for (auto id : event.reads) if (diagnose && (state[id].availability != 2 || state[id].stale))
                fail(i, "ownership read is unavailable or has stale alias provenance");
            for (auto id : event.consumes) {
                if (diagnose && (state[id].availability != 2 || state[id].stale)) fail(i, "ownership consumption is invalid on a reachable path");
                state[id].availability = 4;
                for (auto& [alias, value] : state) if (value.aliases.count(id)) value.stale = true;
            }
            for (auto id : event.initializes) if (state[id].availability == 1) state[id].availability = 2;
            for (auto id : event.defines) {
                for (auto& [alias, value] : state) if (value.aliases.count(id)) value.stale = true;
                state[id] = Binding{2, false, {}};
            }
            for (auto [alias, origin] : event.aliases) {
                state[alias].aliases.insert(origin);
                state[alias].aliases.insert(state[origin].aliases.begin(), state[origin].aliases.end());
                state[alias].stale |= state[origin].availability != 2 || state[origin].stale;
            }
        }
        return state;
    };
    while (!queue.empty()) {
        auto id = queue.front(); queue.pop_front(); queued[id] = false;
        auto out = transfer(*inputs[id], blocks[id], false);
        for (auto successor : blocks[id].successors) {
            if (!inputs[successor]) {inputs[successor] = out; enqueue(successor); continue;}
            auto merged = *inputs[successor];
            std::set<Memory::Identity> ids;
            for (auto& [binding, state] : merged) ids.insert(binding);
            for (auto& [binding, state] : out) ids.insert(binding);
            for (auto binding : ids) {
                auto& a = merged[binding]; auto b = out.count(binding) ? out.at(binding) : Binding{};
                a.availability |= b.availability; a.stale |= b.stale;
                a.aliases.insert(b.aliases.begin(), b.aliases.end());
            }
            if (merged != *inputs[successor]) {inputs[successor] = std::move(merged); enqueue(successor);}
        }
    }
    const auto before = errors.size();
    for (const auto& block : blocks) if (inputs[block.id]) (void)transfer(*inputs[block.id], block, true);
    // With no capability operations this function cannot create or resolve a
    // capability-derived pointer. Ownership and region verification still run;
    // propagating unknown tokens for every ordinary call proves nothing here.
    const bool has_references = std::any_of(func.instructions.begin(), func.instructions.end(), [](const LIR_Inst& inst) {
        return inst.op == LIR_Op::RefCreate || inst.op == LIR_Op::RefResolve ||
               inst.op == LIR_Op::RefMove || inst.op == LIR_Op::RefRelease;
    });
    if (!has_references) return errors.size() == before;
    // Capabilities are dynamic tokens, but their explicit LIR lifetimes are
    // verifiable without consulting the AST. Unknown tokens retain runtime checks.
    struct References {
        std::map<Reg, std::map<size_t, unsigned>> handles, pointers;
        std::vector<uint32_t> regions;
        std::map<size_t, unsigned> permissions; // 1: read-only, 2: writable, 4: dynamic
        std::set<Reg> return_promotions;
        bool operator==(const References&) const = default;
    };
    std::map<size_t, uint32_t> token_regions;
    std::vector<std::optional<References>> reference_inputs(blocks.size());
    reference_inputs[0] = References{};
    for (Reg p = 0; p < func.param_count; ++p) reference_inputs[0]->handles[p][0] = 2;
    auto reference_operands = [](const LIR_Inst& inst) {
        std::vector<Reg> operands;
        switch (inst.op) {
            case LIR_Op::Nop: case LIR_Op::Label: case LIR_Op::Jump:
            case LIR_Op::RegionEnter: case LIR_Op::RegionExit: case LIR_Op::LoadConst: break;
            case LIR_Op::FrameGetField: case LIR_Op::Cast:
            case LIR_Op::RegionMove: case LIR_Op::RefCreate: case LIR_Op::RefResolve:
            case LIR_Op::RefRelease: case LIR_Op::RefMove: case LIR_Op::OwnershipConsume:
                operands = {inst.a}; break;
            case LIR_Op::FrameSetField: operands = {inst.dst, inst.b}; break;
            case LIR_Op::ListSet: case LIR_Op::DictSet: case LIR_Op::TupleSet:
                operands = {inst.dst, inst.a, inst.b}; break;
            default: operands = {inst.a, inst.b}; break;
        }
        operands.insert(operands.end(), inst.call_args.begin(), inst.call_args.end());
        return operands;
    };
    auto reference_transfer = [&](References state, const AnalysisBlock& block, bool diagnose) {
        auto fail = [&](size_t i, const std::string& message) {
            if (diagnose) errors.push_back("Function " + func.name + " instruction " + std::to_string(i) + ": " + message);
        };
        auto valid = [&](const std::map<size_t, unsigned>& tokens, size_t i) {
            for (auto [token, live] : tokens) if (live != 2) fail(i, "reference is invalid on a reachable path");
        };
        for (size_t i = block.start_inst_idx; i < block.end_inst_idx; ++i) {
            const auto& inst = func.instructions[i];
            if (!Memory::valid_reference_instruction(inst)) fail(i, "malformed reference/ownership instruction");
            // Frame field offsets and region identities are immediates, not
            // register uses. Store operations use dst as an input object.
            auto operands = reference_operands(inst);
            for (auto r : operands) if (state.pointers.count(r) && !(inst.isReturn() && state.return_promotions.count(r))) valid(state.pointers[r], i);
            auto source = state.handles.count(inst.a) ? state.handles.at(inst.a) : std::map<size_t,unsigned>{};
            auto source_pointers = state.pointers.count(inst.a) ? state.pointers.at(inst.a) : std::map<size_t,unsigned>{};
            if (inst.dst != UINT32_MAX && inst.result_type != Type::Void && !inst.isReturn()) {state.handles.erase(inst.dst); state.pointers.erase(inst.dst); state.return_promotions.erase(inst.dst);}
            if (inst.op == LIR_Op::RegionMove && inst.imm == 0) state.return_promotions.insert(inst.a);
            else if (inst.op == LIR_Op::RegionEnter) state.regions.push_back(static_cast<uint32_t>(inst.imm));
            else if (inst.op == LIR_Op::RegionExit) {
                for (auto* values : {&state.handles, &state.pointers}) for (auto& [reg, tokens] : *values)
                    for (auto& [token, live] : tokens) if (token && token_regions[token] == static_cast<uint32_t>(inst.imm)) live = 4;
                if (!state.regions.empty()) state.regions.pop_back();
            } else if (inst.op == LIR_Op::RefCreate) {
                const auto token = i + 1;
                token_regions[token] = state.regions.empty() ? 0 : state.regions.back();
                state.handles[inst.dst] = {{token, 2}};
                state.permissions[token] = (inst.imm & Memory::ReferenceWritable) ? 2 : 1;
            } else if (inst.op == LIR_Op::RefResolve || inst.op == LIR_Op::RefRelease || inst.op == LIR_Op::RefMove) {
                if (source.empty()) fail(i, "reference operand has no capability definition");
                valid(source, i);
                if (inst.op == LIR_Op::RefResolve) {
                    for (auto [token, live] : source) if (token && (inst.imm & Memory::ReferenceWritable) && (state.permissions[token] & 1))
                        fail(i, "write resolution of a read-only reference");
                    state.pointers[inst.dst] = source;
                } else {
                    for (auto [token, live] : source) for (auto* values : {&state.handles, &state.pointers})
                        for (auto& [reg, tokens] : *values) if (tokens.count(token)) tokens[token] = 4;
                    if (inst.op == LIR_Op::RefMove) {
                        const auto token = i + 1;
                        token_regions[token] = static_cast<uint32_t>(inst.imm & Memory::ReferenceRegionMask); state.handles[inst.dst] = {{token, 2}};
                        unsigned permission = 0;
                        for (auto [origin, live] : source) permission |= origin ? state.permissions[origin] : 4;
                        state.permissions[token] = permission;
                    }
                }
            } else if (inst.op == LIR_Op::Mov) {
                if (!source.empty()) state.handles[inst.dst] = source;
                if (!source_pointers.empty()) state.pointers[inst.dst] = source_pointers;
            } else if (inst.op == LIR_Op::Call || inst.op == LIR_Op::CallIndirect || inst.op == LIR_Op::CallBuiltin || inst.op == LIR_Op::LoadGlobal) {
                if (inst.dst != UINT32_MAX) state.handles[inst.dst] = {{0, 2}};
            }
        }
        return state;
    };
    // This is verifier-state liveness, not instruction or check elimination.
    // Every operand read remains an obligation even when its result is unused.
    std::vector<std::set<Reg>> reference_live(blocks.size());
    bool live_changed;
    do {
        live_changed = false;
        for (auto block = blocks.rbegin(); block != blocks.rend(); ++block) {
            std::set<Reg> live;
            for (auto successor : block->successors)
                live.insert(reference_live[successor].begin(), reference_live[successor].end());
            for (size_t index = block->end_inst_idx; index > block->start_inst_idx;) {
                const auto& inst = func.instructions[--index];
                if (inst.dst != UINT32_MAX && inst.result_type != Type::Void && !inst.isReturn()) live.erase(inst.dst);
                for (auto reg : reference_operands(inst)) if (reg != UINT32_MAX) live.insert(reg);
            }
            if (live != reference_live[block->id]) {reference_live[block->id] = std::move(live); live_changed = true;}
        }
    } while (live_changed);
    auto project_references = [](const References& state, const std::set<Reg>& live) {
        References result; result.regions = state.regions;
        std::set<size_t> tokens;
        auto retain = [&](auto& target, const auto& values) {
            for (const auto& [reg, provenance] : values) if (live.count(reg)) {
                target.emplace(reg, provenance);
                for (auto [token, validity] : provenance) tokens.insert(token);
            }
        };
        retain(result.handles, state.handles); retain(result.pointers, state.pointers);
        for (auto token : tokens) if (auto permission = state.permissions.find(token); permission != state.permissions.end())
            result.permissions.emplace(*permission);
        for (auto reg : state.return_promotions) if (live.count(reg)) result.return_promotions.insert(reg);
        return result;
    };
    queue = {0}; queued.assign(blocks.size(), false); queued[0] = true;
    while (!queue.empty()) {
        const auto id = queue.front(); queue.pop_front(); queued[id] = false;
        auto out = reference_transfer(*reference_inputs[id], blocks[id], false);
        for (auto successor : blocks[id].successors) {
            auto edge = project_references(out, reference_live[successor]);
            if (!reference_inputs[successor]) {reference_inputs[successor] = edge; enqueue(successor); continue;}
            auto merged = *reference_inputs[successor];
            auto merge_values = [](auto& target, const auto& incoming) {
                std::set<Reg> registers;
                for (const auto& [reg, tokens] : target) registers.insert(reg);
                for (const auto& [reg, tokens] : incoming) registers.insert(reg);
                for (auto reg : registers) {
                    const bool missing_left = !target.count(reg), missing_right = !incoming.count(reg);
                    if (!missing_right) for (auto [token, live] : incoming.at(reg)) target[reg][token] |= live | (missing_left ? 1 : 0);
                    if (missing_right) for (auto& [token, live] : target[reg]) live |= 1;
                }
            };
            merge_values(merged.handles, edge.handles); merge_values(merged.pointers, edge.pointers);
            for (auto [token, permission] : edge.permissions) merged.permissions[token] |= permission;
            for (auto it = merged.return_promotions.begin(); it != merged.return_promotions.end();) {
                if (!edge.return_promotions.count(*it)) it = merged.return_promotions.erase(it); else ++it;
            }
            if (merged != *reference_inputs[successor]) {reference_inputs[successor] = std::move(merged); enqueue(successor);}
        }
    }
    for (const auto& block : blocks) if (reference_inputs[block.id]) (void)reference_transfer(*reference_inputs[block.id], block, true);
    return errors.size() == before;
}

// Region stacks are invocation-local. Every reachable predecessor must agree
// on the complete active stack; lexical depth alone cannot establish identity.
bool Verifier::verify_memory_regions(const LIR_Function& func, std::vector<std::string>& errors) {
    if (!verify_control_flow(func, errors)) return false;
    CFGAnalysis cfg(func);
    cfg.analyze();
    const auto& blocks = cfg.get_blocks();
    if (blocks.empty()) return true;
    using Stack = std::vector<uint32_t>;
    std::vector<std::optional<Stack>> entry(blocks.size());
    entry[0] = Stack{};
    std::deque<uint32_t> pending{0};
    bool valid = true;
    auto fail = [&](size_t index, const std::string& message) {
        errors.push_back("Function " + func.name + " instruction " + std::to_string(index) + ": " + message);
        valid = false;
    };
    while (!pending.empty()) {
        auto id = pending.front(); pending.pop_front();
        auto stack = *entry[id];
        const auto& block = blocks[id];
        for (size_t i = block.start_inst_idx; i < block.end_inst_idx; ++i) {
            const auto& inst = func.instructions[i];
            const auto region = static_cast<uint32_t>(inst.imm & Memory::ReferenceRegionMask);
            if ((inst.op == LIR_Op::RegionEnter || inst.op == LIR_Op::RegionExit || inst.op == LIR_Op::RegionMove) && (inst.imm & Memory::ReferenceMoveNullable))
                { fail(i, "Region identity exceeds canonical 31-bit range"); return false; }
            if (inst.op == LIR_Op::RegionEnter) {
                if (region == 0 || std::find(stack.begin(), stack.end(), region) != stack.end())
                    fail(i, "region entry has invalid or already active identity");
                stack.push_back(region);
            } else if (inst.op == LIR_Op::RegionExit) {
                if (stack.empty() || stack.back() != region) {
                    fail(i, "region exit does not match active region");
                    return false;
                }
                stack.pop_back();
            } else if (inst.op == LIR_Op::RegionMove || inst.op == LIR_Op::RefMove) {
                if (region != 0 && std::find(stack.begin(), stack.end(), region) == stack.end())
                    fail(i, "promotion target is not an active ancestor region");
            } else if (inst.isReturn() && !stack.empty()) {
                fail(i, "return leaves regions without cleanup");
            }
        }
        if (block.successors.empty() && !stack.empty())
            fail(block.end_inst_idx - 1, "exit leaves regions without cleanup");
        for (auto successor : block.successors) {
            if (!entry[successor]) {
                entry[successor] = stack;
                pending.push_back(successor);
            } else if (*entry[successor] != stack) {
                fail(block.end_inst_idx - 1, "control-flow predecessors disagree on active regions");
            }
        }
    }
    return valid;
}

bool Verifier::verify_instruction(const LIR_Inst& inst, const LIR_Function& func, std::vector<std::string>& errors) {
    if (!Memory::valid_reference_instruction(inst)) {
        errors.push_back("Malformed memory capability instruction: " + lir_op_to_string(inst.op));
        return false;
    }
    if (!inst.call_arg_ownership.empty() && inst.call_arg_ownership.size() != inst.call_args.size()) {
        errors.push_back("Invalid call ownership effect count"); return false;
    }
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
    bool success = true;
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.op == LIR_Op::Label && inst.imm != i) {
            errors.push_back("Function " + func.name + " label identity differs from its canonical instruction offset");
            success = false;
        }
        if ((inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) &&
            inst.imm >= func.instructions.size()) {
            errors.push_back("Function " + func.name + " jumps outside its instruction stream");
            success = false;
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

bool Verifier::verify_bit_vector_semantics(const LIR_Function& func, std::vector<std::string>& errors) {
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.op == LIR_Op::Shl || inst.op == LIR_Op::Shr) {
            if (inst.imm >= 64 && inst.b == UINT32_MAX) {
                errors.push_back("[warning] Function " + func.name + " instruction " + std::to_string(i) +
                                 " (" + lir_op_to_string(inst.op) +
                                 ") scalar bitwise shift count " + std::to_string(inst.imm) +
                                 " wraps or exceeds 64-bit width");
            }
        }
    }
    return true;
}

bool Verifier::verify_float_arithmetic_semantics(const LIR_Function& func, std::vector<std::string>& errors) {
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.op == LIR_Op::Div) {
            if (inst.type_a == Type::F64 || inst.type_b == Type::F64) {
                if (inst.const_val == 0 && inst.b == UINT32_MAX) {
                    errors.push_back("[warning] Function " + func.name + " instruction " + std::to_string(i) +
                                     " (" + lir_op_to_string(inst.op) +
                                     ") float division by literal zero creates IEEE infinity or NaN");
                }
            }
        }
    }
    return true;
}

bool Verifier::verify_collections_and_strings(const LIR_Function& func, std::vector<std::string>& errors) {
    bool ok = true;
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.op == LIR_Op::ListIndex || inst.op == LIR_Op::StringIndex || inst.op == LIR_Op::TupleGet) {
            if (inst.a == UINT32_MAX) {
                errors.push_back("Function " + func.name + " instruction " + std::to_string(i) +
                                 " (" + lir_op_to_string(inst.op) +
                                 ") missing collection object register");
                ok = false;
            }
        } else if (inst.op == LIR_Op::CapabilityAcquire) {
            uint32_t begin = inst.b;
            uint32_t end = inst.imm;
            if (end <= begin) {
                errors.push_back("Function " + func.name + " instruction " + std::to_string(i) +
                                 " (" + lir_op_to_string(inst.op) +
                                 ") invalid capability slice range [" +
                                 std::to_string(begin) + ".." + std::to_string(end) + ")");
                ok = false;
            }
        }
    }
    return ok;
}

bool Verifier::verify_enums_unions_and_contracts(const LIR_Function& func, std::vector<std::string>& errors) {
    bool ok = true;
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.op == LIR_Op::MakeEnum) {
            if (inst.dst == UINT32_MAX) {
                errors.push_back("Function " + func.name + " instruction " + std::to_string(i) +
                                 " (MakeEnum) missing destination register");
                ok = false;
            }
        } else if (inst.op == LIR_Op::GetTag || inst.op == LIR_Op::GetPayload) {
            if (inst.a == UINT32_MAX) {
                errors.push_back("Function " + func.name + " instruction " + std::to_string(i) +
                                 " (" + lir_op_to_string(inst.op) +
                                 ") missing enum/union object register");
                ok = false;
            }
        }
    }
    return ok;
}

} // namespace LIR
} // namespace LM
