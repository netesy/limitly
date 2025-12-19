#ifndef REGISTER_H
#define REGISTER_H

#include "../../lir/lir.hh"
#include <vector>
#include <string>
#include <variant>
#include <cstdint>

namespace Register {

// Register value type
using RegisterValue = std::variant<int64_t, double, bool, std::string, std::nullptr_t>;

class RegisterVM {
public:
    RegisterVM();
    
    // Main execution method
    void execute_function(const LIR::LIR_Function& function);
    
    // Register access
    inline const RegisterValue& get_register(LIR::Reg reg) const {
        return registers[reg];
    }
    
    inline void set_register(LIR::Reg reg, const RegisterValue& value) {
        registers[reg] = value;
    }
    
    void reset();
    std::string to_string(const RegisterValue& value) const;

private:
    std::vector<RegisterValue> registers;
    
    // Helper methods - all inlined for performance
    inline bool is_numeric(const RegisterValue& value) const {
        return std::holds_alternative<int64_t>(value) || 
               std::holds_alternative<double>(value);
    }
    
    inline int64_t to_int(const RegisterValue& value) const {
        if (std::holds_alternative<int64_t>(value)) return std::get<int64_t>(value);
        if (std::holds_alternative<double>(value)) return static_cast<int64_t>(std::get<double>(value));
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? 1 : 0;
        return 0;
    }
    
    inline double to_float(const RegisterValue& value) const {
        if (std::holds_alternative<double>(value)) return std::get<double>(value);
        if (std::holds_alternative<int64_t>(value)) return static_cast<double>(std::get<int64_t>(value));
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? 1.0 : 0.0;
        return 0.0;
    }
    
    inline bool to_bool(const RegisterValue& value) const {
        if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
        if (std::holds_alternative<int64_t>(value)) return std::get<int64_t>(value) != 0;
        if (std::holds_alternative<double>(value)) return std::get<double>(value) != 0.0;
        if (std::holds_alternative<std::string>(value)) return !std::get<std::string>(value).empty();
        return false;
    }
    

};

} // namespace Register

#endif // REGISTER_H