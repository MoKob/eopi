#ifndef EOPI_STACKS_ALGORITHMS_HPP_
#define EOPI_STACKS_ALGORITHMS_HPP_

#include <algorithm>
#include <cstdint>
#include <stack>
#include <string>

namespace eopi {
namespace stacks {
namespace algorithms {

// compute the length of the maximum substring with correct opening/closing
// braces
std::uint64_t maximum_valid_bracket_substring(std::string const &braces) {
  // a pair of braces () is valid, the same is (A) and A() if A is a string of
  // valid braces. We can compute the longest sequence, by counting the current
  // matching brackets and reset the entire state at every failing bracket

  // the length of previous valid segments, that we can add if all braces are
  // closed
  std::stack<std::uint64_t> previous_length;
  std::uint64_t current_valid = 0, max_valid = 0;

  // loop over all
  for (auto c : braces) {
    if (c == '(') {
      previous_length.push(current_valid);
      current_valid = 0;
      previous_length.push(0);
    } else {
      // closing off a brace. In case of an open brace, we get a valid pair:
      if (!previous_length.empty() && previous_length.top() == 0) {
        current_valid += 2;
        previous_length.pop();
        // can we combine the current sequence with a previous sequence?
        if (!previous_length.empty() && previous_length.top() != 0) {
          current_valid += previous_length.top();
          previous_length.pop();
        }
      } else {
        // a closing brace without a matching opening one indicates that we can
        // never re-use any sequence prior to it, clear state
        while (!previous_length.empty())
          previous_length.pop();
      }
      max_valid = std::max(max_valid, current_valid);
    }
  }

  return max_valid;
}

// recursively sort a stack (without release of memory, this requires O(N)
// additional space. The algorithm essentialy follows the insertion sort
// paradigm
void sort_descending(std::stack<int> &stack) {
  if (stack.empty())
    return;

  auto element = stack.top();
  stack.pop();
  sort_descending(stack);
  if (stack.empty() || stack.top() < element) {
    stack.push(element);
  } else {
    std::swap(stack.top(), element);
    sort_descending(stack);
    stack.push(element);
  }
}

} // namespace algorithms
} // namespace stacks
} // namespace eopi

#endif // EOPI_STACKS_ALGORITHM_HPP_
