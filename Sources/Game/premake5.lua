project "RunAndFire"
  language "C++"
    cppdialect (CPPDIALECT)
    rtti (RTTI)
    targetdir (TARGET_DIR)
    objdir (OUTPUT_DIR .. "/%{prj.name}")

    files { "**.hpp", "**.cpp" }

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

    links
    {
        "opengl32",
        "freetype",
        "winmm",
        "gdi32",
        "flac",
        "vorbisenc",
        "vorbisfile",
        "vorbis",
        "ogg",
        "ws2_32"
    }

    links { "Utility", "Engine" }

    defines { "SFML_STATIC" }

    filter "configurations:Debug"
        kind "ConsoleApp"
        defines { "DEBUG" }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        kind "WindowedApp"
        defines { "NDEBUG", "RELEASE", "PUGIXML_NO_EXCEPTIONS"}
        optimize "On"
        runtime "Release"

        links
        {
            "sfml-main"
        }