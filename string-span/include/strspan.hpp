#ifndef _STRSPAN_HPP_
#define _STRSPAN_HPP_

#include <cstring>
#include <string_view>
#include <type_traits>

namespace strspan {

template <class T>
concept StrSpanKind = requires { typename T::StrSpanTrait{}; };

template <class T>
concept StringLike = std::is_convertible_v<T, std::string_view> || StrSpanKind<T>;

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
  struct StrSpanTrait {};

  const std::size_t begin_idx;
  const std::size_t end_idx;

 private:
  std::size_t _size;

 public:
  StrSpan(T& str, std::size_t begin_idx = 0, std::size_t end_idx = 0)
      : _str(str)
      , begin_idx(begin_idx)
      , end_idx(end_idx ? end_idx : detail::size_of_strlike(str))
      , _size(end_idx - begin_idx) {}

  StrSpan(const StrSpan& span, std::size_t begin_idx = 0, std::size_t end_idx = 0)
      : _str(span._str)
      , begin_idx(span.begin_idx + begin_idx)
      , end_idx(end_idx ? span.begin_idx + end_idx : span.end_idx)
      , _size(0) {
    _size = this->end_idx - this->begin_idx;
  }

  std::size_t size() const {
    return _size;
  }

  auto begin() const {
    return _str_begin() + begin_idx;
  }

  auto end() const {
    return _str_begin() + end_idx;
  }

  auto& operator[](std::size_t i) const {
    return *(begin() + i);
  }

  template <StringLike U>
  bool operator==(const U& str) const {
    if constexpr (std::is_same_v<std::decay_t<decltype(*this)>, U>) {
      if (begin() == str.begin() and end() == str.end()) return true;
    }

    if (detail::size_of_strlike(str) != _size) return false;

    for (std::size_t i = 0; i < _size; ++i)
      if ((*this)[i] != str[i]) return false;

    return true;
  }

  StrSpan slice(std::size_t from, std::size_t to) const {
    return StrSpan(*this, from, to);
  }
};

}  // namespace strspan

#endif  // _STRSPAN_HPP_
