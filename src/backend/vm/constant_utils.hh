#ifndef LIMITLY_BACKEND_VM_CONSTANT_UTILS_H
#define LIMITLY_BACKEND_VM_CONSTANT_UTILS_H

#include "frontend/value.hh"
#include "backend/value.hh"
#include "backend/vm/vm_runtime.hh"
#include "backend/vm/vm_value.hh"
#include "backend/vm/vm_list.hh"

namespace LM {
namespace Backend {
namespace VM {

inline __int128 parse_i128_literal(const std::string& text) {
    bool negative = !text.empty() && text[0] == '-';
    size_t start = negative ? 1 : 0;
    unsigned __int128 value = 0;
    for (size_t i = start; i < text.size(); ++i) {
        if (text[i] < '0' || text[i] > '9') break;
        value = value * 10 + static_cast<unsigned>(text[i] - '0');
    }
    return negative ? -static_cast<__int128>(value) : static_cast<__int128>(value);
}

inline unsigned __int128 parse_u128_literal(const std::string& text) {
    unsigned __int128 value = 0;
    for (char c : text) {
        if (c < '0' || c > '9') break;
        value = value * 10 + static_cast<unsigned>(c - '0');
    }
    return value;
}

inline LM::Backend::Value compiler_value_to_backend_value(const std::shared_ptr<::Value>& cv) {
    if (!cv) return VAL_NIL;
    switch (cv->type->tag) {
        case ::TypeTag::Int:
        case ::TypeTag::Int8:
        case ::TypeTag::Int16:
        case ::TypeTag::Int32:
        case ::TypeTag::Int64: {
            try {
                return make_i64(std::stoll(cv->data));
            } catch (...) {
                try {
                    return make_u64(std::stoull(cv->data));
                } catch (...) {
                    return make_i128(parse_i128_literal(cv->data));
                }
            }
        }
        case ::TypeTag::Decimal2: {
            size_t dot = cv->data.find('.');
            int64_t scaled = 0;
            if (dot == std::string::npos) scaled = std::stoll(cv->data) * 100;
            else {
                std::string ip = cv->data.substr(0, dot);
                std::string fp = cv->data.substr(dot + 1);
                while (fp.length() < 2) fp += '0';
                if (fp.length() > 2) fp = fp.substr(0, 2);
                scaled = (ip.empty() ? 0 : std::stoll(ip)) * 100 + (fp.empty() ? 0 : std::stoll(fp));
            }
            return make_i64(scaled);
        }
        case ::TypeTag::Decimal4: {
            size_t dot = cv->data.find('.');
            int64_t scaled = 0;
            if (dot == std::string::npos) scaled = std::stoll(cv->data) * 10000;
            else {
                std::string ip = cv->data.substr(0, dot);
                std::string fp = cv->data.substr(dot + 1);
                while (fp.length() < 4) fp += '0';
                if (fp.length() > 4) fp = fp.substr(0, 4);
                scaled = (ip.empty() ? 0 : std::stoll(ip)) * 10000 + (fp.empty() ? 0 : std::stoll(fp));
            }
            return make_i64(scaled);
        }
        case ::TypeTag::Decimal6: {
            size_t dot = cv->data.find('.');
            int64_t scaled = 0;
            if (dot == std::string::npos) scaled = std::stoll(cv->data) * 1000000;
            else {
                std::string ip = cv->data.substr(0, dot);
                std::string fp = cv->data.substr(dot + 1);
                while (fp.length() < 6) fp += '0';
                if (fp.length() > 6) fp = fp.substr(0, 6);
                scaled = (ip.empty() ? 0 : std::stoll(ip)) * 1000000 + (fp.empty() ? 0 : std::stoll(fp));
            }
            return make_i64(scaled);
        }
        case ::TypeTag::Int128:
            return make_i128(parse_i128_literal(cv->data));
        case ::TypeTag::UInt:
        case ::TypeTag::UInt8:
        case ::TypeTag::UInt16:
        case ::TypeTag::UInt32:
        case ::TypeTag::UInt64:
            return make_u64(std::stoull(cv->data));
        case ::TypeTag::UInt128:
            return make_u128(parse_u128_literal(cv->data));
        case ::TypeTag::Float32:
        case ::TypeTag::Float64:
            return make_float(std::stod(cv->data));
        default:
            break;
    }
    if (cv->type->tag == ::TypeTag::List) {
        if (std::holds_alternative<ListValue>(cv->complexData)) {
            const auto& elements = std::get<ListValue>(cv->complexData).elements;
            LmList* list = lm_list_new();
            for (const auto& elem : elements) {
                lm_list_append(list, compiler_value_to_backend_value(elem));
            }
            return BOX_PTR(list);
        }
        return BOX_PTR(lm_list_new());
    }
    if (cv->type->tag == ::TypeTag::String) {
        return BOX_PTR(lm_str_from_bytes(cv->data.data(), cv->data.length()));
    }
    if (cv->type->tag == ::TypeTag::Bool) {
        return (cv->data == "true") ? VAL_TRUE : VAL_FALSE;
    }
    return VAL_NIL;
}

} // namespace VM
} // namespace Backend
} // namespace LM

#endif // LIMITLY_BACKEND_VM_CONSTANT_UTILS_H
