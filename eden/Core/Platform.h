#ifndef H_CORE_PLATFORM_H
#define H_CORE_PLATFORM_H

// --------------------------------------------------------------------------------------------------------------------
// System OS

// Identifying the operating system that we are running on.
// Reference and information from:
// http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system

#if defined(_WIN32) || defined (_WIN64)
	#define EDN_WINDOWS

	// Making sure that NOMINMAX is defined.
	#ifndef NOMINMAX
	#define NOMINMAX
	#endif
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>

	// undef the shittiest win32 macros of ALL TIME. No one needs these they just get in the way
	// and it is our fault for having to include the biggest pile of shit windows.h
	#undef near
	#undef far
	#undef min
	#undef max
	// Sanity has been restored

	// @Note: This is not recommended as every project that uses this file will not
	// have a console window
	//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#elif defined (__APPLE__) && defined(__MACH__)
	#define EDN_UNIX
	#define EDN_MACOSX
#elif defined(__unix__)
	#define EDN_UNIX
	#if defined(__linux__)
		#define EDN_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernal__)
		#define EDN_FREEBSD
	#else
		#error This Unix operating system is not supported by Eden
	#endif
#endif

// ----------------------------------------------------------------------------
// Debug Release Mode

#if defined (_DEBUG)
	#define EDN_DEBUG
#else
	#define EDN_RELEASE
#endif

// ----------------------------------------------------------------------------
// Compiler Identification

#if defined(_MSC_VER)
	// Microsoft Visual Studio.
	#define EDN_COMPILER_MSVC
	#define _ALLOW_KEYWORD_MACROS
#elif defined(__clang__)
	// Clang.
	#define EDN_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
	// GNU GCC/G++ Compiler.
	#define EDN_COMPILER_GCC
#elif defined(__INTEL_COMPILER)
	// Intel C++ Compiler.
	#define EDN_COMPILER_INTEL
#endif

#if !defined(EDN_COMPILER_MSVC) && !defined(EDN_COMPILER_GCC) && !defined(EDN_COMPILER_CLANG)
#error No compiler macro defined. Compiler is not supported by Eden.
#endif

// ----------------------------------------------------------------------------
// Enviroment Bit Size

#if defined(EDN_COMPILER_MSVC)
	#if defined(_WIN64)
		#define EDN_64_BIT
	#else
		#define EDN_32_BIT
	#endif
#endif

#if defined(EDN_COMPILER_GCC) || defined(EDN_COMPILER_CLANG)
	#if defined(__x86_64__) || defined(__LP64__) || defined(_i386_)
		#define EDN_64_BIT
	#else
		#define EDN_32_BIT
	#endif
#endif

#if !defined(EDN_32_BIT) && !defined(EDN_64_BIT)
#error Cound not figure out the bit archetecture
#endif

// ----------------------------------------------------------------------------
// Static VS. Dynalic Linking

#if !defined(EDN_STATIC)
	#if defined(EDN_WINDOWS)
		#if defined(EDN_NON_CLIENT_BUILD)
			#if !defined(EDN_API)
			#define EDN_API __declspec(dllexport)
			#endif
		#else
			#if !defined(EDN_API)
			#define EDN_API __declspec(dllimport)
			#endif
		#endif
	#else
		#if __GNUC__ >= 4
		// GCC 4 has unique keywords for showing/hiding symbols.
		// The same keyword is used for both import and export
		#define EDN_API __attribute__ ((__visibility__("default")))
		#else
			#define EDN_API
		#endif
	#endif
#else
	#define EDN_API
#endif

// ----------------------------------------------------------------------------
// Disable compiler warnings on MSVC

#if defined(EDN_COMPILER_MSVC)
	#define EDN_DISABLE_WARNING(WARNING_NUMBER) __pragma(warning(disable : WARNING_NUMBER))
	#define EDN_RESET_WARNING(WARNING_NUMBER) __pragma(warning(default : WARNING_NUMBER))
#else
	#define EDN_DISABLE_WARNING(WARNING_NUMBER)
	#define EDN_RESET_WARNING(WARNING_NUMBER)
#endif

// ----------------------------------------------------------------------------
// Miselaneous defines

#if defined(EDN_WINDOWS)
	#define EDN_PATH_DELIMITER '\\'
#else
	#define EDN_PATH_DELIMITER '/'
#endif

#endif
