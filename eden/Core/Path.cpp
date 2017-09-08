#include "Precompiled.h"
#include "Path.h"
#include "ScopeGuard.h"

#include <algorithm>
#include <cctype>
#include <locale>

#if defined(EDN_UNIX)
#include <fts.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#endif

#if defined(EDN_LINUX)
#include <sys/sendfile.h>
#endif

#if defined(EDN_MACOSX)
#include <copyfile.h>
#include <sys/socket.h>
#include <sys/uio.h>
#endif

using StringList = std::vector<String>;
const String cur_dir = ".";
const String par_dir = "..";

size_t find_nth(const String& haystack, size_t position, const String& needle, size_t nth)
{
	size_t found = haystack.find(needle, position);
	if (nth == 0) return found;
	if (String::npos == found) return -1;
	return find_nth(haystack, found + 1, needle, nth);
}

size_t find_nth(const String& haystack, const String& needle, u32 nth)
{
	return find_nth(haystack, 0, needle, static_cast<size_t>(nth));
}

inline bool starts_with(const String& str, const String& start)
{
	return !str.compare(0, start.length(), start);
}

inline bool ends_with(const String& str, const String& end)
{
	return std::mismatch(end.rbegin(), end.rend(), str.rbegin()).first == end.rend();
}

inline void ltrim(String& str, char trim)
{
	auto index = str.find_first_not_of(String(1, trim));
	if (String::npos != index)
		str = str.substr(index);
}

inline void rtrim(String& str, char trim)
{
	auto index = str.find_last_not_of(String(1, trim));
	if (String::npos != index)
		str = str.substr(0, index + 1);
}

inline StringList split(const String& str, char delim)
{
	StringList list;
	auto start = static_cast<size_t>(0u);
	auto end = str.find(delim);
	while (end != String::npos)
	{
		list.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find(delim, start);
	}
	list.push_back(str.substr(start, end - start));
	return list;
}

template <typename Iter>
String join(Iter begin, Iter end, std::string const& separator)
{
	std::ostringstream result;
	if (begin != end)
		result << *begin++;
	while (begin != end)
		result << separator << *begin++;
	return result.str();
}

namespace edn
{
	static String special_prefix[] = { "\\\\.\\", "\\\\?\\" };

	Path::Path(const String& value)
		: value(value) {}

	Path::Path(const char* value)
		: value(value) {}

	Path Path::Abspath(const Path& path)
	{
		if (IsAbs(path))
			return Normpath(path);
		return Normpath(Join(Cwd(), path));
	}

	Path Path::Basename(const Path& path)
	{
		return Split(path)[1];
	}

	bool Path::Changedir(const Path& path)
	{
#if defined(EDN_WINDOWS)
		return SetCurrentDirectory(path.value.c_str()) != 0;
#else
		return chdir(path.value.c_str()) != 0;
#endif
	}

	bool Path::Copyfile(const Path& oldpath, const Path& newpath, bool overwrite)
	{
#if defined(EDN_WINDOWS)
		return CopyFile(oldpath.value.c_str(), newpath.value.c_str(), overwrite ? TRUE : FALSE) != 0;
#elif defined(EDN_MACOSX)
		copyfile_state_t s = copyfile_state_alloc();
		auto result = copyfile(oldpath.value.c_str(), newpath.value.c_str(), s, COPYFILE_ALL);
		copyfile_state_free(s);
		return result == 0;
#else
		s32 read_fd;
		s32 write_fd;
		struct stat st;
		off_t offset = 0;

		read_fd = open(oldpath.value.c_str(), O_RDONLY);
		fstat(read_fd, &st);
		write_fd = open(newpath.value.c_str(), O_WRONLY | O_CREAT, st.st_mode);
		sendfile(write_fd, read_fd, &offset, st.st_size);
		close(read_fd);
		close(write_fd);
		return true;
#endif
	}

