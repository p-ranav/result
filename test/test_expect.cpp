#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Unwraps a result, yielding the content of an Ok." *
          test_suite("expect")) {
  Result<int, std::string> x = Err(std::string{"emergency failure"});
  try {
    x.expect("Testing expect");
  } catch (const std::string& err) {
    REQUIRE(err == "Testing expect: emergency failure");
  }
}