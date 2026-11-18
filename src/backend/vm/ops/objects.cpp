#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"
#include "../vm_string.hh"
#include <stdexcept>
#include <string>
#include <cstring>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_objects(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::MakeEnum: {
            // In the unified model, Enum is a specialized LmFrame with 3 fields: [tag, payload, variant_name]
            void* enum_obj = lm_frame_alloc("__lir_internal_enum__", 3);
            lm_frame_set_field(enum_obj, 0, make_i64(static_cast<int64_t>(pc->imm)));
            lm_frame_set_field(enum_obj, 1, pc->a == UINT32_MAX ? VAL_NIL : registers[pc->a]);
            lm_frame_set_field(enum_obj, 2, pc->func_name.empty() ? VAL_NIL : BOX_PTR(lm_str_from_cstr(pc->func_name.c_str())));
            registers[pc->dst] = BOX_PTR(enum_obj);
            break;
        }
        case LIR::LIR_Op::ConstructError: {
            // Error union with [is_error=1, payload]
            void* err_obj = lm_frame_alloc("__lir_internal_error__", 2);
            lm_frame_set_field(err_obj, 0, make_i64(1));
            LmValue payload = pc->a == UINT32_MAX ? VAL_NIL : registers[pc->a];
            if (!argument_stack.empty()) {
                payload = argument_stack.back();
                argument_stack.pop_back();
            }
            lm_frame_set_field(err_obj, 1, payload);
            registers[pc->dst] = BOX_PTR(err_obj);
            break;
        }
        case LIR::LIR_Op::ConstructOk: {
            // Error union with [is_error=0, payload]
            void* ok_obj = lm_frame_alloc("__lir_internal_ok__", 2);
            lm_frame_set_field(ok_obj, 0, make_i64(0));
            lm_frame_set_field(ok_obj, 1, pc->a == UINT32_MAX ? VAL_NIL : registers[pc->a]);
            registers[pc->dst] = BOX_PTR(ok_obj);
            break;
        }
        case LIR::LIR_Op::IsError: {
            registers[pc->dst] = VAL_FALSE;
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                ObjHeader* h = (ObjHeader*)obj;
                if (h && h->type_id == TYPE_FRAME) {
                    LmFrame* f = (LmFrame*)obj;
                    if (f->name && (std::strcmp(f->name, "__lir_internal_ok__") == 0 ||
                                    std::strcmp(f->name, "__lir_internal_error__") == 0)) {
                        LmValue is_err = lm_frame_get_field(obj, 0);
                        registers[pc->dst] = (as_i64(is_err) != 0) ? VAL_TRUE : VAL_FALSE;
                    }
                }
            }
            break;
        }
        case LIR::LIR_Op::Unwrap: {
            registers[pc->dst] = registers[pc->a];
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                ObjHeader* h = (ObjHeader*)obj;
                if (h && h->type_id == TYPE_FRAME) {
                    LmFrame* f = (LmFrame*)obj;
                    if (f->name && (std::strcmp(f->name, "__lir_internal_ok__") == 0 ||
                                    std::strcmp(f->name, "__lir_internal_error__") == 0)) {
                        registers[pc->dst] = lm_frame_get_field(obj, 1);
                    }
                }
            }
            break;
        }
        case LIR::LIR_Op::UnwrapOr: {
            // pc->a = Ok/Error union, pc->b = default value (may be UINT32_MAX
            // meaning "no default supplied" -- in that case fall back to NIL).
            RegisterValue fallback = (pc->b != UINT32_MAX) ? registers[pc->b] : VAL_NIL;
            registers[pc->dst] = registers[pc->a];
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                ObjHeader* h = (ObjHeader*)obj;
                if (h && h->type_id == TYPE_FRAME) {
                    LmFrame* f = (LmFrame*)obj;
                    if (f->name && (std::strcmp(f->name, "__lir_internal_ok__") == 0 ||
                                    std::strcmp(f->name, "__lir_internal_error__") == 0)) {
                        LmValue is_err = lm_frame_get_field(obj, 0);
                        registers[pc->dst] = (as_i64(is_err) != 0) ? fallback : lm_frame_get_field(obj, 1);
                    }
                }
            }
            break;
        }
        case LIR::LIR_Op::GetTag: {
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = lm_frame_get_field(obj, 0);
            }
            break;
        }
        case LIR::LIR_Op::GetPayload: {
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = lm_frame_get_field(obj, 1);
            }
            break;
        }
        default:
            throw std::runtime_error(
                "VM: execute_objects: unsupported opcode " +
                std::to_string(static_cast<int>(pc->op)));
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
