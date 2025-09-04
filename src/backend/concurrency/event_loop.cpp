#include "event_loop.hh"
#include <stdexcept>
#include <iostream>

#ifdef __linux__
#include "epoll_event_loop.hh"
#elif _WIN32
#include "iocp_event_loop.hh"
#elif __APPLE__
#include "kqueue_event_loop.hh"
#else
#error "Unsupported platform"
#endif

EventLoop::EventLoop() {
#ifdef __linux__
    pimpl_ = std::make_unique<EpollEventLoop>();
#elif _WIN32
    pimpl_ = std::make_unique<IocpEventLoop>();
#elif __APPLE__
    pimpl_ = std::make_unique<KqueueEventLoop>();
#endif
}

EventLoop::~EventLoop() = default;

void EventLoop::register_event(int fd, EventCallback callback) {
    try {
        pimpl_->register_event(fd, std::move(callback));
    } catch (const std::exception& e) {
        std::cerr << "Error registering event: " << e.what() << std::endl;
    }
}

void EventLoop::unregister_event(int fd) {
    try {
        pimpl_->unregister_event(fd);
    } catch (const std::exception& e) {
        std::cerr << "Error unregistering event: " << e.what() << std::endl;
    }
}

void EventLoop::run() {
    if (running_.exchange(true)) {
        return; // Already running
    }

    try {
        pimpl_->run();
    } catch (const std::exception& e) {
        std::cerr << "Event loop error: " << e.what() << std::endl;
    }

    running_ = false;
}

void EventLoop::stop() {
    if (!running_.load()) {
        return; // Not running
    }
    pimpl_->stop();
}

bool EventLoop::is_running() const {
    return running_.load();
}
