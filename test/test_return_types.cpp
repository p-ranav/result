#include <doctest.hpp>
#include <result/result.hpp>
using namespace result;

using doctest::test_suite;

enum class FooError {
  Bad,
};

enum class BarError {
  Horrible,
};

TEST_CASE("Different Return Types" *
          test_suite("map")) {
  Result<Result<int, FooError>, BarError> res = Ok(Result<int, FooError>(Err(FooError::Bad)));

  auto value = res
    // `map` will only call the closure for `Ok(Result<int, FooError>)`
    .map([](Result<int, FooError> res) {
      // transform `Ok(Result<int, FooError>)` into `Ok(Result<size_t, std::string>)`
      return res
        // transform int to size_t
        .map([](int n) { return static_cast<size_t>(n); })

        // transform `FooError` into std::string
        .map_err([](FooError e) { return std::string{"bad FooError"}; });
    })

    // `map_err` will only call the closure for `Err(BadError)
    .map_err([](BarError e) {
      // transform `BarError` into std::string
      return std::string{"horrible BarError"};
    });

  // value now has type Result<Result<size_t, std::string>, std::string>
  REQUIRE(value.unwrap() == std::string{"bad FooError"});
}