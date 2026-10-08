#define BUILDING_RUNTIME
#define _POSIX_C_SOURCE 200809L
#include "vm_runtime.hh"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

RUNTIME_API void lm_print_int(int64_t val) {
    printf("%ld\n", val);
}

RUNTIME_API void lm_print_string(const char* val) {
    if (val) printf("%s\n", val);
}

RUNTIME_API void lm_print_box(LmBox* box) {
    if (!box) {
        printf("null\n");
        return;
    }
    switch (box->type) {
        case LM_BOX_INT: printf("%ld\n", box->value.as_int); break;
        case LM_BOX_FLOAT: printf("%f\n", box->value.as_float); break;
        case LM_BOX_BOOL: printf("%s\n", box->value.as_bool ? "true" : "false"); break;
        case LM_BOX_STRING: printf("%s\n", (char*)box->value.as_ptr); break;
        case LM_BOX_NULLPTR: printf("null\n"); break;
        default: printf("<unknown box type %d>\n", box->type);
    }
}

RUNTIME_API void lm_assert(int condition, const char* message) {
    if (!condition) {
        fprintf(stderr, "Assertion failed: %s\n", message ? message : "unnamed assertion");
        abort();
    }
}

RUNTIME_API LmBox* lm_box_int(int64_t value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX; 
    box->header.metadata = 0;
    box->type = LM_BOX_INT;
    box->value.as_int = value;
    return box;
}

RUNTIME_API LmBox* lm_box_float(double value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX;
    box->header.metadata = 0;
    box->type = LM_BOX_FLOAT;
    box->value.as_float = value;
    return box;
}

RUNTIME_API LmValue lm_box_float_from_bits(uint64_t bits) {
    union {
        uint64_t u;
        double d;
    } u;
    u.u = bits;
    return BOX_PTR(lm_box_float(u.d));
}

RUNTIME_API LmBox* lm_box_bool(uint8_t value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX;
    box->header.metadata = 0;
    box->type = LM_BOX_BOOL;
    box->value.as_bool = value;
    return box;
}

RUNTIME_API LmBox* lm_box_string(const char* value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX;
    box->header.metadata = 0;
    box->type = LM_BOX_STRING;
    box->value.as_ptr = value ? strdup(value) : NULL;
    return box;
}

RUNTIME_API LmBox* lm_box_nullptr(void) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX;
    box->header.metadata = 0;
    box->type = LM_BOX_NULLPTR;
    box->value.as_ptr = NULL;
    return box;
}

RUNTIME_API int64_t lm_unbox_int(LmBox* box) {
    if (!box || box->type != LM_BOX_INT) return 0;
    return box->value.as_int;
}

RUNTIME_API double lm_unbox_float(LmBox* box) {
    if (!box || box->type != LM_BOX_FLOAT) return 0.0;
    return box->value.as_float;
}

RUNTIME_API uint8_t lm_unbox_bool(LmBox* box) {
    if (!box || box->type != LM_BOX_BOOL) return 0;
    return box->value.as_bool;
}

RUNTIME_API const char* lm_unbox_string(LmBox* box) {
    if (!box || box->type != LM_BOX_STRING) return NULL;
    return (const char*)box->value.as_ptr;
}

RUNTIME_API void* lm_unbox_ptr(LmBox* box) {
    if (!box || box->type != LM_BOX_NULLPTR) return NULL;
    return box->value.as_ptr;
}

RUNTIME_API void lm_box_free(LmBox* box) {
    if (!box) return;
    if (box->type == LM_BOX_STRING && box->value.as_ptr) {
        free(box->value.as_ptr);
    }
    free(box);
}

