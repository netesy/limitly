#include "../register.hh"
#include "../vm_value.hh"
#include "../../../frontend/value.hh"
#include <cmath>
#include <stdexcept>
#include <string>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

namespace {

// Return the decimal scale (number of digits after the decimal point)
// associated with a language type. Returns -1 for non-decimal types.
int decimal_scale_of(const ::TypePtr& t) {
    if (!t) return -1;
    switch (t->tag) {
        case ::TypeTag::Decimal2: return 2;
        case ::TypeTag::Decimal4: return 4;
        case ::TypeTag::Decimal6: return 6;
        default: return -1;
    }
}

// Compute 10^n for small non-negative n.
int64_t pow10_i64(int n) {
    int64_t r = 1;
    for (int i = 0; i < n; ++i) r *= 10;
    return r;
}

} // namespace

void RegisterVM::execute_arithmetic(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::Add:
            registers[pc->dst] = lm_add(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::Sub:
            registers[pc->dst] = lm_sub(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::Mul:
            registers[pc->dst] = lm_mul(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::Div:
            registers[pc->dst] = lm_div(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::Mod:
            if (is_integer(registers[pc->a]) && is_integer(registers[pc->b])) {
                __int128 divisor = as_i128(registers[pc->b]);
                registers[pc->dst] = divisor == 0 ? VAL_NIL : make_i128(as_i128(registers[pc->a]) % divisor);
            } else if (is_numeric(registers[pc->a]) && is_numeric(registers[pc->b])) {
                double divisor = as_float(registers[pc->b]);
                registers[pc->dst] = divisor == 0.0 ? VAL_NIL : make_float(std::fmod(as_float(registers[pc->a]), divisor));
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::Neg:
            registers[pc->dst] = lm_sub(make_i64(0), registers[pc->a]);
            break;
        case LIR::LIR_Op::DecAdd:
            registers[pc->dst] = lm_add(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::DecSub:
            registers[pc->dst] = lm_sub(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::DecMul:
            // Simplified: decimal multiply needs rescaling, but let's use runtime
            registers[pc->dst] = lm_mul(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::DecDiv:
            registers[pc->dst] = lm_div(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::DecMod:
            if (is_integer(registers[pc->a]) && is_integer(registers[pc->b])) {
                __int128 divisor = as_i128(registers[pc->b]);
                registers[pc->dst] = divisor == 0 ? VAL_NIL : make_i128(as_i128(registers[pc->a]) % divisor);
            } else {
                double divisor = as_float(registers[pc->b]);
                registers[pc->dst] = divisor == 0.0 ? VAL_NIL : make_float(std::fmod(as_float(registers[pc->a]), divisor));
            }
            break;
        case LIR::LIR_Op::DecNeg:
            registers[pc->dst] = lm_sub(make_i64(0), registers[pc->a]);
            break;
        case LIR::LIR_Op::DecRescale: {
            // M34: previously this was a no-op copy, which silently dropped
            // decimal precision. Rescale the integer representation of the
            // decimal value from the source scale to the target scale by
            // multiplying or dividing by 10^(target_scale - source_scale).
            //
            // The source and target decimal scales are looked up from the
            // current function's per-register language-type table. If the
            // type information is unavailable (e.g. the LIR wasn't emitted
            // by the decimal-aware generator path) we fall back to a plain
            // copy so existing callers don't crash.
            int src_scale = -1;
            int dst_scale = -1;
            if (current_function_) {
                auto src_it = current_function_->register_language_types.find(pc->a);
                if (src_it != current_function_->register_language_types.end()) {
                    src_scale = decimal_scale_of(src_it->second);
                }
                auto dst_it = current_function_->register_language_types.find(pc->dst);
                if (dst_it != current_function_->register_language_types.end()) {
                    dst_scale = decimal_scale_of(dst_it->second);
                }
            }

            RegisterValue src = registers[pc->a];
            if (src_scale < 0 || dst_scale < 0 || src_scale == dst_scale) {
                // No type info or no rescaling required: identity copy.
                registers[pc->dst] = src;
                break;
            }

            int delta = dst_scale - src_scale;  // positive => multiply
            if (is_integer(src)) {
                int64_t v = as_i64(src);
                if (delta > 0) {
                    int64_t factor = pow10_i64(delta);
                    registers[pc->dst] = make_i64(v * factor);
                } else {
                    int64_t factor = pow10_i64(-delta);
                    // Truncating division towards zero, matching the
                    // existing decimal semantics.
                    registers[pc->dst] = make_i64(v / factor);
                }
            } else if (is_float(src)) {
                double v = as_float(src);
                if (delta > 0) {
                    double factor = std::pow(10.0, delta);
                    registers[pc->dst] = make_float(v * factor);
                } else {
                    double factor = std::pow(10.0, -delta);
                    registers[pc->dst] = make_float(v / factor);
                }
            } else {
                registers[pc->dst] = src;
            }
            break;
        }
        default:
            throw std::runtime_error(
                "VM: execute_arithmetic: unsupported opcode " +
                std::to_string(static_cast<int>(pc->op)));
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

