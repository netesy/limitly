#include "serializer.hh"
#include "../runtime/runtime.h"
#include "../runtime/runtime_value.h"
#include <cstring>
#include <cstdint>
#include <stdexcept>

namespace LM {
namespace LIR {

// ============================================================================
// LIR tagged binary serialization format — version 1 ("LIR1")
//
// Header:
//   magic         4 bytes   "LIR1"
//   version       1 byte    = 1
//
// Function:
//   name_len      4 bytes   uint32_t LE
//   name          name_len bytes
//   param_count   4 bytes   uint32_t
//   reg_count     4 bytes   uint32_t
//   inst_count    4 bytes   uint32_t
//
// Per instruction (in order):
//   op            4 bytes   uint32_t (LIR_Op enum value)
//   result_type   4 bytes   uint32_t (Type enum value)
//   type_a        4 bytes   uint32_t
//   type_b        4 bytes   uint32_t
//   dst           4 bytes   uint32_t
//   a             4 bytes   uint32_t
//   b             4 bytes   uint32_t
//   imm           8 bytes   uint64_t (Imm is uint32_t but we reserve 8 for
//                                  forward-compat / future expansion)
//   const_tag     1 byte    ConstTag (see below)
//   [const payload — see ConstTag table]
//   has_func_name 1 byte    0/1
//   [if 1: 4 bytes len + bytes]
//   has_type_name 1 byte    0/1
//   [if 1: 4 bytes len + bytes]
//   args_count    4 bytes   uint32_t
//   args          count * 4 bytes (uint32_t Reg each)
//   arg_types_cnt 4 bytes   uint32_t
//   arg_types     count * 4 bytes (uint32_t Type each — fits in 1 byte,
//                                  padded to 4 for alignment)
//   has_loc       1 byte    0/1
//   [if 1: 4 bytes file_len + file bytes + 4 bytes line + 4 bytes column]
//   has_comment   1 byte    0/1
//   [if 1: 4 bytes len + bytes]
//
// ConstTag (uint8_t):
//   0   None           — same as Nil (used when const_val == VAL_NIL)
//   1   Nil            — VAL_NIL (no payload)
//   2   True           — VAL_TRUE (no payload)
//   3   False          — VAL_FALSE (no payload)
//   4   Smi            — 8 bytes int64_t  (BOX_INT(v))
//   5   HeapI64        — 8 bytes int64_t  (lm_alloc_i64(v))
//   6   HeapU64        — 8 bytes uint64_t (lm_alloc_u64(v))
//   7   HeapI128       — 16 bytes __int128 (lm_alloc_i128(v))
//   8   HeapU128       — 16 bytes unsigned __int128 (lm_alloc_u128(v))
//   9   HeapFloat      — 8 bytes double   (lm_alloc_float(v))
//  10   BoxedString    — 4 bytes len + len bytes  (lm_box_string(s))
//  11   BoxedInt       — 8 bytes int64_t  (lm_box_int(v))
//  12   BoxedFloat     — 8 bytes double   (lm_box_float(v))
//  13   BoxedBool      — 1 byte           (lm_box_bool(v))
//  14   BoxedNullPtr   — no payload       (lm_box_nullptr())
//  255  Unknown        — no payload (restored as VAL_NIL; loses info)
// ============================================================================

namespace {

constexpr char kMagic[4] = {'L', 'I', 'R', '1'};
constexpr uint8_t kVersion = 1;

enum class ConstTag : uint8_t {
    None         = 0,
    Nil          = 1,
    True         = 2,
    False        = 3,
    Smi          = 4,
    HeapI64      = 5,
    HeapU64      = 6,
    HeapI128     = 7,
    HeapU128     = 8,
    HeapFloat    = 9,
    BoxedString  = 10,
    BoxedInt     = 11,
    BoxedFloat   = 12,
    BoxedBool    = 13,
    BoxedNullPtr = 14,
    Unknown      = 255,
};

// ---- Byte writer (serialize side) ---------------------------------------

struct Writer {
    std::vector<uint8_t> buf;

