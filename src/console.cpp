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
void handleArgs(int count, char** arguments) {
    // First create an argument
    Argument arg(count, arguments);
    // Now create the datapak and handle arguments
    Datapak dat;
    // 0 args
    if (arg.size == 0) {
        LOG("Error: Too few arguments provided!");
    }
    // 1 arg
    else if (arg.size == 1) {
        // Help command
        if (arg.args[1] == "help") {
           LOG("Datapak is a CLI tool to package your files into a single file!");
        }
        else if(arg.args[1] == "new") {
            LOG("Warning: No name provided. Using default name file.datapak instead..");
            dat.load("file.datapak");
        }
        else if (arg.args[1] == "list") {
            LOG("Listing all files..");
            
        }
    }
}

int main(int argc, char** argv) {
    handleArgs(argc, argv);
}