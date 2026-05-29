#include "intrinsic_registry.hh"

namespace LM {
namespace LIR {

IntrinsicRegistry& IntrinsicRegistry::getInstance() {
    static IntrinsicRegistry instance;
    return instance;
}

IntrinsicRegistry::IntrinsicRegistry() {
    // Memory Operations (formerly FFI)
    // std.ffi::alloc -> MemoryAlloc
    registerIntrinsic("std.ffi::alloc", {LIR_Op::MemoryAlloc, 0, 0, 1, 0});
    registerIntrinsic("std.ffi::free", {LIR_Op::MemoryFree, 0, 0, 1, 0});
    registerIntrinsic("std.ffi::realloc", {LIR_Op::MemoryResize, 0, 0, 2, 0});

    // MemoryLoad/Store with type_id (0: i8, 1: u8, 2: i16, 3: u16, 4: i32, 5: u32, 6: i64, 7: u64, 8: f32, 9: f64, 10: ptr)
    registerIntrinsic("std.ffi::load_i8", {LIR_Op::MemoryLoad, 0, 0, 1, 0});
    registerIntrinsic("std.ffi::load_u8", {LIR_Op::MemoryLoad, 0, 0, 1, 1});
    registerIntrinsic("std.ffi::load_i16", {LIR_Op::MemoryLoad, 0, 0, 1, 2});
    registerIntrinsic("std.ffi::load_u16", {LIR_Op::MemoryLoad, 0, 0, 1, 3});
    registerIntrinsic("std.ffi::load_i32", {LIR_Op::MemoryLoad, 0, 0, 1, 4});
    registerIntrinsic("std.ffi::load_u32", {LIR_Op::MemoryLoad, 0, 0, 1, 5});
    registerIntrinsic("std.ffi::load_i64", {LIR_Op::MemoryLoad, 0, 0, 1, 6});
    registerIntrinsic("std.ffi::load_u64", {LIR_Op::MemoryLoad, 0, 0, 1, 7});
    registerIntrinsic("std.ffi::load_f32", {LIR_Op::MemoryLoad, 0, 0, 1, 8});
    registerIntrinsic("std.ffi::load_f64", {LIR_Op::MemoryLoad, 0, 0, 1, 9});
    registerIntrinsic("std.ffi::load_ptr", {LIR_Op::MemoryLoad, 0, 0, 1, 10});

    registerIntrinsic("std.ffi::store_i8", {LIR_Op::MemoryStore, 0, 0, 2, 0});
    registerIntrinsic("std.ffi::store_u8", {LIR_Op::MemoryStore, 0, 0, 2, 1});
    registerIntrinsic("std.ffi::store_i16", {LIR_Op::MemoryStore, 0, 0, 2, 2});
    registerIntrinsic("std.ffi::store_u16", {LIR_Op::MemoryStore, 0, 0, 2, 3});
    registerIntrinsic("std.ffi::store_i32", {LIR_Op::MemoryStore, 0, 0, 2, 4});
    registerIntrinsic("std.ffi::store_u32", {LIR_Op::MemoryStore, 0, 0, 2, 5});
    registerIntrinsic("std.ffi::store_i64", {LIR_Op::MemoryStore, 0, 0, 2, 6});
    registerIntrinsic("std.ffi::store_u64", {LIR_Op::MemoryStore, 0, 0, 2, 7});
    registerIntrinsic("std.ffi::store_f32", {LIR_Op::MemoryStore, 0, 0, 2, 8});
    registerIntrinsic("std.ffi::store_f64", {LIR_Op::MemoryStore, 0, 0, 2, 9});
    registerIntrinsic("std.ffi::store_ptr", {LIR_Op::MemoryStore, 0, 0, 2, 10});

    // Foreign Call
    registerIntrinsic("std.ffi::ccall_execute", {LIR_Op::ForeignCall, 0, 0, 2, 0});

    // Legacy aliases for tests
    registerIntrinsic("std.ffi::ffi_alloc", {LIR_Op::MemoryAlloc, 0, 0, 1, 0});
    registerIntrinsic("std.ffi::ffi_free", {LIR_Op::MemoryFree, 0, 0, 1, 0});
}

void IntrinsicRegistry::registerIntrinsic(const std::string& qualified_name, const IntrinsicMetadata& meta) {
    intrinsics_[qualified_name] = meta;
}

std::optional<IntrinsicMetadata> IntrinsicRegistry::getIntrinsic(const std::string& qualified_name) const {
    auto it = intrinsics_.find(qualified_name);
    if (it != intrinsics_.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool IntrinsicRegistry::isIntrinsic(const std::string& qualified_name) const {
    return intrinsics_.find(qualified_name) != intrinsics_.end();
}

} // namespace LIR
} // namespace LM
