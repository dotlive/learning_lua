#ifndef _GFL_PLATFORM_H_
#define _GFL_PLATFORM_H_

// Detects supported platforms
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    #define MAGE_PLATFORM_WINDOWS

    #define MAGE_HAS_DECLSPEC

    #if defined(_WIN64)
        #define MAGE_PLATFORM_WIN64
    #else
        #define MAGE_PLATFORM_WIN32
    #endif

    // Shut min/max in windows.h
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #ifndef WINDOWS_LEAN_AND_MEAN
        #define WINDOWS_LEAN_AND_MEAN
    #endif

    #if defined(__MINGW32__)
        #include <_mingw.h>
    #else
        #include <sdkddkver.h>
    #endif

    #ifndef _WIN32_WINNT_WIN7
        #define _WIN32_WINNT_WIN7 0x0601
    #endif
    #ifndef _WIN32_WINNT_WINBLUE
        #define _WIN32_WINNT_WINBLUE 0x0603
    #endif
    #ifndef _WIN32_WINNT_WIN10
        #define _WIN32_WINNT_WIN10 0x0A00
    #endif

    #if (_WIN32_WINNT >= _WIN32_WINNT_WIN10)
        #include <winapifamily.h>
        #if defined(WINAPI_FAMILY)
            #if WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
                #define MAGE_PLATFORM_WINDOWS_DESKTOP
            #else
                #define MAGE_PLATFORM_WINDOWS_STORE
            #endif
        #else
            #define MAGE_PLATFORM_WINDOWS_DESKTOP
        #endif
    #else
        #define MAGE_PLATFORM_WINDOWS_DESKTOP
    #endif
#elif defined(__ANDROID__)
    #define MAGE_PLATFORM_ANDROID
#elif defined(__CYGWIN__)
    #define MAGE_PLATFORM_CYGWIN
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #define MAGE_PLATFORM_LINUX
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define MAGE_PLATFORM_IOS
    #else
        #define MAGE_PLATFORM_DARWIN
    #endif
#else
    #error "Unknown platform. The supported target platforms are Windows, Android, Linux, macOS, and iOS."
#endif

#endif // _GFL_PLATFORM_H_
