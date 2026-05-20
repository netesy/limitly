#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../../lir/function_registry.hh"
#include "../../lir/builtin_functions.hh"
#include "register.hh"
#include "../../runtime/runtime.h"
#include "../../runtime/runtime_list.h"
#include "../../runtime/runtime_dict.h"
#include "../../runtime/runtime_tuple.h"
#include "../../runtime/runtime_value.h"
#include <iostream>
#include <memory>
#include <cstring>
#include <cstdint>
#include <string>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// Helpers moved from register.cpp or redefined
int get_decimal_scale(TypeTag tag) {
    switch (tag) {
        case TypeTag::Decimal2: return 2;
        case TypeTag::Decimal4: return 4;
        case TypeTag::Decimal6: return 6;
        default: return 0;
    }
}

constexpr const char* INTERNAL_ENUM_FRAME_TYPE = "__lir_internal_enum__";

// Hash function for boxed values - now defined in runtime_dict.c
extern "C" {
    uint64_t hash_boxed_value(LmValue key);
    int cmp_boxed_value(LmValue k1, LmValue k2);
}

std::string RegisterVM::to_string(const RegisterValue& value) const {
    LmString s = lm_value_to_string(value);
    std::string result(s.data ? s.data : "nil");
    lm_string_free(s);
    return result;
}

ValuePtr RegisterVM::createErrorValue(const std::string& errorType, const std::string& message) {
    auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
    return std::make_shared<::Value>(nil_type, "Error: " + errorType + ": " + message);
}

ValuePtr RegisterVM::createSuccessValue(const RegisterValue& value) {
    auto string_type = std::make_shared<::Type>(TypeTag::String);
    return std::make_shared<::Value>(string_type, this->to_string(value));
}

bool RegisterVM::isErrorValue(LIR::Reg reg) const {
    auto& value = registers[reg];
    if (is_integer(value)) {
        int64_t int_val = as_i64(value);
        return int_val <= -1000000;
    }
    return false;
}

RegisterVM::RegisterVM()
    : type_system(std::make_unique<TypeSystem>()) {
    registers.resize(1024, VAL_NIL);
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function_ = nullptr;

    shared_variables.emplace(std::piecewise_construct,
        std::forward_as_tuple("shared_counter"),
        std::forward_as_tuple(0));
}

void RegisterVM::reset() {
    std::fill(registers.begin(), registers.end(), VAL_NIL);
    argument_stack.clear();
    task_contexts.clear();
    channels.clear();
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function_ = nullptr;

    shared_variables.clear();
    shared_variables.emplace(std::piecewise_construct,
        std::forward_as_tuple("shared_counter"),
        std::forward_as_tuple(0));

    shared_cells.clear();
    default_atomic.store(0);
    work_queues.clear();
    work_queue_counter.store(0);
    instruction_count = 0;
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
