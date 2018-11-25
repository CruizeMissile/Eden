#pragma once

#include "../../core/platform.hpp"

#if defined(EDEN_OS_WINDOWS)
#    include "win32/win32_native_handle.hpp"
#elif defined(EDEN_OS_MACOSX)
#    include "osx/osx_native_handle.hpp"
#elif defined(EDEN_OS_LINUX)
#    include "linux/linux_native_handle.hpp"
#else
#    error "Platform is not supported"
#endif
