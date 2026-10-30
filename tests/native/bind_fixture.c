// bind_fixture.c - Implementation of the fixture header for 2b verification.
#include "bind_fixture.h"
#include <string.h>
#include <stdlib.h>

int32_t fixture_answer(void) { return 42; }

int32_t fixture_add(int32_t a, int32_t b) { return a + b; }

void fixture_increment(int32_t* value) { if (value) (*value)++; }

double fixture_multiply(double x, double y) { return x * y; }

int32_t fixture_strlen(const char* s) { return (int32_t)strlen(s); }

int32_t fixture_clamp(int32_t lo, int32_t hi, int32_t val) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

void* fixture_alloc(size_t n) { return malloc(n); }
