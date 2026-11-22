// binding_generator.cpp - Emits a Lymar module wrapping C functions with std.ffi
// typed call helpers. See the header for design details.

#include "binding_generator.hh"
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace LM::Backend::Native {
namespace {

// Qualified name ("<module>.<fn>") -> precise C signature for direct-safe
// c-import wrappers. Read by the LIR generator in AOT mode.
std::unordered_map<std::string, CDirectSignature>& direct_signature_table() {
    static std::unordered_map<std::string, CDirectSignature> table;
    return table;
}

// ─── Type mapping helpers ─────────────────────────────────────────────────────

std::string ffi_type_id(const CType& t);

// ffi.TYPE_* ids for a struct's flat scalar fields, in declaration order.
// Used to build ffi.struct_param([...]) / ffi.struct_alloc([...]) arguments.
std::vector<std::string> struct_elem_type_ids(const CType& t) {
    std::vector<std::string> ids;
    if (t.kind != CType::Struct || !t.def) return ids;
    for (const auto& f : t.def->fields) ids.push_back(ffi_type_id(f.type));
    return ids;
}

// Lymar expression producing the [any] element-type list for a struct type,
// e.g. "ffi.struct_param([ffi.TYPE_F32, ffi.TYPE_F32])" or "[]" when the
// type is not a supported struct.
std::string struct_param_expr(const CType& t, const std::string& ffi_prefix = "ffi.") {
    auto ids = struct_elem_type_ids(t);
    if (ids.empty()) return ffi_prefix + "struct_param([])";
    std::string out = ffi_prefix + "struct_param([";
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i) out += ", ";
        out += ids[i];
    }
    out += "])";
    return out;
}

// A struct type is marshalable when it parsed to a supported flat layout.
bool is_supported_struct(const CType& t) {
    return t.kind == CType::Struct && t.def && t.def->supported && !t.def->fields.empty();
}

// Returns the Lymar type annotation for a CType (e.g., "int", "float", "ffi.pubptr")
std::string lymar_type(const CType& t) {
    switch (t.kind) {
        case CType::Void:     return "nil";
        case CType::Bool:     return "int";
        case CType::Char:     return "int";
        case CType::Short:    return "int";
        case CType::Int:      return "int";
        case CType::Long:     return "int";
        case CType::LongLong: return "int";
        case CType::Float:    return "float";
        case CType::Double:   return "float";
        case CType::Ptr:      return "ffi.pubptr";
        case CType::FixedWidth: return "int";
        case CType::Struct:   return is_supported_struct(t) ? "ffi.pubptr" : "int";
        case CType::Custom:   return "int"; // fallback
    }
    return "int";
}

// Returns the ffi.TYPE_* constant name for the FFI type id
std::string ffi_type_id(const CType& t) {
    switch (t.kind) {
        case CType::Void:     return "ffi.TYPE_VOID";
        case CType::Bool:     return "ffi.TYPE_I8";
        case CType::Char:     return t.is_unsigned ? "ffi.TYPE_U8" : "ffi.TYPE_I8";
        case CType::Short:    return t.is_unsigned ? "ffi.TYPE_U16" : "ffi.TYPE_I16";
        case CType::Int:      return t.is_unsigned ? "ffi.TYPE_U32" : "ffi.TYPE_I32";
        case CType::Long:     return t.is_unsigned ? "ffi.TYPE_U64" : "ffi.TYPE_I64";
        case CType::LongLong: return t.is_unsigned ? "ffi.TYPE_U64" : "ffi.TYPE_I64";
        case CType::Float:    return "ffi.TYPE_F32";
        case CType::Double:   return "ffi.TYPE_F64";
        case CType::Ptr:      return "ffi.TYPE_PTR";
        case CType::FixedWidth: {
            if (t.width == 8)  return t.is_unsigned ? "ffi.TYPE_U8" : "ffi.TYPE_I8";
            if (t.width == 16) return t.is_unsigned ? "ffi.TYPE_U16" : "ffi.TYPE_I16";
            if (t.width == 32) return t.is_unsigned ? "ffi.TYPE_U32" : "ffi.TYPE_I32";
            return t.is_unsigned ? "ffi.TYPE_U64" : "ffi.TYPE_I64";
        }
        case CType::Struct:   return "ffi.TYPE_PTR"; // struct args use struct_param() descriptors
        case CType::Custom:   return "ffi.TYPE_I64";
    }
    return "ffi.TYPE_I64";
}

