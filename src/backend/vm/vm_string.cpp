#define BUILDING_RUNTIME
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "vm_string.hh"
#include "vm_list.hh"
#include "backend/utf8.hh"

#ifdef __cplusplus
extern "C" {
#endif

RUNTIME_API LmStringHeader* lm_str_alloc(uint64_t cap) {
    uint64_t initial_cap = cap > 0 ? cap : 16;
    LmStringHeader* str = (LmStringHeader*)malloc(sizeof(LmStringHeader) + initial_cap + 1);
    if (!str) return NULL;
    str->header.type_id = TYPE_STRING;
    str->header.metadata = 0;
    str->len = 0;
    str->cap = initial_cap;
    str->data[0] = '\0';
    return str;
}

RUNTIME_API LmStringHeader* lm_str_from_bytes(const char* data, uint64_t len) {
    LmStringHeader* str = lm_str_alloc(len);
    if (!str) return NULL;
    if (data && len > 0) {
        memcpy(str->data, data, len);
    }
    str->len = len;
    str->data[len] = '\0';
    return str;
}

RUNTIME_API LmStringHeader* lm_str_from_cstr(const char* cstr) {
    if (!cstr) return lm_str_from_bytes("", 0);
    return lm_str_from_bytes(cstr, strlen(cstr));
}

RUNTIME_API void lm_str_free(LmStringHeader* str) {
    if (str) {
        free(str);
    }
}

RUNTIME_API LmStringHeader* lm_str_concat(const LmStringHeader* a, const LmStringHeader* b) {
    uint64_t len_a = a ? a->len : 0;
    uint64_t len_b = b ? b->len : 0;
    uint64_t total_len = len_a + len_b;

    LmStringHeader* res = lm_str_alloc(total_len);
    if (!res) return NULL;

    if (len_a > 0 && a && a->data) memcpy(res->data, a->data, len_a);
    if (len_b > 0 && b && b->data) memcpy(res->data + len_a, b->data, len_b);

    res->len = total_len;
    res->data[total_len] = '\0';
    return res;
}

RUNTIME_API LmStringHeader* lm_str_substring(const LmStringHeader* str, int64_t start, int64_t end) {
    if (!str || start < 0) return lm_str_from_bytes("", 0);
    uint64_t ustart = (uint64_t)start;
    uint64_t uend = (end < 0) ? 0 : (uint64_t)end;
    if (uend > str->len) uend = str->len;
    if (ustart >= uend) return lm_str_from_bytes("", 0);

    return lm_str_from_bytes(str->data + ustart, uend - ustart);
}

RUNTIME_API uint8_t lm_str_byte_at(const LmStringHeader* str, uint64_t index) {
    if (!str || index >= str->len) return 0;
    return (uint8_t)str->data[index];
}

RUNTIME_API int64_t lm_str_index_of(const LmStringHeader* str, const LmStringHeader* needle) {
    if (!str || !needle || needle->len == 0 || needle->len > str->len) return -1;
    for (uint64_t i = 0; i <= str->len - needle->len; i++) {
        if (memcmp(str->data + i, needle->data, needle->len) == 0) {
            return (int64_t)i;
        }
    }
    return -1;
}

RUNTIME_API bool lm_str_contains(const LmStringHeader* str, const LmStringHeader* needle) {
    return lm_str_index_of(str, needle) != -1;
}

RUNTIME_API bool lm_str_starts_with(const LmStringHeader* str, const LmStringHeader* prefix) {
    if (!str || !prefix || prefix->len > str->len) return false;
    return memcmp(str->data, prefix->data, prefix->len) == 0;
}

RUNTIME_API bool lm_str_ends_with(const LmStringHeader* str, const LmStringHeader* suffix) {
    if (!str || !suffix || suffix->len > str->len) return false;
    return memcmp(str->data + (str->len - suffix->len), suffix->data, suffix->len) == 0;
}

RUNTIME_API LmStringHeader* lm_str_trim(const LmStringHeader* str) {
    if (!str || str->len == 0) return lm_str_from_bytes("", 0);

    uint64_t start = 0;
    while (start < str->len && isspace((unsigned char)str->data[start])) {
        start++;
    }

    uint64_t end = str->len;
    while (end > start && isspace((unsigned char)str->data[end - 1])) {
        end--;
    }

    return lm_str_from_bytes(str->data + start, end - start);
}

RUNTIME_API LmStringHeader* lm_str_to_lower(const LmStringHeader* str) {
    if (!str || str->len == 0) return lm_str_from_bytes("", 0);
    LmStringHeader* res = lm_str_from_bytes(str->data, str->len);
    for (uint64_t i = 0; i < res->len; i++) {
        if (res->data[i] >= 'A' && res->data[i] <= 'Z') {
            res->data[i] += ('a' - 'A');
        }
    }
    return res;
}

RUNTIME_API LmStringHeader* lm_str_to_upper(const LmStringHeader* str) {
    if (!str || str->len == 0) return lm_str_from_bytes("", 0);
    LmStringHeader* res = lm_str_from_bytes(str->data, str->len);
    for (uint64_t i = 0; i < res->len; i++) {
        if (res->data[i] >= 'a' && res->data[i] <= 'z') {
            res->data[i] -= ('a' - 'A');
        }
    }
    return res;
}

RUNTIME_API LmStringHeader* lm_str_replace(const LmStringHeader* str, const LmStringHeader* old_sub, const LmStringHeader* new_sub) {
    if (!str || !old_sub || old_sub->len == 0 || old_sub->len > str->len) {
        return str ? lm_str_from_bytes(str->data, str->len) : lm_str_from_bytes("", 0);
    }

    uint64_t count = 0;
    for (uint64_t i = 0; i <= str->len - old_sub->len;) {
        if (memcmp(str->data + i, old_sub->data, old_sub->len) == 0) {
            count++;
            i += old_sub->len;
        } else {
            i++;
        }
    }

    if (count == 0) {
        return lm_str_from_bytes(str->data, str->len);
    }

    uint64_t new_len = str->len - (count * old_sub->len) + (count * (new_sub ? new_sub->len : 0));
    LmStringHeader* res = lm_str_alloc(new_len);

    uint64_t last = 0;
    uint64_t out_idx = 0;
    for (uint64_t i = 0; i <= str->len - old_sub->len;) {
        if (memcmp(str->data + i, old_sub->data, old_sub->len) == 0) {
            uint64_t chunk = i - last;
            if (chunk > 0) {
                memcpy(res->data + out_idx, str->data + last, chunk);
                out_idx += chunk;
            }
            if (new_sub && new_sub->len > 0) {
                memcpy(res->data + out_idx, new_sub->data, new_sub->len);
                out_idx += new_sub->len;
            }
            i += old_sub->len;
            last = i;
        } else {
            i++;
        }
    }
    if (last < str->len) {
        uint64_t chunk = str->len - last;
        memcpy(res->data + out_idx, str->data + last, chunk);
        out_idx += chunk;
    }

    res->len = out_idx;
    res->data[out_idx] = '\0';
    return res;
}

RUNTIME_API uint64_t lm_str_decode_next(const LmStringHeader* str, uint64_t offset) {
    if (!str || offset >= str->len) return 0;
    uint64_t cur_offset = offset;
    uint32_t cp = 0;
    uint8_t consumed = 0;
    if (!utf8_decode_next(str->data, str->len, &cur_offset, &cp, &consumed)) {
        return 0;
    }
    return ((uint64_t)cp << 8) | (uint64_t)consumed;
}

RUNTIME_API LmStringHeader* lm_int_to_str(int64_t value) {
    char temp[32];
    int len = snprintf(temp, sizeof(temp), "%lld", (long long)value);
    if (len <= 0) return lm_str_from_bytes("", 0);
    return lm_str_from_bytes(temp, len);
}

RUNTIME_API LmStringHeader* lm_double_to_str(double value) {
    char temp[64];
    int len = snprintf(temp, sizeof(temp), "%.6g", value);
    if (len <= 0) return lm_str_from_bytes("", 0);
    return lm_str_from_bytes(temp, len);
}

RUNTIME_API LmStringHeader* lm_bool_to_str(uint8_t value) {
    const char* str = value ? "true" : "false";
    return lm_str_from_cstr(str);
}

RUNTIME_API LmStringHeader* lm_str_format(const LmStringHeader* format_str, const LmStringHeader* arg_str) {
    if (!format_str || !format_str->data) return arg_str ? lm_str_from_bytes(arg_str->data, arg_str->len) : lm_str_from_bytes("", 0);
    if (!arg_str || !arg_str->data) return lm_str_from_bytes(format_str->data, format_str->len);

    const char* pos = strstr(format_str->data, "%s");
    if (pos) {
        uint64_t before_len = pos - format_str->data;
        uint64_t after_len = format_str->len - before_len - 2;

        LmStringHeader* res = lm_str_alloc(before_len + arg_str->len + after_len);
        memcpy(res->data, format_str->data, before_len);
        memcpy(res->data + before_len, arg_str->data, arg_str->len);
        memcpy(res->data + before_len + arg_str->len, pos + 2, after_len);
        res->len = before_len + arg_str->len + after_len;
        res->data[res->len] = '\0';
        return res;
    } else {
        return lm_str_concat(format_str, arg_str);
    }
}

#ifdef __cplusplus
}
#endif

