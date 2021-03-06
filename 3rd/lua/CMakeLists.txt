CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT("lua")

# core
SET(HDR_CORE
    ${LUA_SRC_DIR}/lapi.h
    ${LUA_SRC_DIR}/lcode.h
    ${LUA_SRC_DIR}/lctype.h
    ${LUA_SRC_DIR}/ldebug.h
    ${LUA_SRC_DIR}/ldo.h
    ${LUA_SRC_DIR}/lfunc.h
    ${LUA_SRC_DIR}/lgc.h
    ${LUA_SRC_DIR}/llex.h
    ${LUA_SRC_DIR}/llimits.h
    ${LUA_SRC_DIR}/lmem.h
    ${LUA_SRC_DIR}/lobject.h
    ${LUA_SRC_DIR}/lopcodes.h
    ${LUA_SRC_DIR}/lparser.h
    ${LUA_SRC_DIR}/lstate.h
    ${LUA_SRC_DIR}/lstring.h
    ${LUA_SRC_DIR}/ltable.h
    ${LUA_SRC_DIR}/ltm.h
    ${LUA_SRC_DIR}/lua.h
    ${LUA_SRC_DIR}/luaconf.h
    ${LUA_SRC_DIR}/lualib.h
    ${LUA_SRC_DIR}/lundump.h
    ${LUA_SRC_DIR}/lvm.h
    ${LUA_SRC_DIR}/lzio.h
)
SET(SRC_CORE
    ${LUA_SRC_DIR}/lapi.c
    ${LUA_SRC_DIR}/lcode.c
    ${LUA_SRC_DIR}/lctype.c
    ${LUA_SRC_DIR}/ldebug.c
    ${LUA_SRC_DIR}/ldo.c
    ${LUA_SRC_DIR}/ldump.c
    ${LUA_SRC_DIR}/lfunc.c
    ${LUA_SRC_DIR}/lgc.c
    ${LUA_SRC_DIR}/llex.c
    ${LUA_SRC_DIR}/lmem.c
    ${LUA_SRC_DIR}/lobject.c
    ${LUA_SRC_DIR}/lopcodes.c
    ${LUA_SRC_DIR}/lparser.c
    ${LUA_SRC_DIR}/lstate.c
    ${LUA_SRC_DIR}/lstring.c
    ${LUA_SRC_DIR}/ltable.c
    ${LUA_SRC_DIR}/ltm.c
    ${LUA_SRC_DIR}/lundump.c
    ${LUA_SRC_DIR}/lvm.c
    ${LUA_SRC_DIR}/lzio.c
)
# official libs
SET(HDR_LIB
    ${LUA_SRC_DIR}/lauxlib.h
)
SET(SRC_LIB
    ${LUA_SRC_DIR}/lauxlib.c
    ${LUA_SRC_DIR}/lbaselib.c
    ${LUA_SRC_DIR}/lbitlib.c
    ${LUA_SRC_DIR}/lcorolib.c
    ${LUA_SRC_DIR}/ldblib.c
    ${LUA_SRC_DIR}/liolib.c
    ${LUA_SRC_DIR}/lmathlib.c
    ${LUA_SRC_DIR}/loadlib.c
    ${LUA_SRC_DIR}/loslib.c
    ${LUA_SRC_DIR}/lstrlib.c
    ${LUA_SRC_DIR}/ltablib.c
    ${LUA_SRC_DIR}/linit.c
)
# compiler
SET(SRC_LUAC
    ${LUA_SRC_DIR}/luac.c
)
# interpreter
SET(SRC_LUA
    ${LUA_SRC_DIR}/lua.c
)

SOURCE_GROUP("core\\header" FILES ${HDR_CORE})
SOURCE_GROUP("core\\src" FILES ${SRC_CORE})
SOURCE_GROUP("lib\\headers" FILES ${HDR_LIB})
SOURCE_GROUP("lib\\src" FILES ${SRC_LIB})

# append headers to sources to make them show up in MSVC GUI
LIST(APPEND SRC_CORE ${HDR_CORE})
LIST(APPEND SRC_LIB ${HDR_LIB})

# set include file directory
INCLUDE_DIRECTORIES(${LUA_SRC_DIR})
LINK_DIRECTORIES(${MAGE_BIN_DIR})

# Library
ADD_LIBRARY(${LUA_STATIC_LIB} STATIC ${SRC_CORE} ${SRC_LIB})
SET_TARGET_PROPERTIES(${LUA_STATIC_LIB} PROPERTIES
    FOLDER "${3RD_PROJECT_FOLDER_PREFIX}/luasrc"
)
# DLL
ADD_LIBRARY(${LUA_SHARED_LIB} SHARED ${SRC_CORE} ${SRC_LIB})
SET_TARGET_PROPERTIES(${LUA_SHARED_LIB} PROPERTIES
    FOLDER "${3RD_PROJECT_FOLDER_PREFIX}/luasrc"
)
# luac
ADD_EXECUTABLE(${LUA_COMPILER} ${SRC_LUAC})
TARGET_LINK_LIBRARIES(${LUA_COMPILER} ${LUA_STATIC_LIB})
SET_TARGET_PROPERTIES(${LUA_COMPILER} PROPERTIES
    FOLDER "${3RD_PROJECT_FOLDER_PREFIX}/luasrc"
)
# lua
ADD_EXECUTABLE(${LUA_INTERPRETER} ${SRC_LUA})
TARGET_LINK_LIBRARIES(${LUA_INTERPRETER} ${LUA_SHARED_LIB})
SET_TARGET_PROPERTIES(${LUA_INTERPRETER} PROPERTIES
    FOLDER "${3RD_PROJECT_FOLDER_PREFIX}/luasrc"
)

IF(MAGE_PLATFORM_WINDOWS)
    CREATE_VCPROJ_USERFILE(${LUA_STATIC_LIB})
    CREATE_VCPROJ_USERFILE(${LUA_SHARED_LIB})
    CREATE_VCPROJ_USERFILE(${LUA_COMPILER})
    CREATE_VCPROJ_USERFILE(${LUA_INTERPRETER})

    SET_TARGET_PROPERTIES(${LUA_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "LUA_BUILD_AS_DLL")
ENDIF()
