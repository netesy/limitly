#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "scheduler.hh"
#include <vector>
#include <thread>
#include <memory>

class ThreadPool {
public:
    ThreadPool(size_t num_threads, std::shared_ptr<Scheduler> scheduler);
    ~ThreadPool();

    // Non-copyable
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    void start();
    void stop();

private:
    void worker_loop();

    size_t num_threads_;
    std::shared_ptr<Scheduler> scheduler_;
    std::vector<std::thread> workers_;
};

#endif // THREAD_POOL_H
