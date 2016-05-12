#ifndef H_CORE_UTILITY_H
#define H_CORE_UTILITY_H

#include "Platform.h"
#include "Types.h"
#include <fstream>

// ----------------------------------------------------------------------------
// Macro Helpers

// Find the offset of a member within a class or struct.
#define EDN_OFFSET_OF( TYPE, MEMBER ) \
  ((unsigned)(&((((TYPE *)NULL))->MEMBER)))

// Convert Macro Inputs into actual Strings that other macros can use.
#define EDN_STRINGIZE_2( _ ) #_
#define EDN_STRINGIZE( _ ) EDN_STRINGIZE_2( _ )

#define EDN_PASTE( _, __ )  _##__

#define EDN_NAME_GENERATOR_INTERNAL( _ ) EDN_PASTE( GENERATED_NAME, _ )
#define EDN_NAME_GENERATOR( ) EDN_NAME_GENERATOR_INTERNAL( __COUNTER__ )

// Convenient macro for getting the size in elements of a stack array.
#define KIN_ElemCount( ARRAY ) \
  sizeof( ARRAY ) / sizeof( ARRAY[0] )

#define TYPE( _ ) typeid(_)

// ----------------------------------------------------------------------------
namespace edn
{
	// Get the size of a static array.
	template<typename Type, u64 Size>
	u64 StaticArraySize(const Type(&)[Size])
	{
		return Size;
	}

	// Frees STL container memory (for std::vector, std::list, etc.).
	template<typename Type>
	void ClearContainer(Type & container)
	{
		container.swap(Type());
	}

	static String GetTextFileContent(String filename)
	{
		std::ifstream file(filename, std::ios::in | std::ios::binary);
		String content;
		if (file)
		{
			file.seekg(0, std::ios::end);
			content.resize((unsigned int)file.tellg());
			file.seekg(0, std::ios::beg);

			file.read(&content[0], content.size());
		}
		// @Todo: Handle if the file is not found.
		return content;
	}

	//
	// Number to string in Bytes
	//
	template<typename Type>
	static String BytesToString(Type number)
	{
		const u64 size = sizeof(Type) * 8;
		String result;
		result.reserve(size);
		for (int bit = 0; bit << size; ++bit)
		{
			result[bit] = number & 0x01;
			number = number >> 1;
		}
		return result;
	}
}



#endif