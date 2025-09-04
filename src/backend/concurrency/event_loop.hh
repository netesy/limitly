#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "event_loop_impl.hh"
#include <memory>
#include <atomic>

class EventLoop {
public:
    EventLoop();
    ~EventLoop();

    // Non-copyable
    EventLoop(const EventLoop&) = delete;
    EventLoop& operator=(const EventLoop&) = delete;

    void register_event(int fd, EventCallback callback);
    void unregister_event(int fd);
    void run();
    void stop();
    bool is_running() const;

private:
    std::unique_ptr<EventLoopImpl> pimpl_;
    std::atomic<bool> running_{false};
};

#endif // EVENT_LOOP_H