bool is_float_type(const CType& t) { return t.kind == CType::Float || t.kind == CType::Double; }
bool is_void_type(const CType& t) { return t.kind == CType::Void; }

// Determine which call helper to use:
// Returns "call_i64_0", "call_i64_1", "call_i64_2", "call_f64_2", "call_void_1",
// or "" for fallback (generic foreign_call).
std::string select_helper(const CFunctionDecl& fn) {
    if (is_void_type(fn.return_type)) {
        // void return: call_void_1 works for exactly 1 ptr arg
        if (fn.params.size() == 1 && !fn.is_variadic) {
            return "call_void_1";
        }
        if (fn.params.empty() && !fn.is_variadic) {
            // void func() - no args, void return - use call_i64_0 and discard
            return "call_i64_0";
        }
        return "";
    }
    // Non-void return
    if (fn.params.size() == 0 && !fn.is_variadic) return "call_i64_0";
    if (fn.params.size() == 1 && !fn.is_variadic && !is_float_type(fn.params[0].type))
        return "call_i64_1";
    if (fn.params.size() == 2 && !fn.is_variadic) {
        if (is_float_type(fn.params[0].type) && is_float_type(fn.params[1].type))
            return "call_f64_2";
        if (!is_float_type(fn.params[0].type) && !is_float_type(fn.params[1].type))
            return "call_i64_2";
    }
    return ""; // generic fallback
}

// ─── Direct C-extern calls (AOT native Call, VM fnptr+libffi) ────────────────
std::string safe_param_name(const CParam& p, size_t index);
std::string c_signature_str_impl(const CFunctionDecl& fn);
// A param is direct-safe when its C ABI maps cleanly onto the Lymar word the
// binding passes: int-family -> i64, float/double -> f64 (the boundary cast
// narrows to f32 for C `float`), pointer -> i64. Variadic and struct/unknown
// types stay on the generic path.
bool direct_safe_param(const CType& t) {
    switch (t.kind) {
        case CType::Bool: case CType::Char: case CType::Short: case CType::Int:
        case CType::Long: case CType::LongLong: case CType::Ptr: case CType::Double:
        case CType::Float:
            return true;
        case CType::FixedWidth: return t.width <= 64;
        // Small flat structs (<=16 bytes) lower to native register/stack
        // packing in AOT; the VM path marshals them through libffi.
        case CType::Struct:
            return is_supported_struct(t) && t.def->size <= 16;
        default: return false;
    }
}

// Whether the function's return type can be produced by the direct path:
// void, scalar types, or a small supported struct (register/sret return).
bool direct_safe_return(const CType& t) {
    if (is_void_type(t)) return true;
    if (t.kind == CType::Struct)
        return is_supported_struct(t) && t.def->size <= 16;
    return direct_safe_param(t);
}

// A signature eligible for AOT call-site lowering (ForeignCallDirect with
// native ABI packing). Unlike direct_helper this admits struct params and
// struct returns; the generated wrapper still uses ffi.foreign_call so the
// VM path stays correct.
bool direct_call_site_safe(const CFunctionDecl& fn) {
    if (fn.is_variadic || fn.params.size() > 8) return false;
    for (const auto& p : fn.params)
        if (!direct_safe_param(p.type)) return false;
    return direct_safe_return(fn.return_type);
}

// Returns the c_call_* helper name for signatures that can use a direct
// extern call, or "" to keep the typed/generic foreign_call path. Return
// kinds: void, i64-family ints, f64, ptr. Narrower signed/unsigned returns
// are handled by a shift/mask fixup in the emitted wrapper.
std::string direct_helper(const CFunctionDecl& fn) {
    if (fn.is_variadic || fn.params.size() > 4) return "";
    for (const auto& p : fn.params)
        // Struct args need libffi struct marshaling the c_call_* intrinsics
        // cannot express; they stay on the ffi.foreign_call wrapper path.
        if (p.type.kind == CType::Struct || !direct_safe_param(p.type)) return "";
    const CType& r = fn.return_type;
    if (r.kind == CType::Struct) return "";
    const std::string p = "c_call_";
    const std::string n = std::to_string(fn.params.size());
    if (is_void_type(r)) return p + "void_" + n;
    if (r.kind == CType::Ptr) return p + "ptr_" + n;
    if (r.kind == CType::Double) return p + "f64_" + n;
    if (r.kind == CType::Float) return p + "f32_" + n;
    switch (r.kind) {
        case CType::Bool: case CType::Char: case CType::Short: case CType::Int:
        case CType::Long: case CType::LongLong:
            return p + "i64_" + n;
        case CType::FixedWidth:
            return r.width <= 64 ? p + "i64_" + n : "";
        default:
            return ""; // Float(f32), Custom, etc.
    }
}

