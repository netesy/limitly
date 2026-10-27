#include "dap_server.hh"
#include "vm_debug_target.hh"
#include "lldb_dap_target.hh"

#include <iostream>
#include <sstream>
#include <cctype>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fcntl.h>
#include <io.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

namespace LM {
namespace DAP {

DapServer::DapServer() {}

DapServer::~DapServer() {
#ifdef _WIN32
    if (socket_fd_ != -1) closesocket(socket_fd_);
#else
    if (socket_fd_ != -1) close(socket_fd_);
#endif
}

void DapServer::sendMessage(const DapJson::Value& msg) {
    std::lock_guard<std::mutex> lock(send_mutex_);
    std::string payload = msg.serialize();
    std::string header = "Content-Length: " + std::to_string(payload.size()) + "\r\n\r\n";

    if (is_socket_mode_ && socket_fd_ != -1) {
        std::string full = header + payload;
#ifdef _WIN32
        send(socket_fd_, full.c_str(), static_cast<int>(full.size()), 0);
#else
        auto res = write(socket_fd_, full.c_str(), full.size());
        (void)res;
#endif
    } else {
        std::cout << header << payload;
        std::cout.flush();
    }
}

void DapServer::sendResponse(int seq, const std::string& command, bool success, const DapJson::Value& body, const std::string& message) {
    DapJson::Value res = DapJson::Value::object();
    res["seq"] = sequence_number_++;
    res["type"] = "response";
    res["request_seq"] = seq;
    res["command"] = command;
    res["success"] = success;
    if (!success && !message.empty()) {
        res["message"] = message;
    }
    if (!body.empty()) {
        res["body"] = body;
    }
    sendMessage(res);
}

void DapServer::sendEvent(const std::string& eventType, const DapJson::Value& body) {
    DapJson::Value evt = DapJson::Value::object();
    evt["seq"] = sequence_number_++;
    evt["type"] = "event";
    evt["event"] = eventType;
    if (!body.empty()) {
        evt["body"] = body;
    }
    sendMessage(evt);
}

void DapServer::runStdio() {
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    std::cerr << "Lymar DAP Server started over stdio..." << std::endl;

    while (std::cin) {
        std::string line;
        char c = 0;
        while (std::cin.get(c)) {
            if (c == '\r') {
                if (std::cin.peek() == '\n') std::cin.get(c);
                break;
            }
            if (c == '\n') break;
            line += c;
        }

        if (std::cin.eof() && line.empty()) break;
        if (line.empty()) continue;

        std::string lower_line = line;
        for (char& ch : lower_line) ch = std::tolower(ch);

        if (lower_line.rfind("content-length:", 0) == 0) {
            size_t colon_pos = line.find(':');
            int content_length = std::stoi(line.substr(colon_pos + 1));

            // Consume headers until empty line
            while (std::cin.get(c)) {
                if (c == '\r') {
                    if (std::cin.peek() == '\n') std::cin.get(c);
                    break;
                }
                if (c == '\n') break;
                std::string extra_hdr;
                extra_hdr += c;
                while (std::cin.get(c)) {
                    if (c == '\r') {
                        if (std::cin.peek() == '\n') std::cin.get(c);
                        break;
                    }
                    if (c == '\n') break;
                    extra_hdr += c;
                }
                if (extra_hdr.empty()) break;
            }

            std::string payload(content_length, '\0');
            std::cin.read(&payload[0], content_length);

            DapJson::Parser parser(payload);
            DapJson::Value msg = parser.parse();
            if (msg.is_object()) {
                handleRequest(msg);
            }
        }
    }
}

void DapServer::runSocket(int port) {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Failed to create DAP server socket" << std::endl;
        return;
    }

    int opt = 1;
#ifdef _WIN32
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
#else
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Failed to bind DAP server socket on port " << port << std::endl;
        return;
    }

    listen(server_fd, 1);
    std::cerr << "Lymar DAP Server listening on TCP port " << port << "..." << std::endl;

    sockaddr_in client_addr{};
    socklen_t addrlen = sizeof(client_addr);
    socket_fd_ = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);
    if (socket_fd_ < 0) {
        std::cerr << "DAP accept failed" << std::endl;
        return;
    }

    is_socket_mode_ = true;
    std::cerr << "DAP client connected on TCP socket." << std::endl;

    std::string buffer;
    char chunk[1024];

    while (socket_fd_ != -1) {
#ifdef _WIN32
        int bytes = recv(socket_fd_, chunk, sizeof(chunk), 0);
#else
        int bytes = read(socket_fd_, chunk, sizeof(chunk));
#endif
        if (bytes <= 0) break;
        buffer.append(chunk, bytes);

        while (true) {
            size_t header_pos = buffer.find("Content-Length:");
            if (header_pos == std::string::npos) break;

            size_t body_start = buffer.find("\r\n\r\n", header_pos);
            if (body_start == std::string::npos) break;

            size_t len_start = header_pos + 15;
            size_t len_end = buffer.find("\r\n", header_pos);
            int content_len = std::stoi(buffer.substr(len_start, len_end - len_start));

            size_t payload_start = body_start + 4;
            if (buffer.size() < payload_start + content_len) break;

            std::string payload = buffer.substr(payload_start, content_len);
            buffer.erase(0, payload_start + content_len);

            DapJson::Parser parser(payload);
            DapJson::Value msg = parser.parse();
            if (msg.is_object()) {
                handleRequest(msg);
            }
        }
    }
}

