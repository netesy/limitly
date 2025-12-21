#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Platform-specific monotonic tick counter
// Header-only implementation - no .c file needed!
static inline uint64_t get_ticks(void) {
#ifdef __linux__
    #include <time.h>
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
#elif defined(_WIN32)
    #include <windows.h>
    return GetTickCount64();
#elif defined(BARE_METAL_ARM)
    extern volatile uint64_t systick_ms;
    return systick_ms;
#else
    // Fallback: Simple counter (NOT thread-safe but we're single-threaded!)
    static uint64_t simple_counter = 0;
    return simple_counter++;
#endif
}

#ifdef __cplusplus
}
#endif

#endif // PLATFORM_H
