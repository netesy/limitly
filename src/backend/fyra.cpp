// fyra.cpp - Fyra Backend Integration Implementation

#include "fyra.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <unordered_set>

namespace fs = std::filesystem;

namespace LM::Backend::Fyra {
namespace {

std::string to_fyra_type(LIR::Type type) {
    switch (type) {
        case LIR::Type::I32: return "i32";
        case LIR::Type::I64: return "i64";
        case LIR::Type::F64: return "f64";
        case LIR::Type::Bool: return "bool";
        case LIR::Type::Ptr: return "ptr";
        case LIR::Type::Void: return "void";
    }
    return "unknown";
}

std::string format_reg(LIR::Reg reg) {
    return "%r" + std::to_string(reg);
}

std::string format_const(const ValuePtr& value) {
    if (!value) {
        return "null";
    }
    return value->toString();
}


int expected_operand_count(LIR::LIR_Op op) {
    switch (op) {
        case LIR::LIR_Op::Nop:
        case LIR::LIR_Op::Return:
        case LIR::LIR_Op::VaEnd:
        case LIR::LIR_Op::Label:
            return 0;
        case LIR::LIR_Op::Add:
        case LIR::LIR_Op::Sub:
        case LIR::LIR_Op::Mul:
        case LIR::LIR_Op::Div:
        case LIR::LIR_Op::Mod:
        case LIR::LIR_Op::And:
        case LIR::LIR_Op::Or:
        case LIR::LIR_Op::Xor:
        case LIR::LIR_Op::CmpEQ:
        case LIR::LIR_Op::CmpNEQ:
        case LIR::LIR_Op::CmpLT:
        case LIR::LIR_Op::CmpLE:
        case LIR::LIR_Op::CmpGT:
        case LIR::LIR_Op::CmpGE:
        case LIR::LIR_Op::Load:
        case LIR::LIR_Op::Store:
        case LIR::LIR_Op::ListIndex:
        case LIR::LIR_Op::DictSet:
        case LIR::LIR_Op::DictGet:
        case LIR::LIR_Op::TupleGet:
        case LIR::LIR_Op::TupleSet:
            return 2;
        default:
            return 1;
    }
}

class FyraIRBuilder {
public:
    FyraIRBuilder(const LIR::LIR_Function& function, FyraCompiler::TranslationReport& report)
        : function_(function), report_(report) {}

    std::string build() {
        emit_header();
        emit_signature();
        emit_body();
        ir_ << "}\n";
        return ir_.str();
    }

private:
    const LIR::LIR_Function& function_;
    FyraCompiler::TranslationReport& report_;
    std::stringstream ir_;

    void emit_header() {
        ir_ << "// Fyra IR generated from LIR IRBuilder\n";
        ir_ << "// Function: " << function_.name << "\n";
        ir_ << "// Instructions: " << function_.instructions.size() << "\n";
        ir_ << "// Non-SSA lowering: preserves mutable registers and explicit control flow\n\n";
    }

    void emit_signature() {
        ir_ << "fn @" << function_.name << "(";
        for (uint32_t i = 0; i < function_.param_count; ++i) {
            if (i > 0) ir_ << ", ";
            LIR::Type ty = LIR::Type::I64;
            auto it = function_.register_types.find(i);
            if (it != function_.register_types.end()) ty = it->second;
            ir_ << format_reg(i) << " : " << to_fyra_type(ty);
        }
        ir_ << ") {\n";
    }

    void emit_body() {
        std::unordered_set<LIR::Imm> label_targets;
        for (const auto& inst : function_.instructions) {
            if (inst.op == LIR::LIR_Op::Jump || inst.op == LIR::LIR_Op::JumpIfFalse || inst.op == LIR::LIR_Op::JumpIf) {
                label_targets.insert(inst.imm);
            }
        }

        for (size_t index = 0; index < function_.instructions.size(); ++index) {
            if (label_targets.count(static_cast<LIR::Imm>(index)) > 0) {
                ir_ << "bb" << index << ":\n";
            }
            emit_instruction(function_.instructions[index], index);
        }
    }

