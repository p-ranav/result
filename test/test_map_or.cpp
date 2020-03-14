#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Applies a function to the contained value (if any), or returns the "
          "provided default (if not)." *
          test_suite("map_or")) {
  Result<std::string, std::string> x = Ok(std::string{"foo"});
  auto y = x.map_or(42, [](auto v) { return v.length(); });
  REQUIRE(y == 3);

  x = Err(std::string{"bar"});
  y = x.map_or(42, [](auto v) { return v.length(); });
  REQUIRE(y == 42);
}