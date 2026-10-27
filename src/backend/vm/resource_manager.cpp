#include "resource_manager.hh"
#include "../../runtime/hash_engine.hh"
#include "../../runtime/os_info.hh"
#include "register.hh"
#include "vm_list.hh"
#include "vm_runtime.hh"
#include "vm_value.hh"
#include "vm_string.hh"
#include <iostream>
#include "../channel.hh"
#include "../fiber.hh"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <mutex>
#include <filesystem>
#include <random>
#include <stdexcept>


#include "../../runtime/software_graphics.hh"

#include "../../runtime/sokol/sokol_app_runtime.hh"

// Platform-specific headers and macros
#if defined(_WIN32)
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #include <bcrypt.h>
    #include <io.h>
    #define SOCKET_CLOSE(fd) ::closesocket(fd)
    #define POLL_FUNC(fds, nfds, timeout) ::WSAPoll(fds, nfds, timeout)
    #define MSG_NOSIGNAL 0
    #ifndef POLLIN
        #define POLLIN POLLRDNORM
    #endif
    #ifndef MSG_WAITALL
        #define MSG_WAITALL 0x8
    #endif
    typedef int socklen_t;
    #ifndef _SSIZE_T_DEFINED
        #define _SSIZE_T_DEFINED
        #ifdef _WIN64
            typedef __int64 ssize_t;
        #else
            typedef int ssize_t;
        #endif
    #endif
    #ifdef DELETE
        #undef DELETE
    #endif
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <fcntl.h>
    #include <poll.h>
    #if defined(__APPLE__)
        #include <sys/random.h>
    #elif defined(__linux__)
        #include <sys/random.h>
    #endif
    #define SOCKET_CLOSE(fd) ::close(fd)
    #define POLL_FUNC(fds, nfds, timeout) ::poll(fds, nfds, timeout)
    #ifndef MSG_NOSIGNAL
        #define MSG_NOSIGNAL 0
    #endif
#endif

namespace LM {
namespace Backend {
namespace VM {

// Helper to inspect header type
static ObjHeader* check_header_type(RegisterValue value, uint32_t type_id) {
    if (!IS_PTR(value)) return nullptr;
    ObjHeader* header = reinterpret_cast<ObjHeader*>(UNBOX_PTR(value));
    return (header && header->type_id == type_id) ? header : nullptr;
}

// ===================== Value extraction helpers =====================

const char* register_value_to_cstr(RegisterValue val) {
    if (!IS_PTR(val)) return nullptr;
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
    if (!h) return nullptr;
    if (h->type_id == TYPE_STRING) {
        return ((LmStringHeader*)h)->data;
    }
    if (h->type_id == TYPE_BOX) {
        LmBox* box = (LmBox*)h;
        if (box->type == LM_BOX_STRING) return (const char*)box->value.as_ptr;
    }
    return nullptr;
}

int64_t register_value_to_i64(RegisterValue val) {
    if (IS_INT(val)) return UNBOX_INT(val);
    if (IS_PTR(val)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
        if (!h) return 0;
        if (h->type_id == TYPE_I64) return ((ObjI64*)h)->value;
        if (h->type_id == TYPE_U64) return (int64_t)((ObjU64*)h)->value;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            if (box->type == LM_BOX_INT) return box->value.as_int;
        }
    }
    return 0;
}

static double register_value_to_double(RegisterValue val) {
    return as_float(val);
}

namespace {

#if defined(_WIN32)
class SocketInitializer {
public:
    SocketInitializer() {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }
    ~SocketInitializer() {
        WSACleanup();
    }
};
static SocketInitializer g_socket_initializer;
#endif

/**
 * fill_random_internal
 * Fills a buffer with cryptographically secure random bytes.
 */
static void fill_random_internal(char* out, size_t n) {
#if defined(_WIN32)
    HCRYPTPROV hProv;
    if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) {
        CryptGenRandom(hProv, (DWORD)n, (BYTE*)out);
        CryptReleaseContext(hProv, 0);
        return;
    }
#elif defined(__APPLE__)
    if (getentropy(out, n) == 0) return;
#elif defined(__linux__)
    ssize_t got = 0;
    while ((size_t)got < n) {
        ssize_t r = ::getrandom(out + got, n - (size_t)got, 0);
        if (r <= 0) break;
        got += r;
    }
    if ((size_t)got == n) return;
#endif
    // Fallback for other POSIX or if syscalls fail
    FILE* f = std::fopen("/dev/urandom", "rb");
    if (f) {
        size_t rd = std::fread(out, 1, n, f);
        std::fclose(f);
        if (rd == n) return;
    }
    // Stronger fallback using <random>
    try {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 255);
        for (size_t i = 0; i < n; ++i) {
            out[i] = static_cast<char>(distrib(gen));
        }
    } catch (...) {
        throw std::runtime_error("Failed to gather sufficient entropy");
    }
}

// Build a heap-allocated string box from a C-string.
RegisterValue make_string_value(const char* s) {
    if (!s) return VAL_NIL;
    LmBox* box = lm_box_string(s);
    return box ? BOX_PTR(box) : VAL_NIL;
}

RegisterValue make_i64(int64_t v) {
    return lm_alloc_i64(v);
}

using LM::Runtime::HashEngine;
using LM::Runtime::compute_hmac;

} // anonymous namespace

