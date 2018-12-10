PROJECT(launcher)

SET(HDR_CORE
    pch.h
    core/lua_engine.h
)
SET(SRC_CORE
    core/lua_engine.cpp
    core/launcher.cpp
)

SET(HDR_TEST
    test/test_case.h
)
SET(SRC_TEST
    test/test_case.cpp
)

SOURCE_GROUP("include\\core" FILES ${HDR_CORE})
SOURCE_GROUP("src\\core" FILES ${SRC_CORE})
SOURCE_GROUP("include\\test" FILES ${HDR_TEST})
SOURCE_GROUP("src\\test" FILES ${SRC_TEST})

SET(LIB_NAME launcher)

INCLUDE_DIRECTORIES(${LUA_SRC_DIR})
INCLUDE_DIRECTORIES(${SDK_ROOT_DIR}/include)
LINK_DIRECTORIES(${MAGE_BIN_DIR})
LINK_DIRECTORIES("${SDK_ROOT_DIR}/lib/${MAGE_PLATFORM_NAME}")

ADD_EXECUTABLE(${LIB_NAME}
    ${SRC_CORE} ${HDR_CORE}
    ${SRC_TEST} ${HDR_TEST}
)
TARGET_LINK_LIBRARIES(${LIB_NAME}
    ${LUA_SHARED_LIB}
    foundation_d
    gtestd
    gtest_maind
)

IF(MAGE_PLATFORM_WINDOWS)
    CREATE_VCPROJ_USERFILE(${LIB_NAME})
ENDIF()