    void emit_raw(const std::string& op, const LIR::LIR_Inst& inst, bool typed = true) {
        ir_ << "  ";
        if (inst.result_type != LIR::Type::Void) {
            ir_ << format_reg(inst.dst) << " = ";
        }
        ir_ << op;

        const int operand_count = expected_operand_count(inst.op);
        if (!inst.call_args.empty() || operand_count > 0) {
            ir_ << " ";
            bool first = true;
            auto append = [&](const std::string& t) {
                if (!first) ir_ << ", ";
                ir_ << t;
                first = false;
            };
            if (!inst.call_args.empty()) {
                for (auto arg : inst.call_args) append(format_reg(arg));
            } else {
                if (operand_count >= 1) append(format_reg(inst.a));
                if (operand_count >= 2) append(format_reg(inst.b));
            }
        }

        if (typed) {
            ir_ << " : " << to_fyra_type(inst.result_type);
        }
        if (!inst.comment.empty()) {
            ir_ << " ; " << inst.comment;
        }
        ir_ << "\n";
    }

    void emit_jump(const std::string& op, const LIR::LIR_Inst& inst, bool with_cond) {
        ir_ << "  " << op;
        if (with_cond) {
            ir_ << " " << format_reg(inst.a) << ", ";
        } else {
            ir_ << " ";
        }
        ir_ << "bb" << inst.imm << "\n";
    }

    void emit_call_like(const std::string& op, const LIR::LIR_Inst& inst) {
        ir_ << "  ";
        if (inst.result_type != LIR::Type::Void && inst.op != LIR::LIR_Op::CallVoid) {
            ir_ << format_reg(inst.dst) << " = ";
        }
        ir_ << op;
        if (!inst.func_name.empty()) {
            ir_ << " @" << inst.func_name;
        }
        ir_ << "(";
        for (size_t i = 0; i < inst.call_args.size(); ++i) {
            if (i > 0) ir_ << ", ";
            ir_ << format_reg(inst.call_args[i]);
        }
        ir_ << ") : " << to_fyra_type(inst.result_type) << "\n";
    }

