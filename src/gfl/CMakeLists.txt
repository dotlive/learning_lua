PROJECT(GFL)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(GFL_MAJOR_VERSION 1)
SET(GFL_MINOR_VERSION 0)
SET(GFL_PATCH_VERSION 0)
SET(GFL_VERSION ${GFL_MAJOR_VERSION}.${GFL_MINOR_VERSION}.${GFL_PATCH_VERSION})

SET(GFL_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# The project settings

SET(LIB_NAME gfl)

# Base
SET(BASE_HEADER_FILES
    ${GFL_PROJECT_DIR}/include/gfl/gfl.h
    ${GFL_PROJECT_DIR}/include/gfl/platform.h
    ${GFL_PROJECT_DIR}/include/gfl/base/dll_loader.h
    ${GFL_PROJECT_DIR}/include/gfl/base/file_sys.h
)
SET(BASE_SOURCE_FIELS
    ${GFL_PROJECT_DIR}/src/base/gfl.cpp
    ${GFL_PROJECT_DIR}/src/base/dll_loader.cpp
    ${GFL_PROJECT_DIR}/src/base/file_sys.cpp
)

# Utils
SET(UTILS_HEADER_FILES
    ${GFL_PROJECT_DIR}/include/gfl/utils/string_util.h
)
SET(UTILS_SOURCE_FILES
    ${GFL_PROJECT_DIR}/src/utils/string_util.cpp
)

SOURCE_GROUP("Base\\Header Files" FILES ${BASE_HEADER_FILES})
SOURCE_GROUP("Base\\Source Files" FILES ${BASE_SOURCE_FIELS})
SOURCE_GROUP("Utils\\Header Files" FILES ${UTILS_HEADER_FILES})
SOURCE_GROUP("Utils\\Source Files" FILES ${UTILS_SOURCE_FILES})

INCLUDE_DIRECTORIES(${GFL_PROJECT_DIR}/include)
ADD_LIBRARY(${LIB_NAME} STATIC
    ${BASE_SOURCE_FIELS} ${BASE_HEADER_FILES}
    ${UTILS_SOURCE_FILES} ${UTILS_HEADER_FILES}
)