// Post-call fixup for sub-64-bit integer returns: the extern call yields the
// raw register contents; sign-extend signed values and mask unsigned ones.
// Sign extension uses the (x ^ signbit) - signbit trick because `>>` is not
// reliably arithmetic across VM/AOT. Returns "" when i64 is already exact.
std::string return_fixup(const CType& t) {
    auto mask = [](uint64_t bits) {
        return "(_r & " + std::to_string(bits) + ")";
    };
    auto sext = [](uint64_t signbit) {
        return "((_r ^ " + std::to_string(signbit) + ") - " +
               std::to_string(signbit) + ")";
    };
    // Sub-32-bit returns can carry garbage above the return width in rax, so
    // mask to the width before sign-extending.
    auto sext_narrow = [&](uint64_t mask_bits, uint64_t signbit) {
        return "(((_r & " + std::to_string(mask_bits) + ") ^ " +
               std::to_string(signbit) + ") - " + std::to_string(signbit) + ")";
    };
    switch (t.kind) {
        case CType::Bool:   return mask(1);
        case CType::Char:   return t.is_unsigned ? mask(0xFF) : sext_narrow(0xFF, 0x80);
        case CType::Short:  return t.is_unsigned ? mask(0xFFFF) : sext_narrow(0xFFFF, 0x8000);
        case CType::Int:    return t.is_unsigned ? mask(0xFFFFFFFFULL) : sext(0x80000000ULL);
        case CType::FixedWidth:
            if (t.width >= 64) return "";
            if (t.width == 32) {
                return t.is_unsigned ? mask(0xFFFFFFFFULL) : sext(0x80000000ULL);
            }
            if (t.is_unsigned) {
                if (t.width == 8)  return mask(0xFF);
                return mask(0xFFFF);
            }
            if (t.width == 8)  return sext_narrow(0xFF, 0x80);
            return sext_narrow(0xFFFF, 0x8000);
        default: return ""; // i64/u64/long/longlong: exact already
    }
}

// Per-argument expression: int-family params normalize with `as int`,
// float/ptr params already carry the right Lymar type.
std::string direct_arg_expr(const CFunctionDecl& fn, size_t i) {
    std::string name = safe_param_name(fn.params[i], i);
    switch (fn.params[i].type.kind) {
        case CType::Bool: case CType::Char: case CType::Short: case CType::Int:
        case CType::Long: case CType::LongLong: case CType::FixedWidth:
            return name + " as int";
        case CType::Float:
            // C `float` is f32; the Lymar `float` param is f64. The `as f32`
            // gives the argument an F32 ABI type so VM libffi marshals a
            // true float and AOT narrows at the extern boundary.
            return name + " as f32";
        default:
            return name; // Double -> float, Ptr -> ffi.pubptr
    }
}

void emit_direct_fn(std::ostringstream& out, const CFunctionDecl& fn,
                    const std::string& helper) {
    out << "// C: " << c_signature_str_impl(fn) << "\n";
    out << "// (direct extern call -- AOT emits a native call)\n";

    out << "pub fn " << fn.name << "(";
    for (size_t i = 0; i < fn.params.size(); ++i) {
        if (i > 0) out << ", ";
        out << safe_param_name(fn.params[i], i) << ": " << lymar_type(fn.params[i].type);
    }
    out << "): " << lymar_type(fn.return_type) << " {\n";
    out << "    _ensure();\n";
    out << "    unsafe {\n";

    std::string call = "ffi." + helper + "(_sym_" + fn.name + ", \"" + fn.name + "\"";
    for (size_t i = 0; i < fn.params.size(); ++i)
        call += ", " + direct_arg_expr(fn, i);
    call += ")";

    std::string fixup = return_fixup(fn.return_type);
    if (helper.rfind("c_call_void_", 0) == 0) {
        out << "        return " << call << ";\n";
    } else if (fn.return_type.kind == CType::Float) {
        // c_call_f32_* yields f32; widen back to the wrapper's `float` (f64).
        out << "        return (" << call << ") as float;\n";
    } else if (fixup.empty()) {
        out << "        return " << call << ";\n";
    } else {
        out << "        var _r: int = " << call << ";\n";
        out << "        return " << fixup << ";\n";
    }
    out << "    }\n";
    out << "}\n\n";
}

