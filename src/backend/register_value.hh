#ifndef REGISTER_VALUE_H
#define REGISTER_VALUE_H

#include <variant>
#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>
#include <mutex>
#include "../runtime/runtime_value_base.h"

namespace LM {
namespace Backend {

// Forward declaration
struct FrameInstance;
using FrameInstancePtr = std::shared_ptr<FrameInstance>;

// Register value type - Can be a tagged int64_t, a double (not tagged), a string (not tagged), or a FrameInstance (not tagged)
// To comply with the objective, we will primarily use int64_t for tagged values.
using RegisterValue = std::variant<int64_t, uint64_t, double, bool, std::string, std::nullptr_t, FrameInstancePtr>;

// Frame instance representation for VM execution
// We keep this as a C++ struct for shared_ptr convenience, but we'll also have a C-compatible LmFrame in the runtime.
struct FrameInstance {
    ObjHeader header;                          // Header for consistency
    std::string frame_type;                    // Frame type name
    std::vector<RegisterValue> fields;         // Field values (indexed)
    mutable std::mutex mutex;                  // Mutex for atomic field access
    
    FrameInstance() {
        header.type_id = TYPE_FRAME;
        header.metadata = 0;
    }
    explicit FrameInstance(const std::string& type_name) : frame_type(type_name) {
        header.type_id = TYPE_FRAME;
        header.metadata = 0;
    }
    explicit FrameInstance(const std::string& type_name, size_t field_count)
        : frame_type(type_name), fields(field_count, (int64_t)VAL_NIL) {
        header.type_id = TYPE_FRAME;
        header.metadata = (uint32_t)field_count;
    }
    
    // Get field value
    const RegisterValue& getField(size_t index) const {
        if (index >= fields.size()) {
            static RegisterValue nil_val = (int64_t)VAL_NIL;
            return nil_val;
        }
        return fields[index];
    }
    
    // Set field value
    void setField(size_t index, const RegisterValue& value) {
        if (index >= fields.size()) {
            fields.resize(index + 1, (int64_t)VAL_NIL);
        }
        fields[index] = value;
    }
};

} // namespace Backend
} // namespace LM

#endif // REGISTER_VALUE_H
