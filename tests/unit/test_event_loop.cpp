#include "backend/concurrency/event_loop.hh"
#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#endif

// Helper to create a non-blocking socket pair
void create_socket_pair(int fds[2]) {
#ifdef _WIN32
    // This is a bit complex on Windows. We'll create a listening socket
    // and connect to it.
    SOCKET listener = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = 0; // Automatically assign a port
    bind(listener, (sockaddr*)&addr, sizeof(addr));
    int len = sizeof(addr);
    getsockname(listener, (sockaddr*)&addr, &len);
    listen(listener, 1);

    fds[0] = socket(AF_INET, SOCK_STREAM, 0);
    connect(fds[0], (sockaddr*)&addr, sizeof(addr));
    fds[1] = accept(listener, NULL, NULL);

    // Set to non-blocking
    u_long mode = 1;
    ioctlsocket(fds[0], FIONBIO, &mode);
    ioctlsocket(fds[1], FIONBIO, &mode);
    closesocket(listener);
#else
    socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
    fcntl(fds[0], F_SETFL, O_NONBLOCK);
    fcntl(fds[1], F_SETFL, O_NONBLOCK);
#endif
}

void close_socket(int fd) {
#ifdef _WIN32
    closesocket(fd);
#else
    close(fd);
#endif
}

void test_event_loop_with_socket() {
    std::cout << "Running test: Event Loop with Socket... ";
    EventLoop event_loop;
    std::atomic<bool> callback_was_called(false);

    int fds[2];
    create_socket_pair(fds);

    event_loop.register_event(fds[0], [&](int fd) {
        char buffer[10];
        recv(fd, buffer, sizeof(buffer), 0);
        callback_was_called = true;
        event_loop.stop();
    });

    std::thread event_thread([&]() {
        event_loop.run();
    });

    // Give the event loop a moment to start up
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Write to the other end of the socket to trigger the event
    send(fds[1], "test", 4, 0);

    event_thread.join();
    close_socket(fds[0]);
    close_socket(fds[1]);

    assert(callback_was_called);
    std::cout << "PASSED" << std::endl;
}

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    test_event_loop_with_socket();

    std::cout << "\nAll event loop tests passed!" << std::endl;

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
