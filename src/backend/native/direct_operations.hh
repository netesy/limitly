#pragma once
#include <cstdint>

namespace LM::Backend::Native {
// Private optional helper feature. Api layout and existing helper ordinals stay
// compatible; older hosts reject the new feature rather than silently falling back.
struct DirectOperations {
    uint32_t version;
    uint32_t size;
#define LM_NATIVE_OP(result, name, parameters) result (*name) parameters;
#include "direct_operations_fields.hh"
#undef LM_NATIVE_OP
};
inline constexpr const char* direct_operations_source =
    "struct DirectOperations { uint32_t version; uint32_t size;"
#define LM_NATIVE_OP(result, name, parameters) #result "(*" #name ")" #parameters ";"
#include "direct_operations_fields.hh"
#undef LM_NATIVE_OP
    "};\n"
    R"CPP(
static const DirectOperations* direct_operations(const Api* api, void* ctx) {
    struct Cached { const Api* api=nullptr; const DirectOperations* ops=nullptr; };
    static thread_local Cached cached;
    if(cached.api!=api) {
        auto* ops=reinterpret_cast<const DirectOperations*>(
            api->helper(ctx,HDirectOperations,1ULL,0,0,nullptr,nullptr,0));
        if(!ops || ops->version!=1 || ops->size!=sizeof(DirectOperations))
            throw std::runtime_error("Unsupported native direct operations");
        cached={api,ops};
    }
    return cached.ops;
}
)CPP";
}
