#ifndef _STRSPAN_HPP_
#define _STRSPAN_HPP_

#include <cstring>
#include <string>
#include <string_view>
#include <type_traits>

namespace strspan {

template <class T>
concept StrSpanKind = requires { typename T::StrSpanTrait{}; };

template <class T>
concept BuiltInStringKind = std::is_convertible_v<T, std::string_view>;

template <class T>
concept StringLike = BuiltInStringKind<T> || StrSpanKind<T>;

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
class StrSpan {
 private:
  T& _str;

  auto _str_begin() const {
    if constexpr (CharBasedString<T>) {
      return _str;
    } else {
      return _str.begin();
    }
  }

  template <class U>
  constexpr bool _is_same_type(const U&) const {
    return std::is_same_v<std::decay_t<decltype(*this)>, U>;
  }

 public:
  struct StrSpanTrait {};

 private:
  std::size_t _begin_idx;
  std::size_t _end_idx;
  std::size_t _size;

 public:
  StrSpan(T& str, std::size_t begin_idx = 0, std::size_t end_idx = 0)
      : _str(str)
      , _begin_idx(begin_idx)
      , _end_idx(end_idx ? end_idx : detail::size_of_strlike(str))
      , _size(_end_idx - _begin_idx) {}

  StrSpan(const StrSpan& span, std::size_t begin_idx = 0, std::size_t end_idx = 0)
      : _str(span._str)
      , _begin_idx(span._begin_idx + begin_idx)
      , _end_idx(end_idx ? span._begin_idx + end_idx : span._end_idx)
      , _size(_end_idx - _begin_idx) {}

  StrSpan& operator=(const StrSpan& span) {
    if (this == &span) return *this;
    _str = span._str;
    _begin_idx = span._begin_idx;
    _end_idx = span._end_idx;
    _size = span._size;
    return *this;
  }

  StrSpan& operator=(T& str) {
    _str = str;
    _begin_idx = 0;
    _end_idx = detail::size_of_strlike(str);
    _size = _end_idx;
    return *this;
  }

  std::size_t size() const {
    return _size;
  }

  auto begin() const {
    return _str_begin() + _begin_idx;
  }

  auto end() const {
    return _str_begin() + _end_idx;
  }

  auto& operator[](std::size_t i) const {
    return *(begin() + i);
  }

  template <StringLike U>
  bool operator==(const U& str) const {
    if constexpr (_is_same_type(str)) {
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

  auto& origin() const {
    return _str;
  }

  std::size_t begin_idx() const {
    return _begin_idx;
  }

  std::size_t end_idx() const {
    return _end_idx;
  }

  void begin_idx(std::size_t idx) {
    _begin_idx = idx;
    _size = _end_idx - _begin_idx;
  }

  void end_idx(std::size_t idx) {
    _end_idx = idx;
    _size = _end_idx - _begin_idx;
  }

  void set_bounds(std::size_t begin_idx, std::size_t end_idx) {
    _begin_idx = begin_idx;
    _end_idx = end_idx;
    _size = _end_idx - _begin_idx;
  }

  std::string_view to_view() const {
    if constexpr (CharBasedString<T>) {
      return std::string_view(begin(), size());
    } else {
      return std::string_view(begin(), end());
    }
  }

  std::string to_string() const {
    if constexpr (CharBasedString<T>) {
      return std::string(begin(), size());
    } else {
      return std::string(begin(), end());
    }
  }

  bool empty() const {
    return _size == 0;
  }
};

}  // namespace strspan

#endif  // _STRSPAN_HPP_
