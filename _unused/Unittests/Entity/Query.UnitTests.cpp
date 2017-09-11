#include "UnitTest.h"
#include "Entity/Query.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace edn;
using namespace edn::Query;
using namespace std;

typedef vector<int> List;

TEST_CASE("Querying logic", "[Query]")
{
    List one = { 1, 2, 4, 6,  7,  8, 10, 12, 17, 22, 26, 30 };
    List two = { 1, 3, 6, 9, 10, 11, 13, 15, 21, 22, 23, 24, 26, 40 };

    SECTION("Intersection")
    {
        List expected = { 1, 6, 10, 22, 26 };
        //auto intersection = make_intersection_range(one, two);
        auto intersection = make_intersection_range(one.begin(), one.end(), two.begin(), two.end());
        auto it = intersection.begin();
        auto end = intersection.end();

        CHECK(it != end);
        CHECK(List(it, end) == expected);
    }

    SECTION("Difference")
    {
        List expected = { 2, 4, 7, 8, 12, 17, 30 };
        //auto difference = make_difference_range(one, two);
        auto difference = make_difference_range(one.begin(), one.end(), two.begin(), two.end());
        auto it = difference.begin();
        auto end = difference.end();

        CHECK(it != end);
        CHECK(List(it, end) == expected);
    }

    SECTION("Union")
    {
        List expected = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11,
            12, 13, 15, 17, 21, 22, 23, 24, 26, 30, 40};
        //auto union_range = make_union_range(one, two);
        auto union_range = make_union_range(one.begin(), one.end(), two.begin(), two.end());
        auto it = union_range.begin();
        auto end = union_range.end();

        CHECK(it != end);
        CHECK(List(it, end) == expected);
    }

    SECTION("Exclusive")
    {
        List expected = { 2, 3, 4, 7, 8, 9, 11, 12, 13, 15, 17, 21, 23, 24, 30, 40 };
        //auto exclusive = make_exclusive_range(one, two);
        auto exclusive = make_exclusive_range(one.begin(), one.end(), two.begin(), two.end());
        auto it = exclusive.begin();
        auto end = exclusive.end();

        CHECK(it != end);
        CHECK(List(it, end) == expected);
    }
}

