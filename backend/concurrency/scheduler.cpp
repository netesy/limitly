#include "scheduler.hh"

Scheduler::Scheduler() {}

Scheduler::~Scheduler() {
    // Ensure the channel is closed on destruction to prevent hangs.
    shutdown();
}

void Scheduler::submit(Task task) {
    task_queue_.send(std::move(task));
}

bool Scheduler::get_next_task(Task& task) {
    return task_queue_.receive(task);
}

void Scheduler::shutdown() {
    task_queue_.close();
}
