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

Type language_type_to_abi_type(LanguageType* lang_type) {
    if (!lang_type) return Type::Void;
    
    switch (lang_type->tag) {
        // Integer types - map to appropriate ABI integer
        case LanguageTypeTag::Int8:
        case LanguageTypeTag::Int16:
        case LanguageTypeTag::Int32:
        case LanguageTypeTag::UInt8:
        case LanguageTypeTag::UInt16:
        case LanguageTypeTag::UInt32:
            return Type::I32;
            
        case LanguageTypeTag::Int64:
        case LanguageTypeTag::Int128:
        case LanguageTypeTag::UInt64:
        case LanguageTypeTag::UInt128:
            return Type::I64;
            
        // Floating point types
        case LanguageTypeTag::Float32:
        case LanguageTypeTag::Float64:
            return Type::F64;
            
        // Boolean
        case LanguageTypeTag::Bool:
            return Type::Bool;
            
        // String and complex types - all map to pointer
        case LanguageTypeTag::String:
        case LanguageTypeTag::List:
        case LanguageTypeTag::Dict:
        case LanguageTypeTag::Tuple:
        case LanguageTypeTag::Function:
        case LanguageTypeTag::Closure:
        case LanguageTypeTag::Class:
        case LanguageTypeTag::Struct:
        case LanguageTypeTag::Ptr:
        case LanguageTypeTag::Ref:
        case LanguageTypeTag::Union:
        case LanguageTypeTag::Intersection:
        case LanguageTypeTag::Option:
        case LanguageTypeTag::ErrorUnion:
        case LanguageTypeTag::Error:
        case LanguageTypeTag::Enum:
        case LanguageTypeTag::Module:
        case LanguageTypeTag::Any:
        default:
            return Type::Ptr;
            
        // Special types
        case LanguageTypeTag::Nil:
        case LanguageTypeTag::Void:
            return Type::Void;
    }
}

} // namespace LIR
