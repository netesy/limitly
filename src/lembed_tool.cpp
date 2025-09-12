#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "lembed.hh"

void printUsage(const char* prog) {
    std::cout << "lembed - embed generation utility\n";
    std::cout << "Usage:\n";
    std::cout << "  " << prog << " -list                    List generated embedded modules (if any)\n";
    std::cout << "  " << prog << " -embed-source <src> <name>  Generate embed from source file\n";
    std::cout << "      Optional: append ' -build' to invoke tools/make_embedded.bat/.sh to build a standalone interpreter with the embed.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string cmd = argv[1];
    if (cmd == "-list") {
        auto names = lembed::listEmbeddedNames();
        std::cout << "Builtin embedded modules:\n";
        for (auto &n : names) std::cout << "  " << n << "\n";
        return 0;
    }

    if (cmd == "-embed-source" && argc >= 4) {
        std::string srcPath = argv[2];
        std::string name = argv[3];
        bool doBuild = false;
        if (argc >= 5 && std::string(argv[4]) == "-build") doBuild = true;

        // Step 1: ensure we have a bytecode dump. Use the existing limitly CLI to emit bytecode.
        std::string bytecodeTmp = "build_temp.bytecode.txt";
        std::string genCmd = "bin\\limitly -bytecode \"" + srcPath + "\" > " + bytecodeTmp;
        std::cout << "Generating bytecode via: " << genCmd << "\n";
        int rc = std::system(genCmd.c_str());
        if (rc != 0) {
            std::cerr << "Failed to generate bytecode (ensure bin\\limitly exists and is buildable)." << std::endl;
            return 1;
        }

        // Step 2: run the python goembed converter to emit src/lembed_generated.cpp/.hh
        std::string pyCmd = "python tools\\goembed.py " + bytecodeTmp + " " + name + " src\\lembed_generated";
        std::cout << "Running generator: " << pyCmd << "\n";
        rc = std::system(pyCmd.c_str());
        if (rc != 0) {
            std::cerr << "goembed generation failed." << std::endl;
            return 1;
        }

        std::cout << "Generated src/lembed_generated.cpp and src/lembed_generated.hh\n";

        if (doBuild) {
#ifdef _WIN32
            std::string buildCmd = "tools\\make_embedded.bat " + name;
#else
            std::string buildCmd = "tools/make_embedded.sh " + name;
#endif
            std::cout << "Invoking: " << buildCmd << "\n";
            rc = std::system(buildCmd.c_str());
            if (rc != 0) {
                std::cerr << "Embedded build failed with exit code " << rc << "\n";
                return 1;
            }
        }

        return 0;
    }

    printUsage(argv[0]);
    return 1;
}
}
