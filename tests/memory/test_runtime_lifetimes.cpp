#include "backend/vm/register.hh"
#include "backend/vm/vm_dict.hh"
#include "backend/vm/vm_list.hh"
#include "backend/vm/vm_tuple.hh"
#include "backend/native/abi.hh"
#include "runtime/lymarrt/lymarrt.h"
#include "lir/functions.hh"
#include <cassert>
#include <cstddef>
#include <iostream>

using LM::Backend::VM::Register::RegisterVM;
using namespace LM::LIR;
static_assert(sizeof(ObjHeader) == 8);
static_assert(sizeof(LmList) == 32);
static_assert(offsetof(LmList, data) == 8 && offsetof(LmList, size) == 16 && offsetof(LmList, capacity) == 24);
static_assert(sizeof(LmTuple) == 32);

int main() {
    // Constant operands are reusable across reset and independent VMs.
    LIR_Function arithmetic("allocation_balance", 0);
    arithmetic.instructions.emplace_back(LIR_Op::RegionEnter, LM::LIR::Type::Void, 0, 0, 0, 7);
    arithmetic.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::F64, 0, make_float(0));
    arithmetic.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::F64, 1, make_float(.5));
    for (int i = 0; i < 1000; ++i)
        arithmetic.instructions.emplace_back(LIR_Op::Add, LM::LIR::Type::F64, 0, 0, 1);
    arithmetic.instructions.emplace_back(LIR_Op::RegionExit, LM::LIR::Type::Void, 0, 0, 0, 7);
    for (int i = 0; i < 3; ++i) {
        RegisterVM vm;
        vm.execute(arithmetic);
        assert(vm.live_allocation_count() == 2);
        vm.reset();
        assert(vm.live_allocation_count() == 0);
        vm.execute(arithmetic);
        assert(vm.live_allocation_count() == 2);
    }
    {
        RegisterVM vm;
        vm.native_region(LIR_Op::RegionEnter, 1);
        auto outer = BOX_PTR(lm_list_new());
        vm.register_native_allocation(outer);
        // Same lexical identifier can be active in recursive invocations.
        auto depth = vm.begin_native_call();
        vm.native_region(LIR_Op::RegionEnter, 1);
        auto inner = BOX_PTR(lm_list_new());
        vm.register_native_allocation(inner);
        lm_list_append(reinterpret_cast<LmList*>(UNBOX_PTR(inner)), outer);
        vm.transfer_native_ownership(outer, inner); // Must not shorten outer lifetime.
        vm.native_region(LIR_Op::RegionExit, 1);
        assert(vm.live_allocation_count() == 1);
        assert(lm_list_len(reinterpret_cast<LmList*>(UNBOX_PTR(outer))) == 0);
        vm.end_native_call(depth, VAL_NIL);
        vm.native_region(LIR_Op::RegionExit, 1);
        assert(vm.live_allocation_count() == 0);
    }
    {
        RegisterVM vm;
        vm.native_region(LIR_Op::RegionEnter, 1);
        auto depth = vm.begin_native_call();
        vm.native_region(LIR_Op::RegionEnter, 2);
        auto graph = BOX_PTR(lm_list_new());
        auto child = make_float(4.5);
        lm_list_append(reinterpret_cast<LmList*>(UNBOX_PTR(graph)), child);
        lm_list_append(reinterpret_cast<LmList*>(UNBOX_PTR(graph)), graph); // Cycle.
        vm.register_native_allocation(graph);
        vm.native_region(LIR_Op::RegionMove, 0, graph);
        vm.native_region(LIR_Op::RegionExit, 2);
        vm.end_native_call(depth, graph);
        assert(vm.live_allocation_count() == 2);
        assert(as_float(lm_list_get(reinterpret_cast<LmList*>(UNBOX_PTR(graph)), 0)) == 4.5);
        vm.native_region(LIR_Op::RegionExit, 1);
        assert(vm.live_allocation_count() == 0);
    }
    {
        RegisterVM vm;
        vm.native_region(LIR_Op::RegionEnter, 1);
        vm.set_global("persistent", BOX_PTR(lm_list_new()));
        vm.native_region(LIR_Op::RegionExit, 1);
        assert(vm.live_allocation_count() == 1);
        vm.reset();
        assert(vm.get_global("persistent") == VAL_NIL);
        assert(vm.live_allocation_count() == 0);
    }
    {
        LIR_Function raw("raw_lifetime", 0);
        raw.instructions.emplace_back(LIR_Op::RegionEnter, LM::LIR::Type::Void, 0, 0, 0, 10);
        raw.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::I64, 0, make_i64(1024));
        raw.instructions.emplace_back(LIR_Op::MemoryAlloc, LM::LIR::Type::Ptr, 1, 0, 0);
        raw.instructions.emplace_back(LIR_Op::RegionExit, LM::LIR::Type::Void, 0, 0, 0, 10);
        RegisterVM vm;
        vm.execute(raw);
        assert(vm.live_raw_allocation_count() == 0);
        assert(vm.live_allocation_count() == 0);
        raw.instructions.insert(raw.instructions.end() - 1, LIR_Inst(LIR_Op::RegionMove, LM::LIR::Type::Void, 0, 1, 0, 0));
        vm.execute(raw);
        assert(vm.live_raw_allocation_count() == 1);
        vm.reset();
        assert(vm.live_raw_allocation_count() == 0);
        assert(vm.live_allocation_count() == 0);
    }
    {
        LIRFunctionManager::getInstance().createFunction("unused_callback", {}, LM::LIR::Type::Void, nullptr);
        LIR_Function callback("callback_lifetime", 0);
        callback.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::Ptr, 0, BOX_PTR(lm_str_from_bytes("unused_callback", 15)));
        callback.instructions.emplace_back(LIR_Op::ListCreate, LM::LIR::Type::Ptr, 1, 0, 0);
        callback.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::I64, 2, make_i64(0));
        LIR_Inst create(LIR_Op::CallbackCreate, LM::LIR::Type::I64, 3, 0, 0);
        create.call_args = {0, 1, 2};
        callback.instructions.push_back(create);
        LIR_Inst store(LIR_Op::StoreGlobal, LM::LIR::Type::Void, UINT32_MAX, 3, 0);
        store.func_name = "callback";
        callback.instructions.push_back(store);
        RegisterVM vm;
        vm.execute(callback);
        assert(vm.live_callback_count() == 1);
        auto id = as_i64(vm.get_global("callback"));
        assert(lymarrt_callback_get_ptr(id) != nullptr);
        vm.reset();
        assert(vm.live_callback_count() == 0);
        assert(lymarrt_callback_get_ptr(id) == nullptr);
    }
    {
        LmDict* dict = lm_dict_new(lm_hash_int, lm_cmp_int);
        for (int i = 0; i < 16384; ++i) lm_dict_set(dict, make_i64(i), make_i64(i));
        assert(dict->bucket_count >= 32768);
        int expected = 0;
        for (auto* entry = dict->head; entry; entry = entry->order_next) {
            assert(as_i64(entry->key) == expected++);
            assert(as_i64(lm_dict_get(dict, entry->key)) == as_i64(entry->key));
        }
        lm_dict_set(dict, make_i64(42), VAL_NIL);
        assert(lm_dict_contains(dict, make_i64(42)));
        assert(!lm_dict_contains(dict, make_i64(-1)));
        lm_dict_free(dict);
    }
    std::cout << "runtime lifetime, reset, cycle, global, and dictionary checks passed\n";
}
