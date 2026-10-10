#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstdint>
extern "C" {
uint64_t lymar_aot_call_enter();
void lymar_aot_call_leave(uint64_t);
void lymar_aot_region_enter(uint64_t);
void lymar_aot_region_exit(uint64_t);
void lymar_aot_region_move(uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t lymar_aot_alloc(uint64_t);
uint64_t lymar_aot_live_allocations();
}
int main(int argc, char** argv) {
    const int mode = argc > 1 ? std::atoi(argv[1]) : 0;
    const int count = argc > 2 ? std::atoi(argv[2]) : 500000;
    if (mode < 0 || mode > 5 || count <= 0) return 2;
    volatile unsigned long control = 0;
    const auto wall = std::chrono::steady_clock::now();
    const auto cpu = std::clock();
    for (int i = 0; i < count; ++i) {
        if (mode == 0) { control = control + i; continue; }
        const auto caller = lymar_aot_call_enter();
        if (mode >= 2) lymar_aot_region_enter(1);
        if (mode >= 3 && mode != 5) lymar_aot_region_enter(2);
        if (mode == 4) lymar_aot_region_move(1, 0, caller, 0);
        if (mode == 5) (void)lymar_aot_alloc(64);
        if (mode >= 3 && mode != 5) lymar_aot_region_exit(2);
        if (mode >= 2) lymar_aot_region_exit(1);
        lymar_aot_call_leave(caller);
    }
    const double cpu_ms = 1000.0 * (std::clock() - cpu) / CLOCKS_PER_SEC;
    const double wall_ms = std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - wall).count();
    std::printf("mode=%d iterations=%d cpu_ms=%.3f wall_ms=%.3f live=%llu\n", mode, count,
                cpu_ms, wall_ms, static_cast<unsigned long long>(lymar_aot_live_allocations()));
    return lymar_aot_live_allocations() != 0;
}
