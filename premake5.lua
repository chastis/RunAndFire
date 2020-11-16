workspace "RunAndFire"
    configurations { "Debug", "Release" }
    architecture "x64"
    startproject "RunAndFire"
    platforms { "Win64" }

    flags { "MultiProcessorCompile" , "FatalWarnings", "NoPCH"}

    CPPDIALECT = "C++17"
    RTTI = "Off"

    TARGET_DIR = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"
    OUTPUT_DIR = "%{wks.location}/bin/obj/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"

    INCLUDE_PATHS = 
    {
        SFML = "%{wks.location}/Game/SFML/Sources/include",
        ROOT = "%{wks.location}/Game"
    }

    LIB_PATHS = 
    {
        SFML = "%{wks.location}/Game/SFML/Build/lib/%{cfg.buildcfg}",
        SFML_DIST = "%{wks.location}/Game/SFML/build/lib/Release"
    }

    filter "action:vs*"
        LIB_PATHS.SFML_EXTLIB = "%{wks.location}/Game/SFML/Sources/extlibs/libs-msvc-universal/x64"
        buildoptions {"/Zc:__cplusplus"}

    filter "system:windows"
        systemversion "latest"

   include "Game/RunAndFire"
   include "Game/Utility"
   