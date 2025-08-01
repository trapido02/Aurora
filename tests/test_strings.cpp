#include <catch2/catch_all.hpp>
#include <string>

TEST_CASE("String operations work", "[string]")
{
    std::string s = "hello";
    REQUIRE(s.size() == 5);
    REQUIRE(s.substr(0, 2) == "he");

    s += " world";
    REQUIRE(s == "hello world");
}
