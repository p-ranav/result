<p align="center">
  <img height="70" src="img/logo.png"/>  
</p>

## Highlights
* `Result<T, E>` is a type that represents either success (`Ok`) or failure (`Err`)
* Inspired by Rust `std::result::Result`
* Requires C++17
* MIT License

## Quick Start

Simply include `result/result.hpp` and you're good to go. 

`Result<T, E>` has two variants:

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
    std::cout << "Good Reuslt: " << good_result.unwrap() << std::endl;
  }

  auto bad_result = Div(100.0, 0.0);
  if (bad_result.is_err()) {
    auto reason = bad_result.unwrap_err(); // "Division by zero"
    std::cout << "Bad Result: " << reason << std::endl;
  }
}
```

At a module level, creating aliases can be particularly helpful. Errors found in a specific module often have the same `Err` type, so a single alias can succinctly define all associated Results.

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
