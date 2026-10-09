#include "backend/native/abi.hh"
#include "backend/native/direct_operations.hh"
#include "backend/vm/register.hh"
#include <cassert>
#include <iostream>
using namespace LM;
using namespace Backend::Native;
template<class F> void rejects(F f) {
    bool rejected = false;
    try { f(); } catch (const std::runtime_error&) { rejected = true; }
    assert(rejected);
}
int main() {
    Backend::VM::Register::RegisterVM vm;
    const auto& api = host_api();
    auto* ops = reinterpret_cast<const DirectOperations*>(
        api.helper(&vm, static_cast<uint32_t>(Helper::DirectOperations), 1, 0, 0, nullptr, nullptr, 0));
    assert(ops && ops->version == 1 && ops->size == sizeof(DirectOperations));
    rejects([&] { api.helper(&vm, static_cast<uint32_t>(Helper::DirectOperations), 2, 0, 0, nullptr, nullptr, 0); });
    auto call = [&](Helper operation, LmValue a=VAL_NIL, LmValue b=VAL_NIL, const char* name=nullptr) {
        return api.helper(&vm, static_cast<uint32_t>(operation), a, b, VAL_NIL, name, nullptr, 0);
    };
    vm.native_region(LIR::LIR_Op::RegionEnter, 1);
    auto parent = call(Helper::ListNew);
    auto frame = call(Helper::FrameNew, BOX_INT(1), VAL_NIL, "Probe");
    ops->frame_set(&vm, frame, 0, BOX_INT(17), true);
    assert(ops->frame_get(&vm, frame, 0, true) == BOX_INT(17));
    rejects([&] { ops->frame_get(&vm, frame, 1, false); });
    rejects([&] { ops->frame_set(&vm, VAL_NIL, 0, BOX_INT(2), false); });
    vm.native_region(LIR::LIR_Op::RegionEnter, 2);
    auto child = call(Helper::ListNew);
    ops->list_append(&vm, child, BOX_INT(7));
    ops->list_append(&vm, parent, child);
    vm.native_region(LIR::LIR_Op::RegionExit, 2);
    assert(ops->sequence_get(ops->sequence_get(parent, 0), 0) == BOX_INT(7));
    assert(ops->sequence_get(parent, -1) == VAL_NIL);
    assert(ops->sequence_get(parent, 100) == VAL_NIL);
    assert(ops->sequence_get(BOX_INT(9), 0) == VAL_NIL);
    assert(ops->list_length(parent) == BOX_INT(1));
    assert(ops->dict_get(VAL_NIL, BOX_INT(0)) == VAL_NIL);
    assert(ops->dict_has(VAL_NIL, BOX_INT(0)) == VAL_FALSE);
    vm.native_region(LIR::LIR_Op::RegionExit, 1);
    assert(vm.live_allocation_count() == 0);
    rejects([&] { ops->frame_get(&vm, frame, 0, false); });
    std::cout << "Direct operation bounds, frame validation, atomic access and promotion passed\n";
}
