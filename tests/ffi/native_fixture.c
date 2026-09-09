#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int32_t add_i32(int32_t a, int32_t b) {
    return a + b;
}

double multiply_double(double a, double b) {
    return a * b;
}

void increment_i32(int32_t* ptr) {
    if (ptr) {
        *ptr += 1;
    }
}

int32_t string_len(const char* str) {
    if (!str) return 0;
    return (int32_t)strlen(str);
}

typedef int32_t (*binary_op_fn)(int32_t, int32_t);

int32_t invoke_callback(binary_op_fn cb, int32_t a, int32_t b) {
    if (!cb) return 0;
    return cb(a, b);
}
