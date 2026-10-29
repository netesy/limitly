#include "../type_checker.hh"
#include "../../backend/vm/register.hh"
#include "../../lir/builtin_functions.hh"
#include "../../lir/function_registry.hh"
#include "../../lir/functions.hh"
#include "../../lir/generator.hh"
#include "../../lir/lir.hh"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <string>
#include <vector>

namespace LM {
namespace Frontend {

// Stage-0 VM fallback for staged bodies outside the AST folder's subset
// (docs/staged.md, docs/roadmaps.md build step 4).
//
// The AST folder stays the canonical evaluator: it is the only one that can carry the type
// domain (`: type` parameters, type constructors, structural types), and it is what the rest
// of the staged tests exercise. This file adds the second executor the roadmap asks for, used
// only when a body contains a construct the folder does not implement (loops, local mutation).
// Such a body is type-checked, lowered to one LIR function, and run on the embedded Register
// VM. The result is folded back into a constant exactly like a folder result, so from the
// program's point of view the two executors are indistinguishable.

namespace {

using LM::Backend::RegisterValue;

// Statements the AST folder implements. Anything else needs a real execution engine.
bool foldable_statement(const std::shared_ptr<LM::Frontend::AST::Statement>& stmt) {
    if (!stmt) return true;
    if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
        for (const auto& inner : block->statements) {
            if (!foldable_statement(inner)) return false;
        }
        return true;
    }
    if (auto if_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt)) {
        return foldable_statement(if_stmt->thenBranch) &&
               foldable_statement(if_stmt->elseBranch);
    }
    return std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt) != nullptr ||
           std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt) != nullptr;
}

// Builtins whose result depends on the environment or on the order of execution. Stage 0 has
// to be a pure function of its inputs, so these stay out of reach even though they are part of
// the language runtime.
bool observable_builtin(const std::string& name) {
    return name == "print" || name == "input" || name == "time" || name == "clock" ||
           name == "random" || name == "sleep";
}

