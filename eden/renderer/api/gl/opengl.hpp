
#pragma once

#include "../../../core/platform.hpp"

#if defined(EDEN_OS_WINDOWS)
#include <pride/config/include/windows.hpp>
#include <GL/GL.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#elif defined(EDEN_OS_MACOSX)
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#elif defined(EDEN_OS_LINUX)
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#else
#error Platform is not supported for OpenGL
#endif
