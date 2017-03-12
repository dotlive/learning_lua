cmake_minimum_required(VERSION 2.8.6)
project(LuaSrc-522)

# lua static library
add_library(lualib STATIC
	lapi.h lapi.c
	lauxlib.h lauxlib.c
	lbaselib.c
	lbitlib.c
	lcode.h lcode.c
	lcorolib.c
	lctype.h lctype.c
	ldblib.c
	ldebug.h ldebug.c
	ldo.h ldo.c
	ldump.c
	lfunc.h lfunc.c
	lgc.h lgc.c
	linit.c
	liolib.c
	llex.h llex.c
	llimits.h
	lmathlib.c
	lmem.h lmem.c
	loadlib.c
	lobject.h lobject.c
	lopcodes.h lopcodes.c
	loslib.c
	lparser.h lparser.c
	lstate.h lstate.c
	lstring.h lstring.c
	lstrlib.c
	ltable.h ltable.c
	ltablib.c
	ltm.h ltm.c
	lua.h
	lua.hpp
	luaconf.h
	lualib.h
	lundump.h lundump.c
	lvm.h lvm.c
	lzio.h lzio.c)
set_target_properties(lualib PROPERTIES OUTPUT_NAME "lua")

# lua interpreter
link_directories(${LUA_BINARY_DIR})
add_executable(lua lua.c)
target_link_libraries(lua lualib)

# lua compiler
link_directories(${LUA_BINARY_DIR})
add_executable(luac luac.c)
target_link_libraries(luac lualib)