#ifndef LIMITLY_BACKEND_VM_RESOURCE_MANAGER_H
#define LIMITLY_BACKEND_VM_RESOURCE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <mutex>
#include <functional>
#include <string>
#include <vector>
#include <cstdint>
#include "resource_types.hh"
#include "../register_value.hh"

namespace LM {
namespace Backend {
namespace VM {

class Resource {
public:
    virtual ~Resource() = default;
    virtual ResourceType getType() const = 0;
    virtual RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* context = nullptr) = 0;
};

// Helper to extract a C-string from a RegisterValue (LM_BOX_STRING).
// Returns nullptr if the value is not a string.
const char* register_value_to_cstr(RegisterValue val);

// Helper to extract an int64 from a RegisterValue.
int64_t register_value_to_i64(RegisterValue val);

// Helper to extract a raw pointer from a RegisterValue (foreign ptr or int).
void* register_value_to_ptr(RegisterValue val);

class ResourceManager {
public:
    static ResourceManager& getInstance();

    // Create a resource of the given type. Optional creation args may be
    // provided (e.g. size for MEMORY, capacity for CHANNEL). Returns the
    // new resource id on success, or -1 on failure.
    int64_t create(ResourceType type, const std::vector<RegisterValue>& args = {});

    // Convenience overload that matches the historical 0-arg signature.
    int64_t create(ResourceType type) { return create(type, {}); }

    RegisterValue call(int64_t id, ResourceOperation op, const std::vector<RegisterValue>& args, void* context = nullptr);
    void destroy(int64_t id);

    void shutdown();

private:
    ResourceManager() = default;
    ~ResourceManager();

    std::unordered_map<int64_t, std::unique_ptr<Resource>> resources_;
    int64_t next_id_ = 1;
    std::mutex mutex_;
};

} // namespace VM
} // namespace Backend
} // namespace LM

#endif // LIMITLY_BACKEND_VM_RESOURCE_MANAGER_H