// ===================== Software Graphics Backend =====================

struct VMGraphicsAccess {
    using Base=Resource; using Value=RegisterValue; using List=LmList;
    static Value boolean(bool value) {return value?VAL_TRUE:VAL_FALSE;}
    static Value nil() {return VAL_NIL;}
    static void* list(Value value) {return check_header_type(value,TYPE_LIST);}
    static int64_t integer(Value value) {return register_value_to_i64(value);}
    static double floating(Value value) {return register_value_to_double(value);}
    static const char* string(Value value) {return register_value_to_cstr(value);}
    static size_t length(List* value) {return lm_list_len(value);}
    static Value item(List* value,size_t index) {return lm_list_get(value,index);}
    static List* new_list() {return lm_list_new();}
    static void append(List* list,Value value) {lm_list_append(list,value);}
    static Value pointer(List* value) {return BOX_PTR(value);}
    // make_i64, not BOX_INT: it keeps the immediate encoding when the value fits and
    // heap-promotes when it does not, matching make_integer below.
    static Value number(int64_t value) {return make_i64(value);}
    static Value make_integer(int64_t value) {return make_i64(value);}
};
using SoftwareGraphicsResource=LM::Runtime::SoftwareGraphicsResource<VMGraphicsAccess>;

// ===================== Concrete Resource Implementations =====================

/**
 * FileResource
 * Provides basic file system access.
 */
class FileResource : public Resource {
public:
    FileResource() = default;
    ~FileResource() override {
        if (fp_) std::fclose(fp_);
    }

    ResourceType getType() const override { return ResourceType::FILE; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        switch (op) {
            case ResourceOperation::OPEN: {
                if (fp_) { std::fclose(fp_); fp_ = nullptr; }
                const char* path = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                const char* mode = args.size() > 1 ? register_value_to_cstr(args[1]) : nullptr;
                if (!path || !mode) return VAL_FALSE;
                fp_ = std::fopen(path, mode);
                return fp_ ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::CLOSE: {
                if (fp_) { std::fclose(fp_); fp_ = nullptr; }
                return VAL_TRUE;
            }
            case ResourceOperation::READ: {
                if (!fp_) return VAL_NIL;
                long cur = std::ftell(fp_);
                if (cur < 0) return VAL_NIL;
                std::fseek(fp_, 0, SEEK_END);
                long end = std::ftell(fp_);
                std::fseek(fp_, cur, SEEK_SET);

                size_t n = (size_t)(end - cur);
                std::vector<char> buf(n + 1, 0);
                size_t rd = (n > 0) ? std::fread(buf.data(), 1, n, fp_) : 0;
                buf[rd] = 0;
                return make_string_value(buf.data());
            }
            case ResourceOperation::READ_BYTES: {
                // Binary read — returns a [int] list of raw byte values (0..255).
                // Unlike READ (make_string_value), handles embedded \0 bytes correctly.
                if (!fp_) return VAL_NIL;
                long cur = std::ftell(fp_);
                if (cur < 0) return VAL_NIL;
                std::fseek(fp_, 0, SEEK_END);
                long end = std::ftell(fp_);
                std::fseek(fp_, cur, SEEK_SET);

                size_t n = (size_t)(end - cur);
                LmList* list = lm_list_new();
                if (!list) return VAL_NIL;
                if (n > 0) {
                    std::vector<uint8_t> rawbuf(n);
                    size_t rd = std::fread(rawbuf.data(), 1, n, fp_);
                    for (size_t i = 0; i < rd; ++i) {
                        lm_list_append(list, BOX_INT((int64_t)(uint8_t)rawbuf[i]));
                    }
                }
                return BOX_PTR(list);
            }
            case ResourceOperation::WRITE: {

                if (!fp_) return VAL_FALSE;
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!data) return VAL_FALSE;
                size_t len = std::strlen(data);
                size_t w = std::fwrite(data, 1, len, fp_);
                std::fflush(fp_);
                return (w == len) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::POLL: {
                return fp_ ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::FLUSH: {
                if (fp_) {
                    std::fflush(fp_);
                    return VAL_TRUE;
                }
                return VAL_FALSE;
            }
            case ResourceOperation::MKDIR: {
                const char* path = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!path) return VAL_FALSE;
                try {
                    return std::filesystem::create_directories(path) ? VAL_TRUE : VAL_FALSE;
                } catch (...) { return VAL_FALSE; }
            }
            case ResourceOperation::READDIR: {
                const char* path = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!path) return VAL_NIL;
                try {
                    std::string res;
                    for (const auto& entry : std::filesystem::directory_iterator(path)) {
                        res += entry.path().filename().string() + "\n";
                    }
                    return make_string_value(res.c_str());
                } catch (...) { return VAL_NIL; }
            }
            case ResourceOperation::RENAME: {
                const char* old_path = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                const char* new_path = args.size() > 1 ? register_value_to_cstr(args[1]) : nullptr;
                if (!old_path || !new_path) return VAL_FALSE;
                try {
                    std::filesystem::rename(old_path, new_path);
                    return VAL_TRUE;
                } catch (...) { return VAL_FALSE; }
            }
            case ResourceOperation::EXISTS: {
                const char* path = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!path) return VAL_FALSE;
                return std::filesystem::exists(path) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::DELETE: {
                const char* path = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!path) return VAL_FALSE;
                try {
                    return std::filesystem::remove_all(path) > 0 ? VAL_TRUE : VAL_FALSE;
                } catch (...) { return VAL_FALSE; }
            }
            default:
                return VAL_NIL;
        }
    }

