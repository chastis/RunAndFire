workspace "RunAndFire"
    configurations { "Debug", "Release" }
    architecture "x64"
    startproject "RunAndFire"
    platforms { "Win64" }

    flags { "MultiProcessorCompile" , "FatalWarnings", "NoPCH"}

    CPPDIALECT = "C++latest"
    RTTI = "Off"

    TARGET_DIR = "%{wks.location}/../bin/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"
    OUTPUT_DIR = "%{wks.location}/../bin/obj/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"

    INCLUDE_PATHS = 
    {
        SFML = "%{wks.location}/SFML/Sources/include",
        ROOT = "%{wks.location}"
    }

    LIB_PATHS = 
    {
        SFML = "%{wks.location}/SFML/Build/lib/%{cfg.buildcfg}",
        SFML_DIST = "%{wks.location}/SFML/Build/lib/Release"
    }

    filter "action:vs*"
        LIB_PATHS.SFML_EXTLIB = "%{wks.location}/SFML/Sources/extlibs/libs-msvc-universal/x64"
        buildoptions {"/Zc:__cplusplus"}
    
    filter "system:windows"
        systemversion "latest"
    
    postbuildcommands {
        "{COPY} %{wks.location}../Data " .. TARGET_DIR .. "/Data",
    }

    include "Engine"
    include "Utility"
    include "Game"