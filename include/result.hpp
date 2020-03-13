#include <variant>

namespace result {

template <typename T> struct ok {
  T value;
  ok(T value) : value(value) {}
};

template <typename E> struct err {
  E value;
  err(E value) : value(value) {}
};

template <typename T, typename E>
struct result {

  std::variant<ok<T>, err<E>> value;

  result(const ok<T> &val) : value(val) {}
  result(const err<E> &val) : value(val) {}

  bool is_ok() const { return std::holds_alternative<ok<T>>(value); }
  bool is_err() const { return std::holds_alternative<err<E>>(value); }

  result operator=(const ok<T> &val) {
    value = val;
    return *this;
  }

  result operator=(const err<E> &val) {
    value = val;
    return *this;
  }

  bool contains(const T &this_value) {
    if (is_ok()) {
      return std::visit([&this_value](auto& v) { return v.value == this_value; }, value);
    }
    return false;
  }

  bool contains_err(const E &this_value) {
    if (is_err()) {
      return std::visit([&this_value](auto& v) { return v.value == this_value; }, value);
    }
    return false;
  }  
  
};

}