private:
    FILE* fp_ = nullptr;
};

class StdoutResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::STDOUT; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        if (op == ResourceOperation::WRITE) {
            if (args.empty()) return VAL_FALSE;
            LmStringHeader* s = lm_value_to_string(args[0]);
            if (s) {
                std::fwrite(s->data, 1, s->len, stdout);
                std::fflush(stdout);
                lm_str_free(s);
                return VAL_TRUE;
            }
            return VAL_FALSE;
        }
        return (op == ResourceOperation::CLOSE || op == ResourceOperation::POLL) ? VAL_TRUE : VAL_NIL;
    }
};

class StderrResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::STDERR; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        if (op == ResourceOperation::WRITE) {
            if (args.empty()) return VAL_FALSE;
            LmStringHeader* s = lm_value_to_string(args[0]);
            if (s) {
                std::fwrite(s->data, 1, s->len, stderr);
                std::fflush(stderr);
                lm_str_free(s);
                return VAL_TRUE;
            }
            return VAL_FALSE;
        }
        return (op == ResourceOperation::CLOSE || op == ResourceOperation::POLL) ? VAL_TRUE : VAL_NIL;
    }
};

/**
 * SocketResource
 * Provides TCP socket capabilities.
 */
class SocketResource : public Resource {
public:
    SocketResource() {
        fd_ = (int)::socket(AF_INET, SOCK_STREAM, 0);
        if (fd_ >= 0) {
            int opt = 1;
            ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
        }
    }
    explicit SocketResource(int fd) : fd_(fd) {}
    ~SocketResource() override {
        if (fd_ >= 0) SOCKET_CLOSE(fd_);
    }

