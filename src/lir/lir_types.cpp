#include "lir.hh"
#include <stdexcept>

namespace LIR {

std::string type_to_string(Type type) {
    switch (type) {
        case Type::I32: return "i32";
        case Type::I64: return "i64";
        case Type::F64: return "f64";
        case Type::Bool: return "bool";
        case Type::Ptr: return "ptr";
        case Type::Void: return "void";
        default: return "unknown_type";
    }
}

Type language_type_to_abi_type(TypePtr lang_type) {
    if (!lang_type) return Type::Void;
    
    switch (lang_type->tag) {
        // Integer types - map to appropriate ABI integer
        case TypeTag::Int8:
        case TypeTag::Int16:
        case TypeTag::Int32:
        case TypeTag::UInt8:
        case TypeTag::UInt16:
        case TypeTag::UInt32:
            return Type::I32;
            
        // 64-bit integers
        case TypeTag::Int64:
        case TypeTag::Int128:
        case TypeTag::UInt64:
        case TypeTag::UInt128:
            return Type::I64;
            
        // Other integer types
        case TypeTag::Int:
        case TypeTag::UInt:
            return Type::I64;
            
        // Floating point
        case TypeTag::Float32:
        case TypeTag::Float64:
            return Type::F64;
            
        // Boolean
        case TypeTag::Bool:
            return Type::Bool;
            
        // Reference types
        case TypeTag::String:
        case TypeTag::List:
        case TypeTag::Dict:
        case TypeTag::Tuple:
        case TypeTag::Function:
        case TypeTag::Closure:
        case TypeTag::Class:
        case TypeTag::Object:
            return Type::Ptr;
            
        // Other types
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
            
        // Nil
        case TypeTag::Nil:
            return Type::Void;
            
        default:
            return Type::Void;
    }
}

} // namespace LIR