// Instructions stage-0 may execute.
//
// This is deliberately an allowlist. Stage 0 runs inside the compiler, so the safe default for
// any opcode is "refused": a new LIR instruction (or one added to a backend later) is denied
// compile-time access until someone classifies it here, and forgetting is a compile error
// rather than a sandbox escape. The entries are the pure, deterministic subset -- scalar and
// decimal arithmetic, comparison, control flow, conversions, string building, fallible values,
// enums, aggregates, and the region bookkeeping every lexical scope emits.
//
// Notably refused, and why: dynamic linking, foreign calls, callbacks, raw memory/pointer and
// marshal/buffer operations, resources (they cross into the host); the whole concurrency and
// scheduler surface, atomics, tick counts and delays (stage 0 must be a pure function of its
// inputs); module globals and imports (no module has been initialised at fold time); frames,
// traits and their methods (no runtime function has been lowered yet, so a call would fail
// inside the VM with a message about a missing symbol rather than here); CallIndirect (the
// target is a value, so the call fence below cannot classify it); and VaStart/VaArg/VaEnd,
// effects and capability references (no meaning without a surrounding runtime).
bool stage0_op_allowed(LIR::LIR_Op op) {
    switch (op) {
        // Scalar arithmetic and logic
        case LIR::LIR_Op::Mov:
        case LIR::LIR_Op::LoadConst:
        case LIR::LIR_Op::Add:
        case LIR::LIR_Op::Sub:
        case LIR::LIR_Op::Mul:
        case LIR::LIR_Op::Div:
        case LIR::LIR_Op::Mod:
        case LIR::LIR_Op::Neg:
        case LIR::LIR_Op::And:
        case LIR::LIR_Op::Or:
        case LIR::LIR_Op::Xor:
        case LIR::LIR_Op::Shl:
        case LIR::LIR_Op::Shr:
        case LIR::LIR_Op::Copy:
        // Unchecked integer variants: same values as the checked forms, minus the trap
        case LIR::LIR_Op::IAdd_Unchecked:
        case LIR::LIR_Op::IXor_Unchecked:
        case LIR::LIR_Op::IAnd_Unchecked:
        case LIR::LIR_Op::IOr_Unchecked:
        // Fixed-point decimal arithmetic
        case LIR::LIR_Op::DecAdd:
        case LIR::LIR_Op::DecSub:
        case LIR::LIR_Op::DecMul:
        case LIR::LIR_Op::DecDiv:
        case LIR::LIR_Op::DecMod:
        case LIR::LIR_Op::DecNeg:
        case LIR::LIR_Op::DecRescale:
        // Comparison
        case LIR::LIR_Op::CmpEQ:
        case LIR::LIR_Op::CmpNEQ:
        case LIR::LIR_Op::CmpLT:
        case LIR::LIR_Op::CmpLE:
        case LIR::LIR_Op::CmpGT:
        case LIR::LIR_Op::CmpGE:
        // Control flow
        case LIR::LIR_Op::Jump:
        case LIR::LIR_Op::JumpIf:
        case LIR::LIR_Op::JumpIfFalse:
        case LIR::LIR_Op::Label:
        case LIR::LIR_Op::Return:
        case LIR::LIR_Op::Ret:
        case LIR::LIR_Op::Nop:
        // Conversions and string building -- deterministic, no external state
        case LIR::LIR_Op::Cast:
        case LIR::LIR_Op::ToString:
        case LIR::LIR_Op::STR_CONCAT:
        case LIR::LIR_Op::STR_FORMAT:
        case LIR::LIR_Op::StringIndex:
        // Fallible values
        case LIR::LIR_Op::ConstructError:
        case LIR::LIR_Op::ConstructOk:
        case LIR::LIR_Op::IsError:
        case LIR::LIR_Op::Unwrap:
        case LIR::LIR_Op::UnwrapOr:
        // Enums
        case LIR::LIR_Op::MakeEnum:
        case LIR::LIR_Op::GetTag:
        case LIR::LIR_Op::GetPayload:
        // Aggregates. Pure, but they allocate on the VM heap, which is why the instruction
        // budget below is paired with a retained-output bound.
        case LIR::LIR_Op::ListCreate:
        case LIR::LIR_Op::ListAppend:
        case LIR::LIR_Op::ListIndex:
        case LIR::LIR_Op::ListSet:
        case LIR::LIR_Op::ListLen:
        case LIR::LIR_Op::DictCreate:
        case LIR::LIR_Op::DictSet:
        case LIR::LIR_Op::DictGet:
        case LIR::LIR_Op::DictHas:
        case LIR::LIR_Op::DictLen:
        case LIR::LIR_Op::DictItems:
        case LIR::LIR_Op::TupleCreate:
        case LIR::LIR_Op::TupleGet:
        case LIR::LIR_Op::TupleSet:
        case LIR::LIR_Op::TupleLen:
        // Region bookkeeping. enter_scope()/exit_scope() emit these for every lexical block,
        // so refusing them would refuse any function at all.
        case LIR::LIR_Op::RegionEnter:
        case LIR::LIR_Op::RegionExit:
        case LIR::LIR_Op::RegionMove:
        // Named calls. Allowed as an opcode, refused or accepted by stage0_call_hostile()
        // based on the target: recursion and intrinsics are fine, anything else is not.
        case LIR::LIR_Op::Call:
        case LIR::LIR_Op::CallVoid:
        case LIR::LIR_Op::CallBuiltin:
        case LIR::LIR_Op::CallVariadic:
            return true;
        default:
            return false;
    }
}