    ResourceType getType() const override { return ResourceType::SOCKET; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        switch (op) {
            case ResourceOperation::CONNECT: {
                const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                int64_t port = args.size() > 1 ? register_value_to_i64(args[1]) : 0;
                if (!host || port <= 0 || fd_ < 0) return VAL_FALSE;
                struct sockaddr_in addr;
                std::memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons((uint16_t)port);
                if (::inet_pton(AF_INET, host, &addr.sin_addr) <= 0) return VAL_FALSE;
                return (::connect(fd_, (struct sockaddr*)&addr, sizeof(addr)) == 0) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::SEND: {
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!data || fd_ < 0) return VAL_FALSE;
                size_t len = std::strlen(data);
                ssize_t s = ::send(fd_, data, (int)len, MSG_NOSIGNAL);
                return (s >= 0 && (size_t)s == len) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::RECEIVE: {
                if (fd_ < 0) return VAL_NIL;
                char buf[65536];
                ssize_t r = ::recv(fd_, buf, sizeof(buf) - 1, 0);
                if (r <= 0) return VAL_NIL;
                buf[r] = 0;
                return make_string_value(buf);
            }
            case ResourceOperation::BIND: {
                const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : "0.0.0.0";
                int64_t port = args.size() > 1 ? register_value_to_i64(args[1]) : 0;
                if (port <= 0 || fd_ < 0) return VAL_FALSE;
                struct sockaddr_in addr;
                std::memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons((uint16_t)port);
                if (::inet_pton(AF_INET, host, &addr.sin_addr) <= 0) return VAL_FALSE;
                return (::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) == 0) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::LISTEN: {
                int64_t backlog = args.size() > 0 ? register_value_to_i64(args[0]) : 128;
                return (fd_ >= 0 && ::listen(fd_, (int)backlog) == 0) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::ACCEPT: {
                if (fd_ < 0) return VAL_NIL;
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = (int)::accept(fd_, (struct sockaddr*)&client_addr, &client_len);
                return (client_fd >= 0) ? make_i64((int64_t)client_fd) : VAL_NIL;
            }
            case ResourceOperation::CLOSE: {
                if (fd_ >= 0) { SOCKET_CLOSE(fd_); fd_ = -1; }
                return VAL_TRUE;
            }
            case ResourceOperation::POLL: {
                if (fd_ < 0) return VAL_FALSE;
                struct pollfd p;
                p.fd = fd_;
                p.events = POLLIN;
                return (POLL_FUNC(&p, 1, 0) > 0) ? VAL_TRUE : VAL_FALSE;
            }
            default:
                return VAL_NIL;
        }
    }
private:
    int fd_ = -1;
};

class UdpSocketResource : public Resource {
public:
    UdpSocketResource() {
        fd_ = (int)::socket(AF_INET, SOCK_DGRAM, 0);
        if (fd_ >= 0) {
            int opt = 1;
            ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
        }
    }
    ~UdpSocketResource() override {
        if (fd_ >= 0) SOCKET_CLOSE(fd_);
    }

    ResourceType getType() const override { return ResourceType::UDP_SOCKET; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        switch (op) {
            case ResourceOperation::BIND: {
                const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : "0.0.0.0";
                int64_t port = args.size() > 1 ? register_value_to_i64(args[1]) : 0;
                struct sockaddr_in addr;
                std::memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons((uint16_t)port);
                if (port <= 0 || fd_ < 0 || ::inet_pton(AF_INET, host, &addr.sin_addr) <= 0) return VAL_FALSE;
                return (::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) == 0) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::SEND_TO: {
                const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                int64_t port = args.size() > 1 ? register_value_to_i64(args[1]) : 0;
                const char* data = args.size() > 2 ? register_value_to_cstr(args[2]) : nullptr;
                if (!host || port <= 0 || !data || fd_ < 0) return VAL_FALSE;
                struct sockaddr_in addr;
                std::memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons((uint16_t)port);
                if (::inet_pton(AF_INET, host, &addr.sin_addr) <= 0) return VAL_FALSE;
                ssize_t s = ::sendto(fd_, data, (int)std::strlen(data), 0, (struct sockaddr*)&addr, sizeof(addr));
                return (s >= 0) ? make_i64((int64_t)s) : VAL_NIL;
            }
            case ResourceOperation::RECV_FROM: {
                if (fd_ < 0) return VAL_NIL;
                char buf[65536];
                struct sockaddr_in from;
                socklen_t flen = sizeof(from);
                ssize_t r = ::recvfrom(fd_, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&from, &flen);
                if (r <= 0) return VAL_NIL;
                buf[r] = 0;
                char ip[INET_ADDRSTRLEN];
                ::inet_ntop(AF_INET, &from.sin_addr, ip, sizeof(ip));
                std::string res = std::string(ip) + ":" + std::to_string(ntohs(from.sin_port)) + "\n" + buf;
                return make_string_value(res.c_str());
            }
            case ResourceOperation::CLOSE: {
                if (fd_ >= 0) { SOCKET_CLOSE(fd_); fd_ = -1; }
                return VAL_TRUE;
            }
            case ResourceOperation::POLL: {
                if (fd_ < 0) return VAL_FALSE;
                struct pollfd p;
                p.fd = fd_;
                p.events = POLLIN;
                return (POLL_FUNC(&p, 1, 0) > 0) ? VAL_TRUE : VAL_FALSE;
            }
            default:
                return VAL_NIL;
        }
    }
private:
    int fd_ = -1;
};

class DnsResolverResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::DNS_RESOLVER; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        if (op == ResourceOperation::RESOLVE) {
            const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
            if (!host || !*host) return VAL_NIL;
            struct addrinfo hints, *res;
            std::memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET;
            if (::getaddrinfo(host, nullptr, &hints, &res) != 0) return VAL_NIL;
            char ip[INET_ADDRSTRLEN];
            ::inet_ntop(AF_INET, &((struct sockaddr_in*)res->ai_addr)->sin_addr, ip, sizeof(ip));
            ::freeaddrinfo(res);
            return make_string_value(ip);
        }
        return (op == ResourceOperation::CLOSE) ? VAL_TRUE : VAL_NIL;
    }
};

/**
 * WebSocketResource
 * Provides basic RFC 6455 WebSocket client capabilities.
 */
