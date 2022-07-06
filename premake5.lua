-- premake5.lua
workspace "DataPak"
    architecture "x64"
    configurations {"Debug", "Release"}

project "datapak-sys"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/"

    files {"datapak/datapak.cpp"}
    includedirs {"external/"}
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "datapak"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/"

    files {"src/**.cpp"}
    includedirs {"datapak/", "external/"}
    libdirs {"external/"}
    links {"datapak-sys", "spdlog"}

    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"