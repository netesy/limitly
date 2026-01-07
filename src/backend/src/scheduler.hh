#pragma once
#include <vector>
#include <memory>
#include "task.hh"

// Forward declarations
struct Fiber;

// Scheduler for threadless concurrency
struct Scheduler {
    std::vector<std::unique_ptr<TaskContext>> tasks;
    uint64_t current_time;
    uint64_t next_task_id;
    
    Scheduler() : current_time(0), next_task_id(1) {}
    
    void add_task(std::unique_ptr<TaskContext> task) {
        // Don't reassign task_id - it's already set correctly during initialization
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

    // Static methods for fiber management
    static void suspend_current();
    static void resume(Fiber* fiber);
};
