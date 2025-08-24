#include "iocp_event_loop.hh"
#include <iostream>

// NOTE: This is a stub implementation for Windows IOCP.
// It cannot be implemented or tested in the current Linux environment.

IocpEventLoop::IocpEventLoop() {
    // std::cout << "Warning: IOCP Event Loop is not implemented." << std::endl;
}

IocpEventLoop::~IocpEventLoop() {}

void IocpEventLoop::register_event(int fd, EventCallback callback) {
    // TODO: Implement using Windows IOCP
}

void IocpEventLoop::unregister_event(int fd) {
    // TODO: Implement using Windows IOCP
}

void IocpEventLoop::run() {
    // TODO: Implement using Windows IOCP
}

void IocpEventLoop::stop() {
    // TODO: Implement using Windows IOCP
}