void DapServer::handleRequest(const DapJson::Value& req) {
    if (!req.has("command")) return;
    std::string command = req["command"].as_string();
    int seq = static_cast<int>(req["seq"].as_int());
    DapJson::Value args = req.has("arguments") ? req["arguments"] : DapJson::Value();

    if (command == "initialize") {
        handleInitialize(seq, args);
    } else if (command == "launch") {
        handleLaunch(seq, args);
    } else if (command == "attach") {
        handleAttach(seq, args);
    } else if (command == "setBreakpoints") {
        handleSetBreakpoints(seq, args);
    } else if (command == "configurationDone") {
        handleConfigurationDone(seq, args);
    } else if (command == "threads") {
        handleThreads(seq, args);
    } else if (command == "stackTrace") {
        handleStackTrace(seq, args);
    } else if (command == "scopes") {
        handleScopes(seq, args);
    } else if (command == "variables") {
        handleVariables(seq, args);
    } else if (command == "continue") {
        handleContinue(seq, args);
    } else if (command == "next") {
        handleNext(seq, args);
    } else if (command == "stepIn") {
        handleStepIn(seq, args);
    } else if (command == "stepOut") {
        handleStepOut(seq, args);
    } else if (command == "pause") {
        handlePause(seq, args);
    } else if (command == "disconnect") {
        handleDisconnect(seq, args);
    } else {
        sendResponse(seq, command, false, DapJson::Value(), "Unsupported request: " + command);
    }
}

void DapServer::handleInitialize(int seq, const DapJson::Value& args) {
    DapJson::Value capabilities = DapJson::Value::object();
    capabilities["supportsConfigurationDoneRequest"] = true;
    capabilities["supportsFunctionBreakpoints"] = false;
    capabilities["supportsConditionalBreakpoints"] = true;
    capabilities["supportsHitConditionalBreakpoints"] = false;
    capabilities["supportsEvaluateForHovers"] = true;
    capabilities["supportsStepBack"] = false;
    capabilities["supportsSetVariable"] = true;
    capabilities["supportsRestartFrame"] = false;

    sendResponse(seq, "initialize", true, capabilities);
    sendEvent("initialized");
}

void DapServer::handleLaunch(int seq, const DapJson::Value& args) {
    std::string mode = "vm";
    if (args.has("mode")) {
        mode = args["mode"].as_string();
    }

    if (mode == "aot" || mode == "lldb") {
        target_ = std::make_unique<LldbDapTarget>();
    } else {
        target_ = std::make_unique<VmDebugTarget>();
    }

    target_->setEventListener(this);
    std::string error;
    if (target_->launch(args, error)) {
        sendResponse(seq, "launch", true);
    } else {
        sendResponse(seq, "launch", false, DapJson::Value(), error);
    }
}

void DapServer::handleAttach(int seq, const DapJson::Value& args) {
    target_ = std::make_unique<VmDebugTarget>();
    target_->setEventListener(this);
    std::string error;
    if (target_->attach(args, error)) {
        sendResponse(seq, "attach", true);
    } else {
        sendResponse(seq, "attach", false, DapJson::Value(), error);
    }
}

void DapServer::handleSetBreakpoints(int seq, const DapJson::Value& args) {
    if (!target_) {
        sendResponse(seq, "setBreakpoints", false, DapJson::Value(), "Debug target not initialized");
        return;
    }

    std::string source_path;
    if (args.has("source") && args["source"].has("path")) {
        source_path = args["source"]["path"].as_string();
    }

    std::vector<DapSourceBreakpoint> sbps;
    if (args.has("breakpoints") && args["breakpoints"].is_array()) {
        for (size_t i = 0; i < args["breakpoints"].size(); ++i) {
            sbps.push_back(DapSourceBreakpoint::from_json(args["breakpoints"][i]));
        }
    }

    auto bps = target_->setBreakpoints(source_path, sbps);

    DapJson::Value body = DapJson::Value::object();
    DapJson::Value bps_arr = DapJson::Value::array();
    for (const auto& bp : bps) {
        bps_arr.push_back(bp.to_json());
    }
    body["breakpoints"] = bps_arr;

    sendResponse(seq, "setBreakpoints", true, body);
}

void DapServer::handleConfigurationDone(int seq, const DapJson::Value& args) {
    if (target_) {
        target_->configurationDone();
    }
    sendResponse(seq, "configurationDone", true);
}

