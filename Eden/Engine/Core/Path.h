#pragma once
#include "Types.h"
#include "Platform.h"
#include <tuple>
#include <iostream>
#include <array>

namespace edn
{
	class Path;
	struct PathTuple;
	
	class Path
	{
	public:
#if defined(EDN_WINDOWS)
		static constexpr const char Seperator = '\\';
		static constexpr const char AltSeperator = '/';
#else
		static constexpr const char Seperator = '/';
		static constexpr const char AltSeperator = '\\';
#endif
		static constexpr const char BothSeperators[] = { '\\', '/' };

		Path() = default;
		Path(const Path&) = default;
		Path(Path&&) = default;

		Path(const String& value);
		Path(const char* value);

		Path& operator=(const Path&) = default;
		Path& operator=(Path&&) = default;

		// operator +
		Path operator+(const Path& rhs) const;

		// ----------------------------------------------------------------------------------------------
		// Static utility functions

		// Return a normalized absolutized version of the pathname path.On most platforms,
		// this is equivalent to calling the function normpath() as follows
		// normpath(join(os.getcwd(), path)).
		static Path Abspath(const Path& path);
		
		// Return the base name of pathname path. This is the second element of the
		// pair returned by passing path to the function split()
		static Path Basename(const Path& path);

		// Change the current directory to the path given
		static bool Changedir(const Path& path);

		// Copy file from one location to another
		bool Copyfile(const Path& oldpath, const Path& newpath, bool overwrite=false);

		// Return the current working directory of the application
		static Path Cwd();

		// Return the directory name of pathname path. This is the first element of
		// the pair returned by passing path to the function split().
		static Path Dirname(const Path& path);

		// Return the directory where the application is located in
		static Path Execdir();

		// Return True if path refers to an existing path or an open file descriptor.
		// Returns False for broken symbolic links. On some platforms, this function may
		// return False if permission is not granted to execute os.stat() on the requested
		// file, even if the path physically exists.
		static bool Exists(const Path& path);

		// Return True if path is an absolute pathname. On Unix, that means it begins
		// with a slash, on Windows that it begins with a (back)slash after chopping 
		// off a potential drive letter.
		static bool IsAbs(const Path& path);

		// Return True if path is an existing directory. This follows symbolic links, so
		// both islink() and isdir() can be true for the same path.
		static bool IsDir(const Path& path);

		// Return True if path is an existing regular file. This follows symbolic links,
		// so both islink() and isfile() can be true for the same path.
		static bool IsFile(const Path& path);

		// Return the result of the make directory operation. It will atempt to make a
		// directroy with the path speified and the result of the operation is returned.
		static bool Makedir(const Path& path);

		// Move a file to a new location on disk. Note that they both need to be valid paths
		static bool Movefile(const Path& oldpath, const Path& newpath);

		// Normalize the case of a pathname. On Unix and Mac OS X, this returns the path 
		// unchanged; on case-insensitive filesystems, it converts the path to lowercase.
		static Path Normcase(const Path& path);

		// Normalize a pathname by collapsing redundant separators and up-level references
		// so that A//B, A/B/, A/./B and A/foo/../B all become A/B. This string manipulation 
		// may change the meaning of a path that contains symbolic links. On Windows, it 
		// converts forward slashes to backward slashes. To normalize case, use normcase().
		static Path Normpath(const Path& path);

		// Return a relative filepath to path either from the current directory or from an optional
		// start directory. This is a path computation: the filesystem is not accessed to confirm
		// the existence or nature of path or start.
		static Path Relpath(const Path& path, const Path& start = Cwd());

		// Remove (delete) the file path. If path is a directory, OSError is raised;
		static bool Remove(const Path& path);

		// Remove (delete) the directory path. Only works when the directory is empty, 
		// otherwise, will return false
		static bool Rmdir(const Path& path);

		static bool Rename(const Path& oldpath, const Path& newpath);

		// Split the pathname path into a pair, (head, tail) where tail is the last pathname
		// component and head is everything leading up to that. The tail part will never contain
		// a slash; if path ends in a slash, tail will be empty. If there is no slash in path, 
		// head will be empty. If path is empty, both head and tail are empty. Trailing slashes
		// are stripped from head unless it is the root (one or more slashes only). 
		// In all cases, join(head, tail) returns a path to the same location as path
		static PathTuple Split(const Path& path);

		static PathTuple Splitdirve(const Path& path);

		// Split the pathname path into a pair (root, ext) such that root + ext == path, 
		// and ext is empty or begins with a period and contains at most one period. 
		// Leading periods on the basename are ignored; splitext('.cshrc') returns ('.cshrc', '').
		static PathTuple Splitext(const Path& path);


		template<typename... Args>
		static Path Join(const Path& one, const Path& two, Args&&... args);
		static Path Join(const Path& path);

		friend std::ostream& operator<<(std::ostream& os, const Path& path);
		operator String&();

		bool isabs();
		bool isdir();
		bool isfile();
		bool exists();

		Path dirname();
		Path basename();

		String value;
	};

	struct PathTuple
	{
		PathTuple(const Path& one, const Path& two)
		{
			tuple[0] = one;
			tuple[1] = two;
		}
		std::array<Path, 2> tuple;
		Path& operator[](u32 index) { return tuple[index]; }
	};

	std::ostream& operator<<(std::ostream& os, const Path& path);

	template<typename... Args>
	Path Path::Join(const Path& one, const Path& two, Args&&... args)
	{
		return Join(one + two, std::forward<Args>(args)...);
	}
}