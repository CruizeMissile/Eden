#ifndef H_CORE_TYPES_H
#define H_CORE_TYPES_H

#include "Platform.h"
#include <string>

// --------------------------------------------------------------------------------------------------------------------
// Type Specification

// Integer:         [us](8|16|32|64)
// Floating Point:  f(32|64)
// Integral Size:   [us]size
// Boolean:         b(8|32) // @Note: 16 bit boolean is never needed
// Pointer Integer: u?intptr

// All "common" platforms use the same size for char, short and int
// We do not need to include stdint.h/cstdint which not always available.

// The amount of times that I have swapped between conventions is a lot!
// s8/i8/int8 etc. & u8/uint8 etc. This makes sure that all my code uses
// the same conventions.

// Note: If you want to know the size of the int just use the formula
// below. This is just incase you wanted to know or just forgot.
// u +(2^n)-1 | s -(2^n-1) | s +(2^n-1)-1
using s8 = signed char;     // -128 | 127
using u8 = unsigned char;   // 255

using s16 = signed short;   // -32,768 | 32,767
using u16 = unsigned short; // 65,535

using s32 = signed int;     // -2,147,483,648 | 2,147,483,647
using u32 = unsigned int;   // 4,294,967,295

#if defined( _MSC_VER )
using s64 = signed __int64;     // -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807
using u64 = unsigned __int64;   // 18,446,744,073,709,551,615
#else
using s64 = signed long long;   // -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807
using u64 = unsigned long long; // 18,446,744,073,709,551,615
#endif

// Defining the min and max of each of these int sizes
#define S8_MAX 0x7f
#define S8_MIN (-S8_MAX - 1)
#define U8_MAX ((u8)-1)

#define S16_MAX 0x7fff
#define S16_MIN (-S16_MAX - 1)
#define U16_MAX ((u16)-1)

#define S32_MAX 0x7fffffffL
#define S32_MIN (-S32_MAX - 1L)
#define U32_MAX ((u32)-1)

#define S64_MAX 0x7fffffffffffffffLL
#define S64_MIN (-S64_MAX - 1LL)
#define U64_MAX ((u64)-1)

// This makes sure that depending on the platform target that we are working on
    // the size will reflect the platform target. This makes sure that if we need
    // size of something that we will be using the size of the platform target.
#if defined(EDN_64_BIT)
    using usize = u64;
    using ssize = s64;
#elif defined(EDN_32_BIT)
    using usize = u32;
    using ssize = s32;
#else
#error Unknown bit size
#endif

// Understand that float is 32 bits and double is a double persision float
// that is 64 bits but like to see the size on the type and shorter to type in.
using f32 = float;
using f64 = double;

// Hate typing std::string and String is soooo much better :)
using String = std::string;

#endif
