#include "benchmark_runner.hh"
#include "process_helper.hh"
#include "lyra_common.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;

namespace LM {

namespace {

void enable_ansi_colors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

std::string format_time_ns(double ns) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    if (ns < 1000.0) {
        ss << ns << " ns/op";
    } else if (ns < 1000000.0) {
        ss << (ns / 1000.0) << " us/op";
    } else if (ns < 1000000000.0) {
        ss << (ns / 1000000.0) << " ms/op";
    } else {
        ss << (ns / 1000000000.0) << " s/op";
    }
    return ss.str();
}

std::string format_ops(double ops) {
    std::ostringstream ss;
    if (ops >= 1000000.0) {
        ss << std::fixed << std::setprecision(1) << (ops / 1000000.0) << "M ops/s";
    } else if (ops >= 1000.0) {
        ss << std::fixed << std::setprecision(1) << (ops / 1000.0) << "k ops/s";
    } else {
        ss << static_cast<long long>(ops) << " ops/s";
    }
    return ss.str();
}

} // namespace

BenchmarkResult BenchmarkRunner::runBenchmark(const std::string& filepath, const std::string& binary_path, const Options& opts) {
    BenchmarkResult res;
    res.file = filepath;
    res.name = fs::path(filepath).filename().string();

    std::string out;

    // 1. Warm-up runs
    for (int w = 0; w < opts.warmup_runs; ++w) {
        int code = Lyra::run_command_capture(binary_path, {"run", filepath}, out);
        if (code != 0) {
            res.success = false;
            res.error_message = out.empty() ? ("Process exited with code " + std::to_string(code)) : out;
            return res;
        }
    }

    // 2. Timed measurement runs
    std::vector<double> samples_ns;
    auto start_all = std::chrono::high_resolution_clock::now();

    while (true) {
        auto t0 = std::chrono::high_resolution_clock::now();
        int code = Lyra::run_command_capture(binary_path, {"run", filepath}, out);
        auto t1 = std::chrono::high_resolution_clock::now();

        if (code != 0) {
            res.success = false;
            res.error_message = out.empty() ? ("Process exited with code " + std::to_string(code)) : out;
            return res;
        }

        double duration_ns = std::chrono::duration<double, std::nano>(t1 - t0).count();
        samples_ns.push_back(duration_ns);

        auto now = std::chrono::high_resolution_clock::now();
        double elapsed_sec = std::chrono::duration<double>(now - start_all).count();

        if (samples_ns.size() >= static_cast<size_t>(opts.min_iterations) && elapsed_sec >= opts.min_duration_sec) {
            break;
        }

        // Safety cap
        if (samples_ns.size() >= 1000 || elapsed_sec >= 15.0) {
            break;
        }
    }

    auto end_all = std::chrono::high_resolution_clock::now();
    res.total_time_sec = std::chrono::duration<double>(end_all - start_all).count();
    res.iterations = samples_ns.size();

    // 3. Statistics
    std::sort(samples_ns.begin(), samples_ns.end());
    res.min_time_ns = samples_ns.front();
    res.max_time_ns = samples_ns.back();
    res.median_time_ns = samples_ns[samples_ns.size() / 2];

    double sum = std::accumulate(samples_ns.begin(), samples_ns.end(), 0.0);
    res.mean_time_ns = sum / samples_ns.size();
    res.ops_per_sec = (res.mean_time_ns > 0) ? (1e9 / res.mean_time_ns) : 0;
    res.success = true;

    return res;
}

