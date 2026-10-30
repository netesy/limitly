// binding_generator.hh - Emits a Lymar source module from parsed C function
// declarations (roadmap item 2b). The generated module uses std.ffi's typed
// call helpers (call_i64_0/1/2, call_f64_2, call_void_1) for functions with
// supported signatures and falls back to ffi.foreign_call for complex ones.

#pragma once
#include "header_parser.hh"
#include <string>
#include <vector>

namespace LM::Backend::Native {

// Generate a complete .lm module source string from the parsed C functions.
// module_name: the identifier used for `import <module_name>;`
// lib_path: the string passed to ffi.load() (shared library path or name)
std::string generate_bindings(const std::vector<CFunctionDecl>& functions,
                              const std::string& module_name,
                              const std::string& lib_path);

} // namespace LM::Backend::Native
