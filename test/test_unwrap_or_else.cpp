#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Unwraps a result, yielding the content of an Ok. If the value is an "
          "Err then it calls op with its value." *
          test_suite("unwrap_or_else")) {
  auto count = [](const std::string &str) { return str.length(); };
  REQUIRE(Result<int, std::string>(Ok(2)).unwrap_or_else(count) == 2);
  REQUIRE(
      Result<int, std::string>(Err(std::string{"foo"})).unwrap_or_else(count) ==
      3);
}