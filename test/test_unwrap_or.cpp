#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE(
    "Unwraps a result, yielding the content of an Ok. Else, it returns optb." *
    test_suite("unwrap_or")) {
  auto optb = 2;
  Result<int, std::string> x = Ok(9);
  REQUIRE(x.unwrap_or(optb) == 9);

  x = Err(std::string{"error"});
  REQUIRE(x.unwrap_or(optb) == optb);
}