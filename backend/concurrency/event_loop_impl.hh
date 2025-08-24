#ifndef EVENT_LOOP_IMPL_H
#define EVENT_LOOP_IMPL_H

#include <functional>

using EventCallback = std::function<void()>;

class EventLoopImpl {
public:
    virtual ~EventLoopImpl() = default;

    virtual void register_event(int fd, EventCallback callback) = 0;
    virtual void unregister_event(int fd) = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
};

#endif // EVENT_LOOP_IMPL_H
