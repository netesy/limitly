#ifndef RUNTIME_C_API_H
#define RUNTIME_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

// Opaque pointers to the C++ objects
typedef struct Scheduler Scheduler;
typedef struct ThreadPool ThreadPool;

// Task function pointer type
typedef void (*task_func_t)(void);

// Scheduler functions
Scheduler* scheduler_create();
void scheduler_destroy(Scheduler* scheduler);
void scheduler_submit(Scheduler* scheduler, task_func_t task);
void scheduler_shutdown(Scheduler* scheduler);

// ThreadPool functions
ThreadPool* thread_pool_create(size_t num_threads, Scheduler* scheduler);
void thread_pool_destroy(ThreadPool* pool);
void thread_pool_start(ThreadPool* pool);
void thread_pool_stop(ThreadPool* pool);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_C_API_H
