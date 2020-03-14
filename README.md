<p align="center">
  <img height="70" src="img/logo.png"/>  
</p>

## Highlights
* `Result<T, E>` is a type that represents either success (`Ok`) or failure (`Err`)
* Inspired by Rust `std::result::Result`
* Requires C++17
* MIT License

## Quick Start

```bash
git clone https://github.com/p-ranav/result
cd result
mkdir build && cd build
cmake -DRESULT_BUILD_TESTS=ON ..
make
./test/test
```

Simply include `result/result.hpp` and you're good to go. `Result<T, E>` has two variants:

* `Ok(value)` which indicates that the operation succeeded, and wraps the value returned by the operation. (`value` has type `T`)
* `Err(why)`, which indicates that the operation failed, and wraps why, which (hopefully) explains the cause of the failure. (`why` has type `E`)

```cpp
#include <iostream>
#include <string>
#include "result.hpp"
using namespace result;

auto Div(double x, double y) -> Result<double, std::string> {
  if (y == 0.0)
    return Err(std::string{"Division by zero"});
  else
    return Ok(x / y);
}

int main() {
  auto good_result = Div(100.0, 25.0);
  if (good_result.is_ok()) {
    // Continue with result
    std::cout << "Good Result: " << good_result.unwrap() << std::endl;
  }

  auto bad_result = Div(100.0, 0.0);
  if (bad_result.is_err()) {
    auto reason = bad_result.unwrap_err(); // "Division by zero"
    std::cout << "Bad Result: " << reason << std::endl;
  }
}
```

At a module level, creating aliases can be particularly helpful. Errors found in a specific module often have the same `Err` type, so a single alias can succinctly define all associated `Results`. Using `Result.and_then`, one can chain operations and terminate early as needed:

```cpp
#include <iostream>
#include <cmath>
#include <result/result.hpp>
using namespace result;

enum class MathError {
  DivisionByZero,
  NonPositiveLogarithm,
  NegativeSquareRoot,
};

using MathResult = Result<double, MathError>;

auto Div(double x, double y) -> MathResult {
  if (y == 0.0)
    return Err(MathError::DivisionByZero);
  else
    return Ok(x / y);
}

auto Sqrt(double x) -> MathResult {
  if (x < 0.0) 
    return Err(MathError::NegativeSquareRoot);
  else
    return Ok(sqrt(x));
}

auto Log(double x) -> MathResult {
  if (x <= 0.0)
    return Err(MathError::NonPositiveLogarithm);
  else
    return Ok(log(x));
}

auto Op(double x, double y) -> double {
  return Div(x, y)
    .and_then(Sqrt)
    .and_then(Log)
    .unwrap();
}

int main() {
  std::cout << Op(100.0, 25.0) << std::endl; // 0.693147
}
```

## `map` for `Result`

`map` maps a `Result<T, E>` to `Result<U, E>` by applying a function to a contained `Ok` value, leaving an `Err` value untouched. The following example implements a `string -> int` parser function and then uses it's results to multiply two numbers. The multiplication will proceed if both numbers are parsed correctly from their string representation. Else, the resultant error is propagated. 

```cpp
#include <iostream>
#include <string>
#include "result.hpp"
using namespace result;

Result<int, std::string> 
parse(const std::string &message) {
  try {
    return Ok(std::stoi(message));
  } catch (std::invalid_argument& err) {
    return Err(std::string(err.what()));
  }
}

Result<int, std::string> 
multiply(const std::string &first_string, const std::string &second_string) {
  return parse(first_string).and_then([&](auto first) {
    return parse(second_string).map([&](auto second) { return first * second; });
  });
}

int main() {
  // This still presents a reasonable answer
  auto twenty = multiply("10", "2");
  std::cout << twenty << std::endl;   // prints "20"

  auto tt = multiply("t", "2");
  std::cout << tt << std::endl;       // prints "stoi: no conversion"
}
```
