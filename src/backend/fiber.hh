#ifndef FIBER_H
#define FIBER_H

#include "task.hh"
#include <cstdint>

namespace LM {
namespace Backend {

// Fiber states for execution management
enum class FiberState {
    CREATED,
    RUNNING,
    SUSPENDED,
    COMPLETED,
    FAILED
};

// Fiber class for managing execution contexts
struct Fiber {
    uint64_t fiber_id;
    FiberState state;
    TaskContext* task_context;
    uint64_t current_instruction;
    uint64_t suspend_count;
    
    // Fiber stack/context information
    void* stack_pointer;
    size_t stack_size;
    
    Fiber(uint64_t id, TaskContext* context) 
        : fiber_id(id), state(FiberState::CREATED), task_context(context),
          current_instruction(0), suspend_count(0), stack_pointer(nullptr), stack_size(0) {
        if (task_context) {
            current_instruction = task_context->body_start_pc;
        }
    }
    
    // Fiber control methods
    void suspend() {
        if (state == FiberState::RUNNING) {
            state = FiberState::SUSPENDED;
            suspend_count++;
        }
    }
    
    void resume() {
        if (state == FiberState::SUSPENDED) {
            state = FiberState::RUNNING;
        }
    }
    
    void complete() {
        state = FiberState::COMPLETED;
    }
    
    void fail() {
        state = FiberState::FAILED;
    }
    
    // Check fiber state
    bool is_running() const { return state == FiberState::RUNNING; }
    bool is_suspended() const { return state == FiberState::SUSPENDED; }
    bool is_completed() const { return state == FiberState::COMPLETED; }
    bool is_failed() const { return state == FiberState::FAILED; }
    bool is_finished() const { return is_completed() || is_failed(); }
    
    // Get next instruction to execute
    uint64_t get_next_instruction() const {
        return current_instruction;
    }
    
    // Advance to next instruction
    void advance_instruction() {
        if (task_context && current_instruction < task_context->body_end_pc) {
            current_instruction++;
        }
    }
    
    // Check if fiber has more instructions
    bool has_more_instructions() const {
        return task_context && current_instruction <= task_context->body_end_pc;
    }
};

} // namespace Backend
} // namespace LM

#endif // FIBER_H
