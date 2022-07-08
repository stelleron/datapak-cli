#include "datapak.hpp"
#include "logger.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

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
            }
        }
    }
};

// Enum to store path types
enum PathType {
    FILE_PATH = 0,
    DIR_PATH,
    UNKNOWN_PATH,
};

// Check if a given path leads to a file or a directory 
inline PathType getPathType(const char* path) {
    struct stat buffer;
    stat(path, &buffer);
    if (buffer.st_mode & S_IFREG ) 
        return FILE_PATH;
    else if (buffer.st_mode & S_IFDIR )
        return DIR_PATH;
    else
        return UNKNOWN_PATH;
}

// Load a file from the given filename(assume validation) 
inline std::string loadFile(const std::string& fPath) {
    std::ifstream fileStream;
    fileStream.open(fPath, std::ios::in);
    std::stringstream buffer;
    buffer << fileStream.rdbuf() << '\0';
    return buffer.str();
}

void exploreDir(std::string& dirname, std::vector<std::string> *buffer, std::string& rootpath) {
    // Explore the directory recursively
    if (getPathType(dirname.c_str()) == DIR_PATH) {
        // Now loop through the folder
        for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
            if (getPathType(entry.path().c_str()) == FILE_PATH) {
                buffer->push_back(entry.path().c_str());
            }
            else if (getPathType(entry.path().c_str()) == DIR_PATH) {
                std::string newRootPath = rootpath + dirname;
                std::string dirPath = entry.path().string();
                exploreDir(dirPath, buffer, newRootPath);
            }
        }
    }
    else {
        ERROR("Error: Given invalid path! Path must be an existing directory");
    }
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
        std::string rootpath = "";
        std::vector<std::string> filenameBuffer;
        exploreDir(arg.argArray[2], &filenameBuffer, rootpath);
        INFO("");
        for (int x = 0; x < filenameBuffer.size(); x++) {
            INFO("{0}", filenameBuffer[x].c_str());
        }
        // Now add them all to the datapak   
        dat->load(dName);
        INFO("Found {0} files. Reading them all..", filenameBuffer.size());
        std::string fileSrc;
        for (int x = 0; x < filenameBuffer.size(); x++) {
            fileSrc = loadFile(filenameBuffer[x]);
            dat->write(filenameBuffer[x].c_str(), fileSrc);
        }

    }
    else if (arg.argArray[0] == "add_file") {
        GET_DATAPAK_NAME(1);
        // Check if the file being added is actually a file
        if (getPathType(arg.argArray[2].c_str()) != FILE_PATH) {
            ERROR("Error: Path given is not to a file!");
        }
        else {
            // If no additional alias is given
            if (arg.argArray.size() == 3) {
                // Load and add the file source to it
                dat->load(dName);
                std::string fileSrc = loadFile(arg.argArray[2].c_str());
                dat->write(arg.argArray[2].c_str(), fileSrc);
            }
            else if (arg.argArray.size() == 4) {
                dat->load(dName);
                std::string fileSrc = loadFile(arg.argArray[2].c_str());
                dat->write(arg.argArray[3].c_str(), fileSrc);
            }
        }
    }
    else if (arg.argArray[0] == "list") {
       GET_DATAPAK_NAME(1);
       dat->load(dName);
       INFO("The given datapak is home to {0} files. Listing them all: \n", dat->getNumChunks());
       dat->list(); 
       INFO("\n");
    }
    else if (arg.argArray[0] == "rename") {
        GET_DATAPAK_NAME(1);
        dat->load(dName);
        dat->rename(arg.argArray[2].c_str(), arg.argArray[3].c_str());
    }
    else if (arg.argArray[0] == "remove") {
        GET_DATAPAK_NAME(1);
        dat->load(dName);
        dat->remove(arg.argArray[2].c_str());
    }
    else if (arg.argArray[0] == "extract") {
        GET_DATAPAK_NAME(1);
        dat->load(dName);
        // Check if 2 or 3 arguments are given
        if (arg.argArray.size() == 3) {
            std::ofstream nFile;
            nFile.open(arg.argArray[2], std::ios::out);
            std::string data = dat->read(arg.argArray[2].c_str());
            nFile.write(data.c_str(), data.size());
        }
        else {
            ERROR("Error: Provided invalid number of call arguments!");
        }
    }
    else {
        ERROR("Error: Provided invalid call argument! Type \"datapak help\" to find a list of valid arguments");
    }
}

int main(int argc, char** argv) {
    // First initialise the logger
    Logger::init();
    // Then handle the arguments and create the datapak
    Datapak* dat = new Datapak();
    handleArgs(argc, argv, dat);
    delete dat;
}