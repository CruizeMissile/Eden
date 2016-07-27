#include "UnitTest.h"

#include "Core/TypeInfo.h"

class TestCase;

EDN_REGISTER_TYPE(TestCase);


TEST_CASE("Registration of type info", "[TypeInfo]")
{
	auto name = TypeInfo<TestCase>::name;
	auto hash = TypeInfo<TestCase>::hash;

	const char * check_name= "TestCase";
	auto check_hash = EDN_HASH(check_name);

	CHECK(name == check_name);
	CHECK(hash == check_hash);
}