// Helper to format a C signature for comments in generated output
std::string c_signature_str_impl(const CFunctionDecl& fn) {
    std::ostringstream ss;
    switch (fn.return_type.kind) {
        case CType::Void: ss << "void"; break;
        case CType::Bool: ss << "_Bool"; break;
        case CType::Char: ss << (fn.return_type.is_unsigned ? "unsigned char" : "char"); break;
        case CType::Short: ss << (fn.return_type.is_unsigned ? "unsigned short" : "short"); break;
        case CType::Int: ss << (fn.return_type.is_unsigned ? "unsigned int" : "int"); break;
        case CType::Long: ss << (fn.return_type.is_unsigned ? "unsigned long" : "long"); break;
        case CType::LongLong: ss << (fn.return_type.is_unsigned ? "unsigned long long" : "long long"); break;
        case CType::Float: ss << "float"; break;
        case CType::Double: ss << "double"; break;
        case CType::Ptr: ss << "void*"; break;
        case CType::FixedWidth: ss << fn.return_type.base_name; break;
        case CType::Custom: ss << (fn.return_type.base_name.empty() ? "auto" : fn.return_type.base_name); break;
        case CType::Struct: ss << (fn.return_type.base_name.empty() ? "struct" : "struct " + fn.return_type.base_name); break;
    }
    ss << " " << fn.name << "(";
    for (size_t i = 0; i < fn.params.size(); ++i) {
        if (i > 0) ss << ", ";
        const auto& p = fn.params[i];
        switch (p.type.kind) {
            case CType::Void: ss << "void"; break;
            case CType::Ptr: ss << "void*"; break;
            case CType::FixedWidth: ss << p.type.base_name; break;
            case CType::Custom: ss << (p.type.base_name.empty() ? "?" : p.type.base_name); break;
            case CType::Struct: ss << (p.type.base_name.empty() ? "struct" : "struct " + p.type.base_name); break;
            default:
                if (p.type.is_unsigned) ss << "unsigned ";
                switch (p.type.kind) {
                    case CType::Char: ss << "char"; break;
                    case CType::Short: ss << "short"; break;
                    case CType::Int: ss << "int"; break;
                    case CType::Long: ss << "long"; break;
                    case CType::LongLong: ss << "long long"; break;
                    case CType::Float: ss << "float"; break;
                    case CType::Double: ss << "double"; break;
                    default: ss << "?"; break;
                }
        }
        if (!p.name.empty()) ss << " " << p.name;
    }
    if (fn.is_variadic) ss << (fn.params.empty() ? "" : ", ") << "...";
    ss << ")";
    return ss.str();
}

// Returns a safe Lymar identifier for a C parameter name.
// Reserved words (val, var, const, fn, if, etc.) are prefixed with 'p_'.
std::string safe_param_name(const CParam& p, size_t index) {
    static const std::vector<std::string> reserved = {
        "val","var","const","fn","if","elif","else","while","for","iter",
        "return","frame","trait","import","match","in","type","enum",
        "err","ok","and","or","not","as","where","self","super",
        "true","false","nil","break","continue","parallel","concurrent",
        "task","worker","contract","staged","unsafe","module","mixin",
        "show","hide","from","static","pub","prot","any","bool","int",
        "float","str","channel","atomic","embed","init","deinit","this"
    };
    std::string name = p.name;
    if (name.empty()) return "arg" + std::to_string(index);
    bool is_reserved = std::find(reserved.begin(), reserved.end(), name) != reserved.end();
    if (is_reserved) return "p_" + name;
    return name;
}

// ─── Code emitter ─────────────────────────────────────────────────────────────

void emit_preamble(std::ostringstream& out, const std::string& module_name,
                   const std::string& lib_path,
                   const std::vector<std::string>& direct_syms) {
    out << "// Auto-generated from " << module_name << " header -- do not edit.\n";
    out << "import std.ffi as ffi;\n\n";
    out << "var _handle: ffi.pubptr = 0;\n";
    for (const auto& sym : direct_syms)
        out << "var _sym_" << sym << ": ffi.fnptr = 0;\n";
    out << "\n";
    out << "fn _ensure() {\n";
    out << "    if (_handle == 0) {\n";
    out << "        unsafe {\n";
    out << "            _handle = ffi.library_load(\"" << lib_path << "\");\n";
    for (const auto& sym : direct_syms)
        out << "            _sym_" << sym << " = ffi.library_get_symbol(_handle, \"" << sym << "\");\n";
    out << "        }\n";
    out << "    }\n";
    out << "}\n\n";
}

