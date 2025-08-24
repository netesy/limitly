#ifndef IOCP_EVENT_LOOP_H
#define IOCP_EVENT_LOOP_H

#include "event_loop_impl.hh"

class IocpEventLoop : public EventLoopImpl {
public:
    IocpEventLoop();
    ~IocpEventLoop() override;

    void register_event(int fd, EventCallback callback) override;
    void unregister_event(int fd) override;
    void run() override;
    void stop() override;
};

#endif // IOCP_EVENT_LOOP_H
