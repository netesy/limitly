#pragma once
#include "model.hh"
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

namespace LM::Frontend::AST { struct Program; }
namespace LM::Memory {
using Identity = uint64_t;
enum ParameterEffect : uint8_t { Read = 1, Mutate = 2, Consume = 4, Retain = 8, Opaque = 16 };
struct SemanticEffects {
    std::vector<uint8_t> parameters;
    std::set<uint32_t> return_aliases, return_projections;
    std::set<Identity> captures_read, captures_consumed;
    bool unknown_result = false;
    std::set<Identity> returned_callables, returned_globals;
    std::map<Identity, uint32_t> returned_capture_parameters;
    // Ownership obligations depending on captured formals, discharged by callers.
    std::set<Identity> captures_opaque;
    bool operator==(const SemanticEffects&) const = default;
};
struct OwnershipEvent {
    std::vector<Identity> reads, consumes, defines, initializes;
    std::vector<std::pair<Identity, Identity>> aliases;
    bool empty() const { return reads.empty() && consumes.empty() && defines.empty() && initializes.empty() && aliases.empty(); }
    bool operator==(const OwnershipEvent&) const = default;
};
struct NodeOwnership {
    Identity binding = 0, allocation = 0, region = 0;
    OwnershipEvent event;
    std::vector<Ownership> arguments;
    std::set<Identity> origins;
    bool managed = false, unknown_origin = false;
};
struct SemanticFacts {
    std::map<Identity, NodeOwnership> nodes;
    std::map<Identity, SemanticEffects> functions;
    std::map<Identity, std::vector<Identity>> parameters;
    std::map<Identity, std::string> names;
    std::set<Identity> reference_bindings, global_bindings;
    std::map<std::string, std::set<Identity>> module_initializations;
    std::vector<std::string> errors;
    bool verified = false;
};
std::shared_ptr<SemanticFacts> analyze_ownership(const std::shared_ptr<Frontend::AST::Program>& program, const std::set<std::string>& intrinsics = {});
} // namespace LM::Memory
