#include "handlers.hh"
#include "resolver.hh"
#include "lock_system.hh"
#include <iostream>

int handle_update() {
    std::cout << "Updating dependencies...\n";
    std::vector<ResolvedDependency> deps = DependencyResolver::resolve(".");
    LockSystem::generate_lockfile(".", deps);
    std::cout << "Lockfile updated successfully.\n";
    return 0;
}
