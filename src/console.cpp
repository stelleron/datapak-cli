#include "datapak.hpp"
#include "logger.hpp"
#include <sys/stat.h>

#define GET_DATAPAK_NAME(x) const char* dName = arg.argArray[x].c_str()

struct Argument {
    std::vector<std::string> argArray;
    Argument(int count, char** args) {
        if (count < 2) {
            ERROR("Error: Too few arguments passed!");
        }
        else {
            argArray.resize(count - 1);
            for (int x = 1; x < count; x++) {
                argArray[x - 1] = args[x];
                INFO("{0}", argArray[x - 1]);
            }
        }
    }
};

void exploreDir(const char* dirname, std::vector<std::string> *buffer) {
    // Explore the directory recursively
}

void handleArgs(int argc, char** argv, Datapak* dat) {
    // Store all necessary args
    Argument arg(argc, argv);
    // Now handle them
    if (arg.argArray[0] == "help") {
        INFO("Datapak CLI is a command-line interface for creating, packaging, modifying and extracting .datapak(extension not needed) files!\n Current Version: 1.0.0");
    }
    else if (arg.argArray[0] == "new") {
        if (arg.argArray.size() == 1) {
            WARN("No name provided for the Datapak! Creating one with a default name instead (file.datapak)!");
            dat = new Datapak("file.datapak");
        }
        else {
            INFO("Creating a datapak with the given name: {0}", arg.argArray[1].c_str());
            dat = new Datapak(arg.argArray[1].c_str());
        }
    }
    else if (arg.argArray[0] == "load") {
        ERROR("Currently not supporting live editing mode!");
    }
    else if (arg.argArray[0] == "add_dir") {
        GET_DATAPAK_NAME(1);
        // Recursively find all files in the directory
        std::vector<std::string> filenameBuffer;
        exploreDir(arg.argArray[2].c_str(), &filenameBuffer);
    }
}

int main(int argc, char** argv) {
    // First initialise the logger
    Logger::init();
    // Then handle the arguments and create the datapak
    Datapak* dat;
    handleArgs(argc, argv, dat);
}