    void u8(uint8_t v) { buf.push_back(v); }
    void u32(uint32_t v) {
        buf.insert(buf.end(), reinterpret_cast<uint8_t*>(&v),
                   reinterpret_cast<uint8_t*>(&v) + 4);
    }
    void u64(uint64_t v) {
        buf.insert(buf.end(), reinterpret_cast<uint8_t*>(&v),
                   reinterpret_cast<uint8_t*>(&v) + 8);
    }
    void bytes(const void* p, size_t n) {
        const auto* b = reinterpret_cast<const uint8_t*>(p);
        buf.insert(buf.end(), b, b + n);
    }
    void str(const std::string& s) {
        u32(static_cast<uint32_t>(s.size()));
        bytes(s.data(), s.size());
    }
    void flag(bool v) { u8(v ? 1 : 0); }
};

// ---- Byte reader (deserialize side) -------------------------------------

struct Reader {
    const std::vector<uint8_t>& buf;
    size_t pos = 0;

    explicit Reader(const std::vector<uint8_t>& b) : buf(b) {}

    void need(size_t n) const {
        if (pos + n > buf.size()) {
            throw std::runtime_error("LIR deserialize: unexpected end of buffer");
        }
    }
    uint8_t u8() {
        need(1);
        return buf[pos++];
    }
    uint32_t u32() {
        need(4);
        uint32_t v;
        std::memcpy(&v, &buf[pos], 4);
        pos += 4;
        return v;
    }
    uint64_t u64() {
        need(8);
        uint64_t v;
        std::memcpy(&v, &buf[pos], 8);
        pos += 8;
        return v;
    }
    double f64() {
        uint64_t bits = u64();
        double v;
        std::memcpy(&v, &bits, 8);
        return v;
    }
    int64_t i64() { return static_cast<int64_t>(u64()); }
    __int128 i128() {
        need(16);
        __int128 v;
        std::memcpy(&v, &buf[pos], 16);
        pos += 16;
        return v;
    }
    unsigned __int128 u128() {
        need(16);
        unsigned __int128 v;
        std::memcpy(&v, &buf[pos], 16);
        pos += 16;
        return v;
    }
    std::string str() {
        uint32_t n = u32();
        need(n);
        std::string s(reinterpret_cast<const char*>(&buf[pos]), n);
        pos += n;
        return s;
    }
    bool flag() { return u8() != 0; }
};

// Map a Backend::Value (LmValue) to its ConstTag, writing payload to `w`.
void write_const_val(Writer& w, Backend::Value v) {
    if (IS_NIL(v)) {
        w.u8(static_cast<uint8_t>(ConstTag::Nil));
        return;
    }
    if (v == VAL_TRUE) {
        w.u8(static_cast<uint8_t>(ConstTag::True));
        return;
    }
    if (v == VAL_FALSE) {
        w.u8(static_cast<uint8_t>(ConstTag::False));
        return;
    }
    if (IS_INT(v)) {
        w.u8(static_cast<uint8_t>(ConstTag::Smi));
        w.u64(static_cast<uint64_t>(UNBOX_INT(v)));
        return;
    }
    if (IS_PTR(v)) {
        void* raw = UNBOX_PTR(v);
        if (!raw) {
            // Treat null pointer as nil for safety.
            w.u8(static_cast<uint8_t>(ConstTag::Nil));
            return;
        }
        ObjHeader* h = static_cast<ObjHeader*>(raw);
        switch (h->type_id) {
            case TYPE_I64: {
                w.u8(static_cast<uint8_t>(ConstTag::HeapI64));
                int64_t val = reinterpret_cast<ObjI64*>(h)->value;
                w.u64(static_cast<uint64_t>(val));
                return;
            }
            case TYPE_U64: {
                w.u8(static_cast<uint8_t>(ConstTag::HeapU64));
                w.u64(reinterpret_cast<ObjU64*>(h)->value);
                return;
            }
            case TYPE_I128: {
                w.u8(static_cast<uint8_t>(ConstTag::HeapI128));
                __int128 val = reinterpret_cast<ObjI128*>(h)->value;
                w.bytes(&val, 16);
                return;
            }
            case TYPE_U128: {
                w.u8(static_cast<uint8_t>(ConstTag::HeapU128));
                unsigned __int128 val = reinterpret_cast<ObjU128*>(h)->value;
                w.bytes(&val, 16);
                return;
            }
            case TYPE_FLOAT: {
                w.u8(static_cast<uint8_t>(ConstTag::HeapFloat));
                double val = reinterpret_cast<ObjFloat*>(h)->value;
                uint64_t bits;
                std::memcpy(&bits, &val, 8);
                w.u64(bits);
                return;
            }
            case TYPE_BOX: {
                LmBox* box = reinterpret_cast<LmBox*>(h);
                switch (box->type) {
                    case LM_BOX_INT:
                        w.u8(static_cast<uint8_t>(ConstTag::BoxedInt));
                        w.u64(static_cast<uint64_t>(box->value.as_int));
                        return;
                    case LM_BOX_FLOAT: {
                        w.u8(static_cast<uint8_t>(ConstTag::BoxedFloat));
                        double val = box->value.as_float;
                        uint64_t bits;
                        std::memcpy(&bits, &val, 8);
                        w.u64(bits);
                        return;
                    }
                    case LM_BOX_BOOL:
                        w.u8(static_cast<uint8_t>(ConstTag::BoxedBool));
                        w.u8(box->value.as_bool ? 1 : 0);
                        return;
                    case LM_BOX_STRING: {
                        const char* s = static_cast<const char*>(box->value.as_ptr);
                        uint32_t len = s ? static_cast<uint32_t>(std::strlen(s)) : 0;
                        w.u8(static_cast<uint8_t>(ConstTag::BoxedString));
                        w.u32(len);
                        if (len) w.bytes(s, len);
                        return;
                    }
                    case LM_BOX_NULLPTR:
                        w.u8(static_cast<uint8_t>(ConstTag::BoxedNullPtr));
                        return;
                    default:
                        break; // fall through to unknown
                }
            }
            // fall through
        }
    }
    // Unknown representation — drop and round-trip as NIL.
    w.u8(static_cast<uint8_t>(ConstTag::Unknown));
}

// Read a ConstTag + payload from `r` and reconstruct a Backend::Value.
Backend::Value read_const_val(Reader& r) {
    ConstTag tag = static_cast<ConstTag>(r.u8());
    switch (tag) {
        case ConstTag::None:
        case ConstTag::Nil:
            return VAL_NIL;
        case ConstTag::True:
            return VAL_TRUE;
        case ConstTag::False:
            return VAL_FALSE;
        case ConstTag::Smi:
            return BOX_INT(static_cast<int64_t>(r.u64()));
        case ConstTag::HeapI64:
            return lm_alloc_i64(r.i64());
        case ConstTag::HeapU64:
            return lm_alloc_u64(r.u64());
        case ConstTag::HeapI128:
            return lm_alloc_i128(r.i128());
        case ConstTag::HeapU128:
            return lm_alloc_u128(r.u128());
        case ConstTag::HeapFloat:
            return lm_alloc_float(r.f64());
        case ConstTag::BoxedString: {
            uint32_t len = r.u32();
            std::string s;
            s.reserve(len);
            for (uint32_t i = 0; i < len; ++i) s.push_back(static_cast<char>(r.u8()));
            return BOX_PTR(lm_box_string(s.c_str()));
        }
        case ConstTag::BoxedInt:
            return BOX_PTR(lm_box_int(r.i64()));
        case ConstTag::BoxedFloat:
            return BOX_PTR(lm_box_float(r.f64()));
        case ConstTag::BoxedBool:
            return BOX_PTR(lm_box_bool(r.u8()));
        case ConstTag::BoxedNullPtr:
            return BOX_PTR(lm_box_nullptr());
        case ConstTag::Unknown:
        default:
            return VAL_NIL;
    }
}

} // namespace

// ========================================================================
// Public API
// ========================================================================

std::vector<uint8_t> Serializer::serialize(const LIR_Function& func) {
    Writer w;

    // Header
    w.bytes(kMagic, 4);
    w.u8(kVersion);

    // Function metadata
    w.str(func.name);
    w.u32(func.param_count);
    w.u32(func.register_count);
    w.u32(static_cast<uint32_t>(func.instructions.size()));

    for (const auto& inst : func.instructions) {
        // Fixed-width fields
        w.u32(static_cast<uint32_t>(inst.op));
        w.u32(static_cast<uint32_t>(inst.result_type));
        w.u32(static_cast<uint32_t>(inst.type_a));
        w.u32(static_cast<uint32_t>(inst.type_b));
        w.u32(inst.dst);
        w.u32(inst.a);
        w.u32(inst.b);
        w.u64(static_cast<uint64_t>(inst.imm));

        // const_val (tagged)
        write_const_val(w, inst.const_val);

        // func_name (optional)
        w.flag(!inst.func_name.empty());
        if (!inst.func_name.empty()) w.str(inst.func_name);

        // type_name (optional)
        w.flag(!inst.type_name.empty());
        if (!inst.type_name.empty()) w.str(inst.type_name);

        // call_args
        w.u32(static_cast<uint32_t>(inst.call_args.size()));
        for (Reg r : inst.call_args) w.u32(r);

        // call_arg_types
        w.u32(static_cast<uint32_t>(inst.call_arg_types.size()));
        for (Type t : inst.call_arg_types) w.u32(static_cast<uint32_t>(t));

        // loc (optional)
        bool has_loc = !inst.loc.file.empty();
        w.flag(has_loc);
        if (has_loc) {
            w.str(inst.loc.file);
            w.u32(inst.loc.line);
            w.u32(inst.loc.column);
        }

        // comment (optional)
        w.flag(!inst.comment.empty());
        if (!inst.comment.empty()) w.str(inst.comment);
    }

    return w.buf;
}

LIR_Function Serializer::deserialize(const std::vector<uint8_t>& buffer) {
    Reader r(buffer);

    // Header
    r.need(4);
    if (std::memcmp(&buffer[0], kMagic, 4) != 0) {
        throw std::runtime_error("LIR deserialize: bad magic header");
    }
    r.pos += 4;
    uint8_t version = r.u8();
    if (version != kVersion) {
        throw std::runtime_error("LIR deserialize: unsupported version " +
                                 std::to_string(version));
    }

    // Function metadata
    std::string name = r.str();
    uint32_t param_count = r.u32();
    uint32_t register_count = r.u32();
    uint32_t inst_count = r.u32();

    LIR_Function func(name, param_count);
    func.register_count = register_count;
    func.instructions.reserve(inst_count);

    for (uint32_t i = 0; i < inst_count; ++i) {
        LIR_Inst inst;
        // LIR_Inst's default constructor does not value-initialize the POD
        // members of LIR_SourceLoc (line/column). Force zero-init here so
        // that an instruction with no loc on the wire round-trips to a
        // deterministic loc{} rather than uninitialized memory.
        inst.loc = LIR_SourceLoc{"", 0, 0};
        inst.op = static_cast<LIR_Op>(r.u32());
        inst.result_type = static_cast<Type>(r.u32());
        inst.type_a = static_cast<Type>(r.u32());
        inst.type_b = static_cast<Type>(r.u32());
        inst.dst = r.u32();
        inst.a = r.u32();
        inst.b = r.u32();
        inst.imm = static_cast<Imm>(r.u64());

        inst.const_val = read_const_val(r);

        if (r.flag()) inst.func_name = r.str();
        if (r.flag()) inst.type_name = r.str();

        uint32_t args_n = r.u32();
        inst.call_args.reserve(args_n);
        for (uint32_t k = 0; k < args_n; ++k) inst.call_args.push_back(r.u32());

        uint32_t arg_t_n = r.u32();
        inst.call_arg_types.reserve(arg_t_n);
        for (uint32_t k = 0; k < arg_t_n; ++k) {
            inst.call_arg_types.push_back(static_cast<Type>(r.u32()));
        }

        if (r.flag()) {
            inst.loc.file = r.str();
            inst.loc.line = r.u32();
            inst.loc.column = r.u32();
        }

        if (r.flag()) inst.comment = r.str();

        func.instructions.push_back(std::move(inst));
    }

    return func;
}

} // namespace LIR
} // namespace LM
