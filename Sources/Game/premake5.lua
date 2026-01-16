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
        "openal32",
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

    filter "configurations:Release"
        DATA_PATH = "\"Data\""

    filter "configurations:Debug"
        kind "ConsoleApp"
        defines { "DEBUG", "WORKING_DIRECTORY=".."\"%{wks.location}/../Data\"", "PROFILE_ENABLED" }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        kind "WindowedApp"
        defines { "NDEBUG", "RELEASE", "PUGIXML_NO_EXCEPTIONS",  "WORKING_DIRECTORY=".."\"%{wks.location}/../Data\"" }
        optimize "On"
        runtime "Release"

        links
        {
            "sfml-main"
        }

    filter "configurations:Dist"
        kind "WindowedApp"
        defines { "NDEBUG", "DIST", "PUGIXML_NO_EXCEPTIONS", "WORKING_DIRECTORY=".."\"Data\"" }
        optimize "On"
        runtime "Release"

        links
        {
            "sfml-main"
        }