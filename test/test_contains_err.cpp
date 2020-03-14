#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Returns true if the result is an Err value containing the given value." *
          test_suite("contains_err")) {
  Result<int, std::string> x = Ok(2);
  REQUIRE_FALSE(x.contains_err("Some error message"));

  x = Err(std::string{"Some error message"});
  REQUIRE(x.contains_err("Some error message"));

  x = Err(std::string{"Some other error message"});
  REQUIRE_FALSE(x.contains_err("Some error message"));
}