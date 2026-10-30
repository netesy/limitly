// foreign_sources.hh - Native toolchain compilation of foreign .c/.cpp
// sources for link-time integration (roadmap item 2a). The sources are not
// lowered through LIR; cc/clang compiles them to object files that every
// artifact link path then contributes to the produced image.

#pragma once
#include <string>
#include <vector>

namespace LM::Backend::Native {

// Compile each foreign source to a temporary object file placed next to
// `output` and return the object paths. Throws std::runtime_error when the
// toolchain rejects a source. `.c` files use the C driver, everything else
// the C++ driver. Both honor LYMAR_AOT_CXX (C++) and LYMAR_AOT_CC (C)
// overrides, mirroring how the AOT runtime archive is built.
std::vector<std::string> compile_foreign_sources(const std::vector<std::string>& sources,
                                                 const std::vector<std::string>& include_dirs,
                                                 const std::vector<std::string>& extra_cflags,
                                                 const std::string& output,
                                                 const std::string& target,
                                                 const std::string& arch);

// Remove the object files returned by compile_foreign_sources once the link
// that consumes them has finished.
void cleanup_foreign_objects(const std::vector<std::string>& objects);

} // namespace LM::Backend::Native
