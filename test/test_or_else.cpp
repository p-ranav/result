#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Calls op if the result is Err, otherwise returns the Ok value of self." *
          test_suite("or_else")) {
  auto sq = [](auto x) { return Ok(x * x); };
  auto err = [](auto x) { return Err(x); };
  REQUIRE(Result<int, int>(Ok(2)).or_else(sq).or_else(sq) == Ok(2));
  REQUIRE(Result<int, int>(Ok(2)).or_else(err).or_else(sq) == Ok(2));
  REQUIRE(Result<int, int>(Err(3)).or_else(sq).or_else(err) == Ok(9));
  REQUIRE(Result<int, int>(Err(3)).or_else(err).or_else(err) == Err(3));
}