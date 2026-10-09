#pragma once
#include <cstdint>

namespace LM::Memory {
// Backend-private sidecar for native words. Public object/FFI layouts are unchanged.
// Floats crossing an erased boundary use tracked TYPE_FLOAT objects, not a new kind.
enum class AOTValueKind : uint64_t { Integer = 0, Object = 1, Boolean = 2 };
}
