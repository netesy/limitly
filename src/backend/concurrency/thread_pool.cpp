#include "thread_pool.hh"
#include <algorithm>
#include <random>

ThreadPool::ThreadPool(size_t num_threads, std::shared_ptr<Scheduler> scheduler)
    : num_threads_(num_threads), scheduler_(std::move(scheduler)) {
    // Initialize work-stealing queues
    worker_queues_.resize(num_threads_);
    queue_mutexes_.reserve(num_threads_);
    queue_conditions_.reserve(num_threads_);
    
    for (size_t i = 0; i < num_threads_; ++i) {
        queue_mutexes_.emplace_back(std::make_unique<std::mutex>());
        queue_conditions_.emplace_back(std::make_unique<std::condition_variable>());
    }
}

ThreadPool::~ThreadPool() {
    stop();
    
    // Ensure threads are stopped and joined on destruction.
    // The check for joinable() is important in case stop() was already called.
    for (auto& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::start() {
    shutdown_requested_.store(false);
    active_workers_.store(0);
    
    workers_.reserve(num_threads_);
    for (size_t i = 0; i < num_threads_; ++i) {
        workers_.emplace_back([this, i] { worker_loop(i); });
    }
}

void ThreadPool::stop() {
    shutdown_requested_.store(true);
    scheduler_->shutdown();
    
    // Wake up all workers
    for (auto& condition : queue_conditions_) {
        condition->notify_all();
    }
    
    // Wait for all workers to finish
    for (auto& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    
    workers_.clear();
}

void ThreadPool::setWorkerCount(size_t count) {
    if (count == num_threads_) return;
    
    // Stop current workers
    stop();
    
    // Resize data structures
    num_threads_ = count;
    worker_queues_.resize(num_threads_);
    
    // Clear and resize mutex/condition vectors
    queue_mutexes_.clear();
    queue_conditions_.clear();
    queue_mutexes_.reserve(num_threads_);
    queue_conditions_.reserve(num_threads_);
    
    for (size_t i = 0; i < num_threads_; ++i) {
        queue_mutexes_.emplace_back(std::make_unique<std::mutex>());
        queue_conditions_.emplace_back(std::make_unique<std::condition_variable>());
    }
    
    // Clear any existing queues
    for (auto& queue : worker_queues_) {
        queue.clear();
    }
    
    // Restart with new worker count
    start();
}

void ThreadPool::submitToWorker(size_t worker_id, Task task) {
    if (worker_id >= num_threads_) {
        // Fallback to round-robin distribution
        worker_id = worker_id % num_threads_;
    }
    
    {
        std::lock_guard<std::mutex> lock(*queue_mutexes_[worker_id]);
        worker_queues_[worker_id].push_back(std::move(task));
    }
    queue_conditions_[worker_id]->notify_one();
}

size_t ThreadPool::getWorkerQueueSize(size_t worker_id) const {
    if (worker_id >= num_threads_) return 0;
    
    std::lock_guard<std::mutex> lock(*queue_mutexes_[worker_id]);
    return worker_queues_[worker_id].size();
}

size_t ThreadPool::getTotalQueuedTasks() const {
    size_t total = 0;
    for (size_t i = 0; i < num_threads_; ++i) {
        total += getWorkerQueueSize(i);
    }
    return total;
}

bool ThreadPool::stealWork(size_t thief_id, Task& stolen_task) {
    // Try to steal from other workers' queues
    for (size_t i = 1; i < num_threads_; ++i) {
        size_t victim_id = (thief_id + i) % num_threads_;
        
        std::unique_lock<std::mutex> lock(*queue_mutexes_[victim_id], std::try_to_lock);
        if (lock.owns_lock() && !worker_queues_[victim_id].empty()) {
            // Steal from the back of the victim's queue (LIFO for better cache locality)
            stolen_task = std::move(worker_queues_[victim_id].back());
            worker_queues_[victim_id].pop_back();
            return true;
        }
    }
    return false;
}

void ThreadPool::worker_loop(size_t worker_id) {
    active_workers_.fetch_add(1);
    
    Task task;
    while (!shutdown_requested_.load()) {
        bool got_task = false;
        
        // First, try to get a task from our local queue
        if (try_get_local_task(worker_id, task)) {
            got_task = true;
        }
        // If no local task, try to steal from other workers
        else if (try_steal_from_others(worker_id, task)) {
            got_task = true;
        }
        // If no work to steal, try the global scheduler
        else if (scheduler_->get_next_task(task)) {
            got_task = true;
        }
        
        if (got_task) {
            try {
                task();
            } catch (...) {
                // In a real system, we'd want to log this exception.
                // For now, we'll just ignore it to prevent one failed task
                // from taking down a worker thread.
            }
        } else {
            // No work available, wait for new work or shutdown
            std::unique_lock<std::mutex> lock(*queue_mutexes_[worker_id]);
            queue_conditions_[worker_id]->wait_for(lock, std::chrono::milliseconds(10), 
                [this, worker_id] { 
                    return shutdown_requested_.load() || !worker_queues_[worker_id].empty(); 
                });
        }
    }
    
    active_workers_.fetch_sub(1);
}

bool ThreadPool::try_get_local_task(size_t worker_id, Task& task) {
    std::lock_guard<std::mutex> lock(*queue_mutexes_[worker_id]);
    if (!worker_queues_[worker_id].empty()) {
        // Take from the front of our own queue (FIFO for our own work)
        task = std::move(worker_queues_[worker_id].front());
        worker_queues_[worker_id].pop_front();
        return true;
    }
    return false;
}

bool ThreadPool::try_steal_from_others(size_t worker_id, Task& task) {
    return stealWork(worker_id, task);
}
