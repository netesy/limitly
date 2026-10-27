#include "dap/dap_types.hh"
#include "dap/debug_target.hh"
#include "dap/vm_debug_target.hh"
#include "dap/lldb_dap_target.hh"
#include "dap/dap_server.hh"

#include <iostream>
#include <cassert>
#include <fstream>
#include <filesystem>

void test_json_rpc() {
    std::cout << "Testing DAP JSON-RPC parsing & serialization..." << std::endl;

    LM::DAP::DapJson::Value val = LM::DAP::DapJson::Value::object();
    val["seq"] = 1;
    val["type"] = "request";
    val["command"] = "initialize";

    std::string str = val.serialize();
    assert(str.find("\"command\":\"initialize\"") != std::string::npos);

    LM::DAP::DapJson::Parser parser(str);
    auto parsed = parser.parse();
    assert(parsed.is_object());
    assert(parsed["seq"].as_int() == 1);
    assert(parsed["command"].as_string() == "initialize");

    std::cout << "[PASS] JSON-RPC test passed." << std::endl;
}

void test_vm_debug_target() {
    std::cout << "Testing VmDebugTarget launch, breakpoints, stack trace, scopes, and variables..." << std::endl;

    // Create a temporary sample Lymar source file
    std::string temp_file = "temp_dap_test.lm";
    {
        std::ofstream out(temp_file);
        out << "var x = 10;\n";
        out << "var y = 20;\n";
        out << "var sum = x + y;\n";
        out << "print(sum);\n";
    }

    LM::DAP::VmDebugTarget target;

    LM::DAP::DapJson::Value launch_args = LM::DAP::DapJson::Value::object();
    launch_args["program"] = temp_file;
    launch_args["stopOnEntry"] = true;

    std::string err;
    bool ok = target.launch(launch_args, err);
    assert(ok && err.empty());

    std::vector<LM::DAP::DapSourceBreakpoint> sbps;
    LM::DAP::DapSourceBreakpoint sbp;
    sbp.line = 3;
    sbps.push_back(sbp);

    auto bps = target.setBreakpoints(temp_file, sbps);
    assert(bps.size() == 1);
    assert(bps[0].line == 3);
    assert(bps[0].verified);

    auto threads = target.getThreads();
    assert(!threads.empty());
    assert(threads[0].id == 1);

    auto frames = target.getStackTrace(1, 0, 10);
    assert(!frames.empty());
    assert(frames[0].line >= 1);

    auto scopes = target.getScopes(frames[0].id);
    assert(!scopes.empty());

    auto vars = target.getVariables(scopes[0].variablesReference);
    assert(!vars.empty());

    target.disconnect(true);

    if (std::filesystem::exists(temp_file)) {
        std::filesystem::remove(temp_file);
    }

    std::cout << "[PASS] VmDebugTarget test passed." << std::endl;
}

void test_lldb_dap_target() {
    std::cout << "Testing LldbDapTarget pass-through abstraction & Fyra AOT integration..." << std::endl;

    std::string temp_file = "temp_lldb_dap_test.lm";
    {
        std::ofstream out(temp_file);
        out << "var a = 100;\n";
        out << "print(a);\n";
    }

    LM::DAP::LldbDapTarget target;

    LM::DAP::DapJson::Value launch_args = LM::DAP::DapJson::Value::object();
    launch_args["program"] = temp_file;

    std::string err;
    bool ok = target.launch(launch_args, err);
    assert(ok);

    auto threads = target.getThreads();
    assert(!threads.empty());

    auto frames = target.getStackTrace(1, 0, 10);
    assert(!frames.empty());

    auto scopes = target.getScopes(frames[0].id);
    assert(!scopes.empty());

    auto vars = target.getVariables(scopes[0].variablesReference);
    assert(!vars.empty());

    target.disconnect(true);

    if (std::filesystem::exists(temp_file)) {
        std::filesystem::remove(temp_file);
    }
    std::string bin_file = "temp_lldb_dap_test";
#ifdef _WIN32
    bin_file += ".exe";
#endif
    if (std::filesystem::exists(bin_file)) {
        std::filesystem::remove(bin_file);
    }

    std::cout << "[PASS] LldbDapTarget test passed." << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "Running DAP Server Unit & Integration Tests" << std::endl;
    std::cout << "========================================" << std::endl;

    test_json_rpc();
    test_vm_debug_target();
    test_lldb_dap_target();

    std::cout << "========================================" << std::endl;
    std::cout << "All DAP Server Tests Passed Successfully!" << std::endl;
    std::cout << "========================================" << std::endl;
    return 0;
}
