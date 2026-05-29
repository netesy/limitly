#ifndef LIMITLY_LIR_VERIFIER_H
#define LIMITLY_LIR_VERIFIER_H

#include "lir.hh"
#include <string>
#include <vector>
#include <unordered_set>

namespace LM {
namespace LIR {

class Verifier {
public:
    static bool verify(const LIR_Function& func, std::vector<std::string>& errors);

private:
    static bool verify_instruction(const LIR_Inst& inst, const LIR_Function& func, std::vector<std::string>& errors);
    static bool verify_control_flow(const LIR_Function& func, std::vector<std::string>& errors);
    static bool detect_infinite_loops(const LIR_Function& func, std::vector<std::string>& errors);
};

} // namespace LIR
} // namespace LM

#endif // LIMITLY_LIR_VERIFIER_H
