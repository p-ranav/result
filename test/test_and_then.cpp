#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE(
    "Calls op if the result is Ok, otherwise returns the Err value of self." *
    test_suite("and_then")) {
  auto sq = [](auto x) { return Ok(x * x); };
  auto err = [](auto x) { return Err(x); };
  REQUIRE(Result<int, int>(Ok(2)).and_then(sq).and_then(sq) == Ok(16));
  REQUIRE(Result<int, int>(Ok(2)).and_then(sq).and_then(err) == Err(4));
  REQUIRE(Result<int, int>(Ok(2)).and_then(err).and_then(sq) == Err(2));
  REQUIRE(Result<int, int>(Err(3)).and_then(sq).and_then(sq) == Err(3));
}