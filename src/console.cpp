#include "datapak.hpp"
#include <iostream>
#include <sys/stat.h>

#define LOG(arg) std::cout << arg << std::endl
#define ERROR(arg) LOG(arg); exit(1)

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
    CMD_REMOVE, // Remove a file

    CMD_EXTRACT, // Extract all files stored in the datapak
    CMD_EXTRACT_FILE, // Extract a file from the datapak

    CMD_UNKNOWN, // Unknown command
};

// Enum to store path types
enum PathType {
    FILE_PATH = 0,
    DIR_PATH,
    UNKNOWN_PATH,
};

// Check if a given path leads to a file or a directory 
PathType getPathType(std::string& path) {
    struct stat buffer;
    if ( stat(path.c_str(), &buffer) == 0) {
        if( buffer.st_mode & S_IFDIR )
        {
            return DIR_PATH;
        }
        else if( buffer.st_mode & S_IFREG )
        {
            return FILE_PATH;
        }
        else
        {
           return UNKNOWN_PATH;
        }
    }
    else {
        return UNKNOWN_PATH;
    }
}

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
            #ifdef DEBUG
                LOG(args[x]);
            #endif
        }
        // Now get the command type
        if (size < 2) {
            ERROR("Error: Too few arguments provided!"); 
        }
        else {
            if (args[2] == "help") {
                cmdType = CMD_HELP;
            }
            else if (args[2] == "new") {
                cmdType = CMD_NEW;
            }
            else if (args[2] == "load") {
                cmdType = CMD_NEW;
            }
            else if (args[2] == "add") {
                if (size == 2) {
                    ERROR("Error: Nothing to add!");
                }
                else {
                    switch (getPathType(args[3])) {
                        case FILE_PATH: cmdType = CMD_ADD_FILE;
                        case DIR_PATH: cmdType = CMD_ADD_DIR;
                        default: break;
                    }
                }
            }
            else if (args[2] == "list") {
                cmdType = CMD_LIST;
            }
            else if (args[2] == "rename") {
                cmdType = CMD_RENAME;
            }
            else if (args[2] == "find") {
                cmdType = CMD_FIND;
            }
            else if (args[2] == "remove") {
                cmdType = CMD_REMOVE;
            }
            else if (args[2] == "extract") {
                cmdType = CMD_EXTRACT;
            }
            else {
                cmdType = CMD_UNKNOWN;
            }
        }
    }
};

// Handle the argument types
void handleArgs(int count, char** arguments) {
    // First create an argument
    Argument arg(count, arguments);
    // Now create the datapak and handle arguments
    Datapak dat;
    
}

int main(int argc, char** argv) {
    handleArgs(argc, argv);
}