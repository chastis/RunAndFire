project "Engine"
    location ""
    language "C++"
    cppdialect (CPPDIALECT)
    rtti (RTTI)
    targetdir (TARGET_DIR)
    objdir (OUTPUT_DIR .. "/%{prj.name}")
    kind "StaticLib"

    files { "**.hpp", "**.h", "**.cpp" }

    includedirs
    {
        INCLUDE_PATHS.ROOT,
        INCLUDE_PATHS.SFML
    }

    libdirs
    {
        LIB_PATHS.SFML,
        LIB_PATHS.SFML_EXTLIB
    }

    defines { "SFML_STATIC" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        runtime "Debug"

        links 
        {
            "sfml-graphics-s-d",
            "sfml-window-s-d",
            "sfml-system-s-d",
            "sfml-audio-s-d"
        }

    filter "configurations:Release"
        defines { "NDEBUG", "RELEASE" }
        optimize "On"
        runtime "Release"

        links
        {
            "sfml-graphics-s",
            "sfml-window-s",
            "sfml-system-s",
            "sfml-audio-s",
        }