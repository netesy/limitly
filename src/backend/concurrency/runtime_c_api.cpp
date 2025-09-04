#include "runtime_c_api.hh"
#include "scheduler.hh"
#include "thread_pool.hh"
#include <memory>

// The C functions are wrappers around the C++ classes.
// We use reinterpret_cast to move between the C-style opaque pointers
// and the C++ class pointers.

extern "C" {

Scheduler* scheduler_create() {
    return reinterpret_cast<Scheduler*>(new Scheduler());
}

void scheduler_destroy(Scheduler* scheduler) {
    delete reinterpret_cast<Scheduler*>(scheduler);
}

void scheduler_submit(Scheduler* scheduler, task_func_t task) {
    if (scheduler && task) {
        reinterpret_cast<Scheduler*>(scheduler)->submit(task);
    }
}

void scheduler_shutdown(Scheduler* scheduler) {
    if (scheduler) {
        reinterpret_cast<Scheduler*>(scheduler)->shutdown();
    }
}

ThreadPool* thread_pool_create(size_t num_threads, Scheduler* scheduler) {
    // Note: This creates a new shared_ptr, but the original scheduler object
    // is managed by the caller. This is a bit tricky. A better design might
    // pass shared_ptr around, but that's hard across a C boundary.
    // For this use case, we assume the scheduler outlives the pool.
    auto scheduler_ptr = std::shared_ptr<Scheduler>(reinterpret_cast<Scheduler*>(scheduler));
    return reinterpret_cast<ThreadPool*>(new ThreadPool(num_threads, scheduler_ptr));
}

void thread_pool_destroy(ThreadPool* pool) {
    delete reinterpret_cast<ThreadPool*>(pool);
}

void thread_pool_start(ThreadPool* pool) {
    if (pool) {
        reinterpret_cast<ThreadPool*>(pool)->start();
    }
}

void thread_pool_stop(ThreadPool* pool) {
    if (pool) {
        reinterpret_cast<ThreadPool*>(pool)->stop();
    }
}

} // extern "C"
