#include "profiler.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <filesystem>
#include "lymar.hh"

namespace LM {

static std::string format_time_ns(uint64_t ns) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    if (ns >= 1'000'000'000ULL) {
        ss << (ns / 1'000'000'000.0) << " s";
    } else if (ns >= 1'000'000ULL) {
        ss << (ns / 1'000'000.0) << " ms";
    } else if (ns >= 1'000ULL) {
        ss << (ns / 1'000.0) << " us";
    } else {
        ss << ns << " ns";
    }
    return ss.str();
}

void Profiler::start() {
    enabled_ = true;
    call_stack_.clear();
    profiles_.clear();
    folded_stacks_.clear();
    total_calls_ = 0;
    session_start_ = std::chrono::steady_clock::now();
}

void Profiler::stop() {
    session_end_ = std::chrono::steady_clock::now();
    total_session_ns_ = std::chrono::duration_cast<std::chrono::nanoseconds>(session_end_ - session_start_).count();
    // Flush any frames remaining on the stack (e.g. if an exception occurred)
    while (!call_stack_.empty()) {
        exit_function();
    }
    enabled_ = false;
}

void Profiler::reset() {
    enabled_ = false;
    call_stack_.clear();
    profiles_.clear();
    folded_stacks_.clear();
    total_calls_ = 0;
    total_session_ns_ = 0;
}

void Profiler::enter_function(const std::string& name) {
    if (!enabled_) return;
    if (call_stack_.size() > 50000) return; // Guard against stack blowup on runaway recursion

    total_calls_++;
    call_stack_.push_back(StackFrame{name, std::chrono::steady_clock::now(), 0});
}

void Profiler::exit_function() {
    if (!enabled_ || call_stack_.empty()) return;

    StackFrame frame = call_stack_.back();
    call_stack_.pop_back();

    auto now = std::chrono::steady_clock::now();
    uint64_t elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now - frame.start_time).count();
    uint64_t self_ns = (elapsed_ns >= frame.child_time_ns) ? (elapsed_ns - frame.child_time_ns) : 0;

    auto& prof = profiles_[frame.name];
    prof.name = frame.name;
    prof.call_count++;
    prof.total_time_ns += elapsed_ns;
    prof.self_time_ns += self_ns;
    if (elapsed_ns < prof.min_time_ns) prof.min_time_ns = elapsed_ns;
    if (elapsed_ns > prof.max_time_ns) prof.max_time_ns = elapsed_ns;

    if (!call_stack_.empty()) {
        call_stack_.back().child_time_ns += elapsed_ns;
    }

    // Folded call path for Flamegraph generation
    std::string folded_path;
    for (const auto& parent : call_stack_) {
        if (!folded_path.empty()) folded_path += ";";
        folded_path += parent.name;
    }
    if (!folded_path.empty()) folded_path += ";";
    folded_path += frame.name;
    folded_stacks_[folded_path] += self_ns;
}

void Profiler::report(const std::string& source_file,
                      const std::string& flamegraph_file,
                      bool json_output,
                      const std::string& sort_by,
                      size_t top_n) {
    if (profiles_.empty()) {
        std::cout << "No profiling samples collected for " << source_file << "\n";
        return;
    }

    std::vector<FunctionProfile> sorted;
    sorted.reserve(profiles_.size());
    uint64_t aggregate_self_ns = 0;
    for (const auto& [name, prof] : profiles_) {
        sorted.push_back(prof);
        aggregate_self_ns += prof.self_time_ns;
    }

    uint64_t baseline_ns = (total_session_ns_ > aggregate_self_ns) ? total_session_ns_ : aggregate_self_ns;
    if (baseline_ns == 0) baseline_ns = 1;

    if (sort_by == "total") {
        std::sort(sorted.begin(), sorted.end(), [](const FunctionProfile& a, const FunctionProfile& b) {
            return a.total_time_ns > b.total_time_ns;
        });
    } else if (sort_by == "calls") {
        std::sort(sorted.begin(), sorted.end(), [](const FunctionProfile& a, const FunctionProfile& b) {
            return a.call_count > b.call_count;
        });
    } else { // default: sort by self
        std::sort(sorted.begin(), sorted.end(), [](const FunctionProfile& a, const FunctionProfile& b) {
            return a.self_time_ns > b.self_time_ns;
        });
    }

    // Export flamegraph folded stack file if requested
    if (!flamegraph_file.empty()) {
        std::ofstream fg(flamegraph_file);
        if (fg.is_open()) {
            for (const auto& [stack, duration_ns] : folded_stacks_) {
                // Flamegraph folded format: stack_string sample_count_or_time_us
                uint64_t samples = duration_ns / 1'000ULL; // microsecond resolution
                if (samples == 0) samples = 1;
                fg << stack << " " << samples << "\n";
            }
            fg.close();
            std::cout << "\nFlamegraph folded stack written to: " << flamegraph_file << "\n";
            std::cout << "Render using: flamegraph.pl " << flamegraph_file << " > flamegraph.svg\n";
        } else {
            std::cerr << "Warning: Could not open flamegraph output file: " << flamegraph_file << "\n";
        }
    }

    if (json_output) {
        std::cout << "{\n";
        std::cout << "  \"source_file\": \"" << source_file << "\",\n";
        std::cout << "  \"total_runtime_ns\": " << total_session_ns_ << ",\n";
        std::cout << "  \"total_calls\": " << total_calls_ << ",\n";
        std::cout << "  \"functions\": [\n";
        for (size_t i = 0; i < sorted.size(); i++) {
            const auto& p = sorted[i];
            double pct = (double)p.self_time_ns * 100.0 / baseline_ns;
            std::cout << "    {\n";
            std::cout << "      \"name\": \"" << p.name << "\",\n";
            std::cout << "      \"calls\": " << p.call_count << ",\n";
            std::cout << "      \"total_ns\": " << p.total_time_ns << ",\n";
            std::cout << "      \"self_ns\": " << p.self_time_ns << ",\n";
            std::cout << "      \"self_percent\": " << std::fixed << std::setprecision(2) << pct << "\n";
            std::cout << "    }" << (i + 1 < sorted.size() ? "," : "") << "\n";
        }
        std::cout << "  ]\n";
        std::cout << "}\n";
        return;
    }

    std::cout << "\n========================================================================================\n";
    std::cout << "Lymar Execution Profile: " << source_file << "\n";
    std::cout << "Total Runtime: " << format_time_ns(total_session_ns_)
              << " | Total Invocations: " << total_calls_
              << " | Unique Functions: " << profiles_.size() << "\n";
    std::cout << "========================================================================================\n";
    std::cout << std::left << std::setw(38) << "Function Name"
              << std::right << std::setw(10) << "Calls"
              << std::setw(16) << "Total Time"
              << std::setw(16) << "Self Time"
              << std::setw(10) << "% Self"
              << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    size_t display_count = std::min(top_n, sorted.size());
    for (size_t i = 0; i < display_count; i++) {
        const auto& p = sorted[i];
        double pct = (double)p.self_time_ns * 100.0 / baseline_ns;
        std::string fname = p.name;
        if (fname.length() > 36) {
            fname = fname.substr(0, 33) + "...";
        }

        std::ostringstream pct_ss;
        pct_ss << std::fixed << std::setprecision(1) << pct << "%";

        std::cout << std::left << std::setw(38) << fname
                  << std::right << std::setw(10) << p.call_count
                  << std::setw(16) << format_time_ns(p.total_time_ns)
                  << std::setw(16) << format_time_ns(p.self_time_ns)
                  << std::setw(10) << pct_ss.str()
                  << "\n";
    }
    std::cout << "----------------------------------------------------------------------------------------\n";

    if (!sorted.empty()) {
        const auto& top_fn = sorted[0];
        double top_pct = (double)top_fn.self_time_ns * 100.0 / baseline_ns;
        std::cout << "Top Bottleneck: '" << top_fn.name << "' consumed "
                  << std::fixed << std::setprecision(1) << top_pct << "% ("
                  << format_time_ns(top_fn.self_time_ns) << ") of execution time.\n";
    }
    if (display_count < sorted.size()) {
        std::cout << "(" << (sorted.size() - display_count) << " smaller functions omitted; use --top="
                  << sorted.size() << " to see all)\n";
    }
    std::cout << std::endl;
}

int Profiler::run(int argc, char* argv[]) {
    LM::CompileOptions options;
    options.profile = true;
    std::string source_file;
    bool passthrough = false;

    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (passthrough) {
            options.program_args.push_back(arg);
            continue;
        }
        if (arg == "--") {
            passthrough = true;
            continue;
        }
        if (arg == "--help" || arg == "-h") {
            std::cout << "Usage: lymar profile <file.lm> [options] [-- args...]\n\n"
                      << "Options:\n"
                      << "  --sort=self|total|calls   Sort hotspots by self time (default), total time, or call count\n"
                      << "  --top=<N>                 Show top N hotspot functions (default: 25)\n"
                      << "  --flamegraph=<file>       Export folded stack file for Flamegraph generation\n"
                      << "  --json                    Output profiling results in JSON format\n"
                      << "  -I <dir>                  Add module search path\n"
                      << "  -debug                    Enable debug verification\n";
            return 0;
        }
        if (arg.rfind("--flamegraph=", 0) == 0) {
            options.profile_flamegraph = arg.substr(13);
        } else if (arg.rfind("--sort=", 0) == 0) {
            options.profile_sort = arg.substr(7);
        } else if (arg.rfind("--top=", 0) == 0) {
            options.profile_top = std::stoul(arg.substr(6));
        } else if (arg == "--json") {
            options.profile_json = true;
        } else if (arg == "-I" && i + 1 < argc) {
            options.include_dirs.push_back(argv[++i]);
        } else if (arg[0] != '-') {
            if (source_file.empty()) source_file = arg;
            else options.program_args.push_back(arg);
        }
    }

    if (source_file.empty()) {
        std::cerr << "Error: No source file specified for profiling.\n";
        std::cerr << "Usage: lymar profile <file.lm> [options]\n";
        return 1;
    }

    if (!std::filesystem::exists(source_file)) {
        std::cerr << "Error: File '" << source_file << "' does not exist.\n";
        return 1;
    }

    return LM::Compiler::executeFile(source_file, options);
}

} // namespace LM
