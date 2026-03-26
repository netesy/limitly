#include "metrics.hh"
#include <iostream>

namespace LM {
namespace LIR {

void LIRMetrics::print() const {
    std::cout << "=== LIR Metrics ===\n";
    std::cout << "Total Instructions: " << total_instructions << "\n";
    std::cout << "Total Registers:    " << total_registers << "\n";
    std::cout << "Opcode Distribution:\n";
    for (const auto& [op, count] : op_counts) {
        std::cout << "  " << lir_op_to_string(op) << ": " << count << "\n";
    }
    std::cout << "===================\n";
}

LIRMetrics MetricsCollector::collect(const LIR_Function& func) {
    LIRMetrics metrics;
    metrics.total_instructions = func.instructions.size();
    metrics.total_registers = func.register_count;

    for (const auto& inst : func.instructions) {
        metrics.op_counts[inst.op]++;
    }

    return metrics;
}

} // namespace LIR
} // namespace LM
