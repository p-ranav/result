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

  bool is_ok() const { return std::holds_alternative<Ok<T>>(value); }
  bool is_err() const { return std::holds_alternative<Err<E>>(value); }

  auto ok() const { return std::get<0>(value); }
  auto err() const { return std::get<1>(value); }

  bool contains(const T &this_value) {
    return is_ok() ? ok().value == this_value : false;
  }

  bool contains_err(const E &this_value) {
    return is_err() ? err().value == this_value : false;
  }

  template <typename Function>
  auto map(Function fn) -> Result<decltype(fn(T())), E> {
    if (is_ok())
      return std::visit([&fn](auto &v) { 
        return Result<decltype(fn(T())), E>(Ok<decltype(fn(T()))>(fn(v.value))); 
      }, value);
    else
      return std::visit([&fn](auto &v) { 
        return Result<decltype(fn(T())), E>(Err<E>(v.value)); 
      }, value);
  }
  
};

}
