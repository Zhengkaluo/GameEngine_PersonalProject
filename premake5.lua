-- premake5.lua
--[[project "HelloWorld"
   kind "ConsoleApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.h", "**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

value tokens
wks.name
wks.location -- (location where the workspace/solution is written, not the premake-wks.lua file)

prj.name
prj.location -- (location where the project is written, not the premake-prj.lua file)
prj.language
prj.group

cfg.longname
cfg.shortname
cfg.kind
cfg.architecture
cfg.platform
cfg.system
cfg.buildcfg
cfg.buildtarget -- (see [target], below)
cfg.linktarget -- (see [target], below)
cfg.objdir
--]]


workspace "KaluoEngine"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }
    startproject "SandBox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--include directories relative to the root folder (for now is for GLFW)
IncludeDir = {}
IncludeDir["GLFW"] = "KaluoEngine/vendor/GLFW/include"

include "KaluoEngine/vendor/GLFW"

project "KaluoEngine"
    location "KaluoEngine" --[KaluoEngine is the folder inside root directory] 
    kind "SharedLib" --indicate it is a dynamic library 
    language "C++"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}") --for bin
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") --for bin-int

    pchheader "Kaluopch.h"
    pchsource "KaluoEngine/src/Kaluopch.cpp"

    files
    { --define which files will be included
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On" --linking of library
        systemversion "latest"

        defines
        {
            "KALUO_PLATFORM_WINDOWS",
            "KALUO_BUILD_DLL"
        }

        postbuildcommands
        {
        --[[
            project "MyProject"
            postbuildcommands { "copy dependencies/*.lib bin" }
            postbuildmessage "Copying dependencies..."
        --]]
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
        }

    filter "configurations:Debug"
        defines "KALUO_DEBUG"
        buildoptions "/MDd"
        symbols "On"
    filter "configurations:Release"
        defines "KALUO_RELEASE"
        buildoptions "/MD"
        optimize "On"
     filter "configurations:Dist"
        defines "KALUO_DIST"
        buildoptions "/MD"
        optimize "On"
     

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}") --for bin
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") --for bin-int

    files
    { --define which files will be included
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "KaluoEngine/vendor/spdlog/include",
        "KaluoEngine/src"
    }

    links
    {
        "KaluoEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On" --linking of library
        systemversion "latest"

        defines
        {
            "KALUO_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "KALUO_DEBUG"
        buildoptions "/MDd"
        symbols "On"
    filter "configurations:Release"
        defines "KALUO_RELEASE"
        buildoptions "/MD"
        optimize "On"
     filter "configurations:Dist"
        defines "KALUO_DIST"
        buildoptions "/MD"
        optimize "On"
     