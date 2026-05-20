#ifndef REGISTER_VALUE_H
#define REGISTER_VALUE_H

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <mutex>
#include "../runtime/runtime_value_base.h"

namespace LM {
namespace Backend {

// RegisterValue is now a unified tagged LmValue
using RegisterValue = LmValue;

// Frame instance representation for VM execution
struct FrameInstance {
    ObjHeader header;
    std::string frame_type;
    std::vector<RegisterValue> fields;
    mutable std::mutex mutex;
    
    FrameInstance() {
        header.type_id = TYPE_FRAME;
        header.metadata = 0;
    }
    explicit FrameInstance(const std::string& type_name) : frame_type(type_name) {
        header.type_id = TYPE_FRAME;
        header.metadata = 0;
    }
    explicit FrameInstance(const std::string& type_name, size_t field_count)
        : frame_type(type_name), fields(field_count, VAL_NIL) {
        header.type_id = TYPE_FRAME;
        header.metadata = (uint32_t)field_count;
    }
    
    const RegisterValue& getField(size_t index) const {
        if (index >= fields.size()) {
            static RegisterValue nil_val = VAL_NIL;
            return nil_val;
        }
        return fields[index];
    }
    
    void setField(size_t index, RegisterValue value) {
        if (index >= fields.size()) {
            fields.resize(index + 1, VAL_NIL);
        }
        fields[index] = value;
    }
};

using FrameInstancePtr = std::shared_ptr<FrameInstance>;

} // namespace Backend
} // namespace LM

#endif // REGISTER_VALUE_H
