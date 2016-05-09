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

#elif defined (__APPLE__) && defined(__MACH__)
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
#elif defined(__GNUC__) || defined(__GNUG__) && !(defined(__clang__) || defined(__INTEL_COMPILER))
	// GNU GCC/G++ Compiler.
	#define EDN_COMPILER_GNU_GCC
#elif defined(__INTEL_COMPILER)
	// Intel C++ Compiler.
	#define EDN_COMPILER_INTEL
#endif

// ----------------------------------------------------------------------------
// Enviroment Bit Size

#if defined(EDN_COMPILER_MSVC)
    #if defined(_WIN64)
        #define EDN_64_BIT
    #else
        #define EDN_32_BIT
    #endif
	// @Note: Figure out bit size for the other platforms.
#endif

#if defined(EDN_COMPILER_GNUC_GCC)
	#if defined(__x86_64__) || defined(__ppc64__)
        #define EDN_64_BIT
    #else
        #define EDN_32_BIT
    #endif
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
// Miselaneous defines

#if defined(EDN_WINDOWS)
	#define EDN_PATH_DELIMITER '\\'
#else
	#define EDN_PATH_DELIMITER '/'
#endif

#endif