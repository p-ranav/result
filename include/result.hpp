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

// Result is a type that represents either success (Ok) or failure (Err).
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

  // Synonymous with Result.and_(res)
  Result operator&&(const Result<T, E>& res) {
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

  // Returns res if the result is Err, 
  // otherwise returns the Ok value of self.
  Result or_(const Result<T, E>& res) {
    if (is_err())
      return res;
    return ok();
  }

  // Synonymous with Result.or_(res)
  Result operator||(const Result<T, E>& res) {
    if (is_err())
      return res;
    return ok();
  }

  // Calls op if the result is Err, 
  // otherwise returns the Ok value of self.
  template <typename Function>
  Result or_else(Function op) {
    if (is_err())
      return op(unwrap_err());
    return ok();
  }

  // Unwraps a result, yielding the content of an Ok. Else, it returns optb.
  T unwrap_or(T optb) {
    if (is_ok())
      return unwrap();
    return optb;
  }

  // Unwraps a result, yielding the content of an Ok. 
  // If the value is an Err then it calls op with its value.
  template <typename Function>
  T unwrap_or_else(Function op) {
    if (is_ok())
      return unwrap();
    return op(unwrap_err());
  }

  bool contains(const T &this_value) {
    return is_ok() ? unwrap() == this_value : false;
  }

  bool contains_err(const E &this_value) {
    return is_err() ? unwrap_err() == this_value : false;
  }

  // Maps a Result<T, E> to Result<U, E> by 
  // applying a function to a contained Ok value, 
  // leaving an Err value untouched.
  //
  // This function can be used to compose the results of two functions.
  template <typename Function>
  auto map(Function fn) -> Result<decltype(fn(T())), E> {
    if (is_ok())
      return Result<decltype(fn(T())), E>(Ok<decltype(fn(T()))>(fn(unwrap()))); 
    else
      return Result<decltype(fn(T())), E>(Err<E>(unwrap_err()));
  }

  // Applies a function to the contained value (if any), 
  // or returns the provided default (if not).
  template <typename Value, typename Function>
  auto map_or(Value default_value, Function fn) -> decltype(fn(T())) {
    if (is_ok())
      return fn(unwrap());
    else
      return default_value;
  }

  // Maps a Result<T, E> to U by applying a function to a contained Ok value, 
  // or a fallback function to a contained Err value.
  //
  // This function can be used to unpack a successful result while handling an error.
  template <typename ErrorFunction, typename OkFunction>
  auto map_or_else(ErrorFunction err_fn, OkFunction ok_fn) -> decltype(ok_fn(T())) {
    if (is_ok())
      return ok_fn(unwrap());
    else
      return err_fn(unwrap_err());
  }

  // Maps a Result<T, E> to Result<T, F> by 
  // applying a function to a contained Err value, 
  // leaving an Ok value untouched.
  //
  // This function can be used to pass 
  // through a successful result while handling an error.
  template <typename Function>
  auto map_err(Function fn) -> Result<T, decltype(fn(E()))> {
    if (is_err())
      return Result<T, decltype(fn(E()))>(Err<decltype(fn(E()))>(fn(unwrap_err()))); 
    else
      return Result<T, decltype(fn(E()))>(Ok<T>(unwrap()));
  }

  // Unwraps a result, yielding the content of an Ok.
  auto unwrap() const { 
    if (is_ok())
      return ok().value;
    else
      throw err().value;
  }

  // Unwraps a result, yielding the content of an Ok.
  // Panics if the value is an Err, 
  // with a panic message including the passed message, 
  // and the content of the Err.
  T expect(const std::string &msg) {
    if (is_ok())
      return unwrap();
    throw msg + ": " + std::to_string(unwrap_err());
  }

  // Unwraps a result, yielding the content of an Err.
  auto unwrap_err() const {
    if (is_err())
      return err().value;
    else 
      throw ok().value;
  }

  // Unwraps a result, yielding the content of an Err.
  // Panics if the value is an Ok, 
  // with a panic message including the passed message, 
  // and the content of the Ok.
  E expect_err(const std::string &msg) {
    if (is_err())
      return unwrap_err();
    throw msg + ": " + std::to_string(unwrap());
  }

  // Returns the contained value or a default
  // if Ok, returns the contained value, 
  // otherwise if Err, returns the default value for that type.
  T unwrap_or_default() const {
    if (is_ok())
      return unwrap();
    else 
      return T();
  }

};

}