RUNTIME_API LmValue lm_alloc_i64(int64_t value) {
    ObjI64* obj = (ObjI64*)malloc(sizeof(ObjI64));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_I64;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_u64(uint64_t value) {
    ObjU64* obj = (ObjU64*)malloc(sizeof(ObjU64));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_U64;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_i128(__int128 value) {
    ObjI128* obj = (ObjI128*)malloc(sizeof(ObjI128));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_I128;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_u128(unsigned __int128 value) {
    ObjU128* obj = (ObjU128*)malloc(sizeof(ObjU128));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_U128;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_float(double value) {
    ObjFloat* obj = (ObjFloat*)malloc(sizeof(ObjFloat));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_FLOAT;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_foreign_ptr(void* ptr) {
    ObjForeignPtr* obj = (ObjForeignPtr*)malloc(sizeof(ObjForeignPtr));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_FOREIGN_PTR;
    obj->header.metadata = 0;
    obj->ptr = ptr;
    return BOX_PTR(obj);
}

RUNTIME_API void* lm_frame_alloc(const char* name, int fields) {
    LmFrame* frame = (LmFrame*)malloc(sizeof(LmFrame));
    if (!frame) return NULL;
    frame->header.type_id = TYPE_FRAME;
    frame->header.metadata = 0;
    frame->name = name ? strdup(name) : NULL;
    frame->field_count = fields;
    frame->fields = (LmValue*)malloc(sizeof(LmValue) * fields);
    for (int i = 0; i < fields; i++) frame->fields[i] = VAL_NIL;
    frame->mutex = NULL;
    return frame;
}

RUNTIME_API LmValue lm_frame_get_field(void* frame, int offset) {
    if (!frame) return VAL_NIL;
    LmFrame* f = (LmFrame*)frame;
    if (offset < 0 || offset >= f->field_count) return VAL_NIL;
    return f->fields[offset];
}

RUNTIME_API void lm_frame_set_field(void* frame, int offset, LmValue value) {
    if (!frame) return;
    LmFrame* f = (LmFrame*)frame;
    if (offset >= 0 && offset < f->field_count) {
        f->fields[offset] = value;
    }
}

RUNTIME_API LmValue lm_frame_get_field_atomic(void* frame, int offset) {
    return lm_frame_get_field(frame, offset);
}

RUNTIME_API void lm_frame_set_field_atomic(void* frame, int offset, LmValue value) {
    lm_frame_set_field(frame, offset, value);
}

RUNTIME_API void lm_frame_field_atomic_add(void* frame, int offset, LmValue value) {
    if (!frame) return;
    LmFrame* f = (LmFrame*)frame;
    if (offset >= 0 && offset < f->field_count) {
        f->fields[offset] += value;
    }
}

RUNTIME_API void lm_frame_field_atomic_sub(void* frame, int offset, LmValue value) {
    if (!frame) return;
    LmFrame* f = (LmFrame*)frame;
    if (offset >= 0 && offset < f->field_count) {
        f->fields[offset] -= value;
    }
}

RUNTIME_API void* lm_trait_dispatch(void* trait_obj, const char* trait_name, const char* method_name) {
    return NULL;
}

// Constants outlive individual VMs and instruction copies. Own each object once;
// children are separate entries so aliases and cyclic constant graphs are safe.
#include "vm_list.hh"
#include "vm_tuple.hh"
#include "vm_dict.hh"
#include <unordered_map>
#include <vector>
#include <mutex>
namespace {
struct ConstantPool {
    std::unordered_map<uintptr_t, uint32_t> objects;
    std::mutex mutex;
    ~ConstantPool() {
        for (auto [ptr, kind] : objects) {
            auto* h = reinterpret_cast<ObjHeader*>(ptr);
            switch (kind) {
                case TYPE_STRING: lm_str_free(reinterpret_cast<LmStringHeader*>(h)); break;
                case TYPE_LIST: lm_list_free(reinterpret_cast<LmList*>(h)); break;
                case TYPE_DICT: lm_dict_free(reinterpret_cast<LmDict*>(h)); break;
                case TYPE_TUPLE: lm_tuple_free(reinterpret_cast<LmTuple*>(h)); break;
                case TYPE_BOX: lm_box_free(reinterpret_cast<LmBox*>(h)); break;
                case TYPE_FRAME: {
                    auto* f = reinterpret_cast<LmFrame*>(h);
                    free(f->name); free(f->fields); free(f); break;
                }
                default: free(h); break;
            }
        }
    }
};
ConstantPool& constants() { static ConstantPool pool; return pool; }
}
void lm_keep_constant(LmValue value) {
    auto& pool = constants();
    std::lock_guard<std::mutex> lock(pool.mutex);
    std::vector<LmValue> work{value};
    while (!work.empty()) {
        auto v = work.back(); work.pop_back();
        if (!IS_PTR(v)) continue;
        auto ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(v));
        auto* h = reinterpret_cast<ObjHeader*>(ptr);
        if (!pool.objects.emplace(ptr, h->type_id).second) continue;
        if (h->type_id == TYPE_LIST) {
            auto* list = reinterpret_cast<LmList*>(h);
            for (uint64_t i = 0; i < list->size; ++i) work.push_back(list->data[i]);
        } else if (h->type_id == TYPE_TUPLE) {
            auto* tuple = reinterpret_cast<LmTuple*>(h);
            for (uint64_t i = 0; i < tuple->size; ++i) work.push_back(tuple->elements[i]);
        } else if (h->type_id == TYPE_DICT) {
            for (auto* e = reinterpret_cast<LmDict*>(h)->head; e; e = e->order_next) {
                work.push_back(e->key); work.push_back(e->value);
            }
        } else if (h->type_id == TYPE_FRAME) {
            auto* f = reinterpret_cast<LmFrame*>(h);
            for (int i = 0; i < f->field_count; ++i) work.push_back(f->fields[i]);
        } else if (h->type_id == TYPE_CLOSURE) work.push_back(reinterpret_cast<LmClosure*>(h)->captured_env);
    }
}
bool lm_is_constant(LmValue value) {
    if (!IS_PTR(value)) return false;
    auto& pool = constants();
    std::lock_guard<std::mutex> lock(pool.mutex);
    return pool.objects.count(reinterpret_cast<uintptr_t>(UNBOX_PTR(value))) != 0;
}
