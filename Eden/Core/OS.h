#ifndef H_CORE_OS_H
#define H_CORE_OS_H

#include "Types.h"

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

		template<typename Type>
		Type MakePath(Type t)
		{
			return Type(t);
		}

		template<typename Type, typename... Args>
		Type MakePath(Type t, Args... args)
		{
			return Type(t + PathDelimeter + MakePath(args));
		}
	}
}

#endif