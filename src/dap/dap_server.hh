#pragma once

#include "dap_types.hh"
#include "debug_target.hh"
#include <string>
#include <memory>
#include <mutex>
#include <atomic>
#include <iostream>

namespace LM {
namespace DAP {

class DapServer : public IDebugEventListener {
public:
    DapServer();
    ~DapServer() override;

    // Run DAP server loop over stdio
    void runStdio();

    // Run DAP server loop over TCP socket
    void runSocket(int port);

    // IDebugEventListener overrides
    void onStopped(const StoppedEventParams& params) override;
    void onContinued(int threadId) override;
    void onOutput(const std::string& category, const std::string& output) override;
    void onTerminated() override;
    void onExited(int exitCode) override;

private:
    void sendResponse(int seq, const std::string& command, bool success, const DapJson::Value& body = DapJson::Value(), const std::string& message = "");
    void sendEvent(const std::string& eventType, const DapJson::Value& body = DapJson::Value());
    void sendMessage(const DapJson::Value& msg);

    void handleRequest(const DapJson::Value& req);

    void handleInitialize(int seq, const DapJson::Value& args);
    void handleLaunch(int seq, const DapJson::Value& args);
    void handleAttach(int seq, const DapJson::Value& args);
    void handleSetBreakpoints(int seq, const DapJson::Value& args);
    void handleConfigurationDone(int seq, const DapJson::Value& args);
    void handleThreads(int seq, const DapJson::Value& args);
    void handleStackTrace(int seq, const DapJson::Value& args);
    void handleScopes(int seq, const DapJson::Value& args);
    void handleVariables(int seq, const DapJson::Value& args);
    void handleContinue(int seq, const DapJson::Value& args);
    void handleNext(int seq, const DapJson::Value& args);
    void handleStepIn(int seq, const DapJson::Value& args);
    void handleStepOut(int seq, const DapJson::Value& args);
    void handlePause(int seq, const DapJson::Value& args);
    void handleDisconnect(int seq, const DapJson::Value& args);

    std::unique_ptr<IDebugTarget> target_;
    std::atomic<int> sequence_number_{1};
    std::mutex send_mutex_;
    bool is_socket_mode_ = false;
    int socket_fd_ = -1;
};

} // namespace DAP
} // namespace LM
