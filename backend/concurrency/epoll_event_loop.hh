#ifndef EPOLL_EVENT_LOOP_H
#define EPOLL_EVENT_LOOP_H

#include "event_loop_impl.hh"
#include <map>
#include <vector>

class EpollEventLoop : public EventLoopImpl {
public:
    EpollEventLoop();
    ~EpollEventLoop() override;

    void register_event(int fd, EventCallback callback) override;
    void unregister_event(int fd) override;
    void run() override;
    void stop() override;

private:
    int epoll_fd_;
    bool running_;
    std::map<int, EventCallback> callbacks_;
};

#endif // EPOLL_EVENT_LOOP_H
