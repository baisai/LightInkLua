
cmake_minimum_required(VERSION 2.8)
project(LightInkLua)

include_directories( ${LightInkLua_SOURCE_DIR}/../../include )

set( sourceRootPath ${LightInkLua_SOURCE_DIR}/../../src )

set( middlePath Common )
set( sourceFile 
	RuntimeError.cpp
	SmallObject.cpp
	LightInkVersion.cpp
	WinSnprintf.c
)
foreach(k ${sourceFile} )
  set( fullSourcePath ${fullSourcePath} ${sourceRootPath}/${middlePath}/${k} )
endforeach(k)


set( middlePath LuaEngine )
set( sourceFile
	LuaEngine.cpp
	LuaIndexMetatable.cpp
	LuaIterator.cpp
	LuaModule.cpp
	LuaInt64.cpp
	lua/lapi.c
	lua/lauxlib.c
	lua/lbaselib.c
	lua/lcode.c
	lua/ldblib.c
	lua/ldebug.c
	lua/ldo.c
	lua/ldump.c
	lua/lfunc.c
	lua/lgc.c
	lua/linit.c
	lua/liolib.c
	lua/llex.c
	lua/lmathlib.c
	lua/lmem.c
	lua/loadlib.c
	lua/lobject.c
	lua/lopcodes.c
	lua/loslib.c
	lua/lparser.c
	lua/lstate.c
	lua/lstring.c
	lua/lstrlib.c
	lua/ltable.c
	lua/ltablib.c
	lua/ltm.c
	lua/lundump.c
	lua/lvm.c
	lua/lzio.c
	lua/print.c
)
foreach(k ${sourceFile} )
  set( fullSourcePath ${fullSourcePath} ${sourceRootPath}/${middlePath}/${k} )
endforeach(k)

set( middlePath Atomic )
set( sourceFile 
	mintomic_gcc.c
)
foreach(k ${sourceFile} )
  set( fullSourcePath ${fullSourcePath} ${sourceRootPath}/${middlePath}/${k} )
endforeach(k)


if (CMAKE_BUILD_TYPE STREQUAL Debug)
	add_definitions("-D_DEBUG")
endif ()
add_definitions("-DLIGHTINK_AS_DLL")
add_definitions("-DLIGHTINK_EXPORTS")

add_library( ${PROJECT_NAME} SHARED ${fullSourcePath} )

if (CMAKE_BUILD_TYPE STREQUAL Debug)
set(LIBRARY_OUTPUT_PATH ${LightInkLua_SOURCE_DIR}/../../bin/Debug)
else()
set(LIBRARY_OUTPUT_PATH ${LightInkLua_SOURCE_DIR}/../../bin/Release)
endif()

unset(middlePath)
unset(sourceFile)
unset(fullSourcePath)
unset(sourceRootPath)






