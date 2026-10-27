#pragma once

#include "debug_target.hh"
#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>

namespace LM {
namespace DAP {

class LldbDapTarget : public IDebugTarget {
public:
    LldbDapTarget();
    ~LldbDapTarget() override;

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

private:
    IDebugEventListener* listener_ = nullptr;
    std::string program_path_;
    std::string lldb_dap_path_ = "lldb-dap";
    bool is_running_ = false;

    // Recorded breakpoints and frames for proxy mode
    std::vector<DapBreakpoint> active_breakpoints_;
    int next_bp_id_ = 1;
};

} // namespace DAP
} // namespace LM
