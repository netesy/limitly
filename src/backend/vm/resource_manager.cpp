#include "resource_manager.hh"
#include "../channel.hh"
#include "../fiber.hh"
#include "../../runtime/runtime.h"
#include "../../runtime/runtime_value.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string>
#include <vector>
#include <memory>

// For getrandom(2) on Linux. Fall back to /dev/urandom otherwise.
#ifdef __linux__
#include <sys/random.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#else
#include <unistd.h>
#endif

namespace LM {
namespace Backend {
namespace VM {

// ===================== Value extraction helpers =====================

const char* register_value_to_cstr(RegisterValue val) {
    if (!IS_PTR(val)) return nullptr;
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
    if (!h) return nullptr;
    if (h->type_id == TYPE_BOX) {
        LmBox* box = (LmBox*)h;
        if (box->type == LM_BOX_STRING) return (const char*)box->value.as_ptr;
    }
    return nullptr;
}

int64_t register_value_to_i64(RegisterValue val) {
    if (is_integer(val)) return as_i64(val);
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

void* register_value_to_ptr(RegisterValue val) {
    if (!IS_PTR(val)) {
        if (is_integer(val)) return (void*)(uintptr_t)as_i64(val);
        return nullptr;
    }
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
    if (!h) return nullptr;
    if (h->type_id == TYPE_FOREIGN_PTR) return ((ObjForeignPtr*)h)->ptr;
    if (h->type_id == TYPE_BOX) {
        LmBox* box = (LmBox*)h;
        if (box->type == LM_BOX_NULLPTR) return box->value.as_ptr;
    }
    return (void*)h;
}

namespace {

// Build a heap-allocated string box from a C-string.
RegisterValue make_string_value(const char* s) {
    if (!s) return VAL_NIL;
    LmBox* box = lm_box_string(s);
    return box ? BOX_PTR(box) : VAL_NIL;
}

// ===================== Concrete resources =====================

// ----- FILE -----
class FileResource : public Resource {
public:
    FileResource() = default;
    ~FileResource() override { if (fp_) { std::fclose(fp_); fp_ = nullptr; } }

    ResourceType getType() const override { return ResourceType::FILE; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*context*/) override {
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
                // Read remaining bytes from current position to end of file.
                long cur = std::ftell(fp_);
                if (cur < 0) return VAL_NIL;
                if (std::fseek(fp_, 0, SEEK_END) != 0) return VAL_NIL;
                long end = std::ftell(fp_);
                if (end < 0) return VAL_NIL;
                size_t n = (size_t)(end - cur);
                if (std::fseek(fp_, cur, SEEK_SET) != 0) return VAL_NIL;
                std::vector<char> buf(n + 1, '\0');
                size_t rd = n > 0 ? std::fread(buf.data(), 1, n, fp_) : 0;
                buf[rd] = '\0';
                return make_string_value(buf.data());
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
            default:
                return VAL_NIL;
        }
    }

private:
    FILE* fp_ = nullptr;
};

// ----- STDOUT / STDERR -----
class StdoutResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::STDOUT; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        if (op == ResourceOperation::WRITE) {
            const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
            if (!data) return VAL_FALSE;
            std::fputs(data, stdout);
            std::fflush(stdout);
            return VAL_TRUE;
        }
        if (op == ResourceOperation::CLOSE || op == ResourceOperation::POLL) return VAL_TRUE;
        return VAL_NIL;
    }
};

class StderrResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::STDERR; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        if (op == ResourceOperation::WRITE) {
            const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
            if (!data) return VAL_FALSE;
            std::fputs(data, stderr);
            std::fflush(stderr);
            return VAL_TRUE;
        }
        if (op == ResourceOperation::CLOSE || op == ResourceOperation::POLL) return VAL_TRUE;
        return VAL_NIL;
    }
};

// ----- SOCKET -----
class SocketResource : public Resource {
public:
    SocketResource() {
#ifdef __linux__
        fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
#else
        fd_ = -1;
#endif
    }
    ~SocketResource() override {
#ifdef __linux__
        if (fd_ >= 0) { ::close(fd_); fd_ = -1; }
#endif
    }
    ResourceType getType() const override { return ResourceType::SOCKET; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
#ifdef __linux__
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
                ssize_t s = ::send(fd_, data, len, 0);
                return (s >= 0 && (size_t)s == len) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::RECEIVE: {
                if (fd_ < 0) return VAL_NIL;
                char buf[4096];
                ssize_t r = ::recv(fd_, buf, sizeof(buf) - 1, 0);
                if (r <= 0) return VAL_NIL;
                buf[r] = '\0';
                return make_string_value(buf);
            }
            case ResourceOperation::CLOSE: {
                if (fd_ >= 0) { ::close(fd_); fd_ = -1; }
                return VAL_TRUE;
            }
            default:
                return VAL_NIL;
        }
#else
        return VAL_NIL;
#endif
    }
private:
    int fd_ = -1;
};

// ----- CHANNEL -----
class ChannelResource : public Resource {
public:
    explicit ChannelResource(size_t capacity = 1024) : channel_(capacity) {}
    ResourceType getType() const override { return ResourceType::CHANNEL; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* context) override {
        Fiber* fiber = static_cast<Fiber*>(context);
        switch (op) {
            case ResourceOperation::SEND:
            case ResourceOperation::PUSH:
                channel_.send(args.empty() ? VAL_NIL : args[0], fiber);
                return VAL_TRUE;
            case ResourceOperation::RECEIVE:
            case ResourceOperation::POP:
                return channel_.recv(fiber);
            case ResourceOperation::POLL: {
                RegisterValue out = VAL_NIL;
                return channel_.poll(out) ? out : VAL_NIL;
            }
            case ResourceOperation::CLOSE:
                channel_.close();
                return VAL_TRUE;
            default:
                return VAL_NIL;
        }
    }
private:
    LM::Backend::Channel channel_;
};

