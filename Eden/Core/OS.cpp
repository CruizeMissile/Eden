#include "Precompiled.h"
#include "OS.h"
#include "Platform.h"

#if defined(EDN_WINDOWS)
#include <direct.h>
#elif defined(EDN_LINUX)
#include  <sys\stat.h>
#include  <sys\types.h>
#endif
#include <algorithm>

const char WINDOWS_PATH_DELIMETER = '\\';
const char UNIX_PATH_DELEMETER = '/';

namespace edn
{
	namespace os
	{
		void MakeDir(String & dir)
		{
		#if defined(EDN_WINDOWS)
			_mkdir(dir.c_str());
		#elif defined(EDN_MACOS)
			#error Implement on mac
		#elif defined(END_LINUX)
			// @Note: Need to test to see if this works on Linux
			mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		#endif
		}

		bool IsDir(String & dir)
		{
			// Format path
			String path = Path(dir);
		#if defined(EDN_WINDOWS)
			DWORD attrib = GetFileAttributes(dir.c_str());
			return	(attrib != INVALID_FILE_ATTRIBUTES) &&
				(attrib & FILE_ATTRIBUTE_DIRECTORY);
		#elif defined(EDN_MACOS)
			#error Implement on mac
		#elif defined(EDN_LINUX)
			// @Note: Test to see if code works on Linux
			struct stat info;
			stat(dir.c_str(), &info);
			return S_ISDIR(info.st_mode);
		#endif
		}

		String Path(String & path)
		{
			String copy = path;
		#if defined(EDN_WINDOWS)
			std::replace(copy.begin(), copy.end(), UNIX_PATH_DELEMETER, WINDOWS_PATH_DELIMETER);
		#elif defined(EDN_UNIX) || defined(EDN_MACOSX)
			std::replace(copy.begin(), copy.end(), WINDOWS_PATH_DELIMETER, UNIX_PATH_DELEMETER);
		#endif
			return copy;
		}

		String Dir(String & path, bool traling_slash)
		{
			String copy = path;
			char * dir = &copy[0];
			char * p = strrchr(dir, PathDelimeter());
			copy = copy.substr(0, (int)(p - dir));
			return copy;
		}

		String ExecDir()
		{
		#if defined(EDN_WINDOWS)
			char path[MAX_PATH];
			GetModuleFileName(NULL, path, MAX_PATH);
			return Dir(String(path));
		#elif defined(EDN_MACOS)
			#error Implement on mac
		#elif defined(EDN_LINUX)
			#error Implement on Linux
		#endif
		}

		const char PathDelimeter()
		{
			return EDN_PATH_DELIMITER;
		}

		bool IsFile(String & file)
		{
		#if defined(EDN_WINDOWS)
			WIN32_FIND_DATA FindFileData;
			HANDLE handle = FindFirstFile(file.c_str(), &FindFileData);
			int found = handle != INVALID_HANDLE_VALUE;
			return found ? true : false;
		#elif defined(EDN_MACOS)
			#error Implement on mac
		#elif defined(EDN_LINUX)
			#error Implement on Linux
		#endif
		}

		String MakePath(String * list)
		{
			String result = "";
			u64 count = EDN_ElemCount(list);
			for (u32 i = 0; i < count; ++i)
			{
				result += list[i] + PathDelimeter();
			}
			result.pop_back();

			return Path(result);
		}

	}
}