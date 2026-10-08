#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
extern "C" {
uint64_t lymar_aot_call_enter();
void lymar_aot_call_leave(uint64_t);
uint64_t lymar_aot_region_current();
void lymar_aot_region_enter(uint64_t);
void lymar_aot_region_exit(uint64_t);
void lymar_aot_region_move(uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t lymar_aot_alloc(uint64_t);
void lymar_aot_edge(uint64_t, uint64_t, uint64_t);
void lymar_aot_copy(uint64_t, uint64_t, uint64_t);
uint64_t lymar_aot_resize(uint64_t, uint64_t);
void lymar_aot_set_finalizer(uint64_t, void (*)(uint64_t));
void lymar_aot_finalize(uint64_t);
uint64_t lymar_aot_live_allocations();
uint64_t lymar_aot_slot_pointer(uint64_t);
void lymar_aot_param_push(uint64_t, uint64_t);
uint64_t lymar_aot_param_pop(uint64_t, uint64_t);
uint64_t lymar_aot_return_pointer();
void lymar_aot_reset();
}
static int finalized = 0;
static void finalizer(uint64_t) { ++finalized; }
static void store(uint64_t address, uint64_t value, bool pointer) {
    std::memcpy(reinterpret_cast<void*>(address), &value, 8);
    lymar_aot_edge(address, value, pointer);
}
int main() {
    auto caller = lymar_aot_call_enter();
    lymar_aot_param_push(42, 1);
    lymar_aot_call_enter();
    assert(lymar_aot_param_pop(7, 0) == 7);
    assert(lymar_aot_return_pointer() == 0);
    lymar_aot_param_push(99, 0);
    assert(lymar_aot_param_pop(7, 1) == 99);
    assert(lymar_aot_return_pointer() == 0);
    lymar_aot_call_leave(0);
    assert(lymar_aot_param_pop(7, 0) == 42);
    assert(lymar_aot_return_pointer() == 1);
    lymar_aot_region_enter(1);
    auto outer_region = lymar_aot_region_current();
    auto outer = lymar_aot_alloc(16);
    lymar_aot_region_enter(1); // Recursive lexical identity.
    assert(lymar_aot_region_current() != outer_region);
    auto child = lymar_aot_alloc(16);
    store(outer, child, true); // Child must outlive the older container.
    store(child, outer, true); // Cycle and alias.
    lymar_aot_alloc(8); // Unescaped scratch.
    lymar_aot_region_exit(1);
    assert(lymar_aot_live_allocations() == 2);
    lymar_aot_region_move(outer, 0, caller, true);
    lymar_aot_region_exit(1);
    lymar_aot_call_leave(true);
    assert(lymar_aot_live_allocations() == 2);
    lymar_aot_reset();
    assert(lymar_aot_live_allocations() == 0);

    caller = lymar_aot_call_enter();
    lymar_aot_region_enter(2);
    outer = lymar_aot_alloc(16);
    lymar_aot_region_enter(3);
    child = lymar_aot_alloc(16);
    store(outer, child, false); // Exact same bits, but this is an integer.
    lymar_aot_set_finalizer(child, finalizer);
    lymar_aot_finalize(child);
    lymar_aot_region_exit(3);
    assert(finalized == 1);
    assert(lymar_aot_live_allocations() == 1);
    lymar_aot_region_exit(2);
    lymar_aot_call_leave(false);

    caller = lymar_aot_call_enter();
    lymar_aot_region_enter(4);
    outer = lymar_aot_alloc(16);
    child = lymar_aot_alloc(16);
    store(outer, child, true);
    auto copy = lymar_aot_alloc(16);
    lymar_aot_copy(copy, outer, 16);
    copy = lymar_aot_resize(copy, 32);
    lymar_aot_region_move(copy, 0, caller, true);
    lymar_aot_region_exit(4);
    lymar_aot_call_leave(true);
    assert(lymar_aot_live_allocations() == 2);
    lymar_aot_reset();
    assert(lymar_aot_live_allocations() == 0);

    caller = lymar_aot_call_enter();
    lymar_aot_region_enter(5);
    auto source = lymar_aot_alloc(8), destination = lymar_aot_alloc(8);
    child = lymar_aot_alloc(8);
    store(destination, child, true);
    store(source, 123, false);
    lymar_aot_copy(destination, source, 8);
    assert(lymar_aot_slot_pointer(destination) == 0); // Overwrite must clear pointer metadata.
    lymar_aot_region_move(destination, 0, caller, true);
    lymar_aot_region_exit(5);
    lymar_aot_call_leave(true);
    assert(lymar_aot_live_allocations() == 1); // The former child must not escape.
    lymar_aot_reset();
    assert(lymar_aot_live_allocations() == 0);
    std::cout << "AOT regions, typed edges, recursion, cycles, finalizers and resize passed\n";
}
