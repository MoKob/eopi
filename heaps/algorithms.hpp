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

// compute the running median of a sequence
// requires O(N) space + O(logN) time for each insert
// Median is O(1)
class RunningMedian {
public:
  // push a new element
  void emplace(int value) {
    min_queue.push(value);
    if (min_queue.size() > max_queue.size() + 1) {
      max_queue.push(min_queue.top());
      min_queue.pop();
    }
  }

  // get the current median
  int median() const {
    if (min_queue.size() == max_queue.size())
      return 0.5 * (min_queue.top() + max_queue.top());
    else
      return min_queue.top();
  }

private:
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_queue;
  std::priority_queue<int> max_queue;
};

void compare_helper(std::vector<std::int32_t> const &heap,
                    std::size_t const pos, std::size_t const k,
                    std::int32_t value, std::size_t &equal,
                    std::size_t &larger) {
  // there will be no more larger/equal values in the heap, if heap[pos] < value
  if (larger >= k || pos >= heap.size() || heap[pos] < value)
    return;

  if (heap[pos] == value)
    ++equal;
  else
    ++larger;

  compare_helper(heap, 2 * (pos + 1) - 1, k, value, equal, larger);
  compare_helper(heap, 2 * (pos + 1), k, value, equal, larger);
}

// -1,0,1 find the relative size of value in comparison to heap[kth]
std::int32_t compare(std::vector<std::int32_t> const &heap, const std::size_t k,
                     const std::int32_t value) {
  std::size_t equal = 0, larger = 0;
  compare_helper(heap, 0, k, value, equal, larger);
  return larger >= k ? -1 : (larger + equal >= k ? 0 : 1);
}

} // namespace algorithms
} // namespace heaps
} // namespace eopi

#endif // EOPI_HEAPS_ALGORITHMS_HPP_
