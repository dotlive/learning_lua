CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT("learning_lua")

SET(MAGE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SET(MAGE_BIN_DIR ${MAGE_ROOT_DIR}/bin)
SET(SDK_ROOT_DIR ${MAGE_ROOT_DIR}/sdk)

# lua settings
SET(3RD_ROOT_DIR "${MAGE_ROOT_DIR}/3rd")
SET(LUA_SRC_DIR ${3RD_ROOT_DIR}/lua/lua-5.2.4/src)
SET(LUA_STATIC_LIB lualib)
SET(LUA_SHARED_LIB lua5.2)
SET(LUA_COMPILER luac)
SET(LUA_INTERPRETER lua)

# OUTPUT (for static libs)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MAGE_BIN_DIR})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${MAGE_BIN_DIR})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${MAGE_BIN_DIR})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${MAGE_BIN_DIR})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${MAGE_BIN_DIR})
# LIBRARY (for module libs)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MAGE_BIN_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${MAGE_BIN_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${MAGE_BIN_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${MAGE_BIN_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${MAGE_BIN_DIR})
# RUNTIME (for runable and shared libs)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MAGE_BIN_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${MAGE_BIN_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${MAGE_BIN_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${MAGE_BIN_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${MAGE_BIN_DIR})

INCLUDE(${SDK_ROOT_DIR}/cmake/common.cmake)
INCLUDE(${SDK_ROOT_DIR}/cmake/platform.cmake)
INCLUDE(${SDK_ROOT_DIR}/cmake/compiler.cmake)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/3rd)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src)
