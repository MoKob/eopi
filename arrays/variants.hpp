#ifndef EOPI_ARRAYS_VARIANTS_HPP_
#define EOPI_ARRAYS_VARIANTS_HPP_

#include <algorithm>
#include <cstddef>
#include <string>

namespace eopi {
namespace array {

inline std::string add_bitstrings(std::string lhs, std::string rhs) {
  std::reverse(lhs.begin(), lhs.end());
  std::reverse(rhs.begin(), rhs.end());

  if (lhs.size() < rhs.size())
    std::swap(lhs, rhs);

  int carry = 0;
  for (std::size_t i = 0; i < rhs.size(); ++i) {
    auto num = carry + (lhs[i] == '1') + (rhs[i] == '1');
    carry = num >= 2;
    lhs[i] = (num % 2) ? '1' : '0';
  }

  for (std::size_t i = rhs.size(); i < lhs.size() && carry; ++i) {
    if (lhs[i] == '1') {
      lhs[i] = '0';
    } else {
      carry = 0;
      lhs[i] = '1';
    }
  }

  if (carry)
    lhs.push_back('1');

  std::reverse(lhs.begin(), lhs.end());
  return lhs;
}

std::string inplace_trim(std::string str) {
  auto trimmed_end = str.begin();
  auto cur = str.begin();

  // skip over initial spaces
  while (cur != str.end() && *cur == ' ')
    ++cur;

  while (cur != str.end()) {
    if (*cur != ' ' || *(trimmed_end - 1) != ' ') {
      *trimmed_end = *cur;
      ++trimmed_end;
    }
    ++cur;
  }

  str.erase(trimmed_end, str.end());
  if (!str.empty() && str.back() == ' ')
    str.pop_back();

  return str;
}

} // namespace array
} // namespace eopi

#endif // EOPI_ARRAYS_VARIANTS_HPP_
