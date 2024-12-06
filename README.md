# string-span
An implementation of a span for strings.

```C++
#include <string_view>
#include <string>
#include <regex>

#include <strspan.hpp>

int main() {
  std::regex re(R"([0-9]+)");
  const std::string s = "123456789";
  std::string_view sv(s);
  strspan::StrSpan ss(s);
  std::smatch sm;

  if (std::regex_search(s.cbegin(), s.cend(), sm, re))  // Ok
    std::cout << "First match: " << sm[0] << std::endl;

  // if (std::regex_search(sv.cbegin(), sv.cend(), sm, re)) // Wrong
  //   std::cout << "First match: " << sm[0] << std::endl;

  if (std::regex_search(ss.begin(), ss.end(), sm, re))  // Ok
    std::cout << "First match: " << sm[0] << std::endl;
}
```