	Path Path::Cwd()
	{
#if defined(EDN_WINDOWS)
		char path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, path);
		return path;
#else
		char path[PATH_MAX];
		if (getcwd(path, sizeof(path)) != 0)
			return Path();
		return path;
#endif
	}

	Path Path::Dirname(const Path& path)
	{
		return Split(path)[0];
	}

	Path Path::Execdir()
	{
#if defined(EDN_WINDOWS)
		char path[MAX_PATH];
		GetModuleFileName(NULL, path, MAX_PATH);
		return path;
#else
		char result[ PATH_MAX ];
		ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
		return std::string( result, (count > 0) ? count : 0 );
#endif
	}

	bool Path::Exists(const Path& path)
	{
#if defined(EDN_WINDOWS)
		return GetFileAttributes(path.value.c_str()) != INVALID_FILE_ATTRIBUTES;
#else
		struct stat s;
		return stat(path.value.c_str(), &s) == 0
			&& (S_ISDIR(s.st_mode) || S_ISREG(s.st_mode) || S_ISLNK(s.st_mode));
#endif
	}

	bool Path::IsAbs(const Path& path)
	{
#if defined(EDN_WINDOWS)
		return Splitdirve(path)[0].value.length() > 0;
#else
		return path.value[0] == '/';
#endif
	}

	bool Path::IsDir(const Path& path)
	{
#if defined(EDN_WINDOWS)
		DWORD attrib = GetFileAttributes(path.value.c_str());
		return	(attrib != INVALID_FILE_ATTRIBUTES) &&
			(attrib & FILE_ATTRIBUTE_DIRECTORY);
#else
		struct stat s;
		return (stat(path.value.c_str(), &s) == 0 && S_ISDIR(s.st_mode));
#endif
	}

	bool Path::IsFile(const Path& path)
	{
#if defined(EDN_WINDOWS)
		WIN32_FIND_DATA data;
		HANDLE handle = FindFirstFile(path.value.c_str(), &data);
		return handle != INVALID_HANDLE_VALUE;
#else
		struct stat s;
		return (stat(path.value.c_str(), &s) == 0 && S_ISREG(s.st_mode));
#endif

	}

	Path Path::Join(const Path& path)
	{
		return path;
	}

	bool Path::Makedir(const Path& path)
	{
#if defined(EDN_WINDOWS)
		return CreateDirectory(path.value.c_str(), 0) != 0;
#else
		// http://stackoverflow.com/a/5685578
		mode_t mode = 0755;
		auto result = mkdir(path.value.c_str(), mode);

		if (result == 0)
			return true;

		u32 pos;
		switch(errno)
		{
		case ENOENT:
			// parent does not exist, try to create it
			pos = path.value.find_last_of(Seperator);
			if (pos == static_cast<u32>(String::npos))
				return false;
			if (!Makedir(path.value.substr(0, pos)))
				return false;
			return mkdir(path.value.c_str(), mode) == 0;
		case EEXIST:
			// done
			return IsDir(path);
		default:
			return false;
		}
#endif
	}

	bool Path::Movefile(const Path& oldpath, const Path& newpath)
	{
#if defined(EDN_WINDOWS)
		return MoveFile(oldpath.value.c_str(), newpath.value.c_str()) != 0;
#else
/* #error Not Implemented */
        return true;
#endif
	}

	Path Path::Normcase(const Path& path)
	{
		auto value = path.value;
		std::locale loc;
		for (auto i : value)
			i = std::tolower(i, loc);
		return Path(value);
	}

	Path Path::Normpath(const Path& path)
	{
		auto sep = String(1, Seperator);
		for (auto special : special_prefix)
		{
			if (!path.value.compare(0, special.size(), special))
				// in the case of paths with these prefixes :
				// \\.\->device names
				// \\ ? \ -> literal paths
				// do not do any normalization, but return the path unchanged
				return path;
		}
		auto value = path.value;
		std::replace(value.begin(), value.end(), AltSeperator, Seperator);

		auto tuple = Splitdirve(path);
		auto prefix = tuple[0];
		auto p = tuple[1];

		// collapse initial backslashes
		if (starts_with(p, sep))
		{
			prefix.value += Seperator;
			ltrim(p.value, Seperator);
		}

		// Removing ending slash if there is one
		if (ends_with(p, sep))
			rtrim(p.value, Seperator);

		auto comps = split(p, Seperator);
		auto i = 0u;
		while (i < comps.size())
		{
			if (comps[i] == cur_dir || comps[i].length() == String::npos)
				comps.erase(comps.begin() + i);
			else if (comps[i] == par_dir)
			{
				if (i > 0)
				{
					if (comps[i - 1] != par_dir)
					{
						comps.erase(comps.begin() + (i - 1));
						comps.erase(comps.begin() + (i - 1));
						i--;
					}
				}
				else if (i == 0 && ends_with(prefix, sep))
					comps.erase(comps.begin() + i);
				else
					++i;
			}
			else
				++i;
		}

		// If the path is now empty substitute with "."
		if (prefix.value.length() == String::npos && comps.empty())
			comps.push_back(cur_dir);
		return Path(prefix.value + Seperator + join(comps.begin(), comps.end(), sep));
	}

	Path Path::Relpath(const Path& path, const Path& start)
	{
		// Todo: throw an exception
		if (path.value.length() == String::npos)
			printf("Error path is empty");

		auto start_abs = Abspath(start);
		auto path_abs = Abspath(path);

		auto start_split = Splitdirve(start_abs);
		auto path_split = Splitdirve(path_abs);

		// Todo: throw an exception
		if (Normcase(start_split[0]).value != Normcase(path_split[0]).value)
			printf("path is on mount %s, start on mount %s", start_split[0].value.c_str(), path_split[0].value.c_str());

		auto start_list = split(start_split[1], Seperator);
		auto path_list = split(path_split[1], Seperator);

		// Figuring out how much of the filepath is shared by start and path
		auto smaller = start_list.size() < path_list.size() ? start_list.size() : path_list.size();
		u32 i = 0;
		for (; i < smaller; ++i)
		{
			if (Normcase(start_list[i]).value != Normcase(path_list[i]).value)
				break;
		}

		auto nparents = start_list.size() - i;
		std::vector<String> rel_list;

		while (nparents > 0)
		{
			rel_list.push_back(par_dir);
			--nparents;
		}

		auto it = path_list.begin() + i;
		for (; it != path_list.end(); ++it)
			rel_list.push_back(*it);

		return join(rel_list.begin(), rel_list.end(), String(1, Seperator));
	}

	bool Path::Remove(const Path& path)
	{
#if defined(EDN_WINDOWS)
		return DeleteFile(path.value.c_str()) == 0;
#else
		return unlink(path.value.c_str()) == 0;
#endif

	}

	bool Path::Rename(const Path& oldpath, const Path& newpath)
	{
		return rename(oldpath.value.c_str(), newpath.value.c_str()) == 0; // Todo: check if right
	}

	bool Path::Rmdir(const Path& path)
	{
#if defined(EDN_WINDOWS)
		return RemoveDirectory(path.value.c_str()) != 0;
#else
		// http://stackoverflow.com/a/27808574
		char* files[] = {(char*) path.value.c_str(), 0};
		FTS* ftsp = 0;
		FTSENT* curr;
		int ret = 0;

		// FTS_NOCHDIR  - Avoid changing cwd, which could cause unexpected behavior
		//                in multithreaded programs
		// FTS_PHYSICAL - Don't follow symlinks. Prevents deletion of files outside
		//                of the specified directory
		// FTS_XDEV     - Don't cross filesystem boundaries
		ftsp = fts_open(files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, 0);
		if (!ftsp)
			return false;

		auto cleanup = MakeScopeGuard([&]()
		{
			fts_close(ftsp);
		});

		while ((curr = fts_read(ftsp)))
		{
			switch(curr->fts_info)
			{
			case FTS_NS:
			case FTS_DNR:
			case FTS_ERR:
				return false;

			case FTS_DP:
			case FTS_F:
			case FTS_SL:
			case FTS_SLNONE:
			case FTS_DEFAULT:
				if (remove(curr->fts_accpath) < 0)
					ret = -1;
				break;
			}
		}
		return ret == 0;
#endif

	}

	PathTuple Path::Split(const Path& path)
	{
		auto split = Splitdirve(path);
		auto d = split[0].value;
		auto p = split[1].value;

		// set i to the index beyond p's last slash
		auto i = p.length() - 1;
		while (i != 0)
		{
			bool match = false;
			for (auto sep : BothSeperators)
			{
				if (p[i - 1] == sep)
				{
					match = true;
					break;
				}
			}
			if (match)
				break;
			i--;
		}

		// Now the tail has no slash
		auto head = p.substr(0, i);
		auto tail = p.substr(i, p.length() - 1);
		tail.erase(std::remove(tail.begin(), tail.end(), Seperator), tail.end());

		// remove trailing slashes from head, unless it's all slashes
		i = head.length() - 1;
		while (i != 0)
		{
			bool match = false;
			for (auto sep : BothSeperators)
			{
				if (head[i] == sep)
				{
					match = true;
					break;
				}
			}
			if (match)
				break;
			i--;
		}
		auto head2 = head.substr(0, i);
		head = String::npos == head2.length() ? head : head2;
		return PathTuple{ Path(d + Seperator + head), Path(tail) };
	}

	PathTuple Path::Splitdirve(const Path& path)
	{
		auto value = path.value;
		if (path.value.length() > 1)
		{
			if (!value.compare(0, 2, String(2, Seperator)) && !!value.compare(2, 3, String(1, Seperator)))
			{
				// This is a UNC path
				// vvvvvvvvvvvvvvvvvvvv drive letter or UNC path
				// \\machine\mountpoint\directory\etc\...
				//           directory ^^^^^^^^^^^^^^^
				auto idx = value.find_first_of(Seperator, 2);
				if (idx == String::npos)
					return PathTuple{ Path(), path };
				auto idx2 = value.find_first_of(Seperator, idx + 1);

				// A UNC path can't have two slashes in a row
				// (after the initial two)
				if (idx2 == idx + 1)
					return PathTuple{ Path(), path };
				if (idx2 == String::npos)
					idx2 = value.length() - 1;
				return PathTuple{ Path(value.substr(0, idx2)), Path(value.substr(idx2 + 1, value.length() - 1)) };
			}
		}
		if (value[1] == ':')
			return PathTuple{ Path(value.substr(0, 2)), Path(value.substr(3, value.length())) };
		return PathTuple{ Path(), path };
	}

	PathTuple Path::Splitext(const Path& path)
	{
		auto index = path.value.find_last_of('.');
		if (index == String::npos)
			return PathTuple{ path, Path() };
		return PathTuple{ Path(path.value.substr(0, index)), Path(path.value.substr(index, path.value.length())) };
	}

	// Operator overloading

	Path Path::operator+(const Path& rhs) const
	{
		return value + Seperator + rhs.value;
	}

	// Cast operators

	Path::operator String&()
	{
		return value;
	}

	std::ostream& operator<<(std::ostream& os, const Path& path)
	{
		return os << path.value;
	}

	// Member functions
	bool Path::isabs() { return Path::IsAbs(*this); }
	bool Path::isdir() { return Path::IsDir(*this); }
	bool Path::isfile() { return Path::IsFile(*this); }
	bool Path::exists() { return Path::Exists(*this); }

	Path Path::dirname() { return Path::Dirname(*this); }
	Path Path::basename() { return Path::Basename(*this); }
}

