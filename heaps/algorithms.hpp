#ifndef EOPI_HEAPS_ALGORITHMS_HPP_
#define EOPI_HEAPS_ALGORITHMS_HPP_

#include <cstddef>
#include <cstdint>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

namespace eopi {
namespace heaps {
namespace algorithms {

// lines of code in order of line. Return fair bonusses, so that every developer
// writing more spaghetti code is rewarded
inline std::int32_t bonusses(std::vector<std::int32_t> const &lines_of_codes) {
  std::vector<std::int32_t> tickets(lines_of_codes.size(), 1);
  for (std::size_t i = 0; i + 1 < lines_of_codes.size(); ++i) {
    if (lines_of_codes[i] < lines_of_codes[i + 1])
      tickets[i + 1] = tickets[i] + 1;
  }
  for (std::size_t i = lines_of_codes.size() - 1; i > 1; --i) {
    if (lines_of_codes[i] < lines_of_codes[i - 1] &&
        tickets[i - 1] <= tickets[i])
      tickets[i - 1] = tickets[i] + 1;
  }
  return std::accumulate(tickets.begin(), tickets.end(), 0);
}

} // namespace algorithms
} // namespace heaps
} // namespace eopi

#endif // EOPI_HEAPS_ALGORITHMS_HPP_
