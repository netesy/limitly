#include "memory/memory.hh"
#include <cassert>
#include <iostream>
#include <limits>
using namespace LM::Memory;
template<class F> void rejects(F f) {
    bool rejected = false;
    try { f(); } catch (const std::exception&) { rejected = true; }
    assert(rejected);
}
struct Probe { int* count; ~Probe() { ++*count; } };
struct alignas(256) Aligned { int value = 7; };
int main() {
    static_assert(same_generation(3, 3));
    static_assert(!same_generation(2, 3));
    static_assert(borrow_outlives_owner(2, 1));
    LifetimeRegistry registry;
    registry.adopt(0x1000);
    auto read = registry.borrow(0x1000, false);
    assert(registry.resolve(read) == 0x1000);
    rejects([&] { registry.borrow(0x1000, true); });
    rejects([&] { registry.resolve(read, true); });
    rejects([&] { registry.consume(0x1000); });
    registry.revoke(0x1000);
    registry.adopt(0x1000);
    rejects([&] { registry.resolve(read); });
    auto write = registry.borrow(0x1000, true);
    registry.end_borrow(read); // stale release must not disturb new allocation
    assert(registry.resolve(write, true) == 0x1000);
    rejects([&] { registry.borrow(0x1000, false); });
    registry.end_borrow(write);
    rejects([&] { registry.end_borrow(write); });
    registry.consume(0x1000);
    auto after_move = registry.borrow(0x1000, false);
    registry.reset();
    registry.adopt(0x1000);
    rejects([&] { registry.resolve(after_move); });
    auto after_reset = registry.borrow(0x1000, false);
    assert(after_reset != after_move);
    LifetimeRegistry other;
    other.adopt(0x1000);
    auto other_token = other.borrow(0x1000, false);
    assert(other_token != after_reset);
    rejects([&] { other.resolve(after_reset); });
    rejects([&] { registry.resolve(other_token); });
    other.end_borrow(other_token);
    registry.end_borrow(after_reset);
    auto outer = registry.borrow(0x1000, false, 10);
    auto inner = registry.borrow(0x1000, false, 11);
    registry.end_region(11);
    rejects([&] { registry.resolve(inner); });
    assert(registry.resolve(outer) == 0x1000);
    registry.end_region(10);
    rejects([&] { registry.resolve(outer); });
    auto mutable_again = registry.borrow(0x1000, true, 12);
    registry.end_region(12);
    rejects([&] { registry.resolve(mutable_again); });

    auto moving = registry.borrow(0x1000, true, 14);
    auto moved = registry.move_reference(moving, 13);
    rejects([&] { registry.resolve(moving); });
    registry.end_region(14);
    assert(registry.resolve(moved, true) == 0x1000);
    registry.end_region(13);
    rejects([&] { registry.resolve(moved); });

    MemoryManager<> manager;
    MemoryManager<>::Ref<int> expired;
    int count = 0;
    {
        MemoryManager<>::Region region(manager);
        auto* first = region.create<int>(7);
        expired = MemoryManager<>::Ref<int>(region, first);
        region.deallocate<int>(first);
        auto* second = region.create<int>(9);
        assert(!expired.isValid());
        rejects([&] { expired.get(); });
        region.enterScope();
        region.create<Probe>(&count);
        region.exitScope();
        assert(count == 1);
        auto* aligned = region.create<Aligned>();
        assert(reinterpret_cast<uintptr_t>(aligned) % alignof(Aligned) == 0);
        assert(aligned->value == 7);
        region.deallocate<Aligned>(aligned);
        region.deallocate<int>(second);
    }
    assert(!expired.isValid());
    rejects([&] { expired.get(); });
    auto* bytes = static_cast<unsigned char*>(MemoryManager<>::Unsafe::allocate(8));
    for (int i = 0; i < 8; ++i) bytes[i] = i;
    bytes = static_cast<unsigned char*>(MemoryManager<>::Unsafe::resize(bytes, 64));
    for (int i = 0; i < 8; ++i) assert(bytes[i] == i);
    MemoryManager<>::Unsafe::deallocate(bytes);
    rejects([&] { MemoryManager<>::Unsafe::allocateZeroed(SIZE_MAX, 2); });
    std::cout << "Memory identities, borrows, reuse, reset, drops and alignment passed\n";
}
