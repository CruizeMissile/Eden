#include "UnitTest.h"
#include "Entity/Database.h"
#include "Core/TypeInfo.h"
#include <string>

using namespace edn;

class Position : public Component<Position>
{
public:
	Position(float x, float y, float z)
		: x(x), y(y), z(z) { }

	bool operator==(const Position& other)
	{
		return x == x && y == y && z == z;
	}
	
	String toString() { return "Position"; }

	float x, y, z;
};
EDN_REGISTER_TYPE(Position);

class Name : public Component<Name>
{
public:
	Name(std::string name)
		: name(name) { }

	bool operator==(const Name& other) { return name == other.name; }
	String toString() { return "Name"; }
	std::string name;
};
EDN_REGISTER_TYPE(Name);

TEST_CASE("Entity Component System", "[Entity]")
{
	auto & db = Database::Instance();
	auto entity = db.create();
	
	SECTION("Adding and removing components")
	{
		entity->add<Position>(1.f, 2.f, 3.f);
		entity->remove<Position>();
		entity->add<Position>(3.f, 2.f, 1.f);
		entity->add<Name>("This is the name Component");

		auto position = entity->get<Position>();
		auto name = entity->get<Name>();

		CHECK(position->getType() != name->getType());
	}

	SECTION("Entity leaving scope")
	{
		u32 pre_scope_size = db.getEntityCount();
		u32 inside_scope_size;

		{
			auto scope = db.create();
			scope->add<Name>("This is the scope name");
			inside_scope_size = db.getEntityCount();
		}

		u32 post_scope_size = db.getEntityCount();
		CHECK(pre_scope_size != inside_scope_size);
		CHECK(pre_scope_size == post_scope_size);
	}
}