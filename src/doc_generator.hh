#ifndef LYMAR_DOC_GENERATOR_HH
#define LYMAR_DOC_GENERATOR_HH

#include <string>
#include <vector>

namespace LM {

class DocGenerator {
public:
    enum class Format {
        Markdown,
        HTML
    };

    struct Options {
        Format format = Format::Markdown;
        std::string output_path;
        bool stdout_only = false;
        std::vector<std::string> target_files;
    };

    static int run(int argc, char** argv);
    static std::string generateMarkdown(const std::string& filepath, const std::string& source);
    static std::string generateHTML(const std::string& filepath, const std::string& source);
};

} // namespace LM

#endif // LYMAR_DOC_GENERATOR_HH
