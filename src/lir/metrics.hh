#pragma once

#include "lir.hh"
#include <map>
#include <string>

namespace LM {
namespace LIR {

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
};

} // namespace LIR
} // namespace LM
