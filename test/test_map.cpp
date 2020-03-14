#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Maps a Result<T, E> to Result<U, E> by applying a function to a "
          "contained Ok value, leaving an Err value untouched." *
          test_suite("map")) {
  Result<int, std::string> x = Ok(2);
  Result<std::string, std::string> y =
      x.map([](auto i) { return std::to_string(i * 2); });
  REQUIRE(y.is_ok());
  REQUIRE_FALSE(y.is_err());
  REQUIRE(y.unwrap() == "4");
  REQUIRE(y == Ok(std::string{"4"}));
}