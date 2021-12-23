workspace "yeop"
  startproject "yeop-editor"
  architecture "x64"
  
  configurations
  {
    "Debug",
    "Release"
  }
  
tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

-- Externals Dependencies
externals = {}
externals["sdl2"] = "external/SDL2"
externals["maclibs"] = "external/maclibs"
externals["spdlog"] = "external/spdlog"

project "yeop"
  location "yeop"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir(tdir)
  objdir(odir)

  files 
  {
    "%{prj.name}/include/**.h",
    "%{prj.name}/include/**.hpp",
    "%{prj.name}/include/**.cpp",
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  sysincludedirs
  {
    "%{prj.name}/include/yeop",
    "%{externals.sdl2}/include",
    "%{externals.spdlog}/include"
  }

  flags {"FatalWarnings"}

  filter {"system:windows", "configurations:*"}
    systemversion "latest"

    defines {"YEOP_PLATFORM_WINDOWS"}

  filter {"system:macosx", "configurations:*"}
    xcodebuildsettings
    {
      ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
      ["UseModernBuildSystem"] = "NO"
    }

    defines {"YEOP_PLATFORM_MACOSX"}

  filter {"system:linux", "configurations:*"}
    defines {"YEOP_PLATFORM_LINUX"}
    
    
  filter {"configurations:Debug"}
    defines {"YEOP_CONFIG_DEBUG"}
    runtime "DEBUG"
    symbols "on"

  filter {"configurations:Release"}
    defines {"YEOP_CONFIG_RELEASE"}
    runtime "RELEASE"
    symbols "off"
    optimize "on"

project "yeop-editor"
  location "yeop-editor"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"
  links "yeop"
  
  targetdir(tdir)
  objdir(odir)
  
  files 
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  sysincludedirs
  {
    "SDL2",
    "yeop/include",
    "%{externals.spdlog}/include",
  }

  flags {"FatalWarnings"}

  filter {"system:windows", "configurations:*"}
    systemversion "latest"

    defines {"YEOP_PLATFORM_WINDOWS"}

    libdirs{"%{externals.sdl2}/lib"}

    links
    {
      "SDL2"
    }

  filter {"system:macosx", "configurations:*"}
    xcodebuildsettings
    {
      ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
      ["UseModernBuildSystem"] = "NO"
    }

    defines {"YEOP_PLATFORM_MACOSX"}

    abspath = path.getabsolute("%{externals.maclibs}")
    linkoptions {"-F " .. abspath}
    
    links
    {
      "SDL2.framework"
    }

  filter {"system:linux", "configurations:*"}
    defines {"YEOP_PLATFORM_LINUX"}

    links
    {
      "SDL2"
    }
    
  filter {"configurations:Debug"}
    defines {"YEOP_CONFIG_DEBUG"}
    runtime "DEBUG"
    symbols "on"

  filter {"configurations:Release"}
    defines {"YEOP_CONFIG_RELEASE"}
    runtime "RELEASE"
    symbols "off"
    optimize "on"
