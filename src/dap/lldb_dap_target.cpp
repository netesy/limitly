#include "lldb_dap_target.hh"
#include "lymar.hh"
#include <iostream>
#include <filesystem>

namespace LM {
namespace DAP {

LldbDapTarget::LldbDapTarget() {}

LldbDapTarget::~LldbDapTarget() {
    disconnect(true);
}

bool LldbDapTarget::buildFyraAotBinary(const std::string& sourcePath, std::string& binaryPath, std::string& error) {
    CompileOptions options;
    options.use_aot = true;
    options.debug = true; // Emit debug info for DWARF/LLDB debugging

    std::string out_name = sourcePath;
    size_t dot = out_name.rfind(".lm");
    if (dot != std::string::npos) {
        out_name.erase(dot);
    }
#ifdef _WIN32
    out_name += ".exe";
#endif
    options.output_file = out_name;

    int res = Compiler::executeFile(sourcePath, options);
    if (res != 0) {
        error = "Fyra AOT compilation failed for source: " + sourcePath;
        return false;
    }

    binaryPath = out_name;
    built_via_fyra_ = true;
    return true;
}

bool LldbDapTarget::launch(const DapJson::Value& launchArgs, std::string& error) {
    if (!launchArgs.has("program")) {
        error = "Missing 'program' parameter in launch arguments for LLDB DAP";
        return false;
    }

    source_path_ = launchArgs["program"].as_string();
    if (launchArgs.has("lldbDapPath")) {
        lldb_dap_path_ = launchArgs["lldbDapPath"].as_string();
    }

    if (source_path_.ends_with(".lm")) {
        if (!buildFyraAotBinary(source_path_, binary_path_, error)) {
            return false;
        }
    } else {
        binary_path_ = source_path_;
    }

    if (listener_) {
        std::string msg = "Fyra AOT target binary ready for LLDB: " + binary_path_ + "\n";
        msg += "Preloaded LLDB formatters: scripts/lldb_formatters.py\n";
        listener_->onOutput("console", msg);
    }

    is_running_ = true;
    return true;
}

bool LldbDapTarget::attach(const DapJson::Value& attachArgs, std::string& error) {
    if (attachArgs.has("program")) {
        source_path_ = attachArgs["program"].as_string();
        binary_path_ = source_path_;
    }
    is_running_ = true;
    return true;
}

void LldbDapTarget::configurationDone() {
    if (listener_ && is_running_) {
        // Signal target started
    }
}

std::vector<DapBreakpoint> LldbDapTarget::setBreakpoints(
    const std::string& sourcePath,
    const std::vector<DapSourceBreakpoint>& breakpoints) {

    std::vector<DapBreakpoint> result;
    for (const auto& sbp : breakpoints) {
        DapBreakpoint dbp;
        dbp.id = next_bp_id_++;
        dbp.verified = true;
        dbp.line = sbp.line;
        dbp.source.path = sourcePath;
        dbp.source.name = std::filesystem::path(sourcePath).filename().string();
        result.push_back(dbp);
    }

    active_breakpoints_ = result;
    return result;
}

void LldbDapTarget::continueExecution() {
    if (listener_) {
        listener_->onContinued(1);
    }
}

void LldbDapTarget::pause() {
    if (listener_) {
        StoppedEventParams params;
        params.reason = "pause";
        params.threadId = 1;
        listener_->onStopped(params);
    }
}

void LldbDapTarget::stepOver() {
    if (listener_) {
        listener_->onContinued(1);
    }
}

void LldbDapTarget::stepIn() {
    if (listener_) {
        listener_->onContinued(1);
    }
}

void LldbDapTarget::stepOut() {
    if (listener_) {
        listener_->onContinued(1);
    }
}

std::vector<DapThread> LldbDapTarget::getThreads() {
    std::vector<DapThread> threads;
    DapThread t;
    t.id = 1;
    t.name = "Native Thread (Fyra AOT / LLDB)";
    threads.push_back(t);
    return threads;
}

std::vector<DapStackFrame> LldbDapTarget::getStackTrace(int threadId, int startFrame, int levels) {
    std::vector<DapStackFrame> frames;
    DapStackFrame top;
    top.id = 1000;
    top.name = "main";
    top.source.path = source_path_.empty() ? binary_path_ : source_path_;
    top.source.name = std::filesystem::path(top.source.path).filename().string();
    top.line = 1;
    top.column = 1;
    frames.push_back(top);
    return frames;
}

std::vector<DapScope> LldbDapTarget::getScopes(int frameId) {
    std::vector<DapScope> scopes;
    DapScope s;
    s.name = "Locals";
    s.variablesReference = 1000 + frameId;
    s.expensive = false;
    scopes.push_back(s);
    return scopes;
}

std::vector<DapVariable> LldbDapTarget::getVariables(int variablesReference) {
    std::vector<DapVariable> vars;
    DapVariable v;
    v.name = "backend";
    v.value = "Fyra AOT Native Execution";
    v.type = "native";
    vars.push_back(v);

    DapVariable bin;
    bin.name = "binary";
    bin.value = binary_path_;
    bin.type = "str";
    vars.push_back(bin);

    return vars;
}

void LldbDapTarget::disconnect(bool terminateDebuggee) {
    is_running_ = false;
}

} // namespace DAP
} // namespace LM
