#pragma once
// Shared declarations for the AOT graphics resource. The implementation
// (SoftwareGraphicsResource instantiation and its sokol/truetype/d3d11
// backends) lives in aot_graphics.cpp so console-only programs never pull
// the graphics objects out of the runtime archive. The value-access methods
// declared here are defined in aot_runtime.cpp, which owns the heap helpers
// they need; the linker resolves them across the archive boundary.
#include <cstdint>
#include <vector>
#include "../backend/vm/resource_types.hh"
#include "aot_value_kind.hh"
#include "aot_ffi_values.hh"

struct GraphicsValue { uint64_t word, kind; };
struct GraphicsBase {
    virtual ~GraphicsBase() = default;
    virtual LM::Backend::VM::ResourceType getType() const = 0;
    virtual GraphicsValue call(LM::Backend::VM::ResourceOperation, const std::vector<GraphicsValue>&, void*) = 0;
};
struct NativeGraphicsAccess {
    using Base = GraphicsBase;
    using Value = GraphicsValue;
    using List = uint64_t;
    static constexpr uint64_t object_kind = static_cast<uint64_t>(LM::Memory::AOTValueKind::Object);
    static constexpr uint64_t boolean_kind = static_cast<uint64_t>(LM::Memory::AOTValueKind::Boolean);
    static Value boolean(bool value) { return {value ? uint64_t(1) : uint64_t(0), boolean_kind}; }
    static Value nil() { return {2, object_kind}; }
    static void* list(Value value);
    static int64_t integer(Value value) { return static_cast<int64_t>(lymar_aot_to_integer(value.word)); }
    static double floating(Value value) { return lymar_aot_to_float(value.word); }
    static const char* string(Value value);
    static size_t length(List* value) { return lymar_aot_ffi_list_size(reinterpret_cast<uint64_t>(value)); }
    static Value item(List* value, size_t index) {
        auto pointer = reinterpret_cast<uint64_t>(value);
        auto item_word = lymar_aot_ffi_list_item(pointer, index);
        return {item_word, lymar_aot_word_kind(item_word)};
    }
    static List* new_list();
    static void append(List*, Value);
    static Value pointer(List* value) { return {reinterpret_cast<uint64_t>(value), object_kind}; }
    static Value number(int64_t value) { return {static_cast<uint64_t>(value), 0}; }
    static Value make_integer(int64_t value) { return number(value); }
    static Value real(double value) { return {lymar_aot_box_float(value), object_kind}; }
};
// Implemented in aot_graphics.cpp; returns a heap SoftwareGraphicsResource.
// aot_runtime.cpp references it through #pragma weak so console-only builds
// leave it unresolved (NULL) instead of pulling aot_graphics.o — and with it
// sokol/truetype/d3d11 — into every executable. GUI builds force extraction
// with -Wl,-u,aot_gfx_create (driver) or BackendBuilder::addUndefinedSymbol
// (internal linker).
extern "C" GraphicsBase* aot_gfx_create();
