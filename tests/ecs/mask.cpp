
#include "test.hpp"
#include <eden/ecs.hpp>
#include <bitset>

using namespace eden::ecs;

TEST_CASE("Dynamic Bitset")
{
    SECTION("Construct")
    {
        SECTION("Default")
        {
            constexpr size_t bit_size = 16;
            dynamic_bitset<bit_size> bs;
            CHECK(bs.count() == 0);
            CHECK(bs.size() == bit_size);
            CHECK(!bs.all());
            CHECK(!bs.any());
            CHECK(bs.none());
        }

        SECTION("Value")
        {
            constexpr size_t bit_size = 8;
            dynamic_bitset<bit_size> bs(21);
            CHECK(bs.count() == 3);
            CHECK(bs.size() == bit_size);
            CHECK(!bs.all());
            CHECK(bs.any());
            CHECK(!bs.none());
            CHECK(bs.test(0));
            CHECK(!bs.test(1));
            CHECK(bs.test(2));
            CHECK(!bs.test(3));
            CHECK(bs.test(4));
            CHECK(bs.to_string() == "00010101");
        }
    }

    SECTION("Accessors")
    {
        constexpr size_t bit_size = 32;
        constexpr size_t bit_value = 1234;
        dynamic_bitset<bit_size> bs(bit_value);
        CHECK(!bs[0]);
        CHECK(bs[1]);
        CHECK(!bs[2]);
        CHECK(!bs[3]);
        CHECK(bs[4]);
        CHECK(!bs[5]);
        CHECK(bs.test(6));
        CHECK(bs.test(7));
        CHECK(!bs.test(8));
        CHECK(!bs.test(9));
        CHECK(bs.test(10));
        CHECK(!bs.test(11));
        CHECK(!bs.test(12));

        CHECK(bs.count() == 5);
        CHECK(bs.size() == bit_size);

        CHECK_THROWS_AS(bs.test(32), std::out_of_range);
    }

    SECTION("Setting Values")
    {
        constexpr size_t bit_size = 32;
        dynamic_bitset<bit_size> bs;
        bs.set(0);
        bs.set(bit_size + 1);

        CHECK(bs[0]);
        CHECK(!bs[1]);
        CHECK(!bs[32]);
        CHECK(bs[33]);
        CHECK(!bs[34]);

        auto cp = bs;
        CHECK(cp == bs);

        bs.flip();
        CHECK(cp != bs);    
        for (size_t i = 0 ; i < bs.size(); ++i)
            CHECK(bs[i] != cp[i]);

        bs.reset();
        CHECK(bs.none());

        cp.set();
        CHECK(cp.all());
    }

    SECTION("Logical Operators")
    {
        constexpr size_t bit_size = 8;
        SECTION("And")
        {
            {
                dynamic_bitset<bit_size> bs1(1);
                dynamic_bitset<bit_size> bs2(2);
                dynamic_bitset<bit_size> bs3(4);
                dynamic_bitset<bit_size> answer(7);

                auto result = bs1 & bs2 & bs3;
                CHECK(result == answer);
            }
        }
    }
}
