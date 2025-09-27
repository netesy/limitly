#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "scheduler.hh"
#include <vector>
#include <thread>
#include <memory>
#include <atomic>
#include <mutex>
#include <deque>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(size_t num_threads, std::shared_ptr<Scheduler> scheduler);
    ~ThreadPool();

    // Non-copyable
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    void start();
    void stop();
    
    // Work distribution methods for parallel tasks
    void setWorkerCount(size_t count);
    size_t getWorkerCount() const { return num_threads_; }
    
    // Submit work directly to specific worker queues for load balancing
    void submitToWorker(size_t worker_id, Task task);
    
    // Get worker statistics for load balancing
    size_t getWorkerQueueSize(size_t worker_id) const;
    size_t getTotalQueuedTasks() const;
    
    // Work-stealing support
    bool stealWork(size_t thief_id, Task& stolen_task);

private:
    void worker_loop(size_t worker_id);
    bool try_get_local_task(size_t worker_id, Task& task);
    bool try_steal_from_others(size_t worker_id, Task& task);

    size_t num_threads_;
    std::shared_ptr<Scheduler> scheduler_;
    std::vector<std::thread> workers_;
    
    // Work-stealing queues - one per worker thread
    std::vector<std::deque<Task>> worker_queues_;
    std::vector<std::unique_ptr<std::mutex>> queue_mutexes_;
    std::vector<std::unique_ptr<std::condition_variable>> queue_conditions_;
    
    std::atomic<bool> shutdown_requested_{false};
    std::atomic<size_t> active_workers_{0};
};

#endif // THREAD_POOL_H
