#pragma once

#include "lir.hh"
#include <map>
#include <string>

namespace LM {
namespace LIR {

struct OptimizationReport {
    std::string function_name;
    size_t initial_instructions = 0;
    size_t final_instructions = 0;

    std::map<std::string, int> pass_deltas;

    size_t memory_ops_before = 0;
    size_t memory_ops_after = 0;

    size_t spills_before = 0;
    size_t spills_after = 0;

    void print() const;
};

struct LIRMetrics {
    size_t total_instructions = 0;
    std::map<LIR_Op, size_t> op_counts;
    size_t total_registers = 0;
    size_t total_functions = 0;

    void print() const;
};

class MetricsCollector {
public:
    static LIRMetrics collect(const LIR_Function& func);
    static size_t count_memory_ops(const LIR_Function& func);
};

} // namespace LIR
} // namespace LM
