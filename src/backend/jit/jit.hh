#ifndef JIT_H
#define JIT_H

#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../../memory/memory.hh"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <chrono>  

namespace LM {
namespace Backend {
namespace JIT {
namespace Compiler {

// Compilation modes
enum class CompileMode {
    ToMemory,    // Keep in memory for immediate execution
    ToFile,      // Compile to object file
    ToExecutable // Compile to executable
};

// Compilation result
struct CompileResult {
    bool success;
    std::string error_message;
    
    // For memory compilation
    void* compiled_function;
    
    // For file compilation
    std::string output_file;
    
    CompileResult() : success(false), compiled_function(nullptr) {}
};

class JITBackend {
public:
    JITBackend();
    ~JITBackend();

    void process_function(const LIR::LIR_Function&);
    void compile_function(const LIR::LIR_Function&);
    CompileResult compile(CompileMode mode = CompileMode::ToMemory, const std::string& output_path = "");
    int execute_compiled_function(const std::vector<int>& args = {});
    void enable_optimizations(bool enable = true);
    void set_debug_mode(bool debug = true);

    struct Stats {
        size_t functions_compiled = 0;
        size_t instructions_compiled = 0;
        double compilation_time_ms = 0.0;
    };
    Stats get_stats() const;

private:
    bool m_optimizations_enabled;
    bool m_debug_mode;
    void* m_compiled_function;
    void* m_jit_result;
};

} // namespace Compiler
} // namespace JIT
} // namespace Backend
} // namespace LM

#endif // JIT_H
