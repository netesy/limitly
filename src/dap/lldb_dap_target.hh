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
    bool buildFyraAotBinary(const std::string& sourcePath, std::string& binaryPath, std::string& error);
    bool spawnLldbDapProcess(std::string& error);

    IDebugEventListener* listener_ = nullptr;
    std::string source_path_;
    std::string binary_path_;
    std::string lldb_dap_path_ = "lldb-dap";
    bool is_running_ = false;
    bool built_via_fyra_ = false;

    // Subprocess handles
#ifndef _WIN32
    int pid_ = -1;
    int pipe_in_[2] = {-1, -1};
    int pipe_out_[2] = {-1, -1};
#else
    void* h_process_ = nullptr;
    void* h_in_write_ = nullptr;
    void* h_out_read_ = nullptr;
#endif

    std::thread io_thread_;
    std::atomic<bool> stop_io_{false};

    // Recorded breakpoints and frames for proxy mode
    std::vector<DapBreakpoint> active_breakpoints_;
    int next_bp_id_ = 1;
};

} // namespace DAP
} // namespace LM
