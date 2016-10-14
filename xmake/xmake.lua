


local name = "LightInkLua"

local output = g_output

local prefixInclude = "../include/"
local prefixSrc = "../src/"

set_project(name)
set_version("0.0.1")

function set_mode_config(name)
	if is_mode("debug") then
		if is_plat("windows") then
			-- enable some checkers
			add_cxflags("-Gs", "-RTC1") 

			-- link libcmtd.lib
			add_cxflags("-MDd") 
			
			add_cxflags("-Zi", "-Fd$(buildir)\\" .. name .. ".pdb")
			add_ldflags("-pdb:$(buildir)\\" .. name .. ".pdb")
			add_arflags("-pdb:$(buildir)\\" .. name .. ".pdb")
			add_defines("_DEBUG=1")
		else
			-- enable the debug symbols
			set_symbols("debug")
		end
		add_defines("Debug")
		-- disable optimization
		set_optimize("none")
	elseif is_mode("release") then
		  -- set the symbols visibility: hidden
		set_symbols("hidden")

		-- enable fastest optimization
		set_optimize("fastest")

		-- strip all symbols
		set_strip("all")
		if is_plat("windows") then
			-- link libcmt.lib
			add_cxflags("-MD") 
		else
		
		end
	
	end
	
	if is_plat("windows") then
		add_defines("_WINDOWS", "WINDOWS", "_WIN32", "WIN32")
	end
	
	--set_languages("c99")
	
	add_defines("LIGHTINK_AS_DLL", "LIGHTINK_EXPORTS")
	
end


-- add target
target(name)
	
	set_mode_config(name)
	
    -- set kind
    set_kind("shared")
	
	add_includedirs(prefixInclude)

	if output then
		set_targetdir(output.bin)
		set_objectdir(output.obj)
		set_headerdir(output.include)
	end

	
	-- add headers
	add_headers(prefixInclude .. "/Common/**.h", 
				prefixInclude .. "/Common/**.cpp",
				prefixInclude .. "/LuaEngine/**.h", 
				prefixInclude .. "/LuaEngine/**.hpp", 
				prefixInclude .. "/LuaEngine/**.cpp")

		
	-- add files
	add_files(prefixSrc .. "/Common/**.cpp", 
				prefixSrc .. "/Common/**.c",
				prefixSrc .. "/LuaEngine/**.cpp", 
				prefixSrc .. "/LuaEngine/**.c")
	if not is_plat("windows") then
		add_files(prefixSrc .. "/Atomic/*.c")
	end
	
	

