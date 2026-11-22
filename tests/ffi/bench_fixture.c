#include <stdint.h>

// Scalar leaf calls
int64_t bench_leaf_i64(int64_t x) { return x * 1103515245LL + 12345LL; }
double bench_leaf_f64(double x) { return x * 1.0000001 + 0.5; }

// Bulk buffer pass
int64_t bench_sum_i64(const int64_t* p, int64_t n) {
    int64_t s = 0;
    for (int64_t i = 0; i < n; ++i) s += p[i];
    return s;
}

// C -> Lymar callback per element
typedef int64_t (*bench_cb)(int64_t);
int64_t bench_map_i64(bench_cb cb, int64_t n) {
    int64_t s = 0;
    for (int64_t i = 0; i < n; ++i) s += cb(i);
    return s;
}
