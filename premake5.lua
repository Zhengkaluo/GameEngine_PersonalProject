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

--include directories relative to the root folder (for now is for GLFW)(also Glad)
IncludeDir = {}
IncludeDir["GLFW"] = "KaluoEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "KaluoEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "KaluoEngine/vendor/imgui"
IncludeDir["glm"] = "KaluoEngine/vendor/glm"
IncludeDir["stb_image"] = "KaluoEngine/vendor/stb_image"


group "Dependencies"
    include "KaluoEngine/vendor/GLFW"
    include "KaluoEngine/vendor/Glad"
    include "KaluoEngine/vendor/imgui"
group ""

project "KaluoEngine"
    location "KaluoEngine" --[KaluoEngine is the folder inside root directory] 
    --kind "SharedLib" --indicate it is a dynamic library 
    kind "StaticLib"
    language "C++"
    --staticruntime "off"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}") --for bin
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") --for bin-int

    pchheader "Kaluopch.h"
    pchsource "KaluoEngine/src/Kaluopch.cpp"

    files
    { --define which files will be included
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        --cppdialect "C++17"
        --staticruntime "On" --linking of library
        systemversion "latest"

        defines
        {
            "KALUO_PLATFORM_WINDOWS",
            "KALUO_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        -- postbuildcommands
        -- {
        -- --[[
        --     project "MyProject"
        --     postbuildcommands { "copy dependencies/*.lib bin" }
        --     postbuildmessage "Copying dependencies..."
        -- --]]
        --     ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/SandBox/\"")
        -- }

    filter "configurations:Debug"
        defines "KALUO_DEBUG"
        runtime "Debug"
        --buildoptions "/MDd"
        symbols "on"
    filter "configurations:Release"
        defines "KALUO_RELEASE"
        runtime "Release"
        --buildoptions "/MD"
        optimize "on"
     filter "configurations:Dist"
        defines "KALUO_DIST"
        --buildoptions "/MD"
        runtime "Release"
        optimize "on"
     

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "KaluoEngine/src",
        "KaluoEngine/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "KaluoEngine"
    }

    filter "system:windows"
        --cppdialect "C++17"
        --staticruntime "On" --linking of library
        systemversion "latest"

        defines
        {
            "KALUO_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "KALUO_DEBUG"
        runtime "Debug"
        --buildoptions "/MDd"
        symbols "on"
    filter "configurations:Release"
        defines "KALUO_RELEASE"
        --buildoptions "/MD"
        runtime "Release"
        optimize "on"
     filter "configurations:Dist"
        defines "KALUO_DIST"
        --buildoptions "/MD"
        runtime "Release"
        optimize "on"
     