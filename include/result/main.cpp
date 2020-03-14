#include <iostream>
#include <cmath>
#include "result.hpp"
using namespace result;

enum class FooError {
  Bad,
};

enum class BarError {
  Horrible,
};

int main() {
  Result<Result<int, FooError>, BarError> res = Ok(Result<int, FooError>{Err(FooError::Bad)});

  auto value = res
    // `map` will only call the closure for `Ok(Result<int, FooError>)`
    .map([&](Result<int, FooError> res) {
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
    })

  std::cout << value.unwrap() << std::endl; // "bad FooError"
}

/*


let res: Result<Result<i32, FooError>, BarError> = Ok(Err(FooError::Bad));

let value = res

    // `and_then` will only call the closure for `Ok(Result<usize, &'static str>)`
    // Note: this is result of our first `map` above
    .and_then(|n: Result<usize, &'static str>| {
        // transform (flatten) `Ok(Result<usize, &'static str>)` into `Result<usize, &'static str>`
        // this may be `Ok(Ok(usize))` _or_ `Ok(Err(&'static str))`
        n
    })

    // `and_then` will only call the closure for `Ok(usize)`
    .and_then(|n: usize| {
        // transform Ok(usize) into Ok(usize * 2)
        Ok(n * 2)
    });

assert_eq!(Err("bad FooError"), value);
}
*/