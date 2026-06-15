#ifndef LIMITLY_BACKEND_VM_RESOURCE_MANAGER_H
#define LIMITLY_BACKEND_VM_RESOURCE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <mutex>
#include <functional>
#include <string>
#include <vector>
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

class ResourceManager {
public:
    static ResourceManager& getInstance();

    int64_t create(ResourceType type);
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
