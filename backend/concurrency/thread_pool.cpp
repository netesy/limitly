#include "thread_pool.hh"

ThreadPool::ThreadPool(size_t num_threads, std::shared_ptr<Scheduler> scheduler)
    : num_threads_(num_threads), scheduler_(std::move(scheduler)) {
}

ThreadPool::~ThreadPool() {
    // Ensure threads are stopped and joined on destruction.
    // The check for joinable() is important in case stop() was already called.
    for (auto& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::start() {
    workers_.reserve(num_threads_);
    for (size_t i = 0; i < num_threads_; ++i) {
        workers_.emplace_back([this] { worker_loop(); });
    }
}

void ThreadPool::stop() {
    scheduler_->shutdown();
}

void ThreadPool::worker_loop() {
    Task task;
    while (scheduler_->get_next_task(task)) {
        try {
            task();
        } catch (...) {
            // In a real system, we'd want to log this exception.
            // For now, we'll just ignore it to prevent one failed task
            // from taking down a worker thread.
        }
    }
}
