#ifndef REGISTER_H
#define REGISTER_H

#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../types.hh"
#include "../../memory/memory.hh"
#include "../value.hh"
#include "../task.hh"
#include "../channel.hh"
#include "../shared_cell.hh"
#include "../scheduler.hh"
#include "../fiber.hh"
#include "../register_value.hh"
#include <vector>
#include <string>
#include <variant>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <memory>
#include <atomic>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

    class RegisterVM {
public:
    RegisterVM();
    
    void execute_instructions(const LIR::LIR_Function& function, size_t start_pc, size_t end_pc);
    // Main execution method
    void execute_function(const LIR::LIR_Function& function);
    
    // Execute LIRFunction (new method)
    void execute_lir_function(const LIR::LIRFunction& function);
    
    // Register access
    inline const RegisterValue& get_register(LIR::Reg reg) const {
        return registers[reg];
    }
    
    inline void set_register(LIR::Reg reg, const RegisterValue& value) {
        registers[reg] = value;
    }
    
    void reset();
    std::string to_string(const RegisterValue& value) const;
    
    // Execute task body using instruction range
    void execute_task_body(TaskContext* task, const LIR::LIR_Function& function);
    
    // Fiber management methods
    uint64_t create_fiber(std::unique_ptr<TaskContext> task);
    void suspend_fiber(uint64_t fiber_id);
    void resume_fiber(uint64_t fiber_id);
    void execute_fiber_step();
    bool has_active_fibers() const;
    Fiber* get_current_fiber();
    
    // Set current function for task execution
    void set_current_function(const LIR::LIR_Function* func) { current_function_ = func; }

private:
    std::vector<RegisterValue> registers;
    
    // Error information structure for primitive error handling
    struct ErrorInfo {
        std::string errorType;
        std::string message;
        bool isError;
        
        ErrorInfo() : isError(false) {}
        ErrorInfo(const std::string& type, const std::string& msg, bool error = true)
            : errorType(type), message(msg), isError(error) {}
    };
    
    // Error table mapping error IDs to error information
    std::unordered_map<int64_t, ErrorInfo> error_table;
    
    // Error storage for proper error handling (legacy compatibility)
    std::unordered_map<LIR::Reg, std::shared_ptr<ErrorValue>> error_storage;
    
    // Current function for task execution
    const LIR::LIR_Function* current_function_ = nullptr;
    
    // Global variable storage
    std::unordered_map<std::string, RegisterValue> globals_;
    
    // Type system instance
    std::unique_ptr<TypeSystem> type_system;
    
    // Concurrency management
    std::vector<std::unique_ptr<TaskContext>> task_contexts;
    std::vector<std::unique_ptr<LM::Backend::Channel>> channels;
    std::unique_ptr<Scheduler> scheduler;
    uint64_t current_time;
    
    // Shared atomic variables for true shared state across tasks
    std::unordered_map<std::string, std::atomic<int64_t>> shared_variables;
    
    // SharedCell operations for parallel execution
    std::unordered_map<uint32_t, std::unique_ptr<SharedCell>> shared_cells;
    
    // Frame instance storage for VM execution
    std::unordered_map<uint64_t, FrameInstancePtr> frame_instances;
    uint64_t next_frame_id = 1;
    
    // Atomic variables and work queues for lock-free parallel operations
    std::atomic<int64_t> default_atomic{0};
    std::vector<std::queue<uint64_t>> work_queues;
    std::atomic<uint64_t> work_queue_counter{0};
    
    // Argument stack for indirect calls and parameter passing
    std::vector<RegisterValue> argument_stack;

    // Instruction count limit to prevent infinite loops
    static constexpr uint64_t MAX_INSTRUCTIONS = 100000;
    uint64_t instruction_count = 0;
    
    // Helper methods - all inlined for performance
    inline LIR::Type get_register_type(LIR::Reg reg) const {
        if (!current_function_) return LIR::Type::Void;
        auto it = current_function_->register_types.find(reg);
        return (it != current_function_->register_types.end()) ? it->second : LIR::Type::Void;
    }
    
    inline bool is_numeric(const RegisterValue& value) const {
        return std::holds_alternative<int64_t>(value) || 
               std::holds_alternative<uint64_t>(value) ||
               std::holds_alternative<double>(value);
    }
    
    inline int64_t to_int(const RegisterValue& value) const {
        if (std::holds_alternative<int64_t>(value)) return std::get<int64_t>(value);
        if (std::holds_alternative<uint64_t>(value)) return static_cast<int64_t>(std::get<uint64_t>(value));
        if (std::holds_alternative<double>(value)) return static_cast<int64_t>(std::get<double>(value));
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? 1 : 0;
        return 0;
    }
    
    inline uint64_t to_uint(const RegisterValue& value) const {
        if (std::holds_alternative<uint64_t>(value)) return std::get<uint64_t>(value);
        if (std::holds_alternative<int64_t>(value)) return static_cast<uint64_t>(std::get<int64_t>(value));
        if (std::holds_alternative<double>(value)) return static_cast<uint64_t>(std::get<double>(value));
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? 1 : 0;
        return 0;
    }
    
    inline double to_float(const RegisterValue& value) const {
        if (std::holds_alternative<double>(value)) return std::get<double>(value);
        if (std::holds_alternative<int64_t>(value)) return static_cast<double>(std::get<int64_t>(value));
        if (std::holds_alternative<uint64_t>(value)) return static_cast<double>(std::get<uint64_t>(value));
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? 1.0 : 0.0;
        return 0.0;
    }
    
    inline bool to_bool(const RegisterValue& value) const {
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
        if (std::holds_alternative<int64_t>(value)) return std::get<int64_t>(value) != 0;
        if (std::holds_alternative<uint64_t>(value)) return std::get<uint64_t>(value) != 0;
        if (std::holds_alternative<double>(value)) return std::get<double>(value) != 0.0;
        if (std::holds_alternative<std::string>(value)) return !std::get<std::string>(value).empty();
        return false;
    }
    
    // Error handling methods
    ValuePtr createErrorValue(const std::string& errorType, const std::string& message = "");
    ValuePtr createSuccessValue(const RegisterValue& value);
    bool isErrorValue(LIR::Reg reg) const;
    
    // Frame management methods
    FrameInstancePtr createFrameInstance(const std::string& frame_type);
    void setFrameField(FrameInstancePtr frame, size_t index, const RegisterValue& value);
    RegisterValue getFrameField(FrameInstancePtr frame, size_t index) const;
    

};

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

#endif // REGISTER_H