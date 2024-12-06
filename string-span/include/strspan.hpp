#ifndef _STRSPAN_HPP_
#define _STRSPAN_HPP_

#include <cstring>
#include <string_view>
#include <type_traits>

namespace strspan {

template <class T>
concept StringLike = std::is_convertible_v<T, std::string_view>;

template <class T>
concept CharBasedString = StringLike<T> && (std::is_array_v<T> || std::is_pointer_v<T>);

namespace detail {
template <StringLike T>
std::size_t size_of_strlike(T s) {
  if constexpr (CharBasedString<T>) {
    return std::strlen(s);
  } else {
    return s.size();
  }
}
}  // namespace detail

template <StringLike T>
class StrSpan final {
 private:
  T& _str;

  auto _str_begin() const {
    if constexpr (CharBasedString<T>) {
      return _str;
    } else {
      return _str.begin();
    }
  }

 public:
  const std::size_t begin_idx;
  const std::size_t end_idx;
  const std::size_t size;

  StrSpan(T& str, std::size_t begin_idx = 0, std::size_t end_idx = 0)
      : _str(str)
      , begin_idx(begin_idx)
      , end_idx(end_idx ? end_idx : detail::size_of_strlike(str))
      , size(end_idx - begin_idx) {}

  auto begin() const {
    return _str_begin() + begin_idx;
  }

  auto end() const {
    return _str_begin() + end_idx;
  }

  auto& operator[](std::size_t i) const {
    return *(_str_begin() + i);
  }
};

}  // namespace strspan

#endif  // _STRSPAN_HPP_
