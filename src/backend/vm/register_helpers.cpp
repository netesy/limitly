#include "register.hh"
#include "../../runtime/runtime.h"
#include "../../runtime/runtime_value.h"
#include "../../runtime/runtime_list.h"
#include "../../runtime/runtime_dict.h"
#include "../../runtime/runtime_tuple.h"
#include <iostream>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void* box_register_value(const RegisterValue& value) {
    if (IS_PTR(value)) return UNBOX_PTR(value);
    if (IS_INT(value)) return lm_box_int(as_i64(value));
    if (IS_BOOL(value)) return lm_box_bool(UNBOX_BOOL(value));
    if (IS_NIL(value)) return lm_box_nullptr();

    // Check if it's a boxed float
    if (IS_PTR(value)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(value);
        if (h->type_id == TYPE_FLOAT) return lm_box_float(((ObjFloat*)h)->value);
    }

    return lm_box_nullptr();
}

RegisterValue unbox_register_value(void* boxed_value) {
    if (!boxed_value) return VAL_NIL;

    ObjHeader* header = (ObjHeader*)boxed_value;
    switch (header->type_id) {
        case TYPE_I64: return make_i64(((ObjI64*)header)->value);
        case TYPE_U64: return make_u64(((ObjU64*)header)->value);
        case TYPE_I128: return make_i128(((ObjI128*)header)->value);
        case TYPE_U128: return make_u128(((ObjU128*)header)->value);
        case TYPE_FLOAT: return make_float(((ObjFloat*)header)->value);
        case TYPE_BOX: {
            LmBox* box = (LmBox*)boxed_value;
            switch (box->type) {
                case LM_BOX_INT: return make_i64(box->value.as_int);
                case LM_BOX_FLOAT: return make_float(box->value.as_float);
                case LM_BOX_BOOL: return box->value.as_bool ? VAL_TRUE : VAL_FALSE;
                case LM_BOX_NULLPTR: return VAL_NIL;
                case LM_BOX_STRING: return BOX_PTR(box);
                default: return VAL_NIL;
            }
        }
        default:
            return BOX_PTR(boxed_value);
    }
}

ValuePtr register_to_value_ptr(RegisterValue rv) {
    if (is_integer(rv)) {
        LmString s = lm_value_to_string(rv);
        std::string str(s.data ? s.data : "0");
        lm_string_free(s);
        auto intType = std::make_shared<::Type>(::TypeTag::Int128);
        return std::make_shared<::Value>(intType, str);
    } else if (IS_BOOL(rv)) {
        auto boolType = std::make_shared<::Type>(::TypeTag::Bool);
        return std::make_shared<::Value>(boolType, UNBOX_BOOL(rv) ? "true" : "false");
    } else if (IS_PTR(rv)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(rv);
        if (h->type_id == TYPE_FLOAT) {
            auto floatType = std::make_shared<::Type>(::TypeTag::Float64);
            return std::make_shared<::Value>(floatType, std::to_string(((ObjFloat*)h)->value));
        } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
            auto stringType = std::make_shared<::Type>(::TypeTag::String);
            return std::make_shared<::Value>(stringType, (char*)((LmBox*)h)->value.as_ptr);
        } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_FLOAT) {
             auto floatType = std::make_shared<::Type>(::TypeTag::Float64);
             return std::make_shared<::Value>(floatType, std::to_string(((LmBox*)h)->value.as_float));
        }
    }
    auto nullType = std::make_shared<::Type>(::TypeTag::Nil);
    return std::make_shared<::Value>(nullType);
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
