#ifndef EOPI_DP_ALGORITHMS_HPP_
#define EOPI_DP_ALGORITHMS_HPP_

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace std {
template <> struct hash<pair<uint32_t, uint32_t>> {
  size_t operator()(pair<uint32_t, uint32_t> const &value) const {
    return hash<uint32_t>()(value.first) ^ hash<uint32_t>()(value.second);
  }
};
}

namespace eopi {
namespace dp {
namespace algorithms {

inline std::uint64_t football_combinations(std::int32_t final_score) {
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

inline std::uint32_t levenshtein_distance(std::string const &lhs,
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
inline std::uint32_t
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
inline std::uint32_t knapsack_zero_one(
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

inline bool measure_helper(
    std::unordered_set<std::pair<std::uint32_t, std::uint32_t>> &cache,
    std::uint32_t min, std::uint32_t max) {
  // already found to be not possible
  if (cache.count(std::make_pair(min, max)))
    return false;

  if (min <= 230 && max >= 240) {
    std::cout << "A";
    return true;
  } else if (min <= 290 && max >= 310) {
    std::cout << "B";
    return true;
  } else if (min <= 500 && max >= 515) {
    std::cout << "C";
    return true;
  }

  if (min > 230 && max > 240 && measure_helper(cache, min - 230, max - 240)) {
    std::cout << "A";
    return true;
  }
  if (min > 290 && max > 310 && measure_helper(cache, min - 290, max - 310)) {
    std::cout << "B";
    return true;
  }
  if (min > 500 && max > 515 && measure_helper(cache, min - 500, max - 515)) {
    std::cout << "C";
    return true;
  }

  // not possible
  cache.insert(std::make_pair(min, max));
  return false;
}

inline bool measure(std::uint32_t min, std::uint32_t max) {
  std::unordered_set<std::pair<std::uint32_t, std::uint32_t>> cache;
  auto res = measure_helper(cache, min, max);
  if (res)
    std::cout << std::endl;
  return res;
}

// in contrast to the linear case, we need to walk through the array twice. In
// addition to the best value, we also track the current length. If the length
// is > n, there is a positive loop and no optimum exists (infinite optimum)
inline std::uint64_t
max_subarray_sum_cyclic(std::vector<std::int32_t> const &values) {
  std::uint64_t prev = 0;
  std::uint64_t length = 0;
  std::uint64_t best = 0;

  for (std::size_t i = 0; i < 2 * values.size(); ++i) {
    auto val = values[i % values.size()];
    // we summed the full array
    if (length >= values.size()) {
      do {
        val -= values[i - length];
        --length;
        // skip over all negatives as well
      } while (length && values[i - length] < 0);
    }
    if (val >= 0 || static_cast<std::uint64_t>(std::abs(val)) < prev) {
      prev += val;
      length++;
      best = std::max(best, prev);
    } else {
      // total sum becomes negative, start a new sequence
      prev = 0;
      length = 0;
    }
  }
  return best;
}

inline std::uint64_t critical_case_helper(
    std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint64_t>
        &cache,
    std::uint32_t const cases, std::uint32_t const drops) {
  // base cases
  if (cases == 1)
    return drops;
  if (cases == 0 || drops == 0)
    return 0;

  auto params = std::make_pair(cases, drops);
  auto itr = cache.find(params);
  if (itr != cache.end())
    return itr->second;

  cache[params] = critical_case_helper(cache, cases - 1, drops - 1) + 1 +
                  critical_case_helper(cache, cases, drops - 1);
  return cache[params];
}

inline std::uint64_t critical_case(std::uint32_t const cases,
                                   std::uint32_t const drops) {
  std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint64_t>
      cache;
  return critical_case_helper(cache, cases, drops);
}

inline std::uint32_t max_coin_gain_helper(
    std::vector<std::uint32_t> const &values,
    std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint64_t>
        &cache,
    std::size_t begin, std::size_t end, std::uint64_t total_sum) {
  // if only a single coin is left, it is the gain
  if (begin + 1 == end)
    return values[begin];

  auto params = std::make_pair(begin, end);
  if (cache.count(params))
    return cache[params];

  cache[params] =
      std::max((total_sum - max_coin_gain_helper(values, cache, begin + 1, end,
                                                 total_sum - values[begin])),
               (total_sum - max_coin_gain_helper(values, cache, begin, end - 1,
                                                 total_sum - values[end - 1])));

  return cache[params];
}

inline std::uint32_t max_coin_gain(std::vector<std::uint32_t> const &values) {
  std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint64_t>
      cache;
  auto total = std::accumulate(values.begin(), values.end(), 0);
  auto max_profit =
      max_coin_gain_helper(values, cache, 0, values.size(), total);
  std::cout << "Total: " << total << " Profit: " << max_profit << std::endl;
  return 2 * max_profit - total;
}

// find a non-decreasing subsequence (A_i <= A_j for i < j) within data
inline std::vector<std::int32_t>
longest_nondecreasing_subsequence(std::vector<std::int32_t> const &data) {
  // for every possible length, remember the smallest possible tail
  std::vector<std::int32_t> tails;
  // the positions of the tails within the array
  std::vector<std::int32_t> positions;
  // for every data entry, we remember the previous entry if it is part of our
  // list of tails
  std::vector<std::int32_t> parents(data.size(), -1);
  for (std::size_t i = 0; i < data.size(); ++i) {
    auto itr = std::upper_bound(tails.begin(), tails.end(), data[i]);
    if (itr == tails.end()) {
      if (!tails.empty()) {
        parents[i] = tails.back();
      }
      positions.push_back(i);
      tails.push_back(data[i]);
    } else {
      auto pos = std::distance(tails.begin(), itr);
      if (itr != tails.begin()) {
        parents[i] = positions[pos - 1];
      }
      *itr = data[i];
      positions[pos] = i;
    }
  }
  std::vector<std::int32_t> result;
  auto cur = positions.back();
  while (cur != -1) {
    result.push_back(data[cur]);
    cur = parents[cur];
  }
  std::reverse(result.begin(), result.end());
  return result;
}

} // namespace algorithms
} // namespace dp
} // namespace eopi

#endif // EOPI_DP_ALGORITHMS_HPP_
