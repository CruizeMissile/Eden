#include "UnitTest.h"
#include "Core/Path.h"
#include <iostream>

using namespace edn; 
using namespace std;

#define SPLIT "Split"
#define SPLIT_DIRVES "Split Drives"
#define SPLIT_TEXT "Split Text"
#define NORMAILZE "Normalize Path"
#define JOIN "Join Path"
#define RELPATH "Relative Path"

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

TEST_CASE("Path")
{
	auto exec_dir = Path::Execdir();
	auto cwd_dir = Path::Cwd();

	CHECK(Path::Exists(exec_dir));
	CHECK(Path::IsAbs(exec_dir));
	CHECK(!Path::IsDir(exec_dir));
	CHECK(Path::IsFile(exec_dir));

	SECTION(JOIN)
	{
		auto result = Path::Join("D:", String("a"), "b", "c", "d", String(".."), "e");
		
		std::vector<String> list = { "D:", "a", "b", "c", "d", "..", "e" };
		auto compare = join(list.begin(), list.end(), String(1, Path::Seperator));
		CHECK(result.value == compare);
	}
}

TEST_CASE("DRIVE_Paths")
{
	auto path = Path::Join("D:", "a", "b", "c");

	SECTION(NORMAILZE)
	{
		path = Path::Join("D:", "a", "b", "c", "d", "..", "..", "e", "f", "..", "h", "i");
		auto result = Path::Normpath(path);
		CHECK(result.value == Path::Join("D:", "a", "b", "e", "h", "i").value);
	}

	SECTION(RELPATH)
	{
		auto result = Path::Relpath(Path::Join("D:", "a", "b", "e", "f"), path);
		CHECK(result.value == Path::Join("..", "e", "f").value);
	}

	SECTION(SPLIT)
	{
		auto result = Path::Split(path);
		CHECK(result[0].value == Path::Join("D:", "a", "b").value);
		CHECK(result[1].value == "c");

		CHECK(result[0].value == Path::Dirname(path).value);
		CHECK(result[1].value == Path::Basename(path).value);
	}

	SECTION(SPLIT_DIRVES)
	{
		auto result = Path::Splitdirve(path);
		CHECK(result[0].value == "D:");
		CHECK(result[1].value == Path::Join("a", "b", "c").value);

		path = Path::Join("a", "b", "c", "d");
		result = Path::Splitdirve(path);
		CHECK(result[0].value == "");
		CHECK(result[1].value == Path::Join("a", "b", "c", "d").value);
	}

	SECTION(SPLIT_TEXT)
	{
		auto result = Path::Splitext(path);
		CHECK(result[0].value == Path::Join("D:", "a", "b", "c").value);
		CHECK(result[1].value == "");

		result = Path::Splitext(Path::Join("a", "b", "c.txt"));
		CHECK(result[0].value == Path::Join("a", "b", "c").value);
		CHECK(result[1].value == ".txt");
	}
}

TEST_CASE("UNC_Paths")
{
	auto path = Path("\\\\machine\\mountpoint\\directory\\etc\\");

	SECTION(SPLIT_DIRVES)
	{
		auto result = Path::Splitdirve(path);
		
		CHECK(result[0].value == "\\\\machine\\mountpoint");
		CHECK(result[1].value == "directory\\etc\\");
	}

	SECTION(SPLIT)
	{
		auto result = Path::Split(path);
		
		CHECK(result[0].value == "\\\\machine\\mountpoint\\directory");
		CHECK(result[1].value == "etc");
		
		CHECK(result[0].value == Path::Dirname(path).value);
		CHECK(result[1].value == Path::Basename(path).value);
	}

	SECTION(SPLIT_TEXT)
	{
		auto result = Path::Splitext(path);
		
		CHECK(result[0].value == "\\\\machine\\mountpoint\\directory\\etc\\");
		CHECK(result[1].value == "");
	}

	SECTION(NORMAILZE)
	{
		path = Path("\\\\machine\\mountpoint\\a\\b\\c\\d\\..\\..\\e\\f\\..\\h\\i\\");
		auto result = Path::Normpath(path);

		CHECK(result.value == "\\\\machine\\mountpoint\\a\\b\\e\\h\\i");
	}
}