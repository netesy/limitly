#ifndef LIMITLY_LIR_INTRINSIC_REGISTRY_H
#define LIMITLY_LIR_INTRINSIC_REGISTRY_H

#include "lir.hh"
#include <string>
#include <unordered_map>
#include <optional>
#include <vector>

namespace LM {
namespace LIR {

struct IntrinsicMetadata {
    LIR_Op opcode;
    uint32_t resource_type;
    uint32_t operation_type;
    uint32_t arity;
    uint32_t type_id; // For MemoryLoad/Store
};

class IntrinsicRegistry {
public:
    static IntrinsicRegistry& getInstance();
    
    void registerIntrinsic(const std::string& qualified_name, const IntrinsicMetadata& meta);
    std::optional<IntrinsicMetadata> getIntrinsic(const std::string& qualified_name) const;
    bool isIntrinsic(const std::string& qualified_name) const;

private:
    IntrinsicRegistry();
    std::unordered_map<std::string, IntrinsicMetadata> intrinsics_;
};

} // namespace LIR
} // namespace LM

#endif // LIMITLY_LIR_INTRINSIC_REGISTRY_H
