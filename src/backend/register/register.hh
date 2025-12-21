#ifndef REGISTER_H
#define REGISTER_H

#include "../../lir/lir.hh"
#include <vector>
#include <string>
#include <variant>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <memory>

namespace Register {

// Register value type
using RegisterValue = std::variant<int64_t, double, bool, std::string, std::nullptr_t>;

// Task states for threadless concurrency
enum class TaskState {
    INIT,
    RUNNING,
    SLEEPING,
    COMPLETED
};

// Task context structure
struct TaskContext {
    TaskState state;
    uint64_t task_id;
    uint64_t sleep_until;
    int64_t counter;
    RegisterValue channel_ptr;
    std::unordered_map<int, RegisterValue> fields;
    
    TaskContext() : state(TaskState::INIT), task_id(0), sleep_until(0), counter(0), channel_ptr(nullptr) {}
    
    // Copy constructor
    TaskContext(const TaskContext& other) 
        : state(other.state), task_id(other.task_id), sleep_until(other.sleep_until), 
          counter(other.counter), channel_ptr(other.channel_ptr), fields(other.fields) {}
};

// Channel structure for threadless communication
struct Channel {
    std::queue<RegisterValue> buffer;
    size_t capacity;
    
    Channel(size_t cap) : capacity(cap) {}
    
    bool push(const RegisterValue& value) {
        if (buffer.size() < capacity) {
            buffer.push(value);
            return true;
        }
        return false;
    }
    
    bool pop(RegisterValue& value) {
        if (!buffer.empty()) {
            value = buffer.front();
            buffer.pop();
            return true;
        }
        return false;
    }
    
    bool has_data() const {
        return !buffer.empty();
    }
    
    size_t size() const {
        return buffer.size();
    }
};

// Scheduler for threadless concurrency
struct Scheduler {
    std::vector<std::unique_ptr<TaskContext>> tasks;
    uint64_t current_time;
    uint64_t next_task_id;
    
    Scheduler() : current_time(0), next_task_id(1) {}
    
    void add_task(std::unique_ptr<TaskContext> task) {
        task->task_id = next_task_id++;
        tasks.push_back(std::move(task));
    }
    
    void tick() {
        current_time++;
        // Simple round-robin scheduling
        for (auto& task : tasks) {
            if (task->state == TaskState::SLEEPING && current_time >= task->sleep_until) {
                task->state = TaskState::RUNNING;
            }
        }
    }
    
    bool has_running_tasks() const {
        for (const auto& task : tasks) {
            if (task->state != TaskState::COMPLETED) {
                return true;
            }
        }
        return false;
    }
};

class RegisterVM {
public:
    RegisterVM();
    
    // Main execution method
    void execute_function(const LIR::LIR_Function& function);
    
    // Register access
    inline const RegisterValue& get_register(LIR::Reg reg) const {
        return registers[reg];
    }
    
    inline void set_register(LIR::Reg reg, const RegisterValue& value) {
        registers[reg] = value;
    }
    
    void reset();
    std::string to_string(const RegisterValue& value) const;

private:
    std::vector<RegisterValue> registers;
    
    // Concurrency management
    std::vector<std::unique_ptr<TaskContext>> task_contexts;
    std::vector<std::unique_ptr<Channel>> channels;
    std::unique_ptr<Scheduler> scheduler;
    uint64_t current_time;
    
    // Helper methods - all inlined for performance
    inline bool is_numeric(const RegisterValue& value) const {
        return std::holds_alternative<int64_t>(value) || 
               std::holds_alternative<double>(value);
    }
    
    inline int64_t to_int(const RegisterValue& value) const {
        if (std::holds_alternative<int64_t>(value)) return std::get<int64_t>(value);
        if (std::holds_alternative<double>(value)) return static_cast<int64_t>(std::get<double>(value));
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? 1 : 0;
        return 0;
    }
    
    inline double to_float(const RegisterValue& value) const {
        if (std::holds_alternative<double>(value)) return std::get<double>(value);
        if (std::holds_alternative<int64_t>(value)) return static_cast<double>(std::get<int64_t>(value));
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? 1.0 : 0.0;
        return 0.0;
    }
    
    inline bool to_bool(const RegisterValue& value) const {
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
        if (std::holds_alternative<int64_t>(value)) return std::get<int64_t>(value) != 0;
        if (std::holds_alternative<double>(value)) return std::get<double>(value) != 0.0;
        if (std::holds_alternative<std::string>(value)) return !std::get<std::string>(value).empty();
        return false;
    }
    

};

} // namespace Register

#endif // REGISTER_H