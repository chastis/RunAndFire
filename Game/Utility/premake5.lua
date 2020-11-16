project "Utility"
    language "C++"
    cppdialect (CPPDIALECT)
    rtti (RTTI)
    targetdir (TARGET_DIR)
    objdir (OUTPUT_DIR .. "/%{prj.name}")
    kind "StaticLib"

    files { "**.hpp", "**.cpp" }

    includedirs
    {
        INCLUDE_PATHS.ROOT
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines { "NDEBUG", "RELEASE", "PUGIXML_NO_EXCEPTIONS"}
        optimize "On"
        runtime "Release"