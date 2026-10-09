#include "backend/vm/register.hh"
#include "backend/vm/reference_ops.hh"
#include "backend/vm/vm_list.hh"
#include "backend/native/abi.hh"
#include "backend/native/emitter.hh"
#include "backend/fyra/fyra.hh"
#include "lir/serializer.hh"
#include "lir/functions.hh"
#include "lir/verifier.hh"
#include "memory/lir_analysis.hh"
#include <cassert>
#include <filesystem>
#include <iostream>
#if defined(__linux__) && defined(__x86_64__)
#include <dlfcn.h>
#endif
using namespace LM::LIR;
using Machine = LM::Backend::VM::Register::RegisterVM;
LIR_Function probe() {
    LIR_Function f("memory_probe.checked", 0);
    f.register_count = 7;
    f.instructions.emplace_back(LIR_Op::ListCreate, LM::LIR::Type::Ptr, 0, UINT32_MAX, UINT32_MAX);
    f.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::I64, 1, make_i64(41));
    f.instructions.emplace_back(LIR_Op::ListAppend, LM::LIR::Type::Void, UINT32_MAX, 0, 1);
    f.instructions.emplace_back(LIR_Op::RefCreate, LM::LIR::Type::U64, 2, 0, UINT32_MAX, 0, LM::LIR::Type::Ptr);
    f.instructions.emplace_back(LIR_Op::RefMove, LM::LIR::Type::U64, 6, 2, UINT32_MAX, 0, LM::LIR::Type::U64);
    f.instructions.emplace_back(LIR_Op::RefResolve, LM::LIR::Type::Ptr, 3, 6, UINT32_MAX, 0, LM::LIR::Type::U64);
    f.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::I64, 4, make_i64(0));
    f.instructions.emplace_back(LIR_Op::ListIndex, LM::LIR::Type::I64, 5, 3, 4);
    f.instructions.emplace_back(LIR_Op::RefRelease, LM::LIR::Type::Void, UINT32_MAX, 6, UINT32_MAX, 0, LM::LIR::Type::U64);
    LIR_Inst store(LIR_Op::StoreGlobal, LM::LIR::Type::Void, UINT32_MAX, 5, UINT32_MAX);
    store.func_name = "reference_result";
    f.instructions.push_back(store);
    f.instructions.emplace_back(LIR_Op::CallBuiltin, std::string("print"), std::vector<Reg>{5}, std::vector<LM::LIR::Type>{LM::LIR::Type::I64});
    f.instructions.emplace_back(LIR_Op::Return, LM::LIR::Type::I64, UINT32_MAX, 5, UINT32_MAX);
    return f;
}
int main(int argc, char** argv) {
    assert(argc == 2);
    FunctionUtils::initializeFunctions();
    std::filesystem::path directory(argv[1]);
    std::filesystem::create_directories(directory);
    auto f = Serializer::deserialize(Serializer::serialize(probe()));
    std::vector<std::string> errors;
    assert(Verifier::verify(f, errors));
    Machine vm;
    vm.execute(f);
    assert(as_i64(vm.get_global("reference_result")) == 41);
    vm.reset();
    using ReferenceOps = LM::Backend::VM::Register::ReferenceOperations;
    auto nil_token = ReferenceOps::create(vm, VAL_NIL, LM::Memory::ReferenceNullable);
    assert(nil_token == 0);
    assert(IS_NIL(ReferenceOps::resolve(vm, nil_token, LM::Memory::ReferenceNullable)));
    assert(ReferenceOps::move(vm, nil_token, LM::Memory::ReferenceMoveNullable) == 0);
    ReferenceOps::release(vm, nil_token, LM::Memory::ReferenceNullable);
    for (int operation=0; operation<5; ++operation) {
        bool failed = false;
        try {
            if (operation==0) (void)ReferenceOps::create(vm, VAL_NIL, 0);
            if (operation==1) (void)ReferenceOps::resolve(vm, nil_token, 0);
            if (operation==2) (void)ReferenceOps::move(vm, nil_token, 0);
            if (operation==3) ReferenceOps::release(vm, nil_token, 0);
            if (operation==4) (void)ReferenceOps::create(vm, make_i64(0), LM::Memory::ReferenceNullable);
        } catch (const std::exception&) { failed = true; }
        assert(failed);
    }
    // Hosted native field access shares VM validation, including nil, erased
    // wrong types, bounds, and use after reset. No ABI table extension is needed.
    auto& api = LM::Backend::Native::host_api();
    using NativeHelper = LM::Backend::Native::Helper;
    auto native_frame = api.helper(&vm, static_cast<uint32_t>(NativeHelper::FrameNew), make_i64(1), VAL_NIL, VAL_NIL, "Checked", nullptr, 0);
    api.helper(&vm, static_cast<uint32_t>(NativeHelper::FrameSet), native_frame, make_i64(0), make_i64(7), "", nullptr, 0);
    assert(as_i64(api.helper(&vm, static_cast<uint32_t>(NativeHelper::FrameGet), native_frame, make_i64(0), VAL_NIL, "", nullptr, 0)) == 7);
    auto wrong_type = BOX_PTR(lm_list_new()); vm.register_native_allocation(wrong_type);
    for (auto receiver : {VAL_NIL, wrong_type}) for (auto operation : {NativeHelper::FrameGet, NativeHelper::FrameSet}) {
        bool failed = false;
        try { api.helper(&vm, static_cast<uint32_t>(operation), receiver, make_i64(0), make_i64(1), "", nullptr, 0); }
        catch (const std::exception&) { failed = true; }
        assert(failed);
    }
    for (auto index : {-1, 1}) {
        bool failed = false;
        try { api.helper(&vm, static_cast<uint32_t>(NativeHelper::FrameGet), native_frame, make_i64(index), VAL_NIL, "", nullptr, 0); }
        catch (const std::exception&) { failed = true; }
        assert(failed);
    }
    vm.reset();
    bool expired_frame = false;
    try { api.helper(&vm, static_cast<uint32_t>(NativeHelper::FrameGet), native_frame, make_i64(0), VAL_NIL, "", nullptr, 0); }
    catch (const std::exception&) { expired_frame = true; }
    assert(expired_frame);
    // A token into a region becomes invalid before it can dereference freed data.
    vm.native_region(LIR_Op::RegionEnter, 1);
    auto object = BOX_PTR(lm_list_new());
    vm.register_native_allocation(object);
    auto token = vm.borrow_memory(object, false);
    vm.native_region(LIR_Op::RegionExit, 1);
    bool rejected = false;
    try { vm.resolve_memory(token, false); } catch (const std::exception&) { rejected = true; }
    assert(rejected);
    rejected = false;
    try { vm.release_memory_borrow(token); } catch (const std::exception&) { rejected = true; }
    assert(rejected);
#if defined(__linux__) && defined(__x86_64__)
    std::string error;
    auto shared = (directory / "checked.so").string();
    assert(LM::Backend::Native::emit_shared_module(f, "memory_probe", shared, 2, error));
    auto* handle = dlopen(shared.c_str(), RTLD_NOW);
    if (!handle) throw std::runtime_error(dlerror());
    auto version = reinterpret_cast<uint32_t(*)()>(dlsym(handle, "lymar_module_abi_version"));
    assert(version && version() == LM::Backend::Native::ABI_VERSION);
    auto entry = reinterpret_cast<LM::Backend::Native::Entry>(dlsym(handle, "memory_probe.checked"));
    assert(entry);
    assert(as_i64(entry(&LM::Backend::Native::host_api(), &vm, nullptr, 0)) == 41);
    auto old_api = LM::Backend::Native::host_api(); old_api.version = 2;
    rejected = false;
    try { entry(&old_api, &vm, nullptr, 0); } catch (const std::exception&) { rejected = true; }
    assert(rejected);
    vm.reset();
    dlclose(handle);
    f.name = "main";
    // Globals are separately covered; keep executable probe focused on refs.
    f.instructions.erase(f.instructions.end() - 3);
    for (int level = 0; level < 3; ++level) {
        LM::Backend::Fyra::FyraCompiler compiler;
        auto output = (directory / ("checked-o" + std::to_string(level))).string();
        auto result = compiler.compile_aot(f, output, LM::Backend::Fyra::Platform::Linux,
            LM::Backend::Fyra::Architecture::X86_64, static_cast<LM::Backend::Fyra::OptimizationLevel>(level));
        if (!result.success) throw std::runtime_error(result.error_message);
    }
#endif
    LIR_Function closed("closed", 0);
    closed.register_count = 3;
    closed.instructions.emplace_back(LIR_Op::ListCreate, LM::LIR::Type::Ptr, 0, UINT32_MAX, UINT32_MAX);
    closed.instructions.emplace_back(LIR_Op::RefCreate, LM::LIR::Type::U64, 1, 0, UINT32_MAX);
    closed.instructions.emplace_back(LIR_Op::RefResolve, LM::LIR::Type::Ptr, 2, 1, UINT32_MAX);
    closed.instructions.emplace_back(LIR_Op::RefRelease, LM::LIR::Type::Void, UINT32_MAX, 1, UINT32_MAX);
    auto escaped = closed;
    escaped.instructions.emplace_back(LIR_Op::Return, LM::LIR::Type::U64, UINT32_MAX, 1, UINT32_MAX);
    assert(!LM::Memory::eliminate_proven_local_borrows(escaped));
    assert(LM::Memory::eliminate_proven_local_borrows(closed));
    assert(closed.instructions[2].op == LIR_Op::Mov);
    std::cout << "Reference VM/native/AOT lowering, ABI rejection and local proof passed\n";
}
