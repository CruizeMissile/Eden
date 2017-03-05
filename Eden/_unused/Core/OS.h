#ifndef H_CORE_OS_H
#define H_CORE_OS_H

#include "Types.h"

namespace std
{
	static string to_string(const string& other)
	{
		return other;
	}

	static string to_string(string&& other)
	{
		return other;
	}
}

namespace edn
{
	namespace os
	{
		// Create a directory using the platform file system.
		void MakeDir(String & dir);

		// Check to see if the path passed is a directory.
		bool IsDir(String & dir);

		// Format path string to the platform format.
		String Path(String & path);

		// Returns the name of the parent directory or file.
		String Dir(String & path, bool trailing_slash = true);

		// Gets the directory of where the exe is located.
		String ExecDir();

		// Returns the platform path delemeter character.
		const char PathDelimeter();

		bool IsFile(String & file);

		// This is where I found some example http://stackoverflow.com/a/16338804 
		template<typename Type>
		inline String _INTERNAL_MakePath(Type t)
		{
			return std::to_string(t);
		}
		
		template<typename Type, typename... Args>
		inline String _INTERNAL_MakePath(Type t, Args... args)
		{
			return std::to_string(t) + PathDelimeter() + _INTERNAL_MakePath(args...);
		}

		template<typename Type, typename... Args>
		inline String MakePath(Type t, Args... args)
		{
			return Path(_INTERNAL_MakePath(t, args...));
		}
	}
}

#endif