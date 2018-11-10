
#include <eden/ecs.hpp>
#include <iostream>

int main()
{
    using namespace eden::ecs;

    director_t d;
    auto ent = d.create();
    auto ents = d.create(100);

    for (int i = 0; i < ents.size(); ++i)
    {
        if (i % 2 == 0 )
            ents[i].destroy();
    }

    std::cout << d.count() << '\n';

    return 0;
}
