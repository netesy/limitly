#include "kqueue_event_loop.hh"

#ifdef __APPLE__
#include <sys/event.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

KqueueEventLoop::KqueueEventLoop() : running_(false) {
    kqueue_fd_ = kqueue();
    if (kqueue_fd_ == -1) {
        throw std::runtime_error("Failed to create kqueue file descriptor");
    }
}

KqueueEventLoop::~KqueueEventLoop() {
    if (kqueue_fd_ != -1) {
        close(kqueue_fd_);
    }
}

void KqueueEventLoop::register_event(int fd, EventCallback callback) {
    if (fd == -1) {
        // Immediate execution for non-fd-based tasks
        callback(fd);
        return;
    }
    struct kevent event;
    EV_SET(&event, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
    if (kevent(kqueue_fd_, &event, 1, nullptr, 0, nullptr) == -1) {
        throw std::runtime_error("Failed to add file descriptor to kqueue");
    }
    callbacks_[fd] = std::move(callback);
}

void KqueueEventLoop::unregister_event(int fd) {
    struct kevent event;
    EV_SET(&event, fd, EVFILT_READ, EV_DELETE, 0, 0, 0);
    if (kevent(kqueue_fd_, &event, 1, nullptr, 0, nullptr) == -1) {
        std::cerr << "Warning: Failed to remove file descriptor from kqueue" << std::endl;
    }
    callbacks_.erase(fd);
}

void KqueueEventLoop::run() {
    running_ = true;
    const int MAX_EVENTS = 10;
    std::vector<struct kevent> events(MAX_EVENTS);

    while (running_) {
        int n = kevent(kqueue_fd_, nullptr, 0, events.data(), MAX_EVENTS, nullptr);
        if (n == -1) {
            if (errno == EINTR) {
                continue; // Interrupted by a signal, safe to continue
            }
            throw std::runtime_error("kevent failed");
        }

        for (int i = 0; i < n; ++i) {
            int fd = events[i].ident;
            auto it = callbacks_.find(fd);
            if (it != callbacks_.end()) {
                it->second(fd); // Execute the callback, passing the fd
            }
        }
    }
}

void KqueueEventLoop::stop() {
    running_ = false;
}
#endif // __APPLE__