int BenchmarkRunner::run(int argc, char** argv) {
    enable_ansi_colors();

    Options opts;
    std::string bin_path = Lyra::find_compiler_path();

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--json") {
            opts.json_output = true;
        } else if (arg == "--no-color") {
            opts.no_color = true;
        } else if (arg == "-v" || arg == "--verbose") {
            opts.verbose = true;
        } else if ((arg == "--warmup" || arg == "-w") && i + 1 < argc) {
            opts.warmup_runs = std::stoi(argv[++i]);
        } else if ((arg == "--time" || arg == "-t") && i + 1 < argc) {
            opts.min_duration_sec = std::stod(argv[++i]);
        } else if ((arg == "--iters" || arg == "-n") && i + 1 < argc) {
            opts.min_iterations = std::stoi(argv[++i]);
        } else if ((arg == "--filter" || arg == "-f") && i + 1 < argc) {
            opts.filter = argv[++i];
        } else if (arg[0] != '-') {
            opts.target_paths.push_back(arg);
        }
    }

    if (opts.target_paths.empty()) {
        if (fs::exists("benchmarks")) {
            opts.target_paths.push_back("benchmarks");
        } else if (fs::exists("tests")) {
            for (const auto& entry : fs::directory_iterator("tests")) {
                std::string fname = entry.path().filename().string();
                if (fname.rfind("benchmark_", 0) == 0 && entry.path().extension() == ".lm") {
                    opts.target_paths.push_back(entry.path().generic_string());
                }
            }
        }
    }

    std::vector<std::string> bench_files;
    for (const auto& p : opts.target_paths) {
        if (fs::is_regular_file(p)) {
            bench_files.push_back(p);
        } else if (fs::is_directory(p)) {
            for (const auto& entry : fs::recursive_directory_iterator(p)) {
                if (entry.is_regular_file() && entry.path().extension() == ".lm") {
                    bench_files.push_back(entry.path().generic_string());
                }
            }
        }
    }

    if (!opts.filter.empty()) {
        std::vector<std::string> filtered;
        for (const auto& f : bench_files) {
            if (f.find(opts.filter) != std::string::npos) {
                filtered.push_back(f);
            }
        }
        bench_files = filtered;
    }

    std::sort(bench_files.begin(), bench_files.end());

    if (bench_files.empty()) {
        std::cerr << "No benchmark files found. Place benchmarks in benchmarks/ or provide a .lm file.\n";
        return 1;
    }

    std::string reset = !opts.no_color ? "\033[0m" : "";
    std::string bold = !opts.no_color ? "\033[1m" : "";
    std::string cyan = !opts.no_color ? "\033[1;36m" : "";
    std::string green = !opts.no_color ? "\033[1;32m" : "";
    std::string red = !opts.no_color ? "\033[1;31m" : "";
    std::string gray = !opts.no_color ? "\033[90m" : "";

    if (!opts.json_output) {
        std::cout << bold << "========================================================================================\n"
                  << "Lymar Benchmark Suite " << reset << "(Warmup: " << opts.warmup_runs
                  << ", Target Window: " << opts.min_duration_sec << "s)\n"
                  << bold << "========================================================================================\n"
                  << std::left << std::setw(42) << "Benchmark"
                  << std::right << std::setw(12) << "Iterations"
                  << std::setw(18) << "Mean Time"
                  << std::setw(16) << "Throughput" << "\n"
                  << gray << "----------------------------------------------------------------------------------------\n" << reset;
    }

    auto suite_start = std::chrono::high_resolution_clock::now();
    size_t pass_count = 0;
    size_t fail_count = 0;

    for (const auto& file : bench_files) {
        auto res = runBenchmark(file, bin_path, opts);

        if (opts.json_output) {
            std::cout << "{\"benchmark\":\"" << res.name << "\",\"file\":\"" << res.file
                      << "\",\"success\":" << (res.success ? "true" : "false")
                      << ",\"iterations\":" << res.iterations
                      << ",\"mean_ns\":" << res.mean_time_ns
                      << ",\"median_ns\":" << res.median_time_ns
                      << ",\"min_ns\":" << res.min_time_ns
                      << ",\"max_ns\":" << res.max_time_ns
                      << ",\"ops_per_sec\":" << res.ops_per_sec
                      << ",\"mean_str\":\"" << format_time_ns(res.mean_time_ns) << "\"}\n";
        } else {
            if (res.success) {
                pass_count++;
                std::cout << std::left << std::setw(42) << (res.file.size() > 40 ? res.file.substr(0, 37) + "..." : res.file)
                          << std::right << std::setw(12) << res.iterations
                          << green << std::setw(18) << format_time_ns(res.mean_time_ns) << reset
                          << cyan << std::setw(16) << format_ops(res.ops_per_sec) << reset
                          << "\n";
            } else {
                fail_count++;
                std::cout << std::left << std::setw(42) << res.file
                          << red << std::right << std::setw(46) << "FAILED" << reset << "\n";
                if (opts.verbose && !res.error_message.empty()) {
                    std::cout << gray << "  " << res.error_message << reset << "\n";
                }
            }
        }
    }

    auto suite_end = std::chrono::high_resolution_clock::now();
    double total_sec = std::chrono::duration<double>(suite_end - suite_start).count();

    if (!opts.json_output) {
        std::cout << gray << "----------------------------------------------------------------------------------------\n" << reset;
        std::cout << bold << "Benchmark finished: " << pass_count << " passed, " << fail_count << " failed in "
                  << std::fixed << std::setprecision(2) << total_sec << "s.\n" << reset;
    }

    return (fail_count > 0) ? 1 : 0;
}

} // namespace LM