    void emit_instruction(const LIR::LIR_Inst& inst, size_t index) {
        switch (inst.op) {
            case LIR::LIR_Op::Mov: emit_raw("mov", inst); break;
            case LIR::LIR_Op::LoadConst:
                ir_ << "  " << format_reg(inst.dst) << " = const " << format_const(inst.const_val)
                    << " : " << to_fyra_type(inst.result_type) << "\n";
                break;
            case LIR::LIR_Op::Add: emit_raw("add", inst); break;
            case LIR::LIR_Op::Sub: emit_raw("sub", inst); break;
            case LIR::LIR_Op::Mul: emit_raw("mul", inst); break;
            case LIR::LIR_Op::Div: emit_raw("div", inst); break;
            case LIR::LIR_Op::Mod: emit_raw("mod", inst); break;
            case LIR::LIR_Op::Neg: emit_raw("neg", inst); break;
            case LIR::LIR_Op::And: emit_raw("and", inst); break;
            case LIR::LIR_Op::Or: emit_raw("or", inst); break;
            case LIR::LIR_Op::Xor: emit_raw("xor", inst); break;
            case LIR::LIR_Op::CmpEQ: emit_raw("cmp.eq", inst); break;
            case LIR::LIR_Op::CmpNEQ: emit_raw("cmp.neq", inst); break;
            case LIR::LIR_Op::CmpLT: emit_raw("cmp.lt", inst); break;
            case LIR::LIR_Op::CmpLE: emit_raw("cmp.le", inst); break;
            case LIR::LIR_Op::CmpGT: emit_raw("cmp.gt", inst); break;
            case LIR::LIR_Op::CmpGE: emit_raw("cmp.ge", inst); break;
            case LIR::LIR_Op::Jump: emit_jump("br", inst, false); break;
            case LIR::LIR_Op::JumpIfFalse: emit_jump("br_if_false", inst, true); break;
            case LIR::LIR_Op::JumpIf: emit_jump("br_if", inst, true); break;
            case LIR::LIR_Op::Label: ir_ << "bb" << inst.imm << ":\n"; break;
            case LIR::LIR_Op::Call: emit_call_like("call", inst); break;
            case LIR::LIR_Op::CallVoid: emit_call_like("call", inst); break;
            case LIR::LIR_Op::CallIndirect: emit_call_like("call_indirect", inst); break;
            case LIR::LIR_Op::CallBuiltin: emit_call_like("call_builtin", inst); break;
            case LIR::LIR_Op::CallVariadic: emit_call_like("call_variadic", inst); break;
            case LIR::LIR_Op::Return: ir_ << "  ret\n"; break;
            case LIR::LIR_Op::FuncDef: emit_call_like("funcdef", inst); break;
            case LIR::LIR_Op::Param: emit_raw("param", inst); break;
            case LIR::LIR_Op::Ret:
                ir_ << "  ret " << format_reg(inst.a) << " : " << to_fyra_type(inst.type_a) << "\n";
                break;
            case LIR::LIR_Op::VaStart: emit_raw("vastart", inst); break;
            case LIR::LIR_Op::VaArg: emit_raw("vaarg", inst); break;
            case LIR::LIR_Op::VaEnd: emit_raw("vaend", inst, false); break;
            case LIR::LIR_Op::Copy: emit_raw("copy", inst); break;
            case LIR::LIR_Op::PrintInt: emit_raw("print_int", inst, false); break;
            case LIR::LIR_Op::PrintUint: emit_raw("print_uint", inst, false); break;
            case LIR::LIR_Op::PrintFloat: emit_raw("print_float", inst, false); break;
            case LIR::LIR_Op::PrintBool: emit_raw("print_bool", inst, false); break;
            case LIR::LIR_Op::PrintString: emit_raw("print_string", inst, false); break;
            case LIR::LIR_Op::Nop: ir_ << "  nop\n"; break;
            case LIR::LIR_Op::Load: emit_raw("load", inst); break;
            case LIR::LIR_Op::Store: emit_raw("store", inst, false); break;
            case LIR::LIR_Op::Cast: emit_raw("cast", inst); break;
            case LIR::LIR_Op::ToString: emit_raw("to_string", inst); break;
            case LIR::LIR_Op::STR_CONCAT: emit_raw("str_concat", inst); break;
            case LIR::LIR_Op::STR_FORMAT: emit_raw("str_format", inst); break;
            case LIR::LIR_Op::ConstructError: emit_raw("construct_error", inst); break;
            case LIR::LIR_Op::ConstructOk: emit_raw("construct_ok", inst); break;
            case LIR::LIR_Op::IsError: emit_raw("is_error", inst); break;
            case LIR::LIR_Op::Unwrap: emit_raw("unwrap", inst); break;
            case LIR::LIR_Op::UnwrapOr: emit_raw("unwrap_or", inst); break;
            case LIR::LIR_Op::AtomicLoad: emit_raw("atomic_load", inst); break;
            case LIR::LIR_Op::AtomicStore: emit_raw("atomic_store", inst, false); break;
            case LIR::LIR_Op::AtomicFetchAdd: emit_raw("atomic_fetch_add", inst); break;
            case LIR::LIR_Op::Await: emit_raw("await", inst); break;
            case LIR::LIR_Op::AsyncCall: emit_call_like("async_call", inst); break;
            case LIR::LIR_Op::TaskContextAlloc: emit_raw("task_context_alloc", inst); break;
            case LIR::LIR_Op::TaskContextInit: emit_raw("task_context_init", inst, false); break;
            case LIR::LIR_Op::TaskGetState: emit_raw("task_get_state", inst); break;
            case LIR::LIR_Op::TaskSetState: emit_raw("task_set_state", inst, false); break;
            case LIR::LIR_Op::TaskSetField: emit_raw("task_set_field", inst, false); break;
            case LIR::LIR_Op::TaskGetField: emit_raw("task_get_field", inst); break;
            case LIR::LIR_Op::ChannelAlloc: emit_raw("channel_alloc", inst); break;
            case LIR::LIR_Op::ChannelPush: emit_raw("channel_push", inst, false); break;
            case LIR::LIR_Op::ChannelPop: emit_raw("channel_pop", inst); break;
            case LIR::LIR_Op::ChannelHasData: emit_raw("channel_has_data", inst); break;
            case LIR::LIR_Op::ChannelSend: emit_raw("channel_send", inst); break;
            case LIR::LIR_Op::ChannelOffer: emit_raw("channel_offer", inst); break;
            case LIR::LIR_Op::ChannelRecv: emit_raw("channel_recv", inst); break;
            case LIR::LIR_Op::ChannelPoll: emit_raw("channel_poll", inst); break;
            case LIR::LIR_Op::ChannelClose: emit_raw("channel_close", inst, false); break;
            case LIR::LIR_Op::SchedulerInit: emit_raw("scheduler_init", inst); break;
            case LIR::LIR_Op::SchedulerRun: emit_raw("scheduler_run", inst); break;
            case LIR::LIR_Op::SchedulerTick: emit_raw("scheduler_tick", inst); break;
            case LIR::LIR_Op::SchedulerAddTask: emit_raw("scheduler_add_task", inst, false); break;
            case LIR::LIR_Op::GetTickCount: emit_raw("get_tick_count", inst); break;
            case LIR::LIR_Op::DelayUntil: emit_raw("delay_until", inst); break;
            case LIR::LIR_Op::ParallelInit: emit_raw("parallel_init", inst); break;
            case LIR::LIR_Op::ParallelSync: emit_raw("parallel_sync", inst); break;
            case LIR::LIR_Op::ListCreate: emit_raw("list_create", inst); break;
            case LIR::LIR_Op::ListAppend: emit_raw("list_append", inst, false); break;
            case LIR::LIR_Op::ListIndex: emit_raw("list_index", inst); break;
            case LIR::LIR_Op::ListLen: emit_raw("list_len", inst); break;
            case LIR::LIR_Op::DictCreate: emit_raw("dict_create", inst); break;
            case LIR::LIR_Op::DictSet: emit_raw("dict_set", inst, false); break;
            case LIR::LIR_Op::DictGet: emit_raw("dict_get", inst); break;
            case LIR::LIR_Op::DictItems: emit_raw("dict_items", inst); break;
            case LIR::LIR_Op::TupleCreate: emit_raw("tuple_create", inst); break;
            case LIR::LIR_Op::TupleGet: emit_raw("tuple_get", inst); break;
            case LIR::LIR_Op::TupleSet: emit_raw("tuple_set", inst, false); break;
            case LIR::LIR_Op::NewFrame: emit_raw("new_frame", inst); break;
            case LIR::LIR_Op::FrameGetField: emit_raw("frame_get_field", inst); break;
            case LIR::LIR_Op::FrameSetField: emit_raw("frame_set_field", inst, false); break;
            case LIR::LIR_Op::FrameGetFieldAtomic: emit_raw("frame_get_field_atomic", inst); break;
            case LIR::LIR_Op::FrameSetFieldAtomic: emit_raw("frame_set_field_atomic", inst, false); break;
            case LIR::LIR_Op::FrameFieldAtomicAdd: emit_raw("frame_field_atomic_add", inst); break;
            case LIR::LIR_Op::FrameFieldAtomicSub: emit_raw("frame_field_atomic_sub", inst); break;
            case LIR::LIR_Op::FrameCallMethod: emit_call_like("frame_call_method", inst); break;
            case LIR::LIR_Op::FrameCallInit: emit_call_like("frame_call_init", inst); break;
            case LIR::LIR_Op::FrameCallDeinit: emit_call_like("frame_call_deinit", inst); break;
            case LIR::LIR_Op::TraitCallMethod: emit_call_like("trait_call_method", inst); break;
            case LIR::LIR_Op::MakeTraitObject: emit_raw("make_trait_object", inst); break;
            case LIR::LIR_Op::ImportModule: emit_raw("import_module", inst); break;
            case LIR::LIR_Op::ExportSymbol: emit_raw("export_symbol", inst, false); break;
            case LIR::LIR_Op::BeginModule: emit_raw("begin_module", inst, false); break;
            case LIR::LIR_Op::EndModule: emit_raw("end_module", inst, false); break;
            case LIR::LIR_Op::SharedCellAlloc: emit_raw("shared_cell_alloc", inst); break;
            case LIR::LIR_Op::SharedCellLoad: emit_raw("shared_cell_load", inst); break;
            case LIR::LIR_Op::SharedCellStore: emit_raw("shared_cell_store", inst, false); break;
            case LIR::LIR_Op::SharedCellAdd: emit_raw("shared_cell_add", inst); break;
            case LIR::LIR_Op::SharedCellSub: emit_raw("shared_cell_sub", inst); break;
        }

        if (inst.op == LIR::LIR_Op::Jump || inst.op == LIR::LIR_Op::JumpIf || inst.op == LIR::LIR_Op::JumpIfFalse) {
            if (inst.imm >= function_.instructions.size()) {
                report_.diagnostics.push_back({
                    FyraCompiler::TranslationDiagnostic::Severity::Error,
                    index,
                    "control-flow target out of bounds: " + std::to_string(inst.imm)
                });
            }
        }
    }
};

} // namespace

FyraCompiler::FyraCompiler() {
    // Initialize Fyra compiler
}

FyraCompiler::~FyraCompiler() {
    // Cleanup if needed
}

std::string FyraCompiler::convert_lir_to_fyra_ir(const LIR::LIR_Function& lir_func, TranslationReport& report) {
    FyraIRBuilder builder(lir_func, report);
    return builder.build();
}

CompileResult FyraCompiler::compile(const LIR::LIR_Function& lir_func,
                                   const FyraCompileOptions& options) {
    CompileResult result;

    try {
        TranslationReport report;
        std::string fyra_ir = convert_lir_to_fyra_ir(lir_func, report);

        for (const auto& diagnostic : report.diagnostics) {
            std::stringstream msg;
            msg << "[LIR->Fyra @" << diagnostic.instruction_index << "] " << diagnostic.message;
            if (diagnostic.severity == TranslationDiagnostic::Severity::Error) {
                if (!result.error_message.empty()) result.error_message += "\n";
                result.error_message += msg.str();
            } else {
                result.warnings.push_back(msg.str());
            }
        }

        if (report.has_errors()) {
            result.success = false;
            last_error_ = result.error_message;
            return result;
        }

        if (debug_mode_) {
            std::cout << "Generated Fyra IR:\n" << fyra_ir << "\n";
        }

        result = invoke_fyra(fyra_ir, options);

    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = std::string("Fyra compilation error: ") + e.what();
        last_error_ = result.error_message;
    }

    return result;
}

CompileResult FyraCompiler::compile_aot(const LIR::LIR_Function& lir_func,
                                       const std::string& output_file,
                                       OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::AOT;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;

    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_wasm(const LIR::LIR_Function& lir_func,
                                        const std::string& output_file,
                                        OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASM;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;

    return compile(lir_func, options);
}

CompileResult FyraCompiler::compile_wasi(const LIR::LIR_Function& lir_func,
                                        const std::string& output_file,
                                        OptimizationLevel opt_level) {
    FyraCompileOptions options;
    options.target = CompileTarget::WASI;
    options.output_file = output_file;
    options.opt_level = opt_level;
    options.debug_info = debug_mode_;

    return compile(lir_func, options);
}

CompileResult FyraCompiler::invoke_fyra(const std::string& ir_code,
                                       const FyraCompileOptions& options) {
    CompileResult result;

    try {
        std::string temp_ir_file = "temp_fyra_ir.ll";
        std::ofstream ir_file(temp_ir_file);
        ir_file << ir_code;
        ir_file.close();

        std::string cmd = "fyra";
        switch (options.target) {
            case CompileTarget::AOT: cmd += " --target aot"; break;
            case CompileTarget::WASM: cmd += " --target wasm"; break;
            case CompileTarget::WASI: cmd += " --target wasi"; break;
        }

        switch (options.opt_level) {
            case OptimizationLevel::O0: cmd += " -O0"; break;
            case OptimizationLevel::O1: cmd += " -O1"; break;
            case OptimizationLevel::O2: cmd += " -O2"; break;
            case OptimizationLevel::O3: cmd += " -O3"; break;
        }

        cmd += " -o " + options.output_file;

        if (options.debug_info) {
            cmd += " -g";
        }

        cmd += " " + temp_ir_file;

        if (options.verbose) {
            std::cout << "Executing: " << cmd << "\n";
        }

        int exit_code = std::system(cmd.c_str());
        fs::remove(temp_ir_file);

        if (exit_code == 0) {
            result.success = true;
            result.output_file = options.output_file;
        } else {
            result.success = false;
            result.error_message = "Fyra compiler exited with code " + std::to_string(exit_code);
            last_error_ = result.error_message;
        }

    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = std::string("Failed to invoke Fyra: ") + e.what();
        last_error_ = result.error_message;
    }

    return result;
}

} // namespace LM::Backend::Fyra
