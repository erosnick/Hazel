workspace "Hazel"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Shipping"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "modules/GLFW/include"
IncludeDir["Glad"] = "modules/Glad/include"
IncludeDir["ImGui"] = "modules/imgui"

include "modules/GLFW"
include "modules/Glad"
include "modules/ImGui"

project "Hazel"
        location "Hazel"
        kind "SharedLib"

        language "C++"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }

        includedirs
        {
            "modules/spdlog/include",
            "Hazel/src",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.ImGui}"
        }

        links
        {
            "GLFW",
            "Glad",
            "ImGui",
            "opengl32.lib"
        }

        disablewarnings { "4251", "4566" }

        pchheader "HazelPCH.h"
        pchsource "%{prj.name}/src/HazelPCH.cpp"

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "Off"
            systemversion "latest"

            defines
            {
                "HAZEL_EXPORTS",
                "HAZEL_WINDOWS_PLATFORM"
            }

            postbuildcommands
            {
                {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
            }

        filter "configurations:Debug"
            defines "HAZLE_DEBUG;HAZEL_ENABLE_ASSERTS"
            symbols "On"

        filter "configurations:Release"
            defines "HAZEL_RELEASE"
            optimize "On"

        filter "configurations:Shipping"
            defines "HAZEL_SHIPPING"
            optimize "On"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"

        language "C++"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }

        includedirs
        {
            "modules/spdlog/include",
            "Hazel/src"
        }

        links
        {
            "Hazel"
        }

        disablewarnings { "4251", "4566" }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "Off"
            systemversion "latest"

        defines
        {
            "HAZEL_WINDOWS_PLATFORM"
        }

        filter "configurations:Debug"
            defines "HAZLE_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "HAZEL_RELEASE"
            optimize "On"

        filter "configurations:Shipping"
            defines "HAZEL_SHIPPING"
            optimize "On"