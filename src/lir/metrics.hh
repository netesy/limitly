#pragma once

#include "lir.hh"
#include <map>
#include <string>

namespace LM {
namespace LIR {

struct PassRecord {
    std::string pass_name;
    size_t instructions_before = 0;
    size_t instructions_after = 0;
    int instruction_delta = 0;

    size_t memory_ops_before = 0;
    size_t memory_ops_after = 0;
    int memory_delta = 0;

    size_t loads_before = 0;
    size_t loads_after = 0;
    int loads_delta = 0;

    size_t stores_before = 0;
    size_t stores_after = 0;
    int stores_delta = 0;

    size_t blocks_before = 0;
    size_t blocks_after = 0;
    int blocks_delta = 0;
};

struct OptimizationReport {
    std::string function_name;

    // Immutable Baseline recorded before any optimization pass
    size_t initial_instructions = 0;
    size_t initial_blocks = 0;
    size_t initial_memory_ops = 0;
    size_t initial_loads = 0;
    size_t initial_stores = 0;

    // Per-pass sequential metrics
    std::vector<PassRecord> passes;

    // Final state
    size_t final_instructions = 0;
    size_t final_blocks = 0;
    size_t final_memory_ops = 0;
    size_t final_loads = 0;
    size_t final_stores = 0;

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
    static size_t count_loads(const LIR_Function& func);
    static size_t count_stores(const LIR_Function& func);
    static size_t count_blocks(const LIR_Function& func);
};

} // namespace LIR
} // namespace LM
