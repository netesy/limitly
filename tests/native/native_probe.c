// Roadmap item 2a fixture: a plain C translation unit compiled by the host
// toolchain and linked into the Lymar artifact. No LIR is involved here.
#include <stdint.h>

int32_t lymar_native_probe(int32_t value) {
    return value * 2 + 1;
}
