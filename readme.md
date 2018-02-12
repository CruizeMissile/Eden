# Eden [![Build Status](https://travis-ci.org/CruizeMissile/Eden.svg?branch=master)](https://travis-ci.org/CruizeMissile/Eden) [![Build status](https://ci.appveyor.com/api/projects/status/99dlxhm5tfkie1ik/branch/master?svg=true)](https://ci.appveyor.com/project/CruizeMissile/eden/branch/master)

Eden is a cross platform c++ game engine. It is archetected around Entity-Component-System and a multi api renderer.

# Quick start
#### Note: Currently Eden is developed on windows and linux (manjaro/arch). Eden uses the lastest and greatest c++ 17 features.

```bash
$ git clone https://github.com/cruizemissile/eden
$ cd eden
$ git submodule update --init --recursive
$ cmake . -Bbuild
$ cmake --build build
```

# Entity samples
```cpp
class Position : public Component<Position>
{
public:
    Position(Entity& owner) : Component(owner), x(0), y(0), z(0) {}
    Position(Entity & owner, float x, float y, float z) 
        : Component(owner), x(x), y(y), z(z) { }

    bool operator==(const Position& other)
    {
        return x == x && y == y && z == z;
    }

    String toString() { return "Position"; }
    float x, y, z;
};

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

int main()
{
    // Ask the entity database to create a new entity
    auto ent = Db.create();

    // Now we can add a position component
    ent->add<Position>(1.f, 2.f, 3.f);
    ent->add<Name>("Eden");

    // Now we can get the component from the entity
    auto position = ent->get<Position>();

    // Wait does the entity have a name component?
    if (ent->has<Name>())
    {
        // No we dont want to have a name, We are anon!
        ent->remove<Name>();
    }

    // We should have one component
    auto count = ent->getComponentCount();

    // by by entity
    db.destroy(ent);

    // Lets make some more entities
    std::vector<Entity::Ptr> entities;
    bool toggle = true;
    for (int i = 0; i < 100; ++i)
    {
        auto e = Db.create();
        if (toggle)
            e->add<Name>();
        else
            e->add<Position>();
        toggle = !toggle;
        entities.push_back(e);
    }
    
    // Now lets query the database for all the names
    for (auto& entity : Db.where(hasComponent<Name>()))
    {
        auto name = entity.get<Name>();
        // ...
    }
}
```

# In development
Eden is currently in development and is not feature complete.

# Dependencies
All Dependencies used under their respective licenses. Copyright is held by their respective owners.
* [Catch](https://github.com/philsquared/Catch)
* [Glew](http://glew.sourceforge.net)
* [Gsl](https://github.com/Microsoft/GSL)
* [Loguru](https://github.com/emilk/loguru)
* [Vulkan](https://www.khronos.org/vulkan/)