class WebSocketResource : public Resource {
public:
    WebSocketResource() : state_(WS_CLOSED), fd_(-1) {}
    ~WebSocketResource() override {
        if (fd_ >= 0) {
            if (state_ == WS_CONNECTED) send_close();
            SOCKET_CLOSE(fd_);
        }
    }

    ResourceType getType() const override { return ResourceType::WEBSOCKET; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        switch (op) {
            case ResourceOperation::CONNECT: {
                const char* url_cstr = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!url_cstr) return VAL_FALSE;
                std::string url(url_cstr), host, path = "/";
                int port = 80;
                bool ssl = false;
                if (url.substr(0, 6) == "wss://") { ssl = true; port = 443; }
                size_t start = ssl ? 6 : 5;
                size_t slash = url.find('/', start);
                std::string hp = (slash == std::string::npos) ? url.substr(start) : url.substr(start, slash - start);
                if (slash != std::string::npos) path = url.substr(slash);
                size_t colon = hp.find(':');
                if (colon != std::string::npos) {
                    host = hp.substr(0, colon);
                    port = std::stoi(hp.substr(colon + 1));
                } else {
                    host = hp;
                }

                fd_ = (int)::socket(AF_INET, SOCK_STREAM, 0);
                if (fd_ < 0) return VAL_FALSE;

                struct sockaddr_in addr;
                std::memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons((uint16_t)port);
                if (::inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
                    struct addrinfo hints, *res;
                    std::memset(&hints, 0, sizeof(hints));
                    hints.ai_family = AF_INET;
                    if (::getaddrinfo(host.c_str(), nullptr, &hints, &res) != 0) {
                        SOCKET_CLOSE(fd_); fd_ = -1; return VAL_FALSE;
                    }
                    addr.sin_addr = ((struct sockaddr_in*)res->ai_addr)->sin_addr;
                    ::freeaddrinfo(res);
                }

                if (::connect(fd_, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
                    SOCKET_CLOSE(fd_); fd_ = -1; return VAL_FALSE;
                }

                std::string key = gen_key();
                std::string req = "GET " + path + " HTTP/1.1\r\n"
                                  "Host: " + host + "\r\n"
                                  "Upgrade: websocket\r\n"
                                  "Connection: Upgrade\r\n"
                                  "Sec-WebSocket-Key: " + key + "\r\n"
                                  "Sec-WebSocket-Version: 13\r\n\r\n";
                ::send(fd_, req.c_str(), (int)req.size(), 0);

                char resp[4096];
                ssize_t rd = ::recv(fd_, resp, sizeof(resp) - 1, 0);
                if (rd <= 0 || std::string(resp).find("101") == std::string::npos) {
                    SOCKET_CLOSE(fd_); fd_ = -1; return VAL_FALSE;
                }
                state_ = WS_CONNECTED;
                return VAL_TRUE;
            }
            case ResourceOperation::SEND: {
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                return (state_ == WS_CONNECTED && data && send_frame(data)) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::RECEIVE: {
                return (state_ == WS_CONNECTED) ? recv_frame() : VAL_NIL;
            }
            case ResourceOperation::CLOSE: {
                if (fd_ >= 0) {
                    if (state_ == WS_CONNECTED) send_close();
                    SOCKET_CLOSE(fd_);
                    fd_ = -1;
                    state_ = WS_CLOSED;
                }
                return VAL_TRUE;
            }
            case ResourceOperation::POLL: {
                if (fd_ < 0) return VAL_FALSE;
                struct pollfd p;
                p.fd = fd_;
                p.events = POLLIN;
                return (POLL_FUNC(&p, 1, 0) > 0) ? VAL_TRUE : VAL_FALSE;
            }
            default:
                return VAL_NIL;
        }
    }

private:
    enum WsState { WS_CLOSED, WS_CONNECTED } state_;
    int fd_;

    std::string gen_key() {
        char buf[17];
        fill_random_internal(buf, 16);
        static const char* b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string res;
        for (int i = 0; i < 16; i += 3) {
            unsigned int n = (unsigned char)buf[i] << 16;
            if (i + 1 < 16) n |= (unsigned char)buf[i+1] << 8;
            if (i + 2 < 16) n |= (unsigned char)buf[i+2];
            res += b64[(n >> 18) & 63];
            res += b64[(n >> 12) & 63];
            res += (i + 1 < 16) ? b64[(n >> 6) & 63] : '=';
            res += (i + 2 < 16) ? b64[n & 63] : '=';
        }
        return res;
    }

    bool send_frame(const std::string& d) {
        std::vector<uint8_t> frame = { 0x81 }; // FIN + Text
        size_t len = d.size();
        if (len < 126) {
            frame.push_back((uint8_t)len);
        } else if (len < 65536) {
            frame.push_back(126);
            frame.push_back(len >> 8);
            frame.push_back(len & 255);
        } else {
            frame.push_back(127);
            for (int i = 56; i >= 0; i -= 8) frame.push_back((len >> i) & 255);
        }
        frame.insert(frame.end(), d.begin(), d.end());
        return ::send(fd_, (const char*)frame.data(), (int)frame.size(), 0) == (ssize_t)frame.size();
    }

    void send_close() {
        uint8_t frame[] = { 0x88, 0 };
        ::send(fd_, (const char*)frame, 2, 0);
    }

    RegisterValue recv_frame() {
        uint8_t head[2];
        if (::recv(fd_, (char*)head, 2, MSG_WAITALL) < 2) return VAL_NIL;

        uint8_t opcode = head[0] & 0x0F;
        bool masked = (head[1] & 0x80) != 0;
        uint64_t len = head[1] & 0x7F;

        if (len == 126) {
            uint8_t ext[2];
            if (::recv(fd_, (char*)ext, 2, MSG_WAITALL) < 2) return VAL_NIL;
            len = (ext[0] << 8) | ext[1];
        } else if (len == 127) {
            uint8_t ext[8];
            if (::recv(fd_, (char*)ext, 8, MSG_WAITALL) < 8) return VAL_NIL;
            len = 0;
            for (int i = 0; i < 8; i++) len = (len << 8) | ext[i];
        }

        // Bounds check: 10 MB maximum payload to prevent OOM
        if (len > 10 * 1024 * 1024) return VAL_NIL;

        uint8_t mask[4] = { 0 };
        if (masked) {
            if (::recv(fd_, (char*)mask, 4, MSG_WAITALL) < 4) return VAL_NIL;
        }

        std::vector<char> payload(len);
        size_t total = 0;
        while (total < len) {
            ssize_t n = ::recv(fd_, payload.data() + total, (int)(len - total), 0);
            if (n <= 0) return VAL_NIL;
            total += n;
        }

        if (masked) {
            for (size_t i = 0; i < len; i++) payload[i] ^= mask[i % 4];
        }

        if (opcode == 0x8) { // CLOSE
            state_ = WS_CLOSED;
            send_close();
            return VAL_NIL;
        }
        if (opcode == 0x9) { // PING
            std::vector<uint8_t> pong = { 0x8A, (uint8_t)(len < 126 ? len : 126) };
            if (len >= 126) { pong.push_back(0); pong.push_back(0); }
            pong.insert(pong.end(), payload.begin(), payload.end());
            ::send(fd_, (const char*)pong.data(), (int)pong.size(), 0);
            return recv_frame();
        }

        payload.push_back(0); // Ensure null termination for make_string_value
        return make_string_value(payload.data());
    }
};

class HashEngineResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::HASH_ENGINE; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        switch (op) {
            case ResourceOperation::OPEN: {
                const char* a = args.size() > 0 ? register_value_to_cstr(args[0]) : "sha256";
                if (!a) return VAL_FALSE;
                return engine_.open(a) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::WRITE: {
                const char* d = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!d) return VAL_FALSE;
                engine_.write(d,std::strlen(d));
                return VAL_TRUE;
            }
            case ResourceOperation::READ: {
                return make_string_value(engine_.read().c_str());
            }
            case ResourceOperation::HMAC: {
                const char* algo = args.size() > 0 ? register_value_to_cstr(args[0]) : "sha256";
                const char* key = args.size() > 1 ? register_value_to_cstr(args[1]) : nullptr;
                const char* data = args.size() > 2 ? register_value_to_cstr(args[2]) : nullptr;
                if (!key || !data) return VAL_NIL;
                std::string res = compute_hmac(algo, key, data);
                return make_string_value(res.c_str());
            }
            case ResourceOperation::CLOSE: return VAL_TRUE;
            default: return VAL_NIL;
        }
    }
