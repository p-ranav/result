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

  enum class state {
    ok,
    err
  };
  
  state state_;
  std::variant<ok<T>, err<E>> value;

  result(::ok<T> val) : state_(state::ok), value(val) {}
  result(::err<E> val) : state_(state::err), value(val) {}

  bool is_ok() const { return state_ == state::ok; }
  bool is_err() const { return state_ == state::err; }

  result operator=(::ok<T> val) {
    value = val;
    return *this;
  }

  result operator=(::err<E> val) {
    value = val;
    return *this;
  }

  bool contains(T value) {
    return state_ == state::ok && std::get<ok<T>>(value).value == value;
  }
  
};

}
