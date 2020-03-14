#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Returns true if the result is Ok." *
          test_suite("is_ok")) {
  Result<int, std::string> x = Ok(-3);
  REQUIRE(x.is_ok());
}