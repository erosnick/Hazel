workspace "Hazel"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Shipping"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
            "modules/spdlog/include"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "Off"
            systemversion "10.0.18362.0"

            defines
            {
                "HAZEL_EXPORTS"
            }

            postbuildcommands
            {
                {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
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

        filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "10.0.18362.0"

        defines
        {
            
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