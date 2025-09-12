#include "lembed.hh"
#include "opcodes.hh"

// A tiny helper to build an Instruction
static Instruction I(Opcode op, uint32_t line = 0, int64_t iv = 0, float fv = 0.0f, bool bv = false, const std::string& sv = "") {
    Instruction ins;
    ins.opcode = op;
    ins.line = line;
    ins.intValue = iv;
    ins.floatValue = fv;
    ins.boolValue = bv;
    ins.stringValue = sv;
    return ins;
}

namespace {
    void register_hello_embed() {
        lembed::Bytecode bc;
        bc.push_back(I(Opcode::PUSH_STRING, 1, 0, 0.0f, false, "Hello from embed"));
    // PRINT's intValue is the argument count
    bc.push_back(I(Opcode::PRINT, 1, 1));
    bc.push_back(I(Opcode::PUSH_NULL, 1));
    // Do not emit RETURN at top-level; emit HALT to stop execution
    bc.push_back(I(Opcode::HALT, 0));
        lembed::registerEmbed("hello_embed", bc);
    }
}

extern "C" void registerBuiltinEmbeds() {
    register_hello_embed();
}
