IF(WIN32)
    IF(MSVC)
        IF((CMAKE_GENERATOR_PLATFORM STREQUAL "x64") OR (CMAKE_GENERATOR MATCHES "Win64"))
            SET(MAGE_ARCH_NAME "x64")
            SET(MAGE_VS_PLATFORM_NAME "x64")
        ELSEIF((CMAKE_GENERATOR_PLATFORM STREQUAL "ARM64") OR (CMAKE_GENERATOR MATCHES "ARM64"))
            SET(MAGE_ARCH_NAME "arm64")
            SET(MAGE_VS_PLATFORM_NAME "ARM64")
        ELSEIF((CMAKE_GENERATOR_PLATFORM STREQUAL "ARM") OR (CMAKE_GENERATOR MATCHES "ARM"))
            SET(MAGE_ARCH_NAME "arm")
            SET(MAGE_VS_PLATFORM_NAME "ARM")
        ELSE()
            MESSAGE(FATAL_ERROR "This CPU architecture is not supported")
        ENDIF()
    ENDIF()
    IF(WINDOWS_STORE)
        SET(MAGE_PLATFORM_NAME "win_store")
        SET(MAGE_PLATFORM_WINDOWS_STORE TRUE)
    ELSE()
        SET(MAGE_PLATFORM_NAME "win")
        SET(MAGE_PLATFORM_WINDOWS_DESKTOP TRUE)
    ENDIF()
    SET(MAGE_PLATFORM_WINDOWS TRUE)
ELSEIF(ANDROID)
    SET(MAGE_PLATFORM_NAME "android")
    SET(MAGE_PLATFORM_ANDROID TRUE)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(MAGE_PLATFORM_NAME "linux")
    SET(MAGE_PLATFORM_LINUX TRUE)
ELSEIF(IOS)
    SET(MAGE_PLATFORM_NAME "ios")
    SET(MAGE_PLATFORM_IOS TRUE)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    IF(IOS)
        SET(MAGE_PLATFORM_NAME "ios")
        SET(MAGE_PLATFORM_IOS TRUE)
    ELSE()
        SET(MAGE_PLATFORM_NAME "darwin")
        SET(MAGE_PLATFORM_DARWIN TRUE)
    ENDIF()
ENDIF()

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    SET(MAGE_HOST_PLATFORM_NAME "win")
    SET(MAGE_HOST_PLATFORM_WINDOWS TRUE)
ELSEIF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    SET(MAGE_HOST_PLATFORM_NAME "linux")
    SET(MAGE_HOST_PLATFORM_LINUX TRUE)
ELSEIF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
    SET(MAGE_HOST_PLATFORM_NAME "darwin")
    SET(MAGE_HOST_PLATFORM_DARWIN TRUE)
ENDIF()

IF(NOT MAGE_ARCH_NAME)
    IF((CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64") OR (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64"))
        SET(MAGE_ARCH_NAME "x64")
    ELSE()
        SET(MAGE_ARCH_NAME "x86")
    ENDIF()
ENDIF()

IF((CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "AMD64") OR (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64"))
    SET(MAGE_HOST_ARCH_NAME "x64")
ELSE()
    SET(MAGE_HOST_ARCH_NAME "x86")
ENDIF()

SET(MAGE_PLATFORM_NAME ${MAGE_PLATFORM_NAME}_${MAGE_ARCH_NAME})
SET(MAGE_HOST_PLATFORM_NAME ${MAGE_HOST_PLATFORM_NAME}_${MAGE_HOST_ARCH_NAME})

IF(MAGE_PLATFORM_ANDROID OR MAGE_PLATFORM_IOS)
    SET(MAGE_PREFERRED_LIB_TYPE "STATIC")
ELSE()
    SET(MAGE_PREFERRED_LIB_TYPE "SHARED")
ENDIF()

IF (MAGE_PLATFORM_WINDOWS_DESKTOP OR MAGE_PLATFORM_LINUX OR MAGE_PLATFORM_DARWIN)
    SET(MAGE_IS_DEV_PLATFORM TRUE)
ELSE()
    SET(MAGE_IS_DEV_PLATFORM FALSE)
ENDIF()
