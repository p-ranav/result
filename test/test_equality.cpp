#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Compare result objects for equality" *
          test_suite("operator==")) {
  Result<int, std::string> foo = Ok(0);
  Result<int, std::string> bar = Ok(0);  
  REQUIRE(foo == bar);
  REQUIRE_FALSE(foo != bar);

  bar = Err(std::string{"error"});
  REQUIRE_FALSE(foo == bar);
  REQUIRE(foo != bar);
}