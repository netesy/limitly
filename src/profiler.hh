#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <cstdint>
#include <memory>
#include "lymar.hh"

namespace LM {

struct FunctionProfile {
    std::string name;
    uint64_t call_count = 0;
    uint64_t total_time_ns = 0; // Inclusive duration (including sub-calls)
    uint64_t self_time_ns = 0;  // Exclusive duration (excluding sub-calls)
    uint64_t min_time_ns = UINT64_MAX;
    uint64_t max_time_ns = 0;
};

struct StackFrame {
    std::string name;
    std::chrono::steady_clock::time_point start_time;
    uint64_t child_time_ns = 0;
};

class Profiler {
public:
    static Profiler& getInstance() {
        static Profiler instance;
        return instance;
    }

    void enable(bool value = true) { enabled_ = value; }
    bool is_enabled() const { return enabled_; }

    void start();
    void stop();
    void reset();

    void enter_function(const std::string& name);
    void exit_function();

    void report(const std::string& source_file,
                const std::string& flamegraph_file = "",
                bool json_output = false,
                const std::string& sort_by = "self",
                size_t top_n = 25);

    static int run(int argc, char* argv[]);

private:
    Profiler() = default;

    bool enabled_ = false;
    std::chrono::steady_clock::time_point session_start_;
    std::chrono::steady_clock::time_point session_end_;
    uint64_t total_session_ns_ = 0;
    uint64_t total_calls_ = 0;

    std::vector<StackFrame> call_stack_;
    std::unordered_map<std::string, FunctionProfile> profiles_;
    std::unordered_map<std::string, uint64_t> folded_stacks_; // "main;foo;bar" -> duration ns
};

class ProfileScope {
public:
    explicit ProfileScope(const std::string& name) : active_(Profiler::getInstance().is_enabled()) {
        if (active_) {
            Profiler::getInstance().enter_function(name);
        }
    }
    ~ProfileScope() {
        if (active_) {
            Profiler::getInstance().exit_function();
        }
    }
private:
    bool active_;
};

} // namespace LM
