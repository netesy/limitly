// cimport_fixture.c - Implementation for roadmap 2c verification.
#include "cimport_fixture.h"
#include <math.h>

int32_t fixture_answer(void) { return 42; }

int32_t fixture_add(int32_t a, int32_t b) { return a + b; }

float fixture_sqrt(float x) { return (float)sqrt((double)x); }

float fixture_f32_add(float a, float b) { return a + b; }

float fixture_mix_i_f(int32_t n, float f) { return (float)(n * (double)f); }

int32_t fixture_i32_f32(float x) { return (int32_t)(x * 2.0f); }

// ─── Struct-by-value implementations ─────────────────────────────────────────

CVec2 cvec2_add(CVec2 a, CVec2 b) {
    CVec2 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

float cvec2_dot(CVec2 a, CVec2 b) {
    return a.x * b.x + a.y * b.y;
}

CIvec2 civec2_add(CIvec2 a, CIvec2 b) {
    CIvec2 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

int32_t civec2_dot(CIvec2 a, CIvec2 b) {
    return a.x * b.x + a.y * b.y;
}

CColor ccolor_pack(uint32_t rgba) {
    CColor c;
    c.r = (uint8_t)(rgba & 0xFF);
    c.g = (uint8_t)((rgba >> 8) & 0xFF);
    c.b = (uint8_t)((rgba >> 16) & 0xFF);
    c.a = (uint8_t)((rgba >> 24) & 0xFF);
    return c;
}

uint32_t ccolor_unpack(CColor c) {
    return (uint32_t)c.r | ((uint32_t)c.g << 8) |
           ((uint32_t)c.b << 16) | ((uint32_t)c.a << 24);
}

int32_t crect_area(CRect r) {
    return r.w * r.h;
}

CRect crect_offset(CRect r, int32_t dx, int32_t dy) {
    CRect o;
    o.x = r.x + dx;
    o.y = r.y + dy;
    o.w = r.w;
    o.h = r.h;
    return o;
}

CDVec2 cdvec2_make(double x, double y) {
    CDVec2 v;
    v.x = x;
    v.y = y;
    return v;
}

CVec4 cvec4_add(CVec4 a, CVec4 b) {
    CVec4 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    r.w = a.w + b.w;
    return r;
}

CDVec2 cdvec2_add(CDVec2 a, CDVec2 b) {
    CDVec2 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

double cdvec2_dot(CDVec2 a, CDVec2 b) {
    return a.x * b.x + a.y * b.y;
}
