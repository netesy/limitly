#pragma once

#include "debug_target.hh"
#include "backend/vm/register.hh"
#include "lir/lir.hh"
#include "frontend/ast.hh"
#include "frontend/type_checker.hh"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <memory>

namespace LM {
namespace DAP {

enum class ExecutionState {
    NotStarted,
    Running,
    SteppingOver,
    SteppingInto,
    SteppingOut,
    Paused,
    Terminated
};

struct BreakpointInfo {
    int id;
    int line;
    std::string condition;
    bool verified;
};

class VmDebugTarget : public IDebugTarget {
public:
    VmDebugTarget();
    ~VmDebugTarget() override;

    void setEventListener(IDebugEventListener* listener) override {
        listener_ = listener;
    }

    bool launch(const DapJson::Value& launchArgs, std::string& error) override;
    bool attach(const DapJson::Value& attachArgs, std::string& error) override;
    void configurationDone() override;

    std::vector<DapBreakpoint> setBreakpoints(
        const std::string& sourcePath,
        const std::vector<DapSourceBreakpoint>& breakpoints) override;

    void continueExecution() override;
    void pause() override;
    void stepOver() override;
    void stepIn() override;
    void stepOut() override;

    std::vector<DapThread> getThreads() override;
    std::vector<DapStackFrame> getStackTrace(int threadId, int startFrame, int levels) override;
    std::vector<DapScope> getScopes(int frameId) override;
    std::vector<DapVariable> getVariables(int variablesReference) override;

    void disconnect(bool terminateDebuggee) override;

    // Direct execution hook for VM instruction stepping
    void onInstructionStep(const LIR::LIR_Function& function, uint64_t pc);

private:
    void runVmThread();
    bool shouldStopOnInstruction(const std::string& sourcePath, int line, uint64_t currentDepth);
    void pauseAndNotify(const std::string& reason, const std::string& text = "");
    int registerStructuredVariable(LmValue val);
    std::string formatLmValue(LmValue val) const;
    std::string getLmValueTypeName(LmValue val) const;

    IDebugEventListener* listener_ = nullptr;
    std::string source_path_;
    bool stop_on_entry_ = false;
    bool is_attached_ipc_ = false;
    int socket_port_ = 0;

    std::atomic<ExecutionState> state_{ExecutionState::NotStarted};
    std::unique_ptr<LM::Backend::VM::Register::RegisterVM> vm_;
    std::unique_ptr<LIR::LIR_Function> compiled_function_;

    std::thread vm_thread_;
    std::mutex state_mutex_;
    std::condition_variable state_cv_;

    // Breakpoint table: normalized_path -> list of breakpoints
    std::unordered_map<std::string, std::vector<BreakpointInfo>> breakpoints_;
    int next_breakpoint_id_ = 1;

    // Stepping state tracking
    uint64_t step_start_depth_ = 0;
    int step_start_line_ = -1;
    std::string step_start_file_;

    // Source line mapping cache
    int current_pc_line_ = 1;
    std::string current_pc_file_;
    uint64_t current_call_depth_ = 0;

    // Variable reference tracking for structured objects
    struct VariableRefEntry {
        LmValue value;
        std::string type_name;
    };
    std::unordered_map<int, VariableRefEntry> variable_refs_;
    int next_var_ref_ = 100000;
};

} // namespace DAP
} // namespace LM
