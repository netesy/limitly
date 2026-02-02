#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.hh"
#include "fiber.hh"
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>

namespace LM {
namespace Backend {

// Scheduler for fiber-based concurrency
struct Scheduler {
    std::vector<std::unique_ptr<Fiber>> fibers;
    std::queue<uint64_t> ready_queue;
    std::vector<uint64_t> suspended_fibers;
    uint64_t current_time;
    uint64_t next_fiber_id;
    uint64_t current_fiber_id;
    
    Scheduler() : current_time(0), next_fiber_id(1), current_fiber_id(0) {}
    
    // Add a new fiber to the scheduler
    uint64_t add_fiber(std::unique_ptr<TaskContext> task) {
        auto fiber = std::make_unique<Fiber>(next_fiber_id, task.get());
        uint64_t fiber_id = fiber->fiber_id;
        
        fibers.push_back(std::move(fiber));
        ready_queue.push(fiber_id);
        
        // Store the task context for cleanup
        task_contexts.push_back(std::move(task));
        next_fiber_id++;
        
        return fiber_id;
    }
    
    // Suspend a fiber
    void suspend_fiber(uint64_t fiber_id) {
        Fiber* fiber = get_fiber(fiber_id);
        if (fiber && fiber->is_running()) {
            fiber->suspend();
            suspended_fibers.push_back(fiber_id);
        }
    }
    
    // Resume a suspended fiber
    void resume_fiber(uint64_t fiber_id) {
        Fiber* fiber = get_fiber(fiber_id);
        if (fiber && fiber->is_suspended()) {
            fiber->resume();
            ready_queue.push(fiber_id);
            
            // Remove from suspended list
            auto it = std::find(suspended_fibers.begin(), suspended_fibers.end(), fiber_id);
            if (it != suspended_fibers.end()) {
                suspended_fibers.erase(it);
            }
        }
    }
    
    // Get the next fiber to execute
    Fiber* get_next_fiber() {
        if (ready_queue.empty()) {
            return nullptr;
        }
        
        uint64_t fiber_id = ready_queue.front();
        ready_queue.pop();
        current_fiber_id = fiber_id;
        
        return get_fiber(fiber_id);
    }
    
    // Execute one instruction of the current fiber
    void execute_current_fiber_step() {
        Fiber* fiber = get_fiber(current_fiber_id);
        if (fiber && fiber->is_running() && fiber->has_more_instructions()) {
            // Advance instruction pointer
            fiber->advance_instruction();
            
            // Check if fiber is completed
            if (!fiber->has_more_instructions()) {
                fiber->complete();
            } else {
                // Re-queue for next execution cycle
                ready_queue.push(current_fiber_id);
            }
        }
    }
    
    // Main scheduler tick - process time-based events
    void tick() {
        current_time++;
        
        // Check sleeping tasks and wake them up
        for (auto& fiber : fibers) {
            if (fiber->task_context && 
                fiber->task_context->state == TaskState::SLEEPING && 
                current_time >= fiber->task_context->sleep_until) {
                
                fiber->task_context->state = TaskState::RUNNING;
                if (fiber->is_suspended()) {
                    resume_fiber(fiber->fiber_id);
                }
            }
        }
    }
    
    // Check if there are runnable fibers
    bool has_runnable_fibers() const {
        return !ready_queue.empty() || !suspended_fibers.empty();
    }
    
    // Check if there are active fibers (not completed/failed)
    bool has_active_fibers() const {
        for (const auto& fiber : fibers) {
            if (!fiber->is_finished()) {
                return true;
            }
        }
        return false;
    }
    
    // Get fiber by ID
    Fiber* get_fiber(uint64_t fiber_id) {
        for (auto& fiber : fibers) {
            if (fiber->fiber_id == fiber_id) {
                return fiber.get();
            }
        }
        return nullptr;
    }
    
    // Get current executing fiber
    Fiber* get_current_fiber() {
        return get_fiber(current_fiber_id);
    }
    
    // Get statistics
    size_t get_total_fibers() const { return fibers.size(); }
    size_t get_ready_count() const { return ready_queue.size(); }
    size_t get_suspended_count() const { return suspended_fibers.size(); }
    
    // Static methods for channel operations
    static void suspend_current();
    static void resume(Fiber* fiber);
    
private:
    std::vector<std::unique_ptr<TaskContext>> task_contexts;
    static Scheduler* instance_; // For static methods access
};

} // namespace Backend
} // namespace LM

#endif // SCHEDULER_H
