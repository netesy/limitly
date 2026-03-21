#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

struct PackageMetadata {
    std::string name;
    std::string version;
};

class ConfigParser {
public:
    static PackageMetadata parse(const std::string& filename) {
        std::ifstream file(filename);
        PackageMetadata meta;
        if (!file.is_open()) return meta;

        std::string line;
        bool in_package_section = false;
        while (std::getline(file, line)) {
            // Trim whitespace from start
            size_t first = line.find_first_not_of(" \t\r\n");
            if (first == std::string::npos) continue; // Skip empty or whitespace-only lines

            size_t last = line.find_last_not_of(" \t\r\n");
            line = line.substr(first, (last - first + 1));

            if (line.empty() || line[0] == '#') continue;

            if (line == "[package]") {
                in_package_section = true;
                continue;
            } else if (line[0] == '[') {
                in_package_section = false;
                continue;
            }

            if (in_package_section) {
                size_t eq_pos = line.find('=');
                if (eq_pos != std::string::npos) {
                    std::string key = line.substr(0, eq_pos);
                    std::string value = line.substr(eq_pos + 1);

                    // Trim key
                    size_t k_first = key.find_first_not_of(" \t");
                    size_t k_last = key.find_last_not_of(" \t");
                    if (k_first != std::string::npos) {
                        key = key.substr(k_first, (k_last - k_first + 1));
                    }

                    // Trim value and remove quotes
                    size_t v_first = value.find_first_not_of(" \t\"");
                    size_t v_last = value.find_last_not_of(" \t\"");
                    if (v_first != std::string::npos) {
                        value = value.substr(v_first, (v_last - v_first + 1));
                    }

                    if (key == "name") meta.name = value;
                    else if (key == "version") meta.version = value;
                }
            }
        }
        return meta;
    }
};
