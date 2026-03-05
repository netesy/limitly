#ifndef REGISTER_VALUE_H
#define REGISTER_VALUE_H

#include <variant>
#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>

namespace LM {
namespace Backend {

// Forward declaration
struct FrameInstance;
using FrameInstancePtr = std::shared_ptr<FrameInstance>;

// Register value type - now includes frame instances
using RegisterValue = std::variant<int64_t, uint64_t, double, bool, std::string, std::nullptr_t, std::shared_ptr<struct FrameInstance>>;

// Frame instance representation for VM execution
struct FrameInstance {
    std::string frame_type;                    // Frame type name
    std::vector<RegisterValue> fields;         // Field values (indexed)
    
    FrameInstance() = default;
    explicit FrameInstance(const std::string& type_name) : frame_type(type_name) {}
    explicit FrameInstance(const std::string& type_name, size_t field_count)
        : frame_type(type_name), fields(field_count, nullptr) {}
    
    // Get field value
    const RegisterValue& getField(size_t index) const {
        if (index >= fields.size()) {
            throw std::runtime_error("Field index out of bounds: " + std::to_string(index));
        }
        return fields[index];
    }
    
    // Set field value
    void setField(size_t index, const RegisterValue& value) {
        if (index >= fields.size()) {
            fields.resize(index + 1, nullptr);
        }
        fields[index] = value;
    }
};

using FrameInstancePtr = std::shared_ptr<FrameInstance>;

} // namespace Backend
} // namespace LM

#endif // REGISTER_VALUE_H
