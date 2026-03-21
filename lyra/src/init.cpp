#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int handle_init() {
    std::string project_name;
    // Default name is current directory name
    project_name = fs::current_path().filename().string();

    std::cout << "Initializing project '" << project_name << "'...\n";

    // Create luminar.toml
    std::ofstream config_file("luminar.toml");
    if (!config_file.is_open()) {
        std::cerr << "error: could not create luminar.toml\n";
        return 1;
    }
    config_file << "[package]\n";
    config_file << "name = \"" << project_name << "\"\n";
    config_file << "version = \"0.1.0\"\n";
    config_file.close();

    // Create src directory
    fs::create_directory("src");

    // Create src/main.lm
    std::ofstream main_file("src/main.lm");
    if (!main_file.is_open()) {
        std::cerr << "error: could not create src/main.lm\n";
        return 1;
    }
    main_file << "// Main entry point for " << project_name << "\n";
    main_file << "print(\"Hello, Luminar!\");\n";
    main_file.close();

    std::cout << "Project initialized successfully.\n";
    return 0;
}
