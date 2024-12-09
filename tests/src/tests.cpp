#include "strspan.hpp"
#include <gtest/gtest.h>

using namespace strspan;

TEST(begin, same) {
  std::string s = "123456789";

  StrSpan span1(s);
  StrSpan span2(span1);

  EXPECT_EQ(span1.begin(), span2.begin());
}

TEST(end, same) {
  std::string s = "123456789";

  StrSpan span1(s);
  StrSpan span2(span1);

  EXPECT_EQ(span1.end(), span2.end());
}

TEST(begin, string) {
  std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s.begin(), span.begin());
}

TEST(end, string) {
  std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s.end(), span.end());
}

TEST(begin, const_string) {
  const std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s.begin(), span.begin());
}

TEST(end, const_string) {
  const std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s.end(), span.end());
}

TEST(begin, char_ptr) {
  char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s, span.begin());
}

TEST(end, char_ptr) {
  char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s + 9, span.end());
}

TEST(begin, const_char_ptr) {
  const char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s, span.begin());
}

TEST(end, const_char_ptr) {
  const char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s + 9, span.end());
}

TEST(begin, char_array) {
  char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s, span.begin());
}

TEST(end, char_array) {
  char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s + 9, span.end());
}

TEST(begin, const_char_array) {
  const char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s, span.begin());
}

TEST(end, const_char_array) {
  const char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s + 9, span.end());
}

TEST(subscript, string) {
  std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
  s[5] = '0';
  EXPECT_EQ(s[5], span[5]);
}

TEST(subscript, const_string) {
  const std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
}

TEST(subscript, char_ptr) {
  char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
}

TEST(subscript, const_char_ptr) {
  const char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
}

TEST(subscript, char_array) {
  char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
  s[5] = '0';
  EXPECT_EQ(s[5], span[5]);
}

TEST(subscript, const_char_array) {
  const char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
}

TEST(comparison, same_string) {
  std::string s = "123456789";

  StrSpan span1(s, 1, 4);
  StrSpan span2(s, 1, 4);
  StrSpan span4(s, 1, 6);
  StrSpan span3(s, 2, 5);

  EXPECT_EQ(span1, span1);
  EXPECT_EQ(span2, span2);
  EXPECT_EQ(span3, span3);

  EXPECT_EQ(span1, span2);
  EXPECT_NE(span1, span3);
  EXPECT_NE(span1, span4);
}

TEST(comparison, same_string_const_char_ptr) {
  std::string s1 = "123456789";
  const char* s2 = "123456789";

  StrSpan span1(s1, 1, 4);
  StrSpan span2(s2, 1, 4);
  StrSpan span4(s1, 1, 6);
  StrSpan span3(s2, 2, 5);

  EXPECT_EQ(span1, span1);
  EXPECT_EQ(span2, span2);
  EXPECT_EQ(span3, span3);

  EXPECT_EQ(span1, span2);
  EXPECT_NE(span1, span3);
  EXPECT_NE(span1, span4);
}

TEST(comparison, string) {
  std::string s = "0123456789";
  std::string s1 = "123";

  StrSpan span1(s, 1, 4);
  StrSpan span2(s, 2, 6);

  EXPECT_EQ(s1, span1);
  EXPECT_NE(s1, span2);
}

TEST(comparison, string_const_char_ptr) {
  std::string s = "0123456789";
  const char* s1 = "123";

  StrSpan span1(s, 1, 4);
  StrSpan span2(s, 2, 6);

  EXPECT_EQ(s1, span1);
  EXPECT_NE(s1, span2);
}

TEST(slice, string) {
  std::string s = "0123456789";
  StrSpan span(s, 1, 8);  // "1234567"
  auto sliced = span.slice(2, 4);  // "34"

  EXPECT_EQ(sliced.size(), 2);
  EXPECT_EQ(span[2], sliced[0]);
  EXPECT_EQ(span[3], sliced[1]);
}

TEST(conv, from_string) {
  std::string s = "0123456789";
  StrSpan span(s, 1, 8);

  EXPECT_EQ(span.to_string(), span.to_view());
}

TEST(conv, from_char_string) {
  const char* s = "0123456789";
  StrSpan span(s, 1, 8);

  EXPECT_EQ(span.to_string(), span.to_view());
}

TEST(assign, string) {
  std::string s = "0123456789";
  std::string s1 = "9876543210";
  StrSpan span(s1);

  EXPECT_NE(span, s);

  span = s;
  EXPECT_EQ(span, s);
}

TEST(assign, const_char_ptr) {
  const char* s = "0123456789";
  const char* s1 = "9876543210";
  StrSpan span(s1);

  EXPECT_NE(span, s);

  span = s;
  EXPECT_EQ(span, s);
}

TEST(assign, string_view) {
  std::string_view s = "0123456789";
  std::string_view s1 = "9876543210";
  StrSpan span(s1);

  EXPECT_NE(span, s);

  span = s;
  EXPECT_EQ(span, s);
}

TEST(assign, same) {
  std::string_view s1 = "0123456789";
  std::string_view s2 = "9876543210";
  StrSpan span1(s1);
  StrSpan span2(s2);

  EXPECT_NE(span1, span2);

  span1 = span2;
  EXPECT_EQ(span1, span2);
}

TEST(chaned_bounds, string) {
  std::string s = "0123456789";
  StrSpan span1(s);
  StrSpan span2(s);

  span1.begin_idx(2);
  span1.end_idx(6);

  span2.set_bounds(2, 6);
}
