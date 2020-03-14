#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Maps a Result<T, E> to U by applying a function to a contained Ok value, or a fallback function to a contained Err value." *
          test_suite("map_or_else")) {
  size_t k = 21;
  Result<std::string, std::string> x = Ok(std::string{"foo"});
  auto y = x.map_or_else([&k](auto e) { return k * 2; }, [](auto v) { return v.length(); });
  REQUIRE(y == 3);

  x = Err(std::string{"bar"});
  y = x.map_or_else([&k](auto e) { return k * 2; }, [](auto v) { return v.length(); });
  REQUIRE(y == 42);
}