#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Unwraps a result, yielding the content of an Err." *
          test_suite("unwrap_err")) {
  Result<int, std::string> x = Ok(2);
  try {
    x.unwrap_err();
  } catch (int value) {
    REQUIRE(value == 2);
  }

  x = Err(std::string{"Emergency Failure"});
  REQUIRE(x.unwrap_err() == "Emergency Failure");
}