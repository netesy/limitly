#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int32_t add_i32(int32_t a, int32_t b) {
    return a + b;
}

int64_t factorial(int64_t n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

double multiply_f64(double a, double b) {
    return a * b;
}

const char* hello(void) {
    return "Hello from C native library!";
}

size_t string_length(const char* text) {
    if (!text) return 0;
    return strlen(text);
}

int mutate_value(int32_t* value) {
    if (!value) return 0;
    *value = *value * 2;
    return 1;
}

typedef int (*callback_fn)(int);

int apply_callback(callback_fn fn, int value) {
    if (!fn) return -1;
    return fn(value);
}
