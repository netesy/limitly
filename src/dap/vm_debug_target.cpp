#include "vm_debug_target.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/type_checker.hh"
#include "frontend/module_manager.hh"
#include "lir/generator.hh"
#include "lir/functions.hh"
#include "backend/vm/vm_value.hh"
#include "backend/vm/vm_string.hh"
#include "backend/vm/vm_list.hh"
#include "backend/vm/vm_dict.hh"
#include "backend/vm/vm_tuple.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <chrono>

namespace LM {
namespace DAP {

namespace {

std::string normalizePath(const std::string& path) {
    if (path.empty()) return "";
    try {
        std::error_code ec;
        std::filesystem::path p = std::filesystem::absolute(path, ec);
        std::string res = p.generic_string();
        for (char& c : res) c = std::tolower(c);
        return res;
    } catch (...) {
        std::string res = path;
        for (char& c : res) {
            if (c == '\\') c = '/';
            c = std::tolower(c);
        }
        return res;
    }
}

} // namespace

VmDebugTarget::VmDebugTarget() {
    vm_ = std::make_unique<LM::Backend::VM::Register::RegisterVM>();
}

VmDebugTarget::~VmDebugTarget() {
    disconnect(true);
}

bool VmDebugTarget::launch(const DapJson::Value& launchArgs, std::string& error) {
    if (!launchArgs.has("program")) {
        error = "Missing 'program' parameter in launch arguments";
        return false;
    }

    source_path_ = launchArgs["program"].as_string();
    if (launchArgs.has("stopOnEntry")) {
        stop_on_entry_ = launchArgs["stopOnEntry"].as_bool(false);
    }

    std::ifstream file(source_path_);
    if (!file.is_open()) {
        error = "Failed to open source file: " + source_path_;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source_code = buffer.str();

    try {
        Frontend::Scanner scanner(source_code);
        auto tokens = scanner.scanTokens();
        Frontend::Parser parser(scanner, false);
        auto ast = parser.parse();

        if (!ast) {
            error = "Syntax error while parsing " + source_path_;
            return false;
        }

        Frontend::ModuleManager::getInstance().resolve_all(ast, source_path_);
        auto tc_result = Frontend::TypeCheckerFactory::check_program(ast, source_code, source_path_);

        LIR::Generator generator;
        compiled_function_ = generator.generate_program(tc_result);
    } catch (const std::exception& e) {
        error = std::string("Compilation error: ") + e.what();
        return false;
    }

    current_pc_file_ = source_path_;
    current_pc_line_ = 1;

    return true;
}

bool VmDebugTarget::attach(const DapJson::Value& attachArgs, std::string& error) {
    is_attached_ipc_ = true;
    if (attachArgs.has("port")) {
        socket_port_ = static_cast<int>(attachArgs["port"].as_int());
    }
    if (attachArgs.has("program")) {
        source_path_ = attachArgs["program"].as_string();
    }
    return true;
}

void VmDebugTarget::configurationDone() {
    if (state_ == ExecutionState::NotStarted) {
        state_ = ExecutionState::Running;
        if (stop_on_entry_) {
            state_ = ExecutionState::Paused;
            if (listener_) {
                StoppedEventParams params;
                params.reason = "entry";
                params.threadId = 1;
                params.description = "Paused on entry";
                listener_->onStopped(params);
            }
        }
        vm_thread_ = std::thread(&VmDebugTarget::runVmThread, this);
    } else if (state_ == ExecutionState::Paused) {
        continueExecution();
    }
}

void VmDebugTarget::runVmThread() {
    if (stop_on_entry_) {
        std::unique_lock<std::mutex> lock(state_mutex_);
        state_cv_.wait(lock, [this] {
            return state_ != ExecutionState::Paused || state_ == ExecutionState::Terminated;
        });
    }

    if (state_ == ExecutionState::Terminated) return;

    try {
        if (compiled_function_) {
            // Execution loop with debug hook
            const auto& insts = compiled_function_->instructions;
            size_t pc = 0;
            size_t end_pc = insts.size();

            while (pc < end_pc && state_ != ExecutionState::Terminated) {
                const auto& inst = insts[pc];
                if (inst.loc.line > 0) {
                    current_pc_line_ = inst.loc.line;
                }

                if (shouldStopOnInstruction(source_path_, current_pc_line_, current_call_depth_)) {
                    std::string reason = "breakpoint";
                    if (state_ == ExecutionState::SteppingOver ||
                        state_ == ExecutionState::SteppingInto ||
                        state_ == ExecutionState::SteppingOut) {
                        reason = "step";
                    }
                    pauseAndNotify(reason);
                }

                // Execute single step
                vm_->execute_instructions(*compiled_function_, pc, pc + 1);
                pc++;
            }
        }
    } catch (const std::exception& e) {
        if (listener_) {
            listener_->onOutput("stderr", std::string("Runtime error: ") + e.what() + "\n");
        }
    }

    state_ = ExecutionState::Terminated;
    if (listener_) {
        listener_->onExited(0);
        listener_->onTerminated();
    }
}

bool VmDebugTarget::shouldStopOnInstruction(const std::string& sourcePath, int line, uint64_t currentDepth) {
    if (state_ == ExecutionState::Paused) {
        std::unique_lock<std::mutex> lock(state_mutex_);
        state_cv_.wait(lock, [this] {
            return state_ != ExecutionState::Paused || state_ == ExecutionState::Terminated;
        });
        if (state_ == ExecutionState::Terminated) return false;
    }

    std::string norm_path = normalizePath(sourcePath);

    // 1. Check breakpoints
    auto it = breakpoints_.find(norm_path);
    if (it != breakpoints_.end()) {
        for (const auto& bp : it->second) {
            if (bp.line == line && bp.verified) {
                return true;
            }
        }
    }

    // 2. Check stepping
    if (state_ == ExecutionState::SteppingOver) {
        if (currentDepth <= step_start_depth_ && (line != step_start_line_ || norm_path != step_start_file_)) {
            return true;
        }
    } else if (state_ == ExecutionState::SteppingInto) {
        if (line != step_start_line_ || norm_path != step_start_file_ || currentDepth != step_start_depth_) {
            return true;
        }
    } else if (state_ == ExecutionState::SteppingOut) {
        if (currentDepth < step_start_depth_) {
            return true;
        }
    }

    return false;
}

void VmDebugTarget::pauseAndNotify(const std::string& reason, const std::string& text) {
    state_ = ExecutionState::Paused;
    if (listener_) {
        StoppedEventParams params;
        params.reason = reason;
        params.threadId = 1;
        params.description = text;
        listener_->onStopped(params);
    }

    std::unique_lock<std::mutex> lock(state_mutex_);
    state_cv_.wait(lock, [this] {
        return state_ != ExecutionState::Paused || state_ == ExecutionState::Terminated;
    });
}

std::vector<DapBreakpoint> VmDebugTarget::setBreakpoints(
    const std::string& sourcePath,
    const std::vector<DapSourceBreakpoint>& breakpoints) {

    std::string norm_path = normalizePath(sourcePath);
    std::vector<DapBreakpoint> result;
    std::vector<BreakpointInfo> new_bps;

    for (const auto& sbp : breakpoints) {
        DapBreakpoint dbp;
        dbp.id = next_breakpoint_id_++;
        dbp.verified = true;
        dbp.line = sbp.line;
        dbp.source.path = sourcePath;
        dbp.source.name = std::filesystem::path(sourcePath).filename().string();

        BreakpointInfo info;
        info.id = dbp.id;
        info.line = sbp.line;
        info.condition = sbp.condition;
        info.verified = true;

        new_bps.push_back(info);
        result.push_back(dbp);
    }

    breakpoints_[norm_path] = new_bps;
    return result;
}

void VmDebugTarget::continueExecution() {
    state_ = ExecutionState::Running;
    state_cv_.notify_all();
    if (listener_) {
        listener_->onContinued(1);
    }
}

void VmDebugTarget::pause() {
    state_ = ExecutionState::Paused;
    if (listener_) {
        StoppedEventParams params;
        params.reason = "pause";
        params.threadId = 1;
        listener_->onStopped(params);
    }
}

void VmDebugTarget::stepOver() {
    step_start_depth_ = current_call_depth_;
    step_start_line_ = current_pc_line_;
    step_start_file_ = normalizePath(source_path_);
    state_ = ExecutionState::SteppingOver;
    state_cv_.notify_all();
    if (listener_) {
        listener_->onContinued(1);
    }
}

void VmDebugTarget::stepIn() {
    step_start_depth_ = current_call_depth_;
    step_start_line_ = current_pc_line_;
    step_start_file_ = normalizePath(source_path_);
    state_ = ExecutionState::SteppingInto;
    state_cv_.notify_all();
    if (listener_) {
        listener_->onContinued(1);
    }
}

void VmDebugTarget::stepOut() {
    step_start_depth_ = current_call_depth_;
    step_start_line_ = current_pc_line_;
    step_start_file_ = normalizePath(source_path_);
    state_ = ExecutionState::SteppingOut;
    state_cv_.notify_all();
    if (listener_) {
        listener_->onContinued(1);
    }
}

std::vector<DapThread> VmDebugTarget::getThreads() {
    std::vector<DapThread> threads;
    DapThread t;
    t.id = 1;
    t.name = "Main Thread";
    threads.push_back(t);
    return threads;
}

std::vector<DapStackFrame> VmDebugTarget::getStackTrace(int threadId, int startFrame, int levels) {
    std::vector<DapStackFrame> frames;

    DapStackFrame top;
    top.id = 1000;
    top.name = (compiled_function_ && !compiled_function_->name.empty()) ? compiled_function_->name : "main";
    top.source.path = source_path_;
    top.source.name = std::filesystem::path(source_path_).filename().string();
    top.line = current_pc_line_ > 0 ? current_pc_line_ : 1;
    top.column = 1;
    frames.push_back(top);

    return frames;
}

std::vector<DapScope> VmDebugTarget::getScopes(int frameId) {
    std::vector<DapScope> scopes;

    DapScope locals;
    locals.name = "Locals";
    locals.variablesReference = 1000 + frameId;
    locals.expensive = false;
    scopes.push_back(locals);

    DapScope globals;
    globals.name = "Globals";
    globals.variablesReference = 2000 + frameId;
    globals.expensive = false;
    scopes.push_back(globals);

    return scopes;
}

std::string VmDebugTarget::formatLmValue(LmValue val) const {
    if (!vm_) return "nil";
    return vm_->to_string(val);
}

std::string VmDebugTarget::getLmValueTypeName(LmValue val) const {
    if (IS_NIL(val)) return "nil";
    if (IS_BOOL(val)) return "bool";
    if (IS_INT(val)) return "int";
    if (IS_PTR(val)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
        if (!h) return "nil";
        switch (h->type_id) {
            case TYPE_FLOAT: return "float";
            case TYPE_STRING: return "str";
            case TYPE_LIST: return "list";
            case TYPE_DICT: return "dict";
            case TYPE_TUPLE: return "tuple";
            case TYPE_FRAME: return "frame";
            case TYPE_BOX: return "box";
            default: return "object";
        }
    }
    return "any";
}

int VmDebugTarget::registerStructuredVariable(LmValue val) {
    int ref = next_var_ref_++;
    VariableRefEntry entry;
    entry.value = val;
    entry.type_name = getLmValueTypeName(val);
    variable_refs_[ref] = entry;
    return ref;
}

std::vector<DapVariable> VmDebugTarget::getVariables(int variablesReference) {
    std::vector<DapVariable> vars;

    // 1. Local scope variables
    if (variablesReference >= 1000 && variablesReference < 2000) {
        DapVariable status_var;
        status_var.name = "status";
        status_var.value = "running";
        status_var.type = "str";
        vars.push_back(status_var);

        DapVariable file_var;
        file_var.name = "file";
        file_var.value = std::filesystem::path(source_path_).filename().string();
        file_var.type = "str";
        vars.push_back(file_var);
    }
    // 2. Global scope variables
    else if (variablesReference >= 2000 && variablesReference < 3000) {
        DapVariable target_var;
        target_var.name = "Target";
        target_var.value = "Lymar Register VM";
        target_var.type = "str";
        vars.push_back(target_var);
    }
    // 3. Structured compound variables (lists, dicts, frames, tuples)
    else {
        auto it = variable_refs_.find(variablesReference);
        if (it != variable_refs_.end()) {
            LmValue val = it->second.value;
            if (IS_PTR(val)) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                if (h) {
                    if (h->type_id == TYPE_LIST) {
                        LmList* list = (LmList*)h;
                        for (uint64_t i = 0; i < list->size; ++i) {
                            DapVariable elem;
                            elem.name = "[" + std::to_string(i) + "]";
                            elem.value = formatLmValue(list->data[i]);
                            elem.type = getLmValueTypeName(list->data[i]);
                            if (IS_PTR(list->data[i]) && ((ObjHeader*)UNBOX_PTR(list->data[i]))->type_id >= TYPE_LIST) {
                                elem.variablesReference = registerStructuredVariable(list->data[i]);
                            }
                            vars.push_back(elem);
                        }
                    } else if (h->type_id == TYPE_FRAME) {
                        LmFrame* frame = (LmFrame*)h;
                        for (int i = 0; i < frame->field_count; ++i) {
                            DapVariable fvar;
                            fvar.name = "field_" + std::to_string(i);
                            fvar.value = formatLmValue(frame->fields[i]);
                            fvar.type = getLmValueTypeName(frame->fields[i]);
                            if (IS_PTR(frame->fields[i]) && ((ObjHeader*)UNBOX_PTR(frame->fields[i]))->type_id >= TYPE_LIST) {
                                fvar.variablesReference = registerStructuredVariable(frame->fields[i]);
                            }
                            vars.push_back(fvar);
                        }
                    } else if (h->type_id == TYPE_TUPLE) {
                        LmTuple* tuple = (LmTuple*)h;
                        for (uint64_t i = 0; i < tuple->size; ++i) {
                            DapVariable tvar;
                            tvar.name = "(" + std::to_string(i) + ")";
                            tvar.value = formatLmValue(tuple->elements[i]);
                            tvar.type = getLmValueTypeName(tuple->elements[i]);
                            if (IS_PTR(tuple->elements[i]) && ((ObjHeader*)UNBOX_PTR(tuple->elements[i]))->type_id >= TYPE_LIST) {
                                tvar.variablesReference = registerStructuredVariable(tuple->elements[i]);
                            }
                            vars.push_back(tvar);
                        }
                    }
                }
            }
        }
    }

    return vars;
}

void VmDebugTarget::disconnect(bool terminateDebuggee) {
    state_ = ExecutionState::Terminated;
    state_cv_.notify_all();
    if (vm_thread_.joinable()) {
        vm_thread_.join();
    }
}

} // namespace DAP
} // namespace LM
