#include <catch2/catch_all.hpp>
#include <cmath>

TEST_CASE("Basic math sanity checks", "[math]")
{
    REQUIRE(2 + 2 == 4);
    REQUIRE(std::sqrt(9.0) == Catch::Approx(3.0));
    REQUIRE(std::pow(2.0, 3.0) == Catch::Approx(8.0));
    FAIL("This test should fail");
}