// A call is allowed when it lands back inside the staged fn (recursion) or when it is a
// compiler intrinsic (`_builtin_*`) or a deterministic runtime builtin. A call to a sibling
// function of the program is refused: that function is not part of this compile-time unit, so
// the VM has nothing to dispatch to, and reaching it would be host access by another name.
// Dispatch also crosses into precompiled native shared libraries for any exported symbol, so
// this gate cannot be relaxed just because the opcode itself looks innocent.
bool stage0_call_hostile(const LIR::LIR_Inst& inst, const std::string& self) {
    switch (inst.op) {
        case LIR::LIR_Op::Call:
        case LIR::LIR_Op::CallVoid:
        case LIR::LIR_Op::CallBuiltin:
        case LIR::LIR_Op::CallVariadic:
        case LIR::LIR_Op::CallIndirect:
            break;
        default:
            return false;
    }
    if (inst.op == LIR::LIR_Op::CallIndirect) return true;
    if (inst.func_name == self) return false;
    if (inst.func_name.rfind("_builtin_", 0) == 0) return false;
    if (LIR::BuiltinUtils::isBuiltinFunction(inst.func_name)) {
        return observable_builtin(inst.func_name);
    }
    return true;
}

} // namespace

bool TypeChecker::staged_body_needs_vm(
        const std::shared_ptr<LM::Frontend::AST::Statement>& body) {
    // Parity switch. When enabled, every staged body is routed through the VM, including the ones
    // the AST folder implements, so running the suite twice (once normally, once with
    // LYMAR_STAGE0_FORCE_VM=1) turns every existing staged test into a differential test of the
    // two executors. Divergence between them is a miscompile, and this is the cheap way to find
    // it; it is also the harness that makes removing the folder later a safe deletion.
    // "0" and empty mean off, so a shell that exports the variable cannot silently force a run.
    static const bool force_vm = []() {
        const char* value = std::getenv("LYMAR_STAGE0_FORCE_VM");
        return value != nullptr && *value != '\0' && std::strcmp(value, "0") != 0;
    }();
    if (force_vm) return true;
    return !foldable_statement(body);
}

bool TypeChecker::check_staged_body_for_vm(
        const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& fn) {
    if (!fn || !fn->body) {
        add_error("stage 0 VM: staged fn '" + (fn ? fn->name : std::string()) + "' has no body",
                  fn ? fn->line : 0);
        return false;
    }
    // Parameters keep the declared types from the signature already collected for runtime
    // calls, so the body sees exactly the types a normal function body would.
    std::vector<TypePtr> param_types;
    auto sig_it = function_signatures.find(fn->name);
    if (sig_it != function_signatures.end()) param_types = sig_it->second.param_types;

    const size_t errors_before = errors.size();
    const bool saved_staged_body = checking_staged_body_;
    auto saved_function = current_function;
    auto saved_return_type = current_return_type;

    checking_staged_body_ = true;
    current_function = fn;
    current_return_type = fn->inferred_type;
    enter_scope();
    for (size_t i = 0; i < fn->params.size(); ++i) {
        TypePtr type = i < param_types.size() ? param_types[i] : type_system.ANY_TYPE;
        declare_variable(fn->params[i].first, type);
    }
    for (size_t i = 0; i < fn->optionalParams.size(); ++i) {
        size_t index = fn->params.size() + i;
        TypePtr type = index < param_types.size() ? param_types[index] : type_system.ANY_TYPE;
        declare_variable(fn->optionalParams[i].first, type);
    }

    check_statement(fn->body);

    exit_scope();
    current_function = saved_function;
    current_return_type = saved_return_type;
    checking_staged_body_ = saved_staged_body;

    // Diagnostics from the body are genuine: the body only gets here because it is the one
    // being compiled. Report the failure as "not foldable" rather than letting lowering run
    // over nodes that carry no inferred type.
    return errors.size() == errors_before;
}

