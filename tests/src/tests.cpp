#include "strspan.hpp"
#include <gtest/gtest.h>

using namespace strspan;

TEST(String, begin) {
  std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s.begin(), span.begin());
}

TEST(String, end) {
  std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s.end(), span.end());
}

TEST(ConstString, begin) {
  const std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s.begin(), span.begin());
}

TEST(ConstString, end) {
  const std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s.end(), span.end());
}

TEST(CharPtr, begin) {
  char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s, span.begin());
}

TEST(CharPtr, end) {
  char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s + 9, span.end());
}

TEST(ConstCharPtr, begin) {
  const char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s, span.begin());
}

TEST(ConstCharPtr, end) {
  const char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s + 9, span.end());
}

TEST(CharArray, begin) {
  char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s, span.begin());
}

TEST(CharArray, end) {
  char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s + 9, span.end());
}

TEST(ConstCharArray, begin) {
  const char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s, span.begin());
}

TEST(ConstCharArray, end) {
  const char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s + 9, span.end());
}

TEST(String, subscript) {
  std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
  s[5] = '0';
  EXPECT_EQ(s[5], span[5]);
}

TEST(ConstString, subscript) {
  const std::string s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
}

TEST(CharPtr, subscript) {
  char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
}

TEST(ConstCharPtr, subscript) {
  const char* s = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
}

TEST(CharArray, subscript) {
  char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
  s[5] = '0';
  EXPECT_EQ(s[5], span[5]);
}

TEST(ConstCharArray, subscript) {
  const char s[] = "123456789";
  StrSpan span(s);
  EXPECT_EQ(s[5], span[5]);
}
