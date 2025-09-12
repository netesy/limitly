#include "lembed.hh"
#include <mutex>

namespace lembed {
    static std::unordered_map<std::string, Bytecode> embeds;
    static std::mutex embeds_mutex;

    void registerEmbed(const std::string& name, const Bytecode& bc) {
        std::lock_guard<std::mutex> lock(embeds_mutex);
        embeds[name] = bc;
    }

    const Bytecode* getEmbeddedBytecode(const std::string& name) {
        std::lock_guard<std::mutex> lock(embeds_mutex);
        auto it = embeds.find(name);
        if (it == embeds.end()) return nullptr;
        return &it->second;
    }

    std::vector<std::string> listEmbeddedNames() {
        std::lock_guard<std::mutex> lock(embeds_mutex);
        std::vector<std::string> names;
        names.reserve(embeds.size());
        for (auto &p : embeds) names.push_back(p.first);
        return names;
    }
}
