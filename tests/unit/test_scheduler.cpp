#include "backend/concurrency/scheduler.hh"
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <atomic>

void test_scheduler_basic() {
    std::cout << "Running test: Scheduler Basic... ";
    Scheduler scheduler;
    const int num_tasks = 10;
    std::atomic<int> tasks_executed(0);

    // Create a worker thread
    std::thread worker([&]() {
        Task task;
        while (scheduler.get_next_task(task)) {
            task();
        }
    });

    // Submit tasks from the main thread
    for (int i = 0; i < num_tasks; ++i) {
        scheduler.submit([&]() {
            tasks_executed++;
        });
    }

    // Shutdown the scheduler, which will cause the worker to exit its loop
    scheduler.shutdown();

    worker.join();

    assert(tasks_executed == num_tasks);
    std::cout << "PASSED" << std::endl;
}

int main() {
    test_scheduler_basic();

    std::cout << "\nAll scheduler tests passed!" << std::endl;
    return 0;
}
