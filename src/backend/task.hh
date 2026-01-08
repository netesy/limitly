#ifndef TASK_H
#define TASK_H

#include "register_value.hh"
#include <unordered_map>
#include <cstdint>

namespace Register {

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
    
    // Store task body as instruction range
    int64_t body_start_pc;  // Start instruction index
    int64_t body_end_pc;    // End instruction index
    
    TaskContext() 
        : state(TaskState::INIT), task_id(0), sleep_until(0), 
          counter(0), channel_ptr(nullptr),
          body_start_pc(-1), body_end_pc(-1) {}
    
    TaskContext(const TaskContext& other) 
        : state(other.state), task_id(other.task_id), 
          sleep_until(other.sleep_until), counter(other.counter), 
          channel_ptr(other.channel_ptr), fields(other.fields),
          body_start_pc(other.body_start_pc), 
          body_end_pc(other.body_end_pc) {}
};

} // namespace Register

#endif // TASK_H
