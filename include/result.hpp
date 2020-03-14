#include <iostream>
#include <variant>

namespace result {

template <typename T> struct Ok {
  T value;
  Ok(T value) : value(value) {}
};

template <typename E> struct Err {
  E value;
  Err(E value) : value(value) {}
};

template <typename T, typename E>
struct Result {

  std::variant<Ok<T>, Err<E>> value;

  Result(const Ok<T> &val) : value(val) {}
  Result(const Err<E> &val) : value(val) {}

  Result operator=(const Ok<T> &val) {
    value = val;
    return *this;
  }

  Result operator=(const Err<E> &val) {
    value = val;
    return *this;
  }

  bool operator==(const Ok<T> &val) {
    return is_ok() && unwrap() == val.value;
  }

  bool operator==(const Err<E> &val) {
    return is_err() && unwrap_err() == val.value;
  }

  bool is_ok() const { return std::holds_alternative<Ok<T>>(value); }
  bool is_err() const { return std::holds_alternative<Err<E>>(value); }

  auto ok() const { return std::get<0>(value); }
  auto err() const { return std::get<1>(value); }

  // Returns res if the result is Ok, otherwise returns the Err value of self.
  Result and_(const Result<T, E>& res) {
    if (is_ok())
      return res;
    return err();
  }

  // Calls op if the result is Ok, otherwise returns the Err value of self.
  // This function can be used for control flow based on Result values.
  template <typename Function>
  Result and_then(Function op) {
    if (is_ok())
      return op(unwrap());
    return err();
  }

  auto unwrap() const { 
    if (is_ok())
      return ok().value;
    else
      throw err().value;
  }

  auto unwrap_err() const {
    if (is_err())
      return err().value;
    else 
      throw ok().value;
  }

  bool contains(const T &this_value) {
    return is_ok() ? unwrap() == this_value : false;
  }

  bool contains_err(const E &this_value) {
    return is_err() ? unwrap_err() == this_value : false;
  }

  template <typename Function>
  auto map(Function fn) -> Result<decltype(fn(T())), E> {
    if (is_ok())
      return Result<decltype(fn(T())), E>(Ok<decltype(fn(T()))>(fn(unwrap()))); 
    else
      return Result<decltype(fn(T())), E>(Err<E>(unwrap_err()));
  }

  template <typename Value, typename Function>
  auto map_or(Value default_value, Function fn) -> decltype(fn(T())) {
    if (is_ok())
      return fn(unwrap());
    else
      return default_value;
  }
  
};

}
