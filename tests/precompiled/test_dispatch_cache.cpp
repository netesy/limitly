#include "backend/vm/compiled_resolver.hh"
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <new>
#include <thread>
#include <array>

static bool count_allocations = false;
static size_t allocations = 0;
void* operator new(size_t size) {
    if (count_allocations) ++allocations;
    if (void* p = std::malloc(size ? size : 1)) return p;
    throw std::bad_alloc();
}
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, size_t) noexcept { std::free(p); }

// Supply two ordinary ABI-compatible test modules via argv. They export the
// same symbol but return different values, so stale dispatch targets are visible.
int main(int argc, char** argv) {
    assert(argc == 4);
    using namespace LM;
    auto& manager = Frontend::ModuleManager::getInstance();
    auto& registry = LIR::FunctionRegistry::getInstance();
    auto& resolver = CompiledResolver::getInstance();
    auto function = std::make_unique<LIR::LIR_Function>("cache.answer", 0);
    registry.registerFunction("cache.answer", std::move(function));
    LIR::LIR_Inst call;
    call.dst = 0;
    call.call_args = {0};
    const std::vector<LmValue> captures = {BOX_INT(7)};
    std::vector<LmValue> registers(1, VAL_NIL);
    assert(!resolver.dispatch("cache.answer", call, registers, nullptr, captures));
    Frontend::CompiledModuleMeta meta;
    meta.module_name = "cache";
    meta.artifact_kind = "shared";
    meta.exports = {"cache.answer"};
    meta.artifact_path = argv[1];
    auto unrelated = meta;
    unrelated.module_name = "unrelated";
    unrelated.exports = {"cache.other"};
    manager.register_compiled_module(unrelated);
    assert(!resolver.dispatch("cache.answer", call, registers, nullptr, captures));
    assert(!resolver.dispatch("cache.answer", call, registers, nullptr, captures));
    manager.register_compiled_module(meta);
    assert(resolver.dispatch("cache.answer", call, registers, nullptr, captures));
    count_allocations = true;
    for (int i = 0; i < 10; ++i) {
        assert(resolver.dispatch("cache.answer", call, registers, nullptr, captures));
        assert(registers[0] == BOX_INT(11));
    }
    count_allocations = false;
    assert(allocations == 0); // Warm dispatch does not allocate argument buffers.
    manager.clear();
    assert(!resolver.dispatch("cache.answer", call, registers, nullptr, captures));
    meta.artifact_path = argv[2];
    manager.register_compiled_module(meta);
    assert(resolver.dispatch("cache.answer", call, registers, nullptr, captures));
    assert(registers[0] == BOX_INT(22));
    std::array<std::thread, 4> workers;
    for (auto& worker : workers) worker = std::thread([&] {
        auto& local_resolver = CompiledResolver::getInstance();
        std::vector<LmValue> local_registers(1, VAL_NIL);
        for (int i = 0; i < 100; ++i) {
            assert(local_resolver.dispatch("cache.answer", call, local_registers, nullptr, captures));
            assert(local_registers[0] == BOX_INT(22));
        }
    });
    for (auto& worker : workers) worker.join();
    manager.clear();
    meta.artifact_path = argv[3];
    manager.register_compiled_module(meta);
    bool rejected = false;
    try { resolver.dispatch("cache.answer", call, registers, nullptr, captures); }
    catch (const std::runtime_error& e) {
        rejected = std::string(e.what()).find("Unsupported precompiled module ABI") != std::string::npos;
    }
    assert(rejected);
    std::cout << "Dispatch cache invalidation and ABI rejection passed\n";
}
