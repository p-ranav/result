#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

TEST_CASE("Converts from Result<T, E> to std::optional<E>." *
          test_suite("err")) {
  Result<int, std::string> x = Ok(2);
  REQUIRE_FALSE(x.err().has_value());

  x = Err(std::string{"Nothing here"});
  REQUIRE(x.err().value() == "Nothing here");
}