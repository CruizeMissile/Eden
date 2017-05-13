-- scripting reference https://github.com/bkaradzic/genie/blob/master/docs/scripting-reference.md#table-of-contents
-- note on linking https://github.com/bkaradzic/GENie/issues/133
-- Paths
EDEN_DIR           = path.getabsolute("../../")
SOURCE_DIR         = EDEN_DIR  .. "/Eden"
ENGINE_SOURCE_DIR  = EDEN_DIR  .. "/Eden/Engine"
TESTS_SOURCE_DIR   = EDEN_DIR  .. "/Eden/Unittests"
DEPENDENCY_DIR     = EDEN_DIR  .. "/Resources" .. "/3rdparty"
BUILD_DIR          = EDEN_DIR  .. "/Build"
BUILD_INCLUDE_DIR  = EDEN_DIR  .. "/Build/Include"
OUTPUT_DIR         = BUILD_DIR .. "/Bin"
SOLTUION_DIR       = BUILD_DIR .. "/Project/" .. _ACTION

function setup_configuration(project_name)
    includedirs
    {
        ENGINE_SOURCE_DIR,
        DEPENDENCY_DIR .. "/include"
    }

    configuration {"Debug", "x32"}
        targetdir(OUTPUT_DIR .. "/" .. project_name  .. "/Debug/x32")
        libdirs
        {
            OUTPUT_DIR .. "/" .. project_name  .. "/Debug/x32",
            DEPENDENCY_DIR .. "/lib/Debug/x32/"
        }
    configuration {"Debug", "x64"}
        targetdir(OUTPUT_DIR .. "/" .. project_name  .. "/Debug/x64")
        libdirs
        {
            OUTPUT_DIR .. "/" .. project_name  .. "/Debug/x64",
            DEPENDENCY_DIR .. "/lib/Debug/x64/"
        }
    configuration {"Release", "x32"}
        targetdir(OUTPUT_DIR .. "/" .. project_name  .. "/Release/x32")
        libdirs
        {
            OUTPUT_DIR .. "/" .. project_name  .. "/Release/x32",
            DEPENDENCY_DIR .. "/lib/Release/x32/"
        }
    configuration {"Release", "x64"}
        targetdir(OUTPUT_DIR .. "/" .. project_name  .. "/Release/x64")
        libdirs
        {
            OUTPUT_DIR .. "/" .. project_name  .. "/Release/x64",
            DEPENDENCY_DIR .. "/lib/Release/x64/"
        }

    -- reset configuration
    configuration {}
end

function add_eden_engine_dependencies()
    links
    {
        "glfw3"
    }
end

--
-- Solution
--
solution "Eden"
    -- Configuration
    language "C++"
    configurations { "Debug", "Release", }
    platforms { "x32", "x64" }
    location(SOLTUION_DIR)
    startproject "UnitTests"

    flags { "FatalWarnings" }
    configuration { "Debug" }
        flags { "Symbols" }
    configuration { "Release" }
        flags { "NoBufferSecurityCheck", "OptimizeSpeed", }

	configuration { "gmake" }
		buildoptions { "-std=c++14" }

project "Eden"
    kind "StaticLib"

    files { ENGINE_SOURCE_DIR .. "/**"}
    vpaths { ["*"] = ENGINE_SOURCE_DIR }

    pchheader "Precompiled.h"
    pchsource (ENGINE_SOURCE_DIR .. "/Precompiled.cpp")

    setup_configuration("Eden")

    configuration { "vs*" }
        buildoptions
        {
            "/wd 4127", -- Disable 'Conditional expression is constant' for do {} while(0).
            "/wd 4201", -- Disable 'Nonstandard extension used: nameless struct/union'. Used for uniforms in the project.
            "/wd 4345", -- Disable 'An object of POD type constructed with an initializer of the form () will be default-initialized'. It's an obsolete warning.
            "/wd 4814", -- Disable 'in C++14 'constexpr' will not imply 'const'; consider explicitly specifying 'const'. Thanks I can handle that
            "/wd 4101", -- Disable  no 'object' file generated. Ok so this doesn't make sense when I am up to my eye balls in templates. Yes some branches will not actualy be hit.
        }

    configuration { "windows" }
        prebuildcommands { "xcopy /D /Y /S /i /q \"" .. ENGINE_SOURCE_DIR:gsub("%/", "\\") .. "\\*.h\" \"" .. BUILD_INCLUDE_DIR:gsub("%/", "\\") .. "\"" }

    configuration { "linux or macosx" }
        prebuildcommands { "mkdir -p \"" .. BUILD_INCLUDE_DIR .. "\"  && rsync -arm --include '*/' --include '*.h' --exclude '*' \"" .. ENGINE_SOURCE_DIR .. "\" \"" .. BUILD_INCLUDE_DIR .. "\""}

project "UnitTests"
    kind "ConsoleApp"

    includedirs
    {
        ENGINE_SOURCE_DIR,
        TESTS_SOURCE_DIR,
        DEPENDENCY_DIR .. "/tests",
    }

    files { TESTS_SOURCE_DIR .. "/**" }
    vpaths { ["*"] = TESTS_SOURCE_DIR }
    links { "Eden" }
    setup_configuration("UnitTests")

project "Sample"
    kind "ConsoleApp"

    includedirs
    {
        -- BUILD_INCLUDE_DIR, -- Change to this when this gets refactored into its own repo
        ENGINE_SOURCE_DIR,
        DEPENDENCY_DIR .. "/include"
    }

    files { SOURCE_DIR .. "/Sample/**" }
    vpaths { ["*"] = SOURCE_DIR .. "/Sample" }
    links { "Eden" }
    setup_configuration("Sample")
    add_eden_engine_dependencies()