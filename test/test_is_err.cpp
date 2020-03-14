#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Returns true if the result is Err." * test_suite("is_err")) {
  Result<int, std::string> x = Err(std::string{"Some error message"});
  REQUIRE(x.is_err());

  x = Ok(-3);
  REQUIRE_FALSE(x.is_err());
}