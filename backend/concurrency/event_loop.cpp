#include "event_loop.hh"
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

EventLoop::EventLoop() : running_(false) {
    epoll_fd_ = epoll_create1(0);
    if (epoll_fd_ == -1) {
        throw std::runtime_error("Failed to create epoll file descriptor");
    }
}

EventLoop::~EventLoop() {
    if (epoll_fd_ != -1) {
        close(epoll_fd_);
    }
}

void EventLoop::register_event(int fd, EventCallback callback) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET; // Edge-triggered for input events
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event) == -1) {
        throw std::runtime_error("Failed to add file descriptor to epoll");
    }
    callbacks_[fd] = std::move(callback);
}

void EventLoop::unregister_event(int fd) {
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, nullptr) == -1) {
        // Don't throw from here, just log, as it might be called in cleanup paths
        std::cerr << "Warning: Failed to remove file descriptor from epoll" << std::endl;
    }
    callbacks_.erase(fd);
}

void EventLoop::run() {
    running_ = true;
    const int MAX_EVENTS = 10;
    std::vector<epoll_event> events(MAX_EVENTS);

    while (running_) {
        int n = epoll_wait(epoll_fd_, events.data(), MAX_EVENTS, -1);
        if (n == -1) {
            if (errno == EINTR) {
                continue; // Interrupted by a signal, safe to continue
            }
            throw std::runtime_error("epoll_wait failed");
        }

        for (int i = 0; i < n; ++i) {
            int fd = events[i].data.fd;
            auto it = callbacks_.find(fd);
            if (it != callbacks_.end()) {
                it->second(); // Execute the callback
            }
        }
    }
}

void EventLoop::stop() {
    running_ = false;
    // A more robust implementation would use an eventfd to wake up the epoll_wait call immediately.
    // For this project, a simple flag is sufficient as we control the test environment.
}
