
#include <eden/ecs.hpp>
#include <iostream>

struct health
{
    size_t value = 10;
};

int main()
{
    using namespace eden::ecs;

    director_t d;
    auto ent = d.create();
    auto ents = d.create(100);

    ent.add<health>();

    for (size_t i = 0; i < ents.size(); ++i)
    {
        if (i % 2 == 0 )
            ents[i].destroy();
    }

    std::cout << d.count() << '\n';

    return 0;
}