void DapServer::handleThreads(int seq, const DapJson::Value& args) {
    DapJson::Value body = DapJson::Value::object();
    DapJson::Value threads_arr = DapJson::Value::array();

    if (target_) {
        auto threads = target_->getThreads();
        for (const auto& t : threads) {
            threads_arr.push_back(t.to_json());
        }
    } else {
        DapThread t;
        t.id = 1;
        t.name = "Main Thread";
        threads_arr.push_back(t.to_json());
    }

    body["threads"] = threads_arr;
    sendResponse(seq, "threads", true, body);
}

void DapServer::handleStackTrace(int seq, const DapJson::Value& args) {
    if (!target_) {
        sendResponse(seq, "stackTrace", false, DapJson::Value(), "Debug target not initialized");
        return;
    }

    int thread_id = args.has("threadId") ? static_cast<int>(args["threadId"].as_int()) : 1;
    int start_frame = args.has("startFrame") ? static_cast<int>(args["startFrame"].as_int()) : 0;
    int levels = args.has("levels") ? static_cast<int>(args["levels"].as_int()) : 20;

    auto frames = target_->getStackTrace(thread_id, start_frame, levels);

    DapJson::Value body = DapJson::Value::object();
    DapJson::Value frames_arr = DapJson::Value::array();
    for (const auto& f : frames) {
        frames_arr.push_back(f.to_json());
    }
    body["stackFrames"] = frames_arr;
    body["totalFrames"] = frames.size();

    sendResponse(seq, "stackTrace", true, body);
}

void DapServer::handleScopes(int seq, const DapJson::Value& args) {
    if (!target_) {
        sendResponse(seq, "scopes", false, DapJson::Value(), "Debug target not initialized");
        return;
    }

    int frame_id = args.has("frameId") ? static_cast<int>(args["frameId"].as_int()) : 0;
    auto scopes = target_->getScopes(frame_id);

    DapJson::Value body = DapJson::Value::object();
    DapJson::Value scopes_arr = DapJson::Value::array();
    for (const auto& s : scopes) {
        scopes_arr.push_back(s.to_json());
    }
    body["scopes"] = scopes_arr;

    sendResponse(seq, "scopes", true, body);
}

void DapServer::handleVariables(int seq, const DapJson::Value& args) {
    if (!target_) {
        sendResponse(seq, "variables", false, DapJson::Value(), "Debug target not initialized");
        return;
    }

    int var_ref = args.has("variablesReference") ? static_cast<int>(args["variablesReference"].as_int()) : 0;
    auto vars = target_->getVariables(var_ref);

    DapJson::Value body = DapJson::Value::object();
    DapJson::Value vars_arr = DapJson::Value::array();
    for (const auto& v : vars) {
        vars_arr.push_back(v.to_json());
    }
    body["variables"] = vars_arr;

    sendResponse(seq, "variables", true, body);
}

void DapServer::handleContinue(int seq, const DapJson::Value& args) {
    if (target_) {
        target_->continueExecution();
    }
    DapJson::Value body = DapJson::Value::object();
    body["allThreadsContinued"] = true;
    sendResponse(seq, "continue", true, body);
}

void DapServer::handleNext(int seq, const DapJson::Value& args) {
    if (target_) {
        target_->stepOver();
    }
    sendResponse(seq, "next", true);
}

void DapServer::handleStepIn(int seq, const DapJson::Value& args) {
    if (target_) {
        target_->stepIn();
    }
    sendResponse(seq, "stepIn", true);
}

void DapServer::handleStepOut(int seq, const DapJson::Value& args) {
    if (target_) {
        target_->stepOut();
    }
    sendResponse(seq, "stepOut", true);
}

void DapServer::handlePause(int seq, const DapJson::Value& args) {
    if (target_) {
        target_->pause();
    }
    sendResponse(seq, "pause", true);
}

void DapServer::handleDisconnect(int seq, const DapJson::Value& args) {
    bool terminate = args.has("terminateDebuggee") ? args["terminateDebuggee"].as_bool(true) : true;
    if (target_) {
        target_->disconnect(terminate);
    }
    sendResponse(seq, "disconnect", true);
}

// IDebugEventListener callbacks
void DapServer::onStopped(const StoppedEventParams& params) {
    DapJson::Value body = DapJson::Value::object();
    body["reason"] = params.reason;
    body["threadId"] = params.threadId;
    if (!params.description.empty()) body["description"] = params.description;
    if (!params.text.empty()) body["text"] = params.text;
    body["allThreadsStopped"] = params.allThreadsStopped;
    sendEvent("stopped", body);
}

void DapServer::onContinued(int threadId) {
    DapJson::Value body = DapJson::Value::object();
    body["threadId"] = threadId;
    body["allThreadsContinued"] = true;
    sendEvent("continued", body);
}

void DapServer::onOutput(const std::string& category, const std::string& output) {
    DapJson::Value body = DapJson::Value::object();
    body["category"] = category;
    body["output"] = output;
    sendEvent("output", body);
}

void DapServer::onTerminated() {
    sendEvent("terminated");
}

void DapServer::onExited(int exitCode) {
    DapJson::Value body = DapJson::Value::object();
    body["exitCode"] = exitCode;
    sendEvent("exited", body);
}

} // namespace DAP
} // namespace LM
