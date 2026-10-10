// Link against liblymar/libfyra. Run each mode in a fresh process; an allocator
// interposer can count requests independently of the timed CPU/wall samples.
#include "backend/vm/register.hh"
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv) {
    using namespace LM;
    const int mode = argc > 1 ? std::atoi(argv[1]) : 0;
    const int count = argc > 2 ? std::atoi(argv[2]) : 500000;
    if (mode < 0 || mode > 7 || count <= 0) return 2;
    Backend::VM::Register::RegisterVM vm;
    LIR::LIR_Function raw("raw_region", 0);
    raw.instructions.emplace_back(LIR::LIR_Op::RegionEnter, LIR::Type::Void, 0, 0, 0, 1);
    raw.instructions.emplace_back(LIR::LIR_Op::LoadConst, LIR::Type::I64, 0, make_i64(64));
    raw.instructions.emplace_back(LIR::LIR_Op::MemoryAlloc, LIR::Type::Ptr, 1, 0, 0);
    raw.instructions.emplace_back(LIR::LIR_Op::RegionExit, LIR::Type::Void, 0, 0, 0, 1);
    // Modes 6/7 isolate empty exit/raw reclamation with live raw storage elsewhere.
    if (mode == 6 || mode == 7) {
        auto root = raw;
        root.instructions.erase(root.instructions.begin());
        root.instructions.pop_back();
        for (int i = 0; i < 2000; ++i) vm.execute(root);
    }
    const int region_mode = mode == 6 ? 2 : mode;
    volatile unsigned long control = 0;
    const auto wall = std::chrono::steady_clock::now();
    const auto cpu = std::clock();
    for (int i = 0; i < count; ++i) {
        if (mode == 0) { control = control + i; continue; }
        if (mode == 5 || mode == 7) { vm.execute(raw); continue; }
        auto depth = vm.begin_native_call();
        if (region_mode >= 2) vm.native_region(LIR::LIR_Op::RegionEnter, 1);
        if (region_mode >= 3) vm.native_region(LIR::LIR_Op::RegionEnter, 2);
        if (region_mode >= 4) vm.native_region(LIR::LIR_Op::RegionMove, 0, VAL_TRUE);
        if (region_mode >= 3) vm.native_region(LIR::LIR_Op::RegionExit, 2);
        if (region_mode >= 2) vm.native_region(LIR::LIR_Op::RegionExit, 1);
        vm.end_native_call(depth, VAL_TRUE);
    }
    const double cpu_ms = 1000.0 * (std::clock() - cpu) / CLOCKS_PER_SEC;
    const double wall_ms = std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - wall).count();
    std::printf("mode=%d iterations=%d cpu_ms=%.3f wall_ms=%.3f live_raw=%zu\n",
                mode, count, cpu_ms, wall_ms, vm.live_raw_allocation_count());
    const bool valid = vm.live_raw_allocation_count() == ((mode == 6 || mode == 7) ? 2000 : 0);
    vm.reset();
    return !valid || vm.live_raw_allocation_count() != 0;
}
