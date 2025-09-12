#ifndef LEMBED_H
#define LEMBED_H

#include "opcodes.hh"
#include <string>
#include <vector>
#include <unordered_map>

namespace lembed {
    using Bytecode = std::vector<Instruction>;

    // Register an embedded bytecode under a name.
    void registerEmbed(const std::string& name, const Bytecode& bc);

    // Return pointer to embedded bytecode for name or nullptr if not found.
    const Bytecode* getEmbeddedBytecode(const std::string& name);

    // List available embed names
    std::vector<std::string> listEmbeddedNames();

    // Register builtin embeds explicitly (call from main to avoid static-init order issues)
    extern "C" void registerBuiltinEmbeds();
}

#endif // LEMBED_H
