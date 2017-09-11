#include "UnitTest.h"
#include "Core/Types.h"
#include "Core/ct/static_if.h"
#include <cstddef>

volatile bool banana_eaten = false;
volatile bool apple_eaten = false;
volatile u32 else_count = 0;

using namespace edn;

struct banana
{
    banana() {}
    void peel()
    {
    }
    void eat_banana()
    {
        banana_eaten = true;
    }
};

struct apple
{
    apple() {}
    void peel()
    {
    }
    void eat_apple()
    {
        apple_eaten = true;
    }
};

struct chestnut
{
    chestnut() {}
    void peel()
    {
    }
};

template <typename T>
using is_banana = std::integral_constant<bool, std::is_same<banana, T>::value>;

template <typename T>
using is_apple = std::integral_constant<bool, std::is_same<apple, T>::value>;

template <typename T>
void eat_fruit1(T fruit)
{
    fruit.peel();

    ct::static_if(is_banana<T>{})
        .then([](auto& f)
    {
        f.eat_banana();
    })
        .else_if(is_apple<T>{})
        .then([](auto& f)
    {
        f.eat_apple();
    })(fruit);
}

template<typename T>
void eat_fruit2(T fruit)
{
    fruit.peel();

    ct::static_if(is_banana<T>{})
        .then([](auto& f)
    {
        f.eat_banana();
    })(fruit);

    ct::static_if(is_apple<T>{})
        .then([](auto& f)
    {
        f.eat_apple();
    })(fruit);
}

template <typename T>
void eat_fruit3(T fruit)
{
    fruit.peel();

    ct::static_if(is_banana<T>{})
        .then([](auto& f)
    {
        f.eat_banana();
    })
        .else_([](auto&)
    {
        ++else_count;
    })(fruit);

    ct::static_if(is_apple<T>{})
        .then([](auto& f)
    {
        f.eat_apple();
    })
        .else_([](auto&)
    {
        ++else_count;
    })(fruit);
}


TEST_CASE("static_if")
{
    banana_eaten = apple_eaten = false;
    else_count = 0;

    SECTION("eat_fruit1")
    {
        eat_fruit1(chestnut{});
        CHECK(banana_eaten == false);
        CHECK(apple_eaten == false);

        eat_fruit1(banana{});
        CHECK(banana_eaten == true);
        CHECK(apple_eaten == false);

        eat_fruit1(apple{});
        CHECK(banana_eaten == true);
        CHECK(apple_eaten == true);
    }

    SECTION("eat_fruit1")
    {
        eat_fruit2(chestnut{});
        CHECK(banana_eaten == false);
        CHECK(apple_eaten == false);

        eat_fruit1(banana{});
        CHECK(banana_eaten == true);
        CHECK(apple_eaten == false);

        eat_fruit1(apple{});
        CHECK(banana_eaten == true);
        CHECK(apple_eaten == true);
    }

    SECTION("eat_fruit1")
    {
        eat_fruit3(chestnut{});
        CHECK(banana_eaten == false);
        CHECK(apple_eaten == false);
        CHECK(else_count == 2);

        else_count = 0;
        eat_fruit3(banana{});
        CHECK(banana_eaten == true);
        CHECK(apple_eaten == false);
        CHECK(else_count == 1);

        else_count = 0;
        eat_fruit3(apple{});
        CHECK(banana_eaten == true);
        CHECK(apple_eaten == true);
        CHECK(else_count == 1);
    }
}
