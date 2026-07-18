#ifndef LM_BACKEND_FYRA_CAPABILITY_MAPPER_HH
#define LM_BACKEND_FYRA_CAPABILITY_MAPPER_HH

#include "lir/lir.hh"
#include <optional>
#include <string>

namespace LM {
namespace Backend {
namespace Fyra {

struct CapabilityDescriptor {
    std::string name;
    int min_args;
    int max_args;
    bool returns_value;
    bool fallible;
};

class CapabilityMapper {
public:
    static std::optional<CapabilityDescriptor> map(LIR::LIR_Op op);
};

} // namespace Fyra
} // namespace Backend
} // namespace LM

#endif // LM_BACKEND_FYRA_CAPABILITY_MAPPER_HH
