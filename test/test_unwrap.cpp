#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Unwraps a result, yielding the content of an Ok." *
          test_suite("unwrap")) {
  Result<int, std::string> x = Ok(2);
  REQUIRE(x.unwrap() == 2);

  x = Err(std::string{"Emergency Failure"});
  try {
    x.unwrap();
  } catch (std::string& err) {
    REQUIRE(err == "Emergency Failure");
  }

}