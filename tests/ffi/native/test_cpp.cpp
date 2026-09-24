#include <cstdint>
#include <cstring>
#include <cassert>

extern "C" {
    int32_t cpp_add(int32_t a, int32_t b) {
        return a + b;
    }

    double cpp_scale(double val, double factor) {
        return val * factor;
    }

    size_t cpp_strlen(const char* str) {
        return str ? std::strlen(str) : 0;
    }
}
