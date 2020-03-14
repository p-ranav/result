#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Returns the contained value or a default" *
          test_suite("unwrap_or_default")) {
  Result<int, std::string> x = Ok(10);
  REQUIRE(x.unwrap_or_default() == 10);

  x = Err(std::string{"foo"});
  REQUIRE(x.unwrap_or_default() == 0);

  Result<bool, float> y = Err(3.14f);
  REQUIRE(y.unwrap_or_default() == false);
}