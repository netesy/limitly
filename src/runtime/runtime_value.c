#define BUILDING_RUNTIME
#define _POSIX_C_SOURCE 200809L
#include "runtime_value.h"
#include "runtime_value_base.h"
#include "runtime_list.h"
#include "runtime_dict.h"
#include "runtime_tuple.h"
#include "runtime_string.h"
#include "runtime.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

// Phase 6: Centralized Runtime Constructors
RUNTIME_API LmValue make_i64(int64_t v) {
    if (fits_smi_i64(v)) return BOX_INT(v);
    return lm_alloc_i64(v);
}

RUNTIME_API LmValue make_u64(uint64_t v) {
    if (fits_smi_u64(v)) return BOX_INT(v);
    return lm_alloc_u64(v);
}

RUNTIME_API LmValue make_i128(__int128 v) {
    if (v >= MIN_SMI && v <= MAX_SMI) return BOX_INT((int64_t)v);
    if (v >= INT64_MIN && v <= INT64_MAX) return lm_alloc_i64((int64_t)v);
    return lm_alloc_i128(v);
}

RUNTIME_API LmValue make_u128(unsigned __int128 v) {
    if (v <= (unsigned __int128)MAX_SMI) return BOX_INT((int64_t)v);
    if (v <= UINT64_MAX) return lm_alloc_u64((uint64_t)v);
    return lm_alloc_u128(v);
}

RUNTIME_API LmValue make_float(double v) {
    return lm_alloc_float(v);
}

// Phase 7: Centralized Extraction Helpers
RUNTIME_API bool is_integer(LmValue v) {
    if (IS_INT(v)) return true;
    if (IS_PTR(v)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(v);
        if (h->type_id == TYPE_I64 || h->type_id == TYPE_U64 ||
            h->type_id == TYPE_I128 || h->type_id == TYPE_U128) return true;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            return box->type == LM_BOX_INT;
        }
    }
    return false;
}

RUNTIME_API bool is_float(LmValue v) {
    if (IS_PTR(v)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(v);
        if (h->type_id == TYPE_FLOAT) return true;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            return box->type == LM_BOX_FLOAT;
        }
    }
    return false;
}

static inline bool is_numeric_internal(LmValue v) {
    return is_integer(v) || is_float(v);
}

RUNTIME_API int64_t as_i64(LmValue v) {
    if (IS_INT(v)) return UNBOX_INT(v);
    if (IS_PTR(v)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(v);
        if (h->type_id == TYPE_I64) return ((ObjI64*)h)->value;
        if (h->type_id == TYPE_U64) return (int64_t)((ObjU64*)h)->value;
        if (h->type_id == TYPE_I128) return (int64_t)((ObjI128*)h)->value;
        if (h->type_id == TYPE_U128) return (int64_t)((ObjU128*)h)->value;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            if (box->type == LM_BOX_INT) return box->value.as_int;
            if (box->type == LM_BOX_FLOAT) return (int64_t)box->value.as_float;
        }
    }
    return 0;
}

RUNTIME_API uint64_t as_u64(LmValue v) {
    if (IS_INT(v)) return (uint64_t)UNBOX_INT(v);
    if (IS_PTR(v)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(v);
        if (h->type_id == TYPE_I64) return (uint64_t)((ObjI64*)h)->value;
        if (h->type_id == TYPE_U64) return ((ObjU64*)h)->value;
        if (h->type_id == TYPE_I128) return (uint64_t)((ObjI128*)h)->value;
        if (h->type_id == TYPE_U128) return (uint64_t)((ObjU128*)h)->value;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            if (box->type == LM_BOX_INT) return (uint64_t)box->value.as_int;
        }
    }
    return 0;
}

RUNTIME_API __int128 as_i128(LmValue v) {
    if (IS_INT(v)) return (__int128)UNBOX_INT(v);
    if (IS_PTR(v)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(v);
        if (h->type_id == TYPE_I64) return (__int128)((ObjI64*)h)->value;
        if (h->type_id == TYPE_U64) return (__int128)((ObjU64*)h)->value;
        if (h->type_id == TYPE_I128) return ((ObjI128*)h)->value;
        if (h->type_id == TYPE_U128) return (__int128)((ObjU128*)h)->value;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            if (box->type == LM_BOX_INT) return (__int128)box->value.as_int;
            if (box->type == LM_BOX_FLOAT) return (__int128)box->value.as_float;
        }
    }
    return 0;
}

