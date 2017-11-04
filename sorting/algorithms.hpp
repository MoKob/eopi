#ifndef EOPI_SORTING_ALGORITHMS_HPP_
#define EOPI_SORTING_ALGORITHMS_HPP_

#include <algorithm>
#include <cstdint>
#include <vector>

namespace eopi {
namespace sorting {
namespace algorithms {

// compute the set intersection of two lists
inline std::vector<std::int32_t>
set_intersect(std::vector<std::int32_t> const &lhs,
              std::vector<std::int32_t> const &rhs) {
  std::vector<std::int32_t> result;
  std::size_t left = 0, right = 0;
  while (left < lhs.size() && right < rhs.size()) {
    if (lhs[left] < rhs[right]) {
      ++left;
    } else if (rhs[right] < lhs[left]) {
      ++right;
    } else {
      if (result.empty() || result.back() != lhs[left])
        result.push_back(lhs[left]);

      ++left;
      ++right;
    }
  }
  return result;
}

// resizes lhs to contain both elements of lhs/rhs
inline void semi_inplace_merge(std::vector<std::int32_t> &lhs,
                               std::vector<std::int32_t> const &rhs) {
  std::int64_t left_end = lhs.size(), right_end = rhs.size();
  lhs.resize(lhs.size() + rhs.size());
  std::int64_t out_end = lhs.size();

  auto const emplace = [&](auto val) { lhs[--out_end] = val; };
  while (left_end > 0 && right_end > 0) {
    if (lhs[left_end - 1] < rhs[right_end - 1])
      emplace(rhs[--right_end]);
    else
      emplace(lhs[--left_end]);
  }

  // transfer remaining items, if any
  while (right_end > 0)
    emplace(rhs[--right_end]);

  // left-end to 0 is already in the correct place
}

// for a set of durations, find pairs of min-max sum
inline std::vector<std::pair<std::uint32_t, std::uint32_t>>
schedule(std::vector<std::uint32_t> &durations) {
  std::sort(durations.begin(), durations.end());
  std::vector<std::pair<std::uint32_t, std::uint32_t>> results;
  results.reserve(durations.size() / 2);
  for (std::size_t i = 0; 2 * i < durations.size(); ++i) {
    results.push_back({*(durations.begin() + i), *(durations.rbegin() + i)});
  }
  return results;
}
} // namespace algorithms
} // namespace sorting
} // namespace eopi

#endif // EOPI_SORTING_ALGORITHMS_HPP_
