#include "backend/concurrency/thread_pool.hh"
#include "backend/concurrency/scheduler.hh"
#include <iostream>
#include <memory>
#include <atomic>
#include <cassert>

void test_thread_pool_execution() {
    std::cout << "Running test: Thread Pool Execution... ";

    const int num_threads = 4;
    const int num_tasks = 1000;

    auto scheduler = std::make_shared<Scheduler>();
    ThreadPool pool(num_threads, scheduler);

    std::atomic<int> tasks_executed(0);

    // Start the worker threads
    pool.start();

    // Submit a batch of tasks
    for (int i = 0; i < num_tasks; ++i) {
        scheduler->submit([&]() {
            tasks_executed++;
        });
    }

    // Stop the pool. This will shut down the scheduler, and the destructor
    // of the pool will join the threads. We need a way to wait until
    // all tasks are done. The simplest way is to shut down the scheduler
    // and then wait for the threads to join, which happens in the destructor.
    pool.stop();

    // The ThreadPool destructor will be called here, which joins the threads.
    // We need to add an explicit check here. Let's refine the test.
    // A better test waits for the counter to reach the target value
    // before stopping. But that requires a more complex synchronization.
    // For now, we rely on the fact that stop() + destructor join() will
    // wait for all threads to finish their current task.
    // Let's add a small sleep to give threads time to finish, although this is not ideal.
    // A production system would use a barrier or future/promise.

    // The destructor of 'pool' will be called upon exiting this scope,
    // which will join all threads. Before that, we must ensure all tasks
    // are scheduled and processed.

    // A simple but effective way to wait for completion is to add a final task
    // that signals the main thread. We can use another channel for this.
    Channel<bool> completion_channel;
    scheduler->submit([&]() {
        completion_channel.send(true);
    });

    bool done;
    completion_channel.receive(done);

    // Now stop the pool
    pool.stop();
}

int main() {
    std::cout << "Running test: Thread Pool Execution... ";

    const int num_threads = 4;
    const int num_tasks = 1000;

    auto scheduler = std::make_shared<Scheduler>();
    ThreadPool pool(num_threads, scheduler);

    std::atomic<int> tasks_executed(0);

    pool.start();

    for (int i = 0; i < num_tasks; ++i) {
        scheduler->submit([&]() {
            tasks_executed++;
        });
    }

    // To properly test, we need to wait until the counter is updated.
    // The most reliable way without extra machinery is to poll it.
    // This is not great for production code but fine for a unit test.
    while (tasks_executed < num_tasks) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pool.stop();
    // Destructor will join threads

    assert(tasks_executed == num_tasks);
    std::cout << "PASSED" << std::endl;

    std::cout << "\nAll thread pool tests passed!" << std::endl;
    return 0;
}
