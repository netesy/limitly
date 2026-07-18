#include "lir.hh"
#include <stdexcept>

namespace LM {
namespace LIR {

std::string type_to_string(Type type) {
    switch (type) {
        case Type::I8: return "i8";
        case Type::U8: return "u8";
        case Type::I16: return "i16";
        case Type::U16: return "u16";
        case Type::I32: return "i32";
        case Type::U32: return "u32";
        case Type::I64: return "i64";
        case Type::U64: return "u64";
        case Type::F32: return "f32";
        case Type::F64: return "f64";
        case Type::Bool: return "bool";
        case Type::Ptr: return "ptr";
        case Type::Void: return "void";
        default: return "unknown_type";
    }
}

size_t get_type_size(Type type) {
    switch (type) {
        case Type::I8:   case Type::U8:   case Type::Bool: return 1;
        case Type::I16:  case Type::U16:  return 2;
        case Type::I32:  case Type::U32:  case Type::F32: return 4;
        case Type::I64:  case Type::U64:  case Type::F64: case Type::Ptr: return 8;
        default: return 0;
    }
}

size_t get_type_alignment(Type type) {
    return get_type_size(type);
}

bool is_integer_type(Type type) {
    switch (type) {
        case Type::I8:  case Type::U8:
        case Type::I16: case Type::U16:
        case Type::I32: case Type::U32:
        case Type::I64: case Type::U64: return true;
        default: return false;
    }
}

bool is_unsigned_type(Type type) {
    switch (type) {
        case Type::U8:  case Type::U16:
        case Type::U32: case Type::U64: return true;
        default: return false;
    }
}

bool is_float_type(Type type) {
    return type == Type::F32 || type == Type::F64;
}

Type language_type_to_abi_type(TypePtr lang_type) {
    if (!lang_type) return Type::Void;
    
    switch (lang_type->tag) {
        case TypeTag::Int8: return Type::I8;
        case TypeTag::UInt8: return Type::U8;
        case TypeTag::Int16: return Type::I16;
        case TypeTag::UInt16: return Type::U16;
        case TypeTag::Int32: return Type::I32;
        case TypeTag::UInt32: return Type::U32;
        case TypeTag::Int64:
        case TypeTag::Int128:
        case TypeTag::UInt64:
        case TypeTag::UInt128:
        case TypeTag::Decimal2:
        case TypeTag::Decimal4:
        case TypeTag::Decimal6:
        case TypeTag::Int:
        case TypeTag::UInt:
            return Type::I64;
        case TypeTag::Float32: return Type::F32;
        case TypeTag::Float64: return Type::F64;
        case TypeTag::Bool: return Type::Bool;
        case TypeTag::String:
        case TypeTag::List:
        case TypeTag::Dict:
        case TypeTag::Tuple:
        case TypeTag::Function:
        case TypeTag::Closure:
        case TypeTag::Frame:
        case TypeTag::Union:
        case TypeTag::Sum:
        case TypeTag::Enum:
        case TypeTag::Module:
        case TypeTag::Any:
        case TypeTag::Range:
        case TypeTag::Channel:
        case TypeTag::UserDefined:
        case TypeTag::ErrorUnion:
            return Type::Ptr;
        case TypeTag::Nil: return Type::Void;
        default: return Type::Void;
    }
}

} // namespace LIR
} // namespace LM
