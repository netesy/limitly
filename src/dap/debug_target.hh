#pragma once

#include "dap_types.hh"
#include <string>
#include <vector>
#include <memory>

namespace LM {
namespace DAP {

class IDebugEventListener {
public:
    virtual ~IDebugEventListener() = default;

    virtual void onStopped(const StoppedEventParams& params) = 0;
    virtual void onContinued(int threadId) = 0;
    virtual void onOutput(const std::string& category, const std::string& output) = 0;
    virtual void onTerminated() = 0;
    virtual void onExited(int exitCode) = 0;
};

class IDebugTarget {
public:
    virtual ~IDebugTarget() = default;

    virtual void setEventListener(IDebugEventListener* listener) = 0;

    virtual bool launch(const DapJson::Value& launchArgs, std::string& error) = 0;
    virtual bool attach(const DapJson::Value& attachArgs, std::string& error) = 0;
    virtual void configurationDone() = 0;

    virtual std::vector<DapBreakpoint> setBreakpoints(
        const std::string& sourcePath,
        const std::vector<DapSourceBreakpoint>& breakpoints) = 0;

    virtual void continueExecution() = 0;
    virtual void pause() = 0;
    virtual void stepOver() = 0;
    virtual void stepIn() = 0;
    virtual void stepOut() = 0;

    virtual std::vector<DapThread> getThreads() = 0;
    virtual std::vector<DapStackFrame> getStackTrace(int threadId, int startFrame, int levels) = 0;
    virtual std::vector<DapScope> getScopes(int frameId) = 0;
    virtual std::vector<DapVariable> getVariables(int variablesReference) = 0;

    virtual void disconnect(bool terminateDebuggee) = 0;
};

} // namespace DAP
} // namespace LM
