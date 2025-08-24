#include "backend/concurrency/event_loop.hh"
#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>
#include <sys/timerfd.h>
#include <unistd.h>

void test_event_loop_with_timer() {
    std::cout << "Running test: Event Loop with TimerFD... ";
    EventLoop event_loop;
    std::atomic<bool> callback_was_called(false);

    // 1. Create a timer that will fire in 100ms
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    assert(timer_fd != -1);

    itimerspec ts;
    ts.it_value.tv_sec = 0;
    ts.it_value.tv_nsec = 100000000; // 100ms
    ts.it_interval.tv_sec = 0;       // Not periodic
    ts.it_interval.tv_nsec = 0;

    timerfd_settime(timer_fd, 0, &ts, nullptr);

    // 2. Register the timer with the event loop
    event_loop.register_event(timer_fd, [&]() {
        callback_was_called = true;
        // Read from the timerfd to clear it
        uint64_t expirations;
        read(timer_fd, &expirations, sizeof(expirations));
        event_loop.stop();
    });

    // 3. Run the event loop in a separate thread
    std::thread event_thread([&]() {
        event_loop.run();
    });

    event_thread.join();
    close(timer_fd);

    assert(callback_was_called);
    std::cout << "PASSED" << std::endl;
}


int main() {
    test_event_loop_with_timer();

    std::cout << "\nAll event loop tests passed!" << std::endl;
    return 0;
}
