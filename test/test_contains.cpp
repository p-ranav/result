#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Returns true if the result is an Ok value containing the given value." *
          test_suite("contains")) {
  Result<int, std::string> x = Ok(2);
  REQUIRE(x.contains(2));

  x = Ok(3);
  REQUIRE_FALSE(x.contains(2));

  x = Err(std::string{"Some error message"});
  REQUIRE_FALSE(x.contains(2));
}