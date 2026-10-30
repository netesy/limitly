// cimport_fixture.h - C header for roadmap 2c `import "c:..."` syntax verification.
// Provides three functions covering: 0-arg, 2-arg, and 1-arg float call paths.

#ifndef CIMPORT_FIXTURE_H
#define CIMPORT_FIXTURE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t fixture_answer(void);

int32_t fixture_add(int32_t a, int32_t b);

float fixture_sqrt(float x);

#ifdef __cplusplus
}
#endif

#endif // CIMPORT_FIXTURE_H
