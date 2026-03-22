#ifndef CONFIG_PARSER_HH
#define CONFIG_PARSER_HH

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

struct Dependency {
    std::string name;
    std::string version;
    std::string path;
    std::string git;
    std::string tag;
};

struct PackageMetadata {
    std::string name;
    std::string version;
    std::map<std::string, Dependency> dependencies;
};

class ConfigParser {
public:
    static PackageMetadata parse(const std::string& filename) {
        std::ifstream file(filename);
        PackageMetadata meta;
        if (!file.is_open()) return meta;

        std::string line;
        bool in_package_section = false;
        bool in_dependencies_section = false;
        while (std::getline(file, line)) {
            // Trim whitespace from start
            size_t first = line.find_first_not_of(" \t\r\n");
            if (first == std::string::npos) continue; // Skip empty or whitespace-only lines

            size_t last = line.find_last_not_of(" \t\r\n");
            line = line.substr(first, (last - first + 1));

            if (line.empty() || line[0] == '#') continue;

            if (line == "[package]") {
                in_package_section = true;
                in_dependencies_section = false;
                continue;
            } else if (line == "[dependencies]") {
                in_dependencies_section = true;
                in_package_section = false;
                continue;
            } else if (line[0] == '[') {
                in_package_section = false;
                in_dependencies_section = false;
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
            } else if (in_dependencies_section) {
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

                    Dependency dep;
                    dep.name = key;

                    // Handle inline table: utils = { path = "../utils" }
                    if (value.find('{') != std::string::npos) {
                        size_t start = value.find('{');
                        size_t end = value.find('}');
                        std::string inner = value.substr(start + 1, end - start - 1);

                        std::stringstream ss(inner);
                        std::string pair;
                        while (std::getline(ss, pair, ',')) {
                            size_t p_eq = pair.find('=');
                            if (p_eq != std::string::npos) {
                                std::string p_key = pair.substr(0, p_eq);
                                std::string p_val = pair.substr(p_eq + 1);

                                // Trim
                                p_key.erase(0, p_key.find_first_not_of(" \t"));
                                p_key.erase(p_key.find_last_not_of(" \t") + 1);
                                p_val.erase(0, p_val.find_first_not_of(" \t\""));
                                p_val.erase(p_val.find_last_not_of(" \t\"") + 1);

                                if (p_key == "path") dep.path = p_val;
                                else if (p_key == "version") dep.version = p_val;
                                else if (p_key == "git") dep.git = p_val;
                                else if (p_key == "tag") dep.tag = p_val;
                            }
                        }
                    } else {
                        // Simple version string: utils = "0.1.0"
                        size_t v_first = value.find_first_not_of(" \t\"");
                        size_t v_last = value.find_last_not_of(" \t\"");
                        if (v_first != std::string::npos) {
                            dep.version = value.substr(v_first, (v_last - v_first + 1));
                        }
                    }
                    meta.dependencies[key] = dep;
                }
            }
        }
        return meta;
    }
};

#endif
