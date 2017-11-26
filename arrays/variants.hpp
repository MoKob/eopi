#ifndef EOPI_ARRAYS_VARIANTS_HPP_
#define EOPI_ARRAYS_VARIANTS_HPP_

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

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

// return an vector consisting of all multiplications of elements of A, except
// for A[i] in B[i] without using division
std::vector<int> mult_array(std::vector<int> const &A) {
  auto helper = [](auto itr_a, auto end_a, auto itr_b) {
    int val = 1;
    for (; itr_a != end_a; ++itr_a, ++itr_b) {
      *itr_b *= val;
      val *= *itr_a;
    }
  };
  std::vector<int> B(A.size(), 1);
  helper(A.begin(), A.end(), B.begin());
  helper(A.rbegin(), A.rend(), B.rbegin());
  return B;
}

} // namespace array
} // namespace eopi

#endif // EOPI_ARRAYS_VARIANTS_HPP_
