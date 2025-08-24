#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <functional>
#include <map>
#include <vector>

using EventCallback = std::function<void()>;

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

private:
    int epoll_fd_;
    bool running_;
    std::map<int, EventCallback> callbacks_;
};

#endif // EVENT_LOOP_H
