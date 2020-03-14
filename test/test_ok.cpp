#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Converts from Result<T, E> to std::optional<T>." *
          test_suite("ok")) {
  Result<int, std::string> x = Ok(2);
  REQUIRE(x.ok().value() == 2);

  x = Err(std::string{"Nothing here"});
  REQUIRE_FALSE(x.ok().has_value());
}