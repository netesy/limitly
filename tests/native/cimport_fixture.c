// cimport_fixture.c - Implementation for roadmap 2c verification.
#include "cimport_fixture.h"
#include <math.h>

int32_t fixture_answer(void) { return 42; }

int32_t fixture_add(int32_t a, int32_t b) { return a + b; }

float fixture_sqrt(float x) { return (float)sqrt((double)x); }
