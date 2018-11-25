
#pragma once

#if defined(__unix__) || defined(__unix)
#    if defined(__ANDROID__)
#        define EDEN_OS_ANDROID
#    elif defined(__linux__)
#        define EDEN_OS_LINUX
#    else
#        define EDEN_OS_UNKNOWN
#    endif
#elif defined(_WIN64) || defined(_WIN32) || defined(__CYGWIN32__) || defined(__MINGW32__)
#    define EDEN_OS_WINDOWS
#elif defined(MACOSX) || defined(__DARWIN__) || defined(__APPLE__)
#    define EDEN_OS_MACOSX
#else
#    error "Platform is not supported"
#endif
