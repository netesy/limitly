#include "metrics.hh"
#include <iostream>
#include <iomanip>

namespace LM {
namespace LIR {

void OptimizationReport::print() const {
    std::cout << "\n=== LIR Optimization Report ===\n\n";
    std::cout << "Function: " << (function_name.empty() ? "<anonymous>" : function_name) << "\n\n";
    std::cout << "Initial instructions:        " << initial_instructions << "\n\n";

    for (const auto& [pass, delta] : pass_deltas) {
        if (delta != 0) {
            std::cout << std::left << std::setw(28) << (pass + ":")
                      << std::right << std::setw(6) << (delta > 0 ? ("+" + std::to_string(delta)) : std::to_string(delta))
                      << "\n";
        }
    }

    std::cout << "\nFinal instructions:           " << final_instructions << "\n\n";

    std::cout << "Spills:\n";
    std::cout << "  before: " << spills_before << "\n";
    std::cout << "  after:   " << spills_after << "\n\n";

    std::cout << "Memory operations:\n";
    std::cout << "  before: " << memory_ops_before << "\n";
    std::cout << "  after:  " << memory_ops_after << "\n";
    std::cout << "===============================\n\n";
}

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

size_t MetricsCollector::count_memory_ops(const LIR_Function& func) {
    size_t count = 0;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Load || inst.op == LIR_Op::Store ||
            inst.op == LIR_Op::MemoryLoad || inst.op == LIR_Op::MemoryStore) {
            count++;
        }
    }
    return count;
}

} // namespace LIR
} // namespace LM
