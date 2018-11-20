PROJECT(lua-5.2.2)

# remove warnings
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)

# headers
SET(HDR_CORE
    src/lapi.h src/lcode.h src/lctype.h src/ldebug.h src/ldo.h src/lfunc.h
    src/lgc.h src/llex.h src/llimits.h src/lmem.h src/lobject.h src/lopcodes.h src/lparser.h
    src/lstate.h src/lstring.h src/ltable.h src/ltm.h src/lua.h src/luaconf.h src/lualib.h
    src/lundump.h src/lvm.h src/lzio.h
)
SET(HDR_LIB
    src/lauxlib.h
)
# sources
SET(SRC_CORE
    src/lapi.c src/lcode.c src/lctype.c src/ldebug.c src/ldo.c src/ldump.c src/lfunc.c
    src/lgc.c src/llex.c src/lmem.c src/lobject.c src/lopcodes.c src/lparser.c src/lstate.c
    src/lstring.c src/ltable.c src/ltm.c src/lundump.c src/lvm.c src/lzio.c
)
SET(SRC_LIB
    src/lauxlib.c src/lbaselib.c src/lbitlib.c src/lcorolib.c
    src/ldblib.c src/liolib.c src/lmathlib.c src/loadlib.c
    src/loslib.c src/lstrlib.c src/ltablib.c src/linit.c
)
# interpreter
SET(SRC_LUA src/lua.c)
# compiler
SET(SRC_LUAC src/luac.c)

# set include file directory
INCLUDE_DIRECTORIES(src)
# append headers to sources to make them show up in MSVC GUI
LIST(APPEND SRC_CORE ${HDR_CORE})
LIST(APPEND SRC_LIB ${HDR_LIB})
# make .h files show only
SET_SOURCE_FILES_PROPERTIES(${HDR_CORE} PROPERTIES HEADER_FILE_ONLY TRUE)
SET_SOURCE_FILES_PROPERTIES(${HDR_LIB} PROPERTIES HEADER_FILE_ONLY TRUE)

# compile with C++ compiler
#SET_SOURCE_FILES_PROPERTIES(${SRC_CORE} ${SRC_LIB} ${SRC_LUA} ${SRC_LUAC} PROPERTIES LANGUAGE CXX)

# Library
ADD_LIBRARY(lualib STATIC ${SRC_CORE} ${SRC_LIB})
SET_TARGET_PROPERTIES(lualib PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${COMMON_OUTPUT})

# DLL
ADD_LIBRARY(lua5.2 SHARED ${SRC_CORE} ${SRC_LIB})
SET_TARGET_PROPERTIES(lua5.2 PROPERTIES DEFINE_SYMBOL "LUA_BUILD_AS_DLL")
SET_TARGET_PROPERTIES(lua5.2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${COMMON_OUTPUT})

# exe
ADD_EXECUTABLE(lua ${SRC_LUA})
ADD_EXECUTABLE(luac ${SRC_LUAC})

# lua uses a DLL; luac uses a library
TARGET_LINK_LIBRARIES(lua lua5.2)
TARGET_LINK_LIBRARIES(luac lualib)
SET_TARGET_PROPERTIES(lua PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${COMMON_OUTPUT})
SET_TARGET_PROPERTIES(luac PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${COMMON_OUTPUT})
