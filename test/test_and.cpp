#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Returns res if the result is Ok, otherwise returns the Err value of "
          "self." *
          test_suite("and")) {
  Result<int, std::string> x = Ok(2);
  Result<std::string, std::string> y = Err(std::string{"late error"});
  REQUIRE(x.and_(y) == Err(std::string{"late error"}));

  x = Err(std::string{"early error"});
  y = Ok(std::string{"foo"});
  REQUIRE(x.and_(y) == Err(std::string{"early error"}));

  x = Err(std::string{"not a 2"});
  y = Err(std::string{"late error"});
  REQUIRE(x.and_(y) == Err(std::string{"not a 2"}));

  x = Ok(2);
  y = Ok(std::string{"different result type"});
  REQUIRE(x.and_(y) == Ok(std::string{"different result type"}));
}

TEST_CASE("Returns res if the result is Ok, otherwise returns the Err value of "
          "self." *
          test_suite("operator&&")) {
  Result<int, std::string> x = Ok(2);
  Result<std::string, std::string> y = Err(std::string{"late error"});
  REQUIRE((x && y) == Err(std::string{"late error"}));

  x = Err(std::string{"early error"});
  y = Ok(std::string{"foo"});
  REQUIRE((x && y) == Err(std::string{"early error"}));

  x = Err(std::string{"not a 2"});
  y = Err(std::string{"late error"});
  REQUIRE((x && y) == Err(std::string{"not a 2"}));

  x = Ok(2);
  y = Ok(std::string{"different result type"});
  REQUIRE((x && y) == Ok(std::string{"different result type"}));
}