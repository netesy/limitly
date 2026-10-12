#pragma once
// Backend-private conversion surface for the standalone FFI adapter.
#include <cstdint>
extern "C" {
uint64_t lymar_aot_alloc(uint64_t);
uint64_t lymar_aot_nil();
uint64_t lymar_aot_box_float(double);
double lymar_aot_to_float(uint64_t,uint64_t);
uint64_t lymar_aot_to_integer(uint64_t,uint64_t);
uint64_t lymar_aot_arg_kind(uint64_t,uint64_t);
void lymar_aot_arg_set(uint64_t,uint64_t);
uint64_t lymar_aot_return_pointer();
const char* lymar_aot_ffi_string(uint64_t);
uint64_t lymar_aot_ffi_list_size(uint64_t);
uint64_t lymar_aot_ffi_list_item(uint64_t,uint64_t);
uint64_t lymar_aot_ffi_list_kind(uint64_t,uint64_t);
uint64_t lymar_aot_ffi_pointer(uint64_t,uint64_t);
uint64_t lymar_aot_ffi_wrap(uint64_t);
void lymar_aot_ffi_invalidate(uint64_t);
uint64_t lymar_aot_ffi_infer_type(uint64_t,uint64_t);
void lymar_aot_ffi_result_kind(uint64_t);
}
