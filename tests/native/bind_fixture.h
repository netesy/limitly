// bind_fixture.h - C header exercising the 2b binding generator's type mapping.
// Functions cover: int return + int params, float, void, pointer, 0-arg, and >2-arg.

#ifndef BIND_FIXTURE_H
#define BIND_FIXTURE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// 0 params, int return
int32_t fixture_answer(void);

// 2 int params, int return
int32_t fixture_add(int32_t a, int32_t b);

// 1 int param, void return
void fixture_increment(int32_t* value);

// 2 double params, double return
double fixture_multiply(double x, double y);

// 1 pointer param, int return (string length)
int32_t fixture_strlen(const char* s);

// 3 params (generic fallback path)
int32_t fixture_clamp(int32_t lo, int32_t hi, int32_t val);

// size_t param, pointer return (allocated buffer)
void* fixture_alloc(size_t n);

#ifdef __cplusplus
}
#endif

#endif // BIND_FIXTURE_H
