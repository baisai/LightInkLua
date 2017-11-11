
cmake_minimum_required(VERSION 2.8)
project(LightInkLua)

include_directories( ${LightInkLua_SOURCE_DIR}/../../include )

set( sourceRootPath ${LightInkLua_SOURCE_DIR}/../../src )

set( middlePath Common )
set( sourceFile 
	LightInkVersion.cpp
	RuntimeError.cpp
	SmallObject.cpp
	WinSnprintf.c
)
foreach(k ${sourceFile} )
  set( fullSourcePath ${fullSourcePath} ${sourceRootPath}/${middlePath}/${k} )
endforeach(k)


set( middlePath LuaEngine )
set( sourceFile
	LuaEngine.cpp
	LuaIndexMetatable.cpp
	LuaInt64.cpp
	LuaIterator.cpp
	LuaModule.cpp
	LuaRef.cpp
	LuaTableRef.cpp
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

if (CMAKE_BUILD_TYPE STREQUAL Release)
	add_definitions("-DNDEBUG")
else ()
	add_definitions("-D_DEBUG")
	set( CMAKE_BUILD_TYPE Debug )
endif ()

add_definitions("-DLIGHTINK_AS_DLL")
add_definitions("-DLIGHTINK_EXPORTS")

add_library( ${PROJECT_NAME} SHARED ${fullSourcePath} )

if (CMAKE_BUILD_TYPE STREQUAL Debug)
set(LIBRARY_OUTPUT_PATH ${LightInkLua_SOURCE_DIR}/../../bin/Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -W -pipe -fPIC")
else()
set(LIBRARY_OUTPUT_PATH ${LightInkLua_SOURCE_DIR}/../../bin/Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -W -pipe -fPIC")
endif()

unset(middlePath)
unset(sourceFile)
unset(fullSourcePath)
unset(sourceRootPath)






