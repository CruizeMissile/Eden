#include "UnitTest.h"
#include "Entity/Database.h"
#include "Core/TypeInfo.h"
#include <string>

using namespace edn;

// ------------------------------------------------------------------------------------------------

CREATE_TAG(PositionChanged);
class Position : public Component<Position>
{
public:
	Position(Entity & owner)
		: Component(owner), x(0), y(0), z(0) { }

	Position(Entity & owner, float x, float y, float z)
		: Component(owner), x(x), y(y), z(z) { }

	bool operator==(const Position& other)
	{
		return x == x && y == y && z == z;
	}
	
	String toString() { return "Position"; }

	float x, y, z;
};
EDN_REGISTER_TYPE(Position);

// ------------------------------------------------------------------------------------------------

CREATE_TAG(NameChanged);
class Name : public Component<Name>
{
public:
	Name(Entity & owner)
		: Component(owner), name("Name"){ }

	Name(Entity & owner, std::string name)
		: Component(owner), name(name) { }

	bool operator==(const Name& other) { return name == other.name; }
	String toString() { return "Name"; }
	std::string name;
};
EDN_REGISTER_TYPE(Name);

// ------------------------------------------------------------------------------------------------

class Base : public Component<Base>
{
public:
	Base(Entity & owner) : Component(owner) { }
	String toString() { return "Base"; }
};

// ------------------------------------------------------------------------------------------------

class Alpha : public Base
{
public:
	Alpha(Entity & owner) : Base(owner) { }
	String toString() { return "Alpha"; }
};

class Beta : public Base
{
public:
	Beta(Entity & owner) : Base(owner) { }
	String toString() { return "Beta"; }
};

// ------------------------------------------------------------------------------------------------

TEST_CASE("Entities Interaction with database", "[Entity]")
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

		CHECK(position.GetType() != name.GetType());
	}

	SECTION("Getting Components")
	{
		entity->add<Name>("EDEN");
		auto name = entity->get<Name>();
		CHECK(name.name == "EDEN");
	}

	SECTION("Adding and removing tags")
	{
		entity->addTag(PositionChanged());
		entity->addTag(NameChanged());

		CHECK(entity->hasTag(PositionChanged()));
		CHECK(entity->hasTag(NameChanged()));

		entity->removeTag(NameChanged());
		CHECK(!entity->hasTag(NameChanged()));
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

	SECTION("Component inheritance")
	{
		entity->add<Alpha>();
		CHECK(entity->has<Base>());
		CHECK(entity->has<Alpha>());
		CHECK(!entity->has<Beta>());

		// Testing replace function
		entity->replace<Beta>();
		CHECK(entity->has<Base>());
		CHECK(entity->has<Beta>());
		CHECK(!entity->has<Alpha>());

		// Testing remove
		entity->remove<Beta>();
		CHECK(!entity->has<Base>());
		CHECK(!entity->has<Alpha>());
		CHECK(!entity->has<Beta>());

		// Testing removing something that does not exist
		// This should not affect the entity
		entity->add<Alpha>();
		entity->remove<Beta>();
		CHECK(entity->has<Base>());
		CHECK(entity->has<Alpha>());
		CHECK(!entity->has<Beta>());
	}

	SECTION("Querying Database by type")
	{
		std::vector<Entity::Ptr> entityList;
		
		bool toggle = true;

		for (int i = 0; i < 100; ++i)
		{
			auto e = db.create();
			if (toggle)
				e->add<Name>();
			else
				e->add<Position>();
			entityList.push_back(e);
			toggle = !toggle;
		}

		auto result = toVector(db.where(hasComponent<Position>()));
		CHECK(result.size() == 50);
	}
}