#include "metrics.hh"
#include <iostream>
#include <iomanip>

namespace LM {
namespace LIR {

void OptimizationReport::print() const {
    std::cout << "\n=== LIR Optimization Report ===\n\n";
    std::cout << "Function: " << (function_name.empty() ? "<anonymous>" : function_name) << "\n\n";
    std::cout << "Original LIR\n";
    std::cout << "  Instructions:      " << initial_instructions << "\n";
    std::cout << "  Basic blocks:       " << initial_blocks << "\n";
    std::cout << "  Memory operations:  " << initial_memory_ops << "\n";
    std::cout << "  Loads:              " << initial_loads << "\n";
    std::cout << "  Stores:             " << initial_stores << "\n\n";

    std::cout << std::left << std::setw(30) << "Pass"
              << std::right << std::setw(10) << "Instr Δ"
              << std::right << std::setw(10) << "Mem Δ"
              << std::right << std::setw(10) << "Blocks Δ" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& rec : passes) {
        std::cout << std::left << std::setw(30) << rec.pass_name
                  << std::right << std::setw(10) << (rec.instruction_delta > 0 ? ("+" + std::to_string(rec.instruction_delta)) : std::to_string(rec.instruction_delta))
                  << std::right << std::setw(10) << (rec.memory_delta > 0 ? ("+" + std::to_string(rec.memory_delta)) : std::to_string(rec.memory_delta))
                  << std::right << std::setw(10) << (rec.blocks_delta > 0 ? ("+" + std::to_string(rec.blocks_delta)) : std::to_string(rec.blocks_delta))
                  << "\n";
    }

    std::cout << "\nFinal LIR\n";
    std::cout << "  Instructions:      " << final_instructions << "\n";
    std::cout << "  Basic blocks:       " << final_blocks << "\n";
    std::cout << "  Memory operations:  " << final_memory_ops << "\n";
    std::cout << "  Loads:              " << final_loads << "\n";
    std::cout << "  Stores:             " << final_stores << "\n\n";

    int total_inst_delta = static_cast<int>(final_instructions) - static_cast<int>(initial_instructions);
    int total_mem_delta = static_cast<int>(final_memory_ops) - static_cast<int>(initial_memory_ops);
    int total_blocks_delta = static_cast<int>(final_blocks) - static_cast<int>(initial_blocks);

    std::cout << "Total:\n";
    std::cout << "  Instructions:      " << (total_inst_delta > 0 ? ("+" + std::to_string(total_inst_delta)) : std::to_string(total_inst_delta)) << "\n";
    std::cout << "  Memory operations: " << (total_mem_delta > 0 ? ("+" + std::to_string(total_mem_delta)) : std::to_string(total_mem_delta)) << "\n";
    std::cout << "  Basic blocks:      " << (total_blocks_delta > 0 ? ("+" + std::to_string(total_blocks_delta)) : std::to_string(total_blocks_delta)) << "\n";
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
    return count_loads(func) + count_stores(func);
}

size_t MetricsCollector::count_loads(const LIR_Function& func) {
    size_t count = 0;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Load || inst.op == LIR_Op::MemoryLoad) {
            count++;
        }
    }
    return count;
}

size_t MetricsCollector::count_stores(const LIR_Function& func) {
    size_t count = 0;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Store || inst.op == LIR_Op::MemoryStore) {
            count++;
        }
    }
    return count;
}

size_t MetricsCollector::count_blocks(const LIR_Function& func) {
    size_t count = 0;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Label) {
            count++;
        }
    }
    return count == 0 ? 1 : count;
}

} // namespace LIR
} // namespace LM
