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

float fixture_f32_add(float a, float b);

float fixture_mix_i_f(int32_t n, float f);

int32_t fixture_i32_f32(float x);

// ─── Struct-by-value fixtures (small flat aggregates) ────────────────────────

typedef struct { float x; float y; } CVec2;          // 8 bytes
typedef struct { int32_t x; int32_t y; } CIvec2;     // 8 bytes
typedef struct { float x; float y; float z; float w; } CVec4;  // 16 bytes
typedef struct { int32_t x; int32_t y; int32_t w; int32_t h; } CRect; // 16 bytes
typedef struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; } CColor; // 4 bytes
typedef struct { double x; double y; } CDVec2;       // 16 bytes

CVec2 cvec2_add(CVec2 a, CVec2 b);
float cvec2_dot(CVec2 a, CVec2 b);
CIvec2 civec2_add(CIvec2 a, CIvec2 b);
int32_t civec2_dot(CIvec2 a, CIvec2 b);
CColor ccolor_pack(uint32_t rgba);
uint32_t ccolor_unpack(CColor c);
int32_t crect_area(CRect r);
CRect crect_offset(CRect r, int32_t dx, int32_t dy);
CDVec2 cdvec2_make(double x, double y);
CDVec2 cdvec2_add(CDVec2 a, CDVec2 b);
double cdvec2_dot(CDVec2 a, CDVec2 b);
CVec4 cvec4_add(CVec4 a, CVec4 b);

#ifdef __cplusplus
}
#endif

#endif // CIMPORT_FIXTURE_H
