# Datapak CLI: A command-line interface for creating, packaging, modifying and extracting .datapak files
Datapak CLI is a tool for building and editing Datapaks, a simple to use file compression format that can be intergrated into C++ with the library here: `https://github.com/stelleron/datapak`. 

## Setup
Download the source file from the GitHub repository. The Datapak CLI already comes packaged with all dependencies - you just have to build it on your native platform. The Datapak CLI is also included with a premake5.lua file to build it, as well as the Makefiles.

If you wish to use the Makefiles, just install GNU Make on your computer.  Then, use the terminal to open the project directory and simply just type `make`.

For using the premake5.lua version, download Premake from [here](https://premake.github.io/) and follow setup instructions. Then, use Premake to generate whatever project type you wish using `premake5 (enter your build type here)` and build the project.

## Commands 
`help`: Get information on the Datapak CLI and it's commands.
`new`: Create a new datapak with a default name (file.datapak).
`new [datapak]`: Create a new datapak with the given filename.
`load [datapak]`: Load a datapak and enter live editing mode.
`add_dir [datapak] [dir]`: Add all files in a given directory to the datapak. The file aliases are determined by their path from the given root directory.
`add_file [datapak] [file]`: Add a given file to the datapak.
`add_file [datapak] [file] [alias]`: Add a given file to the datapak under a new alias.
`list [datapak]`: List all file aliases inside a datapak.
`find [datapak] [alias]`: Check whether a file exists in the datapak by its alias.
`rename [datapak] [alias] [nalias]`: Rename a file in a given datapak to a new name.
`remove [datapak] [alias]`: Remove a file under the given name in a datapak.
`extract [datapak]`: Extract the datapak into a file with the same name as the datapak.
`extract [datapak] [alias]`: Extract a file under the given alias.

### Live Editing Mode (currently not supported)
Allows you to interface with the Datapak CLI without needing to type its name each time you call a command. Additionally comes with a `close` command to close the Datapak CLI once you're done.

## License
The Datapak CLI is open-source and uses the MIT license. Check LICENSE to read more about the terms of usage.