private:
    HashEngine engine_;
};

class ChannelResource : public Resource {
public:
    explicit ChannelResource(size_t c = 1024) : ch_(c) {}
    ResourceType getType() const override { return ResourceType::CHANNEL; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* ctx) override {
        Fiber* f = static_cast<Fiber*>(ctx != nullptr ? ctx : ResourceManager::getInstance().getCurrentFiber());
        if (op == ResourceOperation::SEND || op == ResourceOperation::PUSH) {
            ch_.send(args.empty() ? VAL_NIL : args[0], f);
            return VAL_TRUE;
        }
        if (op == ResourceOperation::RECEIVE || op == ResourceOperation::POP) return ch_.recv(f);
        if (op == ResourceOperation::POLL) {
            RegisterValue v = VAL_NIL;
            return ch_.poll(v) ? v : VAL_NIL;
        }
        if (op == ResourceOperation::CLOSE) {
            ch_.close();
            return VAL_TRUE;
        }
        return VAL_NIL;
    }
private:
    LM::Backend::Channel ch_;
};

class MemoryResource : public Resource {
public:
    explicit MemoryResource(size_t s) {
        if (s > 0) {
            ptr_ = std::malloc(s);
            sz_ = ptr_ ? s : 0;
        }
    }
    ~MemoryResource() override { if (ptr_) std::free(ptr_); }
    ResourceType getType() const override { return ResourceType::MEMORY; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        switch (op) {
            case ResourceOperation::OPEN: {
                size_t n = (size_t)register_value_to_i64(args.empty() ? make_i64(sz_) : args[0]);
                if (ptr_) std::free(ptr_);
                ptr_ = n ? std::malloc(n) : nullptr;
                sz_ = ptr_ ? n : 0;
                return (n == 0 || ptr_) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::WRITE: {
                const char* d = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!d || !ptr_) return VAL_FALSE;
                size_t l = std::min(std::strlen(d), sz_);
                std::memcpy(ptr_, d, l);
                return VAL_TRUE;
            }
            case ResourceOperation::READ: {
                if (!ptr_ || sz_ == 0) return VAL_NIL;
                std::vector<char> b(sz_ + 1, 0);
                std::memcpy(b.data(), ptr_, sz_);
                return make_string_value(b.data());
            }
            case ResourceOperation::CLOSE: {
                if (ptr_) { std::free(ptr_); ptr_ = nullptr; sz_ = 0; }
                return VAL_TRUE;
            }
            case ResourceOperation::SIZE: {
                // Memory measurement: report the number of allocated bytes held by this buffer.
                return make_i64(static_cast<int64_t>(sz_));
            }
            default:
                return VAL_NIL;
        }
    }
private:
    void* ptr_ = nullptr;
    size_t sz_ = 0;
};

class EntropyResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::ENTROPY; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        if (op == ResourceOperation::READ) {
            size_t w = (size_t)register_value_to_i64(args.empty() ? make_i64(32) : args[0]);
            if (w == 0) w = 32;
            if (w > 65536) w = 65536;
            std::vector<char> b(w);
            fill_random_internal(b.data(), w);
            std::string s(b.begin(), b.end());
            return make_string_value(s.c_str());
        }
        return (op == ResourceOperation::POLL) ? VAL_TRUE : VAL_NIL;
    }
};

namespace os = LM::Runtime::OS;

// Turn a native string vector into an owned [str] list value.
static RegisterValue make_string_list(const std::vector<std::string>& items) {
    LmList* list = lm_list_new();
    if (!list) return VAL_NIL;
    for (const auto& item : items) lm_list_append(list, make_string_value(item.c_str()));
    return BOX_PTR(list);
}

// Read every argument as a string. resource_call flattens a [any] argument
// list into individual values, so an argv arrives as one string per element.
static std::vector<std::string> read_argument_strings(const std::vector<RegisterValue>& args) {
    std::vector<std::string> items;
    for (const auto& value : args) {
        const char* text = register_value_to_cstr(value);
        if (text) items.emplace_back(text);
    }
    return items;
}

// Ambient machine and environment services. Backs std.os and std.env.
class OsResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::OS; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        auto text = [](const std::string& value) { return make_string_value(value.c_str()); };
        auto truth = [](bool yes) { return yes ? VAL_TRUE : VAL_FALSE; };
        switch (op) {
            case ResourceOperation::ENV_GET: {
                const char* key = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!key) return VAL_NIL;
                std::string value;
                // nil means the variable is unset, so std.env.get can return str?.
                if (!os::env_lookup(key, value)) return VAL_NIL;
                return text(value);
            }
            case ResourceOperation::ENV_SET: {
                const char* key = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                const char* value = args.size() > 1 ? register_value_to_cstr(args[1]) : nullptr;
                if (!key || !value) return VAL_FALSE;
                return truth(os::env_set(key, value));
            }
            case ResourceOperation::ENV_UNSET: {
                const char* key = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!key) return VAL_FALSE;
                return truth(os::env_unset(key));
            }
            case ResourceOperation::ENV_LIST:
                return make_string_list(os::env_list());
            case ResourceOperation::CWD: {
                auto path = os::cwd();
                if (path.empty()) return VAL_NIL;
                return text(path);
            }
            case ResourceOperation::CHDIR: {
                const char* path = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!path) return VAL_FALSE;
                return truth(os::chdir_to(path));
            }
            case ResourceOperation::HOME_DIR:
                return text(os::home_dir());
            case ResourceOperation::TEMP_DIR:
                return text(os::temp_dir());
            case ResourceOperation::EXE_PATH:
                return text(os::exe_path());
            case ResourceOperation::OS_NAME:
                return text(os::os_name());
            case ResourceOperation::ARCH:
                return text(os::arch());
            case ResourceOperation::HOSTNAME:
                return text(os::hostname());
            case ResourceOperation::NUM_CPU:
                return make_i64(os::num_cpu());
            default:
                return VAL_NIL;
        }
    }
};

