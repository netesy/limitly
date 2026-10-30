// binding_generator.cpp - Emits a Lymar module wrapping C functions with std.ffi
// typed call helpers. See the header for design details.

#include "binding_generator.hh"
#include <sstream>
#include <algorithm>

namespace LM::Backend::Native {
namespace {

// ─── Type mapping helpers ─────────────────────────────────────────────────────

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
                   const std::string& lib_path) {
    out << "// Auto-generated from " << module_name << " header -- do not edit.\n";
    out << "import std.ffi as ffi;\n\n";
    out << "var _handle: ffi.pubptr = 0;\n\n";
    out << "fn _ensure() {\n";
    out << "    if (_handle == 0) {\n";
    out << "        unsafe {\n";
    out << "            _handle = ffi.library_load(\"" << lib_path << "\");\n";
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
        out << ffi_type_id(fn.params[i].type);
    }
    out << "];\n";
    out << "        return ffi.foreign_call(_sym, _args, " << ffi_type_id(fn.return_type) << ", _ptypes) as " << lymar_type(fn.return_type) << ";\n";
    out << "    }\n";
    out << "}\n\n";
}

} // anonymous namespace

std::string generate_bindings(const std::vector<CFunctionDecl>& functions,
                              const std::string& module_name,
                              const std::string& lib_path) {
    std::ostringstream out;
    emit_preamble(out, module_name, lib_path);

    for (const auto& fn : functions) {
        std::string helper = select_helper(fn);
        if (helper.empty()) {
            emit_generic_fn(out, fn);
        } else {
            emit_typed_fn(out, fn, helper);
        }
    }
    return out.str();
}

} // namespace LM::Backend::Native