RUNTIME_API unsigned __int128 as_u128(LmValue v) {
    if (IS_INT(v)) return (unsigned __int128)UNBOX_INT(v);
    if (IS_PTR(v)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(v);
        if (h->type_id == TYPE_I64) return (unsigned __int128)((ObjI64*)h)->value;
        if (h->type_id == TYPE_U64) return (unsigned __int128)((ObjU64*)h)->value;
        if (h->type_id == TYPE_I128) return (unsigned __int128)((ObjI128*)h)->value;
        if (h->type_id == TYPE_U128) return ((ObjU128*)h)->value;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            if (box->type == LM_BOX_INT) return (unsigned __int128)box->value.as_int;
        }
    }
    return 0;
}

RUNTIME_API double as_float(LmValue v) {
    if (IS_PTR(v)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(v);
        if (h->type_id == TYPE_FLOAT) return ((ObjFloat*)h)->value;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            if (box->type == LM_BOX_FLOAT) return box->value.as_float;
            if (box->type == LM_BOX_INT) return (double)box->value.as_int;
        }
    }
    if (is_integer(v)) return (double)as_i64(v);
    return 0.0;
}

// Phase 13: Numeric Comparison
RUNTIME_API int numeric_compare(LmValue a, LmValue b) {
    if (a == b) return 0;
    if (is_numeric_internal(a) && is_numeric_internal(b)) {
        if (is_float(a) || is_float(b)) {
            double f1 = as_float(a);
            double f2 = as_float(b);
            if (f1 < f2) return -1;
            if (f1 > f2) return 1;
            return 0;
        } else {
            __int128 i1 = as_i128(a);
            __int128 i2 = as_i128(b);
            if (i1 < i2) return -1;
            if (i1 > i2) return 1;
            return 0;
        }
    }
    return (a < b) ? -1 : 1;
}

RUNTIME_API int lm_value_eq(LmValue v1, LmValue v2) {
    if (v1 == v2) return 1; if (IS_PTR(v1) && IS_PTR(v2)) { ObjHeader* h1 = (ObjHeader*)UNBOX_PTR(v1); ObjHeader* h2 = (ObjHeader*)UNBOX_PTR(v2); if (h1->type_id == h2->type_id && h1->type_id == TYPE_BOX) { LmBox* b1 = (LmBox*)h1; LmBox* b2 = (LmBox*)h2; if (b1->type == b2->type && b1->type == LM_BOX_STRING) return strcmp((char*)b1->value.as_ptr, (char*)b2->value.as_ptr) == 0; } }
    if (is_numeric_internal(v1) && is_numeric_internal(v2)) {
        if (is_float(v1) || is_float(v2)) {
            return as_float(v1) == as_float(v2);
        } else {
            return as_i128(v1) == as_i128(v2);
        }
    }
    return 0;
}

// Stringification
static void append_to_buffer(char** buf, uint64_t* pos, uint64_t* capacity, const char* str) {
    if (!str) return;
    uint64_t str_len = strlen(str);
    while (*pos + str_len >= *capacity) {
        *capacity *= 2;
        char* new_buf = (char*)realloc(*buf, *capacity);
        if (!new_buf) return;
        *buf = new_buf;
    }
    memcpy(*buf + *pos, str, str_len);
    *pos += str_len;
}

static char* int128_to_str(__int128 n) {
    char* buf = (char*)malloc(64);
    if (n == 0) { strcpy(buf, "0"); return buf; }
    int sign = 0;
    if (n < 0) { sign = 1; n = -n; }
    int i = 62;
    buf[63] = '\0';
    while (n > 0) {
        buf[i--] = (char)((n % 10) + '0');
        n /= 10;
    }
    if (sign) buf[i--] = '-';
    char* res = strdup(&buf[i+1]);
    free(buf);
    return res;
}

static char* uint128_to_str(unsigned __int128 n) {
    char* buf = (char*)malloc(64);
    if (n == 0) { strcpy(buf, "0"); return buf; }
    int i = 62;
    buf[63] = '\0';
    while (n > 0) {
        buf[i--] = (char)((n % 10) + '0');
        n /= 10;
    }
    char* res = strdup(&buf[i+1]);
    free(buf);
    return res;
}

static LmString format_value(LmValue value);

static LmString format_list(LmList* list) {
    uint64_t capacity = 256;
    char* buf = (char*)malloc(capacity);
    uint64_t pos = 0;
    buf[0] = 0;
    append_to_buffer(&buf, &pos, &capacity, "[");
    for (uint64_t i = 0; i < list->size; i++) {
        if (i > 0) append_to_buffer(&buf, &pos, &capacity, ", ");
        LmString s = format_value(list->data[i]);
        append_to_buffer(&buf, &pos, &capacity, s.data ? s.data : "nil");
        lm_string_free(s);
    }
    append_to_buffer(&buf, &pos, &capacity, "]");
    buf[pos] = 0;
    return (LmString){ buf, pos };
}

