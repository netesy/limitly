#include "event_loop.hh"

#ifdef __linux__
#include "epoll_event_loop.hh"
#else
#include "iocp_event_loop.hh" // Or other platform
#endif

EventLoop::EventLoop() {
#ifdef __linux__
    pimpl_ = std::make_unique<EpollEventLoop>();
#else
    // For now, we only support Linux. Add other platforms here.
    // On non-Linux, this will default to the stub implementation.
    pimpl_ = std::make_unique<IocpEventLoop>();
#endif
}

EventLoop::~EventLoop() = default; // unique_ptr will handle deletion

void EventLoop::register_event(int fd, EventCallback callback) {
    pimpl_->register_event(fd, std::move(callback));
}

void EventLoop::unregister_event(int fd) {
    pimpl_->unregister_event(fd);
}

void EventLoop::run() {
    pimpl_->run();
}

void EventLoop::stop() {
    pimpl_->stop();
}