bool TypeChecker::stage0_prepare_fn(
        const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& fn) {
    if (!fn) return false;
    const std::string& name = fn->name;

    // Already prepared by an enclosing fold (or earlier in this one): mutual recursion between
    // two staged fns reaches here a second time, and re-lowering would collide with the entry
    // that is already registered.
    if (std::find(stage0_registered_fns_.begin(), stage0_registered_fns_.end(), name) !=
        stage0_registered_fns_.end()) {
        return true;
    }

    if (!check_staged_body_for_vm(fn)) return false;

    auto& registry = LIR::FunctionRegistry::getInstance();
    if (registry.hasFunction(name)) {
        add_error("stage 0 VM: name '" + name + "' is already a runtime function", fn->line);
        return false;
    }

    // Lowering registers the function under its source name in both registries. Neither registry
    // holds a staged fn otherwise, so a call inside the body -- to this function or to another
    // staged fn -- resolves through the entry prepared here, and stage0_release_fns() drops every
    // one of them once the compile-time evaluation is over. Nothing compiled here can reach code
    // generation, the cache, or an export list.
    LIR::LIR_Function* lowered = nullptr;
    try {
        LIR::Generator generator;
        // generate_program() installs the type system for a whole-program pass. Lowering one
        // staged fn happens inside the type checker instead, so hand the generator the checker's
        // own live type system: the decimal and enum paths call type_system_->getType(...) with
        // no null guard, and language types would otherwise degrade to ABI defaults.
        // Non-owning on purpose -- the TypeChecker holds the object for the whole compilation.
        generator.set_type_system(std::shared_ptr<TypeSystem>(&type_system, [](TypeSystem*) {}));
        generator.generate_function(*fn);
        lowered = registry.getFunction(name);
    } catch (const std::exception& e) {
        add_error("stage 0 VM: could not lower staged fn '" + name + "': " + e.what(), fn->line);
        return false;
    }
    if (!lowered) {
        add_error("stage 0 VM: staged fn '" + name + "' produced no code", fn->line);
        return false;
    }
    stage0_registered_fns_.push_back(name);

    // The fence is static, before a single instruction runs: a body that would leave the
    // language is rejected as a compile error rather than as a runtime failure halfway through a
    // fold. `lowered` points into the registry entry, so anything read out of the instruction
    // stream is copied before the entry can be dropped.
    for (const auto& inst : lowered->instructions) {
        if (!stage0_op_allowed(inst.op)) {
            const std::string what = LIR::lir_op_to_string(inst.op);
            add_error("stage 0 VM: '" + what + "' is not available at compile time -- stage 0 "
                      "runs pure, deterministic instructions only", fn->line);
            return false;
        }
        if (stage0_call_hostile(inst, name)) {
            // Not an intrinsic and not this function: allow it only when the target is another
            // staged fn, which is prepared here so the VM can resolve the call. Anything else
            // (a runtime sibling function, an indirect target, the host) stays refused.
            const std::string callee = inst.func_name;
            auto it = staged_functions_.find(callee);
            if (it == staged_functions_.end()) {
                add_error("stage 0 VM: staged fn '" + name + "' cannot call '" + callee +
                          "' at compile time", fn->line);
                return false;
            }
            if (!stage0_prepare_fn(it->second)) return false;
        }
    }
    return true;
}

void TypeChecker::stage0_release_fns() {
    if (stage0_registered_fns_.empty()) return;
    auto& manager = LIR::LIRFunctionManager::getInstance();
    auto& registry = LIR::FunctionRegistry::getInstance();
    for (const auto& prepared : stage0_registered_fns_) {
        registry.erase(prepared);
        manager.erase(prepared);
    }
    stage0_registered_fns_.clear();
}

