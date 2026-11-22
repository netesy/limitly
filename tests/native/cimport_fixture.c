// cimport_fixture.c - Implementation for roadmap 2c verification.
#include "cimport_fixture.h"
#include <math.h>

int32_t fixture_answer(void) { return 42; }

int32_t fixture_add(int32_t a, int32_t b) { return a + b; }

float fixture_sqrt(float x) { return (float)sqrt((double)x); }

float fixture_f32_add(float a, float b) { return a + b; }

float fixture_mix_i_f(int32_t n, float f) { return (float)(n * (double)f); }

int32_t fixture_i32_f32(float x) { return (int32_t)(x * 2.0f); }