void emit_typed_fn(std::ostringstream& out, const CFunctionDecl& fn,
                   const std::string& helper) {
    // Comment with original C signature
    out << "// C: " << c_signature_str_impl(fn) << "\n";

    // Build Lymar parameter list
    out << "pub fn " << fn.name << "(";
    for (size_t i = 0; i < fn.params.size(); ++i) {
        if (i > 0) out << ", ";
        out << safe_param_name(fn.params[i], i) << ": " << lymar_type(fn.params[i].type);
    }
    out << "): " << lymar_type(fn.return_type) << " {\n";
    out << "    _ensure();\n";
    out << "    unsafe {\n";

    std::string sym = "ffi.library_get_symbol(_handle, \"" + fn.name + "\")";

    if (helper == "call_i64_0") {
        out << "        return ffi.call_i64_0(" << sym << ") as " << lymar_type(fn.return_type) << ";\n";
    } else if (helper == "call_i64_1") {
        std::string arg0 = safe_param_name(fn.params[0], 0);
        out << "        return ffi.call_i64_1(" << sym << ", " << arg0 << " as int) as " << lymar_type(fn.return_type) << ";\n";
    } else if (helper == "call_i64_2") {
        std::string arg0 = safe_param_name(fn.params[0], 0);
        std::string arg1 = safe_param_name(fn.params[1], 1);
        out << "        return ffi.call_i64_2(" << sym << ", " << arg0 << " as int, " << arg1 << " as int) as " << lymar_type(fn.return_type) << ";\n";
    } else if (helper == "call_f64_2") {
        std::string arg0 = safe_param_name(fn.params[0], 0);
        std::string arg1 = safe_param_name(fn.params[1], 1);
        out << "        return ffi.call_f64_2(" << sym << ", " << arg0 << ", " << arg1 << ");\n";
    } else if (helper == "call_void_1") {
        std::string arg0 = safe_param_name(fn.params[0], 0);
        out << "        ffi.call_void_1(" << sym << ", " << arg0 << ");\n";
    }
    out << "    }\n";
    out << "}\n\n";
}

// Raw [any] literal of ffi.TYPE_* ids for a struct's fields (for
// ffi.struct_alloc); "[]" for non-struct types.
std::string struct_elem_list(const CType& t) {
    auto ids = struct_elem_type_ids(t);
    if (ids.empty()) return "[]";
    std::string out = "[";
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i) out += ", ";
        out += ids[i];
    }
    out += "]";
    return out;
}

bool uses_struct(const CFunctionDecl& fn) {
    if (fn.return_type.kind == CType::Struct) return true;
    for (const auto& p : fn.params)
        if (p.type.kind == CType::Struct) return true;
    return false;
}

void emit_generic_fn(std::ostringstream& out, const CFunctionDecl& fn) {
    out << "// C: " << c_signature_str_impl(fn) << "\n";
    out << "// (generic fallback -- >2 params or mixed types)\n";

    out << "pub fn " << fn.name << "(";
    for (size_t i = 0; i < fn.params.size(); ++i) {
        if (i > 0) out << ", ";
        out << safe_param_name(fn.params[i], i) << ": " << lymar_type(fn.params[i].type);
    }
    out << "): " << lymar_type(fn.return_type) << " {\n";
    out << "    _ensure();\n";
    out << "    unsafe {\n";
    out << "        var _sym: ffi.fnptr = ffi.library_get_symbol(_handle, \"" << fn.name << "\");\n";
    out << "        var _args: [any] = [";
    for (size_t i = 0; i < fn.params.size(); ++i) {
        if (i > 0) out << ", ";
        out << safe_param_name(fn.params[i], i);
    }
    out << "];\n";
    out << "        var _ptypes: [any] = [";
    for (size_t i = 0; i < fn.params.size(); ++i) {
        if (i > 0) out << ", ";
        const auto& pt = fn.params[i].type;
        if (pt.kind == CType::Struct && is_supported_struct(pt))
            out << "ffi.struct_param(" << struct_elem_list(pt) << ")";
        else
            out << ffi_type_id(pt);
    }
    out << "];\n";

    const bool struct_ret = fn.return_type.kind == CType::Struct && is_supported_struct(fn.return_type);
    if (struct_ret) {
        // Struct-by-value return: foreign_call writes the result bytes into
        // a caller-allocated buffer (libffi handles sret/register returns).
        out << "        var _rb: ffi.pubptr = ffi.struct_alloc(" << struct_elem_list(fn.return_type) << ");\n";
        out << "        ffi.foreign_call(_sym, _args, " << struct_param_expr(fn.return_type)
            << ", _ptypes, _rb);\n";
        out << "        return _rb;\n";
    } else {
        std::string ret_expr;
        if (fn.return_type.kind == CType::Struct)
            ret_expr = "ffi.struct_param(" + struct_elem_list(fn.return_type) + ")";
        else
            ret_expr = ffi_type_id(fn.return_type);
        out << "        return ffi.foreign_call(_sym, _args, " << ret_expr << ", _ptypes) as "
            << lymar_type(fn.return_type) << ";\n";
    }
    out << "    }\n";
    out << "}\n\n";
}

