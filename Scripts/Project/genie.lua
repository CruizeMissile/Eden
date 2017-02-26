-- scripting reference https://github.com/bkaradzic/genie/blob/master/docs/scripting-reference.md#table-of-contents
-- Settngs
EDEN_DIR           = path.getabsolute("../../")
SOURCE_DIR         = EDEN_DIR .. "/Eden"
ENGINE_SOURCE_DIR  = EDEN_DIR .. "/Eden/Engine"
TESTS_SOURCE_DIR   = EDEN_DIR .. "/Eden/Unittests"
DEPENDENCY_DIR     = EDEN_DIR .. "/Resources" .. "/3rdparty"
BUILD_DIR          = EDEN_DIR .. "/Build"
BUILD_INCLUDE_DIR  = EDEN_DIR .. "/Build/Include"
OUTPUT_DIR         = BUILD_DIR ..  "/Bin"
SOLTUION_DIR       = BUILD_DIR ..  "/Project/" .. _ACTION

function get_targetdir(project_name)
	configuration {"Debug", "x32"}
		targetdir(OUTPUT_DIR .. "/" .. project_name  .. "/Debug-x32")
		libdirs { OUTPUT_DIR .. "/" .. project_name  .. "/Debug-x32" }
	configuration {"Debug", "x64"}
		targetdir(OUTPUT_DIR .. "/" .. project_name  .. "/Debug-x64")
		libdirs { OUTPUT_DIR .. "/" .. project_name  .. "/Debug-x64" }
	configuration {"Release", "x32"}
		targetdir(OUTPUT_DIR .. "/" .. project_name  .. "/Release-x32")
		libdirs { OUTPUT_DIR .. "/" .. project_name  .. "/Release-x32" }
	configuration {"Release", "x64"}
		targetdir(OUTPUT_DIR .. "/" .. project_name  .. "/Release-x64")
		libdirs { OUTPUT_DIR .. "/" .. project_name  .. "/Release-x64" }
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

project "Eden"
    kind "StaticLib"

    includedirs
    {
    	ENGINE_SOURCE_DIR,
    	DEPENDENCY_DIR .. "/include"	
	}

	files { ENGINE_SOURCE_DIR .. "/**"}
	vpaths { ["*"] = ENGINE_SOURCE_DIR }

	pchheader "Precompiled.h" 
	pchsource (ENGINE_SOURCE_DIR .. "/Precompiled.cpp")

	-- links {}

    get_targetdir("Eden")

	configuration { "vs*" }
		buildoptions
		{
			"/wd 4127", -- Disable 'Conditional expression is constant' for do {} while(0).
            "/wd 4201", -- Disable 'Nonstandard extension used: nameless struct/union'. Used for uniforms in the project.
            "/wd 4345", -- Disable 'An object of POD type constructed with an initializer of the form () will be default-initialized'. It's an obsolete warning.
		}

	configuration "windows"
		prebuildcommands
		{
			"xcopy /D /Y /S /i /q \"" .. ENGINE_SOURCE_DIR:gsub("%/", "\\") .. "\\*.h\" \"" .. BUILD_INCLUDE_DIR:gsub("%/", "\\") .. "\""
		}

project "UnitTests"
	kind "ConsoleApp"

    includedirs
    {
		ENGINE_SOURCE_DIR,
    	TESTS_SOURCE_DIR,
    	DEPENDENCY_DIR .. "/unittests",
	}

	files { TESTS_SOURCE_DIR .. "/**" }
	vpaths { ["*"] = TESTS_SOURCE_DIR }
	links {	"Eden" }
	-- vpaths { ["*"] = "Eden/Unittests" }
    get_targetdir("UnitTests")

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
	-- vpaths { ["*"] = "Eden/Sample" }
    get_targetdir("Sample")
