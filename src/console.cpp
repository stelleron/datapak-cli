#include "datapak.hpp"
#include <iostream>
#define LOG(arg) std::cout << arg << std::endl

// Enum to handle command types
enum CommandType {
    CMD_HELP, // Print a HELP message

    CMD_NEW, // Create a new datapak
    CMD_LOAD, // Load a given datapak and enter live input mode

    CMD_ADD_DIR, // Add a given directory to the datapak
    CMD_ADD_FILE, // Add a file to the datapak

    CMD_LIST, // List all files stored inside the datapak
    CMD_FIND, // Find a file under the given alias
    CMD_RENAME, // Rename a file with a new alias

    CMD_EXTRACT, // Extract all files stored in the datapak
    CMD_EXTRACT_FILE, // Extract a file from the datapak
};

// Struct to store an argument
struct Argument {
    int size;
    CommandType cmdType;
    std::vector<std::string> args;
    Argument(int count, char** arguments) {
        size = count - 1;
        args.resize(size);
        for (int x = 1; x < count; x++) {
            args[x] = arguments[x];
            std::cout << args[x] << std::endl;
        }
    }
};

// Handle the argument types
Argument handleArgs(int count, char** arguments) {
    // First create an argument
    Argument arg(count, arguments);
    // Now handle them
    if (arg.size == 0) {
        LOG("Datpak: Too few arguments provided!");
    }
    else if (arg.size == 1) {
        if (arg.args[1] == "help") {
           LOG("Datapak is a CLI tool to package your files into a single file!");
        }
    }
    return arg;
}

int main(int argc, char** argv) {
    Argument arg = handleArgs(argc, argv);
}