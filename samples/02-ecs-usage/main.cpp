
#include <eden/ecs.hpp>
#include <iostream>

int main()
{
    eden::ecs::internal::pool<int> pool(8192);
    eden::ecs::mask_t mask(256);
    mask.set(200);

    for (int i = 0; i < mask.length(); ++i)
    {
        if (i % 2 == 0)
            mask.set(i);
    }

    std::cout << mask.to_string() << '\n';
    return 0;
}
