#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Returns res if the result is Err, otherwise returns the Ok value of self." *
          test_suite("or")) {
  Result<int, std::string> x = Ok(2);
  Result<int, std::string> y = Err(std::string{"late error"}); 
  REQUIRE(x.or_(y) == Ok(2));

  x = Err(std::string{"early error"});
  y = Ok(2);
  REQUIRE(x.or_(y) == Ok(2));

  x = Err(std::string{"not a 2"});
  y = Err(std::string{"late error"});
  REQUIRE(x.or_(y) == Err(std::string{"late error"}));

  x = Ok(2);
  y = Ok(100);
  REQUIRE(x.or_(y) == Ok(2));
}

TEST_CASE("Returns res if the result is Ok, otherwise returns the Err value of self." *
          test_suite("operator||")) {
  Result<int, std::string> x = Ok(2);
  Result<int, std::string> y = Err(std::string{"late error"}); 
  REQUIRE((x || y) == Ok(2));

  x = Err(std::string{"early error"});
  y = Ok(2);
  REQUIRE((x || y) == Ok(2));

  x = Err(std::string{"not a 2"});
  y = Err(std::string{"late error"});
  REQUIRE((x || y) == Err(std::string{"late error"}));

  x = Ok(2);
  y = Ok(100);
  REQUIRE((x || y) == Ok(2));
}