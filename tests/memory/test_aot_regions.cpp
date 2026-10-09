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
uint64_t lymar_aot_ref_create(uint64_t, uint64_t);
uint64_t lymar_aot_ref_create_checked(uint64_t, uint64_t, uint64_t);
uint64_t lymar_aot_nil();
uint64_t lymar_aot_is_nil(uint64_t, uint64_t);
uint64_t lymar_aot_is_object(uint64_t, uint64_t);
uint64_t lymar_aot_box_float(double);
uint64_t lymar_aot_value_equal(uint64_t, uint64_t, uint64_t, uint64_t);
double lymar_aot_to_float(uint64_t, uint64_t);
uint64_t lymar_aot_arg_kind(uint64_t, uint64_t);
void lymar_aot_arg_set(uint64_t, uint64_t);
uint64_t lymar_aot_resource_call(uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t lymar_aot_ref_resolve(uint64_t, uint64_t);
void lymar_aot_ref_release(uint64_t);
void lymar_aot_ref_release_nullable(uint64_t);
uint64_t lymar_aot_ref_move(uint64_t, uint64_t, uint64_t);
}
static int finalized = 0;
static void finalizer(uint64_t) { ++finalized; }
static void store(uint64_t address, uint64_t value, bool pointer) {
    std::memcpy(reinterpret_cast<void*>(address), &value, 8);
    lymar_aot_edge(address, value, pointer);
}
int main() {
    assert(lymar_aot_ref_create(0, 2) == 0);
    assert(lymar_aot_ref_create_checked(lymar_aot_nil(), 2, 1) == 0);
    assert(lymar_aot_is_nil(2, 1));
    assert(!lymar_aot_is_nil(2, 0));
    assert(!lymar_aot_is_object(1000000, 0));
    for (uint64_t scalar : {uint64_t(0), uint64_t(2)}) {
        bool rejected = false;
        try { (void)lymar_aot_ref_create_checked(scalar, 2, 0); }
        catch (const std::runtime_error&) { rejected = true; }
        assert(rejected);
    }
    assert(lymar_aot_ref_resolve(0, 2) == 2);
    assert(lymar_aot_ref_move(0, uint64_t{1} << 31, 0) == 0);
    lymar_aot_ref_release_nullable(0);
    for (int operation=0; operation<4; ++operation) {
        bool failed = false;
        try {
            if (operation==0) (void)lymar_aot_ref_create(0, 0);
            if (operation==1) (void)lymar_aot_ref_resolve(0, 0);
            if (operation==2) (void)lymar_aot_ref_move(0, 0, 0);
            if (operation==3) lymar_aot_ref_release(0);
        } catch (const std::exception&) { failed = true; }
        assert(failed);
    }
    auto before_reset = lymar_aot_ref_create(lymar_aot_alloc(16), 0);
    lymar_aot_reset();
    bool expired = false;
    try { lymar_aot_ref_resolve(before_reset, 0); } catch (const std::exception&) { expired = true; }
    assert(expired);
    auto after_reset = lymar_aot_ref_create(lymar_aot_alloc(16), 1);
    assert(after_reset != before_reset);
    lymar_aot_ref_release(after_reset);
    lymar_aot_reset();
    lymar_aot_region_enter(17);
    auto owner = lymar_aot_alloc(16);
    auto scoped = lymar_aot_ref_create(owner, 0);
    bool rejected_move = false;
    try { lymar_aot_ref_move(scoped, 0, 0); } catch (const std::exception&) { rejected_move = true; }
    assert(rejected_move);
    lymar_aot_region_move(owner, 0, 0, true);
    auto promoted = lymar_aot_ref_move(scoped, 0, 0);
    auto expires = lymar_aot_ref_create(owner, 0);
    lymar_aot_region_exit(17);
    assert(lymar_aot_ref_resolve(promoted, 0) == owner);
    expired = false;
    try { lymar_aot_ref_resolve(scoped, 0); } catch (const std::exception&) { expired = true; }
    assert(expired);
    expired = false;
    try { lymar_aot_ref_resolve(expires, 0); } catch (const std::exception&) { expired = true; }
    assert(expired);
    lymar_aot_ref_release(promoted);
    lymar_aot_reset();
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

    // Boolean tags must survive overlapping copies/resizing without being
    // mistaken for ownership edges, and must be revoked on allocation release.
    caller = lymar_aot_call_enter();
    lymar_aot_region_enter(42);
    auto kinds = lymar_aot_alloc(24);
    uint64_t yes = 1;
    std::memcpy(reinterpret_cast<void*>(kinds), &yes, 8);
    lymar_aot_edge(kinds, yes, 2);
    lymar_aot_copy(kinds + 8, kinds, 8);
    assert(lymar_aot_slot_pointer(kinds + 8) == 2);
    kinds = lymar_aot_resize(kinds, 32);
    assert(lymar_aot_slot_pointer(kinds) == 2 && lymar_aot_slot_pointer(kinds + 8) == 2);
    auto number = lymar_aot_box_float(2.5);
    assert(lymar_aot_to_float(number, 1) == 2.5);
    auto float_reference = lymar_aot_ref_create_checked(number, 2, 1);
    assert(lymar_aot_ref_resolve(float_reference, 2) == number);
    lymar_aot_ref_release_nullable(float_reference);
    assert(lymar_aot_value_equal(number, lymar_aot_box_float(2.5), 1, 1));
    assert(!lymar_aot_value_equal(2, 2, 0, 1));
    assert(!lymar_aot_value_equal(1, 1, 2, 0));
    assert(lymar_aot_value_equal(1, 1, 2, 2));
    assert(!lymar_aot_is_nil(2, 2));
    assert(lymar_aot_resource_call(0, 10, 0, 0) == 1);
    assert(lymar_aot_return_pointer() == 2);
    assert(lymar_aot_resource_call(UINT64_MAX, 2, 0, 0) == 2);
    assert(lymar_aot_return_pointer() == 1);
    bool boolean_rejected = false;
    try { (void)lymar_aot_ref_create_checked(1, 2, 2); }
    catch (const std::runtime_error&) { boolean_rejected = true; }
    assert(boolean_rejected);
    lymar_aot_arg_set(0, 0);
    lymar_aot_call_enter();
    assert(lymar_aot_arg_kind(0, 1) == 0); // Integer overrides Ptr formal fallback.
    assert(lymar_aot_arg_kind(1, 1) == 1); // Foreign entry with absent sidecar.
    lymar_aot_call_leave(0);
    lymar_aot_region_exit(42);
    assert(lymar_aot_slot_pointer(kinds) == 0);
    assert(lymar_aot_live_allocations() == 0);
    lymar_aot_call_leave(0);

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
