#ifndef EOPI_DP_ALGORITHMS_HPP_
#define EOPI_DP_ALGORITHMS_HPP_

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

namespace eopi {
namespace dp {
namespace algorithms {

std::uint64_t football_combinations(std::int32_t final_score) {
  std::vector<std::uint64_t> combinations(final_score + 1, 0);
  std::vector<std::size_t> points = {2, 3, 7};
  combinations[0] = 1;
  for (auto p : points) {
    for (std::size_t i = p; i < combinations.size(); ++i) {
      combinations[i] += combinations[i - p];
    }
  }
  return combinations.back();
}

std::uint32_t levenshtein_distance(std::string const &lhs,
                                   std::string const &rhs) {
  // go for minimum memory usage
  if (rhs.size() > lhs.size())
    return levenshtein_distance(rhs, lhs);

  // Koenig swap
  using std::swap;
  // the previous row and the current row allow accessing the DP data, swapped
  // for every row
  std::vector<int> last_row(rhs.size() + 1, 0), current_row(rhs.size() + 1);
  std::iota(last_row.begin(), last_row.end(), 0);
  for (std::size_t i = 0; i < lhs.size(); ++i) {
    current_row[0] = i;
    for (std::size_t j = 0; j < rhs.size(); ++j) {
      current_row[j + 1] =
          std::min(last_row[j + 1] + 1, current_row[j - 1] + 1);
      if (lhs[i] == rhs[j])
        current_row[j + 1] = std::min(current_row[j + 1], last_row[j]);
      else
        current_row[j + 1] = std::min(current_row[j + 1], last_row[j]) + 1;
    }
    swap(last_row, current_row);
  }

  // the full edit distance is (due to the final swap) in the last_row, instead
  // of the current_row
  return last_row.back();
}

// find the most valuable trip through a 2d array going only down and right
// (top_left == [0][0])
std::uint32_t
fishing_trip(std::vector<std::vector<std::int32_t>> const &values) {
  // for reducing additional memory usage, we only remember the current row and
  // the last row, since we need to go left and up in the DP
  std::vector<std::uint32_t> last_row(values.size() + 1, 0),
      current_row(values.size() + 1, 0);

  using std::swap;
  // lower right is the desired value
  for (std::size_t row = 0; row < values.size(); ++row) {
    for (std::size_t col = 0; col < values[0].size(); ++col) {
      current_row[col + 1] =
          std::max(current_row[col], last_row[col + 1]) + values[row][col];
    }
    swap(last_row, current_row);
  }
  return last_row.back();
}

// compute the 0-1 knapsack problem, pseudopolinomial (capacity * |items|)
std::uint32_t knapsack_zero_one(
    std::vector<std::pair<std::uint32_t, std::uint32_t>> const &items,
    std::uint32_t capacity) {
  std::vector<std::uint32_t> values(capacity + 1, 0);

  for (auto item : items) {
    // weight > 0
    for (std::size_t i = values.size() - 1; i >= item.second; --i) {
      values[i] = std::max(values[i], values[i - item.second] + item.first);
    }
  }
  return values.back();
}
} // namespace algorithms
} // namespace dp
} // namespace eopi

#endif // EOPI_DP_ALGORITHMS_HPP_
