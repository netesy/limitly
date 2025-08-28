#include "iocp_event_loop.hh"

#ifdef _WIN32
#include <stdexcept>
#include <iostream>
#include <io.h>  // For _get_osfhandle

IocpEventLoop::IocpEventLoop() : running_(false) {
    iocp_handle_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (iocp_handle_ == NULL) {
        throw std::runtime_error("Failed to create IOCP handle");
    }
}

IocpEventLoop::~IocpEventLoop() {
    if (iocp_handle_ != NULL) {
        CloseHandle(iocp_handle_);
    }
}

void IocpEventLoop::register_event(int fd, EventCallback callback) {
    if (fd == -1) {
        // Immediate execution for non-fd-based tasks
        callback(fd);
        return;
    }
    HANDLE handle = (HANDLE)_get_osfhandle(fd);
    if (CreateIoCompletionPort(handle, iocp_handle_, (ULONG_PTR)fd, 0) == NULL) {
        throw std::runtime_error("Failed to associate file descriptor with IOCP");
    }
    callbacks_[fd] = std::move(callback);
}

void IocpEventLoop::unregister_event(int fd) {
    // IOCP doesn't require explicit unregistration for this model.
    // When the handle is closed, it's automatically removed.
    callbacks_.erase(fd);
}

void IocpEventLoop::run() {
    running_ = true;
    const int MAX_EVENTS = 10;
    OVERLAPPED_ENTRY entries[MAX_EVENTS];
    ULONG events_processed;

    while (running_) {
        BOOL result = GetQueuedCompletionStatusEx(iocp_handle_, entries, MAX_EVENTS, &events_processed, INFINITE, FALSE);
        if (!result) {
            DWORD error = GetLastError();
            if (error == WAIT_TIMEOUT) {
                continue;
            }
            throw std::runtime_error("GetQueuedCompletionStatusEx failed");
        }

        for (ULONG i = 0; i < events_processed; ++i) {
            int fd = (int)entries[i].lpCompletionKey;
            auto it = callbacks_.find(fd);
            if (it != callbacks_.end()) {
                it->second(fd);
            }
        }
    }
}

void IocpEventLoop::stop() {
    running_ = false;
    // Post a special "stop" packet to the IOCP to wake up the run loop
    PostQueuedCompletionStatus(iocp_handle_, 0, (ULONG_PTR)-1, NULL);
}

#endif // _WIN32
