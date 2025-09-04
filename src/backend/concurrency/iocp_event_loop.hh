#ifndef IOCP_EVENT_LOOP_H
#define IOCP_EVENT_LOOP_H

#include "event_loop_impl.hh"
#include <map>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#endif

class IocpEventLoop : public EventLoopImpl {
public:
    IocpEventLoop();
    ~IocpEventLoop() override;

    void register_event(int fd, EventCallback callback) override;
    void unregister_event(int fd) override;
    void run() override;
    void stop() override;

private:
#ifdef _WIN32
    HANDLE iocp_handle_;
#endif
    bool running_;
    std::map<int, EventCallback> callbacks_;
};

#endif // IOCP_EVENT_LOOP_H
