#ifndef LYMAR_LINTER_HH
#define LYMAR_LINTER_HH

#include <string>
#include <vector>
#include <memory>

namespace LM {

struct LintDiagnostic {
    std::string file;
    int line = 0;
    int column = 0;
    std::string severity = "warning"; // "warning" or "error"
    std::string rule;
    std::string message;
    std::string help;
};

class Linter {
public:
    struct Options {
        bool deny_warnings = false;
        bool json_output = false;
        bool no_color = false;
        bool verbose = false;
        std::vector<std::string> target_paths;
    };

    static int run(int argc, char** argv);
    static std::vector<LintDiagnostic> lintFile(const std::string& filepath, const Options& opts);
    static std::vector<LintDiagnostic> lintSource(const std::string& filename, const std::string& source, const Options& opts);
};

} // namespace LM

#endif // LYMAR_LINTER_HH
