-- premake4.lua
solution "led"
   configurations { "Debug", "Release" }

   project "led"
      kind "ConsoleApp"
      language "C++"
      targetdir "bin/"
      links { "wiringPi", "pthread" }
      buildoptions { "-std=c++11" }
   
   
      files { "**.h", "**.c", "**.hpp", "**.cpp" }
   
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-Wall" }
   
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

   
