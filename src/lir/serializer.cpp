#include "serializer.hh"
#include <cstring>

namespace LM {
namespace LIR {

// Simple binary serialization for demonstration
// In a full implementation, this would handle complex values and string tables

std::vector<uint8_t> Serializer::serialize(const LIR_Function& func) {
    std::vector<uint8_t> buffer;

    // Function Name
    uint32_t name_len = func.name.length();
    buffer.insert(buffer.end(), reinterpret_cast<uint8_t*>(&name_len), reinterpret_cast<uint8_t*>(&name_len) + 4);
    buffer.insert(buffer.end(), func.name.begin(), func.name.end());

    // Metadata
    buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&func.param_count), reinterpret_cast<const uint8_t*>(&func.param_count) + 4);
    buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&func.register_count), reinterpret_cast<const uint8_t*>(&func.register_count) + 4);

    // Instructions
    uint32_t inst_count = func.instructions.size();
    buffer.insert(buffer.end(), reinterpret_cast<uint8_t*>(&inst_count), reinterpret_cast<uint8_t*>(&inst_count) + 4);

    for (const auto& inst : func.instructions) {
        // Opcode
        buffer.push_back(static_cast<uint8_t>(inst.op));
        // Dst, A, B, Imm
        buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&inst.dst), reinterpret_cast<const uint8_t*>(&inst.dst) + 4);
        buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&inst.a), reinterpret_cast<const uint8_t*>(&inst.a) + 4);
        buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&inst.b), reinterpret_cast<const uint8_t*>(&inst.b) + 4);
        buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&inst.imm), reinterpret_cast<const uint8_t*>(&inst.imm) + 4);
    }

    return buffer;
}

LIR_Function Serializer::deserialize(const std::vector<uint8_t>& buffer) {
    size_t offset = 0;

    // Name
    uint32_t name_len;
    std::memcpy(&name_len, &buffer[offset], 4); offset += 4;
    std::string name(reinterpret_cast<const char*>(&buffer[offset]), name_len);
    offset += name_len;

    // Metadata
    uint32_t param_count;
    std::memcpy(&param_count, &buffer[offset], 4); offset += 4;
    uint32_t register_count;
    std::memcpy(&register_count, &buffer[offset], 4); offset += 4;

    LIR_Function func(name, param_count);
    func.register_count = register_count;

    // Instructions
    uint32_t inst_count;
    std::memcpy(&inst_count, &buffer[offset], 4); offset += 4;

    for (uint32_t i = 0; i < inst_count; ++i) {
        LIR_Op op = static_cast<LIR_Op>(buffer[offset++]);
        Reg dst, a, b;
        Imm imm;
        std::memcpy(&dst, &buffer[offset], 4); offset += 4;
        std::memcpy(&a, &buffer[offset], 4); offset += 4;
        std::memcpy(&b, &buffer[offset], 4); offset += 4;
        std::memcpy(&imm, &buffer[offset], 4); offset += 4;

        func.instructions.emplace_back(op, dst, a, b, imm);
    }

    return func;
}

} // namespace LIR
} // namespace LM
