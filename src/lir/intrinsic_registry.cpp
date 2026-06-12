#include "intrinsic_registry.hh"
#include "lir.hh"

namespace LM {
namespace LIR {

IntrinsicRegistry& IntrinsicRegistry::getInstance() {
    static IntrinsicRegistry instance;
    return instance;
}

IntrinsicRegistry::IntrinsicRegistry() {
    registerIntrinsic("std.ffi::alloc", {LIR_Op::MemoryAlloc, (uint8_t)Type::Ptr, 0, 1, 0});
    registerIntrinsic("std.ffi::free", {LIR_Op::MemoryFree, (uint8_t)Type::Void, 0, 1, 0});
    registerIntrinsic("std.ffi::realloc", {LIR_Op::MemoryResize, (uint8_t)Type::Ptr, 0, 2, 0});
    registerIntrinsic("std.ffi::load_i8", {LIR_Op::MemoryLoad, (uint8_t)Type::I64, 0, 1, 0});
    registerIntrinsic("std.ffi::load_u8", {LIR_Op::MemoryLoad, (uint8_t)Type::I64, 0, 1, 1});
    registerIntrinsic("std.ffi::load_i16", {LIR_Op::MemoryLoad, (uint8_t)Type::I64, 0, 1, 2});
    registerIntrinsic("std.ffi::load_u16", {LIR_Op::MemoryLoad, (uint8_t)Type::I64, 0, 1, 3});
    registerIntrinsic("std.ffi::load_i32", {LIR_Op::MemoryLoad, (uint8_t)Type::I64, 0, 1, 4});
    registerIntrinsic("std.ffi::load_u32", {LIR_Op::MemoryLoad, (uint8_t)Type::I64, 0, 1, 5});
    registerIntrinsic("std.ffi::load_i64", {LIR_Op::MemoryLoad, (uint8_t)Type::I64, 0, 1, 6});
    registerIntrinsic("std.ffi::load_u64", {LIR_Op::MemoryLoad, (uint8_t)Type::I64, 0, 1, 7});
    registerIntrinsic("std.ffi::load_f32", {LIR_Op::MemoryLoad, (uint8_t)Type::F64, 0, 1, 8});
    registerIntrinsic("std.ffi::load_f64", {LIR_Op::MemoryLoad, (uint8_t)Type::F64, 0, 1, 9});
    registerIntrinsic("std.ffi::load_ptr", {LIR_Op::MemoryLoad, (uint8_t)Type::Ptr, 0, 1, 10});
    registerIntrinsic("std.ffi::store_i8", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 0});
    registerIntrinsic("std.ffi::store_u8", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 1});
    registerIntrinsic("std.ffi::store_i16", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 2});
    registerIntrinsic("std.ffi::store_u16", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 3});
    registerIntrinsic("std.ffi::store_i32", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 4});
    registerIntrinsic("std.ffi::store_u32", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 5});
    registerIntrinsic("std.ffi::store_i64", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 6});
    registerIntrinsic("std.ffi::store_u64", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 7});
    registerIntrinsic("std.ffi::store_f32", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 8});
    registerIntrinsic("std.ffi::store_f64", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 9});
    registerIntrinsic("std.ffi::store_ptr", {LIR_Op::MemoryStore, (uint8_t)Type::Void, 0, 2, 10});
    registerIntrinsic("std.ffi::memset", {LIR_Op::MemoryFill, (uint8_t)Type::Void, 0, 3, 0});
    registerIntrinsic("std.ffi::memcpy", {LIR_Op::MemoryCopy, (uint8_t)Type::Void, 0, 3, 0});
    registerIntrinsic("std.ffi::memcmp", {LIR_Op::MemoryCompare, (uint8_t)Type::I64, 0, 3, 0});
    registerIntrinsic("std.ffi::ptr_add", {LIR_Op::PtrAdd, (uint8_t)Type::Ptr, 0, 2, 0});
    registerIntrinsic("std.ffi::ptr_sub", {LIR_Op::PtrSub, (uint8_t)Type::Ptr, 0, 2, 0});
    registerIntrinsic("std.ffi::ptr_diff", {LIR_Op::PtrDiff, (uint8_t)Type::I64, 0, 2, 0});
    registerIntrinsic("std.ffi::library_load", {LIR_Op::LibraryLoad, (uint8_t)Type::Ptr, 0, 1, 0});
    registerIntrinsic("std.ffi::library_unload", {LIR_Op::LibraryUnload, (uint8_t)Type::Void, 0, 1, 0});
    registerIntrinsic("std.ffi::library_get_symbol", {LIR_Op::LibrarySymbol, (uint8_t)Type::Ptr, 0, 2, 0});
    registerIntrinsic("std.ffi::ccall_execute1", {LIR_Op::ForeignCall, (uint8_t)Type::I64, 0, 0, 0});
    registerIntrinsic("std.ffi::ccall_execute1_ptr", {LIR_Op::ForeignCall, (uint8_t)Type::Ptr, 0, 0, 0});
    registerIntrinsic("std.ffi::ccall_execute1_void", {LIR_Op::ForeignCall, (uint8_t)Type::Void, 0, 0, 0});
    registerIntrinsic("std.ffi::ccall_execute3_ifps_ptr", {LIR_Op::ForeignCall, (uint8_t)Type::Ptr, 0, 0, 0});
    registerIntrinsic("std.ffi::ccall_execute3_piif", {LIR_Op::ForeignCall, (uint8_t)Type::Void, 0, 0, 0});
    registerIntrinsic("std.ffi::ccall_execute4_sppp_ptr", {LIR_Op::ForeignCall, (uint8_t)Type::Ptr, 0, 0, 0});
    registerIntrinsic("std.ffi::ccall_execute5_siiip_int", {LIR_Op::ForeignCall, (uint8_t)Type::I64, 0, 0, 0});
    registerIntrinsic("std.ffi::ffi_alloc", {LIR_Op::MemoryAlloc, (uint8_t)Type::Ptr, 0, 1, 0});
    registerIntrinsic("std.ffi::ffi_free", {LIR_Op::MemoryFree, (uint8_t)Type::Void, 0, 1, 0});
    registerIntrinsic("std.ffi::ffi_realloc", {LIR_Op::MemoryResize, (uint8_t)Type::Ptr, 0, 2, 0});
    registerIntrinsic("std.ffi::ffi_memset", {LIR_Op::MemoryFill, (uint8_t)Type::Void, 0, 3, 0});
    registerIntrinsic("std.ffi::ffi_memcpy", {LIR_Op::MemoryCopy, (uint8_t)Type::Void, 0, 3, 0});
}

void IntrinsicRegistry::registerIntrinsic(const std::string& qualified_name, const IntrinsicMetadata& meta) {
    intrinsics_[qualified_name] = meta;
}

std::optional<IntrinsicMetadata> IntrinsicRegistry::getIntrinsic(const std::string& qualified_name) const {
    auto it = intrinsics_.find(qualified_name);
    if (it != intrinsics_.end()) return it->second;
    return std::nullopt;
}

bool IntrinsicRegistry::isIntrinsic(const std::string& qualified_name) const {
    return intrinsics_.find(qualified_name) != intrinsics_.end();
}

} // namespace LIR
} // namespace LM
