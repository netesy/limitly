#ifndef KQUEUE_EVENT_LOOP_H
#define KQUEUE_EVENT_LOOP_H

#include "event_loop_impl.hh"
#include <map>
#include <vector>

class KqueueEventLoop : public EventLoopImpl {
public:
    KqueueEventLoop();
    ~KqueueEventLoop() override;

    void register_event(int fd, EventCallback callback) override;
    void unregister_event(int fd) override;
    void run() override;
    void stop() override;

private:
    int kqueue_fd_;
    bool running_;
    std::map<int, EventCallback> callbacks_;
};

#endif // KQUEUE_EVENT_LOOP_H
