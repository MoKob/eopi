#ifndef EOPI_DP_ALGORITHMS_HPP_
#define EOPI_DP_ALGORITHMS_HPP_

#include <cstdint>
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

} // namespace algorithms
} // namespace dp
} // namespace eopi

#endif // EOPI_DP_ALGORITHMS_HPP_
