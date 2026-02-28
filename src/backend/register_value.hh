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

// Frame instance representation for VM execution
struct FrameInstance {
    std::string frame_type;                    // Frame type name
    std::unordered_map<std::string, std::variant<int64_t, uint64_t, double, bool, std::string, std::nullptr_t, FrameInstancePtr>> fields;  // Field values
    
    FrameInstance() = default;
    explicit FrameInstance(const std::string& type_name) : frame_type(type_name) {}
    
    // Get field value
    template<typename T>
    T getField(const std::string& field_name) const {
        auto it = fields.find(field_name);
        if (it == fields.end()) {
            throw std::runtime_error("Field not found: " + field_name);
        }
        return std::get<T>(it->second);
    }
    
    // Set field value
    template<typename T>
    void setField(const std::string& field_name, const T& value) {
        fields[field_name] = value;
    }
    
    // Check if field exists
    bool hasField(const std::string& field_name) const {
        return fields.find(field_name) != fields.end();
    }
};

// Register value type - now includes frame instances
using RegisterValue = std::variant<int64_t, uint64_t, double, bool, std::string, std::nullptr_t, FrameInstancePtr>;

} // namespace Backend
} // namespace LM

#endif // REGISTER_VALUE_H