// ----- MEMORY -----
class MemoryResource : public Resource {
public:
    explicit MemoryResource(size_t size) {
        if (size > 0) {
            ptr_ = std::malloc(size);
            size_ = ptr_ ? size : 0;
        }
    }
    ~MemoryResource() override {
        if (ptr_) { std::free(ptr_); ptr_ = nullptr; size_ = 0; }
    }
    ResourceType getType() const override { return ResourceType::MEMORY; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        switch (op) {
            case ResourceOperation::OPEN: {
                // (Re)allocate with the given size.
                size_t new_size = (size_t)register_value_to_i64(args.empty() ? make_i64((int64_t)size_) : args[0]);
                if (ptr_) { std::free(ptr_); ptr_ = nullptr; }
                size_ = 0;
                if (new_size > 0) {
                    ptr_ = std::malloc(new_size);
                    if (ptr_) size_ = new_size;
                }
                return ptr_ ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::WRITE: {
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!data || !ptr_) return VAL_FALSE;
                size_t len = std::strlen(data);
                if (len > size_) len = size_;
                std::memcpy(ptr_, data, len);
                return VAL_TRUE;
            }
            case ResourceOperation::READ: {
                if (!ptr_ || size_ == 0) return VAL_NIL;
                std::vector<char> buf(size_ + 1, '\0');
                std::memcpy(buf.data(), ptr_, size_);
                return make_string_value(buf.data());
            }
            case ResourceOperation::CLOSE: {
                if (ptr_) { std::free(ptr_); ptr_ = nullptr; size_ = 0; }
                return VAL_TRUE;
            }
            default:
                return VAL_NIL;
        }
    }
private:
    void* ptr_ = nullptr;
    size_t size_ = 0;
};

// ----- ENTROPY -----
// Marker resource. Reads return random bytes sourced from getrandom(2)
// (Linux) or /dev/urandom (fallback).
class EntropyResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::ENTROPY; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        if (op == ResourceOperation::READ) {
            size_t want = (size_t)register_value_to_i64(args.empty() ? make_i64(32) : args[0]);
            if (want == 0) want = 32;
            if (want > 65536) want = 65536;
            std::vector<char> buf(want, '\0');
            fill_random(buf.data(), want);
            return make_string_value(std::string(buf.begin(), buf.end()).c_str());
        }
        if (op == ResourceOperation::WRITE || op == ResourceOperation::CLOSE || op == ResourceOperation::POLL) {
            return op == ResourceOperation::POLL ? VAL_TRUE : VAL_NIL;
        }
        return VAL_NIL;
    }
private:
    static void fill_random(char* out, size_t n) {
#ifdef __linux__
        ssize_t got = 0;
        while ((size_t)got < n) {
            ssize_t r = ::getrandom(out + got, n - (size_t)got, 0);
            if (r <= 0) break;
            got += r;
        }
        if ((size_t)got == n) return;
#endif
        // Fallback: /dev/urandom
        FILE* f = std::fopen("/dev/urandom", "rb");
        if (f) {
            size_t rd = std::fread(out, 1, n, f);
            (void)rd;
            std::fclose(f);
            return;
        }
        // Last resort: libc rand
        for (size_t i = 0; i < n; ++i) out[i] = (char)(std::rand() & 0xFF);
    }
};

} // anonymous namespace

// ===================== ResourceManager =====================

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::~ResourceManager() {
    shutdown();
}

int64_t ResourceManager::create(ResourceType type, const std::vector<RegisterValue>& args) {
    std::lock_guard<std::mutex> lock(mutex_);

    std::unique_ptr<Resource> res;
    switch (type) {
        case ResourceType::FILE:
            res = std::make_unique<FileResource>();
            break;
        case ResourceType::STDOUT:
            res = std::make_unique<StdoutResource>();
            break;
        case ResourceType::STDERR:
            res = std::make_unique<StderrResource>();
            break;
        case ResourceType::SOCKET:
            res = std::make_unique<SocketResource>();
            break;
        case ResourceType::CHANNEL: {
            size_t capacity = 1024;
            if (!args.empty()) {
                int64_t c = register_value_to_i64(args[0]);
                if (c > 0) capacity = (size_t)c;
            }
            res = std::make_unique<ChannelResource>(capacity);
            break;
        }
        case ResourceType::MEMORY: {
            size_t sz = 0;
            if (!args.empty()) {
                int64_t s = register_value_to_i64(args[0]);
                if (s > 0) sz = (size_t)s;
            }
            res = std::make_unique<MemoryResource>(sz);
            break;
        }
        case ResourceType::ENTROPY:
            res = std::make_unique<EntropyResource>();
            break;
        default:
            // WINDOW/SURFACE/PROCESS/TIMER/TASK/LIBRARY: not yet implemented.
            return -1;
    }

    int64_t id = next_id_++;
    resources_[id] = std::move(res);
    return id;
}

RegisterValue ResourceManager::call(int64_t id, ResourceOperation op, const std::vector<RegisterValue>& args, void* context) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = resources_.find(id);
    if (it == resources_.end()) {
        return VAL_NIL;
    }
    return it->second->call(op, args, context);
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
