#ifndef EOPI_RECURSION_ALGORITHMS_HPP_
#define EOPI_RECURSION_ALGORITHMS_HPP_

#include <cstdint>
#include <iostream>

namespace eopi {
namespace recursion {
namespace algorithms {

namespace details {
void hanoi_helper(std::int32_t from, std::int32_t to, std::uint32_t discs) {
  if (discs == 0)
    return;
  hanoi_helper(from, 3 - from - to, discs - 1);
  std::cout << "Move disc " << discs << " from " << from << " to " << to
            << std::endl;
  hanoi_helper(3 - from - to, to, discs - 1);
}
} // namespace details

// print a sequence of moves to solve the towers of hanoi for n towers
inline void hanoi(std::uint32_t n) { details::hanoi_helper(0, 1, n); }

} // namespace algorithms
} // namespace recursion
} // namespace eopi

#endif // EOPI_RECURSION_ALGORITHMS_HPP_