bool TypeChecker::run_staged_fn_on_vm(
        const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& fn,
        long long& out_int, double& out_double, bool& out_is_int) {
    if (!fn) return false;
    const std::string& name = fn->name;
    if (!stage0_charge(fn->line)) return false;

    // Registers 0..n-1 hold the declared parameters only. Optional parameters land in the slots
    // after them, and their defaults are expressions the VM has no environment for, so a body
    // with defaults would read uninitialised registers and fold a wrong constant. Refusing is
    // the only safe answer until defaults are evaluated into the argument list.
    if (!fn->optionalParams.empty()) {
        add_error("stage 0 VM: staged fn '" + name +
                  "' with default parameter values is not supported at compile time", fn->line);
        return false;
    }

    // The fold result is a numeric literal, so only the arguments that have a boxed VM
    // representation can cross: numbers, bools and unit-variant enums. They are already bound by
    // the call site; the environment is the transfer format because that is what both executors
    // share.
    std::vector<RegisterValue> args;
    args.reserve(fn->params.size());
    for (const auto& param : fn->params) {
        auto int_it = constant_ints.find(param.first);
        if (int_it != constant_ints.end()) {
            args.push_back(make_i64(int_it->second));
            continue;
        }
        auto double_it = constant_doubles.find(param.first);
        if (double_it != constant_doubles.end()) {
            args.push_back(make_float(double_it->second));
            continue;
        }
        // An enum argument is always a unit variant -- try_stage0_enum_value refuses any variant
        // that carries associated values, so there is never a payload to move. Rebuild the boxed
        // representation MakeEnum produces (the 3-field frame [tag, payload, variant_name]) so a
        // body's `p == TargetPlatform.Linux` lowers to GetTag(p) against GetTag of the constant
        // and compares the same integer tag. Passing the bare tag as an int would compare unequal
        // against that boxed enum and silently fold a wrong constant. field 1 (payload) and field
        // 2 (variant name) stay nil: unit-variant equality reads the tag alone -- the generator
        // skips the payload compare when no variant carries one (generator/expressions.cpp) -- as
        // does match, and a nil name avoids a heap string the frame reclaim never frees (reclaim
        // frees a frame's field array, never its children). The malloc'd frame is bound to its
        // register, registered as a native allocation by call_interpreted, and reclaimed by the
        // RegisterVM destructor like any other boxed argument.
        if (auto enum_it = constant_enums_.find(param.first); enum_it != constant_enums_.end()) {
            void* enum_obj = lm_frame_alloc("__lir_internal_enum__", 3);
            lm_frame_set_field(enum_obj, 0, make_i64(static_cast<int64_t>(enum_it->second.second)));
            lm_frame_set_field(enum_obj, 1, VAL_NIL);
            lm_frame_set_field(enum_obj, 2, VAL_NIL);
            args.push_back(BOX_PTR(enum_obj));
            continue;
        }
        // A type value has no LIR representation at all, so it cannot be handed to the VM. The
        // folder still evaluates it, which is why routing a type-shaped body there is required.
        if (constant_types_.count(param.first)) {
            add_error("stage 0 VM: staged fn '" + name + "' parameter '" + param.first +
                      "' is a type value, which has no LIR representation", fn->line);
            return false;
        }
        add_error("stage 0 VM: staged fn '" + name + "' parameter '" + param.first +
                  "' has no numeric compile-time value", fn->line);
        return false;
    }

    if (!stage0_prepare_fn(fn)) {
        stage0_release_fns();
        return false;
    }
    LIR::LIR_Function* lowered = LIR::FunctionRegistry::getInstance().getFunction(name);
    if (!lowered) {
        stage0_release_fns();
        add_error("stage 0 VM: staged fn '" + name + "' is not available to run", fn->line);
        return false;
    }

    // The depth is about nested *compile-time* entries, which the type domain can reach: a call
    // inside the VM itself never comes back here. Entries therefore stay registered until the
    // outermost evaluation finishes, so a callee prepared for one body is still resolvable while
    // another body calls it.
    ++stage0_vm_depth_;
    RegisterValue result = VAL_NIL;
    bool ran = true;
    try {
        LM::Backend::VM::Register::RegisterVM vm;
        vm.set_instruction_budget(STAGE0_MAX_STEPS);
        result = vm.invoke_function(lowered, args);
    } catch (const std::exception& e) {
        ran = false;
        add_error("stage 0 VM: staged fn '" + name + "' failed: " + e.what(), fn->line);
    }
    --stage0_vm_depth_;
    if (stage0_vm_depth_ == 0) stage0_release_fns();
    if (!ran) return false;

    if (is_integer(result)) {
        out_int = as_i64(result);
        out_is_int = true;
        return true;
    }
    if (IS_BOOL(result)) {
        out_int = UNBOX_BOOL(result) ? 1 : 0;
        out_is_int = true;
        return true;
    }
    if (is_float(result)) {
        out_double = as_float(result);
        out_is_int = false;
        return true;
    }
    add_error("stage 0 VM: staged fn '" + name +
              "' must return a number or bool to be folded to a constant", fn->line);
    return false;
}

} // namespace Frontend
} // namespace LM
