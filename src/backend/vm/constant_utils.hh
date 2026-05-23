#ifndef LIMITLY_BACKEND_VM_CONSTANT_UTILS_H
#define LIMITLY_BACKEND_VM_CONSTANT_UTILS_H

#include "frontend/value.hh"
#include "backend/value.hh"
#include "runtime/runtime.h"
#include "runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {

inline LM::Backend::Value compiler_value_to_backend_value(const std::shared_ptr<::Value>& cv) {
    if (!cv) return VAL_NIL;
    if (cv->type->tag == ::TypeTag::Int || cv->type->tag == ::TypeTag::Int64) {
        return make_i64(std::stoll(cv->data));
    }
    if (cv->type->tag == ::TypeTag::String) {
        return BOX_PTR(lm_box_string(cv->data.c_str()));
    }
    if (cv->type->tag == ::TypeTag::Bool) {
        return (cv->data == "true") ? VAL_TRUE : VAL_FALSE;
    }
    return VAL_NIL;
}

} // namespace VM
} // namespace Backend
} // namespace LM

#endif // LIMITLY_BACKEND_VM_CONSTANT_UTILS_H
