#include "resource_manager.hh"
#include <iostream>

namespace LM {
namespace Backend {
namespace VM {

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::~ResourceManager() {
    shutdown();
}

int64_t ResourceManager::create(ResourceType type) {
    std::lock_guard<std::mutex> lock(mutex_);
    int64_t id = next_id_++;

    // Resource creation logic will be added here or in specific resource factories
    // For now, return -1 as not implemented
    return -1;
}

RegisterValue ResourceManager::call(int64_t id, ResourceOperation op, const std::vector<RegisterValue>& args, void* context) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = resources_.find(id);
    if (it == resources_.end()) {
        return VAL_NIL;
    }
    return it->second->call(op, args);
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
