#ifndef LYMAR_BENCHMARK_RUNNER_HH
#define LYMAR_BENCHMARK_RUNNER_HH

#include <string>
#include <vector>

namespace LM {

struct BenchmarkResult {
    std::string name;
    std::string file;
    size_t iterations = 0;
    double total_time_sec = 0.0;
    double mean_time_ns = 0.0;
    double median_time_ns = 0.0;
    double min_time_ns = 0.0;
    double max_time_ns = 0.0;
    double ops_per_sec = 0.0;
    bool success = true;
    std::string error_message;
};

class BenchmarkRunner {
public:
    struct Options {
        int warmup_runs = 2;
        double min_duration_sec = 0.5; // Target measurement duration per benchmark
        int min_iterations = 3;
        std::string filter;
        bool verbose = false;
        bool json_output = false;
        bool no_color = false;
        std::vector<std::string> target_paths;
    };

    static int run(int argc, char** argv);
    static BenchmarkResult runBenchmark(const std::string& filepath, const std::string& binary_path, const Options& opts);
};

} // namespace LM

#endif // LYMAR_BENCHMARK_RUNNER_HH
