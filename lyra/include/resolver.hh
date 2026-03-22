#ifndef RESOLVER_HH
#define RESOLVER_HH

#include "config_parser.hh"
#include "semver.hh"
#include "fetch_system.hh"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

struct ResolvedDependency {
    std::string name;
    std::string version;
    std::string path;
};

class DependencyResolver {
public:
    static std::vector<ResolvedDependency> resolve(const std::string& project_root) {
        std::vector<ResolvedDependency> resolved;
        std::set<std::string> visiting;
        std::set<std::string> visited;

        resolve_recursive(project_root, resolved, visiting, visited);

        return resolved;
    }

private:
    static void resolve_recursive(const std::string& current_path,
                                std::vector<ResolvedDependency>& resolved,
                                std::set<std::string>& visiting,
                                std::set<std::string>& visited) {

        std::string abs_path = fs::absolute(current_path).string();

        if (visiting.count(abs_path)) {
            std::cerr << "error: circular dependency detected involving '" << abs_path << "'\n";
            exit(1);
        }

        if (visited.count(abs_path)) return;

        visiting.insert(abs_path);

        PackageMetadata meta = ConfigParser::parse(current_path + "/lymar.toml");
        if (meta.name.empty()) {
            visiting.erase(abs_path);
            visited.insert(abs_path);
            return;
        }

        for (auto const& [name, dep] : meta.dependencies) {
            std::string dep_path;
            if (!dep.path.empty()) {
                dep_path = (fs::path(current_path) / dep.path).string();
            } else if (!dep.git.empty()) {
                dep_path = FetchSystem::fetch_git(name, dep.git, dep.tag);
                if (dep_path.empty()) {
                    std::cerr << "error: failed to fetch git dependency '" << name << "'\n";
                    exit(1);
                }
            }

            if (!dep_path.empty()) {
                resolve_recursive(dep_path, resolved, visiting, visited);

                PackageMetadata dep_meta = ConfigParser::parse(dep_path + "/lymar.toml");
                if (!dep_meta.version.empty() && !dep.version.empty()) {
                    if (!Semver::satisfies(dep_meta.version, dep.version)) {
                        std::cerr << "error: dependency version mismatch for '" << name << "'. "
                                  << "Required " << dep.version << ", found " << dep_meta.version << "\n";
                        exit(1);
                    }
                }

                ResolvedDependency rd;
                rd.name = name;
                rd.version = dep_meta.version;
                rd.path = fs::absolute(dep_path).string();

                // Avoid duplicates in resolved list
                bool exists = false;
                for (const auto& r : resolved) {
                    if (r.path == rd.path) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    resolved.push_back(rd);
                }
            }
        }

        visiting.erase(abs_path);
        visited.insert(abs_path);
    }
};

#endif
