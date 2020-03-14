#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Unwraps a result, yielding the content of an Err." *
          test_suite("expect_err")) {
  Result<int, std::string> x = Ok(10);
  try {
    x.expect_err("Testing expect_err");
  } catch (std::string& value) {
    REQUIRE(value == "Testing expect_err: 10");
  }

}