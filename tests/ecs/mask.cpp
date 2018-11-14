
#include "test.hpp"
#include <eden/ecs.hpp>
#include <bitset>

using namespace eden::ecs;

TEST_CASE("Mask")
{
    SECTION("Mask set")
    {
        mask_t mask;
        mask.set(2);
        mask.set(4);
        mask.set(8);
        mask.set(16);

        std::bitset<64> bitset;
        bitset.set(2);
        bitset.set(4);
        bitset.set(8);
        bitset.set(16);

        CHECK(bitset.to_ullong() == mask.get_data()[0]);
    }

    SECTION("And operator")
    {
        mask_t one;
        one.set(1);
        one.set(5);
        one.set(10);

        mask_t two;
        two.set(0);
        two.set(2);
        two.set(4);

        mask_t three;
        three.set(1);
        three.set(3);
        three.set(5);

        mask_t four;

        auto result = two & three;

        CHECK((one & one) == one);
        CHECK((one & two) != one);
        CHECK((two & three) == four);
    }
}