// This process's identity, memory and lifecycle, plus child processes.
// Backs std.process.
class ProcessResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::PROCESS; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        switch (op) {
            case ResourceOperation::PROC_ARGS:
                return make_string_list(os::program_arguments());
            case ResourceOperation::PROC_COMMAND:
                return make_string_value(os::command_name().c_str());
            case ResourceOperation::PROC_ID:
                return make_i64(os::pid());
            case ResourceOperation::PROC_RSS:
                // Kilobytes of current resident set, or -1 when the platform
                // cannot report it. Never an estimate.
                return make_i64(os::rss_kb());
            case ResourceOperation::PROC_PEAK_RSS:
                return make_i64(os::peak_rss_kb());
            case ResourceOperation::PROC_EXIT: {
                int64_t code = args.size() > 0 ? register_value_to_i64(args[0]) : 0;
                os::terminate(static_cast<int>(code));  // does not return
                return VAL_NIL;
            }
            case ResourceOperation::SPAWN: {
                // The argv arrives flattened: element 0 is the program, the rest
                // its arguments. The child runs directly (no shell) and this call
                // blocks until it exits, returning the child's exit code.
                auto argv = read_argument_strings(args);
                if (argv.empty()) return make_i64(-1);
                return make_i64(os::spawn_wait(argv));
            }
            default:
                return VAL_NIL;
        }
    }
};

// ===================== ResourceManager Core =====================
ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager() {
    // Pre-allocate standard resources with fixed IDs
    resources_[0] = std::make_unique<StdoutResource>();
    resources_[1] = std::make_unique<StderrResource>();
    next_id_ = 2;  // Start user resources from ID 2
}

ResourceManager::~ResourceManager() {
    shutdown();
}

int64_t ResourceManager::create(ResourceType type, const std::vector<RegisterValue>& args) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::unique_ptr<Resource> res;
    switch (type) {
        case ResourceType::FILE:          res = std::make_unique<FileResource>(); break;
        case ResourceType::STDOUT:        res = std::make_unique<StdoutResource>(); break;
        case ResourceType::STDERR:        res = std::make_unique<StderrResource>(); break;
        case ResourceType::SOCKET: {
            int fd = !args.empty() ? (int)register_value_to_i64(args[0]) : -1;
            res = (fd >= 0) ? std::make_unique<SocketResource>(fd) : std::make_unique<SocketResource>();
            break;
        }
        case ResourceType::CHANNEL:       res = std::make_unique<ChannelResource>(!args.empty() ? register_value_to_i64(args[0]) : 1024); break;
        case ResourceType::MEMORY:        res = std::make_unique<MemoryResource>(!args.empty() ? register_value_to_i64(args[0]) : 0); break;
        case ResourceType::ENTROPY:       res = std::make_unique<EntropyResource>(); break;
        case ResourceType::DNS_RESOLVER:  res = std::make_unique<DnsResolverResource>(); break;
        case ResourceType::UDP_SOCKET:    res = std::make_unique<UdpSocketResource>(); break;
        case ResourceType::WEBSOCKET:     res = std::make_unique<WebSocketResource>(); break;
        case ResourceType::HASH_ENGINE:   res = std::make_unique<HashEngineResource>(); break;
        case ResourceType::GRAPHICS:      res = std::make_unique<SoftwareGraphicsResource>(); break;
        case ResourceType::OS:            res = std::make_unique<OsResource>(); break;
        case ResourceType::PROCESS:       res = std::make_unique<ProcessResource>(); break;
        default: return -1;
    }
    int64_t id = next_id_++;
    resources_[id] = std::move(res);
    return id;
}

RegisterValue ResourceManager::call(int64_t id, ResourceOperation op, const std::vector<RegisterValue>& args, void* ctx) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = resources_.find(id);
    return (it == resources_.end()) ? VAL_NIL : it->second->call(op, args, ctx != nullptr ? ctx : current_fiber_);
}

void ResourceManager::destroy(int64_t id) {
    std::lock_guard<std::mutex> lock(mutex_);
    resources_.erase(id);
}

void ResourceManager::shutdown() {
    std::lock_guard<std::mutex> lock(mutex_);
    resources_.clear();
}

} // namespace VM
} // namespace Backend
} // namespace LM
