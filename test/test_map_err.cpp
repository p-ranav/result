#include <doctest.hpp>
#include <result/result.hpp>
#include <string>
using namespace result;

using doctest::test_suite;

TEST_CASE("Maps a Result<T, E> to Result<T, F> by applying a function to a contained Err value, leaving an Ok value untouched." *
          test_suite("map_err")) {
  auto stringify = [](auto x) { return "error code: " + std::to_string(x); };

  Result<int, int> x = Ok(2);
  REQUIRE(x.map_err(stringify) == Ok(2));

  x = Err(13);
  REQUIRE(x.map_err(stringify) == Err(std::string{"error code: 13"}));

}