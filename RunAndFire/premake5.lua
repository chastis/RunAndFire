project "RunAndFire"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir (TARGET_DIR)
   objdir (OUTPUT_DIR .. "/%{prj.name}")

   files { "**.hpp", "**.cpp" }

   includedirs {
      INCLUDE_PATHS.SFML
   }
   libdirs {
      TARGET_DIR
   }

   links {
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

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      runtime "Debug"

      links {    
         "sfml-graphics-d",
         "sfml-window-d",
         "sfml-system-d",
         "sfml-audio-d",
         "sfml-network-d"
      }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      runtime "Release"
      links {    
         "sfml-graphics",
         "sfml-window",
         "sfml-system",
         "sfml-audio",
         "sfml-network"
      }