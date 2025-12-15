#ifndef REGISTER_H
#define REGISTER_H

#include "../lir/lir.hh"
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>

namespace Register {

// Register value type for interpreter
using RegisterValue = std::variant<int64_t, double, bool, std::string, std::nullptr_t>;

class RegisterVM {
public:
    RegisterVM();
    
    // Main execution methods
    void execute_function(const LIR::LIR_Function& function);
    RegisterValue execute_instruction(const LIR::LIR_Inst& inst);
    
    // Register access
    const RegisterValue& get_register(LIR::Reg reg) const;
    void set_register(LIR::Reg reg, const RegisterValue& value);
    
    // Utility methods
    void reset();
    std::string register_value_to_string(const RegisterValue& value) const;

private:
    // Virtual registers (simplified - using fixed size for now)
    std::vector<RegisterValue> registers;
    
    // Instruction pointer
    size_t ip;
    
    // Helper methods for operations
    RegisterValue perform_binary_op(LIR::LIR_Op op, const RegisterValue& a, const RegisterValue& b);
    RegisterValue perform_unary_op(LIR::LIR_Op op, const RegisterValue& a);
    bool perform_comparison(LIR::LIR_Op op, const RegisterValue& a, const RegisterValue& b);
    
    // Type checking and conversion
    bool is_numeric(const RegisterValue& value) const;
    int64_t to_int(const RegisterValue& value) const;
    double to_float(const RegisterValue& value) const;
    bool to_bool(const RegisterValue& value) const;
    std::string to_string(const RegisterValue& value) const;
};

} // namespace Register

#endif // REGISTER_H