// Returns a safe Lymar identifier for a C constant name.
// Reserved words are prefixed with 'c_'.
std::string safe_const_name(const std::string& name) {
    static const std::vector<std::string> reserved = {
        "val","var","const","fn","if","elif","else","while","for","iter",
        "return","frame","trait","import","match","in","type","enum",
        "err","ok","and","or","not","as","where","self","super",
        "true","false","nil","break","continue","parallel","concurrent",
        "task","worker","contract","staged","unsafe","module","mixin",
        "show","hide","from","static","pub","prot","any","bool","int",
        "float","str","channel","atomic","embed","init","deinit","this"
    };
    if (std::find(reserved.begin(), reserved.end(), name) != reserved.end())
        return "c_" + name;
    return name;
}

void emit_constants(std::ostringstream& out, const std::vector<CConstantDecl>& constants) {
    if (constants.empty()) return;
    out << "// Constants extracted from C enum bodies.\n";
    std::unordered_set<std::string> seen;
    for (const auto& c : constants) {
        std::string name = safe_const_name(c.name);
        if (!seen.insert(name).second) continue; // first definition wins
        out << "pub const " << name << ": int = " << c.value << ";\n";
    }
    out << "\n";
}

} // anonymous namespace

std::string generate_bindings(const std::vector<CFunctionDecl>& functions,
                              const std::vector<CConstantDecl>& constants,
                              const std::string& module_name,
                              const std::string& lib_path) {
    std::ostringstream out;

    // Publish direct-call signatures so AOT call sites can bypass wrappers.
    register_c_direct_signatures(module_name, functions);

    // Pre-scan: signatures that qualify for a direct extern call get their
    // fnptr cached by _ensure so wrappers can pass it to c_call_*.
    std::vector<std::string> direct_syms;
    for (const auto& fn : functions)
        if (!direct_helper(fn).empty()) direct_syms.push_back(fn.name);

    emit_preamble(out, module_name, lib_path, direct_syms);
    emit_constants(out, constants);

    for (const auto& fn : functions) {
        if (uses_struct(fn)) {
            // Struct-by-value signatures always take the descriptor-driven
            // foreign_call path: correct on VM (libffi) and AOT fallback.
            emit_generic_fn(out, fn);
            continue;
        }
        std::string direct = direct_helper(fn);
        if (!direct.empty()) {
            emit_direct_fn(out, fn, direct);
            continue;
        }
        std::string helper = select_helper(fn);
        if (helper.empty()) {
            emit_generic_fn(out, fn);
        } else {
            emit_typed_fn(out, fn, helper);
        }
    }
    return out.str();
}

void register_c_direct_signatures(const std::string& module_name,
                                  const std::vector<CFunctionDecl>& decls) {
    auto& table = direct_signature_table();
    for (const auto& fn : decls) {
        // Registration covers both c_call_* wrapper lowering AND call-site
        // ForeignCallDirect lowering; the builder picks native packing when
        // the signature is ABI-expressible and falls back to the wrapper
        // call otherwise.
        if (direct_helper(fn).empty() && !direct_call_site_safe(fn)) continue;
        CDirectSignature sig;
        sig.symbol = fn.name;
        sig.return_type = fn.return_type;
        sig.arg_types.reserve(fn.params.size());
        for (const auto& p : fn.params) sig.arg_types.push_back(p.type);
        table[module_name + "." + fn.name] = std::move(sig);
    }
}

const CDirectSignature* find_c_direct_signature(const std::string& qualified_name) {
    auto& table = direct_signature_table();
    auto it = table.find(qualified_name);
    return it == table.end() ? nullptr : &it->second;
}

} // namespace LM::Backend::Native
