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
#include "../../runtime/runtime.h"
#include "../../runtime/runtime_value.h"
#include <vector>
#include <string>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <memory>
#include <atomic>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

    // Forward declaration of the helper
    ValuePtr register_to_value_ptr(RegisterValue rv);

    class RegisterVM {
public:
    RegisterVM();
    
    void execute_instructions(const LIR::LIR_Function& function, size_t start_pc, size_t end_pc);
    void execute_function(const LIR::LIR_Function& function);
    void execute_lir_function(const LIR::LIRFunction& function);
    
    inline const RegisterValue& get_register(LIR::Reg reg) const {
        return registers[reg];
    }
    
    inline void set_register(LIR::Reg reg, const RegisterValue& value) {
        registers[reg] = value;
    }
    
    void reset();
    std::string to_string(const RegisterValue& value) const;
    
    void execute_task_body(TaskContext* task, const LIR::LIR_Function& function);
    
    uint64_t create_fiber(std::unique_ptr<TaskContext> task);
    void suspend_fiber(uint64_t fiber_id);
    void resume_fiber(uint64_t fiber_id);
    void execute_fiber_step();
    bool has_active_fibers() const;
    Fiber* get_current_fiber();
    
    void set_current_function(const LIR::LIR_Function* func) { current_function_ = func; }

private:
    // Opcode execution modules
    void execute_arithmetic(const LIR::LIR_Inst* pc);
    void execute_comparison(const LIR::LIR_Inst* pc);
    void execute_collections(const LIR::LIR_Inst* pc);
    void execute_frames(const LIR::LIR_Inst* pc);
    void execute_control_flow(const LIR::LIR_Inst*& pc, const LIR::LIR_Function& function);
    void execute_io(const LIR::LIR_Inst* pc);
    void execute_concurrency(const LIR::LIR_Inst* pc);
    void execute_bitwise(const LIR::LIR_Inst* pc);
    void execute_modules(const LIR::LIR_Inst* pc);
    void execute_objects(const LIR::LIR_Inst* pc);
    void execute_strings(const LIR::LIR_Inst* pc);
    void execute_calls(const LIR::LIR_Inst* pc);
    void execute_cast(const LIR::LIR_Inst* pc);

    std::vector<RegisterValue> registers;
    
    struct ErrorInfo {
        std::string errorType;
        std::string message;
        bool isError;
        
        ErrorInfo() : isError(false) {}
        ErrorInfo(const std::string& type, const std::string& msg, bool error = true)
            : errorType(type), message(msg), isError(error) {}
    };
    
    std::unordered_map<int64_t, ErrorInfo> error_table;
    
    const LIR::LIR_Function* current_function_ = nullptr;
    std::unordered_map<std::string, RegisterValue> globals_;
    std::unique_ptr<TypeSystem> type_system;
    
    std::vector<std::unique_ptr<TaskContext>> task_contexts;
    std::vector<std::unique_ptr<LM::Backend::Channel>> channels;
    std::unique_ptr<Scheduler> scheduler;
    uint64_t current_time;
    
    std::unordered_map<std::string, std::atomic<int64_t>> shared_variables;
    std::unordered_map<uint32_t, std::unique_ptr<SharedCell>> shared_cells;
    
    std::unordered_map<uint64_t, FrameInstancePtr> frame_instances;
    uint64_t next_frame_id = 1;
    
    std::atomic<int64_t> default_atomic{0};
    std::vector<std::queue<uint64_t>> work_queues;
    std::atomic<uint64_t> work_queue_counter{0};
    
    std::vector<RegisterValue> argument_stack;

    static constexpr uint64_t MAX_INSTRUCTIONS = 1000000000;
    uint64_t instruction_count = 0;
    
    inline LIR::Type get_register_type(LIR::Reg reg) const {
        if (!current_function_) return LIR::Type::Void;
        auto it = current_function_->register_types.find(reg);
        return (it != current_function_->register_types.end()) ? it->second : LIR::Type::Void;
    }
    
    inline bool is_numeric(const RegisterValue& value) const {
        return is_integer(value) || is_float(value);
    }
    
    inline int64_t to_int(const RegisterValue& value) const {
        return as_i64(value);
    }
    
    inline uint64_t to_uint(const RegisterValue& value) const {
        return as_u64(value);
    }
    
    inline double to_float(const RegisterValue& value) const {
        return as_float(value);
    }
    
    inline bool to_bool(const RegisterValue& value) const {
        if (IS_BOOL(value)) return UNBOX_BOOL(value);
        if (IS_NIL(value)) return false;
        if (is_integer(value)) return as_i128(value) != 0;
        if (IS_PTR(value)) {
            ObjHeader* h = (ObjHeader*)UNBOX_PTR(value);
            if (h->type_id == TYPE_FLOAT) return ((ObjFloat*)h)->value != 0.0;
            if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                LmBox* box = (LmBox*)h;
                return box->value.as_ptr && ((char*)box->value.as_ptr)[0] != '\0';
            }
            return true;
        }
        return false;
    }
    
    bool isErrorValue(LIR::Reg reg) const;
    
    FrameInstancePtr createFrameInstance(const std::string& frame_type);
    void setFrameField(FrameInstancePtr frame, size_t index, const RegisterValue& value);
    RegisterValue getFrameField(FrameInstancePtr frame, size_t index) const;
};

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

#endif // REGISTER_H