static LmString format_value(LmValue value) {
    if (IS_INT(value)) return lm_int_to_string(UNBOX_INT(value));
    if (IS_NIL(value)) return lm_string_from_cstr("nil");
    if (IS_BOOL(value)) return lm_bool_to_string(UNBOX_BOOL(value) ? 1 : 0);
    if (IS_PTR(value)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(value);
        switch (h->type_id) {
            case TYPE_BOX: {
                LmBox* box = (LmBox*)h;
                switch (box->type) {
                    case LM_BOX_INT: return lm_int_to_string(box->value.as_int);
                    case LM_BOX_FLOAT: return lm_double_to_string(box->value.as_float);
                    case LM_BOX_BOOL: return lm_bool_to_string(box->value.as_bool);
                    case LM_BOX_STRING: return lm_string_from_cstr((char*)box->value.as_ptr);
                    case LM_BOX_NULLPTR: return lm_string_from_cstr("nil");
                }
                break;
            }
            case TYPE_I64: return lm_int_to_string(((ObjI64*)h)->value);
            case TYPE_U64: {
                char b[64];
                snprintf(b, sizeof(b), "%" PRIu64, ((ObjU64*)h)->value);
                return lm_string_from_cstr(b);
            }
            case TYPE_I128: {
                char* s = int128_to_str(((ObjI128*)h)->value);
                LmString res = lm_string_from_cstr(s);
                free(s);
                return res;
            }
            case TYPE_U128: {
                char* s = uint128_to_str(((ObjU128*)h)->value);
                LmString res = lm_string_from_cstr(s);
                free(s);
                return res;
            }
            case TYPE_FLOAT: return lm_double_to_string(((ObjFloat*)h)->value);
            case TYPE_LIST: return format_list((LmList*)h);
            case TYPE_FRAME: return lm_string_from_cstr(((LmFrame*)h)->name);
            default: break;
        }
    }
    return lm_string_from_cstr("<unknown>");
}

RUNTIME_API LmString lm_value_to_string(LmValue value) {
    return format_value(value);
}

// Phase 12: Overflow-aware Arithmetic
RUNTIME_API LmValue lm_add(LmValue a, LmValue b) {
    if (is_integer(a) && is_integer(b)) {
        __int128 i1 = as_i128(a);
        __int128 i2 = as_i128(b);
        __int128 res;
        if (__builtin_add_overflow(i1, i2, &res)) return VAL_NIL;
        return make_i128(res);
    }
    if (is_numeric_internal(a) && is_numeric_internal(b)) {
        return make_float(as_float(a) + as_float(b));
    }
    return VAL_NIL;
}

RUNTIME_API LmValue lm_sub(LmValue a, LmValue b) {
    if (is_integer(a) && is_integer(b)) {
        __int128 i1 = as_i128(a);
        __int128 i2 = as_i128(b);
        __int128 res;
        if (__builtin_sub_overflow(i1, i2, &res)) return VAL_NIL;
        return make_i128(res);
    }
    if (is_numeric_internal(a) && is_numeric_internal(b)) {
        return make_float(as_float(a) - as_float(b));
    }
    return VAL_NIL;
}

RUNTIME_API LmValue lm_mul(LmValue a, LmValue b) {
    if (is_integer(a) && is_integer(b)) {
        __int128 i1 = as_i128(a);
        __int128 i2 = as_i128(b);
        __int128 res;
        if (__builtin_mul_overflow(i1, i2, &res)) return VAL_NIL;
        return make_i128(res);
    }
    if (is_numeric_internal(a) && is_numeric_internal(b)) {
        return make_float(as_float(a) * as_float(b));
    }
    return VAL_NIL;
}

RUNTIME_API LmValue lm_div(LmValue a, LmValue b) {
    if (is_integer(a) && is_integer(b)) {
        __int128 i1 = as_i128(a);
        __int128 i2 = as_i128(b);
        if (i2 == 0) return VAL_NIL;
        return make_i128(i1 / i2);
    }
    if (is_numeric_internal(a) && is_numeric_internal(b)) {
        double f2 = as_float(b);
        if (f2 == 0.0) return VAL_NIL;
        return make_float(as_float(a) / f2);
    }
    return VAL_NIL;
}
